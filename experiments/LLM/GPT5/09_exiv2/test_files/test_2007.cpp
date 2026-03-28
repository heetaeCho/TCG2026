// File: test_WXMPMeta_GetArrayItem_1_2007.cpp
//
// Unit tests for WXMPMeta_GetArrayItem_1
// Constraints:
// - Treat implementation as black box
// - Use only public/observable behavior
// - No private state access

#include <gtest/gtest.h>

#include <cstring>
#include <string>

// XMP SDK / Exiv2 XMP glue headers (expected to exist in the codebase include paths).
#include "XMP_Const.h"
#include "XMPMeta.hpp"
#include "client-glue/WXMP_Common.hpp"

// The wrapper under test is implemented in WXMPMeta.cpp. Prefer including its public header if present.
// If your build exposes a different header name, adjust this include accordingly.
#if __has_include("client-glue/WXMPMeta.hpp")
#include "client-glue/WXMPMeta.hpp"
#elif __has_include("WXMPMeta.hpp")
#include "WXMPMeta.hpp"
#else
// Fallback: declare the symbol so the test can compile as long as the implementation is linked.
extern "C" {
void WXMPMeta_GetArrayItem_1(XMPMetaRef xmpRef, XMP_StringPtr schemaNS, XMP_StringPtr arrayName,
                            XMP_Index itemIndex, XMP_StringPtr* itemValue, XMP_StringLen* valueSize,
                            XMP_OptionBits* options, WXMP_Result* wResult);
}
#endif

namespace {

class WXMPMetaGetArrayItem1Test_2007 : public ::testing::Test {
protected:
  static void SetUpTestSuite() {
    // Safe to call multiple times if the SDK guards internally; tests should not assume more.
    XMPMeta::Initialize();

    // Register a private test namespace to avoid collisions.
    // If already registered, behavior should remain stable.
    try {
      XMPMeta::RegisterNamespace(kTestSchemaNS, "tst");
    } catch (...) {
      // If registration throws in some environments (e.g., already registered), proceed.
    }
  }

  static void TearDownTestSuite() {
    try {
      XMPMeta::Terminate();
    } catch (...) {
      // Best-effort cleanup; no assumptions about termination behavior.
    }
  }

  static constexpr XMP_StringPtr kTestSchemaNS = "http://example.com/ns/test/1.0/";
  static constexpr XMP_StringPtr kTestArrayName = "tst:ArrayProp";

  static XMPMetaRef ToRef(XMPMeta& meta) {
    // XMPMetaRef is typically a void* in the glue layer; reinterpret_cast is the least assumptive.
    return reinterpret_cast<XMPMetaRef>(&meta);
  }

