// =================================================================================================
// TEST_ID 2030
// Unit tests for WXMPMeta_SetProperty_Bool_1
// File: test_wxmpmeta_setproperty_bool_1_2030.cpp
// =================================================================================================

#include <gtest/gtest.h>

#include <cstring>
#include <memory>
#include <string>

// These headers are expected to exist in the xmpsdk tree used by Exiv2.
// Adjust include paths if your build uses different include conventions.
#include "XMP_Const.h"
#include "XMPMeta.hpp"
#include "client-glue/WXMP_Common.hpp"

// The wrapper under test is implemented in WXMPMeta.cpp; it is commonly declared in a public header.
// If your project exposes it from a different header, include that header instead.
extern "C" {
void WXMPMeta_SetProperty_Bool_1(XMPMetaRef xmpRef, XMP_StringPtr schemaNS, XMP_StringPtr propName,
                                XMP_Bool propValue, XMP_OptionBits options, WXMP_Result* wResult);
}

namespace {

class WXMPMetaSetPropertyBool1Test_2030 : public ::testing::Test {
public:
  static void SetUpTestSuite() {
    // XMPMeta typically requires global init/term. We do not infer internals; we only use public API.
    ASSERT_TRUE(XMPMeta::Initialize());
  }

  static void TearDownTestSuite() { XMPMeta::Terminate(); }

protected:
  // Commonly used schema for XMP basic properties.
  static constexpr XMP_StringPtr kXmpSchema = "http://ns.adobe.com/xap/1.0/";

