#include <Linq.hpp>
#include <UnitTest++/UnitTest++.h>

#include <vector>


SUITE(CharacteristicMethods)
{
    std::vector<int> data{ -1, 1, -4, 5, 2, 3, 6, 5};
    std::vector<int> empty;
    
    bool isEven(const int& v) { return v % 2 == 0; }
    bool isOdd(const int& v)  { return v % 2 != -0; }
    bool isZero(const int& v) { return v == 0; }
    
    
    TEST(Count)
    {
        CHECK_EQUAL(simlinq::Count(data), 8);
        CHECK_EQUAL(simlinq::Count(empty), 0);
    }
    
    TEST(CountConditional)
    {
        CHECK_EQUAL(simlinq::Count(data,isEven), 3);
        CHECK_EQUAL(simlinq::Count(empty, isZero), 0);
    }
    
    
    TEST(LongCount)
    {
        CHECK_EQUAL(simlinq::LongCount(data), 8);
        CHECK_EQUAL(simlinq::LongCount(empty), 0);
    }
    
    TEST(LongCountConditional)
    {
        CHECK_EQUAL(simlinq::LongCount(data,isEven), 3);
        CHECK_EQUAL(simlinq::LongCount(empty, isZero), 0);
    }
    
}
