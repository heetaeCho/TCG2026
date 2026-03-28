#include <gtest/gtest.h>

#include "XMPMeta-Serialize.cpp"

#include "XMPCore_Impl.hpp"



class SerializeCompactRDFElemPropsTest_2113 : public ::testing::Test {

protected:

    XMP_Node parentNode;

    XMP_VarString outputStr;

    const char* newline = "\n";

    const char* indentStr = "  ";

    XMP_Index indent = 0;



    void SetUp() override {

        parentNode = XMP_Node(nullptr, "parentNode", kXMP_PropCompositeMask);

        outputStr.clear();

    }



    void TearDown() override {

        parentNode.RemoveChildren();

        parentNode.RemoveQualifiers();

    }

};



TEST_F(SerializeCompactRDFElemPropsTest_2113, NormalOperationWithSimpleChild_2113) {

    XMP_Node* childNode = new XMP_Node(&parentNode, "child", "value", 0);

    parentNode.children.push_back(childNode);



    SerializeCompactRDFElemProps(&parentNode, outputStr, newline, indentStr, indent);



    EXPECT_EQ(outputStr, "  <child>value\n</child>\n");

}



TEST_F(SerializeCompactRDFElemPropsTest_2113, NormalOperationWithMultipleChildren_2113) {

    XMP_Node* childNode1 = new XMP_Node(&parentNode, "child1", "value1", 0);

    XMP_Node* childNode2 = new XMP_Node(&parentNode, "child2", "value2", 0);

    parentNode.children.push_back(childNode1);

    parentNode.children.push_back(childNode2);



    SerializeCompactRDFElemProps(&parentNode, outputStr, newline, indentStr, indent);



    EXPECT_EQ(outputStr, "  <child1>value1\n</child1>\n  <child2>value2\n</child2>\n");

}



TEST_F(SerializeCompactRDFElemPropsTest_2113, NormalOperationWithURIValue_2113) {

    XMP_Node* childNode = new XMP_Node(&parentNode, "child", "", kXMP_PropValueIsURI);

    childNode->value = "http://example.com";

    parentNode.children.push_back(childNode);



    SerializeCompactRDFElemProps(&parentNode, outputStr, newline, indentStr, indent);



    EXPECT_EQ(outputStr, "  <child rdf:resource=\"http://example.com\"/>\n");

}



TEST_F(SerializeCompactRDFElemPropsTest_2113, NormalOperationWithEmptyValue_2113) {

    XMP_Node* childNode = new XMP_Node(&parentNode, "child", "", 0);

    parentNode.children.push_back(childNode);



    SerializeCompactRDFElemProps(&parentNode, outputStr, newline, indentStr, indent);



    EXPECT_EQ(outputStr, "  <child/>\n");

}



TEST_F(SerializeCompactRDFElemPropsTest_2113, NormalOperationWithArrayChild_2113) {

    XMP_Node* childNode = new XMP_Node(&parentNode, "child", "", kXMP_PropValueIsArray);

    parentNode.children.push_back(childNode);



    SerializeCompactRDFElemProps(&parentNode, outputStr, newline, indentStr, indent);



    EXPECT_EQ(outputStr, "  <child>\n    <rdf:Seq/>\n  </child>\n");

}



TEST_F(SerializeCompactRDFElemPropsTest_2113, NormalOperationWithStructChild_2113) {

    XMP_Node* childNode = new XMP_Node(&parentNode, "child", "", kXMP_PropValueIsStruct);

    parentNode.children.push_back(childNode);



    SerializeCompactRDFElemProps(&parentNode, outputStr, newline, indentStr, indent);



    EXPECT_EQ(outputStr, "  <child rdf:parseType=\"Resource\">\n  </child>\n");

}



TEST_F(SerializeCompactRDFElemPropsTest_2113, ErrorCaseWithMixedQualifiersAndElementFields_2113) {

    XMP_Node* childNode = new XMP_Node(&parentNode, "child", "", kXMP_PropValueIsStruct);

    parentNode.children.push_back(childNode);



    XMP_Node* qualifierNode = new XMP_Node(childNode, "rdf:resource", "http://example.com", 0);

    childNode->qualifiers.push_back(qualifierNode);



    XMP_Node* fieldNode = new XMP_Node(childNode, "field", "value", 0);

    childNode->children.push_back(fieldNode);



    EXPECT_THROW(SerializeCompactRDFElemProps(&parentNode, outputStr, newline, indentStr, indent), std::exception);

}



TEST_F(SerializeCompactRDFElemPropsTest_2113, BoundaryConditionWithNoChildren_2113) {

    SerializeCompactRDFElemProps(&parentNode, outputStr, newline, indentStr, indent);



    EXPECT_EQ(outputStr, "");

}
