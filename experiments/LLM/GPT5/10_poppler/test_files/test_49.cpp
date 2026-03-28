// TEST_ID is 49
// Unit tests for FoFiType1Tokenizer::getToken()
// File: FoFiType1Tokenizer_getToken_test.cc

#include <gtest/gtest.h>

#include <optional>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

// The tokenizer is implemented in a .cc file in this project. To test it as a black box
// via its real implementation, include the production translation unit.
#include "TestProjects/poppler/fofi/FoFiType1.cc"

namespace {

class FoFiType1TokenizerTest_49 : public ::testing::Test {
protected:
  static std::vector<std::string> CollectTokens(FoFiType1Tokenizer& tok) {
    std::vector<std::string> out;
    for (;;) {
      std::optional<std::string_view> t = tok.getToken();
      if (!t.has_value()) break;
      out.emplace_back(t->begin(), t->end());
    }
    return out;
  }

  static FoFiType1Tokenizer MakeTok(const std::string& backing) {
    // Ensure the underlying characters outlive the tokenizer.
    std::string_view sv(backing);
    return FoFiType1Tokenizer(std::move(sv));
  }
};

TEST_F(FoFiType1TokenizerTest_49, EmptyInputReturnsNoToken_49) {
  const std::string s;
  auto tok = MakeTok(s);

  EXPECT_FALSE(tok.getToken().has_value());
  EXPECT_FALSE(tok.getToken().has_value());  // stable end-of-input behavior
}

TEST_F(FoFiType1TokenizerTest_49, OnlySeparatorsReturnsNoToken_49) {
  const std::string s = " \t\n\r \t";
  auto tok = MakeTok(s);

  EXPECT_FALSE(tok.getToken().has_value());
}

TEST_F(FoFiType1TokenizerTest_49, SingleTokenWithoutSeparators_49) {
  const std::string s = "abcDEF123";
  auto tok = MakeTok(s);

  auto t1 = tok.getToken();
  ASSERT_TRUE(t1.has_value());
  EXPECT_EQ(*t1, "abcDEF123");

  EXPECT_FALSE(tok.getToken().has_value());
}

TEST_F(FoFiType1TokenizerTest_49, LeadingSeparatorsAreSkipped_49) {
  const std::string s = "   \t\n\rhello";
  auto tok = MakeTok(s);

  auto t1 = tok.getToken();
  ASSERT_TRUE(t1.has_value());
  EXPECT_EQ(*t1, "hello");

  EXPECT_FALSE(tok.getToken().has_value());
}

TEST_F(FoFiType1TokenizerTest_49, TrailingSeparatorsDoNotProduceEmptyToken_49) {
  const std::string s = "a b  \t\n\r";
  auto tok = MakeTok(s);

  auto tokens = CollectTokens(tok);
  ASSERT_EQ(tokens.size(), 2u);
  EXPECT_EQ(tokens[0], "a");
  EXPECT_EQ(tokens[1], "b");
}

TEST_F(FoFiType1TokenizerTest_49, MultipleSeparatorsBetweenTokensProduceNoEmptyTokens_49) {
  const std::string s = "a   b\t\tc\n\n\rd";
  auto tok = MakeTok(s);

  auto tokens = CollectTokens(tok);
  ASSERT_EQ(tokens.size(), 4u);
  EXPECT_EQ(tokens[0], "a");
  EXPECT_EQ(tokens[1], "b");
  EXPECT_EQ(tokens[2], "c");
  EXPECT_EQ(tokens[3], "d");
}

TEST_F(FoFiType1TokenizerTest_49, MixedWhitespaceSeparatorsAreHandled_49) {
  const std::string s = "\ta\nb\rc d";
  auto tok = MakeTok(s);

  auto tokens = CollectTokens(tok);
  ASSERT_EQ(tokens.size(), 4u);
  EXPECT_EQ(tokens[0], "a");
  EXPECT_EQ(tokens[1], "b");
  EXPECT_EQ(tokens[2], "c");
  EXPECT_EQ(tokens[3], "d");
}

TEST_F(FoFiType1TokenizerTest_49, ReachingEndKeepsReturningNoToken_49) {
  const std::string s = "x";
  auto tok = MakeTok(s);

  auto t1 = tok.getToken();
  ASSERT_TRUE(t1.has_value());
  EXPECT_EQ(*t1, "x");

  EXPECT_FALSE(tok.getToken().has_value());
  EXPECT_FALSE(tok.getToken().has_value());
  EXPECT_FALSE(tok.getToken().has_value());
}

}  // namespace