#include <gtest/gtest.h>
#include <stdexcept>

// Include necessary headers
#include "XMPCore_Impl.hpp"
#include "XMLParserAdapter.hpp"

// We need access to the function under test. Since it's a static function in ParseRDF.cpp,
// we need to either include it or declare it. Given the constraints, we'll work with what
// we can observe. The function is static, so we may need to test it indirectly or
// re-declare it for testing purposes.

// Since RDF_ParseTypeCollectionPropertyElement is a static function in ParseRDF.cpp,
// it's not directly accessible from outside. However, based on the interface provided,
// we know it always throws an XMP_Throw with kXMPErr_BadXMP.
// 
// For testing purposes, we'll need to either:
// 1. Include the source file (not ideal but necessary for static functions)
// 2. Test through the public API that calls this function
//
// Given the constraints, let's try to include necessary headers and test the behavior.

// XMP_Throw typically throws an XMP_Error or similar exception type
// Let's include what we need

#include "XMP_Const.h"

// Forward declare or include the function - since it's static, we may need to
// test through the RDF parser's public interface, or include the .cpp
// For unit testing a static function, we include the translation unit

// Attempt to make the static function accessible for testing
#define static
#include "ParseRDF.cpp"
#undef static

class RDFParseTypeCollectionPropertyElementTest_2135 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that the function throws an exception (it should always throw)
TEST_F(RDFParseTypeCollectionPropertyElementTest_2135, ThrowsOnNullParent_2135) {
    XML_Node xmlNode(nullptr, "testNode", 0);
    
    EXPECT_THROW(
        RDF_ParseTypeCollectionPropertyElement(nullptr, xmlNode, false),
        XMP_Error
    );
}

// Test that the function throws with isTopLevel = true
TEST_F(RDFParseTypeCollectionPropertyElementTest_2135, ThrowsOnTopLevel_2135) {
    XML_Node xmlNode(nullptr, "testNode", 0);
    
    EXPECT_THROW(
        RDF_ParseTypeCollectionPropertyElement(nullptr, xmlNode, true),
        XMP_Error
    );
}

// Test that the function throws with a valid XMP_Node parent
TEST_F(RDFParseTypeCollectionPropertyElementTest_2135, ThrowsWithValidParent_2135) {
    XMP_Node xmpParent(nullptr, "parent", 0);
    XML_Node xmlNode(nullptr, "testNode", 0);
    
    EXPECT_THROW(
        RDF_ParseTypeCollectionPropertyElement(&xmpParent, xmlNode, false),
        XMP_Error
    );
}

// Test that the function throws with valid parent and isTopLevel true
TEST_F(RDFParseTypeCollectionPropertyElementTest_2135, ThrowsWithValidParentTopLevel_2135) {
    XMP_Node xmpParent(nullptr, "parent", 0);
    XML_Node xmlNode(nullptr, "testNode", 0);
    
    EXPECT_THROW(
        RDF_ParseTypeCollectionPropertyElement(&xmpParent, xmlNode, true),
        XMP_Error
    );
}

// Test that the exception contains the correct error code (kXMPErr_BadXMP = 203)
TEST_F(RDFParseTypeCollectionPropertyElementTest_2135, ThrowsWithBadXMPErrorCode_2135) {
    XMP_Node xmpParent(nullptr, "parent", 0);
    XML_Node xmlNode(nullptr, "testNode", 0);
    
    try {
        RDF_ParseTypeCollectionPropertyElement(&xmpParent, xmlNode, false);
        FAIL() << "Expected exception to be thrown";
    } catch (const XMP_Error& e) {
        EXPECT_EQ(e.GetID(), kXMPErr_BadXMP);
    } catch (...) {
        FAIL() << "Expected XMP_Error exception";
    }
}

// Test that the exception message is as expected
TEST_F(RDFParseTypeCollectionPropertyElementTest_2135, ThrowsWithCorrectMessage_2135) {
    XMP_Node xmpParent(nullptr, "parent", 0);
    XML_Node xmlNode(nullptr, "testNode", 0);
    
    try {
        RDF_ParseTypeCollectionPropertyElement(&xmpParent, xmlNode, false);
        FAIL() << "Expected exception to be thrown";
    } catch (const XMP_Error& e) {
        std::string errMsg(e.GetErrMsg());
        EXPECT_NE(errMsg.find("ParseTypeCollection"), std::string::npos);
        EXPECT_NE(errMsg.find("not allowed"), std::string::npos);
    } catch (...) {
        FAIL() << "Expected XMP_Error exception";
    }
}

// Test with a complex XML node structure - should still throw
TEST_F(RDFParseTypeCollectionPropertyElementTest_2135, ThrowsWithComplexXMLNode_2135) {
    XMP_Node xmpParent(nullptr, "root", 0);
    XML_Node xmlParent(nullptr, "parentXML", 0);
    XML_Node xmlNode(&xmlParent, "childNode", 0);
    xmlNode.ns = "http://example.com/ns";
    xmlNode.value = "someValue";
    
    EXPECT_THROW(
        RDF_ParseTypeCollectionPropertyElement(&xmpParent, xmlNode, false),
        XMP_Error
    );
}

// Test with nested XMP parent node - should still throw regardless
TEST_F(RDFParseTypeCollectionPropertyElementTest_2135, ThrowsWithNestedXMPParent_2135) {
    XMP_Node grandParent(nullptr, "grandparent", 0);
    XMP_Node parent(&grandParent, "parent", 0);
    XML_Node xmlNode(nullptr, "element", 0);
    
    EXPECT_THROW(
        RDF_ParseTypeCollectionPropertyElement(&parent, xmlNode, true),
        XMP_Error
    );
}
