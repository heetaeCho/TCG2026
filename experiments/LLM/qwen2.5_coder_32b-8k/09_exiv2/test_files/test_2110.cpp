#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "XMPMeta-Serialize.cpp"

#include "XMPCore_Impl.hpp"



class SerializePrettyRDFPropertyTest_2110 : public ::testing::Test {

protected:

    XMP_Node* propNode;

    XMP_VarString outputStr;

    XMP_StringPtr newline = "\n";

    XMP_StringPtr indentStr = "  ";

    XMP_Index indent = 0;



    void SetUp() override {

        propNode = new XMP_Node(nullptr, "", 0);

    }



    void TearDown() override {

        delete propNode;

    }

};



TEST_F(SerializePrettyRDFPropertyTest_2110, EmptyNode_2110) {

    SerializePrettyRDFProperty(propNode, outputStr, newline, indentStr, indent);

    EXPECT_EQ(outputStr, "<>\n");

}



TEST_F(SerializePrettyRDFPropertyTest_2110, NodeWithValue_2110) {

    propNode->value = "testValue";

    SerializePrettyRDFProperty(propNode, outputStr, newline, indentStr, indent);

    EXPECT_EQ(outputStr, "<>testValue\n");

}



TEST_F(SerializePrettyRDFPropertyTest_2110, NodeWithURI_2110) {

    propNode->options = kXMP_PropValueIsURI;

    propNode->value = "http://example.com";

    SerializePrettyRDFProperty(propNode, outputStr, newline, indentStr, indent);

    EXPECT_EQ(outputStr, "< rdf:resource=\"http://example.com\"/>\n");

}



TEST_F(SerializePrettyRDFPropertyTest_2110, NodeWithQualifiers_2110) {

    XMP_Node* qual = new XMP_Node(nullptr, "qualName", "qualValue", 0);

    propNode->qualifiers.push_back(qual);

    SerializePrettyRDFProperty(propNode, outputStr, newline, indentStr, indent);

    EXPECT_EQ(outputStr, "< qualName=\"qualValue\">\"\n</>\n");

    delete qual;

}



TEST_F(SerializePrettyRDFPropertyTest_2110, NodeWithMultipleQualifiers_2110) {

    XMP_Node* qual1 = new XMP_Node(nullptr, "qualName1", "qualValue1", 0);

    XMP_Node* qual2 = new XMP_Node(nullptr, "qualName2", "qualValue2", 0);

    propNode->qualifiers.push_back(qual1);

    propNode->qualifiers.push_back(qual2);

    SerializePrettyRDFProperty(propNode, outputStr, newline, indentStr, indent);

    EXPECT_EQ(outputStr, "< qualName1=\"qualValue1\" qualName2=\"qualValue2\">\"\n</>\n");

    delete qual1;

    delete qual2;

}



TEST_F(SerializePrettyRDFPropertyTest_2110, NodeWithGeneralQualifiersAndRDFResourceQual_2110) {

    XMP_Node* qual1 = new XMP_Node(nullptr, "qualName", "qualValue", 0);

    XMP_Node* qual2 = new XMP_Node(nullptr, "rdf:resource", "http://example.com", 0);

    propNode->qualifiers.push_back(qual1);

    propNode->qualifiers.push_back(qual2);

    EXPECT_THROW(SerializePrettyRDFProperty(propNode, outputStr, newline, indentStr, indent), XMP_Error);

    delete qual1;

    delete qual2;

}



TEST_F(SerializePrettyRDFPropertyTest_2110, NodeWithChildren_2110) {

    XMP_Node* child = new XMP_Node(nullptr, "childName", "childValue", 0);

    propNode->children.push_back(child);

    SerializePrettyRDFProperty(propNode, outputStr, newline, indentStr, indent);

    EXPECT_EQ(outputStr, "<>\n  <childName>childValue\n</childName>\n</>\n");

    delete child;

}



TEST_F(SerializePrettyRDFPropertyTest_2110, NodeWithArrayChildren_2110) {

    propNode->options = kXMP_PropValueIsArray;

    XMP_Node* child1 = new XMP_Node(nullptr, "childName", "childValue1", 0);

    XMP_Node* child2 = new XMP_Node(nullptr, "childName", "childValue2", 0);

    propNode->children.push_back(child1);

    propNode->children.push_back(child2);

    SerializePrettyRDFProperty(propNode, outputStr, newline, indentStr, indent);

    EXPECT_EQ(outputStr, "<>\n  <rdf:Bag rdf:parseType=\"Collection\">\n    <rdf:li>childValue1</rdf:li>\n    <rdf:li>childValue2</rdf:li>\n  </rdf:Bag>\n</>\n");

    delete child1;

    delete child2;

}



TEST_F(SerializePrettyRDFPropertyTest_2110, NodeWithStructChildren_2110) {

    propNode->options = kXMP_PropValueIsStruct;

    XMP_Node* child = new XMP_Node(nullptr, "childName", "childValue", 0);

    propNode->children.push_back(child);

    SerializePrettyRDFProperty(propNode, outputStr, newline, indentStr, indent);

    EXPECT_EQ(outputStr, "< rdf:parseType=\"Resource\">\n  <childName>childValue\n</childName>\n</>\n");

    delete child;

}



TEST_F(SerializePrettyRDFPropertyTest_2110, NodeWithRDFResourceQualAndComplexField_2110) {

    XMP_Node* qual = new XMP_Node(nullptr, "rdf:resource", "http://example.com", 0);

    XMP_Node* child = new XMP_Node(nullptr, "childName", "childValue", kXMP_PropCompositeMask);

    propNode->qualifiers.push_back(qual);

    propNode->children.push_back(child);

    EXPECT_THROW(SerializePrettyRDFProperty(propNode, outputStr, newline, indentStr, indent), XMP_Error);

    delete qual;

    delete child;

}



TEST_F(SerializePrettyRDFPropertyTest_2110, NodeWithChildrenAndIndentation_2110) {

    XMP_Node* child = new XMP_Node(nullptr, "childName", "childValue", 0);

    propNode->children.push_back(child);

    indent = 1;

    SerializePrettyRDFProperty(propNode, outputStr, newline, indentStr, indent);

    EXPECT_EQ(outputStr, "  <>\n    <childName>childValue\n  </childName>\n  </>\n");

    delete child;

}
