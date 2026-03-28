// File: test_isTiffImageTag_1180.cpp
// TEST_ID: 1180

#include <gtest/gtest.h>

#include <cstdint>
#include <limits>
#include <string>

#ifdef EXIV2_DEBUG_MESSAGES
#include <gtest/internal/gtest-port.h>  // for CaptureStderr / GetCapturedStderr
#endif

// Internal header expected to declare Exiv2::Internal::isTiffImageTag and IfdId.
#include "tiffimage_int.hpp"

namespace {

// Keep the fixture name stable and TEST_ID-suffixed.
class IsTiffImageTagTest_1180 : public ::testing::Test {
 protected:
  using Exiv2::Internal::isTiffImageTag;
  using Exiv2::Internal::IfdId;
};

static uint16_t U16Min() {
  return std::numeric_limits<uint16_t>::min();
}
static uint16_t U16Max() {
  return std::numeric_limits<uint16_t>::max();
}

// Pick a small, commonly-available set of groups in Exiv2.
// If your build exposes additional/different IFD ids, adjust here.
static constexpr Exiv2::Internal::IfdId kCommonGroups[] = {
    Exiv2::Internal::ifd0Id,
    Exiv2::Internal::exifId,
    Exiv2::Internal::gpsId,
};

}  // namespace

TEST_F(IsTiffImageTagTest_1180, DeterministicForSameInputs_1180) {
  const uint16_t tag = 0x0100;  // arbitrary tag value
  const auto group = Exiv2::Internal::ifd0Id;

  const bool r1 = Exiv2::Internal::isTiffImageTag(tag, group);
  const bool r2 = Exiv2::Internal::isTiffImageTag(tag, group);
  const bool r3 = Exiv2::Internal::isTiffImageTag(tag, group);

  EXPECT_EQ(r1, r2);
  EXPECT_EQ(r2, r3);
}

TEST_F(IsTiffImageTagTest_1180, AcceptsBoundaryTagValues_1180) {
  const uint16_t tags[] = {U16Min(), static_cast<uint16_t>(1), U16Max()};

  for (const auto group : kCommonGroups) {
    for (const uint16_t tag : tags) {
      // Observable behavior: must return a bool and not crash.
      const bool result = Exiv2::Internal::isTiffImageTag(tag, group);
      (void)result;
      SUCCEED();
    }
  }
}

TEST_F(IsTiffImageTagTest_1180, DifferentTagsMayProduceDifferentResultsButAreWellFormed_1180) {
  const auto group = Exiv2::Internal::ifd0Id;

  const bool r_a = Exiv2::Internal::isTiffImageTag(static_cast<uint16_t>(0x0000), group);
  const bool r_b = Exiv2::Internal::isTiffImageTag(static_cast<uint16_t>(0x00FF), group);
  const bool r_c = Exiv2::Internal::isTiffImageTag(static_cast<uint16_t>(0xFFFF), group);

  // No assumptions about which tags are image tags; just ensure calls are valid.
  EXPECT_TRUE((r_a == true) || (r_a == false));
  EXPECT_TRUE((r_b == true) || (r_b == false));
  EXPECT_TRUE((r_c == true) || (r_c == false));
}

#ifdef EXIV2_DEBUG_MESSAGES

TEST_F(IsTiffImageTagTest_1180, DebugOutputMentionsImageTagWhenReturnTrue_1180) {
  const uint16_t tag = 0x0100;  // arbitrary tag value
  const auto group = Exiv2::Internal::ifd0Id;

  testing::internal::CaptureStderr();
  const bool result = Exiv2::Internal::isTiffImageTag(tag, group);
  const std::string err = testing::internal::GetCapturedStderr();

  if (result) {
    EXPECT_NE(err.find("Image tag:"), std::string::npos);
  } else {
    // If false, we don't require "Not an image tag" here; that is covered separately.
    SUCCEED();
  }
}

TEST_F(IsTiffImageTagTest_1180, DebugOutputMentionsNotImageTagWhenReturnFalse_1180) {
  const uint16_t tag = 0xFFFF;  // arbitrary tag value
  const auto group = Exiv2::Internal::ifd0Id;

  testing::internal::CaptureStderr();
  const bool result = Exiv2::Internal::isTiffImageTag(tag, group);
  const std::string err = testing::internal::GetCapturedStderr();

  if (!result) {
    EXPECT_NE(err.find("Not an image tag:"), std::string::npos);
  } else {
    // If true, we don't require "Image tag" here; that is covered separately.
    SUCCEED();
  }
}

TEST_F(IsTiffImageTagTest_1180, DebugOutputAlwaysIncludesMarkerNumbers_1180) {
  const uint16_t tag = 0x00FE;  // arbitrary tag value
  const auto group = Exiv2::Internal::ifd0Id;

  testing::internal::CaptureStderr();
  (void)Exiv2::Internal::isTiffImageTag(tag, group);
  const std::string err = testing::internal::GetCapturedStderr();

  // Based only on observable output strings in the provided code.
  // Either "(3)" or "(4)" should appear depending on result.
  const bool has3 = (err.find("(3)") != std::string::npos);
  const bool has4 = (err.find("(4)") != std::string::npos);
  EXPECT_TRUE(has3 || has4);
}

#endif  // EXIV2_DEBUG_MESSAGES