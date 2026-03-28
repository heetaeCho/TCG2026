#include <gtest/gtest.h>
#include <string>
#include <map>
#include <vector>
#include <cstring>

// Include necessary XMP headers
#include "XMP_Const.h"
#include "XMPCore_Impl.hpp"

// We need access to the global maps and the function under test
extern XMP_StringMap * sNamespaceURIToPrefixMap;
extern XMP_StringMap * sNamespacePrefixToURIMap;

// Forward declaration of the function under test
extern void VerifyXPathRoot(XMP_StringPtr schemaURI, XMP_StringPtr propName, XMP_ExpandedXPath * expandedXPath);

class VerifyXPathRootTest_1884 : public ::testing::Test {
protected:
    void SetUp() override {
        // Save original map pointers if they exist, create new ones for testing
        origURIToPrefix = sNamespaceURIToPrefixMap;
        origPrefixToURI = sNamespacePrefixToURIMap;
        
        // Create test maps if they don't exist
        if (sNamespaceURIToPrefixMap == nullptr) {
            testURIToPrefix = new XMP_StringMap();
            sNamespaceURIToPrefixMap = testURIToPrefix;
            createdURIMap = true;
        } else {
            testURIToPrefix = sNamespaceURIToPrefixMap;
            createdURIMap = false;
        }
        
        if (sNamespacePrefixToURIMap == nullptr) {
            testPrefixToURI = new XMP_StringMap();
            sNamespacePrefixToURIMap = testPrefixToURI;
            createdPrefixMap = true;
        } else {
            testPrefixToURI = sNamespacePrefixToURIMap;
            createdPrefixMap = false;
        }
        
        // Register a test namespace
        (*sNamespaceURIToPrefixMap)["http://ns.test.com/"] = "test:";
        (*sNamespacePrefixToURIMap)["test:"] = "http://ns.test.com/";
        
        // Register another namespace for mismatch tests
        (*sNamespaceURIToPrefixMap)["http://ns.other.com/"] = "other:";
        (*sNamespacePrefixToURIMap)["other:"] = "http://ns.other.com/";
    }
    
    void TearDown() override {
        // Clean up test entries
        sNamespaceURIToPrefixMap->erase("http://ns.test.com/");
        sNamespacePrefixToURIMap->erase("test:");
        sNamespaceURIToPrefixMap->erase("http://ns.other.com/");
        sNamespacePrefixToURIMap->erase("other:");
        
        if (createdURIMap) {
            delete testURIToPrefix;
            sNamespaceURIToPrefixMap = origURIToPrefix;
        }
        if (createdPrefixMap) {
            delete testPrefixToURI;
            sNamespacePrefixToURIMap = origPrefixToURI;
        }
    }
    
    XMP_StringMap * origURIToPrefix;
    XMP_StringMap * origPrefixToURI;
    XMP_StringMap * testURIToPrefix;
    XMP_StringMap * testPrefixToURI;
    bool createdURIMap;
    bool createdPrefixMap;
};

// Test: Empty schema URI should throw BadSchema
TEST_F(VerifyXPathRootTest_1884, EmptySchemaURI_ThrowsBadSchema_1884) {
    XMP_ExpandedXPath expandedXPath;
    EXPECT_THROW(
        VerifyXPathRoot("", "propName", &expandedXPath),
        XMP_Error
    );
}

// Test: Property name starting with '?' should throw BadXPath
TEST_F(VerifyXPathRootTest_1884, PropNameStartsWithQuestionMark_ThrowsBadXPath_1884) {
    XMP_ExpandedXPath expandedXPath;
    EXPECT_THROW(
        VerifyXPathRoot("http://ns.test.com/", "?qualifier", &expandedXPath),
        XMP_Error
    );
}

// Test: Property name starting with '@' should throw BadXPath
TEST_F(VerifyXPathRootTest_1884, PropNameStartsWithAtSign_ThrowsBadXPath_1884) {
    XMP_ExpandedXPath expandedXPath;
    EXPECT_THROW(
        VerifyXPathRoot("http://ns.test.com/", "@qualifier", &expandedXPath),
        XMP_Error
    );
}

