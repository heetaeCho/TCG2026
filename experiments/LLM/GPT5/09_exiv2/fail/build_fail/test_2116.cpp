// =================================================================================================
// TEST_ID: 2116
// Unit tests for GetRDFTermKind (from xmpsdk/src/ParseRDF.cpp)
// =================================================================================================

#include <gtest/gtest.h>

#include <string>

// NOTE:
// GetRDFTermKind is declared "static" in ParseRDF.cpp (internal linkage).
// To test the real implementation without re-implementing it, we include the .cpp
// into this test translation unit.
#include "TestProjects/exiv2/xmpsdk/src/ParseRDF.cpp"

namespace {

static RDFTermKind CallGetRDFTermKind(const char* s) {
  XMP_VarString name(s);
  return GetRDFTermKind(name);
}

}  // namespace

TEST(GetRDFTermKindTest_2116, MapsKnownRdfTerms_2116) {
  EXPECT_EQ(kRDFTerm_li, CallGetRDFTermKind("rdf:li"));
  EXPECT_EQ(kRDFTerm_parseType, CallGetRDFTermKind("rdf:parseType"));
  EXPECT_EQ(kRDFTerm_Description, CallGetRDFTermKind("rdf:Description"));
  EXPECT_EQ(kRDFTerm_about, CallGetRDFTermKind("rdf:about"));
  EXPECT_EQ(kRDFTerm_resource, CallGetRDFTermKind("rdf:resource"));
  EXPECT_EQ(kRDFTerm_RDF, CallGetRDFTermKind("rdf:RDF"));
  EXPECT_EQ(kRDFTerm_ID, CallGetRDFTermKind("rdf:ID"));
  EXPECT_EQ(kRDFTerm_nodeID, CallGetRDFTermKind("rdf:nodeID"));
  EXPECT_EQ(kRDFTerm_datatype, CallGetRDFTermKind("rdf:datatype"));
  EXPECT_EQ(kRDFTerm_aboutEach, CallGetRDFTermKind("rdf:aboutEach"));
  EXPECT_EQ(kRDFTerm_aboutEachPrefix, CallGetRDFTermKind("rdf:aboutEachPrefix"));
  EXPECT_EQ(kRDFTerm_bagID, CallGetRDFTermKind("rdf:bagID"));
}

TEST(GetRDFTermKindTest_2116, ReturnsOtherForNonRdfPrefix_2116) {
  EXPECT_EQ(kRDFTerm_Other, CallGetRDFTermKind("xmp:li"));
  EXPECT_EQ(kRDFTerm_Other, CallGetRDFTermKind("RDF:li"));       // wrong case
  EXPECT_EQ(kRDFTerm_Other, CallGetRDFTermKind(" rdf:li"));      // leading space
  EXPECT_EQ(kRDFTerm_Other, CallGetRDFTermKind("abc:rdf:li"));   // not starting with "rdf:"
  EXPECT_EQ(kRDFTerm_Other, CallGetRDFTermKind("rd:li"));        // similar prefix
}

TEST(GetRDFTermKindTest_2116, ReturnsOtherForShortOrBarePrefix_2116) {
  EXPECT_EQ(kRDFTerm_Other, CallGetRDFTermKind(""));       // empty
  EXPECT_EQ(kRDFTerm_Other, CallGetRDFTermKind("r"));
  EXPECT_EQ(kRDFTerm_Other, CallGetRDFTermKind("rdf"));    // no colon
  EXPECT_EQ(kRDFTerm_Other, CallGetRDFTermKind("rdf:"));   // exactly "rdf:" boundary
}

TEST(GetRDFTermKindTest_2116, ReturnsOtherForUnknownRdfNames_2116) {
  EXPECT_EQ(kRDFTerm_Other, CallGetRDFTermKind("rdf:unknown"));
  EXPECT_EQ(kRDFTerm_Other, CallGetRDFTermKind("rdf:Li"));            // near-miss case
  EXPECT_EQ(kRDFTerm_Other, CallGetRDFTermKind("rdf:description"));   // near-miss case
  EXPECT_EQ(kRDFTerm_Other, CallGetRDFTermKind("rdf:about "));        // trailing space
  EXPECT_EQ(kRDFTerm_Other, CallGetRDFTermKind("rdf:li/extra"));      // extra suffix
}

TEST(GetRDFTermKindTest_2116, DoesNotMisclassifyWhenRdfAppearsLater_2116) {
  EXPECT_EQ(kRDFTerm_Other, CallGetRDFTermKind("x:rdf:li"));
  EXPECT_EQ(kRDFTerm_Other, CallGetRDFTermKind("http://example.com/rdf:li"));
  EXPECT_EQ(kRDFTerm_Other, CallGetRDFTermKind("something rdf:li"));
}