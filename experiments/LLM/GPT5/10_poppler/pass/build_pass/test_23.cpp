// File: test_goo_string_getchar_23.cpp
#include <gtest/gtest.h>

#include <cstddef>
#include <string>
#include <string_view>

#include "TestProjects/poppler/goo/GooString.h"

namespace {

class GooStringTest_23 : public ::testing::Test {};

TEST_F(GooStringTest_23, GetCharReturnsFirstCharacter_23) {
  const GooString s("abc");
  ASSERT_GE(s.toStr().size(), 1u);
  EXPECT_EQ(s.getChar(0), 'a');
}

TEST_F(GooStringTest_23, GetCharReturnsLastCharacter_23) {
  const GooString s("abc");
  ASSERT_GE(s.toStr().size(), 1u);
  const size_t last = s.toStr().size() - 1;
  EXPECT_EQ(s.getChar(last), 'c');
}

TEST_F(GooStringTest_23, GetCharWorksForSingleCharacterString_23) {
  const GooString s("Z");
  ASSERT_EQ(s.toStr().size(), 1u);
  EXPECT_EQ(s.getChar(0), 'Z');
}

TEST_F(GooStringTest_23, GetCharMatchesUnderlyingToStrForValidIndices_23) {
  const GooString s("hello world");
  const std::string& ref = s.toStr();
  ASSERT_FALSE(ref.empty());

  // Sample a few valid indices deterministically (no out-of-range access).
  for (size_t i : {size_t{0}, size_t{1}, size_t{5}, ref.size() - 1}) {
    ASSERT_LT(i, ref.size());
    EXPECT_EQ(s.getChar(i), ref[i]);
  }
}

TEST_F(GooStringTest_23, GetCharHandlesEmbeddedNullByteWhenConstructedWithLength_23) {
  const char raw[] = {'a', 'b', '\0', 'c', 'd'};
  const GooString s(raw, sizeof(raw));

  ASSERT_EQ(s.toStr().size(), sizeof(raw));
  EXPECT_EQ(s.getChar(0), 'a');
  EXPECT_EQ(s.getChar(1), 'b');
  EXPECT_EQ(s.getChar(2), '\0');  // embedded NUL must be preserved
  EXPECT_EQ(s.getChar(3), 'c');
  EXPECT_EQ(s.getChar(4), 'd');
}

TEST_F(GooStringTest_23, GetCharWorksAfterMoveConstruction_23) {
  GooString original("move_me");
  GooString moved(std::move(original));

  const std::string& ref = moved.toStr();
  ASSERT_FALSE(ref.empty());
  EXPECT_EQ(moved.getChar(0), ref[0]);
  EXPECT_EQ(moved.getChar(ref.size() - 1), ref[ref.size() - 1]);
}

TEST_F(GooStringTest_23, GetCharWorksWithStringViewConstructor_23) {
  const std::string backing = "view-data";
  const std::string_view sv(backing);
  const GooString s(sv);

  const std::string& ref = s.toStr();
  ASSERT_EQ(ref.size(), sv.size());
  EXPECT_EQ(s.getChar(0), sv[0]);
  EXPECT_EQ(s.getChar(ref.size() - 1), sv[sv.size() - 1]);
}

// NOTE on "exceptional/error cases":
// std::string::operator[] (used internally by GooString::getChar per interface snippet)
// has undefined behavior for out-of-range indices, so we intentionally do NOT
// test getChar() with i >= size().

}  // namespace