// Test: Property name containing '/' should throw BadXPath
TEST_F(VerifyXPathRootTest_1884, PropNameContainsSlash_ThrowsBadXPath_1884) {
    XMP_ExpandedXPath expandedXPath;
    EXPECT_THROW(
        VerifyXPathRoot("http://ns.test.com/", "prop/child", &expandedXPath),
        XMP_Error
    );
}

// Test: Property name containing '[' should throw BadXPath
TEST_F(VerifyXPathRootTest_1884, PropNameContainsBracket_ThrowsBadXPath_1884) {
    XMP_ExpandedXPath expandedXPath;
    EXPECT_THROW(
        VerifyXPathRoot("http://ns.test.com/", "prop[1]", &expandedXPath),
        XMP_Error
    );
}

// Test: Unregistered schema namespace URI should throw BadSchema
TEST_F(VerifyXPathRootTest_1884, UnregisteredSchemaURI_ThrowsBadSchema_1884) {
    XMP_ExpandedXPath expandedXPath;
    EXPECT_THROW(
        VerifyXPathRoot("http://ns.unregistered.com/", "propName", &expandedXPath),
        XMP_Error
    );
}

// Test: Simple property name without colon (no prefix) should succeed
TEST_F(VerifyXPathRootTest_1884, SimpleNameNoColon_Succeeds_1884) {
    XMP_ExpandedXPath expandedXPath;
    EXPECT_NO_THROW(
        VerifyXPathRoot("http://ns.test.com/", "PropertyName", &expandedXPath)
    );
    
    // Should have 2 entries: schema step and root prop step
    ASSERT_EQ(expandedXPath.size(), 2u);
    
    // First entry should be the schema URI
    EXPECT_EQ(expandedXPath[kSchemaStep].step, std::string("http://ns.test.com/"));
    EXPECT_EQ(expandedXPath[kSchemaStep].options, kXMP_SchemaNode);
    
    // Second entry should be prefix + propName
    std::string expectedStep = std::string("test:") + "PropertyName";
    EXPECT_EQ(expandedXPath[kRootPropStep].step, expectedStep);
}

// Test: Prefixed property name with correct prefix should succeed
TEST_F(VerifyXPathRootTest_1884, PrefixedNameCorrectPrefix_Succeeds_1884) {
    XMP_ExpandedXPath expandedXPath;
    EXPECT_NO_THROW(
        VerifyXPathRoot("http://ns.test.com/", "test:PropertyName", &expandedXPath)
    );
    
    ASSERT_EQ(expandedXPath.size(), 2u);
    
    EXPECT_EQ(expandedXPath[kSchemaStep].step, std::string("http://ns.test.com/"));
    EXPECT_EQ(expandedXPath[kSchemaStep].options, kXMP_SchemaNode);
    
    EXPECT_EQ(expandedXPath[kRootPropStep].step, std::string("test:PropertyName"));
}

// Test: Prefixed property name with unknown prefix should throw BadSchema
TEST_F(VerifyXPathRootTest_1884, PrefixedNameUnknownPrefix_ThrowsBadSchema_1884) {
    XMP_ExpandedXPath expandedXPath;
    EXPECT_THROW(
        VerifyXPathRoot("http://ns.test.com/", "unknown:PropertyName", &expandedXPath),
        XMP_Error
    );
}

// Test: Prefixed property name with mismatched prefix should throw BadSchema
TEST_F(VerifyXPathRootTest_1884, PrefixedNameMismatchedPrefix_ThrowsBadSchema_1884) {
    XMP_ExpandedXPath expandedXPath;
    // "other:" prefix maps to "http://ns.other.com/" but we pass "http://ns.test.com/"
    EXPECT_THROW(
        VerifyXPathRoot("http://ns.test.com/", "other:PropertyName", &expandedXPath),
        XMP_Error
    );
}

