// =================================================================================================
// TEST_ID 2043
// Unit tests for WXMPMeta_GetObjectOptions_1
// =================================================================================================

#include <gtest/gtest.h>

#include <cstdint>
#include <limits>

// From provided snippets / typical XMP C API conventions.
#include "client-glue/WXMP_Common.hpp"  // WXMP_Result
#include "xmpsdk/src/XMPMeta.hpp"       // XMPMeta (as provided path)
#include "XMP_Const.h"                 // XMP_OptionBits, XMP error IDs

// The wrapper under test (implemented in ./TestProjects/exiv2/xmpsdk/src/WXMPMeta.cpp).
// Declared here to avoid relying on non-provided headers for this specific wrapper.
extern "C" void WXMPMeta_GetObjectOptions_1(XMPMetaRef xmpRef, WXMP_Result* wResult);

namespace {

class WXMPMeta_GetObjectOptions_1_Test_2043 : public ::testing::Test {
protected:
  static XMPMetaRef ToRef(XMPMeta& meta) {
    // The wrapper converts an XMPMetaRef to an XMPMeta reference internally.
    // Passing the address of a real XMPMeta instance as an opaque ref is a standard pattern.
    return reinterpret_cast<XMPMetaRef>(&meta);
  }
};

}  // namespace

TEST_F(WXMPMeta_GetObjectOptions_1_Test_2043, ReturnsOptionsAfterSet_2043) {
  XMPMeta meta;
  const XMP_OptionBits options = static_cast<XMP_OptionBits>(0x12345678u);
  meta.SetObjectOptions(options);

  WXMP_Result r;
  r.int32Result = 0;

  EXPECT_NO_THROW(WXMPMeta_GetObjectOptions_1(ToRef(meta), &r));
  EXPECT_EQ(r.errMessage, nullptr);
  EXPECT_EQ(r.int32Result, static_cast<XMP_Uns32>(options));
}

TEST_F(WXMPMeta_GetObjectOptions_1_Test_2043, BoundaryOptionsZero_2043) {
  XMPMeta meta;
  const XMP_OptionBits options = static_cast<XMP_OptionBits>(0u);
  meta.SetObjectOptions(options);

  WXMP_Result r;
  r.int32Result = std::numeric_limits<XMP_Uns32>::max();  // sentinel

  EXPECT_NO_THROW(WXMPMeta_GetObjectOptions_1(ToRef(meta), &r));
  EXPECT_EQ(r.errMessage, nullptr);
  EXPECT_EQ(r.int32Result, static_cast<XMP_Uns32>(options));
}

TEST_F(WXMPMeta_GetObjectOptions_1_Test_2043, BoundaryOptionsAllBits_2043) {
  XMPMeta meta;
  const XMP_OptionBits options =
      static_cast<XMP_OptionBits>(std::numeric_limits<XMP_Uns32>::max());
  meta.SetObjectOptions(options);

  WXMP_Result r;
  r.int32Result = 0;

  EXPECT_NO_THROW(WXMPMeta_GetObjectOptions_1(ToRef(meta), &r));
  EXPECT_EQ(r.errMessage, nullptr);
  EXPECT_EQ(r.int32Result, static_cast<XMP_Uns32>(options));
}

TEST_F(WXMPMeta_GetObjectOptions_1_Test_2043, NullRefReportsError_2043) {
  WXMP_Result r;
  r.errMessage = nullptr;
  r.int32Result = 0xA5A5A5A5u;  // sentinel

  // The wrapper is expected to catch failures and report them through WXMP_Result.
  // We only assert observable behavior: no throw and an error message is provided.
  EXPECT_NO_THROW(WXMPMeta_GetObjectOptions_1(nullptr, &r));
  EXPECT_NE(r.errMessage, nullptr);
}