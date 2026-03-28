#include <gtest/gtest.h>
#include <string>
#include <stdexcept>

// Include necessary headers
#include "XMPCore_Impl.hpp"
#include "XMLParserAdapter.hpp"

// XMP_Throw typically throws an XMP_Error or similar exception
// We need to include the appropriate header for the exception type
#include "XMP_Const.h"

// Forward declaration - the function under test
// Since it's static in ParseRDF.cpp, we may need to include or declare it
// For testing purposes, we include the source or use a test-accessible declaration
extern void RDF_ParseTypeLiteralPropertyElement(XMP_Node* xmpParent, const XML_Node& xmlNode, bool isTopLevel);

class ParseTypeLiteralPropertyElementTest_2133 : public ::testing::Test {
protected:
    void SetUp() override {
        // Create basic XMP_Node and XML_Node for testing
        xmpParent = new XMP_Node(nullptr, "testParent", 0);
        xmlNode = new XML_Node(nullptr, "testNode", 0);
    }

    void TearDown() override {
        delete xmpParent;
        delete xmlNode;
    }

    XMP_Node* xmpParent;
    XML_Node* xmlNode;
};

// Test that the function always throws an exception
TEST_F(ParseTypeLiteralPropertyElementTest_2133, AlwaysThrowsException_2133) {
    EXPECT_THROW(
        RDF_ParseTypeLiteralPropertyElement(xmpParent, *xmlNode, false),
        XMP_Error
    );
}

// Test that it throws with isTopLevel = true
TEST_F(ParseTypeLiteralPropertyElementTest_2133, ThrowsWhenIsTopLevelTrue_2133) {
    EXPECT_THROW(
        RDF_ParseTypeLiteralPropertyElement(xmpParent, *xmlNode, true),
        XMP_Error
    );
}

// Test that it throws even with null xmpParent
TEST_F(ParseTypeLiteralPropertyElementTest_2133, ThrowsWithNullXmpParent_2133) {
    EXPECT_THROW(
        RDF_ParseTypeLiteralPropertyElement(nullptr, *xmlNode, false),
        XMP_Error
    );
}

// Test that it throws even with null xmpParent and isTopLevel true
TEST_F(ParseTypeLiteralPropertyElementTest_2133, ThrowsWithNullXmpParentAndTopLevel_2133) {
    EXPECT_THROW(
        RDF_ParseTypeLiteralPropertyElement(nullptr, *xmlNode, true),
        XMP_Error
    );
}

// Test that the exception has the correct error code (kXMPErr_BadXMP = 203)
TEST_F(ParseTypeLiteralPropertyElementTest_2133, ThrowsWithBadXMPErrorCode_2133) {
    try {
        RDF_ParseTypeLiteralPropertyElement(xmpParent, *xmlNode, false);
        FAIL() << "Expected XMP_Error to be thrown";
    } catch (const XMP_Error& e) {
        EXPECT_EQ(e.GetID(), kXMPErr_BadXMP);
    } catch (...) {
        FAIL() << "Expected XMP_Error but got a different exception type";
    }
}

// Test that the exception message is correct
TEST_F(ParseTypeLiteralPropertyElementTest_2133, ThrowsWithCorrectMessage_2133) {
    try {
        RDF_ParseTypeLiteralPropertyElement(xmpParent, *xmlNode, false);
        FAIL() << "Expected XMP_Error to be thrown";
    } catch (const XMP_Error& e) {
        std::string errMsg(e.GetErrMsg());
        EXPECT_NE(errMsg.find("ParseTypeLiteral property element not allowed"), std::string::npos);
    } catch (...) {
        FAIL() << "Expected XMP_Error but got a different exception type";
    }
}

// Test with a more complex XML_Node structure
TEST_F(ParseTypeLiteralPropertyElementTest_2133, ThrowsWithComplexXmlNode_2133) {
    XML_Node complexNode(nullptr, "rdf:Description", 0);
    complexNode.ns = "http://www.w3.org/1999/02/22-rdf-syntax-ns#";
    complexNode.value = "some value";

    EXPECT_THROW(
        RDF_ParseTypeLiteralPropertyElement(xmpParent, complexNode, false),
        XMP_Error
    );
}

// Test with a nested XMP_Node parent
TEST_F(ParseTypeLiteralPropertyElementTest_2133, ThrowsWithNestedXmpParent_2133) {
    XMP_Node grandParent(nullptr, "grandParent", 0);
    XMP_Node parent(&grandParent, "parent", 0);

    EXPECT_THROW(
        RDF_ParseTypeLiteralPropertyElement(&parent, *xmlNode, true),
        XMP_Error
    );
}
