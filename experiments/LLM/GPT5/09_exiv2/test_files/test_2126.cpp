// =================================================================================================
// TEST_ID: 2126
// Unit tests for RDF_NodeElementList (ParseRDF.cpp)
// =================================================================================================

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <cstdint>
#include <stdexcept>
#include <string>
#include <vector>
#include <memory>

// Pull in real types used by ParseRDF.cpp.
#include "TestProjects/exiv2/xmpsdk/src/XMPCore_Impl.hpp"
#include "TestProjects/exiv2/xmpsdk/src/XMLParserAdapter.hpp"

// ---- Interception hooks ----
// 1) Turn XMP_Assert into an observable failure (exception) for testing.
#ifndef XMP_Assert
#define XMP_Assert(cond) \
  do {                   \
    if (!(cond)) throw std::runtime_error("XMP_Assert failed: " #cond); \
  } while (0)
#endif

// 2) Intercept RDF_NodeElement calls to verify external interactions.
struct RDFNodeElementCall_2126 {
  XMP_Node* xmpParent = nullptr;
  const XML_Node* xmlChild = nullptr;
  bool isTopLevel = false;
};

static std::vector<RDFNodeElementCall_2126> g_rdfNodeElementCalls_2126;

static void MockRDF_NodeElement_2126(XMP_Node* xmpParent, const XML_Node& xmlChild, bool isTopLevel) {
  g_rdfNodeElementCalls_2126.push_back(RDFNodeElementCall_2126{ xmpParent, &xmlChild, isTopLevel });
}

// Make ParseRDF.cpp call our mock instead of the real RDF_NodeElement.
#define RDF_NodeElement MockRDF_NodeElement_2126

// Include the implementation file so we can call the internal static function.
#include "TestProjects/exiv2/xmpsdk/src/ParseRDF.cpp"

// -------------------------------------------------------------------------------------------------
// Helpers (black-box probing of XML_Node::IsWhitespaceNode behavior)
// -------------------------------------------------------------------------------------------------

static XMP_Uns8 FindWhitespaceKind_2126() {
  // Probe kinds 0..255. If none are recognized as whitespace, return 0xFF and tests can skip.
  for (int k = 0; k <= 255; ++k) {
    XML_Node n(nullptr, "t", static_cast<XMP_Uns8>(k));
    n.value = " \n\t\r  ";
    if (n.IsWhitespaceNode()) return static_cast<XMP_Uns8>(k);
  }
  return static_cast<XMP_Uns8>(0xFF);
}

static XMP_Uns8 FindNonWhitespaceKind_2126(XMP_Uns8 whitespaceKind) {
  for (int k = 0; k <= 255; ++k) {
    XMP_Uns8 kind = static_cast<XMP_Uns8>(k);
    if (kind == whitespaceKind) continue;
    XML_Node n(nullptr, "t", kind);
    n.value = "not-whitespace";
    if (!n.IsWhitespaceNode()) return kind;
  }
  // Fallback: try whitespaceKind with non-whitespace content (some impls may treat by value only).
  if (whitespaceKind != static_cast<XMP_Uns8>(0xFF)) {
    XML_Node n(nullptr, "t", whitespaceKind);
    n.value = "not-whitespace";
    if (!n.IsWhitespaceNode()) return whitespaceKind;
  }
  return static_cast<XMP_Uns8>(0xFF);
}

static std::shared_ptr<XML_Node> MakeNode_2126(XML_Node* parent, XMP_Uns8 kind, const std::string& name,
                                               const std::string& value) {
  auto ptr = std::make_shared<XML_Node>(parent, name, kind);
  ptr->value = value;
  return ptr;
}

// =================================================================================================
// Test Fixture
// =================================================================================================

class RDF_NodeElementListTest_2126 : public ::testing::Test {
protected:
  void SetUp() override { g_rdfNodeElementCalls_2126.clear(); }
  void TearDown() override { g_rdfNodeElementCalls_2126.clear(); }
};

// =================================================================================================
// Tests
// =================================================================================================

TEST_F(RDF_NodeElementListTest_2126, TopLevelTrueEmptyContentMakesNoCalls_2126) {
  XMP_Node xmpParent(nullptr, "p", 0);
  XML_Node xmlParent(nullptr, "root", 0);
  xmlParent.content.clear();

  ASSERT_NO_THROW(RDF_NodeElementList(&xmpParent, xmlParent, /*isTopLevel*/ true));
  EXPECT_TRUE(g_rdfNodeElementCalls_2126.empty());
}

TEST_F(RDF_NodeElementListTest_2126, TopLevelFalseTriggersAssertionFailure_2126) {
  XMP_Node xmpParent(nullptr, "p", 0);
  XML_Node xmlParent(nullptr, "root", 0);

  // Observable exceptional behavior: XMP_Assert(isTopLevel).
  EXPECT_THROW(RDF_NodeElementList(&xmpParent, xmlParent, /*isTopLevel*/ false), std::runtime_error);
}

TEST_F(RDF_NodeElementListTest_2126, CallsRDFNodeElementForEachNonWhitespaceChild_2126) {
  const XMP_Uns8 wsKind = FindWhitespaceKind_2126();
  const XMP_Uns8 nonWsKind = FindNonWhitespaceKind_2126(wsKind);
  if (nonWsKind == static_cast<XMP_Uns8>(0xFF)) GTEST_SKIP() << "Could not determine a non-whitespace XML_Node kind.";

  XMP_Node xmpParent(nullptr, "p", 0);
  XML_Node xmlParent(nullptr, "root", nonWsKind);

  auto c1 = MakeNode_2126(&xmlParent, nonWsKind, "c1", "A");
  auto c2 = MakeNode_2126(&xmlParent, nonWsKind, "c2", "B");
  auto c3 = MakeNode_2126(&xmlParent, nonWsKind, "c3", "C");

  xmlParent.content = { c1, c2, c3 };

  RDF_NodeElementList(&xmpParent, xmlParent, /*isTopLevel*/ true);

  ASSERT_EQ(g_rdfNodeElementCalls_2126.size(), 3u);
  EXPECT_EQ(g_rdfNodeElementCalls_2126[0].xmpParent, &xmpParent);
  EXPECT_EQ(g_rdfNodeElementCalls_2126[1].xmpParent, &xmpParent);
  EXPECT_EQ(g_rdfNodeElementCalls_2126[2].xmpParent, &xmpParent);

  EXPECT_EQ(g_rdfNodeElementCalls_2126[0].xmlChild, c1.get());
  EXPECT_EQ(g_rdfNodeElementCalls_2126[1].xmlChild, c2.get());
  EXPECT_EQ(g_rdfNodeElementCalls_2126[2].xmlChild, c3.get());

  EXPECT_TRUE(g_rdfNodeElementCalls_2126[0].isTopLevel);
  EXPECT_TRUE(g_rdfNodeElementCalls_2126[1].isTopLevel);
  EXPECT_TRUE(g_rdfNodeElementCalls_2126[2].isTopLevel);
}

TEST_F(RDF_NodeElementListTest_2126, SkipsWhitespaceChildren_2126) {
  const XMP_Uns8 wsKind = FindWhitespaceKind_2126();
  if (wsKind == static_cast<XMP_Uns8>(0xFF)) GTEST_SKIP() << "Could not determine a whitespace XML_Node kind.";
  const XMP_Uns8 nonWsKind = FindNonWhitespaceKind_2126(wsKind);
  if (nonWsKind == static_cast<XMP_Uns8>(0xFF)) GTEST_SKIP() << "Could not determine a non-whitespace XML_Node kind.";

  XMP_Node xmpParent(nullptr, "p", 0);
  XML_Node xmlParent(nullptr, "root", nonWsKind);

  auto non1 = MakeNode_2126(&xmlParent, nonWsKind, "non1", "X");
  auto ws   = MakeNode_2126(&xmlParent, wsKind,   "ws",   " \n\t ");
  auto non2 = MakeNode_2126(&xmlParent, nonWsKind, "non2", "Y");

  // Sanity check our probe: ensure ws node is actually seen as whitespace.
  if (!ws->IsWhitespaceNode()) GTEST_SKIP() << "Probed whitespace kind did not yield IsWhitespaceNode()==true.";

  xmlParent.content = { non1, ws, non2 };

  RDF_NodeElementList(&xmpParent, xmlParent, /*isTopLevel*/ true);

  ASSERT_EQ(g_rdfNodeElementCalls_2126.size(), 2u);
  EXPECT_EQ(g_rdfNodeElementCalls_2126[0].xmlChild, non1.get());
  EXPECT_EQ(g_rdfNodeElementCalls_2126[1].xmlChild, non2.get());
}

TEST_F(RDF_NodeElementListTest_2126, AllWhitespaceChildrenMakesNoCalls_2126) {
  const XMP_Uns8 wsKind = FindWhitespaceKind_2126();
  if (wsKind == static_cast<XMP_Uns8>(0xFF)) GTEST_SKIP() << "Could not determine a whitespace XML_Node kind.";

  XMP_Node xmpParent(nullptr, "p", 0);
  XML_Node xmlParent(nullptr, "root", wsKind);

  auto ws1 = MakeNode_2126(&xmlParent, wsKind, "ws1", "  ");
  auto ws2 = MakeNode_2126(&xmlParent, wsKind, "ws2", "\n\t");
  auto ws3 = MakeNode_2126(&xmlParent, wsKind, "ws3", " \r\n ");

  if (!ws1->IsWhitespaceNode() || !ws2->IsWhitespaceNode() || !ws3->IsWhitespaceNode()) {
    GTEST_SKIP() << "Could not create nodes recognized as whitespace by IsWhitespaceNode().";
  }

  xmlParent.content = { ws1, ws2, ws3 };

  RDF_NodeElementList(&xmpParent, xmlParent, /*isTopLevel*/ true);
  EXPECT_TRUE(g_rdfNodeElementCalls_2126.empty());
}

TEST_F(RDF_NodeElementListTest_2126, LargeNumberOfChildrenBoundaryCase_2126) {
  const XMP_Uns8 wsKind = FindWhitespaceKind_2126();
  const XMP_Uns8 nonWsKind = FindNonWhitespaceKind_2126(wsKind);
  if (nonWsKind == static_cast<XMP_Uns8>(0xFF)) GTEST_SKIP() << "Could not determine a non-whitespace XML_Node kind.";

  XMP_Node xmpParent(nullptr, "p", 0);
  XML_Node xmlParent(nullptr, "root", nonWsKind);

  std::vector<std::shared_ptr<XML_Node>> keepAlive;
  keepAlive.reserve(200);

  // Alternate non-whitespace / whitespace where possible, otherwise just add non-whitespace.
  size_t expectedCalls = 0;
  for (int i = 0; i < 200; ++i) {
    const bool makeWhitespace = (i % 2 == 1) && (wsKind != static_cast<XMP_Uns8>(0xFF));
    XMP_Uns8 kind = makeWhitespace ? wsKind : nonWsKind;
    std::string val = makeWhitespace ? " \n\t " : ("v" + std::to_string(i));
    auto node = MakeNode_2126(&xmlParent, kind, "n" + std::to_string(i), val);

    // Count expected calls based on observable IsWhitespaceNode().
    if (!node->IsWhitespaceNode()) ++expectedCalls;

    keepAlive.push_back(node);
    xmlParent.content.push_back(node);
  }

  RDF_NodeElementList(&xmpParent, xmlParent, /*isTopLevel*/ true);

  EXPECT_EQ(g_rdfNodeElementCalls_2126.size(), expectedCalls);
  for (const auto& call : g_rdfNodeElementCalls_2126) {
    EXPECT_EQ(call.xmpParent, &xmpParent);
    EXPECT_TRUE(call.isTopLevel);
    ASSERT_NE(call.xmlChild, nullptr);
    EXPECT_FALSE(call.xmlChild->IsWhitespaceNode());
  }
}