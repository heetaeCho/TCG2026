#include <gtest/gtest.h>

#include "yaml-cpp/node/detail/node_data.h"



using namespace YAML::detail;



class NodeDataTest_209 : public ::testing::Test {

protected:

    node_data data;

};



TEST_F(NodeDataTest_209, DefaultTagReturnsEmptyString_209) {

    EXPECT_EQ(data.tag(), "");

}



TEST_F(NodeDataTest_209, SetAndGetTag_209) {

    std::string test_tag = "!test";

    data.set_tag(test_tag);

    EXPECT_EQ(data.tag(), test_tag);

}



// Boundary conditions

TEST_F(NodeDataTest_209, EmptyStringAsTag_209) {

    std::string empty_tag = "";

    data.set_tag(empty_tag);

    EXPECT_EQ(data.tag(), empty_tag);

}



// Exceptional or error cases (if observable through the interface)

// In this case, there are no exceptional/error cases that can be directly observed from the provided interface.



// Verification of external interactions

// No external interactions to verify in this class as per the provided interface.

```


