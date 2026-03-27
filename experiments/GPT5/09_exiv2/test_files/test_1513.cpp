// ============================================================================
// tests/test_makernote_int_newOlympus2Mn2_1513.cpp
//
// Unit tests for:
//   Exiv2::Internal::newOlympus2Mn2(uint16_t tag, IfdId group, IfdId mnGroup)
//
// Constraints respected:
// - Treat implementation as a black box (no internal logic assumptions)
// - Only observable behavior via public interface (non-null, ownership/lifetime)
// - No private/internal state access
// ============================================================================

#include <gtest/gtest.h>

#include <cstdint>
#include <memory>

// The function under test is implemented in:
//   ./TestProjects/exiv2/src/makernote_int.cpp
// It should be declared in an internal header.
#include "makernote_int.hpp"

namespace {

class Olympus2Mn2FactoryTest_1513 : public ::testing::Test {};

TEST_F(Olympus2Mn2FactoryTest_1513, ReturnsNonNullForTypicalInputs_1513) {
  const uint16_t tag = 0x1234;
  const auto group = static_cast<Exiv2::Internal::IfdId>(0);
  const auto mnGroup = static_cast<Exiv2::Internal::IfdId>(0);

  std::unique_ptr<Exiv2::Internal::TiffIfdMakernote> mn;
  EXPECT_NO_THROW({
    mn = Exiv2::Internal::newOlympus2Mn2(tag, group, mnGroup);
  });
  EXPECT_NE(mn, nullptr);
}

TEST_F(Olympus2Mn2FactoryTest_1513, ReturnsDistinctInstancesOnMultipleCalls_1513) {
  const uint16_t tag = 0x0001;
  const auto group = static_cast<Exiv2::Internal::IfdId>(0);
  const auto mnGroup = static_cast<Exiv2::Internal::IfdId>(0);

  auto a = Exiv2::Internal::newOlympus2Mn2(tag, group, mnGroup);
  auto b = Exiv2::Internal::newOlympus2Mn2(tag, group, mnGroup);

  ASSERT_NE(a, nullptr);
  ASSERT_NE(b, nullptr);
  EXPECT_NE(a.get(), b.get());  // distinct allocations/instances
}

TEST_F(Olympus2Mn2FactoryTest_1513, AcceptsMinTagValue_1513) {
  const uint16_t tag = 0x0000;
  const auto group = static_cast<Exiv2::Internal::IfdId>(0);
  const auto mnGroup = static_cast<Exiv2::Internal::IfdId>(0);

  auto mn = Exiv2::Internal::newOlympus2Mn2(tag, group, mnGroup);
  EXPECT_NE(mn, nullptr);
}

TEST_F(Olympus2Mn2FactoryTest_1513, AcceptsMaxTagValue_1513) {
  const uint16_t tag = 0xFFFF;
  const auto group = static_cast<Exiv2::Internal::IfdId>(0);
  const auto mnGroup = static_cast<Exiv2::Internal::IfdId>(0);

  auto mn = Exiv2::Internal::newOlympus2Mn2(tag, group, mnGroup);
  EXPECT_NE(mn, nullptr);
}

TEST_F(Olympus2Mn2FactoryTest_1513, AcceptsDifferentGroupAndMnGroupValues_1513) {
  const uint16_t tag = 0x00AB;

  // Use a small set of distinct enum-underlying values without assuming specific enumerators exist.
  const auto group1 = static_cast<Exiv2::Internal::IfdId>(0);
  const auto mnGroup1 = static_cast<Exiv2::Internal::IfdId>(1);
  const auto group2 = static_cast<Exiv2::Internal::IfdId>(2);
  const auto mnGroup2 = static_cast<Exiv2::Internal::IfdId>(3);

  auto a = Exiv2::Internal::newOlympus2Mn2(tag, group1, mnGroup1);
  auto b = Exiv2::Internal::newOlympus2Mn2(tag, group2, mnGroup2);

  EXPECT_NE(a, nullptr);
  EXPECT_NE(b, nullptr);
}

TEST_F(Olympus2Mn2FactoryTest_1513, UniquePtrOwnershipAndResetDoesNotThrow_1513) {
  const uint16_t tag = 0x0102;
  const auto group = static_cast<Exiv2::Internal::IfdId>(0);
  const auto mnGroup = static_cast<Exiv2::Internal::IfdId>(0);

  auto mn = Exiv2::Internal::newOlympus2Mn2(tag, group, mnGroup);
  ASSERT_NE(mn, nullptr);

  // Observable behavior: the returned object is owned by std::unique_ptr and can be released/reset safely.
  EXPECT_NO_THROW({
    mn.reset();
  });
  EXPECT_EQ(mn, nullptr);
}

}  // namespace