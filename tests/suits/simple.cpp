
#include <Linq.hpp>
#include <UnitTest++/UnitTest++.h>

#include <vector>



SUITE(SimpleMethods)
{
    
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
    
}
