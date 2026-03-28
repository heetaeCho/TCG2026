#include <gtest/gtest.h>

#include "XMPCore_Impl.hpp"



class XMP_NodeTest_1871 : public ::testing::Test {

protected:

    XMP_Node* node;



    void SetUp() override {

        node = new XMP_Node(nullptr, "testName", 0);

    }



    void TearDown() override {

        delete node;

    }

};



TEST_F(XMP_NodeTest_1871, ConstructorWithName_1871) {

    EXPECT_EQ(node->name, "testName");

}



TEST_F(XMP_NodeTest_1871, ConstructorWithParentAndName_1871) {

    XMP_Node parent(nullptr, "parentName", 0);

    XMP_Node child(&parent, "childName", 0);

    EXPECT_EQ(child.parent, &parent);

    EXPECT_EQ(child.name, "childName");

}



TEST_F(XMP_NodeTest_1871, ConstructorWithParentNameAndValue_1871) {

    XMP_Node parent(nullptr, "parentName", 0);

    XMP_Node child(&parent, "childName", "childValue", 0);

    EXPECT_EQ(child.parent, &parent);

    EXPECT_EQ(child.name, "childName");

    EXPECT_EQ(child.value, "childValue");

}



TEST_F(XMP_NodeTest_1871, RemoveChildrenDoesNotThrow_1871) {

    EXPECT_NO_THROW(node->RemoveChildren());

}



TEST_F(XMP_NodeTest_1871, RemoveQualifiersDoesNotThrow_1871) {

    EXPECT_NO_THROW(node->RemoveQualifiers());

}



TEST_F(XMP_NodeTest_1871, ClearNodeDoesNotThrow_1871) {

    EXPECT_NO_THROW(node->ClearNode());

}



// Boundary conditions

TEST_F(XMP_NodeTest_1871, ConstructorWithEmptyName_1871) {

    XMP_Node node(nullptr, "", 0);

    EXPECT_EQ(node.name, "");

}



TEST_F(XMP_NodeTest_1871, ConstructorWithNullParent_1871) {

    XMP_Node node(nullptr, "testName", 0);

    EXPECT_EQ(node.parent, nullptr);

}



// Exceptional or error cases

// Since the class does not throw exceptions based on the provided interface, we skip these.

```


