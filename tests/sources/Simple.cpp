#include "../../include/Linq.hpp"



#include "../../third-party/unittest-cpp/UnitTest++/UnitTest++.h"

#include <vector>


SUITE(SimpleMethods)
{
    
    TEST(MaxInt)
    {
        std::vector<int> data{1,2,3,4,5};
        auto max = simlinq::max(data);
        CHECK_EQUAL(max, 5);
    }
    
}
