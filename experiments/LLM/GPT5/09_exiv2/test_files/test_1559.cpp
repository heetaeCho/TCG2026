// File: test_asfvideo_guidtag_1559.cpp
#include <gtest/gtest.h>

#include <array>
#include <set>
#include <string>

#include <exiv2/asfvideo.hpp>

namespace {

using Exiv2::AsfVideo;
using Exiv2::byte;

static std::array<byte, 8> Arr8(std::initializer_list<int> v) {
  std::array<byte, 8> a{};
  size_t i = 0;
  for (int x : v) {
    if (i >= a.size()) break;
    a[i++] = static_cast<byte>(x & 0xFF);
  }
  return a;
}

static AsfVideo::GUIDTag MakeGuid(unsigned int d1, unsigned short d2, unsigned short d3,
                                  const std::array<byte, 8>& d4) {
  return AsfVideo::GUIDTag(d1, d2, d3, d4);
}

}  // namespace

class AsfVideoGuidTagTest_1559 : public ::testing::Test {};

TEST_F(AsfVideoGuidTagTest_1559, LessOrdersByData1WhenDifferent_1559) {
  const auto a = MakeGuid(1u, 2u, 3u, Arr8({0, 0, 0, 0, 0, 0, 0, 0}));
  const auto b = MakeGuid(2u, 0u, 0u, Arr8({255, 255, 255, 255, 255, 255, 255, 255}));

  EXPECT_TRUE(a < b);
  EXPECT_FALSE(b < a);
}

TEST_F(AsfVideoGuidTagTest_1559, LessOrdersByData2WhenData1Equal_1559) {
  const auto a = MakeGuid(7u, 1u, 999u, Arr8({9, 9, 9, 9, 9, 9, 9, 9}));
  const auto b = MakeGuid(7u, 2u, 0u, Arr8({0, 0, 0, 0, 0, 0, 0, 0}));

  EXPECT_TRUE(a < b);
  EXPECT_FALSE(b < a);
}

TEST_F(AsfVideoGuidTagTest_1559, LessOrdersByData3WhenData1Data2Equal_1559) {
  const auto a = MakeGuid(7u, 8u, 1u, Arr8({10, 20, 30, 40, 50, 60, 70, 80}));
  const auto b = MakeGuid(7u, 8u, 2u, Arr8({0, 0, 0, 0, 0, 0, 0, 0}));

  EXPECT_TRUE(a < b);
  EXPECT_FALSE(b < a);
}

TEST_F(AsfVideoGuidTagTest_1559, LessOrdersByLexicographicalData4WhenFirstThreeEqual_1559) {
  const auto a = MakeGuid(10u, 11u, 12u, Arr8({0, 1, 2, 3, 4, 5, 6, 7}));
  const auto b = MakeGuid(10u, 11u, 12u, Arr8({0, 1, 2, 3, 4, 5, 6, 8}));
  const auto c = MakeGuid(10u, 11u, 12u, Arr8({0, 1, 2, 3, 4, 5, 6, 7}));

  EXPECT_TRUE(a < b);
  EXPECT_FALSE(b < a);

  // Identical data4 should not be less either direction.
  EXPECT_FALSE(a < c);
  EXPECT_FALSE(c < a);
}

TEST_F(AsfVideoGuidTagTest_1559, EqualityImpliesNotLessEitherDirection_1559) {
  const auto a = MakeGuid(0u, 0u, 0u, Arr8({0, 0, 0, 0, 0, 0, 0, 0}));
  const auto b = MakeGuid(0u, 0u, 0u, Arr8({0, 0, 0, 0, 0, 0, 0, 0}));

  EXPECT_TRUE(a == b);
  EXPECT_FALSE(a < b);
  EXPECT_FALSE(b < a);
}

TEST_F(AsfVideoGuidTagTest_1559, BoundaryValuesOrderConsistently_1559) {
  const auto min = MakeGuid(0u, 0u, 0u, Arr8({0, 0, 0, 0, 0, 0, 0, 0}));
  const auto max = MakeGuid(0xFFFFFFFFu, 0xFFFFu, 0xFFFFu,
                            Arr8({255, 255, 255, 255, 255, 255, 255, 255}));

  EXPECT_TRUE(min < max);
  EXPECT_FALSE(max < min);
  EXPECT_FALSE(min == max);
}

TEST_F(AsfVideoGuidTagTest_1559, SupportsStrictWeakOrderingInStdSet_1559) {
  const auto a = MakeGuid(1u, 0u, 0u, Arr8({0, 0, 0, 0, 0, 0, 0, 0}));
  const auto b = MakeGuid(1u, 0u, 0u, Arr8({0, 0, 0, 0, 0, 0, 0, 1}));
  const auto c = MakeGuid(2u, 0u, 0u, Arr8({0, 0, 0, 0, 0, 0, 0, 0}));
  const auto dupA = MakeGuid(1u, 0u, 0u, Arr8({0, 0, 0, 0, 0, 0, 0, 0}));

  std::set<AsfVideo::GUIDTag> s;
  s.insert(c);
  s.insert(b);
  s.insert(a);
  s.insert(dupA);  // should not create a new distinct element if == implies equivalent ordering.

  ASSERT_EQ(s.size(), 3u);

  auto it = s.begin();
  ASSERT_NE(it, s.end());
  EXPECT_TRUE(*it == a);
  ++it;
  ASSERT_NE(it, s.end());
  EXPECT_TRUE(*it == b);
  ++it;
  ASSERT_NE(it, s.end());
  EXPECT_TRUE(*it == c);
}

TEST_F(AsfVideoGuidTagTest_1559, ToStringIsNonEmptyAndStableForSameObject_1559) {
  const auto g = MakeGuid(0x12345678u, 0x9ABCu, 0xDEF0u, Arr8({1, 2, 3, 4, 5, 6, 7, 8}));

  const std::string s1 = g.to_string();
  const std::string s2 = g.to_string();

  EXPECT_FALSE(s1.empty());
  EXPECT_EQ(s1, s2);
}

TEST_F(AsfVideoGuidTagTest_1559, ToStringMatchesForEqualValues_1559) {
  const auto a = MakeGuid(5u, 6u, 7u, Arr8({8, 7, 6, 5, 4, 3, 2, 1}));
  const auto b = MakeGuid(5u, 6u, 7u, Arr8({8, 7, 6, 5, 4, 3, 2, 1}));

  ASSERT_TRUE(a == b);
  EXPECT_EQ(a.to_string(), b.to_string());
}