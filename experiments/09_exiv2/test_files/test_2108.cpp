#include <gtest/gtest.h>

#include "XMPCore_Impl.hpp"

#include "XMP_Const.h"



// Test fixture for CanBeRDFAttrProp function

class CanBeRDFAttrPropTest_2108 : public ::testing::Test {

protected:

    XMP_Node* propNode;



    void SetUp() override {

        propNode = new XMP_Node(nullptr, "testName", 0);

    }



    void TearDown() override {

        delete propNode;

    }

};



// Normal operation: Name does not start with '[', no qualifiers, and no URI or composite options

TEST_F(CanBeRDFAttrPropTest_2108, NormalOperation_2108) {

    EXPECT_TRUE(CanBeRDFAttrProp(propNode));

}



// Boundary condition: Name starts with '['

TEST_F(CanBeRDFAttrPropTest_2108, NameStartsWithBracket_2108) {

    propNode->name = "[testName";

    EXPECT_FALSE(CanBeRDFAttrProp(propNode));

}



// Boundary condition: Node has qualifiers

TEST_F(CanBeRDFAttrPropTest_2108, HasQualifiers_2108) {

    XMP_Node* qualifierNode = new XMP_Node(propNode, "qualifier", 0);

    propNode->qualifiers.push_back(qualifierNode);

    EXPECT_FALSE(CanBeRDFAttrProp(propNode));

    delete qualifierNode;

}



// Boundary condition: Node has URI option

TEST_F(CanBeRDFAttrPropTest_2108, HasURIOption_2108) {

    propNode->options = kXMP_PropValueIsURI;

    EXPECT_FALSE(CanBeRDFAttrProp(propNode));

}



// Boundary condition: Node has composite options

TEST_F(CanBeRDFAttrPropTest_2108, HasCompositeOptions_2108) {

    propNode->options = kXMP_PropCompositeMask;

    EXPECT_FALSE(CanBeRDFAttrProp(propNode));

}
