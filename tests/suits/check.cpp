
#include <Linq.hpp>
#include <UnitTest++/UnitTest++.h>

#include <vector>


SUITE(CheckMethods)
{
    std::vector<int> data{ -1, 1, -4, 5, 2, 3, 6, 5};
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
    
    TEST(All)
    {
        std::vector<int> odds{ 1, 3, 5, -1, -3, -5};
        CHECK(simlinq::All(odds, isOdd));
        CHECK(not simlinq::All(data, isEven));
    }
    
    TEST(Any) {
        CHECK(simlinq::Any(data));
        CHECK(not simlinq::Any(empty));
    }
    
    TEST(AnyCondition)
    {
        CHECK(simlinq::Any(data, isOdd));
        CHECK(not simlinq::Any(empty, isOdd));
        CHECK(not simlinq::Any(data, isZero));
    }
    
    TEST(Contains)
    {
        CHECK(simlinq::Contains(data, -4));
        CHECK(not simlinq::Contains(data, 10));
        CHECK(not simlinq::Contains(empty, 0));
    }
    
    TEST(ContainsCondition)
    {
        auto condition = [](const auto& f, const auto& s) { return s + f == 10 ; };
        
        CHECK(simlinq::Contains(data, 5, condition));
        CHECK(not simlinq::Contains(data, -1, condition));
    }
        
}