  // Helper to create a meta object and return the opaque ref used by wrapper.
  static XMPMetaRef MakeRef(XMPMeta* meta) {
    // The wrapper uses WtoXMPMeta_Ptr(xmpRef) internally; in typical SDK builds, XMPMetaRef is an
    // opaque pointer to XMPMeta. We treat this as a black box and only use the public/declared type.
    return reinterpret_cast<XMPMetaRef>(meta);
  }
};

TEST_F(WXMPMetaSetPropertyBool1Test_2030, SetsBoolPropertyTrue_2030) {
  XMPMeta meta;
  WXMP_Result wr;

  // Use a simple property name (no prefix); schema namespace is provided separately.
  const char* propName = "HasVisibleWatermark";

  WXMPMeta_SetProperty_Bool_1(MakeRef(&meta), kXmpSchema, propName, static_cast<XMP_Bool>(true), 0, &wr);

  // Observable behavior via public interface: property should exist and read back as true.
  bool value = false;
  XMP_OptionBits opts = 0;
  const bool ok = meta.GetProperty_Bool(kXmpSchema, propName, &value, &opts);
  EXPECT_TRUE(ok);
  EXPECT_TRUE(value);

  // For success, wrapper should not report an error message.
  EXPECT_TRUE(wr.errMessage == nullptr);
}

TEST_F(WXMPMetaSetPropertyBool1Test_2030, SetsBoolPropertyFalse_2030) {
  XMPMeta meta;
  WXMP_Result wr;

  const char* propName = "HasVisibleWatermark";

  WXMPMeta_SetProperty_Bool_1(MakeRef(&meta), kXmpSchema, propName, static_cast<XMP_Bool>(false), 0, &wr);

  bool value = true;  // start opposite
  XMP_OptionBits opts = 0;
  const bool ok = meta.GetProperty_Bool(kXmpSchema, propName, &value, &opts);
  EXPECT_TRUE(ok);
  EXPECT_FALSE(value);

  EXPECT_TRUE(wr.errMessage == nullptr);
}

TEST_F(WXMPMetaSetPropertyBool1Test_2030, OverwritesExistingValue_2030) {
  XMPMeta meta;
  WXMP_Result wr1;
  WXMP_Result wr2;

  const char* propName = "HasVisibleWatermark";

  WXMPMeta_SetProperty_Bool_1(MakeRef(&meta), kXmpSchema, propName, static_cast<XMP_Bool>(true), 0, &wr1);
  EXPECT_TRUE(wr1.errMessage == nullptr);

  WXMPMeta_SetProperty_Bool_1(MakeRef(&meta), kXmpSchema, propName, static_cast<XMP_Bool>(false), 0, &wr2);
  EXPECT_TRUE(wr2.errMessage == nullptr);

  bool value = true;
  XMP_OptionBits opts = 0;
  const bool ok = meta.GetProperty_Bool(kXmpSchema, propName, &value, &opts);
  EXPECT_TRUE(ok);
  EXPECT_FALSE(value);
}

TEST_F(WXMPMetaSetPropertyBool1Test_2030, OptionsAreAcceptedAndPropertyStillReadable_2030) {
  XMPMeta meta;
  WXMP_Result wr;

  const char* propName = "HasVisibleWatermark";

  // Boundary-ish: pass a non-zero options value without assuming what it means.
  // The observable requirement here is simply "call succeeds and value is set/readable".
  const XMP_OptionBits someOptions = static_cast<XMP_OptionBits>(0x1);

  WXMPMeta_SetProperty_Bool_1(MakeRef(&meta), kXmpSchema, propName, static_cast<XMP_Bool>(true), someOptions, &wr);

  bool value = false;
  XMP_OptionBits opts = 0;
  const bool ok = meta.GetProperty_Bool(kXmpSchema, propName, &value, &opts);
  EXPECT_TRUE(ok);
  EXPECT_TRUE(value);

  EXPECT_TRUE(wr.errMessage == nullptr);
}

TEST_F(WXMPMetaSetPropertyBool1Test_2030, NullSchemaNSReportsError_2030) {
  XMPMeta meta;
  WXMP_Result wr;

  const char* propName = "HasVisibleWatermark";

  WXMPMeta_SetProperty_Bool_1(MakeRef(&meta), nullptr, propName, static_cast<XMP_Bool>(true), 0, &wr);

  // Observable error reporting through WXMP_Result.
  ASSERT_TRUE(wr.errMessage != nullptr);

  // If the wrapper preserves the thrown message, it should mention the schema namespace.
  // We only check a weak condition to avoid overfitting to exact formatting.
  std::string msg(wr.errMessage);
  EXPECT_NE(msg.find("schema"), std::string::npos);
}

TEST_F(WXMPMetaSetPropertyBool1Test_2030, EmptySchemaNSReportsError_2030) {
  XMPMeta meta;
  WXMP_Result wr;

  const char* propName = "HasVisibleWatermark";
  const char* empty = "";

  WXMPMeta_SetProperty_Bool_1(MakeRef(&meta), empty, propName, static_cast<XMP_Bool>(true), 0, &wr);

  ASSERT_TRUE(wr.errMessage != nullptr);
  std::string msg(wr.errMessage);
  EXPECT_NE(msg.find("schema"), std::string::npos);
}

TEST_F(WXMPMetaSetPropertyBool1Test_2030, NullPropNameReportsError_2030) {
  XMPMeta meta;
  WXMP_Result wr;

  WXMPMeta_SetProperty_Bool_1(MakeRef(&meta), kXmpSchema, nullptr, static_cast<XMP_Bool>(true), 0, &wr);

  ASSERT_TRUE(wr.errMessage != nullptr);

  std::string msg(wr.errMessage);
  EXPECT_NE(msg.find("property"), std::string::npos);
}

TEST_F(WXMPMetaSetPropertyBool1Test_2030, EmptyPropNameReportsError_2030) {
  XMPMeta meta;
  WXMP_Result wr;

  const char* empty = "";

  WXMPMeta_SetProperty_Bool_1(MakeRef(&meta), kXmpSchema, empty, static_cast<XMP_Bool>(true), 0, &wr);

  ASSERT_TRUE(wr.errMessage != nullptr);

  std::string msg(wr.errMessage);
  EXPECT_NE(msg.find("property"), std::string::npos);
}

}  // namespace