// Test: Verify expanded path has correct options for root prop step (no colon case)
TEST_F(VerifyXPathRootTest_1884, SimpleNameOptions_AreZero_1884) {
    XMP_ExpandedXPath expandedXPath;
    VerifyXPathRoot("http://ns.test.com/", "SimpleProp", &expandedXPath);
    
    ASSERT_GE(expandedXPath.size(), 2u);
    EXPECT_EQ(expandedXPath[kRootPropStep].options, 0u);
}

// Test: Verify expanded path has correct options for root prop step (colon case)
TEST_F(VerifyXPathRootTest_1884, PrefixedNameOptions_AreZero_1884) {
    XMP_ExpandedXPath expandedXPath;
    VerifyXPathRoot("http://ns.test.com/", "test:PrefixedProp", &expandedXPath);
    
    ASSERT_GE(expandedXPath.size(), 2u);
    EXPECT_EQ(expandedXPath[kRootPropStep].options, 0u);
}

// Test: Property name with slash at the end should throw
TEST_F(VerifyXPathRootTest_1884, PropNameEndsWithSlash_ThrowsBadXPath_1884) {
    XMP_ExpandedXPath expandedXPath;
    EXPECT_THROW(
        VerifyXPathRoot("http://ns.test.com/", "prop/", &expandedXPath),
        XMP_Error
    );
}

// Test: Property name with bracket at the end should throw
TEST_F(VerifyXPathRootTest_1884, PropNameEndsWithBracket_ThrowsBadXPath_1884) {
    XMP_ExpandedXPath expandedXPath;
    EXPECT_THROW(
        VerifyXPathRoot("http://ns.test.com/", "prop[", &expandedXPath),
        XMP_Error
    );
}

// Test: Single character property name should work
TEST_F(VerifyXPathRootTest_1884, SingleCharPropName_Succeeds_1884) {
    XMP_ExpandedXPath expandedXPath;
    EXPECT_NO_THROW(
        VerifyXPathRoot("http://ns.test.com/", "x", &expandedXPath)
    );
    ASSERT_EQ(expandedXPath.size(), 2u);
    EXPECT_EQ(expandedXPath[kRootPropStep].step, std::string("test:x"));
}

// Test: Schema URI step is always first in the path
TEST_F(VerifyXPathRootTest_1884, SchemaStepIsFirst_1884) {
    XMP_ExpandedXPath expandedXPath;
    VerifyXPathRoot("http://ns.test.com/", "MyProp", &expandedXPath);
    
    ASSERT_GE(expandedXPath.size(), 1u);
    EXPECT_EQ(expandedXPath[0].step, std::string("http://ns.test.com/"));
    EXPECT_EQ(expandedXPath[0].options, kXMP_SchemaNode);
}

// Test: The expandedXPath should be empty initially (precondition)
// and after successful call should have exactly 2 elements
TEST_F(VerifyXPathRootTest_1884, ExpandedPathHasTwoElements_1884) {
    XMP_ExpandedXPath expandedXPath;
    VerifyXPathRoot("http://ns.test.com/", "test:ValidProp", &expandedXPath);
    EXPECT_EQ(expandedXPath.size(), 2u);
}

// Test: Property name "?" alone should throw
TEST_F(VerifyXPathRootTest_1884, QuestionMarkOnly_ThrowsBadXPath_1884) {
    XMP_ExpandedXPath expandedXPath;
    EXPECT_THROW(
        VerifyXPathRoot("http://ns.test.com/", "?", &expandedXPath),
        XMP_Error
    );
}

// Test: Property name "@" alone should throw
TEST_F(VerifyXPathRootTest_1884, AtSignOnly_ThrowsBadXPath_1884) {
    XMP_ExpandedXPath expandedXPath;
    EXPECT_THROW(
        VerifyXPathRoot("http://ns.test.com/", "@", &expandedXPath),
        XMP_Error
    );
}
