// SPDX-License-Identifier: GPL-2.0-or-later
// TEST_ID 2168
//
// Unit tests for Exiv2::XmpTextValue constructor behavior (value.cpp)
// Constraints: treat implementation as black box; test only observable behavior via public API.

#include <gtest/gtest.h>

#include <sstream>
#include <string>

#include <exiv2/value.hpp>

namespace {

class XmpTextValueTest_2168 : public ::testing::Test {
 protected:
  static std::string ToString(const Exiv2::Value& v) {
    std::ostringstream oss;
    v.write(oss);
    return oss.str();
  }
};

TEST_F(XmpTextValueTest_2168, ConstructFromString_EmptyString_DoesNotCrash_2168) {
  const std::string input;
  Exiv2::XmpTextValue v(input);

  // Observable behavior: write() is callable and stable.
  EXPECT_NO_THROW({
    (void)ToString(v);
  });

  // Basic invariants: count/size should be non-negative (size_t).
  EXPECT_GE(v.size(), static_cast<size_t>(0));
  EXPECT_GE(v.count(), static_cast<size_t>(0));
}

TEST_F(XmpTextValueTest_2168, ConstructFromString_NonEmpty_WriteIsCallable_2168) {
  const std::string input = "hello xmp";
  Exiv2::XmpTextValue v(input);

  // Observable behavior: write() produces some output (may or may not equal input).
  std::string out;
  EXPECT_NO_THROW({ out = ToString(v); });

  // Boundary: output for non-empty input should be a valid string (not crashing).
  // We avoid asserting exact formatting (black-box).
  EXPECT_GE(out.size(), static_cast<size_t>(0));
}

TEST_F(XmpTextValueTest_2168, ConstructFromString_WithEmbeddedNull_DoesNotCrash_2168) {
  std::string input("abc\0def", 7);  // includes embedded '\0'
  Exiv2::XmpTextValue v(input);

  EXPECT_NO_THROW({
    (void)ToString(v);
    (void)v.size();
    (void)v.count();
  });
}

TEST_F(XmpTextValueTest_2168, ConstructFromString_LargeInput_DoesNotCrash_2168) {
  // Boundary: large-ish buffer (not too huge for unit test runtime/memory).
  const std::string input(1 << 16, 'x');  // 65536 chars
  Exiv2::XmpTextValue v(input);

  EXPECT_NO_THROW({
    (void)ToString(v);
  });
}

TEST_F(XmpTextValueTest_2168, Clone_CreatesIndependentObjectWithSameWrite_2168) {
  const std::string input = "clone me";
  Exiv2::XmpTextValue v(input);

  const std::string before = ToString(v);

  auto cloned = v.clone();
  ASSERT_TRUE(static_cast<bool>(cloned));

  const std::string clonedStr = ToString(*cloned);

  // Observable expectation: clone represents the same value (via write()).
  // We avoid checking internal representation; write() is the public observable.
  EXPECT_EQ(clonedStr, before);

  // Independence check: re-read original, cloned should remain the same.
  ASSERT_NO_THROW({ v.read(std::string("changed")); });
  const std::string after = ToString(v);
  EXPECT_NE(after, before);

  EXPECT_EQ(ToString(*cloned), before);
}

TEST_F(XmpTextValueTest_2168, Read_ReturnsStatusCode_AndIsCallable_2168) {
  Exiv2::XmpTextValue v(std::string("initial"));

  // We only assert that read() returns an int and is callable.
  // No assumption about success/failure codes.
  int rc1 = 0;
  int rc2 = 0;
  EXPECT_NO_THROW({ rc1 = v.read(std::string("")); });
  EXPECT_NO_THROW({ rc2 = v.read(std::string("new value")); });

  (void)rc1;
  (void)rc2;

  // After read, write remains callable.
  EXPECT_NO_THROW({ (void)ToString(v); });
}

TEST_F(XmpTextValueTest_2168, NumericConversions_AreCallable_2168) {
  // XmpTextValue exposes numeric conversions; implementation may return defaults.
  Exiv2::XmpTextValue v(std::string("123"));

  EXPECT_NO_THROW({ (void)v.toInt64(0); });
  EXPECT_NO_THROW({ (void)v.toUint32(0); });
  EXPECT_NO_THROW({ (void)v.toFloat(0); });
  EXPECT_NO_THROW({ (void)v.toRational(0); });
}

TEST_F(XmpTextValueTest_2168, CountAndSize_AreConsistentAcrossMultipleCalls_2168) {
  Exiv2::XmpTextValue v(std::string("repeatability"));

  const auto s1 = v.size();
  const auto c1 = v.count();

  const auto s2 = v.size();
  const auto c2 = v.count();

  EXPECT_EQ(s1, s2);
  EXPECT_EQ(c1, c2);
}

}  // namespace