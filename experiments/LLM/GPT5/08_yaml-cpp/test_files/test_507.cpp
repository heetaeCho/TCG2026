// TEST_ID: 507
#include <gtest/gtest.h>

#include <sstream>
#include <string>

#include "yaml-cpp/parser.h"

namespace {

class ParserPrintTokensTest_507 : public ::testing::Test {
protected:
  static std::string PrintToString(YAML::Parser& parser) {
    std::ostringstream out;
    parser.PrintTokens(out);
    return out.str();
  }
};

TEST_F(ParserPrintTokensTest_507, DefaultConstructed_NoScanner_WritesNothing_507) {
  YAML::Parser parser;
  std::ostringstream out;

  EXPECT_NO_THROW(parser.PrintTokens(out));
  EXPECT_TRUE(out.str().empty());
}

TEST_F(ParserPrintTokensTest_507, LoadWithSimpleYaml_PrintsSomethingAndConsumesTokens_507) {
  YAML::Parser parser;

  std::istringstream in("a: 1\nb: 2\n");
  ASSERT_NO_THROW(parser.Load(in));

  const std::string first = PrintToString(parser);
  // We don't assume the exact token text, only that something is printed for non-empty YAML.
  EXPECT_FALSE(first.empty());
  // Each printed token is followed by '\n' in the implementation.
  EXPECT_EQ(first.back(), '\n');

  const std::string second = PrintToString(parser);
  // Observable behavior: tokens are popped; subsequent call should produce nothing.
  EXPECT_TRUE(second.empty());
}

TEST_F(ParserPrintTokensTest_507, LoadWithEmptyStream_DoesNotThrow_AndIsIdempotentAfterFirstCall_507) {
  YAML::Parser parser;

  std::istringstream in("");
  ASSERT_NO_THROW(parser.Load(in));

  std::ostringstream out1;
  EXPECT_NO_THROW(parser.PrintTokens(out1));

  // Regardless of whether the scanner produces zero or some stream boundary tokens,
  // PrintTokens() consumes what it prints. A second call should therefore be empty.
  std::ostringstream out2;
  EXPECT_NO_THROW(parser.PrintTokens(out2));
  EXPECT_TRUE(out2.str().empty());
}

TEST_F(ParserPrintTokensTest_507, ReloadResetsTokens_PrintTokensProducesOutputAgain_507) {
  YAML::Parser parser;

  std::istringstream in1("key: value\n");
  ASSERT_NO_THROW(parser.Load(in1));
  const std::string firstRun = PrintToString(parser);

  // Consume any tokens from the first load.
  EXPECT_TRUE(PrintToString(parser).empty());

  // Reload with another document; PrintTokens should have something to do again.
  std::istringstream in2("- a\n- b\n");
  ASSERT_NO_THROW(parser.Load(in2));
  const std::string secondRun = PrintToString(parser);

  // We avoid asserting exact tokenization; just verify observable change after reload.
  EXPECT_FALSE(secondRun.empty());

  // If both runs produced output, both should end with '\n' due to the implementation.
  if (!firstRun.empty()) {
    EXPECT_EQ(firstRun.back(), '\n');
  }
  EXPECT_EQ(secondRun.back(), '\n');

  // After printing, tokens should be consumed again.
  EXPECT_TRUE(PrintToString(parser).empty());
}

}  // namespace