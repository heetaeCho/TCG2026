// ============================================================================
// Test file for ExpatAdapter.cpp (SetQualName)
// TEST_ID: 2091
// ============================================================================

#include <gtest/gtest.h>

#include <string>

// Pull in the real SDK headers/types.
#include "XMLParserAdapter.hpp"
#include "XMPMeta.hpp"

// Include the .cpp to get access to the file-scope static SetQualName.
// (This does NOT re-implement anything; it compiles the real production code
// into this test translation unit.)
#include "ExpatAdapter.cpp"

// Some XMP Toolkit builds expose XMP_Error as the thrown type; some may throw
// other exception types. We avoid assuming more than the observable "throws".
static bool StartsWith(const std::string& s, const std::string& prefix) {
  return s.size() >= prefix.size() && s.compare(0, prefix.size(), prefix) == 0;
}

static bool EndsWith(const std::string& s, const std::string& suffix) {
  return s.size() >= suffix.size() &&
         s.compare(s.size() - suffix.size(), suffix.size(), suffix) == 0;
}

class ExpatAdapterSetQualNameTest_2091 : public ::testing::Test {
protected:
  static void SetUpTestSuite() {
    // Initialize XMP global state; required for namespace registry usage.
    XMPMeta::Initialize();

    // Ensure a custom namespace exists for deterministic tests.
    // (If already registered, XMP Toolkit typically tolerates re-registration.)
    XMPMeta::RegisterNamespace("http://ns.example.com/test/", "ex:");

    // Ensure DC is available; SetQualName remaps dc/1.1 -> dc/elements/1.1.
    // Most builds register standard namespaces at init, but registering again
    // should be safe.
    XMPMeta::RegisterNamespace("http://purl.org/dc/elements/1.1/", "dc:");

    // Ensure RDF namespace is known (used by rdf:about / rdf:ID special-casing).
    XMPMeta::RegisterNamespace(kXMP_NS_RDF, "rdf:");
  }

  static void TearDownTestSuite() {
    XMPMeta::Terminate();
  }

  static std::string MakeExpatFullName(const std::string& uri, const std::string& local) {
    std::string full = uri;
    full.push_back(FullNameSeparator);
    full += local;
    return full;
  }
};

TEST_F(ExpatAdapterSetQualNameTest_2091, ParsesNamespacedFullNameAndSetsPrefixLen_2091) {
  XML_Node parent(/*_parent*/ 0, "root", /*_kind*/ 0);
  XML_Node node(&parent, "tmp", /*_kind*/ 0);

  const std::string uri = "http://ns.example.com/test/";
  const std::string local = "prop";
  const std::string fullName = MakeExpatFullName(uri, local);

  SetQualName(fullName.c_str(), &node);

  EXPECT_EQ(node.ns, uri);
  EXPECT_TRUE(EndsWith(node.name, local));
  EXPECT_GT(node.nsPrefixLen, 0u);
  ASSERT_GE(node.name.size(), node.nsPrefixLen);
  EXPECT_EQ(node.name[node.nsPrefixLen - 1], ':');  // nsPrefixLen includes ':'
}

TEST_F(ExpatAdapterSetQualNameTest_2091, RemapsLegacyDublinCoreUri_2091) {
  XML_Node parent(/*_parent*/ 0, "root", /*_kind*/ 0);
  XML_Node node(&parent, "tmp", /*_kind*/ 0);

  const std::string legacyDc = "http://purl.org/dc/1.1/";
  const std::string expectedDc = "http://purl.org/dc/elements/1.1/";
  const std::string local = "title";
  const std::string fullName = MakeExpatFullName(legacyDc, local);

  SetQualName(fullName.c_str(), &node);

  EXPECT_EQ(node.ns, expectedDc);
  EXPECT_TRUE(EndsWith(node.name, local));
  EXPECT_GT(node.nsPrefixLen, 0u);
  ASSERT_GE(node.name.size(), node.nsPrefixLen);
  EXPECT_EQ(node.name[node.nsPrefixLen - 1], ':');
}

TEST_F(ExpatAdapterSetQualNameTest_2091, ThrowsForUnknownNamespaceUri_2091) {
  XML_Node parent(/*_parent*/ 0, "root", /*_kind*/ 0);
  XML_Node node(&parent, "tmp", /*_kind*/ 0);

  const std::string unknownUri = "http://unknown.example.com/ns/";
  const std::string local = "prop";
  const std::string fullName = MakeExpatFullName(unknownUri, local);

  EXPECT_ANY_THROW(SetQualName(fullName.c_str(), &node));
}

TEST_F(ExpatAdapterSetQualNameTest_2091, NonNamespacedNamePreservedWhenParentNotRdfDescription_2091) {
  XML_Node parent(/*_parent*/ 0, "root", /*_kind*/ 0);
  XML_Node node(&parent, "tmp", /*_kind*/ 0);

  SetQualName("about", &node);

  EXPECT_EQ(node.name, "about");
  EXPECT_TRUE(node.ns.empty());
  EXPECT_EQ(node.nsPrefixLen, 0u);
}

TEST_F(ExpatAdapterSetQualNameTest_2091, RdfDescriptionAboutIsQualified_2091) {
  XML_Node parent(/*_parent*/ 0, "rdf:Description", /*_kind*/ 0);
  XML_Node node(&parent, "tmp", /*_kind*/ 0);

  SetQualName("about", &node);

  EXPECT_EQ(node.ns, std::string(kXMP_NS_RDF));
  EXPECT_EQ(node.name, "rdf:about");
  EXPECT_EQ(node.nsPrefixLen, 4u);  // "rdf:"
}

TEST_F(ExpatAdapterSetQualNameTest_2091, RdfDescriptionIdIsQualified_2091) {
  XML_Node parent(/*_parent*/ 0, "rdf:Description", /*_kind*/ 0);
  XML_Node node(&parent, "tmp", /*_kind*/ 0);

  SetQualName("ID", &node);

  EXPECT_EQ(node.ns, std::string(kXMP_NS_RDF));
  EXPECT_EQ(node.name, "rdf:ID");
  EXPECT_EQ(node.nsPrefixLen, 4u);  // "rdf:"
}

TEST_F(ExpatAdapterSetQualNameTest_2091, BoundarySeparatorAtStartUsesEmptyUriAndMayThrow_2091) {
  XML_Node parent(/*_parent*/ 0, "root", /*_kind*/ 0);
  XML_Node node(&parent, "tmp", /*_kind*/ 0);

  // fullName begins with separator: uri is empty, local is "prop".
  std::string fullName;
  fullName.push_back(FullNameSeparator);
  fullName += "prop";

  // Behavior is observable: either it succeeds (if empty URI is registered)
  // or it throws (most likely). We only verify it does not crash and that,
  // on success, it produces a name ending with "prop".
  try {
    SetQualName(fullName.c_str(), &node);
    EXPECT_TRUE(EndsWith(node.name, "prop"));
  } catch (...) {
    SUCCEED();
  }
}