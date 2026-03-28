// ============================================================================
// TEST_ID: 2032
// Unit tests for WXMPMeta_SetProperty_Int64_1
// File: test_wxmpmeta_setproperty_int64_1_2032.cpp
// ============================================================================

#include <gtest/gtest.h>

#include "XMP_Const.h"
#include "client-glue/WXMP_Common.hpp"
#include "XMPMeta.hpp"

// The wrapper lives in WXMPMeta.cpp (C-linkage in the SDK glue in many builds).
// Declare it here to avoid depending on an extra header not provided in the prompt.
extern "C" {
void WXMPMeta_SetProperty_Int64_1(XMPMetaRef xmpRef,
                                 XMP_StringPtr schemaNS,
                                 XMP_StringPtr propName,
                                 XMP_Int64 propValue,
                                 XMP_OptionBits options,
                                 WXMP_Result* wResult);
}

namespace {

class WXMPMeta_SetProperty_Int64_1_Test_2032 : public ::testing::Test {
 protected:
  static constexpr XMP_StringPtr kSchemaNS = "http://example.com/ns/1.0/";
  static constexpr XMP_StringPtr kPropName = "TestInt64";
};

TEST_F(WXMPMeta_SetProperty_Int64_1_Test_2032, SetsPropertyAndCanReadBack_2032) {
  XMPMeta meta;
  WXMP_Result wr;

  const XMP_Int64 setValue = 123456789LL;
  WXMPMeta_SetProperty_Int64_1(reinterpret_cast<XMPMetaRef>(&meta), kSchemaNS, kPropName, setValue,
                              /*options*/ 0, &wr);

  EXPECT_EQ(wr.errMessage, nullptr);

  XMP_Int64 gotValue = 0;
  XMP_OptionBits gotOptions = 0;
  const bool found = meta.GetProperty_Int64(kSchemaNS, kPropName, &gotValue, &gotOptions);
  EXPECT_TRUE(found);
  EXPECT_EQ(gotValue, setValue);
}

TEST_F(WXMPMeta_SetProperty_Int64_1_Test_2032, OverwritesExistingValue_2032) {
  XMPMeta meta;
  WXMP_Result wr1;
  WXMP_Result wr2;

  WXMPMeta_SetProperty_Int64_1(reinterpret_cast<XMPMetaRef>(&meta), kSchemaNS, kPropName, 1LL,
                              /*options*/ 0, &wr1);
  EXPECT_EQ(wr1.errMessage, nullptr);

  WXMPMeta_SetProperty_Int64_1(reinterpret_cast<XMPMetaRef>(&meta), kSchemaNS, kPropName, -99LL,
                              /*options*/ 0, &wr2);
  EXPECT_EQ(wr2.errMessage, nullptr);

  XMP_Int64 gotValue = 0;
  XMP_OptionBits gotOptions = 0;
  EXPECT_TRUE(meta.GetProperty_Int64(kSchemaNS, kPropName, &gotValue, &gotOptions));
  EXPECT_EQ(gotValue, -99LL);
}

TEST_F(WXMPMeta_SetProperty_Int64_1_Test_2032, SupportsInt64BoundaryValues_2032) {
  XMPMeta meta;

  // Min / Max for signed 64-bit.
  const XMP_Int64 kMin = static_cast<XMP_Int64>(0x8000000000000000LL);
  const XMP_Int64 kMax = static_cast<XMP_Int64>(0x7FFFFFFFFFFFFFFFLL);

  {
    WXMP_Result wr;
    WXMPMeta_SetProperty_Int64_1(reinterpret_cast<XMPMetaRef>(&meta), kSchemaNS, "MinValue", kMin,
                                /*options*/ 0, &wr);
    EXPECT_EQ(wr.errMessage, nullptr);

    XMP_Int64 got = 0;
    XMP_OptionBits opt = 0;
    EXPECT_TRUE(meta.GetProperty_Int64(kSchemaNS, "MinValue", &got, &opt));
    EXPECT_EQ(got, kMin);
  }

  {
    WXMP_Result wr;
    WXMPMeta_SetProperty_Int64_1(reinterpret_cast<XMPMetaRef>(&meta), kSchemaNS, "MaxValue", kMax,
                                /*options*/ 0, &wr);
    EXPECT_EQ(wr.errMessage, nullptr);

    XMP_Int64 got = 0;
    XMP_OptionBits opt = 0;
    EXPECT_TRUE(meta.GetProperty_Int64(kSchemaNS, "MaxValue", &got, &opt));
    EXPECT_EQ(got, kMax);
  }
}

TEST_F(WXMPMeta_SetProperty_Int64_1_Test_2032, NullSchemaNamespaceSetsError_2032) {
  XMPMeta meta;
  WXMP_Result wr;

  WXMPMeta_SetProperty_Int64_1(reinterpret_cast<XMPMetaRef>(&meta), /*schemaNS*/ nullptr, kPropName,
                              5LL, /*options*/ 0, &wr);

  EXPECT_NE(wr.errMessage, nullptr);
  EXPECT_NE(*wr.errMessage, '\0');
}

TEST_F(WXMPMeta_SetProperty_Int64_1_Test_2032, EmptySchemaNamespaceSetsError_2032) {
  XMPMeta meta;
  WXMP_Result wr;

  WXMPMeta_SetProperty_Int64_1(reinterpret_cast<XMPMetaRef>(&meta), /*schemaNS*/ "", kPropName, 5LL,
                              /*options*/ 0, &wr);

  EXPECT_NE(wr.errMessage, nullptr);
  EXPECT_NE(*wr.errMessage, '\0');
}

TEST_F(WXMPMeta_SetProperty_Int64_1_Test_2032, NullPropertyNameSetsError_2032) {
  XMPMeta meta;
  WXMP_Result wr;

  WXMPMeta_SetProperty_Int64_1(reinterpret_cast<XMPMetaRef>(&meta), kSchemaNS, /*propName*/ nullptr,
                              5LL, /*options*/ 0, &wr);

  EXPECT_NE(wr.errMessage, nullptr);
  EXPECT_NE(*wr.errMessage, '\0');
}

TEST_F(WXMPMeta_SetProperty_Int64_1_Test_2032, EmptyPropertyNameSetsError_2032) {
  XMPMeta meta;
  WXMP_Result wr;

  WXMPMeta_SetProperty_Int64_1(reinterpret_cast<XMPMetaRef>(&meta), kSchemaNS, /*propName*/ "", 5LL,
                              /*options*/ 0, &wr);

  EXPECT_NE(wr.errMessage, nullptr);
  EXPECT_NE(*wr.errMessage, '\0');
}

TEST_F(WXMPMeta_SetProperty_Int64_1_Test_2032, NullMetaRefSetsError_2032) {
  WXMP_Result wr;

  WXMPMeta_SetProperty_Int64_1(/*xmpRef*/ nullptr, kSchemaNS, kPropName, 42LL, /*options*/ 0, &wr);

  EXPECT_NE(wr.errMessage, nullptr);
  EXPECT_NE(*wr.errMessage, '\0');
}

}  // namespace