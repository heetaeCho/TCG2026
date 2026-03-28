// TEST_ID: 142
#include <gtest/gtest.h>

#include "exp.h"           // YAML::Exp::Tag()
#include "regex_yaml.h"    // YAML::RegEx

namespace {

class TagExpTest_142 : public ::testing::Test {
 protected:
  static const YAML::RegEx& Tag() { return YAML::Exp::Tag(); }
};

TEST_F(TagExpTest_142, ReturnsSameStaticInstance_142) {
  const YAML::RegEx* p1 = &Tag();
  const YAML::RegEx* p2 = &Tag();
  EXPECT_EQ(p1, p2);
}

TEST_F(TagExpTest_142, MatchesAllowedPunctuationCharacters_142) {
  const std::string allowed = "#;/?:@&=+$_.~*'()";
  for (char ch : allowed) {
    EXPECT_TRUE(Tag().Matches(ch)) << "Expected Tag() to match allowed char: '" << ch << "'";
  }
}

TEST_F(TagExpTest_142, DoesNotMatchWhitespaceCharacters_142) {
  EXPECT_FALSE(Tag().Matches(' '));
  EXPECT_FALSE(Tag().Matches('\t'));
  EXPECT_FALSE(Tag().Matches('\n'));
  EXPECT_FALSE(Tag().Matches('\r'));
}

TEST_F(TagExpTest_142, MatchesValidPercentEncodingWithDigits_142) {
  // Percent-encoded form: '%' + Hex() + Hex()
  EXPECT_TRUE(Tag().Matches(std::string("%20")));
  EXPECT_TRUE(Tag().Matches(std::string("%00")));
  EXPECT_TRUE(Tag().Matches(std::string("%99")));
}

TEST_F(TagExpTest_142, DoesNotMatchInvalidOrIncompletePercentEncoding_142) {
  EXPECT_FALSE(Tag().Matches(std::string("%")));
  EXPECT_FALSE(Tag().Matches(std::string("%2")));
  EXPECT_FALSE(Tag().Matches(std::string("2F")));
  EXPECT_FALSE(Tag().Matches(std::string("%2G")));  // non-hex
  EXPECT_FALSE(Tag().Matches(std::string("%G2")));  // non-hex
}

TEST_F(TagExpTest_142, DoesNotMatchEmptyString_142) {
  EXPECT_FALSE(Tag().Matches(std::string("")));
}

TEST_F(TagExpTest_142, DoesNotMatchMultiCharacterSequenceOfAllowedPunctuation_142) {
  // Tag() is defined as an OR of components that include single-character sets and a 3-char %HH sequence.
  // This test ensures it does not claim to match an entire multi-character punctuation string.
  EXPECT_FALSE(Tag().Matches(std::string("##")));
  EXPECT_FALSE(Tag().Matches(std::string("()")));
  EXPECT_FALSE(Tag().Matches(std::string("@@")));
}

}  // namespace
