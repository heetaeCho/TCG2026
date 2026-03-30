#include <gtest/gtest.h>

#include "XMPCore_Impl.hpp"



class XMP_AutoNodeTest_1872 : public ::testing::Test {

protected:

    void SetUp() override {

        // No setup needed for this class as it's stateless and we treat implementation as a black box.

    }



    void TearDown() override {

        // No teardown needed for this class.

    }

};



TEST_F(XMP_AutoNodeTest_1872, DefaultConstructorSetsNodePtrToNull_1872) {

    XMP_AutoNode node;

    EXPECT_EQ(node.nodePtr, nullptr);

}



TEST_F(XMP_AutoNodeTest_1872, ConstructorWithParentAndNameAllocatesNewNode_1872) {

    XMP_Node* parent = new XMP_Node();

    XMP_StringPtr name = "test_name";

    XMP_OptionBits options = 0;



    XMP_AutoNode node(parent, name, options);

    EXPECT_NE(node.nodePtr, nullptr);



    delete parent;

}



TEST_F(XMP_AutoNodeTest_1872, ConstructorWithParentAndNameStringAllocatesNewNode_1872) {

    XMP_Node* parent = new XMP_Node();

    XMP_VarString name("test_name");

    XMP_OptionBits options = 0;



    XMP_AutoNode node(parent, name, options);

    EXPECT_NE(node.nodePtr, nullptr);



    delete parent;

}



TEST_F(XMP_AutoNodeTest_1872, ConstructorWithParentNameAndValueAllocatesNewNode_1872) {

    XMP_Node* parent = new XMP_Node();

    XMP_StringPtr name = "test_name";

    XMP_StringPtr value = "test_value";

    XMP_OptionBits options = 0;



    XMP_AutoNode node(parent, name, value, options);

    EXPECT_NE(node.nodePtr, nullptr);



    delete parent;

}



TEST_F(XMP_AutoNodeTest_1872, ConstructorWithParentNameAndValueStringAllocatesNewNode_1872) {

    XMP_Node* parent = new XMP_Node();

    XMP_VarString name("test_name");

    XMP_VarString value("test_value");

    XMP_OptionBits options = 0;



    XMP_AutoNode node(parent, name, value, options);

    EXPECT_NE(node.nodePtr, nullptr);



    delete parent;

}



TEST_F(XMP_AutoNodeTest_1872, DestructorDeletesNodePtr_1872) {

    XMP_Node* parent = new XMP_Node();

    XMP_StringPtr name = "test_name";

    XMP_OptionBits options = 0;



    {

        XMP_AutoNode node(parent, name, options);

        EXPECT_NE(node.nodePtr, nullptr);

    } // Node should be deleted here



    delete parent;

}
