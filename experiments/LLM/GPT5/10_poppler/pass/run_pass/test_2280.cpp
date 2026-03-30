// GooString_getChar_test_2280.cc
#include <gtest/gtest.h>

#include <cstddef>
#include <cstring>
#include <string>
#include <utility>

#include "goo/GooString.h"

class GooStringTest_2280 : public ::testing::Test {};

TEST_F(GooStringTest_2280, GetChar_ReturnsExpectedCharacters_FromCStringCtor_2280) {
  GooString s("abc");

  EXPECT_EQ(s.getChar(0), 'a');
  EXPECT_EQ(s.getChar(1), 'b');
  EXPECT_EQ(s.getChar(2), 'c');
}

TEST_F(GooStringTest_2280, GetChar_WorksForSingleCharacterString_IndexZero_2280) {
  GooString s("Z");

  EXPECT_EQ(s.getChar(0), 'Z');
}

TEST_F(GooStringTest_2280, GetChar_ReturnsExpectedLastCharacter_InRangeBoundary_2280) {
  static constexpr const char* kText = "hello"; // length 5
  GooString s(kText);

  const std::size_t last = std::strlen(kText) - 1;
  EXPECT_EQ(s.getChar(last), 'o');
}

TEST_F(GooStringTest_2280, GetChar_PreservesEmbeddedNull_WithLengthCtor_2280) {
  const char raw[] = {'a', '\0', 'b'};
  GooString s(raw, sizeof(raw));

  EXPECT_EQ(s.getChar(0), 'a');
  EXPECT_EQ(s.getChar(1), '\0');
  EXPECT_EQ(s.getChar(2), 'b');
}

TEST_F(GooStringTest_2280, GetChar_Works_FromStdStringCtor_2280) {
  const std::string src = "xyz";
  GooString s(src);

  EXPECT_EQ(s.getChar(0), 'x');
  EXPECT_EQ(s.getChar(1), 'y');
  EXPECT_EQ(s.getChar(2), 'z');
}

TEST_F(GooStringTest_2280, GetChar_WorksAfterMoveConstruction_2280) {
  GooString moved_from("move-me");
  GooString s(std::move(moved_from));

  EXPECT_EQ(s.getChar(0), 'm');
  EXPECT_EQ(s.getChar(1), 'o');
  EXPECT_EQ(s.getChar(2), 'v');
  EXPECT_EQ(s.getChar(3), 'e');
}

// Note: We intentionally do NOT test out-of-range indices because std::string::operator[]
// has undefined behavior on out-of-bounds access, and such tests would be non-deterministic.