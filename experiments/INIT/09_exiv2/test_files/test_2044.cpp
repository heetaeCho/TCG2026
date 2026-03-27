// SPDX-License-Identifier: GPL-2.0-or-later
//
// File: ./TestProjects/exiv2/xmpsdk/test/WXMPMeta_SetObjectOptions_1_test.cpp
//
// Unit tests for:
//   void WXMPMeta_SetObjectOptions_1 ( XMPMetaRef xmpRef, XMP_OptionBits options, WXMP_Result * wResult )
//
// Constraints respected:
// - Treat implementation as a black box.
// - Verify only via observable behavior through public interface (XMPMeta::GetObjectOptions).
// - No private/internal state access.

#include <gtest/gtest.h>

#include <cstdint>
#include <memory>

// XMP SDK headers (paths based on provided snippets).
#include "TestProjects/exiv2/xmpsdk/src/XMPMeta.hpp"
#include "client-glue/WXMP_Common.hpp"
#include "XMP_Const.h"

// If XMPMetaRef isn't visible via included headers, treat it as an opaque handle.
// Many XMP SDK builds typedef XMPMetaRef as void* in public glue headers.
// We defensively define it only if not already defined.
#ifndef XMPMetaRef
using XMPMetaRef = void*;
#endif

extern "C" {
// Wrapper under test (defined in WXMPMeta.cpp).
void WXMPMeta_SetObjectOptions_1(XMPMetaRef xmpRef, XMP_OptionBits options, WXMP_Result* wResult);
}  // extern "C"

namespace {

class WXMPMetaSetObjectOptions1Test_2044 : public ::testing::Test {
 protected:
  void SetUp() override {
    meta_ = std::make_unique<XMPMeta>();
    xmpRef_ = reinterpret_cast<XMPMetaRef>(meta_.get());
    // Sanity: ensure we can read object options via the public interface.
    (void)meta_->GetObjectOptions();
  }

  void TearDown() override {
    // xmpRef_ is non-owning; meta_ owns the object.
    xmpRef_ = nullptr;
    meta_.reset();
  }

  std::unique_ptr<XMPMeta> meta_;
  XMPMetaRef xmpRef_{nullptr};
};

TEST_F(WXMPMetaSetObjectOptions1Test_2044, SetsOptionsToZero_2044) {
  WXMP_Result wr;
  // First set to a non-zero value via C++ API so we can observe a change.
  const XMP_OptionBits nonZero = static_cast<XMP_OptionBits>(0x10);
  meta_->SetObjectOptions(nonZero);
  ASSERT_EQ(meta_->GetObjectOptions(), nonZero);

  // Now set to 0 via the wrapper.
  WXMPMeta_SetObjectOptions_1(xmpRef_, static_cast<XMP_OptionBits>(0), &wr);

  // Observable behavior: GetObjectOptions reflects the new value.
  EXPECT_EQ(meta_->GetObjectOptions(), static_cast<XMP_OptionBits>(0));

  // On success, errMessage should remain unset (observable via WXMP_Result).
  EXPECT_EQ(wr.errMessage, nullptr);
}

TEST_F(WXMPMetaSetObjectOptions1Test_2044, SetsOptionsToNonZero_2044) {
  WXMP_Result wr;

  // Start from 0 to make the transition clear.
  meta_->SetObjectOptions(static_cast<XMP_OptionBits>(0));
  ASSERT_EQ(meta_->GetObjectOptions(), static_cast<XMP_OptionBits>(0));

  const XMP_OptionBits desired = static_cast<XMP_OptionBits>(0x1);
  WXMPMeta_SetObjectOptions_1(xmpRef_, desired, &wr);

  EXPECT_EQ(meta_->GetObjectOptions(), desired);
  EXPECT_EQ(wr.errMessage, nullptr);
}

TEST_F(WXMPMetaSetObjectOptions1Test_2044, OverwritesPreviousOptions_2044) {
  WXMP_Result wr;

  const XMP_OptionBits first = static_cast<XMP_OptionBits>(0x2);
  const XMP_OptionBits second = static_cast<XMP_OptionBits>(0x20);

  WXMPMeta_SetObjectOptions_1(xmpRef_, first, &wr);
  ASSERT_EQ(wr.errMessage, nullptr);
  ASSERT_EQ(meta_->GetObjectOptions(), first);

  WXMPMeta_SetObjectOptions_1(xmpRef_, second, &wr);
  EXPECT_EQ(wr.errMessage, nullptr);
  EXPECT_EQ(meta_->GetObjectOptions(), second);
}

TEST_F(WXMPMetaSetObjectOptions1Test_2044, CanRoundTripBetweenTwoValues_2044) {
  WXMP_Result wr;

  const XMP_OptionBits a = static_cast<XMP_OptionBits>(0);
  const XMP_OptionBits b = static_cast<XMP_OptionBits>(0x40);

  WXMPMeta_SetObjectOptions_1(xmpRef_, a, &wr);
  ASSERT_EQ(wr.errMessage, nullptr);
  ASSERT_EQ(meta_->GetObjectOptions(), a);

  WXMPMeta_SetObjectOptions_1(xmpRef_, b, &wr);
  ASSERT_EQ(wr.errMessage, nullptr);
  ASSERT_EQ(meta_->GetObjectOptions(), b);

  WXMPMeta_SetObjectOptions_1(xmpRef_, a, &wr);
  EXPECT_EQ(wr.errMessage, nullptr);
  EXPECT_EQ(meta_->GetObjectOptions(), a);
}

}  // namespace