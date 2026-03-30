#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "XMPCore_Impl.hpp"

#include "XMLParserAdapter.hpp"



using namespace testing;



TEST(RDF_LiteralPropertyElementTest_2132, PutWithValidAttributesAndContent_2132) {

    XMP_Node xmpParent(nullptr, "parent", 0);

    XML_Node xmlNode(nullptr, "xmlNode", kElemNode);



    // Add valid attributes

    XML_Node attrLang(nullptr, "xml:lang", kAttrNode);

    attrLang.value = "en";

    xmlNode.attrs.push_back(&attrLang);



    // Add valid content

    XML_Node cdataNode(nullptr, "", kCDataNode);

    cdataNode.value = "valid content";

    xmlNode.content.push_back(&cdataNode);



    EXPECT_NO_THROW(RDF_LiteralPropertyElement(&xmpParent, xmlNode, true));

}



TEST(RDF_LiteralPropertyElementTest_2132, PutWithInvalidAttributes_2132) {

    XMP_Node xmpParent(nullptr, "parent", 0);

    XML_Node xmlNode(nullptr, "xmlNode", kElemNode);



    // Add invalid attribute

    XML_Node attrInvalid(nullptr, "invalid:attr", kAttrNode);

    attrInvalid.value = "value";

    xmlNode.attrs.push_back(&attrInvalid);



    EXPECT_THROW(RDF_LiteralPropertyElement(&xmpParent, xmlNode, true), XMP_Error);

}



TEST(RDF_LiteralPropertyElementTest_2132, PutWithMissingContent_2132) {

    XMP_Node xmpParent(nullptr, "parent", 0);

    XML_Node xmlNode(nullptr, "xmlNode", kElemNode);



    // Add valid attribute

    XML_Node attrLang(nullptr, "xml:lang", kAttrNode);

    attrLang.value = "en";

    xmlNode.attrs.push_back(&attrLang);



    EXPECT_THROW(RDF_LiteralPropertyElement(&xmpParent, xmlNode, true), XMP_Error);

}



TEST(RDF_LiteralPropertyElementTest_2132, PutWithInvalidContentType_2132) {

    XMP_Node xmpParent(nullptr, "parent", 0);

    XML_Node xmlNode(nullptr, "xmlNode", kElemNode);



    // Add valid attribute

    XML_Node attrLang(nullptr, "xml:lang", kAttrNode);

    attrLang.value = "en";

    xmlNode.attrs.push_back(&attrLang);



    // Add invalid content type

    XML_Node invalidContentNode(nullptr, "", kPINode); // Not a CDATA node

    invalidContentNode.value = "invalid content";

    xmlNode.content.push_back(&invalidContentNode);



    EXPECT_THROW(RDF_LiteralPropertyElement(&xmpParent, xmlNode, true), XMP_Error);

}



TEST(RDF_LiteralPropertyElementTest_2132, PutWithMultipleCDATASections_2132) {

    XMP_Node xmpParent(nullptr, "parent", 0);

    XML_Node xmlNode(nullptr, "xmlNode", kElemNode);



    // Add valid attribute

    XML_Node attrLang(nullptr, "xml:lang", kAttrNode);

    attrLang.value = "en";

    xmlNode.attrs.push_back(&attrLang);



    // Add multiple CDATA sections as content

    XML_Node cdataNode1(nullptr, "", kCDataNode);

    cdataNode1.value = "first part of ";

    xmlNode.content.push_back(&cdataNode1);



    XML_Node cdataNode2(nullptr, "", kCDataNode);

    cdataNode2.value = "second part";

    xmlNode.content.push_back(&cdataNode2);



    EXPECT_NO_THROW(RDF_LiteralPropertyElement(&xmpParent, xmlNode, true));

}
