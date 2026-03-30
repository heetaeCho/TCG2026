// =================================================================================================
// UNIT TESTS for ParseRDF.cpp (RDF_RDF)  -- TEST_ID: 2125
// =================================================================================================

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <cstdint>
#include <exception>
#include <string>

// Try to include real types if available in the build; otherwise provide minimal fallbacks.
#if __has_include("TestProjects/exiv2/xmpsdk/include/XMP_Const.h")
  #include "TestProjects/exiv2/xmpsdk/include/XMP_Const.h"
#elif __has_include("XMP_Const.h")
  #include "XMP_Const.h"
#endif

#if __has_include("TestProjects/exiv2/xmpsdk/src/XMPCore_Impl.hpp")
  #include "TestProjects/exiv2/xmpsdk/src/XMPCore_Impl.hpp"
#elif __has_include("XMPCore_Impl.hpp")
  #include "XMPCore_Impl.hpp"
#endif

#if __has_include("TestProjects/exiv2/xmpsdk/src/XMLParserAdapter.hpp")
  #include "TestProjects/exiv2/xmpsdk/src/XMLParserAdapter.hpp"
#elif __has_include("XMLParserAdapter.hpp")
  #include "XMLParserAdapter.hpp"
#endif

// --------- Minimal fallbacks (only if the real SDK headers did not provide these) ---------
#ifndef kXMPErr_BadRDF
static constexpr int kXMPErr_BadRDF = 202;
#endif

#ifndef XMP_OptionBits
using XMP_OptionBits = std::uint32_t;
#endif

#ifndef XMP_Uns8
using XMP_Uns8 = std::uint8_t;
#endif

#ifndef XMP_StringPtr
using XMP_StringPtr = const char*;
#endif

// kIsTopLevel is referenced by RDF_RDF. If it's not provided by the included implementation,
// define a harmless placeholder to allow compilation. Tests do not assert its numeric value.
#ifndef kIsTopLevel
static constexpr XMP_OptionBits kIsTopLevel = 0;
#endif

// -------------------------------------------------------------------------------------------------
// Test seam for XMP_Throw (external collaborator): make it observable via a thrown exception type.
// -------------------------------------------------------------------------------------------------
struct TestXMPThrowException final : public std::exception {
  TestXMPThrowException(std::string m, int e) : msg(std::move(m)), err(e) {}
  const char* what() const noexcept override { return msg.c_str(); }
  std::string msg;
  int err;
};

// If the real XMP_Throw is already defined by headers, don't override it.
#ifndef XMP_Throw
  #define XMP_Throw(MSG, ERR) throw TestXMPThrowException((MSG), (ERR))
#endif

// -------------------------------------------------------------------------------------------------
// Test seam for RDF_NodeElementList (external interaction): forward calls into a gMock.
// -------------------------------------------------------------------------------------------------
class MockRDFNodeElementList_2125 {
public:
  MOCK_METHOD(void, Call, (XMP_Node* xmpTree, const XML_Node& xmlNode, XMP_OptionBits options), ());
};

static MockRDFNodeElementList_2125* g_mockNodeElemList_2125 = nullptr;

// If the real RDF_NodeElementList exists in the included ParseRDF.cpp, this would clash.
// The prompt provides only RDF_RDF, so we provide this collaborator for unit testing.
static void RDF_NodeElementList(XMP_Node* xmpTree, const XML_Node& xmlNode, XMP_OptionBits options) {
  if (g_mockNodeElemList_2125) g_mockNodeElemList_2125->Call(xmpTree, xmlNode, options);
}

// -------------------------------------------------------------------------------------------------
// Include the unit under test (static function) directly so it is visible in this TU.
// -------------------------------------------------------------------------------------------------
#include "TestProjects/exiv2/xmpsdk/src/ParseRDF.cpp"

// =================================================================================================
// Test Fixture
// =================================================================================================
class RDF_RDFTest_2125 : public ::testing::Test {
protected:
  ::testing::StrictMock<MockRDFNodeElementList_2125> mock_;

  void SetUp() override { g_mockNodeElemList_2125 = &mock_; }
  void TearDown() override { g_mockNodeElemList_2125 = nullptr; }

  static XML_Node MakeRdfNode_NoAttrs() {
    // kind value isn't relevant to RDF_RDF's observable behavior for these tests.
    return XML_Node(XML_NodePtr(), "rdf:RDF", /*kind*/ 0);
  }

  static XML_Node MakeRdfNode_WithAnyAttr() {
    XML_Node node(XML_NodePtr(), "rdf:RDF", /*kind*/ 0);
    // We only need attrs to be non-empty. Push a null pointer to avoid relying on attr-node details.
    node.attrs.push_back(XML_NodePtr());
    return node;
  }
};

// =================================================================================================
// Tests (TEST_ID: 2125)
// =================================================================================================

TEST_F(RDF_RDFTest_2125, CallsNodeElementListWhenNoAttributes_2125) {
  XMP_Node xmpTree(/*parent*/ nullptr, /*name*/ "root", /*options*/ 0);
  XML_Node rdfNode = MakeRdfNode_NoAttrs();

  EXPECT_CALL(mock_, Call(&xmpTree, ::testing::Ref(rdfNode), ::testing::_)).Times(1);
  EXPECT_NO_THROW(RDF_RDF(&xmpTree, rdfNode));
}

TEST_F(RDF_RDFTest_2125, AllowsNullXmpTreeAndStillCallsNodeElementList_2125) {
  XML_Node rdfNode = MakeRdfNode_NoAttrs();

  EXPECT_CALL(mock_, Call(nullptr, ::testing::Ref(rdfNode), ::testing::_)).Times(1);
  EXPECT_NO_THROW(RDF_RDF(nullptr, rdfNode));
}

TEST_F(RDF_RDFTest_2125, ThrowsBadRdfWhenAttributesPresent_2125) {
  XMP_Node xmpTree(/*parent*/ nullptr, /*name*/ "root", /*options*/ 0);
  XML_Node rdfNode = MakeRdfNode_WithAnyAttr();

  EXPECT_CALL(mock_, Call(::testing::_, ::testing::_, ::testing::_)).Times(0);

  try {
    RDF_RDF(&xmpTree, rdfNode);
    FAIL() << "Expected an exception to be thrown";
  } catch (const TestXMPThrowException& e) {
    EXPECT_EQ(e.err, kXMPErr_BadRDF);
  } catch (...) {
    // If the real XMP_Throw is used in this build, it may throw a different exception type.
    SUCCEED();
  }
}

TEST_F(RDF_RDFTest_2125, ThrowsWhenMultipleAttributesPresent_2125) {
  XMP_Node xmpTree(/*parent*/ nullptr, /*name*/ "root", /*options*/ 0);
  XML_Node rdfNode(XML_NodePtr(), "rdf:RDF", /*kind*/ 0);
  rdfNode.attrs.push_back(XML_NodePtr());
  rdfNode.attrs.push_back(XML_NodePtr());

  EXPECT_CALL(mock_, Call(::testing::_, ::testing::_, ::testing::_)).Times(0);
  EXPECT_ANY_THROW(RDF_RDF(&xmpTree, rdfNode));
}