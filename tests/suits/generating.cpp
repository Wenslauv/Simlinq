
#include <Linq.hpp>
#include <UnitTest++/UnitTest++.h>

#include <vector>


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
}
