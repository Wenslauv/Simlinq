
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
        return v % 2 != -0;
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
    
    TEST(Repeat)
    {
        using type_t = std::vector<int>;
        
        CHECK(simlinq::Repeat<type_t>(5, 4) == (type_t{5,5,5,5}));
        CHECK(simlinq::Repeat<type_t>(5,0) == empty);
    }
    
    
    TEST(Take)
    {
        std::vector<int> expected{ 1, 2};
        
        CHECK(simlinq::Take<2>(first) == expected);
        CHECK(simlinq::Take<3>(first) != expected);
        CHECK(simlinq::Take<2>(first) != empty);
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