  static bool CallAndDetectThrow(XMPMetaRef ref, XMP_StringPtr schemaNS, XMP_StringPtr arrayName,
                                 XMP_Index itemIndex, XMP_StringPtr* itemValue,
                                 XMP_StringLen* valueSize, XMP_OptionBits* options,
                                 WXMP_Result* wResult) {
    bool threw = false;
    try {
      WXMPMeta_GetArrayItem_1(ref, schemaNS, arrayName, itemIndex, itemValue, valueSize, options,
                             wResult);
    } catch (...) {
      threw = true;
    }
    return threw;
  }
};

TEST_F(WXMPMetaGetArrayItem1Test_2007, ReturnsTrueAndOutputsItemValue_2007) {
  XMPMeta meta;

  // Create an array and add one item.
  // Use arrayOptions that indicate "array"; exact form is not asserted here.
  meta.AppendArrayItem(kTestSchemaNS, kTestArrayName, kXMP_PropValueIsArray, "one", 0);

  WXMP_Result wr;
  XMP_StringPtr itemValue = nullptr;
  XMP_StringLen valueSize = 0;
  XMP_OptionBits options = 0;

  const bool threw =
      CallAndDetectThrow(ToRef(meta), kTestSchemaNS, kTestArrayName, 1, &itemValue, &valueSize,
                         &options, &wr);

  ASSERT_FALSE(threw);
  EXPECT_EQ(wr.int32Result, 1u);

  ASSERT_NE(itemValue, nullptr);
  EXPECT_GT(valueSize, 0u);

  // The wrapper forwards through to XMPMeta::GetArrayItem; verify returned string matches.
  EXPECT_EQ(std::string(itemValue, itemValue + valueSize), "one");
}

TEST_F(WXMPMetaGetArrayItem1Test_2007, NotFoundReturnsFalse_2007) {
  XMPMeta meta;
  meta.AppendArrayItem(kTestSchemaNS, kTestArrayName, kXMP_PropValueIsArray, "one", 0);

  WXMP_Result wr;
  XMP_StringPtr itemValue = nullptr;
  XMP_StringLen valueSize = 0;
  XMP_OptionBits options = 0;

  const bool threw =
      CallAndDetectThrow(ToRef(meta), kTestSchemaNS, kTestArrayName, 2, &itemValue, &valueSize,
                         &options, &wr);

  // Some implementations might throw for bad index; accept either "false" or an error signal.
  if (threw || wr.errMessage != nullptr) {
    SUCCEED();
  } else {
    EXPECT_EQ(wr.int32Result, 0u);
  }
}

TEST_F(WXMPMetaGetArrayItem1Test_2007, NullOutputPointersAreAllowed_2007) {
  XMPMeta meta;
  meta.AppendArrayItem(kTestSchemaNS, kTestArrayName, kXMP_PropValueIsArray, "one", 0);

  WXMP_Result wr;

  // itemValue/valueSize/options are allowed to be null per wrapper code (it substitutes globals).
  const bool threw = CallAndDetectThrow(ToRef(meta), kTestSchemaNS, kTestArrayName, 1,
                                        /*itemValue*/ nullptr,
                                        /*valueSize*/ nullptr,
                                        /*options*/ nullptr, &wr);

  ASSERT_FALSE(threw);
  EXPECT_EQ(wr.int32Result, 1u);
}

TEST_F(WXMPMetaGetArrayItem1Test_2007, EmptySchemaNamespaceSignalsError_2007) {
  XMPMeta meta;

  WXMP_Result wr;
  XMP_StringPtr itemValue = nullptr;
  XMP_StringLen valueSize = 0;
  XMP_OptionBits options = 0;

  const char empty[] = "";

  const bool threw =
      CallAndDetectThrow(ToRef(meta), empty, kTestArrayName, 1, &itemValue, &valueSize, &options,
                         &wr);

  // Wrapper explicitly checks for empty schemaNS and calls XMP_Throw.
  EXPECT_TRUE(threw || (wr.errMessage != nullptr));
}

TEST_F(WXMPMetaGetArrayItem1Test_2007, NullSchemaNamespaceSignalsError_2007) {
  XMPMeta meta;

  WXMP_Result wr;
  XMP_StringPtr itemValue = nullptr;
  XMP_StringLen valueSize = 0;
  XMP_OptionBits options = 0;

  const bool threw = CallAndDetectThrow(ToRef(meta), /*schemaNS*/ nullptr, kTestArrayName, 1,
                                        &itemValue, &valueSize, &options, &wr);

  EXPECT_TRUE(threw || (wr.errMessage != nullptr));
}

TEST_F(WXMPMetaGetArrayItem1Test_2007, EmptyArrayNameSignalsError_2007) {
  XMPMeta meta;

  WXMP_Result wr;
  XMP_StringPtr itemValue = nullptr;
  XMP_StringLen valueSize = 0;
  XMP_OptionBits options = 0;

  const char empty[] = "";

  const bool threw =
      CallAndDetectThrow(ToRef(meta), kTestSchemaNS, empty, 1, &itemValue, &valueSize, &options,
                         &wr);

  // Wrapper explicitly checks for empty arrayName and calls XMP_Throw.
  EXPECT_TRUE(threw || (wr.errMessage != nullptr));
}

TEST_F(WXMPMetaGetArrayItem1Test_2007, NullArrayNameSignalsError_2007) {
  XMPMeta meta;

  WXMP_Result wr;
  XMP_StringPtr itemValue = nullptr;
  XMP_StringLen valueSize = 0;
  XMP_OptionBits options = 0;

  const bool threw = CallAndDetectThrow(ToRef(meta), kTestSchemaNS, /*arrayName*/ nullptr, 1,
                                        &itemValue, &valueSize, &options, &wr);

  EXPECT_TRUE(threw || (wr.errMessage != nullptr));
}

TEST_F(WXMPMetaGetArrayItem1Test_2007, IndexZeroIsErrorOrNotFound_2007) {
  XMPMeta meta;
  meta.AppendArrayItem(kTestSchemaNS, kTestArrayName, kXMP_PropValueIsArray, "one", 0);

  WXMP_Result wr;
  XMP_StringPtr itemValue = nullptr;
  XMP_StringLen valueSize = 0;
  XMP_OptionBits options = 0;

  const bool threw =
      CallAndDetectThrow(ToRef(meta), kTestSchemaNS, kTestArrayName, 0, &itemValue, &valueSize,
                         &options, &wr);

  // XMP array indices are typically 1-based; accept either a thrown error or "not found".
  if (threw || wr.errMessage != nullptr) {
    SUCCEED();
  } else {
    EXPECT_EQ(wr.int32Result, 0u);
  }
}

}  // namespace