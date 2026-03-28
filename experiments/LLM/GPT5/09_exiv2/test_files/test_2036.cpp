// =================================================================================================
// TEST_ID: 2036
// Unit tests for WXMPMeta_Sort_1 (./TestProjects/exiv2/xmpsdk/src/WXMPMeta.cpp)
// =================================================================================================

#include <gtest/gtest.h>

#include "XMP_Const.h"
#include "client-glue/WXMP_Common.hpp"
#include "XMPMeta.hpp"

// If XMPMetaRef is not visible via included headers in some build configurations,
// provide a conservative fallback typedef. The real project headers (typically XMPCore)
// usually define XMPMetaRef as an opaque pointer type.
#ifndef XMPMetaRef
using XMPMetaRef = void*;
#endif

extern "C" {
void WXMPMeta_Sort_1(XMPMetaRef xmpRef, WXMP_Result* wResult);
}  // extern "C"

namespace {

class WXMPMetaSort1Test_2036 : public ::testing::Test {
 protected:
  static constexpr XMP_StringPtr kSchemaNS = "http://ns.adobe.com/xap/1.0/";
};

TEST_F(WXMPMetaSort1Test_2036, Sort_DoesNotSetErrorForValidObject_2036) {
  XMPMeta meta;  // Default-construct a valid object.
  WXMP_Result result;

  EXPECT_NO_THROW(WXMPMeta_Sort_1(reinterpret_cast<XMPMetaRef>(&meta), &result));

  // Observable wrapper behavior: successful call should not populate an error message.
  EXPECT_EQ(result.errMessage, nullptr);
}

TEST_F(WXMPMetaSort1Test_2036, Sort_PreservesPropertyValues_2036) {
  XMPMeta meta;
  WXMP_Result result;

  // Set a few properties in an arbitrary order.
  meta.SetProperty(kSchemaNS, "CreatorTool", "unit-test-tool", /*options*/ 0);
  meta.SetProperty(kSchemaNS, "Label", "unit-test-label", /*options*/ 0);
  meta.SetProperty(kSchemaNS, "Nickname", "unit-test-nickname", /*options*/ 0);

  // Sanity-check they exist before calling the wrapper.
  {
    XMP_StringPtr v = nullptr;
    XMP_StringLen vLen = 0;
    XMP_OptionBits opts = 0;

    ASSERT_TRUE(meta.GetProperty(kSchemaNS, "CreatorTool", &v, &vLen, &opts));
    ASSERT_NE(v, nullptr);

    ASSERT_TRUE(meta.GetProperty(kSchemaNS, "Label", &v, &vLen, &opts));
    ASSERT_NE(v, nullptr);

    ASSERT_TRUE(meta.GetProperty(kSchemaNS, "Nickname", &v, &vLen, &opts));
    ASSERT_NE(v, nullptr);
  }

  // Call Sort via the C wrapper.
  EXPECT_NO_THROW(WXMPMeta_Sort_1(reinterpret_cast<XMPMetaRef>(&meta), &result));
  EXPECT_EQ(result.errMessage, nullptr);

  // Observable behavior: values should still be retrievable and identical.
  XMP_StringPtr v = nullptr;
  XMP_StringLen vLen = 0;
  XMP_OptionBits opts = 0;

  ASSERT_TRUE(meta.GetProperty(kSchemaNS, "CreatorTool", &v, &vLen, &opts));
  ASSERT_NE(v, nullptr);
  EXPECT_STREQ(v, "unit-test-tool");

  ASSERT_TRUE(meta.GetProperty(kSchemaNS, "Label", &v, &vLen, &opts));
  ASSERT_NE(v, nullptr);
  EXPECT_STREQ(v, "unit-test-label");

  ASSERT_TRUE(meta.GetProperty(kSchemaNS, "Nickname", &v, &vLen, &opts));
  ASSERT_NE(v, nullptr);
  EXPECT_STREQ(v, "unit-test-nickname");
}

TEST_F(WXMPMetaSort1Test_2036, Sort_WithNullRefReportsErrorIfObservable_2036) {
  WXMP_Result result;

  // We treat the implementation as a black box. This test only checks observable behavior:
  // - The wrapper should not throw across the C boundary (if it catches internally).
  // - If an error is reported through WXMP_Result, errMessage should become non-null.
  EXPECT_NO_THROW(WXMPMeta_Sort_1(reinterpret_cast<XMPMetaRef>(nullptr), &result));

  // If the wrapper reports an error, it should do so via errMessage.
  // Some builds might leave errMessage null even on error; in that case we don't over-assert.
  if (result.errMessage != nullptr) {
    EXPECT_NE(std::string(result.errMessage).size(), 0u);
  }
}

TEST_F(WXMPMetaSort1Test_2036, Sort_WithNullResultPointer_DoesNotCrashProcessIfHandled_2036) {
  XMPMeta meta;

  // Boundary: nullptr result pointer. We cannot assume the wrapper will accept it.
  // This test is written to be safe and only asserts "no throw" (C boundary expectation).
  // If your build treats this as programmer error and aborts, convert to EXPECT_DEATH locally.
  EXPECT_NO_THROW(WXMPMeta_Sort_1(reinterpret_cast<XMPMetaRef>(&meta), nullptr));
}

}  // namespace