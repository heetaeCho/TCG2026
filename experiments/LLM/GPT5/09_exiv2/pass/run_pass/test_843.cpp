// File: test_xmparrayvalue_843.cpp
#include <gtest/gtest.h>

#include <sstream>
#include <string>

// Exiv2 header for XmpArrayValue
#include "value.hpp"

namespace {

class XmpArrayValueTest_843 : public ::testing::Test {
 protected:
  // Pick a TypeId that exists in Exiv2 and is suitable for XMP text-ish values.
  // This keeps the tests focused on observable behavior (read/count/toString/write).
  static Exiv2::TypeId kType() { return Exiv2::xmpText; }
};

TEST_F(XmpArrayValueTest_843, ReadNonEmptyReturnsZero_843) {
  Exiv2::XmpArrayValue v(kType());
  const int rc = v.read(std::string("hello"));
  EXPECT_EQ(0, rc);
}

TEST_F(XmpArrayValueTest_843, ReadEmptyReturnsZero_843) {
  Exiv2::XmpArrayValue v(kType());
  const int rc = v.read(std::string());
  EXPECT_EQ(0, rc);
}

TEST_F(XmpArrayValueTest_843, ReadNonEmptyIncreasesCount_843) {
  Exiv2::XmpArrayValue v(kType());
  const size_t before = v.count();

  ASSERT_EQ(0, v.read("one"));
  const size_t after = v.count();

  EXPECT_EQ(before + 1u, after);
}

TEST_F(XmpArrayValueTest_843, ReadEmptyDoesNotIncreaseCount_843) {
  Exiv2::XmpArrayValue v(kType());
  ASSERT_EQ(0, v.read("one"));
  const size_t before = v.count();

  ASSERT_EQ(0, v.read(std::string()));
  const size_t after = v.count();

  EXPECT_EQ(before, after);
}

TEST_F(XmpArrayValueTest_843, MultipleReadsAccumulateCount_843) {
  Exiv2::XmpArrayValue v(kType());
  const size_t before = v.count();

  ASSERT_EQ(0, v.read("a"));
  ASSERT_EQ(0, v.read("b"));
  ASSERT_EQ(0, v.read("c"));

  EXPECT_EQ(before + 3u, v.count());
}

TEST_F(XmpArrayValueTest_843, ToStringForFirstElementContainsInput_843) {
  Exiv2::XmpArrayValue v(kType());
  const std::string input = "first-item";
  ASSERT_EQ(0, v.read(input));
  ASSERT_GT(v.count(), 0u);

  std::string s;
  EXPECT_NO_THROW(s = v.toString(0));
  EXPECT_NE(std::string::npos, s.find(input));
}

TEST_F(XmpArrayValueTest_843, WriteIncludesInsertedString_843) {
  Exiv2::XmpArrayValue v(kType());
  const std::string input = "write-me";
  ASSERT_EQ(0, v.read(input));

  std::ostringstream oss;
  EXPECT_NO_THROW(v.write(oss));

  const std::string out = oss.str();
  EXPECT_FALSE(out.empty());
  EXPECT_NE(std::string::npos, out.find(input));
}

TEST_F(XmpArrayValueTest_843, CloneProducesIndependentObjectWithSameObservableContent_843) {
  Exiv2::XmpArrayValue v(kType());
  ASSERT_EQ(0, v.read("x"));
  ASSERT_EQ(0, v.read("y"));

  const auto beforeCount = v.count();
  std::string first;
  ASSERT_NO_THROW(first = v.toString(0));

  auto cloned = v.clone();
  ASSERT_TRUE(static_cast<bool>(cloned));
  EXPECT_EQ(beforeCount, cloned->count());

  std::string clonedFirst;
  EXPECT_NO_THROW(clonedFirst = cloned->toString(0));
  EXPECT_EQ(first, clonedFirst);

  // Mutate original and ensure clone's count is unchanged (observable independence).
  ASSERT_EQ(0, v.read("z"));
  EXPECT_EQ(beforeCount + 1u, v.count());
  EXPECT_EQ(beforeCount, cloned->count());
}

}  // namespace