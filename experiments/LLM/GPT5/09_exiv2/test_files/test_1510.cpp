// TEST_ID 1510
// Unit tests for: Exiv2::Internal::newIfdMn2
//
// File under test: ./TestProjects/exiv2/src/makernote_int.cpp
// Partial implementation:
//   std::unique_ptr<TiffIfdMakernote> newIfdMn2(uint16_t tag, IfdId group, IfdId mnGroup) {
//     return std::make_unique<TiffIfdMakernote>(tag, group, mnGroup, nullptr);
//   }

#include <gtest/gtest.h>

#include <cstdint>
#include <limits>
#include <memory>
#include <type_traits>

// The declaration for newIfdMn2 / IfdId / TiffIfdMakernote is expected to be available from Exiv2 internals.
// Adjust include path if your build exposes it differently.
#include "makernote_int.hpp"

namespace {

using Exiv2::Internal::IfdId;
using Exiv2::Internal::TiffIfdMakernote;
using Exiv2::Internal::newIfdMn2;

class NewIfdMn2Test_1510 : public ::testing::Test {};

TEST_F(NewIfdMn2Test_1510, HasExpectedSignature_1510) {
  static_assert(
      std::is_same_v<decltype(newIfdMn2(std::declval<uint16_t>(), std::declval<IfdId>(), std::declval<IfdId>())),
                     std::unique_ptr<TiffIfdMakernote>>,
      "newIfdMn2 must return std::unique_ptr<TiffIfdMakernote>.");
}

TEST_F(NewIfdMn2Test_1510, ReturnsNonNullUniquePtr_1510) {
  const uint16_t tag = 0x0001;
  const IfdId group = static_cast<IfdId>(0);
  const IfdId mnGroup = static_cast<IfdId>(0);

  auto mn = newIfdMn2(tag, group, mnGroup);
  EXPECT_NE(mn, nullptr);
  EXPECT_NE(mn.get(), nullptr);
}

TEST_F(NewIfdMn2Test_1510, AcceptsBoundaryTagZero_1510) {
  const uint16_t tag = 0;
  const IfdId group = static_cast<IfdId>(0);
  const IfdId mnGroup = static_cast<IfdId>(0);

  EXPECT_NO_THROW({
    auto mn = newIfdMn2(tag, group, mnGroup);
    EXPECT_NE(mn, nullptr);
  });
}

TEST_F(NewIfdMn2Test_1510, AcceptsBoundaryTagMax_1510) {
  const uint16_t tag = std::numeric_limits<uint16_t>::max();
  const IfdId group = static_cast<IfdId>(0);
  const IfdId mnGroup = static_cast<IfdId>(0);

  EXPECT_NO_THROW({
    auto mn = newIfdMn2(tag, group, mnGroup);
    EXPECT_NE(mn, nullptr);
  });
}

TEST_F(NewIfdMn2Test_1510, ReturnedPointersAreDistinctAcrossCalls_1510) {
  const IfdId group = static_cast<IfdId>(0);
  const IfdId mnGroup = static_cast<IfdId>(0);

  auto a = newIfdMn2(/*tag=*/0x0100, group, mnGroup);
  auto b = newIfdMn2(/*tag=*/0x0100, group, mnGroup);

  ASSERT_NE(a, nullptr);
  ASSERT_NE(b, nullptr);
  EXPECT_NE(a.get(), b.get());
}

TEST_F(NewIfdMn2Test_1510, ReturnValueIsMovableUniquePtr_1510) {
  const uint16_t tag = 0x00FF;
  const IfdId group = static_cast<IfdId>(1);
  const IfdId mnGroup = static_cast<IfdId>(2);

  auto mn = newIfdMn2(tag, group, mnGroup);
  ASSERT_NE(mn, nullptr);

  TiffIfdMakernote* raw = mn.get();
  auto moved = std::move(mn);

  EXPECT_EQ(mn.get(), nullptr);
  EXPECT_EQ(moved.get(), raw);
  EXPECT_NE(moved.get(), nullptr);
}

}  // namespace