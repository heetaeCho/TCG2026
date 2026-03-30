// File: goo_gostring_tostr_test.cpp
#include <gtest/gtest.h>

#include <string>

#include "goo/GooString.h"

namespace {

class GooStringTest_20 : public ::testing::Test {};

TEST_F(GooStringTest_20, ToStrReturnsReferenceToStdString_20) {
  GooString s("hello");
  const std::string& ref = s.toStr();

  EXPECT_EQ(ref, "hello");
  // Verify it's a reference (not a temporary copy) via address stability.
  EXPECT_EQ(&ref, &s.toStr());
}

TEST_F(GooStringTest_20, ToStrReflectsConstructorFromStdString_20) {
  std::string base = "abc";
  GooString s(base);

  const std::string& ref = s.toStr();
  EXPECT_EQ(ref, "abc");
}

TEST_F(GooStringTest_20, ToStrOnDefaultConstructedIsEmpty_20) {
  GooString s;
  EXPECT_TRUE(s.toStr().empty());
  EXPECT_EQ(s.toStr(), std::string());
}

TEST_F(GooStringTest_20, ToStrOnMoveConstructedPreservesMovedValue_20) {
  GooString original("moved");
  GooString moved(std::move(original));

  EXPECT_EQ(moved.toStr(), "moved");
}

TEST_F(GooStringTest_20, ToStrWorksForLargeStringBoundary_20) {
  const std::string large(1024 * 64, 'x');  // 64 KiB
  GooString s(large);

  const std::string& ref = s.toStr();
  EXPECT_EQ(ref.size(), large.size());
  EXPECT_EQ(ref, large);
}

}  // namespace