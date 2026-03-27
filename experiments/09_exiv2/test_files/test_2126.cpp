#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "XMPCore_Impl.hpp"

#include "XMLParserAdapter.hpp"



using namespace ::testing;



// Mock class for XMP_Node to verify interactions if necessary

class MockXMP_Node : public XMP_Node {

public:

    MockXMP_Node(XMP_Node * _parent, const XMP_VarString & _name, const XMP_VarString & _value, XMP_OptionBits _options)

        : XMP_Node(_parent, _name, _value, _options) {}



    MOCK_METHOD0(RemoveChildren, void());

    MOCK_METHOD0(RemoveQualifiers, void());

    MOCK_METHOD0(ClearNode, void());

};



// Mock class for XML_Node to verify interactions if necessary

class MockXML_Node : public XML_Node {

public:

    using XML_Node::XML_Node;

    MOCK_CONST_METHOD0(IsWhitespaceNode, bool());

};



TEST(RDF_NodeElementListTest_2126, NormalOperation_NoWhitespaceNodes_2126) {

    XMP_Node xmpParent(nullptr, "parent", "", 0);

    MockXML_Node xmlParent(nullptr, "xmlParent", 0);

    XML_Node child1(nullptr, "child1", 0);

    XML_Node child2(nullptr, "child2", 0);

    xmlParent.content.push_back(&child1);

    xmlParent.content.push_back(&child2);



    RDF_NodeElementList(&xmpParent, xmlParent, true);

}



TEST(RDF_NodeElementListTest_2126, NormalOperation_WithWhitespaceNodes_2126) {

    XMP_Node xmpParent(nullptr, "parent", "", 0);

    MockXML_Node xmlParent(nullptr, "xmlParent", 0);

    MockXML_Node whitespaceNode(nullptr, "whitespace", 0);

    XML_Node child1(nullptr, "child1", 0);

    ON_CALL(whitespaceNode, IsWhitespaceNode()).WillByDefault(Return(true));

    xmlParent.content.push_back(&whitespaceNode);

    xmlParent.content.push_back(&child1);



    RDF_NodeElementList(&xmpParent, xmlParent, true);

}



TEST(RDF_NodeElementListTest_2126, BoundaryCondition_EmptyContent_2126) {

    XMP_Node xmpParent(nullptr, "parent", "", 0);

    MockXML_Node xmlParent(nullptr, "xmlParent", 0);



    RDF_NodeElementList(&xmpParent, xmlParent, true);

}



TEST(RDF_NodeElementListTest_2126, BoundaryCondition_SingleWhitespaceNode_2126) {

    XMP_Node xmpParent(nullptr, "parent", "", 0);

    MockXML_Node xmlParent(nullptr, "xmlParent", 0);

    MockXML_Node whitespaceNode(nullptr, "whitespace", 0);

    ON_CALL(whitespaceNode, IsWhitespaceNode()).WillByDefault(Return(true));

    xmlParent.content.push_back(&whitespaceNode);



    RDF_NodeElementList(&xmpParent, xmlParent, true);

}



TEST(RDF_NodeElementListTest_2126, Exceptional_TopLevelFalseAssertion_2126) {

    XMP_Node xmpParent(nullptr, "parent", "", 0);

    MockXML_Node xmlParent(nullptr, "xmlParent", 0);



    EXPECT_DEATH({ RDF_NodeElementList(&xmpParent, xmlParent, false); }, "XMP_Assert");

}
