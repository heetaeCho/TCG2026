// =================================================================================================
// TEST_ID: 810
// Unit tests for Exiv2::StringValueBase::toUint32(size_t)
// File under test: ./TestProjects/exiv2/src/value.cpp (partial)
// =================================================================================================

#include <gtest/gtest.h>

#include <cstdint>
#include <stdexcept>
#include <string>

#include "exiv2/value.hpp"

namespace {

class StringValueBaseTest_810 : public ::testing::Test {
 protected:
  // Construct with an arbitrary TypeId value. We intentionally avoid relying on specific TypeId
  // enumerators (black-box; the tests focus on toUint32 observable behavior).
  static Exiv2::StringValueBase Make(const std::string& buf) {
    return Exiv2::StringValueBase(static_cast<Exiv2::TypeId>(0), buf);
  }
};

TEST_F(StringValueBaseTest_810, ToUint32ReturnsUnderlyingElementAsUint32_810) {
  auto v = Make("A");

  // Observable behavior: toUint32 returns a uint32_t derived from the underlying stored content.
  // For a one-character buffer, index 0 should map to that character's value.
  const uint32_t out = v.toUint32(0);
  EXPECT_EQ(out, static_cast<uint32_t>(static_cast<unsigned char>('A')));
}

TEST_F(StringValueBaseTest_810, ToUint32ReturnsNthElement_810) {
  auto v = Make("Az");

  EXPECT_EQ(v.toUint32(0), static_cast<uint32_t>(static_cast<unsigned char>('A')));
  EXPECT_EQ(v.toUint32(1), static_cast<uint32_t>(static_cast<unsigned char>('z')));
}

TEST_F(StringValueBaseTest_810, ToUint32OnLastValidIndexWorks_810) {
  auto v = Make("ABC");

  // Boundary: last valid index.
  EXPECT_EQ(v.toUint32(2), static_cast<uint32_t>(static_cast<unsigned char>('C')));
}

TEST_F(StringValueBaseTest_810, ToUint32ThrowsOnEmptyValue_810) {
  auto v = Make("");

  // Boundary/error: accessing index 0 in an empty value should be observable as an exception.
  EXPECT_THROW((void)v.toUint32(0), std::out_of_range);
}

TEST_F(StringValueBaseTest_810, ToUint32ThrowsWhenIndexEqualsSize_810) {
  auto v = Make("ABC");

  // Boundary: index == size is out of range.
  EXPECT_THROW((void)v.toUint32(3), std::out_of_range);
}

TEST_F(StringValueBaseTest_810, ToUint32ThrowsWhenIndexIsFarOutOfRange_810) {
  auto v = Make("ABC");

  // Error: a clearly invalid index should be observable as an exception.
  EXPECT_THROW((void)v.toUint32(1000), std::out_of_range);
}

TEST_F(StringValueBaseTest_810, ToUint32DoesNotMutateStoredValue_810) {
  const std::string original = "Hello";
  auto v = Make(original);

  (void)v.toUint32(1);

  // Observable through public member (per provided interface): value_ remains unchanged.
  EXPECT_EQ(v.value_, original);
}

}  // namespace