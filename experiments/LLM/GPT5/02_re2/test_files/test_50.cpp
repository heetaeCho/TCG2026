// File: ./TestProjects/re2/python/_re2_onecharlen_test.cc

#include <gtest/gtest.h>

// Include the implementation unit so we can test the internal 'static inline' function
// exactly as used in production (no re-implementation).
#include "TestProjects/re2/python/_re2.cc"

using re2_python::OneCharLen;

namespace {

// Helper: call OneCharLen on a single byte value without signed-char pitfalls.
static int LenOf(uint8_t byte) {
  const char* p = reinterpret_cast<const char*>(&byte);
  return OneCharLen(p);
}

// -------------------- Tests --------------------

TEST(OneCharLenTest_50, Returns1ForAsciiBytes_50) {
  // High nibbles 0x0..0x7 map to 1
  EXPECT_EQ(1, LenOf(0x00));
  EXPECT_EQ(1, LenOf(0x41));  // 'A'
  EXPECT_EQ(1, LenOf(0x7F));  // boundary of ASCII
}

TEST(OneCharLenTest_50, Returns1ForHighNibbles8ToB_50) {
  // High nibbles 0x8..0xB map to 1
  EXPECT_EQ(1, LenOf(0x80));  // start of 0x8*
  EXPECT_EQ(1, LenOf(0x8F));  // end of 0x8*
  EXPECT_EQ(1, LenOf(0x9A));  // 0x9*
  EXPECT_EQ(1, LenOf(0xA0));  // 0xA*
  EXPECT_EQ(1, LenOf(0xBF));  // end of 0xB*
}

TEST(OneCharLenTest_50, Returns2ForC0toDF_50) {
  // High nibbles 0xC..0xD map to 2
  EXPECT_EQ(2, LenOf(0xC0));  // boundary at start
  EXPECT_EQ(2, LenOf(0xC7));
  EXPECT_EQ(2, LenOf(0xDF));  // boundary at end
}

TEST(OneCharLenTest_50, Returns3ForE0toEF_50) {
  // High nibble 0xE maps to 3
  EXPECT_EQ(3, LenOf(0xE0));  // boundary at start
  EXPECT_EQ(3, LenOf(0xE5));
  EXPECT_EQ(3, LenOf(0xEF));  // boundary at end
}

TEST(OneCharLenTest_50, Returns4ForF0toFF_50) {
  // High nibble 0xF maps to 4
  EXPECT_EQ(4, LenOf(0xF0));  // boundary at start
  EXPECT_EQ(4, LenOf(0xF8));
  EXPECT_EQ(4, LenOf(0xFF));  // boundary at end
}

TEST(OneCharLenTest_50, HandlesSignedCharSafelyViaMasking_50) {
  // Ensure correct behavior even if 'char' is signed (uses & 0xFF internally).
  // Using uint8_t + reinterpret_cast ensures we pass the exact byte value.
  EXPECT_EQ(3, LenOf(0xE2));  // negative if 'char' is signed
  EXPECT_EQ(4, LenOf(0xFF));  // negative if 'char' is signed
  EXPECT_EQ(2, LenOf(0xD0));  // another >127 value
}

}  // namespace
