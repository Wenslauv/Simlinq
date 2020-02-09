
#include <Linq.hpp>
#include <UnitTest++/UnitTest++.h>

#include <vector>



SUITE(SimpleMethods)
{
    
    bool isEven(const int& v) {
        return v % 2 == 0;
    }
    
    
    TEST(Min)
    {
        
        std::vector<int> data{ -1, 0 , 1};
        auto min = simlinq::Min(data);
        
        REQUIRE CHECK(min != std::nullopt);
        CHECK_EQUAL(*min, -1);
        
        std::vector<int> empty;
        min = simlinq::Min(empty);
        CHECK(min == std::nullopt);
    }
    
    
    TEST(Max)
    {
        
    }
    
    
    TEST(Count)
    {
        std::vector<int> src{ 1, 2, 3, 4, 5};
        
        auto count = simlinq::count(src);
        CHECK_EQUAL(count, 5);
        
        /* with lambda */
        count = simlinq::count(src, [](const auto& v) { return v % 2 != 0; });
        CHECK_EQUAL(count, 3);
        
        /* with function pointer */
        count = simlinq::count(src, isEven);
        CHECK_EQUAL(count, 2);
        
    }
    
}
