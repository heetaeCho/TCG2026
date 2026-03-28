// SPDX-License-Identifier: GPL-2.0-or-later
// Test file for: ./TestProjects/exiv2/src/makernote_int.cpp
//
// Focus: Exiv2::Internal::TiffMnCreator::create(uint16_t tag, IfdId group, IfdId mnGroup)
// Constraints: black-box tests via public/visible behavior only.

#include <gtest/gtest.h>

#include <cstdint>
#include <memory>
#include <string>

#include "makernote_int.hpp"

namespace {

using Exiv2::Internal::TiffMnCreator;

// Helper: pick an mnGroup value that is extremely unlikely to exist in the registry.
static Exiv2::IfdId VeryUnlikelyIfdId() {
  // Large positive value; avoids common small enum values.
  return static_cast<Exiv2::IfdId>(0x7fffffff);
}

static Exiv2::IfdId AnotherUnlikelyIfdId() {
  return static_cast<Exiv2::IfdId>(0x6fffffff);
}

class TiffMnCreatorTest_1432 : public ::testing::Test {
 protected:
  static std::unique_ptr<Exiv2::Internal::TiffIfdMakernote> CallCreate(uint16_t tag,
                                                                       Exiv2::IfdId group,
                                                                       Exiv2::IfdId mnGroup) {
    // Use the overload under test (member function exists; header also provides a static overload).
    // Prefer the static overload to avoid relying on constructibility details.
    return TiffMnCreator::create(tag, group, mnGroup);
  }
};

// The TEST_ID is 1432
TEST_F(TiffMnCreatorTest_1432, UnknownMnGroupReturnsNullptr_1432) {
  const auto tag = static_cast<uint16_t>(0x1234);
  const auto group = AnotherUnlikelyIfdId();
  const auto mnGroup = VeryUnlikelyIfdId();

  auto mn = CallCreate(tag, group, mnGroup);
  EXPECT_EQ(mn, nullptr);
}

// The TEST_ID is 1432
TEST_F(TiffMnCreatorTest_1432, UnknownMnGroupDoesNotWriteToStdout_1432) {
  const auto tag = static_cast<uint16_t>(0x1234);
  const auto group = AnotherUnlikelyIfdId();
  const auto mnGroup = VeryUnlikelyIfdId();

  testing::internal::CaptureStdout();
  auto mn = CallCreate(tag, group, mnGroup);
  const std::string out = testing::internal::GetCapturedStdout();

  EXPECT_EQ(mn, nullptr);
  EXPECT_TRUE(out.empty());
}

// The TEST_ID is 1432
TEST_F(TiffMnCreatorTest_1432, BoundaryTagZeroWithUnknownMnGroupReturnsNullptr_1432) {
  const auto tag = static_cast<uint16_t>(0);
  const auto group = AnotherUnlikelyIfdId();
  const auto mnGroup = VeryUnlikelyIfdId();

  auto mn = CallCreate(tag, group, mnGroup);
  EXPECT_EQ(mn, nullptr);
}

// The TEST_ID is 1432
TEST_F(TiffMnCreatorTest_1432, BoundaryTagMaxWithUnknownMnGroupReturnsNullptr_1432) {
  const auto tag = static_cast<uint16_t>(0xFFFF);
  const auto group = AnotherUnlikelyIfdId();
  const auto mnGroup = VeryUnlikelyIfdId();

  auto mn = CallCreate(tag, group, mnGroup);
  EXPECT_EQ(mn, nullptr);
}

// The TEST_ID is 1432
TEST_F(TiffMnCreatorTest_1432, RepeatedCallsWithUnknownMnGroupAreStable_1432) {
  const auto tag = static_cast<uint16_t>(0x00FF);
  const auto group = AnotherUnlikelyIfdId();
  const auto mnGroup = VeryUnlikelyIfdId();

  testing::internal::CaptureStdout();
  auto mn1 = CallCreate(tag, group, mnGroup);
  const std::string out1 = testing::internal::GetCapturedStdout();

  testing::internal::CaptureStdout();
  auto mn2 = CallCreate(tag, group, mnGroup);
  const std::string out2 = testing::internal::GetCapturedStdout();

  EXPECT_EQ(mn1, nullptr);
  EXPECT_EQ(mn2, nullptr);
  EXPECT_EQ(out1, out2);
  EXPECT_TRUE(out1.empty());
}

}  // namespace