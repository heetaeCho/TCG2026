#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Mock or include necessary headers for XMP_Node and related classes/functions

using namespace testing;



class ParseRDFFixture : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code, if any, goes here

    }



    void TearDown() override {

        // Teardown code, if any, goes here

    }

};



// Normal operation tests



TEST_F(ParseRDFFixture, FixupQualifiedNode_NormalCase_2123) {

    XMP_Node parent(nullptr, "parent", kXMP_PropValueIsStruct);

    XMP_Node valueNode(&parent, "rdf:value", "value", 0);

    XMP_Node qualNode(&valueNode, "qualifier", "qualValue", 0);



    parent.children.push_back(&valueNode);

    valueNode.qualifiers.push_back(&qualNode);



    FixupQualifiedNode(&parent);



    EXPECT_EQ(parent.qualifiers.size(), 1);

    EXPECT_STREQ(parent.qualifiers[0]->name.c_str(), "qualifier");

    EXPECT_EQ(parent.options & kXMP_PropHasQualifiers, kXMP_PropHasQualifiers);

}



// Boundary conditions tests



TEST_F(ParseRDFFixture, FixupQualifiedNode_EmptyQualifiers_2123) {

    XMP_Node parent(nullptr, "parent", kXMP_PropValueIsStruct);

    XMP_Node valueNode(&parent, "rdf:value", "value", 0);



    parent.children.push_back(&valueNode);



    FixupQualifiedNode(&parent);



    EXPECT_EQ(parent.qualifiers.size(), 0);

    EXPECT_EQ(parent.options & kXMP_PropHasQualifiers, 0);

}



TEST_F(ParseRDFFixture, FixupQualifiedNode_SingleChild_2123) {

    XMP_Node parent(nullptr, "parent", kXMP_PropValueIsStruct);

    XMP_Node valueNode(&parent, "rdf:value", "value", 0);



    parent.children.push_back(&valueNode);



    FixupQualifiedNode(&parent);



    EXPECT_EQ(parent.qualifiers.size(), 0);

    EXPECT_EQ(parent.options & kXMP_PropHasQualifiers, 0);

}



// Exceptional or error cases tests



TEST_F(ParseRDFFixture, FixupQualifiedNode_NoChildren_2123) {

    XMP_Node parent(nullptr, "parent", kXMP_PropValueIsStruct);



    EXPECT_THROW(FixupQualifiedNode(&parent), XMP_Error);

}



TEST_F(ParseRDFFixture, FixupQualifiedNode_WrongChildName_2123) {

    XMP_Node parent(nullptr, "parent", kXMP_PropValueIsStruct);

    XMP_Node valueNode(&parent, "wrongName", "value", 0);



    parent.children.push_back(&valueNode);



    EXPECT_THROW(FixupQualifiedNode(&parent), XMP_Error);

}



TEST_F(ParseRDFFixture, FixupQualifiedNode_DuplicateQualifiers_2123) {

    XMP_Node parent(nullptr, "parent", kXMP_PropValueIsStruct);

    XMP_Node valueNode(&parent, "rdf:value", "value", 0);

    XMP_Node qualNode1(&valueNode, "qualifier", "qualValue1", 0);

    XMP_Node qualNode2(&valueNode, "qualifier", "qualValue2", 0);



    parent.children.push_back(&valueNode);

    valueNode.qualifiers.push_back(&qualNode1);

    valueNode.qualifiers.push_back(&qualNode2);



    EXPECT_THROW(FixupQualifiedNode(&parent), XMP_Error);

}



TEST_F(ParseRDFFixture, FixupQualifiedNode_RedundantLang_2123) {

    XMP_Node parent(nullptr, "parent", kXMP_PropValueIsStruct | kXMP_PropHasLang);

    XMP_Node valueNode(&parent, "rdf:value", "value", 0);

    XMP_Node langQual(&valueNode, "xml:lang", "en-US", kXMP_PropHasLang);



    parent.children.push_back(&valueNode);

    valueNode.qualifiers.push_back(&langQual);



    EXPECT_THROW(FixupQualifiedNode(&parent), XMP_Error);

}



TEST_F(ParseRDFFixture, FixupQualifiedNode_DuplicateLangQualifier_2123) {

    XMP_Node parent(nullptr, "parent", kXMP_PropValueIsStruct);

    XMP_Node valueNode(&parent, "rdf:value", "value", 0);

    XMP_Node langQual(&valueNode, "xml:lang", "en-US", kXMP_PropHasLang);



    parent.children.push_back(&valueNode);

    valueNode.qualifiers.push_back(&langQual);

    parent.children.push_back(&langQual);



    EXPECT_THROW(FixupQualifiedNode(&parent), XMP_Error);

}
