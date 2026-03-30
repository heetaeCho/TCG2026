#include <gtest/gtest.h>

#include "yaml-cpp/node/impl.h"

#include "yaml-cpp/emitterstyle.h"



using namespace YAML;



class NodeTest : public ::testing::Test {

protected:

    Node node;

};



TEST_F(NodeTest_561, SetStyle_DefaultBehavior_561) {

    EmitterStyle::value initial_style = node.Style();

    node.SetStyle(EmitterStyle::Block);

    EXPECT_NE(initial_style, node.Style());

}



TEST_F(NodeTest_561, SetStyle_BlockStyle_561) {

    node.SetStyle(EmitterStyle::Block);

    EXPECT_EQ(node.Style(), EmitterStyle::Block);

}



TEST_F(NodeTest_561, SetStyle_FlowStyle_561) {

    node.SetStyle(EmitterStyle::Flow);

    EXPECT_EQ(node.Style(), EmitterStyle::Flow);

}



// Assuming no other styles are defined, this test checks for invalid input

// Since the internal behavior is unknown and we cannot access private state,

// We assume setting an invalid style would not change the current style.

TEST_F(NodeTest_561, SetStyle_InvalidInput_561) {

    EmitterStyle::value initial_style = node.Style();

    node.SetStyle(static_cast<EmitterStyle::value>(-1));

    EXPECT_EQ(initial_style, node.Style());

}
