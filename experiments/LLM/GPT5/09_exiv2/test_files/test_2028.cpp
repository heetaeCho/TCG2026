// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_wxmpmeta_getproperty_float_1_2028.cpp
//
// Unit tests for:
//   void WXMPMeta_GetProperty_Float_1(...)
//
// Constraints honored:
// - Treat implementation as a black box (no internal logic assumptions).
// - Use only public/observable behavior (return via WXMP_Result, output params, exceptions if any).
// - No private state access.

#include <gtest/gtest.h>

#include <cmath>
#include <cstdint>
#include <cstring>
#include <string>

#include "client-glue/WXMP_Common.hpp"          // WXMP_Result
#include "TestProjects/exiv2/xmpsdk/src/XMPMeta.hpp" // XMPMeta

// If your build provides a proper header declaring this wrapper, include it instead.
// Otherwise, declare the symbol here to compile the tests.
extern "C" {

// These are typically defined by the XMP SDK. Use the common, codebase-typical types.
using XMPMetaRef = void*;
using XMP_StringPtr = const char*;
using XMP_OptionBits = std::uint32_t;

void WXMPMeta_GetProperty_Float_1(XMPMetaRef xmpRef,
                                 XMP_StringPtr schemaNS,
                                 XMP_StringPtr propName,
                                 double* propValue,
                                 XMP_OptionBits* options,
                                 WXMP_Result* wResult);

} // extern "C"

// Some SDKs expose XMP_Error as a C++ exception type. It is shown in the prompt.
class XMP_Error; // forward (real definition should come from the SDK headers if thrown)

// ----------------------------

namespace {

struct CallOutcome {
  bool threw = false;
  std::string what;
};

template <typename Fn>
CallOutcome CallCatchingAny(Fn&& fn) {
  CallOutcome out;
  try {
    fn();
  } catch (const std::exception& e) {
    out.threw = true;
    out.what = e.what();
  } catch (...) {
    out.threw = true;
    out.what = "non-std exception";
  }
  return out;
}

} // namespace

class WXMPMeta_GetProperty_Float_1_Test_2028 : public ::testing::Test {
public:
  static void SetUpTestSuite() {
    // Safe even if already initialized by other tests; black-box friendly.
    (void)XMPMeta::Initialize();
  }
  static void TearDownTestSuite() {
    // Safe even if other suites rely on it; in many codebases this is OK at process end.
    XMPMeta::Terminate();
  }

protected:
  static XMPMetaRef ToRef(XMPMeta& meta) { return reinterpret_cast<XMPMetaRef>(&meta); }
};

// TEST_ID 2028
TEST_F(WXMPMeta_GetProperty_Float_1_Test_2028, GetExistingFloatProperty_ReturnsFoundAndValue_2028) {
  XMPMeta meta;
  const char* kSchema = "http://ns.adobe.com/xap/1.0/";
  const char* kProp = "Rating";

  const double kSetValue = 3.25;
  meta.SetProperty_Float(kSchema, kProp, kSetValue, 0);

  double outValue = 0.0;
  XMP_OptionBits outOptions = 0;
  WXMP_Result wResult;
  ASSERT_EQ(wResult.errMessage, nullptr);

  const auto outcome = CallCatchingAny([&] {
    WXMPMeta_GetProperty_Float_1(ToRef(meta), kSchema, kProp, &outValue, &outOptions, &wResult);
  });

  EXPECT_FALSE(outcome.threw) << outcome.what;
  EXPECT_EQ(wResult.errMessage, nullptr);

  // Observable behavior: found flag returned via int32Result.
  EXPECT_NE(wResult.int32Result, 0u);

  // Observable behavior: output float is the stored value.
  EXPECT_DOUBLE_EQ(outValue, kSetValue);
}

