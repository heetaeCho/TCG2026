#include <gtest/gtest.h>

#include "XMPCore_Impl.hpp"

#include "XMP_Const.h"



class CompareNodeValuesTest_2143 : public ::testing::Test {

protected:

    XMP_Node* leftNode;

    XMP_Node* rightNode;



    void SetUp() override {

        leftNode = new XMP_Node(nullptr, "left", 0);

        rightNode = new XMP_Node(nullptr, "right", 0);

    }



    void TearDown() override {

        delete leftNode;

        delete rightNode;

    }

};



TEST_F(CompareNodeValuesTest_2143, SimplePropsSameValue_2143) {

    leftNode->value = "same";

    rightNode->value = "same";

    EXPECT_FALSE(CompareNodeValues(leftNode, rightNode));

}



TEST_F(CompareNodeValuesTest_2143, SimplePropsLeftLess_2143) {

    leftNode->value = "left";

    rightNode->value = "right";

    EXPECT_TRUE(CompareNodeValues(leftNode, rightNode));

}



TEST_F(CompareNodeValuesTest_2143, SimplePropsRightLess_2143) {

    leftNode->value = "right";

    rightNode->value = "left";

    EXPECT_FALSE(CompareNodeValues(leftNode, rightNode));

}



TEST_F(CompareNodeValuesTest_2143, CompositePropsLeftLess_2143) {

    leftNode->options = kXMP_PropValueIsArray;

    rightNode->options = kXMP_PropValueIsStruct;

    EXPECT_TRUE(CompareNodeValues(leftNode, rightNode));

}



TEST_F(CompareNodeValuesTest_2143, CompositePropsRightLess_2143) {

    leftNode->options = kXMP_PropValueIsStruct;

    rightNode->options = kXMP_PropValueIsArray;

    EXPECT_FALSE(CompareNodeValues(leftNode, rightNode));

}



TEST_F(CompareNodeValuesTest_2143, CompositePropsSameForm_2143) {

    leftNode->options = kXMP_PropValueIsStruct;

    rightNode->options = kXMP_PropValueIsStruct;

    EXPECT_FALSE(CompareNodeValues(leftNode, rightNode));

}



TEST_F(CompareNodeValuesTest_2143, MixedPropsLeftSimpleRightComposite_2143) {

    leftNode->value = "simple";

    rightNode->options = kXMP_PropValueIsArray;

    EXPECT_TRUE(CompareNodeValues(leftNode, rightNode));

}



TEST_F(CompareNodeValuesTest_2143, MixedPropsLeftCompositeRightSimple_2143) {

    leftNode->options = kXMP_PropValueIsArray;

    rightNode->value = "simple";

    EXPECT_FALSE(CompareNodeValues(leftNode, rightNode));

}
