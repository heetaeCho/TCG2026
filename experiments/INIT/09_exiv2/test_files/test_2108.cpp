// =================================================================================================
// TEST_ID: 2108
// File: ./TestProjects/exiv2/xmpsdk/src/XMPMeta-Serialize.cpp (static CanBeRDFAttrProp)
// =================================================================================================

#include <gtest/gtest.h>

// Include the internal node type / option bits.
#include "TestProjects/exiv2/xmpsdk/src/XMPCore_Impl.hpp"
#include "TestProjects/exiv2/xmpsdk/include/XMP_Const.h"

// Include the .cpp directly so this test TU can call the file-local static function.
#include "TestProjects/exiv2/xmpsdk/src/XMPMeta-Serialize.cpp"

namespace {

class CanBeRDFAttrPropTest_2108 : public ::testing::Test {
protected:
  static XMP_Node MakeProp(XMP_StringPtr name, XMP_OptionBits opts = 0) {
    // Parent can be null for these tests; behavior under test is local to the node fields used.
    return XMP_Node(/*_parent*/ nullptr, /*_name*/ name, /*_options*/ opts);
  }
};

TEST_F(CanBeRDFAttrPropTest_2108, ReturnsTrueForSimpleNonCompositeProperty_2108) {
  const XMP_Node prop = MakeProp("dc:title", /*opts*/ 0);
  EXPECT_TRUE(CanBeRDFAttrProp(&prop));
}

TEST_F(CanBeRDFAttrPropTest_2108, ReturnsFalseWhenNameStartsWithLeftBracket_2108) {
  const XMP_Node prop = MakeProp("[1]", /*opts*/ 0);
  EXPECT_FALSE(CanBeRDFAttrProp(&prop));
}

TEST_F(CanBeRDFAttrPropTest_2108, ReturnsFalseWhenQualifiersArePresent_2108) {
  XMP_Node prop = MakeProp("xmp:CreatorTool", /*opts*/ 0);

  // Only the observable condition ".qualifiers.empty()" matters here. We avoid allocating nodes by
  // inserting a null entry if the container holds pointers (as used by the XMPSDK internals).
  prop.qualifiers.push_back(nullptr);

  EXPECT_FALSE(CanBeRDFAttrProp(&prop));
}

TEST_F(CanBeRDFAttrPropTest_2108, ReturnsFalseWhenValueIsURIOptionIsSet_2108) {
  const XMP_Node prop = MakeProp("xmp:Identifier", /*opts*/ kXMP_PropValueIsURI);
  EXPECT_FALSE(CanBeRDFAttrProp(&prop));
}

TEST_F(CanBeRDFAttrPropTest_2108, ReturnsFalseWhenCompositeMaskIsSetWithStruct_2108) {
  const XMP_Node prop = MakeProp("xmp:SomeStruct", /*opts*/ kXMP_PropValueIsStruct);
  EXPECT_FALSE(CanBeRDFAttrProp(&prop));
}

TEST_F(CanBeRDFAttrPropTest_2108, ReturnsFalseWhenCompositeMaskIsSetWithArray_2108) {
  const XMP_Node prop = MakeProp("xmp:SomeArray", /*opts*/ kXMP_PropValueIsArray);
  EXPECT_FALSE(CanBeRDFAttrProp(&prop));
}

TEST_F(CanBeRDFAttrPropTest_2108, ReturnsTrueWhenOnlyNonDisqualifyingOptionsAreSet_2108) {
  // Boundary-ish: set flags that are not checked by CanBeRDFAttrProp.
  const XMP_Node prop = MakeProp("xmp:AliasedProp", /*opts*/ kXMP_PropIsAlias);
  EXPECT_TRUE(CanBeRDFAttrProp(&prop));
}

}  // namespace