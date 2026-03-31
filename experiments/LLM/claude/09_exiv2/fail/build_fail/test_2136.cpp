#include <gtest/gtest.h>
#include <stdexcept>

// Include necessary headers
#include "xmpsdk/src/XMPCore_Impl.hpp"
#include "xmpsdk/src/XMLParserAdapter.hpp"
#include "XMP_Const.h"

// The function under test is static in ParseRDF.cpp, so we need to access it.
// We declare it here as it would be accessible via internal linkage or header.
// If it's not directly accessible, we may need to include the source or use a wrapper.
#include "xmpsdk/src/ParseRDF.cpp"

class RDFParseTypeOtherPropertyElementTest_2136 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that the function throws an exception with null parent and default XML node, not top level
TEST_F(RDFParseTypeOtherPropertyElementTest_2136, ThrowsExceptionWithNullParent_2136) {
    XMP_Node parentNode(nullptr, "testParent", 0);
    XML_Node xmlNode(nullptr, "testNode", 0);

    EXPECT_THROW(
        RDF_ParseTypeOtherPropertyElement(&parentNode, xmlNode, false),
        XMP_Error
    );
}

// Test that the function throws an exception when isTopLevel is true
TEST_F(RDFParseTypeOtherPropertyElementTest_2136, ThrowsExceptionWhenTopLevel_2136) {
    XMP_Node parentNode(nullptr, "testParent", 0);
    XML_Node xmlNode(nullptr, "testNode", 0);

    EXPECT_THROW(
        RDF_ParseTypeOtherPropertyElement(&parentNode, xmlNode, true),
        XMP_Error
    );
}

// Test that the function throws an exception when isTopLevel is false
TEST_F(RDFParseTypeOtherPropertyElementTest_2136, ThrowsExceptionWhenNotTopLevel_2136) {
    XMP_Node parentNode(nullptr, "testParent", 0);
    XML_Node xmlNode(nullptr, "testNode", 0);

    EXPECT_THROW(
        RDF_ParseTypeOtherPropertyElement(&parentNode, xmlNode, false),
        XMP_Error
    );
}

// Test that the exception has the correct error code kXMPErr_BadXMP
TEST_F(RDFParseTypeOtherPropertyElementTest_2136, ThrowsWithCorrectErrorCode_2136) {
    XMP_Node parentNode(nullptr, "testParent", 0);
    XML_Node xmlNode(nullptr, "testNode", 0);

    try {
        RDF_ParseTypeOtherPropertyElement(&parentNode, xmlNode, false);
        FAIL() << "Expected XMP_Error to be thrown";
    } catch (const XMP_Error& e) {
        EXPECT_EQ(e.GetID(), kXMPErr_BadXMP);
    } catch (...) {
        FAIL() << "Expected XMP_Error but caught different exception type";
    }
}

// Test that the exception message contains the expected text
TEST_F(RDFParseTypeOtherPropertyElementTest_2136, ThrowsWithCorrectMessage_2136) {
    XMP_Node parentNode(nullptr, "testParent", 0);
    XML_Node xmlNode(nullptr, "testNode", 0);

    try {
        RDF_ParseTypeOtherPropertyElement(&parentNode, xmlNode, false);
        FAIL() << "Expected XMP_Error to be thrown";
    } catch (const XMP_Error& e) {
        std::string errMsg = e.GetErrMsg();
        EXPECT_NE(errMsg.find("ParseTypeOther property element not allowed"), std::string::npos);
    } catch (...) {
        FAIL() << "Expected XMP_Error but caught different exception type";
    }
}

// Test with a more complex parent node to ensure parameters are irrelevant
TEST_F(RDFParseTypeOtherPropertyElementTest_2136, AlwaysThrowsRegardlessOfParentContent_2136) {
    XMP_Node grandparent(nullptr, "grandparent", 0);
    XMP_Node parentNode(&grandparent, "parent", 0x0010);
    XML_Node xmlNode(nullptr, "rdf:Description", 0);
    xmlNode.ns = "http://www.w3.org/1999/02/22-rdf-syntax-ns#";
    xmlNode.value = "some value";

    EXPECT_THROW(
        RDF_ParseTypeOtherPropertyElement(&parentNode, xmlNode, true),
        XMP_Error
    );
}

// Test with nullptr xmpParent - function should still throw (parameters are ignored)
TEST_F(RDFParseTypeOtherPropertyElementTest_2136, ThrowsWithNullXMPParent_2136) {
    XML_Node xmlNode(nullptr, "testNode", 0);

    EXPECT_THROW(
        RDF_ParseTypeOtherPropertyElement(nullptr, xmlNode, false),
        XMP_Error
    );
}

// Test that the function always throws - it's unconditional
TEST_F(RDFParseTypeOtherPropertyElementTest_2136, UnconditionalThrow_2136) {
    XMP_Node parentNode(nullptr, "", 0);
    XML_Node xmlNode(nullptr, "", 0);

    // Test multiple combinations to confirm unconditional throw
    EXPECT_THROW(RDF_ParseTypeOtherPropertyElement(&parentNode, xmlNode, true), XMP_Error);
    EXPECT_THROW(RDF_ParseTypeOtherPropertyElement(&parentNode, xmlNode, false), XMP_Error);
    EXPECT_THROW(RDF_ParseTypeOtherPropertyElement(nullptr, xmlNode, true), XMP_Error);
    EXPECT_THROW(RDF_ParseTypeOtherPropertyElement(nullptr, xmlNode, false), XMP_Error);
}
