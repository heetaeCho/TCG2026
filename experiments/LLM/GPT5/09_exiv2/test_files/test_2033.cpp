// ============================================================================
// TEST_ID: 2033
// Unit tests for WXMPMeta_SetProperty_Float_1
// ============================================================================

#include <gtest/gtest.h>

#include <cmath>
#include <cstdint>
#include <limits>
#include <string>

#include "XMPMeta.hpp"              // XMPMeta
#include "client-glue/WXMP_Common.hpp" // WXMP_Result, XMP_StringPtr, etc.

// The wrapper under test (implemented in ./TestProjects/exiv2/xmpsdk/src/WXMPMeta.cpp).
extern "C" {
void WXMPMeta_SetProperty_Float_1(XMPMetaRef xmpRef, XMP_StringPtr schemaNS, XMP_StringPtr propName,
                                 double propValue, XMP_OptionBits options, WXMP_Result* wResult);
} // extern "C"

namespace {

class WXMPMetaSetPropertyFloat1Test_2033 : public ::testing::Test {
public:
  static void SetUpTestSuite() {
    // XMP toolkit typically requires initialization.
    // If the build/environment does not require it, Initialize() should still be safe.
    ASSERT_TRUE(XMPMeta::Initialize());
  }

  static void TearDownTestSuite() { XMPMeta::Terminate(); }

protected:
  void SetUp() override { meta_ = new XMPMeta(); }
  void TearDown() override {
    delete meta_;
    meta_ = nullptr;
  }

