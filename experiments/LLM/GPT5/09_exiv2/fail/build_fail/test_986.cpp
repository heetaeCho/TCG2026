// File: version_test_986.cpp
#include <gtest/gtest.h>

#include <exiv2/version.hpp>

#include <algorithm>
#include <cctype>
#include <regex>
#include <string>

namespace {

class VersionStringTest_986 : public ::testing::Test {};

static int CountChar(const std::string& s, char ch) {
  return static_cast<int>(std::count(s.begin(), s.end(), ch));
}

static bool AllDigits(const std::string& s) {
  return !s.empty() &&
         std::all_of(s.begin(), s.end(), [](unsigned char c) { return std::isdigit(c) != 0; });
}

}  // namespace

TEST_F(VersionStringTest_986, ReturnsNonEmptyString_986) {
  std::string v;
  EXPECT_NO_THROW(v = Exiv2::versionString());
  EXPECT_FALSE(v.empty());
}

TEST_F(VersionStringTest_986, MatchesMajorMinorPatchMacrosExactly_986) {
  const std::string expected = std::to_string(EXIV2_MAJOR_VERSION) + "." +
                               std::to_string(EXIV2_MINOR_VERSION) + "." +
                               std::to_string(EXIV2_PATCH_VERSION);

  std::string actual;
  EXPECT_NO_THROW(actual = Exiv2::versionString());
  EXPECT_EQ(expected, actual);
}

TEST_F(VersionStringTest_986, HasExactlyTwoDotsAndThreeNumericComponents_986) {
  const std::string v = Exiv2::versionString();

  EXPECT_EQ(2, CountChar(v, '.'));

  // Split on '.' without assuming anything else.
  const std::size_t p1 = v.find('.');
  ASSERT_NE(std::string::npos, p1);
  const std::size_t p2 = v.find('.', p1 + 1);
  ASSERT_NE(std::string::npos, p2);

  const std::string a = v.substr(0, p1);
  const std::string b = v.substr(p1 + 1, p2 - (p1 + 1));
  const std::string c = v.substr(p2 + 1);

  EXPECT_TRUE(AllDigits(a));
  EXPECT_TRUE(AllDigits(b));
  EXPECT_TRUE(AllDigits(c));
}

TEST_F(VersionStringTest_986, DoesNotContainWhitespace_986) {
  const std::string v = Exiv2::versionString();
  const bool has_ws = std::any_of(v.begin(), v.end(), [](unsigned char ch) { return std::isspace(ch) != 0; });
  EXPECT_FALSE(has_ws);
}

TEST_F(VersionStringTest_986, IsStableAcrossMultipleCalls_986) {
  const std::string v1 = Exiv2::versionString();
  const std::string v2 = Exiv2::versionString();
  const std::string v3 = Exiv2::versionString();
  EXPECT_EQ(v1, v2);
  EXPECT_EQ(v2, v3);
}

TEST_F(VersionStringTest_986, MatchesSimpleNumericDotNumericDotNumericPattern_986) {
  const std::string v = Exiv2::versionString();
  const std::regex re(R"(^\d+\.\d+\.\d+$)");
  EXPECT_TRUE(std::regex_match(v, re));
}