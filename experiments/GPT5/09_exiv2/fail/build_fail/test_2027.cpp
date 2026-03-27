// =================================================================================================
// Unit tests for WXMPMeta_GetProperty_Int64_1
// File: ./TestProjects/exiv2/xmpsdk/src/WXMPMeta.cpp
// TEST_ID: 2027
// =================================================================================================

#include <gtest/gtest.h>

#include <cstdint>
#include <cstring>

// These headers are expected to exist in the XMP SDK / Exiv2 vendor tree.
// If your include layout differs, adjust include paths accordingly.
#include "XMPMeta.hpp"               // XMPMeta
#include "XMP_Const.h"               // kXMPErr_* error ids (if exceptions surface)
#include "client-glue/WXMP_Common.hpp"  // WXMP_Result

// Some trees declare XMPMetaRef in a WXMP header; if not available via includes,
// it is typically a void* handle to an XMPMeta instance.
#ifndef XMPMetaRef
using XMPMetaRef = void*;
#endif

// Wrapper under test (defined in WXMPMeta.cpp).
extern "C" {
void WXMPMeta_GetProperty_Int64_1(XMPMetaRef xmpRef,
                                 XMP_StringPtr schemaNS,
                                 XMP_StringPtr propName,
                                 XMP_Int64* propValue,
                                 XMP_OptionBits* options,
                                 WXMP_Result* wResult);
}

namespace {

class WXMPMeta_GetProperty_Int64_1_Test_2027 : public ::testing::Test {
public:
  static void SetUpTestSuite() {
    // Initialize the toolkit once for this test suite.
    // If your environment auto-initializes, this should still be safe.
    XMPMeta::Initialize();
  }

  static void TearDownTestSuite() {
    XMPMeta::Terminate();
  }

protected:
  static void CallAndCaptureExceptions(const std::function<void()>& fn,
                                       bool* didThrow) {
    *didThrow = false;
    try {
      fn();
    } catch (...) {
      *didThrow = true;
    }
  }

  static XMPMetaRef ToRef(XMPMeta& meta) {
    return reinterpret_cast<XMPMetaRef>(&meta);
  }

  static constexpr XMP_StringPtr kSchema = "http://ns.adobe.com/xap/1.0/";
  static constexpr XMP_StringPtr kProp = "TestInt64";
};

constexpr XMP_StringPtr WXMPMeta_GetProperty_Int64_1_Test_2027::kSchema;
constexpr XMP_StringPtr WXMPMeta_GetProperty_Int64_1_Test_2027::kProp;

TEST_F(WXMPMeta_GetProperty_Int64_1_Test_2027, FoundReturnsTrueAndOutputsValue_2027) {
  XMPMeta meta;
  const XMP_Int64 expected = static_cast<XMP_Int64>(-9223372036854775807LL); // large negative (boundary-ish)
  meta.SetProperty_Int64(kSchema, kProp, expected, 0);

  WXMP_Result r;
  XMP_Int64 value = 0;
  XMP_OptionBits options = 0;

  WXMPMeta_GetProperty_Int64_1(ToRef(meta), kSchema, kProp, &value, &options, &r);

  EXPECT_EQ(r.errMessage, nullptr);
  EXPECT_EQ(r.int32Result, 1u);
  EXPECT_EQ(value, expected);
}

TEST_F(WXMPMeta_GetProperty_Int64_1_Test_2027, MissingPropertyReturnsFalse_2027) {
  XMPMeta meta;

  WXMP_Result r;
  XMP_Int64 value = 123;          // sentinel; behavior on miss is implementation-defined
  XMP_OptionBits options = 0xFFFF; // sentinel

  WXMPMeta_GetProperty_Int64_1(ToRef(meta), kSchema, kProp, &value, &options, &r);

  EXPECT_EQ(r.errMessage, nullptr);
  EXPECT_EQ(r.int32Result, 0u);
}

TEST_F(WXMPMeta_GetProperty_Int64_1_Test_2027, NullPropValuePointerDoesNotCrashAndReturnsFound_2027) {
  XMPMeta meta;
  meta.SetProperty_Int64(kSchema, kProp, static_cast<XMP_Int64>(42), 0);

  WXMP_Result r;
  XMP_OptionBits options = 0;

  // propValue is null: wrapper should internally substitute a sink pointer.
  WXMPMeta_GetProperty_Int64_1(ToRef(meta), kSchema, kProp, nullptr, &options, &r);

  EXPECT_EQ(r.errMessage, nullptr);
  EXPECT_EQ(r.int32Result, 1u);
}

TEST_F(WXMPMeta_GetProperty_Int64_1_Test_2027, NullOptionsPointerDoesNotCrashAndReturnsFound_2027) {
  XMPMeta meta;
  meta.SetProperty_Int64(kSchema, kProp, static_cast<XMP_Int64>(99), 0);

  WXMP_Result r;
  XMP_Int64 value = 0;

  // options is null: wrapper should internally substitute a sink pointer.
  WXMPMeta_GetProperty_Int64_1(ToRef(meta), kSchema, kProp, &value, nullptr, &r);

  EXPECT_EQ(r.errMessage, nullptr);
  EXPECT_EQ(r.int32Result, 1u);
  EXPECT_EQ(value, static_cast<XMP_Int64>(99));
}

TEST_F(WXMPMeta_GetProperty_Int64_1_Test_2027, EmptySchemaReportsErrorOrThrows_2027) {
  XMPMeta meta;

  WXMP_Result r;
  XMP_Int64 value = 0;
  XMP_OptionBits options = 0;

  bool didThrow = false;
  CallAndCaptureExceptions([&] {
    WXMPMeta_GetProperty_Int64_1(ToRef(meta), "", kProp, &value, &options, &r);
  }, &didThrow);

  // Wrapper either throws (if XMP_ENTER/EXIT does not swallow) or reports via errMessage.
  EXPECT_TRUE(didThrow || (r.errMessage != nullptr));
}

TEST_F(WXMPMeta_GetProperty_Int64_1_Test_2027, NullSchemaReportsErrorOrThrows_2027) {
  XMPMeta meta;

  WXMP_Result r;
  XMP_Int64 value = 0;
  XMP_OptionBits options = 0;

  bool didThrow = false;
  CallAndCaptureExceptions([&] {
    WXMPMeta_GetProperty_Int64_1(ToRef(meta), nullptr, kProp, &value, &options, &r);
  }, &didThrow);

  EXPECT_TRUE(didThrow || (r.errMessage != nullptr));
}

TEST_F(WXMPMeta_GetProperty_Int64_1_Test_2027, EmptyPropNameReportsErrorOrThrows_2027) {
  XMPMeta meta;

  WXMP_Result r;
  XMP_Int64 value = 0;
  XMP_OptionBits options = 0;

  bool didThrow = false;
  CallAndCaptureExceptions([&] {
    WXMPMeta_GetProperty_Int64_1(ToRef(meta), kSchema, "", &value, &options, &r);
  }, &didThrow);

  EXPECT_TRUE(didThrow || (r.errMessage != nullptr));
}

TEST_F(WXMPMeta_GetProperty_Int64_1_Test_2027, NullPropNameReportsErrorOrThrows_2027) {
  XMPMeta meta;

  WXMP_Result r;
  XMP_Int64 value = 0;
  XMP_OptionBits options = 0;

  bool didThrow = false;
  CallAndCaptureExceptions([&] {
    WXMPMeta_GetProperty_Int64_1(ToRef(meta), kSchema, nullptr, &value, &options, &r);
  }, &didThrow);

  EXPECT_TRUE(didThrow || (r.errMessage != nullptr));
}

}  // namespace