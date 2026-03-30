// =================================================================================================
// TEST_ID: 2109
// Unit tests for static bool IsRDFAttrQualifier ( XMP_VarString qualName )
// File: xmpsdk/src/XMPMeta-Serialize.cpp
// =================================================================================================

#include <gtest/gtest.h>

#include <string>
#include <vector>

// NOTE:
// IsRDFAttrQualifier is a file-scope static function in XMPMeta-Serialize.cpp.
// These tests include the .cpp directly so the function is available in this test TU.
// This is a common approach for testing internal helpers without changing production code.
#include "xmpsdk/src/XMPMeta-Serialize.cpp"

namespace {

class IsRDFAttrQualifierTest_2109 : public ::testing::Test {};

TEST_F(IsRDFAttrQualifierTest_2109, ReturnsTrueForKnownQualifiers_2109) {
  const std::vector<std::string> qualifiers = {
      "xml:lang", "rdf:resource", "rdf:ID", "rdf:bagID", "rdf:nodeID",
  };

  for (const auto& q : qualifiers) {
    EXPECT_TRUE(IsRDFAttrQualifier(q)) << "Expected true for qualifier: " << q;
  }
}

TEST_F(IsRDFAttrQualifierTest_2109, ReturnsFalseForEmptyString_2109) {
  EXPECT_FALSE(IsRDFAttrQualifier(std::string()));
  EXPECT_FALSE(IsRDFAttrQualifier(""));
}

TEST_F(IsRDFAttrQualifierTest_2109, ReturnsFalseForUnknownQualifier_2109) {
  EXPECT_FALSE(IsRDFAttrQualifier("rdf:about"));
  EXPECT_FALSE(IsRDFAttrQualifier("xml:space"));
  EXPECT_FALSE(IsRDFAttrQualifier("rdf:li"));
  EXPECT_FALSE(IsRDFAttrQualifier("xmp:Label"));
}

TEST_F(IsRDFAttrQualifierTest_2109, IsCaseSensitive_2109) {
  // Known: "rdf:ID" is in the qualifier list; different casing should not match.
  EXPECT_TRUE(IsRDFAttrQualifier("rdf:ID"));
  EXPECT_FALSE(IsRDFAttrQualifier("rdf:id"));
  EXPECT_FALSE(IsRDFAttrQualifier("RDF:ID"));

  EXPECT_TRUE(IsRDFAttrQualifier("xml:lang"));
  EXPECT_FALSE(IsRDFAttrQualifier("xml:Lang"));
  EXPECT_FALSE(IsRDFAttrQualifier("XML:LANG"));
}

TEST_F(IsRDFAttrQualifierTest_2109, ReturnsFalseForNearMatches_2109) {
  EXPECT_FALSE(IsRDFAttrQualifier("xml:lang "));
  EXPECT_FALSE(IsRDFAttrQualifier(" xml:lang"));
  EXPECT_FALSE(IsRDFAttrQualifier("xml:lang\t"));
  EXPECT_FALSE(IsRDFAttrQualifier("rdf:resource#"));
  EXPECT_FALSE(IsRDFAttrQualifier("rdf:nodeID:extra"));
  EXPECT_FALSE(IsRDFAttrQualifier("rdf:bagID2"));
}

TEST_F(IsRDFAttrQualifierTest_2109, DoesNotModifyInputString_2109) {
  std::string q = "xml:lang";
  const std::string original = q;
  (void)IsRDFAttrQualifier(q);
  EXPECT_EQ(q, original);
}

TEST_F(IsRDFAttrQualifierTest_2109, EmbeddedNullDoesNotMatchPlainQualifier_2109) {
  // Boundary-ish: a std::string containing an embedded NUL should not equal the plain qualifier.
  std::string withNull("xml:lang", 8);
  withNull.push_back('\0');
  withNull += "trailing";

  EXPECT_TRUE(IsRDFAttrQualifier("xml:lang"));
  EXPECT_FALSE(IsRDFAttrQualifier(withNull));
}

TEST_F(IsRDFAttrQualifierTest_2109, HandlesLongStrings_2109) {
  std::string longStr(10 * 1024, 'a');
  EXPECT_FALSE(IsRDFAttrQualifier(longStr));

  // Make it long but still not an exact match.
  longStr = std::string(10 * 1024, 'b') + "xml:lang";
  EXPECT_FALSE(IsRDFAttrQualifier(longStr));
}

}  // namespace