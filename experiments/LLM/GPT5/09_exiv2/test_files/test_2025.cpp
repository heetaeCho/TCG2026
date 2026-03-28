// ============================================================================
// Unit tests for WXMPMeta_GetProperty_Bool_1
// File: ./TestProjects/exiv2/xmpsdk/src/WXMPMeta.cpp
// TEST_ID: 2025
// ============================================================================

#include <gtest/gtest.h>

#include <cstring>

#include "XMP_Const.h"
#include "XMPMeta.hpp"
#include "client-glue/WXMP_Common.hpp"

// If the project provides a header that declares this wrapper and XMPMetaRef,
// it should be preferred. Many builds expose it via WXMPMeta.hpp.
// Keep this include if available in your tree; otherwise the extern declaration
// below is sufficient for these tests.
// #include "WXMPMeta.hpp"

// Fallback forward declarations (kept minimal; relies on existing project typedefs).
// If these types are already declared by included headers, these declarations
// should match and will not conflict.
#ifndef XMP_StringPtr
using XMP_StringPtr = const char*;
#endif

#ifndef XMPMetaRef
using XMPMetaRef = void*;
#endif

extern "C" {
void WXMPMeta_GetProperty_Bool_1(XMPMetaRef xmpRef,
                                XMP_StringPtr schemaNS,
                                XMP_StringPtr propName,
                                XMP_Bool* propValue,
                                XMP_OptionBits* options,
                                WXMP_Result* wResult);
}  // extern "C"

namespace {

class WXMPMeta_GetProperty_Bool_1_Test_2025 : public ::testing::Test {
protected:
  static void SetUpTestSuite() {
    // Initialize the XMP toolkit if required by this SDK.
    // Initialize() returns bool; avoid asserting a specific value in case the
    // harness already initialized it elsewhere, but calling it should be safe.
    (void)XMPMeta::Initialize();
  }

  static void TearDownTestSuite() {
    // Terminate should be safe even if the harness manages lifecycle elsewhere.
    // If your environment centralizes init/term, you can remove these calls.
    XMPMeta::Terminate();
  }

  void SetUp() override {
    wResult_ = WXMP_Result();
    // Ensure namespace registration exists for our test schema/prefix.
    // RegisterNamespace may throw on duplicates depending on SDK behavior; so
    // we call it in a try-like way by just attempting once per test via a guard.
    EnsureTestNamespaceRegistered();
  }

  static void EnsureTestNamespaceRegistered() {
    static bool registered = false;
    if (registered) return;

    // Use a custom schema; prefix is used in property name "tst:Flag".
    // Some SDKs require registration before SetProperty_*.
    XMPMeta::RegisterNamespace(kTestSchemaNS, "tst");
    registered = true;
  }

  XMPMeta meta_;
  WXMP_Result wResult_{};

