// =================================================================================================
// UNIT TESTS
// File: ./TestProjects/exiv2/xmpsdk/src/WXMPMeta_SetProperty_Int_1_test.cpp
// Target: WXMPMeta_SetProperty_Int_1 (from WXMPMeta.cpp)
// TEST_ID: 2031
// =================================================================================================

#include <gtest/gtest.h>

#include <limits>
#include <string>

// XMP SDK / Exiv2 XMP headers (project-local)
#include "XMP_Const.h"
#include "WXMP_Common.hpp"
#include "XMPMeta.hpp"

// If XMPMetaRef is not visible via included headers in your build, it is typically a void*.
// We avoid guessing internal details; this is only to satisfy the wrapper signature.
#ifndef XMPMetaRef
using XMPMetaRef = void*;
#endif

// Declare the wrapper under test (C linkage is common for these glue wrappers).
extern "C" {
void WXMPMeta_SetProperty_Int_1(XMPMetaRef xmpRef,
                               XMP_StringPtr schemaNS,
                               XMP_StringPtr propName,
                               XMP_Int32 propValue,
                               XMP_OptionBits options,
                               WXMP_Result* wResult);
}

namespace {

class WXMPMetaSetPropertyInt1Test_2031 : public ::testing::Test {
 protected:
  void SetUp() override {
    meta = new XMPMeta();
    xmpRef = reinterpret_cast<XMPMetaRef>(meta);
  }

  void TearDown() override {
    delete meta;
    meta = nullptr;
    xmpRef = nullptr;
  }

  static constexpr XMP_StringPtr kSchemaNS = "http://ns.adobe.com/xap/1.0/";
  static constexpr XMP_StringPtr kPropName = "TestIntProperty";

  XMPMeta* meta{nullptr};
  XMPMetaRef xmpRef{nullptr};
};

TEST_F(WXMPMetaSetPropertyInt1Test_2031, SetsIntPropertyAndCanReadBack_2031) {
  WXMP_Result wResult;
  ASSERT_EQ(wResult.errMessage, nullptr);

  // Precondition: property should not exist yet (observable via GetProperty_Int).
  XMP_Int32 beforeValue = 0;
  XMP_OptionBits beforeOpts = 0;
  EXPECT_FALSE(meta->GetProperty_Int(kSchemaNS, kPropName, &beforeValue, &beforeOpts));

  EXPECT_NO_THROW(WXMPMeta_SetProperty_Int_1(
      xmpRef, kSchemaNS, kPropName, /*propValue*/ 42, /*options*/ 0, &wResult));

  // On success, errMessage should remain null.
  EXPECT_EQ(wResult.errMessage, nullptr);

  XMP_Int32 afterValue = 0;
  XMP_OptionBits afterOpts = 0;
  EXPECT_TRUE(meta->GetProperty_Int(kSchemaNS, kPropName, &afterValue, &afterOpts));
  EXPECT_EQ(afterValue, 42);
}

TEST_F(WXMPMetaSetPropertyInt1Test_2031, BoundaryValues_Int32MinAndMax_2031) {
  WXMP_Result wResultMin;
  EXPECT_NO_THROW(WXMPMeta_SetProperty_Int_1(
      xmpRef, kSchemaNS, "MinInt32", std::numeric_limits<XMP_Int32>::min(), 0, &wResultMin));
  EXPECT_EQ(wResultMin.errMessage, nullptr);

  XMP_Int32 vMin = 0;
  XMP_OptionBits oMin = 0;
  EXPECT_TRUE(meta->GetProperty_Int(kSchemaNS, "MinInt32", &vMin, &oMin));
  EXPECT_EQ(vMin, std::numeric_limits<XMP_Int32>::min());

  WXMP_Result wResultMax;
  EXPECT_NO_THROW(WXMPMeta_SetProperty_Int_1(
      xmpRef, kSchemaNS, "MaxInt32", std::numeric_limits<XMP_Int32>::max(), 0, &wResultMax));
  EXPECT_EQ(wResultMax.errMessage, nullptr);

  XMP_Int32 vMax = 0;
  XMP_OptionBits oMax = 0;
  EXPECT_TRUE(meta->GetProperty_Int(kSchemaNS, "MaxInt32", &vMax, &oMax));
  EXPECT_EQ(vMax, std::numeric_limits<XMP_Int32>::max());
}

TEST_F(WXMPMetaSetPropertyInt1Test_2031, NullSchemaNamespaceReportsError_2031) {
  WXMP_Result wResult;

  // Ensure a call with invalid schemaNS does not crash/escape exceptions.
  EXPECT_NO_THROW(WXMPMeta_SetProperty_Int_1(
      xmpRef, /*schemaNS*/ nullptr, kPropName, 7, 0, &wResult));

  // Observable error reporting via WXMP_Result.
  EXPECT_NE(wResult.errMessage, nullptr);

  // Property should not be set when schema is invalid.
  XMP_Int32 value = 0;
  XMP_OptionBits opts = 0;
  EXPECT_FALSE(meta->GetProperty_Int(kSchemaNS, kPropName, &value, &opts));
}

TEST_F(WXMPMetaSetPropertyInt1Test_2031, EmptySchemaNamespaceReportsError_2031) {
  WXMP_Result wResult;

  EXPECT_NO_THROW(WXMPMeta_SetProperty_Int_1(
      xmpRef, /*schemaNS*/ "", kPropName, 7, 0, &wResult));

  EXPECT_NE(wResult.errMessage, nullptr);

  XMP_Int32 value = 0;
  XMP_OptionBits opts = 0;
  EXPECT_FALSE(meta->GetProperty_Int(kSchemaNS, kPropName, &value, &opts));
}

TEST_F(WXMPMetaSetPropertyInt1Test_2031, NullPropertyNameReportsError_2031) {
  WXMP_Result wResult;

  EXPECT_NO_THROW(WXMPMeta_SetProperty_Int_1(
      xmpRef, kSchemaNS, /*propName*/ nullptr, 7, 0, &wResult));

  EXPECT_NE(wResult.errMessage, nullptr);

  // With null propName, there is no valid target property to check, but we can
  // at least verify a known different property was not created as a side effect.
  XMP_Int32 value = 0;
  XMP_OptionBits opts = 0;
  EXPECT_FALSE(meta->GetProperty_Int(kSchemaNS, kPropName, &value, &opts));
}

TEST_F(WXMPMetaSetPropertyInt1Test_2031, EmptyPropertyNameReportsError_2031) {
  WXMP_Result wResult;

  EXPECT_NO_THROW(WXMPMeta_SetProperty_Int_1(
      xmpRef, kSchemaNS, /*propName*/ "", 7, 0, &wResult));

  EXPECT_NE(wResult.errMessage, nullptr);

  XMP_Int32 value = 0;
  XMP_OptionBits opts = 0;
  EXPECT_FALSE(meta->GetProperty_Int(kSchemaNS, kPropName, &value, &opts));
}

}  // namespace