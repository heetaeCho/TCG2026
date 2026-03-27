#include <gtest/gtest.h>

#include "XMPCore_Impl.hpp"

#include "XMPMeta-Serialize.cpp"



class SerializeCompactRDFSchemasTest_2114 : public ::testing::Test {

protected:

    XMP_Node xmpTree;

    XMP_VarString outputStr;

    const char* newline = "\n";

    const char* indentStr = "  ";

    XMP_Index baseIndent = 0;



    SerializeCompactRDFSchemasTest_2114() : xmpTree(nullptr, "testName", 0) {}



    void SetUp() override {

        outputStr.clear();

    }

};



TEST_F(SerializeCompactRDFSchemasTest_2114, NormalOperation_2114) {

    XMP_Node schemaNode(&xmpTree, "schemaName", 0);

    xmpTree.children.push_back(schemaNode);



    SerializeCompactRDFSchemas(xmpTree, outputStr, newline, indentStr, baseIndent);



    EXPECT_TRUE(outputStr.find("<rdf:Description rdf:about=\"testName\"") != std::string::npos);

    EXPECT_TRUE(outputStr.find("</rdf:Description>") != std::string::npos);

}



TEST_F(SerializeCompactRDFSchemasTest_2114, NoChildren_2114) {

    SerializeCompactRDFSchemas(xmpTree, outputStr, newline, indentStr, baseIndent);



    EXPECT_EQ(outputStr, "<rdf:Description rdf:about=\"testName\"/>\n");

}



TEST_F(SerializeCompactRDFSchemasTest_2114, MultipleChildren_2114) {

    XMP_Node schemaNode1(&xmpTree, "schemaName1", 0);

    XMP_Node schemaNode2(&xmpTree, "schemaName2", 0);

    xmpTree.children.push_back(schemaNode1);

    xmpTree.children.push_back(schemaNode2);



    SerializeCompactRDFSchemas(xmpTree, outputStr, newline, indentStr, baseIndent);



    EXPECT_TRUE(outputStr.find("<rdf:Description rdf:about=\"testName\"") != std::string::npos);

    EXPECT_TRUE(outputStr.find("</rdf:Description>") != std::string::npos);

}



TEST_F(SerializeCompactRDFSchemasTest_2114, Indentation_2114) {

    baseIndent = 2;



    SerializeCompactRDFSchemas(xmpTree, outputStr, newline, indentStr, baseIndent);



    EXPECT_TRUE(outputStr.find("    <rdf:Description rdf:about=\"testName\"") != std::string::npos);

    EXPECT_TRUE(outputStr.find("  </rdf:Description>") != std::string::npos);

}



TEST_F(SerializeCompactRDFSchemasTest_2114, NewlineAndIndentation_2114) {

    SerializeCompactRDFSchemas(xmpTree, outputStr, newline, indentStr, baseIndent);



    EXPECT_TRUE(outputStr.find("\n  <rdf:Description rdf:about=\"testName\"") != std::string::npos);

    EXPECT_TRUE(outputStr.find("  </rdf:Description>\n") != std::string::npos);

}
