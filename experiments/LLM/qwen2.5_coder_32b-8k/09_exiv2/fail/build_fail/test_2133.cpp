#include <gtest/gtest.h>

#include "XMP_Const.h"

#include "XMLParserAdapter.hpp"



// Mocking XMP_Node for any potential future need, though not used in current tests.

class MockXMP_Node : public XMP_Node {

public:

    using XMP_Node::XMP_Node;

};



// Test fixture for RDF_ParseTypeLiteralPropertyElement

class RDF_ParseTypeLiteralPropertyElementTest_2133 : public ::testing::Test {

protected:

    XMP_Node xmpParent{nullptr, "testNode", 0};

    XML_Node xmlNode{nullptr, "testXMLNode", 1}; // Assuming kind is set to 1 for testing purposes

};



// Test normal operation which should throw an exception

TEST_F(RDF_ParseTypeLiteralPropertyElementTest_2133, ThrowsOnNormalOperation_2133) {

    EXPECT_THROW(RDF_ParseTypeLiteralPropertyElement(&xmpParent, xmlNode, true), XMP_Error);

}



// Test boundary conditions with isTopLevel as false

TEST_F(RDF_ParseTypeLiteralPropertyElementTest_2133, ThrowsWhenIsTopLevelFalse_2133) {

    EXPECT_THROW(RDF_ParseTypeLiteralPropertyElement(&xmpParent, xmlNode, false), XMP_Error);

}



// Test exceptional case with different XML_Node kind (if applicable)

TEST_F(RDF_ParseTypeLiteralPropertyElementTest_2133, ThrowsWithDifferentXMLNodeKind_2133) {

    XML_Node differentKindXmlNode{nullptr, "testXMLNode", 2}; // Assuming kind is set to 2 for testing purposes

    EXPECT_THROW(RDF_ParseTypeLiteralPropertyElement(&xmpParent, differentKindXmlNode, true), XMP_Error);

}



// Test that the correct error code is thrown

TEST_F(RDF_ParseTypeLiteralPropertyElementTest_2133, ThrowsCorrectErrorCode_2133) {

    try {

        RDF_ParseTypeLiteralPropertyElement(&xmpParent, xmlNode, true);

    } catch (const XMP_Error& e) {

        EXPECT_EQ(e.GetID(), kXMPErr_BadXMP);

    }

}



// Test that the correct error message is thrown

TEST_F(RDF_ParseTypeLiteralPropertyElementTest_2133, ThrowsCorrectErrorMessage_2133) {

    try {

        RDF_ParseTypeLiteralPropertyElement(&xmpParent, xmlNode, true);

    } catch (const XMP_Error& e) {

        EXPECT_STREQ(e.GetErrMsg(), "ParseTypeLiteral property element not allowed");

    }

}
