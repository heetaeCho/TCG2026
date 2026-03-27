// TEST_ID: 108
#include <gtest/gtest.h>

#include <string>
#include <vector>

// Ensure RegEx is fully declared before including the inline implementation.
#include "TestProjects/yaml-cpp/src/regex_yaml.h"
#include "TestProjects/yaml-cpp/src/regeximpl.h"

namespace {

class RegExImplTest_108 : public ::testing::Test {};

TEST_F(RegExImplTest_108, MatchesCharEqualsMatchesSingleCharString_108) {
  const YAML::RegEx ex;  // Default-constructed; we don't assume what it matches.

  const char ch = 'a';
  const std::string s(1, ch);

  // The inline method should behave identically to calling Matches(string)
  // with a single-character string created from ch.
  EXPECT_EQ(ex.Matches(ch), ex.Matches(s));
}

TEST_F(RegExImplTest_108, MatchesCharEqualsMatchesSingleCharString_NullChar_108) {
  const YAML::RegEx ex;

  const char ch = '\0';
  const std::string s(1, ch);

  EXPECT_EQ(ex.Matches(ch), ex.Matches(s));
}

TEST_F(RegExImplTest_108, MatchesCharEqualsMatchesSingleCharString_HighBitChar_108) {
  const YAML::RegEx ex;

  // Use a value that may be negative when char is signed; still a valid char value.
  const unsigned char uch = 0xFF;
  const char ch = static_cast<char>(uch);
  const std::string s(1, ch);

  EXPECT_EQ(ex.Matches(ch), ex.Matches(s));
}

TEST_F(RegExImplTest_108, MatchesCharEqualsMatchesSingleCharString_MultipleValues_108) {
  const YAML::RegEx ex;

  const std::vector<unsigned char> values = {
      0x00, 0x01, 0x0A, 0x20, 0x30, 0x41, 0x7F, 0x80, 0xFE, 0xFF,
  };

  for (unsigned char v : values) {
    const char ch = static_cast<char>(v);
    const std::string s(1, ch);
    EXPECT_EQ(ex.Matches(ch), ex.Matches(s)) << "value=" << static_cast<int>(v);
  }
}

}  // namespace
