// ============================================================================
// unit_test_newSigmaMn2_1529.cpp
// Tests for Exiv2::Internal::newSigmaMn2 (makernote_int.cpp)
// ============================================================================

#include <gtest/gtest.h>

#include <cstdint>
#include <limits>
#include <memory>

// Exiv2 internals
#include "makernote_int.hpp"  // Expected to declare Exiv2::Internal::newSigmaMn2

namespace {

class NewSigmaMn2Test_1529 : public ::testing::Test {};

TEST_F(NewSigmaMn2Test_1529, ReturnsNonNullForTypicalValues_1529) {
  const uint16_t tag = 1;
  const auto group = static_cast<Exiv2::IfdId>(0);
  const auto mnGroup = static_cast<Exiv2::IfdId>(0);

  auto mn = Exiv2::Internal::newSigmaMn2(tag, group, mnGroup);
  ASSERT_NE(mn, nullptr);
}

TEST_F(NewSigmaMn2Test_1529, ReturnsDistinctObjectsOnMultipleCalls_1529) {
  const uint16_t tag = 0x1234;
  const auto group = static_cast<Exiv2::IfdId>(1);
  const auto mnGroup = static_cast<Exiv2::IfdId>(2);

  auto a = Exiv2::Internal::newSigmaMn2(tag, group, mnGroup);
  auto b = Exiv2::Internal::newSigmaMn2(tag, group, mnGroup);

  ASSERT_NE(a, nullptr);
  ASSERT_NE(b, nullptr);
  EXPECT_NE(a.get(), b.get());
}

TEST_F(NewSigmaMn2Test_1529, SupportsBoundaryTagValues_1529) {
  const auto group = static_cast<Exiv2::IfdId>(0);
  const auto mnGroup = static_cast<Exiv2::IfdId>(0);

  {
    const uint16_t tagMin = std::numeric_limits<uint16_t>::min();
    auto mnMin = Exiv2::Internal::newSigmaMn2(tagMin, group, mnGroup);
    ASSERT_NE(mnMin, nullptr);
  }
  {
    const uint16_t tagMax = std::numeric_limits<uint16_t>::max();
    auto mnMax = Exiv2::Internal::newSigmaMn2(tagMax, group, mnGroup);
    ASSERT_NE(mnMax, nullptr);
  }
}

TEST_F(NewSigmaMn2Test_1529, AcceptsVariousIfdIdBitPatterns_1529) {
  const uint16_t tag = 0x0001;

  const auto ifd0 = static_cast<Exiv2::IfdId>(0);
  const auto ifd1 = static_cast<Exiv2::IfdId>(1);
  const auto ifdLarge = static_cast<Exiv2::IfdId>(0x7FFF);

  auto a = Exiv2::Internal::newSigmaMn2(tag, ifd0, ifd1);
  auto b = Exiv2::Internal::newSigmaMn2(tag, ifd1, ifdLarge);
  auto c = Exiv2::Internal::newSigmaMn2(tag, ifdLarge, ifd0);

  ASSERT_NE(a, nullptr);
  ASSERT_NE(b, nullptr);
  ASSERT_NE(c, nullptr);
}

TEST_F(NewSigmaMn2Test_1529, UniquePtrCanBeMoved_1529) {
  const uint16_t tag = 0x00FF;
  const auto group = static_cast<Exiv2::IfdId>(0);
  const auto mnGroup = static_cast<Exiv2::IfdId>(0);

  auto mn = Exiv2::Internal::newSigmaMn2(tag, group, mnGroup);
  ASSERT_NE(mn, nullptr);

  auto* raw = mn.get();
  std::unique_ptr<Exiv2::Internal::TiffIfdMakernote> moved = std::move(mn);

  EXPECT_EQ(mn.get(), nullptr);
  ASSERT_NE(moved, nullptr);
  EXPECT_EQ(moved.get(), raw);
}

}  // namespace