  XMPMeta* meta_{nullptr};
};

static constexpr XMP_StringPtr kSchema = "http://ns.adobe.com/xap/1.0/";
static constexpr XMP_StringPtr kProp = "Rating"; // simple property name is valid with schemaNS

TEST_F(WXMPMetaSetPropertyFloat1Test_2033, NullSchemaNS_SetsError_2033) {
  WXMP_Result wr;
  WXMPMeta_SetProperty_Float_1(reinterpret_cast<XMPMetaRef>(meta_), nullptr, kProp, 1.0, 0, &wr);

  EXPECT_NE(wr.errMessage, nullptr);
}

TEST_F(WXMPMetaSetPropertyFloat1Test_2033, EmptySchemaNS_SetsError_2033) {
  WXMP_Result wr;
  WXMPMeta_SetProperty_Float_1(reinterpret_cast<XMPMetaRef>(meta_), "", kProp, 1.0, 0, &wr);

  EXPECT_NE(wr.errMessage, nullptr);
}

TEST_F(WXMPMetaSetPropertyFloat1Test_2033, NullPropName_SetsError_2033) {
  WXMP_Result wr;
  WXMPMeta_SetProperty_Float_1(reinterpret_cast<XMPMetaRef>(meta_), kSchema, nullptr, 1.0, 0, &wr);

  EXPECT_NE(wr.errMessage, nullptr);
}

TEST_F(WXMPMetaSetPropertyFloat1Test_2033, EmptyPropName_SetsError_2033) {
  WXMP_Result wr;
  WXMPMeta_SetProperty_Float_1(reinterpret_cast<XMPMetaRef>(meta_), kSchema, "", 1.0, 0, &wr);

  EXPECT_NE(wr.errMessage, nullptr);
}

TEST_F(WXMPMetaSetPropertyFloat1Test_2033, ValidInputs_SetsFloatProperty_2033) {
  WXMP_Result wr;

  const double expected = 3.141592653589793;
  WXMPMeta_SetProperty_Float_1(reinterpret_cast<XMPMetaRef>(meta_), kSchema, kProp, expected, 0, &wr);

  EXPECT_EQ(wr.errMessage, nullptr);

  double got = 0.0;
  XMP_OptionBits opts = 0;
  const bool ok = meta_->GetProperty_Float(kSchema, kProp, &got, &opts);
  EXPECT_TRUE(ok);
  EXPECT_NEAR(got, expected, 1e-12);
}

TEST_F(WXMPMetaSetPropertyFloat1Test_2033, BoundaryValues_ZeroAndNegative_SetsAndReadsBack_2033) {
  WXMP_Result wr;

  WXMPMeta_SetProperty_Float_1(reinterpret_cast<XMPMetaRef>(meta_), kSchema, kProp, 0.0, 0, &wr);
  EXPECT_EQ(wr.errMessage, nullptr);

  double got = 123.0;
  XMP_OptionBits opts = 0;
  EXPECT_TRUE(meta_->GetProperty_Float(kSchema, kProp, &got, &opts));
  EXPECT_DOUBLE_EQ(got, 0.0);

  WXMPMeta_SetProperty_Float_1(reinterpret_cast<XMPMetaRef>(meta_), kSchema, kProp, -42.25, 0, &wr);
  EXPECT_EQ(wr.errMessage, nullptr);

  got = 0.0;
  opts = 0;
  EXPECT_TRUE(meta_->GetProperty_Float(kSchema, kProp, &got, &opts));
  EXPECT_DOUBLE_EQ(got, -42.25);
}

TEST_F(WXMPMetaSetPropertyFloat1Test_2033, BoundaryValue_LargeMagnitude_SetsAndReadsBack_2033) {
  WXMP_Result wr;

  const double expected = 1.0e300;
  WXMPMeta_SetProperty_Float_1(reinterpret_cast<XMPMetaRef>(meta_), kSchema, "LargeFloat", expected, 0, &wr);

  EXPECT_EQ(wr.errMessage, nullptr);

  double got = 0.0;
  XMP_OptionBits opts = 0;
  EXPECT_TRUE(meta_->GetProperty_Float(kSchema, "LargeFloat", &got, &opts));
  EXPECT_DOUBLE_EQ(got, expected);
}

TEST_F(WXMPMetaSetPropertyFloat1Test_2033, LongPropName_SetsAndReadsBack_2033) {
  WXMP_Result wr;

  std::string longName(200, 'A'); // long but still a simple name
  // Ensure it starts with a legal name char (already 'A').
  WXMPMeta_SetProperty_Float_1(reinterpret_cast<XMPMetaRef>(meta_), kSchema, longName.c_str(), 12.5, 0, &wr);

  EXPECT_EQ(wr.errMessage, nullptr);

  double got = 0.0;
  XMP_OptionBits opts = 0;
  EXPECT_TRUE(meta_->GetProperty_Float(kSchema, longName.c_str(), &got, &opts));
  EXPECT_DOUBLE_EQ(got, 12.5);
}

TEST_F(WXMPMetaSetPropertyFloat1Test_2033, NonFiniteValue_NaN_ReportsErrorOrStores_2033) {
  WXMP_Result wr;

  const double nanVal = std::numeric_limits<double>::quiet_NaN();
  WXMPMeta_SetProperty_Float_1(reinterpret_cast<XMPMetaRef>(meta_), kSchema, "NaNFloat", nanVal, 0, &wr);

  // Observable behavior can vary by toolkit/platform. Require that the call is handled:
  // either an error is reported, or the value is stored and can be retrieved as NaN.
  if (wr.errMessage != nullptr) {
    SUCCEED();
    return;
  }

  double got = 0.0;
  XMP_OptionBits opts = 0;
  const bool ok = meta_->GetProperty_Float(kSchema, "NaNFloat", &got, &opts);
  ASSERT_TRUE(ok);
  EXPECT_TRUE(std::isnan(got));
}

TEST_F(WXMPMetaSetPropertyFloat1Test_2033, NonFiniteValue_Infinity_ReportsErrorOrStores_2033) {
  WXMP_Result wr;

  const double infVal = std::numeric_limits<double>::infinity();
  WXMPMeta_SetProperty_Float_1(reinterpret_cast<XMPMetaRef>(meta_), kSchema, "InfFloat", infVal, 0, &wr);

  // Observable behavior can vary by toolkit/platform. Require that the call is handled:
  // either an error is reported, or the value is stored and can be retrieved as infinity.
  if (wr.errMessage != nullptr) {
    SUCCEED();
    return;
  }

  double got = 0.0;
  XMP_OptionBits opts = 0;
  const bool ok = meta_->GetProperty_Float(kSchema, "InfFloat", &got, &opts);
  ASSERT_TRUE(ok);
  EXPECT_TRUE(std::isinf(got));
}

} // namespace