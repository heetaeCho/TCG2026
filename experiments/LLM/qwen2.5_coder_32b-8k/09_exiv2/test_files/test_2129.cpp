#include <gtest/gtest.h>

#include "XMP_Const.h"

#include "XMLParserAdapter.hpp"

#include "XMPCore_Impl.hpp"



class ParseRDFFixture : public ::testing::Test {

protected:

    XMP_Node xmpParent;

    XML_Node xmlParent;



    ParseRDFFixture()

        : xmpParent(nullptr, "xmpRoot", 0),

          xmlParent(nullptr, "xmlRoot", kElemNode) {}



    virtual void SetUp() override {

        // Clear any initial state

        xmpParent.RemoveChildren();

        xmlParent.content.clear();

    }

};



TEST_F(ParseRDFFixture, NoChildNodes_2129) {

    RDF_PropertyElementList(&xmpParent, xmlParent, true);

    // Expect no changes since there are no child nodes

}



TEST_F(ParseRDFFixture, SingleWhitespaceNode_2129) {

    XML_Node whitespaceNode(nullptr, " ", kRootNode);

    xmlParent.content.push_back(&whitespaceNode);

    RDF_PropertyElementList(&xmpParent, xmlParent, true);

    // Expect no changes since the child node is a whitespace

}



TEST_F(ParseRDFFixture, SingleValidPropertyElement_2129) {

    XML_Node propertyNode(nullptr, "property", kElemNode);

    xmlParent.content.push_back(&propertyNode);

    RDF_PropertyElementList(&xmpParent, xmlParent, true);

    // Expect xmpParent to have one child now

    EXPECT_EQ(xmpParent.children.size(), 1);

}



TEST_F(ParseRDFFixture, MultipleValidPropertyElements_2129) {

    XML_Node propertyNode1(nullptr, "property1", kElemNode);

    XML_Node propertyNode2(nullptr, "property2", kElemNode);

    xmlParent.content.push_back(&propertyNode1);

    xmlParent.content.push_back(&propertyNode2);

    RDF_PropertyElementList(&xmpParent, xmlParent, true);

    // Expect xmpParent to have two children now

    EXPECT_EQ(xmpParent.children.size(), 2);

}



TEST_F(ParseRDFFixture, MixedWhitespaceAndValidNodes_2129) {

    XML_Node whitespaceNode(nullptr, " ", kRootNode);

    XML_Node propertyNode1(nullptr, "property1", kElemNode);

    XML_Node propertyNode2(nullptr, "property2", kElemNode);

    xmlParent.content.push_back(&whitespaceNode);

    xmlParent.content.push_back(&propertyNode1);

    xmlParent.content.push_back(&whitespaceNode);

    xmlParent.content.push_back(&propertyNode2);

    RDF_PropertyElementList(&xmpParent, xmlParent, true);

    // Expect xmpParent to have two children now

    EXPECT_EQ(xmpParent.children.size(), 2);

}



TEST_F(ParseRDFFixture, NonElementChildNodes_2129) {

    XML_Node nonElementNode(nullptr, "nonElement", kAttrNode); // Assuming this is not a valid property element node

    xmlParent.content.push_back(&nonElementNode);

    EXPECT_THROW(RDF_PropertyElementList(&xmpParent, xmlParent, true), XMP_Error);

}



TEST_F(ParseRDFFixture, MixedValidAndInvalidNodes_2129) {

    XML_Node propertyNode1(nullptr, "property1", kElemNode);

    XML_Node nonElementNode(nullptr, "nonElement", kAttrNode); // Assuming this is not a valid property element node

    xmlParent.content.push_back(&propertyNode1);

    xmlParent.content.push_back(&nonElementNode);

    EXPECT_THROW(RDF_PropertyElementList(&xmpParent, xmlParent, true), XMP_Error);

}
