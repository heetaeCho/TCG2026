#include <gtest/gtest.h>

#include "yaml-cpp/emittermanip.h"



class AnchorTest_14 : public ::testing::Test {};



TEST_F(AnchorTest_14, AnchorCreationWithNonEmptyString_14) {

    YAML::_Anchor anchor = YAML::Anchor("test");

    EXPECT_EQ(anchor.m_value, "test");

}



TEST_F(AnchorTest_14, AnchorCreationWithEmptyString_14) {

    YAML::_Anchor anchor = YAML::Anchor("");

    EXPECT_EQ(anchor.m_value, "");

}



// Since the _Anchor class is not fully exposed and we are treating it as a black box,

// we cannot directly test for exceptional cases or internal state. However, we can

// verify that the function behaves correctly with boundary conditions.
