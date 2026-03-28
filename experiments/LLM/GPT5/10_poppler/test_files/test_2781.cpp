// Mul09Table_test_2781.cc
#include <gtest/gtest.h>

#include <cstdint>
#include <type_traits>

// NOTE:
// Mul09Table is defined/declared in Poppler's Decrypt module.
// Adjust the include as needed for your build (some trees expose it via a header,
// others only via the .cc in the same target).
#if __has_include("Decrypt.h")
#  include "Decrypt.h"
#elif __has_include("poppler/Decrypt.h")
#  include "poppler/Decrypt.h"
#elif __has_include("Decrypt.cc")
#  include "Decrypt.cc"
#elif __has_include("poppler/Decrypt.cc")
#  include "poppler/Decrypt.cc"
#endif

namespace {

class Mul09TableTest_2781 : public ::testing::Test {};

TEST_F(Mul09TableTest_2781, IsConstexprDefaultConstructible_2781)
{
  // This verifies the constructor is usable in constant evaluation contexts.
  static_assert(std::is_default_constructible<Mul09Table>::value,
                "Mul09Table should be default constructible");
#if defined(__cpp_lib_is_constant_evaluated) || (defined(__cpp_consteval) || defined(__cpp_constexpr))
  constexpr Mul09Table t{};
  (void)t;
#endif
  SUCCEED();
}

TEST_F(Mul09TableTest_2781, OperatorIsUsableAtCompileTimeForKnownInputs_2781)
{
  // Known values for AES GF(2^8) multiply-by-0x09 tables are widely published.
  // We assert a small set of canonical entries (start of table + a couple of others).
  constexpr Mul09Table t{};
  static_assert(t(static_cast<uint8_t>(0x00)) == static_cast<unsigned char>(0x00), "mul9[0x00]");
  static_assert(t(static_cast<uint8_t>(0x01)) == static_cast<unsigned char>(0x09), "mul9[0x01]");
  static_assert(t(static_cast<uint8_t>(0x02)) == static_cast<unsigned char>(0x12), "mul9[0x02]");
  static_assert(t(static_cast<uint8_t>(0x03)) == static_cast<unsigned char>(0x1b), "mul9[0x03]");

  // A spot-check past the first 16 entries.
  static_assert(t(static_cast<uint8_t>(0x10)) == static_cast<unsigned char>(0x90), "mul9[0x10]");
  static_assert(t(static_cast<uint8_t>(0x1f)) == static_cast<unsigned char>(0xe7), "mul9[0x1f]");

  SUCCEED();
}

TEST_F(Mul09TableTest_2781, ReturnsExpectedValuesForBoundaryIndices_2781)
{
  Mul09Table t;

  // Boundary indices (min/max for uint8_t) should be accepted and return deterministic values.
  EXPECT_EQ(t(static_cast<uint8_t>(0x00)), static_cast<unsigned char>(0x00));
  EXPECT_EQ(t(static_cast<uint8_t>(0xFF)), static_cast<unsigned char>(0x46));

  // Also check the element just below the max boundary.
  EXPECT_EQ(t(static_cast<uint8_t>(0xFE)), static_cast<unsigned char>(0x4F));
}

TEST_F(Mul09TableTest_2781, ReturnsExpectedValuesForSelectedMidRangeInputs_2781)
{
  Mul09Table t;

  // Additional mid-range spot checks.
  EXPECT_EQ(t(static_cast<uint8_t>(0x07)), static_cast<unsigned char>(0x3F));
  EXPECT_EQ(t(static_cast<uint8_t>(0x08)), static_cast<unsigned char>(0x48));
  EXPECT_EQ(t(static_cast<uint8_t>(0x0F)), static_cast<unsigned char>(0x77));

  EXPECT_EQ(t(static_cast<uint8_t>(0x20)), static_cast<unsigned char>(0x3B));
  EXPECT_EQ(t(static_cast<uint8_t>(0x2A)), static_cast<unsigned char>(0x61));
  EXPECT_EQ(t(static_cast<uint8_t>(0x3F)), static_cast<unsigned char>(0xDC));
}

TEST_F(Mul09TableTest_2781, RepeatedCallsReturnSameResult_2781)
{
  Mul09Table t;

  const uint8_t idx = 0x1F;
  const unsigned char first = t(idx);
  for (int i = 0; i < 50; ++i) {
    EXPECT_EQ(t(idx), first);
  }
}

} // namespace