  static constexpr XMP_StringPtr kTestSchemaNS = "http://ns.example.com/xmp/test/1.0/";
  static constexpr XMP_StringPtr kBoolPropName = "tst:Flag";
};

TEST_F(WXMPMeta_GetProperty_Bool_1_Test_2025, GetsExistingBoolPropertyTrue_2025) {
  meta_.SetProperty_Bool(kTestSchemaNS, kBoolPropName, true, /*options*/ 0);

  XMP_Bool outValue = false;
  XMP_OptionBits outOptions = 0;

  WXMPMeta_GetProperty_Bool_1(reinterpret_cast<XMPMetaRef>(&meta_),
                             kTestSchemaNS,
                             kBoolPropName,
                             &outValue,
                             &outOptions,
                             &wResult_);

  EXPECT_EQ(wResult_.errMessage, nullptr);
  EXPECT_EQ(wResult_.int32Result, 1U);  // found
  EXPECT_TRUE(outValue != 0);
}

TEST_F(WXMPMeta_GetProperty_Bool_1_Test_2025, GetsExistingBoolPropertyFalse_2025) {
  meta_.SetProperty_Bool(kTestSchemaNS, kBoolPropName, false, /*options*/ 0);

  XMP_Bool outValue = true;  // start opposite to ensure it can change
  XMP_OptionBits outOptions = 0;

  WXMPMeta_GetProperty_Bool_1(reinterpret_cast<XMPMetaRef>(&meta_),
                             kTestSchemaNS,
                             kBoolPropName,
                             &outValue,
                             &outOptions,
                             &wResult_);

  EXPECT_EQ(wResult_.errMessage, nullptr);
  EXPECT_EQ(wResult_.int32Result, 1U);  // found
  EXPECT_FALSE(outValue != 0);
}

TEST_F(WXMPMeta_GetProperty_Bool_1_Test_2025, ReturnsNotFoundForMissingProperty_2025) {
  // Do not set the property.

  XMP_Bool outValue = false;
  XMP_OptionBits outOptions = 0;

  WXMPMeta_GetProperty_Bool_1(reinterpret_cast<XMPMetaRef>(&meta_),
                             kTestSchemaNS,
                             "tst:DoesNotExist",
                             &outValue,
                             &outOptions,
                             &wResult_);

  EXPECT_EQ(wResult_.errMessage, nullptr);
  EXPECT_EQ(wResult_.int32Result, 0U);  // not found
  // Do not assert outValue/outOptions when not found; behavior is SDK-dependent.
}

TEST_F(WXMPMeta_GetProperty_Bool_1_Test_2025, AllowsNullPropValuePointer_2025) {
  meta_.SetProperty_Bool(kTestSchemaNS, kBoolPropName, true, /*options*/ 0);

  XMP_OptionBits outOptions = 0;

  // propValue == nullptr should be tolerated (no crash) and still report found.
  WXMPMeta_GetProperty_Bool_1(reinterpret_cast<XMPMetaRef>(&meta_),
                             kTestSchemaNS,
                             kBoolPropName,
                             /*propValue*/ nullptr,
                             &outOptions,
                             &wResult_);

  EXPECT_EQ(wResult_.errMessage, nullptr);
  EXPECT_EQ(wResult_.int32Result, 1U);
}

TEST_F(WXMPMeta_GetProperty_Bool_1_Test_2025, AllowsNullOptionsPointer_2025) {
  meta_.SetProperty_Bool(kTestSchemaNS, kBoolPropName, false, /*options*/ 0);

  XMP_Bool outValue = true;

  // options == nullptr should be tolerated (no crash) and still report found.
  WXMPMeta_GetProperty_Bool_1(reinterpret_cast<XMPMetaRef>(&meta_),
                             kTestSchemaNS,
                             kBoolPropName,
                             &outValue,
                             /*options*/ nullptr,
                             &wResult_);

  EXPECT_EQ(wResult_.errMessage, nullptr);
  EXPECT_EQ(wResult_.int32Result, 1U);
  EXPECT_FALSE(outValue != 0);
}

TEST_F(WXMPMeta_GetProperty_Bool_1_Test_2025, ErrorOnNullSchemaNamespace_2025) {
  meta_.SetProperty_Bool(kTestSchemaNS, kBoolPropName, true, /*options*/ 0);

  XMP_Bool outValue = false;
  XMP_OptionBits outOptions = 0;

  WXMPMeta_GetProperty_Bool_1(reinterpret_cast<XMPMetaRef>(&meta_),
                             /*schemaNS*/ nullptr,
                             kBoolPropName,
                             &outValue,
                             &outOptions,
                             &wResult_);

  EXPECT_NE(wResult_.errMessage, nullptr);
}

TEST_F(WXMPMeta_GetProperty_Bool_1_Test_2025, ErrorOnEmptySchemaNamespace_2025) {
  meta_.SetProperty_Bool(kTestSchemaNS, kBoolPropName, true, /*options*/ 0);

  XMP_Bool outValue = false;
  XMP_OptionBits outOptions = 0;

  WXMPMeta_GetProperty_Bool_1(reinterpret_cast<XMPMetaRef>(&meta_),
                             /*schemaNS*/ "",
                             kBoolPropName,
                             &outValue,
                             &outOptions,
                             &wResult_);

  EXPECT_NE(wResult_.errMessage, nullptr);
}

TEST_F(WXMPMeta_GetProperty_Bool_1_Test_2025, ErrorOnNullPropertyName_2025) {
  meta_.SetProperty_Bool(kTestSchemaNS, kBoolPropName, true, /*options*/ 0);

  XMP_Bool outValue = false;
  XMP_OptionBits outOptions = 0;

  WXMPMeta_GetProperty_Bool_1(reinterpret_cast<XMPMetaRef>(&meta_),
                             kTestSchemaNS,
                             /*propName*/ nullptr,
                             &outValue,
                             &outOptions,
                             &wResult_);

  EXPECT_NE(wResult_.errMessage, nullptr);
}

TEST_F(WXMPMeta_GetProperty_Bool_1_Test_2025, ErrorOnEmptyPropertyName_2025) {
  meta_.SetProperty_Bool(kTestSchemaNS, kBoolPropName, true, /*options*/ 0);

  XMP_Bool outValue = false;
  XMP_OptionBits outOptions = 0;

  WXMPMeta_GetProperty_Bool_1(reinterpret_cast<XMPMetaRef>(&meta_),
                             kTestSchemaNS,
                             /*propName*/ "",
                             &outValue,
                             &outOptions,
                             &wResult_);

  EXPECT_NE(wResult_.errMessage, nullptr);
}

}  // namespace