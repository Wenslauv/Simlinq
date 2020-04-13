
#include <Linq.hpp>
#include <UnitTest++/UnitTest++.h>

#include <vector>
#include <string>


SUITE(GeneratingMethods) {
    
    std::vector<int> first{ 1, 2, 3, 4, 5};
    std::vector<int> second{ 3, 4, 5, -1, -4};
    std::vector<int> empty;
    
    
    bool isEven(const int& v) {
        return v % 2 == 0;
    }
    
    bool isOdd(const int& v) {
        return v % 2 != 0;
    }
    
    bool isZero(const int& v) {
        return v == 0;
    }
    
    
    TEST(Concat)
    {
        CHECK(simlinq::Concat(first, second) == std::vector<int>({ 1, 2, 3, 4, 5, 3, 4, 5, -1, -4}));
        CHECK(simlinq::Concat(first, empty) == first);
        CHECK(simlinq::Concat(second, empty) == second);
    }
    
    TEST(DefaultIfEmpty)
    {
        CHECK(simlinq::DefaultIfEmpty(first) == first);
        CHECK(simlinq::DefaultIfEmpty(empty) == std::vector<int>({0}));
    }
    
    TEST(DefaultIfEmptyValue)
    {
        CHECK(simlinq::DefaultIfEmpty(first) == first);
        CHECK(simlinq::DefaultIfEmpty(empty, 5) == std::vector<int>({5}));
    }
    
    TEST(Distinct)
    {
        CHECK(simlinq::Distinct(first, second) == std::vector<int>({1,2}));
        CHECK(simlinq::Distinct(first, empty) == first);
    }
    
    
    TEST(DistinctComparer)
    {
        CHECK(simlinq::Distinct(first,
                                second,
                                [](int l, int r) { return l*2 < r; })
              == std::vector<int>({1,5}));
    }
    
    
    TEST(Empty)
    {
        using vector_t = std::vector<int>;
        CHECK(simlinq::Empty<vector_t>() == vector_t());
    }
    
    
    TEST(Intersect)
    {
        CHECK(simlinq::Intersect(first, second) == std::vector<int>({3,4,5}));
        CHECK(simlinq::Intersect(first, empty) == empty);
        CHECK(simlinq::Intersect(second, empty) == empty);
    }
    
    
    TEST(IntersectComparer)
    {
        CHECK(simlinq::Intersect(first, second, [](int f, int s){ return f*2 < s; }) == std::vector<int>({2, 3, 4}));
    }
    
    TEST(OfType)
    {
        struct A { virtual void do_smth() {}; virtual ~A() = default; };
        struct B : public A {};
        struct C : public A {};
        
        std::vector<A*> data{ new B, new B, new C, new B };
        
        CHECK(simlinq::OfType<C*>(data).size() == 1);
        CHECK(simlinq::OfType<B*>(data).size() == 3);
        CHECK(simlinq::OfType<A*>(data).size() == 4);
        
        for (auto& d : data) {
            delete d;
        }
    }
    
    
    /* OrderBy required data */
    struct S {
        std::string name;
        int age;
    };
    
    using S_collection = std::vector<S>;
       
    auto compare_collections = [](const S_collection& lhv, const S_collection& rhv) {
        if (std::size(lhv) != std::size(rhv))
            return false;
        
        for (int i = 0; i < std::size(lhv); ++i) {
            if ((lhv[i].name != rhv[i].name) or (lhv[i].age != rhv[i].age))
                return false;
        }
        
        return true;
    };
    
    
    TEST(OrderBy)
    {
        S_collection data{ {"C", 10}, {"A", 15 }, {"B", 20 } };
        S_collection expected{  {"A", 15 }, {"B", 20 }, {"C", 10} };
        
        auto key = [](const S& s) { return s.name; };
        CHECK_EQUAL(compare_collections(simlinq::OrderBy(data, key), expected), true);
    }
    
    TEST(OrderByComparer)
    {
        S_collection data{ {"C", 10}, {"A", 15 }, {"B", 20 } };
        S_collection expected{ {"B", 20 }, { "A", 15 }, {"C", 10} };
        
        auto key = [](const S& s) { return s.age; };
        auto compare = [](const int& lhv, const int& rhv) { return lhv > rhv; };
          
        CHECK_EQUAL(compare_collections(simlinq::OrderBy(data, key, compare), expected), true);
    }
    
    TEST(OrderByDescending)
    {
        S_collection data{ {"C", 10}, {"A", 15 }, {"B", 20 } };
        S_collection expected{ {"C", 10}, {"B", 20 }, {"A", 15 }};
        
        auto key = [](const S& s) { return s.name; };
        CHECK_EQUAL(compare_collections(simlinq::OrderByDescending(data, key), expected), true);
    }
    
    TEST(OrderByDescendingComparer)
    {
        S_collection data{ {"C", 10}, {"A", 15 }, {"B", 20 } };
        S_collection expected{ {"B", 20 }, { "A", 15 }, {"C", 10} };
        
        auto key = [](const S& s) { return s.age; };
        auto compare = [](const int& lhv, const int& rhv) { return lhv < rhv; };
        CHECK_EQUAL(compare_collections(simlinq::OrderByDescending(data, key, compare), expected), true);
    }
    
    TEST(Repeat)
    {
        using type_t = std::vector<int>;
        
        CHECK(simlinq::Repeat<type_t>(5, 4) == (type_t{5,5,5,5}));
        CHECK(simlinq::Repeat<type_t>(5,0) == empty);
    }
    
    TEST(Skip)
    {
        std::vector<int> v{ 1,2,3,4,5};
        
        CHECK(simlinq::Skip(v, 3) == std::vector<int>({4,5}));
        CHECK(simlinq::Skip(v, v.size()) == std::vector<int>());
        CHECK(simlinq::Skip(v, 10) == std::vector<int>());
    }
    
    TEST(SkipWhile)
    {
        std::vector<int> oneEven { 1, 3, 5, 6, 7, 8};
        CHECK(simlinq::SkipWhile(oneEven, isOdd) == std::vector<int>({6,7,8}));
        
        std::vector<int> noEven { 1, 3, 5, 7 };
        CHECK(simlinq::SkipWhile(noEven, isOdd) == std::vector<int>());
    }
    
    TEST(SkipWhileIndexed)
    {
        std::vector<int> oneEven { 1, 3, 5, 6, 7, 8};
        auto condition = [](uint32_t indx, int value ) {  return value % 2 != 0 and indx < 5; };
        CHECK(simlinq::SkipWhile<uint32_t>(oneEven, condition) == std::vector<int>({6, 7, 8}));
        
        std::vector<int> noEven { 1, 3, 5, 7 };
        CHECK(simlinq::SkipWhile<uint32_t>(noEven, condition) == std::vector<int>());
    }
    
    TEST(Take)
    {
        std::vector<int> expected{ 1, 2};
        
        CHECK(simlinq::Take<2>(first) == expected);
        CHECK(simlinq::Take<3>(first) != expected);
        CHECK(simlinq::Take<2>(first) != empty);
    }
    
    TEST(TakeWhile)
    {
        std::vector<int> data{ 1,2,3,4,5};
        
        CHECK(simlinq::TakeWhile(data, [](int v)
                                 { return v < 4;}) == std::vector<int>({ 1, 2, 3}));
        CHECK(simlinq::TakeWhile(data, [](int v)
        { return v < 10;}) == data);
    }
    
    TEST(TakeWhileIndexed)
    {
        std::vector<int> data{ 1, 2, 3, 4, 5};
        
        CHECK(simlinq::TakeWhile<uint32_t>(data, [](uint32_t idx, int value){ return idx < 4 and value < 3; } ) == std::vector<int>({1,2}));
        CHECK(simlinq::TakeWhile<uint32_t>(data, [](uint32_t idx, int value) { return idx > 5 and value < 3; }) == std::vector<int>());
    }
    
    TEST(Union)
    {
        auto intersect = simlinq::Union(first, second);
        CHECK_EQUAL(intersect.size(), 7);
        
        std::vector<int> result(intersect.begin(), intersect.end());
        std::vector<int> expected_result{1, 2, 3, 4, 5, -1, -4};
        
        std::sort(std::begin(result), std::end(result));
        std::sort(std::begin(expected_result), std::end(expected_result));
        
        CHECK(result == expected_result);
    }
    
    TEST(UnionComparer)
    {
        /* Stub */
    }
    
    TEST(Where)
    {
        auto sequence = simlinq::Where(first, isEven);
        CHECK_EQUAL(sequence.size(), 2);
        
        std::vector<int> expected{ 2, 4};
        CHECK(expected == sequence);
        
        CHECK_EQUAL(simlinq::Where(first, isZero).size(), 0);
    }
   
    TEST(WherePredicate)
    {
        /* Stub */
    }
    
    
    TEST(Zip)
    {
        std::vector<std::string> strings{ "first", "second", "third" };
        auto zip = simlinq::Zip(first,
                                strings,
                                [](int f, const std::string& s)
                                {
                                    return std::to_string(f) + " : " + s;
                                });
        CHECK(zip == std::vector<std::string>({ "1 : first", "2 : second", "3 : third" }));
    }
}

