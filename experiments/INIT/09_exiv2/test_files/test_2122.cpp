// =================================================================================================
// UNIT TESTS for AddQualifierNode (XMP_Node*, const XML_Node&)
// File: ./TestProjects/exiv2/xmpsdk/src/ParseRDF.cpp
// TEST_ID: 2122
// =================================================================================================

#include <gtest/gtest.h>

#include <string>

// Pull in required types used by the interface under test.
#include "./TestProjects/exiv2/xmpsdk/src/XMPCore_Impl.hpp"
#include "./TestProjects/exiv2/xmpsdk/src/XMLParserAdapter.hpp"
#include "XMP_Const.h"

// The function under test is declared `static` in ParseRDF.cpp (internal linkage).
// To test it as a black box via its real implementation, we include the .cpp.
#include "./TestProjects/exiv2/xmpsdk/src/ParseRDF.cpp"

namespace {

class AddQualifierNode_XMLNodeTest_2122 : public ::testing::Test {
protected:
  static XML_Node MakeAttr(std::string nsURI, std::string name, std::string value) {
    XML_Node attr(/*parent*/ nullptr, /*name*/ "attr", /*kind*/ static_cast<XMP_Uns8>(0));
    attr.ns = std::move(nsURI);
    attr.name = std::move(name);
    attr.value = std::move(value);
    return attr;
  }
};

TEST_F(AddQualifierNode_XMLNodeTest_2122, ThrowsWhenNamespaceEmptyEvenIfParentNull_2122) {
  const XML_Node attr = MakeAttr(/*nsURI*/ "", /*name*/ "a", /*value*/ "v");

  // The wrapper explicitly checks attr.ns and throws if empty.
  EXPECT_ANY_THROW((void)AddQualifierNode(/*xmpParent*/ nullptr, attr));
}

TEST_F(AddQualifierNode_XMLNodeTest_2122, ThrowsWhenNamespaceEmptyEvenIfNameAndValueEmpty_2122) {
  const XML_Node attr = MakeAttr(/*nsURI*/ "", /*name*/ "", /*value*/ "");

  EXPECT_ANY_THROW((void)AddQualifierNode(/*xmpParent*/ nullptr, attr));
}

TEST_F(AddQualifierNode_XMLNodeTest_2122, DoesNotThrowWhenNamespaceNonEmpty_2122) {
  XMP_Node xmpParent(/*parent*/ nullptr, /*name*/ "root", /*options*/ 0);
  const XML_Node attr = MakeAttr(/*nsURI*/ "http://example.com/ns", /*name*/ "qual", /*value*/ "val");

  EXPECT_NO_THROW({
    (void)AddQualifierNode(&xmpParent, attr);
  });
}

TEST_F(AddQualifierNode_XMLNodeTest_2122, TreatsWhitespaceNamespaceAsNonEmpty_2122) {
  XMP_Node xmpParent(/*parent*/ nullptr, /*name*/ "root", /*options*/ 0);
  const XML_Node attr = MakeAttr(/*nsURI*/ "   ", /*name*/ "qual", /*value*/ "val");

  // The interface only checks `empty()`. Whitespace is non-empty.
  EXPECT_NO_THROW({
    (void)AddQualifierNode(&xmpParent, attr);
  });
}

}  // namespace