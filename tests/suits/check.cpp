
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
    
    TEST(AnyConditional)
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
    
    TEST(ContainsConditional)
    {
        auto condition = [](const auto& f, const auto& s) { return s + f == 10 ; };
        
        CHECK(simlinq::Contains(data, 5, condition));
        CHECK(not simlinq::Contains(data, -1, condition));
    }
    
    TEST(SequenceEqual)
    {
        std::vector<int> origin         { 1,2,3,4,5 };
        std::vector<int> candidate_1    { 1,2,3,4,4,5};
        std::vector<int> candidate_2    { 1,2,3,4,5};
        
        CHECK(not simlinq::SequenceEqual(origin, candidate_1));
        
        CHECK(simlinq::SequenceEqual(origin, candidate_2));
        CHECK(simlinq::SequenceEqual(origin, origin));
    }
    
    TEST(SequenceEqualComparer)
    {
        std::vector<int> origin         { 1,2,3,4,5 };
        std::vector<int> candidate     { 2,4,6,8,10 };
            
        CHECK(simlinq::SequenceEqual(origin, candidate, [](const auto& f, const auto& v) { return f*2 == v; }));
        CHECK(not simlinq::SequenceEqual(origin, candidate, [](const auto& f, const auto& v){ return f + 1 == v;} ));
    }
        
}
