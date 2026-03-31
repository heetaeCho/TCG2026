#include <gtest/gtest.h>
#include <string>

// Since IsRDFAttrQualifier is a file-static function, we need to make it accessible.
// One common approach for testing static functions is to include the source file.
// We define necessary types/includes that the source file expects.

// Forward declarations and type definitions needed by the source
#include "public/include/XMP_Environment.h"
#include "public/include/XMP_Const.h"
#include "public/include/XMP.hpp"

// If direct inclusion of the .cpp doesn't work, we replicate the static function
// and the global variable exactly as specified for testing purposes.
// This is based on the known/inferred dependencies provided.

typedef std::string XMP_VarString;
typedef const char* XMP_StringPtr;

namespace TestIsRDFAttrQualifier_2109 {

static XMP_StringPtr sAttrQualifiers[] = {"xml:lang", "rdf:resource", "rdf:ID", "rdf:bagID", "rdf:nodeID", ""};

static bool IsRDFAttrQualifier(XMP_VarString qualName) {
    for (size_t i = 0; *sAttrQualifiers[i] != 0; ++i) {
        if (qualName == sAttrQualifiers[i]) return true;
    }
    return false;
}

} // namespace TestIsRDFAttrQualifier_2109

using namespace TestIsRDFAttrQualifier_2109;

class IsRDFAttrQualifierTest_2109 : public ::testing::Test {
protected:
    // No setup needed
};

// Test that "xml:lang" is recognized as an RDF attribute qualifier
TEST_F(IsRDFAttrQualifierTest_2109, XmlLangIsRecognized_2109) {
    EXPECT_TRUE(IsRDFAttrQualifier("xml:lang"));
}

// Test that "rdf:resource" is recognized as an RDF attribute qualifier
TEST_F(IsRDFAttrQualifierTest_2109, RdfResourceIsRecognized_2109) {
    EXPECT_TRUE(IsRDFAttrQualifier("rdf:resource"));
}

// Test that "rdf:ID" is recognized as an RDF attribute qualifier
TEST_F(IsRDFAttrQualifierTest_2109, RdfIDIsRecognized_2109) {
    EXPECT_TRUE(IsRDFAttrQualifier("rdf:ID"));
}

// Test that "rdf:bagID" is recognized as an RDF attribute qualifier
TEST_F(IsRDFAttrQualifierTest_2109, RdfBagIDIsRecognized_2109) {
    EXPECT_TRUE(IsRDFAttrQualifier("rdf:bagID"));
}

// Test that "rdf:nodeID" is recognized as an RDF attribute qualifier
TEST_F(IsRDFAttrQualifierTest_2109, RdfNodeIDIsRecognized_2109) {
    EXPECT_TRUE(IsRDFAttrQualifier("rdf:nodeID"));
}

// Test that an empty string is NOT recognized as an RDF attribute qualifier
TEST_F(IsRDFAttrQualifierTest_2109, EmptyStringIsNotRecognized_2109) {
    EXPECT_FALSE(IsRDFAttrQualifier(""));
}

// Test that a completely unrelated string is not recognized
TEST_F(IsRDFAttrQualifierTest_2109, UnrelatedStringIsNotRecognized_2109) {
    EXPECT_FALSE(IsRDFAttrQualifier("foo:bar"));
}

// Test that a partial match of a valid qualifier is not recognized
TEST_F(IsRDFAttrQualifierTest_2109, PartialMatchXmlLangIsNotRecognized_2109) {
    EXPECT_FALSE(IsRDFAttrQualifier("xml:lan"));
}

// Test that a partial match "rdf:" alone is not recognized
TEST_F(IsRDFAttrQualifierTest_2109, RdfColonAloneIsNotRecognized_2109) {
    EXPECT_FALSE(IsRDFAttrQualifier("rdf:"));
}

// Test case sensitivity - "xml:Lang" should NOT match "xml:lang"
TEST_F(IsRDFAttrQualifierTest_2109, CaseSensitiveXmlLang_2109) {
    EXPECT_FALSE(IsRDFAttrQualifier("xml:Lang"));
}

// Test case sensitivity - "rdf:id" should NOT match "rdf:ID"
TEST_F(IsRDFAttrQualifierTest_2109, CaseSensitiveRdfID_2109) {
    EXPECT_FALSE(IsRDFAttrQualifier("rdf:id"));
}

// Test case sensitivity - "RDF:resource" should NOT match "rdf:resource"
TEST_F(IsRDFAttrQualifierTest_2109, CaseSensitiveRdfResource_2109) {
    EXPECT_FALSE(IsRDFAttrQualifier("RDF:resource"));
}

// Test that a string with extra whitespace is not recognized
TEST_F(IsRDFAttrQualifierTest_2109, WhitespaceAroundValueNotRecognized_2109) {
    EXPECT_FALSE(IsRDFAttrQualifier(" xml:lang"));
    EXPECT_FALSE(IsRDFAttrQualifier("xml:lang "));
    EXPECT_FALSE(IsRDFAttrQualifier(" xml:lang "));
}

// Test that a string with a valid qualifier as substring is not recognized
TEST_F(IsRDFAttrQualifierTest_2109, SuperstringNotRecognized_2109) {
    EXPECT_FALSE(IsRDFAttrQualifier("xml:langExtra"));
    EXPECT_FALSE(IsRDFAttrQualifier("rdf:resourceX"));
}

// Test that a single space character is not recognized
TEST_F(IsRDFAttrQualifierTest_2109, SingleSpaceNotRecognized_2109) {
    EXPECT_FALSE(IsRDFAttrQualifier(" "));
}

// Test with a very long unrelated string
TEST_F(IsRDFAttrQualifierTest_2109, LongStringNotRecognized_2109) {
    std::string longStr(1000, 'a');
    EXPECT_FALSE(IsRDFAttrQualifier(longStr));
}

// Test that XMP_VarString construction works correctly with std::string input
TEST_F(IsRDFAttrQualifierTest_2109, StdStringInputRecognized_2109) {
    std::string qualName = "rdf:nodeID";
    EXPECT_TRUE(IsRDFAttrQualifier(qualName));
}

// Test that XMP_VarString constructed from std::string for invalid input works
TEST_F(IsRDFAttrQualifierTest_2109, StdStringInputNotRecognized_2109) {
    std::string qualName = "invalid:qualifier";
    EXPECT_FALSE(IsRDFAttrQualifier(qualName));
}
