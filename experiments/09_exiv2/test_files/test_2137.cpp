#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "XMP_Const.h"

#include "XMLParserAdapter.hpp"

#include "XMPCore_Impl.hpp"



using namespace testing;



class RDF_EmptyPropertyElementTest : public Test {

protected:

    XMP_Node xmpParent;

    XML_Node xmlNode;



    void SetUp() override {

        xmpParent = XMP_Node(nullptr, "", 0);

        xmlNode.parent = nullptr;

        xmlNode.name = "test";

        xmlNode.kind = 0;

    }

};



TEST_F(RDF_EmptyPropertyElementTest_2137, NormalOperationNoAttributes_2137) {

    RDF_EmptyPropertyElement(&xmpParent, xmlNode, false);

    EXPECT_TRUE(xmpParent.children.empty());

}



TEST_F(RDF_EmptyPropertyElementTest_2137, NormalOperationWithRDFValue_2137) {

    XML_NodePtr attr = new XML_Node(nullptr, "rdf:value", 0);

    attr->value = "test_value";

    xmlNode.attrs.push_back(attr);



    RDF_EmptyPropertyElement(&xmpParent, xmlNode, false);

    EXPECT_FALSE(xmpParent.children.empty());

    EXPECT_EQ(xmpParent.children[0]->value, "test_value");

}



TEST_F(RDF_EmptyPropertyElementTest_2137, NormalOperationWithRDFResource_2137) {

    XML_NodePtr attr = new XML_Node(nullptr, "rdf:resource", 0);

    attr->value = "http://example.com/resource";

    xmlNode.attrs.push_back(attr);



    RDF_EmptyPropertyElement(&xmpParent, xmlNode, false);

    EXPECT_FALSE(xmpParent.children.empty());

    EXPECT_EQ(xmpParent.children[0]->value, "http://example.com/resource");

    EXPECT_TRUE((xmpParent.children[0]->options & kXMP_PropValueIsURI) != 0);

}



TEST_F(RDF_EmptyPropertyElementTest_2137, NormalOperationWithRDFNodeID_2137) {

    XML_NodePtr attr = new XML_Node(nullptr, "rdf:nodeID", 0);

    attr->value = "node_id";

    xmlNode.attrs.push_back(attr);



    RDF_EmptyPropertyElement(&xmpParent, xmlNode, false);

    EXPECT_TRUE(xmpParent.children.empty());

}



TEST_F(RDF_EmptyPropertyElementTest_2137, NormalOperationWithMultipleAttributes_2137) {

    XML_NodePtr attr1 = new XML_Node(nullptr, "rdf:value", 0);

    attr1->value = "test_value";

    xmlNode.attrs.push_back(attr1);



    XML_NodePtr attr2 = new XML_Node(nullptr, "xml:lang", 0);

    attr2->value = "en";

    xmlNode.attrs.push_back(attr2);



    RDF_EmptyPropertyElement(&xmpParent, xmlNode, false);

    EXPECT_FALSE(xmpParent.children.empty());

    EXPECT_EQ(xmpParent.children[0]->value, "test_value");

}



TEST_F(RDF_EmptyPropertyElementTest_2137, ErrorNestedContentWithRDFResource_2137) {

    XML_NodePtr attr = new XML_Node(nullptr, "rdf:resource", 0);

    attr->value = "http://example.com/resource";

    xmlNode.attrs.push_back(attr);



    XML_NodePtr content = new XML_Node(nullptr, "child_node", 0);

    xmlNode.content.push_back(content);



    EXPECT_THROW(RDF_EmptyPropertyElement(&xmpParent, xmlNode, false), XMP_Error);

}



TEST_F(RDF_EmptyPropertyElementTest_2137, ErrorRDFValueAndRDFResource_2137) {

    XML_NodePtr attr1 = new XML_Node(nullptr, "rdf:value", 0);

    attr1->value = "test_value";

    xmlNode.attrs.push_back(attr1);



    XML_NodePtr attr2 = new XML_Node(nullptr, "rdf:resource", 0);

    attr2->value = "http://example.com/resource";

    xmlNode.attrs.push_back(attr2);



    EXPECT_THROW(RDF_EmptyPropertyElement(&xmpParent, xmlNode, false), XMP_Error);

}



TEST_F(RDF_EmptyPropertyElementTest_2137, ErrorRDFResourceAndRDFNodeID_2137) {

    XML_NodePtr attr1 = new XML_Node(nullptr, "rdf:resource", 0);

    attr1->value = "http://example.com/resource";

    xmlNode.attrs.push_back(attr1);



    XML_NodePtr attr2 = new XML_Node(nullptr, "rdf:nodeID", 0);

    attr2->value = "node_id";

    xmlNode.attrs.push_back(attr2);



    EXPECT_THROW(RDF_EmptyPropertyElement(&xmpParent, xmlNode, false), XMP_Error);

}



TEST_F(RDF_EmptyPropertyElementTest_2137, ErrorUnrecognizedAttribute_2137) {

    XML_NodePtr attr = new XML_Node(nullptr, "unknown_attr", 0);

    attr->value = "test_value";

    xmlNode.attrs.push_back(attr);



    EXPECT_THROW(RDF_EmptyPropertyElement(&xmpParent, xmlNode, false), XMP_Error);

}
