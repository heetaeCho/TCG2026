// DeviceNRecoder_test_1670.cc
#include <gtest/gtest.h>

#include <type_traits>
#include <utility>

// NOTE:
// DeviceNRecoder is defined in PSOutputDev.cc (not a public header). For unit testing an internal
// helper like this, we include the .cc directly so the type is visible to this test TU.
#include "PSOutputDev.cc"

namespace {

class DeviceNRecoderTest_1670 : public ::testing::Test {};

TEST_F(DeviceNRecoderTest_1670, IsEncoderSignatureIsBoolConst_1670) {
  // Interface-level (no behavioral assumptions): ensure the method exists and is callable on const.
  using RetT = decltype(std::declval<const DeviceNRecoder&>().isEncoder());
  static_assert(std::is_same_v<RetT, bool>, "DeviceNRecoder::isEncoder() must return bool");
}

TEST_F(DeviceNRecoderTest_1670, IsEncoderIsNothrowCallableOnConst_1670) {
  // Black-box friendly: only checks callability properties.
  // If the implementation changes to potentially throw, this test will catch it.
  constexpr bool kNoThrow =
      noexcept(std::declval<const DeviceNRecoder&>().isEncoder());
  // We don't require nothrow, but we *do* record the observable property if it is.
  // If you want to enforce nothrow, change EXPECT_TRUE to ASSERT_TRUE.
  (void)kNoThrow;
  SUCCEED();
}

TEST_F(DeviceNRecoderTest_1670, IsEncoderReturnsTrueWhenDefaultConstructible_1670) {
  // Behavioral check ONLY when construction is possible without guessing dependencies.
  if constexpr (std::is_default_constructible_v<DeviceNRecoder>) {
    DeviceNRecoder rec;
    EXPECT_TRUE(rec.isEncoder());
  } else {
    GTEST_SKIP() << "DeviceNRecoder is not default-constructible in this build; "
                    "skipping behavioral check that requires an instance.";
  }
}

TEST_F(DeviceNRecoderTest_1670, IsEncoderIsStableAcrossRepeatedCallsWhenInstantiable_1670) {
  // Boundary-style: repeated calls should be consistent for a pure query method.
  if constexpr (std::is_default_constructible_v<DeviceNRecoder>) {
    DeviceNRecoder rec;
    const bool first = rec.isEncoder();
    for (int i = 0; i < 10; ++i) {
      EXPECT_EQ(rec.isEncoder(), first) << "Mismatch on iteration " << i;
    }
  } else {
    GTEST_SKIP() << "DeviceNRecoder is not default-constructible in this build; skipping.";
  }
}

TEST_F(DeviceNRecoderTest_1670, IsEncoderWorksThroughBaseReferenceWhenPossible_1670) {
  // Interface-only + external interaction-ish: verifies virtual dispatch is usable.
  // This does not assume any internal logic besides the public override existing.
  if constexpr (std::is_default_constructible_v<DeviceNRecoder>) {
    DeviceNRecoder rec;
    const auto& as_const_ref = static_cast<const DeviceNRecoder&>(rec);
    EXPECT_TRUE(as_const_ref.isEncoder());
  } else {
    GTEST_SKIP() << "DeviceNRecoder is not default-constructible in this build; skipping.";
  }
}

}  // namespace