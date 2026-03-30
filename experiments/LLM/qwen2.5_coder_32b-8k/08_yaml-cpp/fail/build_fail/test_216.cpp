#include <gtest/gtest.h>

#include "yaml-cpp/node/detail/node_ref.h"

#include "yaml-cpp/emitterstyle.h"



using namespace YAML::detail;



class NodeRefTest_216 : public ::testing::Test {

protected:

    node_ref ref;

};



TEST_F(NodeRefTest_216, DefaultStyleIsBlock_216) {

    EXPECT_EQ(ref.style(), EmitterStyle::Block);

}



TEST_F(NodeRefTest_216, SetAndGetStyle_216) {

    ref.set_style(EmitterStyle::Flow);

    EXPECT_EQ(ref.style(), EmitterStyle::Flow);

}



// Additional tests for other observable behaviors can be added here



TEST_F(NodeRefTest_216, BoundaryCondition_SetAndGetStyle_216) {

    // Test with another style

    ref.set_style(EmitterStyle::Block);

    EXPECT_EQ(ref.style(), EmitterStyle::Block);

}
