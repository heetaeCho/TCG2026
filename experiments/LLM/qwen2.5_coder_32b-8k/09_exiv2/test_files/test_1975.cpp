#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "XMLParserAdapter.hpp"



class XML_NodeTest_1975 : public ::testing::Test {

protected:

    std::string buffer;

};



TEST_F(XML_NodeTest_1975, Serialize_ElementNode_NoAttributesOrContent_1975) {

    XML_Node node(nullptr, "test", kElemNode);

    node.Serialize(&buffer);

    EXPECT_EQ(buffer, "<test/>");

}



TEST_F(XML_NodeTest_1975, Serialize_ElementNode_WithAttributes_1975) {

    XML_Node node(nullptr, "test", kElemNode);

    XML_Node attr(nullptr, "attr", kAttrNode);

    attr.value = "value";

    node.attrs.push_back(&attr);

    node.Serialize(&buffer);

    EXPECT_EQ(buffer, "<test attr=\"value\"/>");

}



TEST_F(XML_NodeTest_1975, Serialize_ElementNode_WithContent_1975) {

    XML_Node node(nullptr, "test", kElemNode);

    XML_Node content(nullptr, "content", kCDataNode);

    content.value = "data";

    node.content.push_back(&content);

    node.Serialize(&buffer);

    EXPECT_EQ(buffer, "<test>data</test>");

}



TEST_F(XML_NodeTest_1975, Serialize_ElementNode_WithAttributesAndContent_1975) {

    XML_Node node(nullptr, "test", kElemNode);

    XML_Node attr(nullptr, "attr", kAttrNode);

    attr.value = "value";

    node.attrs.push_back(&attr);

    XML_Node content(nullptr, "content", kCDataNode);

    content.value = "data";

    node.content.push_back(&content);

    node.Serialize(&buffer);

    EXPECT_EQ(buffer, "<test attr=\"value\">data</test>");

}



TEST_F(XML_NodeTest_1975, Serialize_AttrNode_1975) {

    XML_Node node(nullptr, "attr", kAttrNode);

    node.value = "value";

    node.Serialize(&buffer);

    EXPECT_EQ(buffer, " attr=\"value\"");

}



TEST_F(XML_NodeTest_1975, Serialize_CDataNode_1975) {

    XML_Node node(nullptr, "data", kCDataNode);

    node.value = "content";

    node.Serialize(&buffer);

    EXPECT_EQ(buffer, "content");

}



TEST_F(XML_NodeTest_1975, Serialize_PINode_Ignored_1975) {

    XML_Node node(nullptr, "pi", kPINode);

    node.value = "processing instruction";

    node.Serialize(&buffer);

    EXPECT_EQ(buffer, "");

}



TEST_F(XML_NodeTest_1975, Serialize_DefaultNamespaceHandling_1975) {

    XML_Node node(nullptr, "_dflt_:test", kElemNode);

    node.Serialize(&buffer);

    EXPECT_EQ(buffer, "<test/>");

}