// TEST_ID 2028
TEST_F(WXMPMeta_GetProperty_Float_1_Test_2028, GetMissingFloatProperty_ReturnsNotFound_2028) {
  XMPMeta meta;
  const char* kSchema = "http://ns.adobe.com/xap/1.0/";
  const char* kProp = "DoesNotExist";

  double outValue = 12345.678; // sentinel; do not assume it is preserved
  XMP_OptionBits outOptions = 0xFFFFFFFFu; // sentinel; do not assume it is preserved
  WXMP_Result wResult;

  const auto outcome = CallCatchingAny([&] {
    WXMPMeta_GetProperty_Float_1(ToRef(meta), kSchema, kProp, &outValue, &outOptions, &wResult);
  });

  EXPECT_FALSE(outcome.threw) << outcome.what;
  EXPECT_EQ(wResult.errMessage, nullptr);

  // Only assert the documented/observable "found" outcome.
  EXPECT_EQ(wResult.int32Result, 0u);
}

// TEST_ID 2028
TEST_F(WXMPMeta_GetProperty_Float_1_Test_2028, NullPropValuePointer_DoesNotCrashAndReturnsFound_2028) {
  XMPMeta meta;
  const char* kSchema = "http://ns.adobe.com/xap/1.0/";
  const char* kProp = "Rating";

  meta.SetProperty_Float(kSchema, kProp, 1.0, 0);

  XMP_OptionBits outOptions = 0;
  WXMP_Result wResult;

  // propValue == nullptr should be handled by wrapper (uses internal voidDouble).
  const auto outcome = CallCatchingAny([&] {
    WXMPMeta_GetProperty_Float_1(ToRef(meta), kSchema, kProp, nullptr, &outOptions, &wResult);
  });

  EXPECT_FALSE(outcome.threw) << outcome.what;
  EXPECT_EQ(wResult.errMessage, nullptr);
  EXPECT_NE(wResult.int32Result, 0u);
}

// TEST_ID 2028
TEST_F(WXMPMeta_GetProperty_Float_1_Test_2028, NullOptionsPointer_DoesNotCrashAndReturnsFound_2028) {
  XMPMeta meta;
  const char* kSchema = "http://ns.adobe.com/xap/1.0/";
  const char* kProp = "Rating";

  meta.SetProperty_Float(kSchema, kProp, 2.0, 0);

  double outValue = 0.0;
  WXMP_Result wResult;

  // options == nullptr should be handled by wrapper (uses internal voidOptionBits).
  const auto outcome = CallCatchingAny([&] {
    WXMPMeta_GetProperty_Float_1(ToRef(meta), kSchema, kProp, &outValue, nullptr, &wResult);
  });

  EXPECT_FALSE(outcome.threw) << outcome.what;
  EXPECT_EQ(wResult.errMessage, nullptr);
  EXPECT_NE(wResult.int32Result, 0u);
  EXPECT_DOUBLE_EQ(outValue, 2.0);
}

// TEST_ID 2028
TEST_F(WXMPMeta_GetProperty_Float_1_Test_2028, NullSchemaNS_ReportsErrorOrThrows_2028) {
  XMPMeta meta;
  const char* kProp = "Rating";

  double outValue = 0.0;
  XMP_OptionBits outOptions = 0;
  WXMP_Result wResult;

  const auto outcome = CallCatchingAny([&] {
    WXMPMeta_GetProperty_Float_1(ToRef(meta), nullptr, kProp, &outValue, &outOptions, &wResult);
  });

  // Wrapper may either throw or capture error into wResult.errMessage depending on macro behavior.
  if (outcome.threw) {
    SUCCEED() << "Exception observed as acceptable error signaling: " << outcome.what;
  } else {
    EXPECT_NE(wResult.errMessage, nullptr);
  }
}

// TEST_ID 2028
TEST_F(WXMPMeta_GetProperty_Float_1_Test_2028, EmptyPropertyName_ReportsErrorOrThrows_2028) {
  XMPMeta meta;
  const char* kSchema = "http://ns.adobe.com/xap/1.0/";

  double outValue = 0.0;
  XMP_OptionBits outOptions = 0;
  WXMP_Result wResult;

  const auto outcome = CallCatchingAny([&] {
    WXMPMeta_GetProperty_Float_1(ToRef(meta), kSchema, "", &outValue, &outOptions, &wResult);
  });

  // Same rationale: either exception or error message is observable.
  if (outcome.threw) {
    SUCCEED() << "Exception observed as acceptable error signaling: " << outcome.what;
  } else {
    EXPECT_NE(wResult.errMessage, nullptr);
  }
}