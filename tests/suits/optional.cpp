
#include <Linq.hpp>
#include <UnitTest++/UnitTest++.h>

#include <vector>



SUITE(OptionalMethods)
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
 
    
    TEST(Min)
    {
        auto min = simlinq::Min(data);
        
        REQUIRE CHECK(min != std::nullopt);
        CHECK_EQUAL(*min, -4);
        
        min = simlinq::Min(empty);
        CHECK(min == std::nullopt);
    }
    
    TEST(MinTransform)
    {
        auto transform = [](const auto& v){ return 10 - v; };
        auto min = simlinq::Min(data, transform);
        
        REQUIRE CHECK(min != std::nullopt);
        CHECK_EQUAL(*min, 4);
        
        min = simlinq::Min(empty, transform);
        CHECK(min == std::nullopt);
    }
    
    TEST(Max)
    {
        auto max = simlinq::Max(data);
        
        REQUIRE CHECK(max != std::nullopt);
        CHECK_EQUAL(*max, 6);
        
        max = simlinq::Max(empty);
        CHECK(max == std::nullopt);
    }
    
    TEST(MaxTransform)
    {
        auto transform = [](const auto& v){ return 10 - v; };
        auto max = simlinq::Max(data, transform);
        
        REQUIRE CHECK(max != std::nullopt);
        CHECK_EQUAL(*max, 14);
        
        max = simlinq::Max(empty, transform);
        CHECK(max == std::nullopt);
    }

    
    TEST(First)
    {
        auto first = simlinq::First(data);
        REQUIRE CHECK(first != std::nullopt);
        CHECK_EQUAL(*first, data[0]);
        
        first = simlinq::First(empty);
        CHECK(first == std::nullopt);
    }
    
    TEST(FirstConditional)
    {
        auto positive = [](const auto& v) { return v > 0;};
        auto first = simlinq::First(data, positive);
        REQUIRE CHECK(first != std::nullopt);
        CHECK_EQUAL(*first, 1);
        
        CHECK(simlinq::First(empty, positive) == std::nullopt);
        CHECK(simlinq::First(data, [](const auto& v){ return v == 0;}) == std::nullopt);
    }
    
    TEST(FirstOrDefault)
    {
        CHECK_EQUAL(simlinq::FirstOrDefault(data), data[0]);
        CHECK_EQUAL(simlinq::FirstOrDefault(empty), int());
    }
    
    TEST(FirstOrDefaultConditional)
    {
        CHECK_EQUAL(simlinq::FirstOrDefault(data, isEven), -4);
        CHECK_EQUAL(simlinq::FirstOrDefault(data, isZero), int());
        CHECK_EQUAL(simlinq::FirstOrDefault(empty, isOdd), int());
    }
    
    TEST(Last)
    {
        auto last = simlinq::Last(data);
        REQUIRE CHECK(last != std::nullopt);
        CHECK_EQUAL(*last, data.back());
        
        CHECK(simlinq::Last(empty) == std::nullopt);
    }
    
    TEST(LastConditional)
    {
        auto negative = [](const auto& v) { return v < 0;};
        auto last = simlinq::Last(data, negative);
        REQUIRE CHECK(last != std::nullopt);
        CHECK_EQUAL(*last, -4);
        
        CHECK(simlinq::Last(empty, negative) == std::nullopt);
        CHECK(simlinq::Last(data, [](const auto& v){ return v == 0;}) == std::nullopt);

    }
    
    TEST(LastOrDefault)
    {
        CHECK_EQUAL(simlinq::LastOrDefault(data), data.back());
        CHECK_EQUAL(simlinq::LastOrDefault(empty), int());
    }
    
    TEST(LastOrDefaultConditional)
    {
        CHECK_EQUAL(simlinq::LastOrDefault(data, isEven), 6);
        CHECK_EQUAL(simlinq::LastOrDefault(data, isZero), int());
        CHECK_EQUAL(simlinq::LastOrDefault(empty, isOdd), int());
    }
    
    TEST(ElementAt)
    {
        CHECK(*simlinq::ElementAt(data, 3) == 5);
        CHECK(simlinq::ElementAt(data, -1) == std::nullopt);
        CHECK(simlinq::ElementAt(data, 10) == std::nullopt);
    }
    
    TEST(ElementAtOrDefault)
    {
        CHECK_EQUAL(simlinq::ElementAtOrDefault(data, 3), 5);
        CHECK_EQUAL(simlinq::ElementAtOrDefault(data, -1), int());
        CHECK_EQUAL(simlinq::ElementAtOrDefault(data, 10), int());
    }
}
