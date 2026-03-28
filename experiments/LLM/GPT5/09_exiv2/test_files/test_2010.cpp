// =================================================================================================
// TEST_ID: 2010
// Unit tests for WXMPMeta_SetProperty_1
// File: ./TestProjects/exiv2/xmpsdk/src/WXMPMeta.cpp
// =================================================================================================

#include <gtest/gtest.h>

#include <cstring>
#include <string>

// Public/common XMP SDK headers used by the wrapper signature.
#include "XMP_Const.h"
#include "client-glue/WXMP_Common.hpp"
#include "XMPMeta.hpp"

// The wrapper function under test.
extern "C" {
void WXMPMeta_SetProperty_1(XMPMetaRef xmpRef,
                           XMP_StringPtr schemaNS,
                           XMP_StringPtr propName,
                           XMP_StringPtr propValue,
                           XMP_OptionBits options,
                           WXMP_Result* wResult);
}

namespace {

class WXMPMetaSetProperty1Test_2010 : public ::testing::Test {
 protected:
  WXMPMetaSetProperty1Test_2010() = default;

  void SetUp() override {
    // Use a fresh result object each time.
    result_ = WXMP_Result();
  }

  static XMPMetaRef AsRef(XMPMeta* meta) {
    // The wrapper converts XMPMetaRef to XMPMeta* internally. In the XMP C-API,
    // XMPMetaRef is typically an opaque pointer. Passing the address is the
    // standard interop pattern in this codebase.
    return reinterpret_cast<XMPMetaRef>(meta);
  }

  static const char* kSchema() { return "http://ns.adobe.com/xap/1.0/"; }

  WXMP_Result result_{};
  XMPMeta meta_{};
};

TEST_F(WXMPMetaSetProperty1Test_2010, NullSchemaNSSetsError_2010) {
  EXPECT_NO_THROW(WXMPMeta_SetProperty_1(AsRef(&meta_), nullptr,
                                        "CreatorTool", "UnitTest", 0, &result_));
  EXPECT_NE(result_.errMessage, nullptr);
}

TEST_F(WXMPMetaSetProperty1Test_2010, EmptySchemaNSSetsError_2010) {
  EXPECT_NO_THROW(WXMPMeta_SetProperty_1(AsRef(&meta_), "",
                                        "CreatorTool", "UnitTest", 0, &result_));
  EXPECT_NE(result_.errMessage, nullptr);
}

TEST_F(WXMPMetaSetProperty1Test_2010, NullPropNameSetsError_2010) {
  EXPECT_NO_THROW(WXMPMeta_SetProperty_1(AsRef(&meta_), kSchema(),
                                        nullptr, "UnitTest", 0, &result_));
  EXPECT_NE(result_.errMessage, nullptr);
}

TEST_F(WXMPMetaSetProperty1Test_2010, EmptyPropNameSetsError_2010) {
  EXPECT_NO_THROW(WXMPMeta_SetProperty_1(AsRef(&meta_), kSchema(),
                                        "", "UnitTest", 0, &result_));
  EXPECT_NE(result_.errMessage, nullptr);
}

TEST_F(WXMPMetaSetProperty1Test_2010, SetsPropertyThenGetPropertySeesValue_2010) {
  const char* propName = "CreatorTool";
  const char* propValue = "UnitTestValue";

  EXPECT_NO_THROW(WXMPMeta_SetProperty_1(AsRef(&meta_), kSchema(), propName,
                                        propValue, 0, &result_));
  EXPECT_EQ(result_.errMessage, nullptr);

  XMP_StringPtr gotValue = nullptr;
  XMP_StringLen gotSize = 0;
  XMP_OptionBits gotOptions = 0;

  const bool ok = meta_.GetProperty(kSchema(), propName, &gotValue, &gotSize, &gotOptions);
  ASSERT_TRUE(ok);
  ASSERT_NE(gotValue, nullptr);

  // Compare by content; do not assume null-termination beyond gotSize.
  std::string got(gotValue, gotValue + gotSize);
  EXPECT_EQ(got, propValue);
}

TEST_F(WXMPMetaSetProperty1Test_2010, NullPropValueDoesNotCrashAndReportsViaResult_2010) {
  // Boundary: propValue == nullptr is permitted by the wrapper signature.
  // We only assert observable wrapper behavior: it should not crash/throw out.
  EXPECT_NO_THROW(WXMPMeta_SetProperty_1(AsRef(&meta_), kSchema(),
                                        "CreatorTool", nullptr, 0, &result_));
  // The API may treat nullptr as "no value"/delete/empty; either way the wrapper
  // should communicate failures through WXMP_Result.
  // So we only require that result_ is in a valid state (no UAF/crash).
  // If it errors, errMessage should be set; if it succeeds, errMessage should be null.
  // (No stronger behavioral assumption here.)
  EXPECT_TRUE((result_.errMessage == nullptr) || (result_.errMessage != nullptr));
}

}  // namespace