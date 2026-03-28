// File: test_makernote_int_newSony2Mn2_1532.cpp

#include <gtest/gtest.h>

#include <cstdint>
#include <limits>
#include <memory>

#include "makernote_int.hpp"  // Expected to declare Exiv2::Internal::newSony2Mn2 and IfdId

namespace {

class NewSony2Mn2Test_1532 : public ::testing::Test {};

TEST_F(NewSony2Mn2Test_1532, ReturnsNonNullForTypicalInputs_1532) {
  using Exiv2::Internal::newSony2Mn2;

  const uint16_t tag = 0x2000;
  const auto group = static_cast<Exiv2::IfdId>(0);
  const auto mnGroup = static_cast<Exiv2::IfdId>(1);

  std::unique_ptr<Exiv2::Internal::TiffIfdMakernote> mn = newSony2Mn2(tag, group, mnGroup);
  ASSERT_NE(mn, nullptr);
}

TEST_F(NewSony2Mn2Test_1532, ReturnsDistinctInstancesOnMultipleCalls_1532) {
  using Exiv2::Internal::newSony2Mn2;

  const uint16_t tag = 0x1234;
  const auto group = static_cast<Exiv2::IfdId>(0);
  const auto mnGroup = static_cast<Exiv2::IfdId>(0);

  auto mn1 = newSony2Mn2(tag, group, mnGroup);
  auto mn2 = newSony2Mn2(tag, group, mnGroup);

  ASSERT_NE(mn1, nullptr);
  ASSERT_NE(mn2, nullptr);
  EXPECT_NE(mn1.get(), mn2.get());  // Each factory call should yield a different object instance.
}

TEST_F(NewSony2Mn2Test_1532, AcceptsBoundaryTagValues_1532) {
  using Exiv2::Internal::newSony2Mn2;

  const auto group = static_cast<Exiv2::IfdId>(0);
  const auto mnGroup = static_cast<Exiv2::IfdId>(0);

  {
    const uint16_t tag_min = std::numeric_limits<uint16_t>::min();
    auto mn = newSony2Mn2(tag_min, group, mnGroup);
    ASSERT_NE(mn, nullptr);
  }

  {
    const uint16_t tag_max = std::numeric_limits<uint16_t>::max();
    auto mn = newSony2Mn2(tag_max, group, mnGroup);
    ASSERT_NE(mn, nullptr);
  }
}

TEST_F(NewSony2Mn2Test_1532, AcceptsDifferentGroupValues_1532) {
  using Exiv2::Internal::newSony2Mn2;

  const uint16_t tag = 0x00AA;

  // Use casts to avoid relying on specific IfdId enumerator names.
  const auto group0 = static_cast<Exiv2::IfdId>(0);
  const auto group1 = static_cast<Exiv2::IfdId>(1);
  const auto group2 = static_cast<Exiv2::IfdId>(2);

  auto mn_a = newSony2Mn2(tag, group0, group1);
  auto mn_b = newSony2Mn2(tag, group1, group2);
  auto mn_c = newSony2Mn2(tag, group2, group0);

  ASSERT_NE(mn_a, nullptr);
  ASSERT_NE(mn_b, nullptr);
  ASSERT_NE(mn_c, nullptr);
}

}  // namespace