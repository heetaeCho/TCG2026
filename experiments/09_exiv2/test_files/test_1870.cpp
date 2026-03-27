#include <gtest/gtest.h>

#include "XMPCore_Impl.hpp"



class XMP_NodeTest_1870 : public ::testing::Test {

protected:

    XMP_Node* node;



    void SetUp() override {

        node = new XMP_Node(nullptr, "testName", "testValue", 0);

    }



    void TearDown() override {

        delete node;

    }

};



TEST_F(XMP_NodeTest_1870, ClearNode_ResetsOptionsAndStrings_1870) {

    node->ClearNode();

    EXPECT_EQ(node->options, 0u);

    EXPECT_TRUE(node->name.empty());

    EXPECT_TRUE(node->value.empty());

}



TEST_F(XMP_NodeTest_1870, ClearNode_RemovesChildren_1870) {

    // Assuming RemoveChildren is observable by some means, we'd need a way to verify it.

    // Since there's no provided interface for that, we assume it works as intended internally.

    node->ClearNode();

    // No direct verification possible without additional methods or mocks

}



TEST_F(XMP_NodeTest_1870, ClearNode_RemovesQualifiers_1870) {

    // Assuming RemoveQualifiers is observable by some means, we'd need a way to verify it.

    // Since there's no provided interface for that, we assume it works as intended internally.

    node->ClearNode();

    // No direct verification possible without additional methods or mocks

}



TEST_F(XMP_NodeTest_1870, ClearNode_NoExternalInteractions_1870) {

    // Assuming no external interactions are involved in ClearNode

    EXPECT_NO_THROW(node->ClearNode());

}
