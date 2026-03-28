// File: test_newSony1Mn2_1531.cpp
#include <gtest/gtest.h>

#include <cstdint>
#include <memory>
#include <type_traits>

// Exiv2 internals
#include "makernote_int.hpp"  // expected to declare Exiv2::Internal::newSony1Mn2(...)
#include "tiffcomposite_int.hpp"  // expected to define TiffIfdMakernote / IfdId (path may vary in your tree)

namespace {

using Exiv2::Internal::IfdId;
using Exiv2::Internal::TiffIfdMakernote;
using Exiv2::Internal::newSony1Mn2;

class NewSony1Mn2Test_1531 : public ::testing::Test {
 protected:
  static IfdId MakeIfdId(int v) { return static_cast<IfdId>(v); }
};

TEST_F(NewSony1Mn2Test_1531, ReturnsNonNullForTypicalInputs_1531) {
  constexpr uint16_t tag = 0x1234;
  const IfdId group = MakeIfdId(1);
  const IfdId mnGroup = MakeIfdId(2);

  std::unique_ptr<TiffIfdMakernote> mn;
  EXPECT_NO_THROW(mn = newSony1Mn2(tag, group, mnGroup));
  ASSERT_NE(mn, nullptr);
  EXPECT_NE(mn.get(), nullptr);
}

TEST_F(NewSony1Mn2Test_1531, ReturnsDistinctObjectsAcrossCalls_1531) {
  constexpr uint16_t tag = 0x0001;
  const IfdId group = MakeIfdId(3);
  const IfdId mnGroup = MakeIfdId(4);

  auto a = newSony1Mn2(tag, group, mnGroup);
  auto b = newSony1Mn2(tag, group, mnGroup);

  ASSERT_NE(a, nullptr);
  ASSERT_NE(b, nullptr);
  EXPECT_NE(a.get(), b.get());  // distinct allocations / instances
}

TEST_F(NewSony1Mn2Test_1531, BoundaryTagZeroDoesNotThrowAndReturnsNonNull_1531) {
  constexpr uint16_t tag = 0x0000;
  const IfdId group = MakeIfdId(0);
  const IfdId mnGroup = MakeIfdId(0);

  std::unique_ptr<TiffIfdMakernote> mn;
  EXPECT_NO_THROW(mn = newSony1Mn2(tag, group, mnGroup));
  ASSERT_NE(mn, nullptr);
}

TEST_F(NewSony1Mn2Test_1531, BoundaryTagMaxDoesNotThrowAndReturnsNonNull_1531) {
  constexpr uint16_t tag = 0xFFFF;
  const IfdId group = MakeIfdId(0x7FFF);
  const IfdId mnGroup = MakeIfdId(0x7FFE);

  std::unique_ptr<TiffIfdMakernote> mn;
  EXPECT_NO_THROW(mn = newSony1Mn2(tag, group, mnGroup));
  ASSERT_NE(mn, nullptr);
}

TEST_F(NewSony1Mn2Test_1531, SameGroupAndMnGroupDoesNotThrowAndReturnsNonNull_1531) {
  constexpr uint16_t tag = 0x00AA;
  const IfdId group = MakeIfdId(5);
  const IfdId mnGroup = group;  // same value on purpose (boundary-ish input relationship)

  std::unique_ptr<TiffIfdMakernote> mn;
  EXPECT_NO_THROW(mn = newSony1Mn2(tag, group, mnGroup));
  ASSERT_NE(mn, nullptr);
}

TEST_F(NewSony1Mn2Test_1531, UnusualIfdIdValuesDoNotThrowAndReturnNonNull_1531) {
  // "Exceptional/error-ish" inputs: values outside normal enum range (if any).
  // We only validate observable behavior: no throw + non-null result.
  constexpr uint16_t tag = 0x0BAD;
  const IfdId group = MakeIfdId(-1);
  const IfdId mnGroup = MakeIfdId(0xDEADBEEF);

  std::unique_ptr<TiffIfdMakernote> mn;
  EXPECT_NO_THROW(mn = newSony1Mn2(tag, group, mnGroup));
  ASSERT_NE(mn, nullptr);
}

TEST_F(NewSony1Mn2Test_1531, DestroyingOneInstanceDoesNotAffectAnother_1531) {
  constexpr uint16_t tag = 0x2222;
  const IfdId group = MakeIfdId(6);
  const IfdId mnGroup = MakeIfdId(7);

  auto first = newSony1Mn2(tag, group, mnGroup);
  auto second = newSony1Mn2(tag, group, mnGroup);

  ASSERT_NE(first, nullptr);
  ASSERT_NE(second, nullptr);

  // Release/destroy first; second should remain valid and owned.
  first.reset();
  EXPECT_EQ(first, nullptr);
  EXPECT_NE(second, nullptr);
  EXPECT_NE(second.get(), nullptr);
}

}  // namespace