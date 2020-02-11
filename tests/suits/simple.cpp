
#include <Linq.hpp>
#include <UnitTest++/UnitTest++.h>

#include <vector>



SUITE(SimpleMethods)
{
    
    std::vector<int> data{ -1, 1, -4, 5, 2, 3, 6, 5};
    std::vector<int> empty;
    

    bool isEven(const int& v) {
        return v % 2 == 0;
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
    
    TEST(Count)
    {
        auto count = simlinq::count(data);
        CHECK_EQUAL(count, 8);
        
        /* with lambda */
        count = simlinq::count(data, [](const auto& v) { return v % 2 != 0; });
        CHECK_EQUAL(count, 5);
        
        /* with function pointer */
        count = simlinq::count(data, isEven);
        CHECK_EQUAL(count, 3);
        
    }
}
