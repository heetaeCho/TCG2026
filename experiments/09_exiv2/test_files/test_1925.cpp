#include <gtest/gtest.h>

#include "XMPMeta-GetSet.cpp"

#include "XMPCore_Impl.hpp"

#include "XMP_Const.h"



class SetNodeTest_1925 : public ::testing::Test {

protected:

    void SetUp() override {

        node = new XMP_Node(nullptr, "testName", kXMP_PropValueIsURI);

    }



    void TearDown() override {

        delete node;

    }



    XMP_Node* node;

};



TEST_F(SetNodeTest_1925, SetStringValue_1925) {

    const char* newValue = "newValue";

    SetNode(node, newValue, 0);

    EXPECT_EQ(node->value, newValue);

}



TEST_F(SetNodeTest_1925, SetValueWithDeleteExistingOption_1925) {

    node->value = "initialValue";

    SetNode(node, "newValue", kXMP_DeleteExisting);

    EXPECT_EQ(node->value, "newValue");

}



TEST_F(SetNodeTest_1925, SetEmptyStringWithoutValue_1925) {

    SetNode(node, nullptr, 0);

    EXPECT_TRUE(node->value.empty());

}



TEST_F(SetNodeTest_1925, SetCompositeMaskWithValueThrowsError_1925) {

    node->options |= kXMP_PropCompositeMask;

    EXPECT_THROW(SetNode(node, "newValue", 0), XMP_Error);

}



TEST_F(SetNodeTest_1925, ChangeArrayTypeToStructThrowsError_1925) {

    node->options |= kXMP_PropArrayIsOrdered;

    EXPECT_THROW(SetNode(node, nullptr, kXMP_PropValueIsStruct), XMP_Error);

}



TEST_F(SetNodeTest_1925, ChangeStructTypeToArrayThrowsError_1925) {

    node->options |= kXMP_PropValueIsStruct;

    EXPECT_THROW(SetNode(node, nullptr, kXMP_PropArrayIsOrdered), XMP_Error);

}



TEST_F(SetNodeTest_1925, SetOptionsWithoutDeleteExisting_1925) {

    XMP_OptionBits newOptions = kXMP_PropHasQualifiers;

    SetNode(node, "newValue", newOptions);

    EXPECT_EQ((node->options & kXMP_PropHasQualifiers), kXMP_PropHasQualifiers);

}



TEST_F(SetNodeTest_1925, SetOptionsWithDeleteExisting_1925) {

    XMP_OptionBits initialOptions = node->options;

    XMP_OptionBits newOptions = kXMP_PropHasQualifiers | kXMP_DeleteExisting;

    SetNode(node, "newValue", newOptions);

    EXPECT_EQ((node->options & kXMP_PropHasQualifiers), kXMP_PropHasQualifiers);

    EXPECT_NE(node->options, initialOptions);

}
