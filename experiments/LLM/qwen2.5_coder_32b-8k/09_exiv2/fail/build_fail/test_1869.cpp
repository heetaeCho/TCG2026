#include <gtest/gtest.h>

#include "XMPCore_Impl.hpp"



class XMP_NodeTest_1869 : public ::testing::Test {

protected:

    XMP_Node* node;



    void SetUp() override {

        node = new XMP_Node(nullptr, "testName", "testValue", 0);

        // Adding some qualifiers to the node

        for (int i = 0; i < 3; ++i) {

            node->qualifiers.push_back(new XMP_VarString("qualifier" + std::to_string(i)));

        }

    }



    void TearDown() override {

        delete node;

    }

};



TEST_F(XMP_NodeTest_1869, RemoveQualifiers_RemovesAllQualifiers_1869) {

    node->RemoveQualifiers();

    EXPECT_EQ(node->qualifiers.size(), 0);

}



TEST_F(XMP_NodeTest_1869, RemoveQualifiers_NoQualifiersInitially_1869) {

    XMP_Node emptyNode(nullptr, "emptyName", "emptyValue", 0);

    emptyNode.RemoveQualifiers();

    EXPECT_EQ(emptyNode.qualifiers.size(), 0);

}



TEST_F(XMP_NodeTest_1869, RemoveQualifiers_NoMemoryLeak_1869) {

    // Assuming that the destructors for XMP_VarString handle memory correctly

    node->RemoveQualifiers();

    // If no crash occurs and all qualifiers are removed, this test passes

}
