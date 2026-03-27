// SPDX-License-Identifier: GPL-2.0-or-later
// Tests for WXMPMeta_UnlockObject_1
//
// File under test:
//   ./TestProjects/exiv2/xmpsdk/src/WXMPMeta.cpp
//
// Black-box tests: we only validate observable behavior through the public interface.

#include <gtest/gtest.h>

#include <cstdint>
#include <limits>

#include "TestProjects/exiv2/xmpsdk/src/XMPMeta.hpp"

// The C API uses XMPMetaRef (typically a void* handle). We declare only what we need here
// to call the wrapper under test, without re-implementing any internal logic.
using XMPMetaRef = void*;
using XMP_OptionBits = std::uint32_t;

// Wrapper under test (defined in WXMPMeta.cpp).
extern "C" void WXMPMeta_UnlockObject_1(XMPMetaRef xmpRef, XMP_OptionBits options);

namespace {

class WXMPMetaUnlockObject1Test_2040 : public ::testing::Test {
protected:
  static void SetUpTestSuite() {
    // Ensure toolkit is initialized for XMPMeta usage.
    // If Initialize returns false in some configurations, the tests relying on XMPMeta
    // would be invalid. We assert here to make failures explicit.
    ASSERT_TRUE(XMPMeta::Initialize());
  }

  static void TearDownTestSuite() { XMPMeta::Terminate(); }

  static XMPMetaRef ToRef(XMPMeta& meta) {
    // Treat as an opaque handle; do not assume internal layout.
    return reinterpret_cast<XMPMetaRef>(&meta);
  }
};

TEST_F(WXMPMetaUnlockObject1Test_2040, ValidRefZeroOptions_NoThrow_2040) {
  XMPMeta meta;
  EXPECT_NO_THROW(WXMPMeta_UnlockObject_1(ToRef(meta), 0u));
}

TEST_F(WXMPMetaUnlockObject1Test_2040, ValidRefMaxOptions_NoThrow_2040) {
  XMPMeta meta;
  constexpr XMP_OptionBits kMax = std::numeric_limits<XMP_OptionBits>::max();
  EXPECT_NO_THROW(WXMPMeta_UnlockObject_1(ToRef(meta), kMax));
}

TEST_F(WXMPMetaUnlockObject1Test_2040, NullRef_Throws_2040) {
  // Observable error case: passing a null reference should not succeed.
  // We assert that an exception is thrown (exact type is an implementation detail).
  EXPECT_ANY_THROW(WXMPMeta_UnlockObject_1(nullptr, 0u));
}

TEST_F(WXMPMetaUnlockObject1Test_2040, UnlockDoesNotEraseExistingProperty_2040) {
  XMPMeta meta;

  const char* kSchema = "http://ns.adobe.com/xap/1.0/";
  const char* kProp = "CreatorTool";
  const char* kValue = "unit-test";

  ASSERT_NO_THROW(meta.SetProperty(kSchema, kProp, kValue, 0u));

  XMP_StringPtr gotValue = nullptr;
  XMP_StringLen gotSize = 0;
  XMP_OptionBits gotOpts = 0;

  ASSERT_TRUE(meta.GetProperty(kSchema, kProp, &gotValue, &gotSize, &gotOpts));
  ASSERT_NE(gotValue, nullptr);
  ASSERT_GT(gotSize, 0u);

  EXPECT_NO_THROW(WXMPMeta_UnlockObject_1(ToRef(meta), 0u));

  XMP_StringPtr gotValue2 = nullptr;
  XMP_StringLen gotSize2 = 0;
  XMP_OptionBits gotOpts2 = 0;

  ASSERT_TRUE(meta.GetProperty(kSchema, kProp, &gotValue2, &gotSize2, &gotOpts2));
  ASSERT_NE(gotValue2, nullptr);
  ASSERT_GT(gotSize2, 0u);

  // The exact storage/lifetime of returned strings is an implementation detail,
  // so we only verify that the property still exists and has a non-empty value.
}

TEST_F(WXMPMetaUnlockObject1Test_2040, UnlockDoesNotChangeObjectOptions_2040) {
  XMPMeta meta;

  const XMP_OptionBits before = meta.GetObjectOptions();
  EXPECT_NO_THROW(WXMPMeta_UnlockObject_1(ToRef(meta), 0u));
  const XMP_OptionBits after = meta.GetObjectOptions();

  EXPECT_EQ(before, after);
}

}  // namespace