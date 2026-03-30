// ============================================================================
// TEST_ID: 2014
// Unit tests for WXMPMeta_SetQualifier_1
// File: ./TestProjects/exiv2/xmpsdk/src/WXMPMeta.cpp
// ============================================================================

#include <gtest/gtest.h>

#include "XMP_Const.h"
#include "client-glue/WXMP_Common.hpp"
#include "XMPMeta.hpp"

// The wrapper under test (implemented in WXMPMeta.cpp).
extern "C" void WXMPMeta_SetQualifier_1(
    XMPMetaRef xmpRef,
    XMP_StringPtr schemaNS,
    XMP_StringPtr propName,
    XMP_StringPtr qualNS,
    XMP_StringPtr qualName,
    XMP_StringPtr qualValue,
    XMP_OptionBits options,
    WXMP_Result* wResult);

namespace {

class WXMPMetaSetQualifier1Test_2014 : public ::testing::Test {
protected:
  static void SetUpTestSuite() {
    // If Initialize() is required, calling it here makes tests robust.
    // If it is a no-op, it is still safe to call.
    (void)XMPMeta::Initialize();
  }

  static void TearDownTestSuite() {
    // Safe even if Initialize() was a no-op.
    XMPMeta::Terminate();
  }

  static XMPMetaRef ToRef(XMPMeta* meta) {
    // WXMP wrappers typically treat XMPMetaRef as an opaque pointer to XMPMeta.
    return reinterpret_cast<XMPMetaRef>(meta);
  }

  static constexpr XMP_StringPtr kSchemaNS = "http://ns.adobe.com/xap/1.0/";
  static constexpr XMP_StringPtr kPropName = "CreatorTool";

  static constexpr XMP_StringPtr kXmlNS = "http://www.w3.org/XML/1998/namespace";
  static constexpr XMP_StringPtr kLangQualName = "lang";
};

TEST_F(WXMPMetaSetQualifier1Test_2014, SetsQualifierAndIsObservableViaGetQualifier_2014) {
  XMPMeta meta;
  meta.SetProperty(kSchemaNS, kPropName, "UnitTestValue", 0);

  WXMP_Result wr;
  WXMPMeta_SetQualifier_1(
      ToRef(&meta),
      kSchemaNS,
      kPropName,
      kXmlNS,
      kLangQualName,
      "en-US",
      0,
      &wr);

  ASSERT_EQ(wr.errMessage, nullptr);

  ASSERT_TRUE(meta.DoesQualifierExist(kSchemaNS, kPropName, kXmlNS, kLangQualName));

  XMP_StringPtr qv = nullptr;
  XMP_StringLen qvSize = 0;
  XMP_OptionBits qOpts = 0;
  ASSERT_TRUE(meta.GetQualifier(kSchemaNS, kPropName, kXmlNS, kLangQualName, &qv, &qvSize, &qOpts));
  ASSERT_NE(qv, nullptr);
  EXPECT_STREQ(qv, "en-US");
}

TEST_F(WXMPMetaSetQualifier1Test_2014, EmptySchemaNamespaceReturnsError_2014) {
  XMPMeta meta;
  meta.SetProperty(kSchemaNS, kPropName, "UnitTestValue", 0);

  WXMP_Result wr;
  WXMPMeta_SetQualifier_1(
      ToRef(&meta),
      "",  // empty schemaNS
      kPropName,
      kXmlNS,
      kLangQualName,
      "en-US",
      0,
      &wr);

  EXPECT_NE(wr.errMessage, nullptr);
}

TEST_F(WXMPMetaSetQualifier1Test_2014, NullSchemaNamespaceReturnsError_2014) {
  XMPMeta meta;
  meta.SetProperty(kSchemaNS, kPropName, "UnitTestValue", 0);

  WXMP_Result wr;
  WXMPMeta_SetQualifier_1(
      ToRef(&meta),
      nullptr,  // null schemaNS
      kPropName,
      kXmlNS,
      kLangQualName,
      "en-US",
      0,
      &wr);

  EXPECT_NE(wr.errMessage, nullptr);
}

TEST_F(WXMPMetaSetQualifier1Test_2014, EmptyPropertyNameReturnsError_2014) {
  XMPMeta meta;

  WXMP_Result wr;
  WXMPMeta_SetQualifier_1(
      ToRef(&meta),
      kSchemaNS,
      "",  // empty propName
      kXmlNS,
      kLangQualName,
      "en-US",
      0,
      &wr);

  EXPECT_NE(wr.errMessage, nullptr);
}

TEST_F(WXMPMetaSetQualifier1Test_2014, NullPropertyNameReturnsError_2014) {
  XMPMeta meta;

  WXMP_Result wr;
  WXMPMeta_SetQualifier_1(
      ToRef(&meta),
      kSchemaNS,
      nullptr,  // null propName
      kXmlNS,
      kLangQualName,
      "en-US",
      0,
      &wr);

  EXPECT_NE(wr.errMessage, nullptr);
}

TEST_F(WXMPMetaSetQualifier1Test_2014, EmptyQualifierNamespaceReturnsError_2014) {
  XMPMeta meta;
  meta.SetProperty(kSchemaNS, kPropName, "UnitTestValue", 0);

  WXMP_Result wr;
  WXMPMeta_SetQualifier_1(
      ToRef(&meta),
      kSchemaNS,
      kPropName,
      "",  // empty qualNS
      kLangQualName,
      "en-US",
      0,
      &wr);

  EXPECT_NE(wr.errMessage, nullptr);
}

TEST_F(WXMPMetaSetQualifier1Test_2014, NullQualifierNamespaceReturnsError_2014) {
  XMPMeta meta;
  meta.SetProperty(kSchemaNS, kPropName, "UnitTestValue", 0);

  WXMP_Result wr;
  WXMPMeta_SetQualifier_1(
      ToRef(&meta),
      kSchemaNS,
      kPropName,
      nullptr,  // null qualNS
      kLangQualName,
      "en-US",
      0,
      &wr);

  EXPECT_NE(wr.errMessage, nullptr);
}

TEST_F(WXMPMetaSetQualifier1Test_2014, EmptyQualifierNameReturnsError_2014) {
  XMPMeta meta;
  meta.SetProperty(kSchemaNS, kPropName, "UnitTestValue", 0);

  WXMP_Result wr;
  WXMPMeta_SetQualifier_1(
      ToRef(&meta),
      kSchemaNS,
      kPropName,
      kXmlNS,
      "",  // empty qualName
      "en-US",
      0,
      &wr);

  EXPECT_NE(wr.errMessage, nullptr);
}

TEST_F(WXMPMetaSetQualifier1Test_2014, NullQualifierNameReturnsError_2014) {
  XMPMeta meta;
  meta.SetProperty(kSchemaNS, kPropName, "UnitTestValue", 0);

  WXMP_Result wr;
  WXMPMeta_SetQualifier_1(
      ToRef(&meta),
      kSchemaNS,
      kPropName,
      kXmlNS,
      nullptr,  // null qualName
      "en-US",
      0,
      &wr);

  EXPECT_NE(wr.errMessage, nullptr);
}

}  // namespace