// ============================================================================
// TEST_ID: 2124
// File: ProcessRDF_test.cpp
// Unit tests for ProcessRDF (./TestProjects/exiv2/xmpsdk/src/ParseRDF.cpp)
// ============================================================================

#include <gtest/gtest.h>

#include <cstdint>
#include <string>

// ---------------------------------------------------------------------------
// Minimal type shims (only what we need to compile the unit under test).
// We do NOT re-implement any internal logic.
// ---------------------------------------------------------------------------
using XMP_Uns8 = std::uint8_t;
using XMP_OptionBits = std::uint32_t;
using XMP_StringPtr = const char*;

// Minimal stand-ins for the classes referenced by the interface.
class XMP_Node {
public:
  // Just enough surface for constructing dummy nodes in tests.
  std::string name;
  std::string value;
  XMP_Node* parent{nullptr};

  XMP_Node(XMP_Node* _parent, XMP_StringPtr _name, XMP_OptionBits /*_options*/)
      : name(_name ? _name : ""), parent(_parent) {}
};

class XML_Node {
public:
  XMP_Uns8 kind{0};
  std::string ns;
  std::string name;
  std::string value;
  size_t nsPrefixLen{0};
  XML_Node* parent{nullptr};

  XML_Node(XML_Node* _parent, XMP_StringPtr _name, XMP_Uns8 _kind)
      : kind(_kind), name(_name ? _name : ""), parent(_parent) {}
};

// ---------------------------------------------------------------------------
// External dependency seam:
// ProcessRDF calls RDF_RDF(xmpTree, rdfNode). We verify that interaction by
// substituting RDF_RDF at compile-time via macro before including ParseRDF.cpp.
// ---------------------------------------------------------------------------

namespace ProcessRDF_Test_2124 {
struct CallLog {
  int callCount = 0;
  XMP_Node* lastTree = nullptr;
  const XML_Node* lastRdfNode = nullptr;
} g_log;

inline void ResetLog() { g_log = CallLog{}; }
}  // namespace ProcessRDF_Test_2124

// Mocked collaborator function that ProcessRDF is expected to call.
static void Mock_RDF_RDF(XMP_Node* xmpTree, const XML_Node& rdfNode) {
  using namespace ProcessRDF_Test_2124;
  ++g_log.callCount;
  g_log.lastTree = xmpTree;
  g_log.lastRdfNode = &rdfNode;
}

// IgnoreParam is referenced by ProcessRDF; define a harmless shim.
template <typename T>
static inline void Mock_IgnoreParam(const T&) {}

// Redirect names used by the unit under test to our shims.
#define RDF_RDF Mock_RDF_RDF
#define IgnoreParam Mock_IgnoreParam

// Include the implementation under test.
// NOTE: This is intentional to keep the test black-box with respect to logic,
// while allowing verification of observable collaboration behavior.
#include "./TestProjects/exiv2/xmpsdk/src/ParseRDF.cpp"

#undef RDF_RDF
#undef IgnoreParam

// ---------------------------------------------------------------------------
// Test fixture
// ---------------------------------------------------------------------------
class ProcessRDFTest_2124 : public ::testing::Test {
protected:
  void SetUp() override { ProcessRDF_Test_2124::ResetLog(); }
};

// ---------------------------------------------------------------------------
// Tests
// ---------------------------------------------------------------------------

TEST_F(ProcessRDFTest_2124, CallsRdfRdfOnceWithSameArgs_2124) {
  XMP_Node tree(/*parent=*/nullptr, "root", /*options=*/0);
  XML_Node rdf(/*parent=*/nullptr, "rdf:RDF", /*kind=*/1);

  ProcessRDF(&tree, rdf, /*options=*/0x12345678u);

  EXPECT_EQ(ProcessRDF_Test_2124::g_log.callCount, 1);
  EXPECT_EQ(ProcessRDF_Test_2124::g_log.lastTree, &tree);
  EXPECT_EQ(ProcessRDF_Test_2124::g_log.lastRdfNode, &rdf);
}

TEST_F(ProcessRDFTest_2124, DifferentOptionsStillCallsRdfRdf_2124) {
  XMP_Node tree(/*parent=*/nullptr, "root", /*options=*/0);
  XML_Node rdf(/*parent=*/nullptr, "rdf:RDF", /*kind=*/2);

  ProcessRDF(&tree, rdf, /*options=*/0u);
  EXPECT_EQ(ProcessRDF_Test_2124::g_log.callCount, 1);
  EXPECT_EQ(ProcessRDF_Test_2124::g_log.lastTree, &tree);
  EXPECT_EQ(ProcessRDF_Test_2124::g_log.lastRdfNode, &rdf);

  ProcessRDF_Test_2124::ResetLog();

  ProcessRDF(&tree, rdf, /*options=*/0xFFFFFFFFu);
  EXPECT_EQ(ProcessRDF_Test_2124::g_log.callCount, 1);
  EXPECT_EQ(ProcessRDF_Test_2124::g_log.lastTree, &tree);
  EXPECT_EQ(ProcessRDF_Test_2124::g_log.lastRdfNode, &rdf);
}

TEST_F(ProcessRDFTest_2124, AllowsNullTreePointerAndStillInvokesRdfRdf_2124) {
  XML_Node rdf(/*parent=*/nullptr, "rdf:RDF", /*kind=*/3);

  // Boundary: null tree pointer.
  ProcessRDF(/*xmpTree=*/nullptr, rdf, /*options=*/0x1u);

  EXPECT_EQ(ProcessRDF_Test_2124::g_log.callCount, 1);
  EXPECT_EQ(ProcessRDF_Test_2124::g_log.lastTree, nullptr);
  EXPECT_EQ(ProcessRDF_Test_2124::g_log.lastRdfNode, &rdf);
}

TEST_F(ProcessRDFTest_2124, MultipleCallsAccumulateAsExpected_2124) {
  XMP_Node treeA(/*parent=*/nullptr, "A", /*options=*/0);
  XMP_Node treeB(/*parent=*/nullptr, "B", /*options=*/0);
  XML_Node rdf1(/*parent=*/nullptr, "rdf:RDF", /*kind=*/10);
  XML_Node rdf2(/*parent=*/nullptr, "rdf:RDF", /*kind=*/11);

  ProcessRDF(&treeA, rdf1, /*options=*/7u);
  EXPECT_EQ(ProcessRDF_Test_2124::g_log.callCount, 1);
  EXPECT_EQ(ProcessRDF_Test_2124::g_log.lastTree, &treeA);
  EXPECT_EQ(ProcessRDF_Test_2124::g_log.lastRdfNode, &rdf1);

  ProcessRDF(&treeB, rdf2, /*options=*/8u);
  EXPECT_EQ(ProcessRDF_Test_2124::g_log.callCount, 2);
  EXPECT_EQ(ProcessRDF_Test_2124::g_log.lastTree, &treeB);
  EXPECT_EQ(ProcessRDF_Test_2124::g_log.lastRdfNode, &rdf2);
}