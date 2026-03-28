// File: parse_signed_char_test_270.cc

#include <cstddef>
#include <gtest/gtest.h>

// Forward declaration of the interface under test.
// (We rely only on the provided signature and observable behavior.)
namespace re2 {
namespace re2_internal {
bool Parse(const char* str, size_t n, signed char* dest);
}  // namespace re2_internal
}  // namespace re2

using re2::re2_internal::Parse;

// --- Normal operation ---

TEST(ParseSignedCharTest_270, WritesByteToDest_WhenLengthOne_270) {
  const char input[] = {'A'};
  signed char out = 0;

  const bool ok = Parse(input, /*n=*/1, &out);

  EXPECT_TRUE(ok);
  EXPECT_EQ(static_cast<signed char>('A'), out);
}

TEST(ParseSignedCharTest_270, WritesZeroByte_WhenInputIsNullChar_270) {
  const char input[] = {'\0'};
  signed char out = -123;  // sentinel

  const bool ok = Parse(input, /*n=*/1, &out);

  EXPECT_TRUE(ok);
  EXPECT_EQ(static_cast<signed char>(0), out);
}

// --- Boundary conditions & error cases ---

TEST(ParseSignedCharTest_270, ReturnsFalse_WhenLengthIsZero_270) {
  const char input[] = { };  // pointer is valid, n = 0
  signed char out = 42;

  const bool ok = Parse(input, /*n=*/0, &out);

  EXPECT_FALSE(ok);
  // No observable modification expected when n != 1.
  EXPECT_EQ(42, out);
}

TEST(ParseSignedCharTest_270, ReturnsFalse_WhenLengthGreaterThanOne_270) {
  const char input[] = {'A', 'B'};
  signed char out = 99;

  const bool ok = Parse(input, /*n=*/2, &out);

  EXPECT_FALSE(ok);
  // No observable modification expected when n != 1.
  EXPECT_EQ(99, out);
}

// --- Null destination handling ---

TEST(ParseSignedCharTest_270, ReturnsTrue_WhenDestIsNullAndLengthOne_270) {
  const char input[] = {'Z'};

  // Should succeed with no write when dest == nullptr and n == 1.
  const bool ok = Parse(input, /*n=*/1, /*dest=*/nullptr);

  EXPECT_TRUE(ok);
}

TEST(ParseSignedCharTest_270, ReturnsFalse_WhenDestIsNullAndLengthNotOne_270) {
  const char input[] = {'X', 'Y'};

  // n != 1 should fail regardless of dest.
  const bool ok = Parse(input, /*n=*/2, /*dest=*/nullptr);

  EXPECT_FALSE(ok);
}
