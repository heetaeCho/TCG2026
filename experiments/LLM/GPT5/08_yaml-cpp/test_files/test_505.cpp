// TEST_ID: 505
#include <gtest/gtest.h>

#include <sstream>
#include <string>

#include "yaml-cpp/parser.h"

namespace {

class ParserLoadTest_505 : public ::testing::Test {
protected:
  static std::string PrintTokensToString(YAML::Parser& parser) {
    std::ostringstream out;
    parser.PrintTokens(out);
    return out.str();
  }
};

TEST_F(ParserLoadTest_505, LoadDoesNotThrowOnTypicalYaml_505) {
  YAML::Parser parser;

  std::istringstream in("a: 1\nb: 2\n");
  EXPECT_NO_THROW(parser.Load(in));

  // After a successful load, observable operations should remain callable.
  EXPECT_NO_THROW({
    (void)PrintTokensToString(parser);
  });
}

TEST_F(ParserLoadTest_505, LoadAllowsEmptyStream_505) {
  YAML::Parser parser;

  std::istringstream empty("");
  EXPECT_NO_THROW(parser.Load(empty));

  // Printing tokens from an empty input should be safe (content is implementation-defined).
  EXPECT_NO_THROW({
    (void)PrintTokensToString(parser);
  });
}

TEST_F(ParserLoadTest_505, MultipleLoadsAreSupportedAndDeterministicForSameInput_505) {
  YAML::Parser parser;

  std::istringstream first("a: 1\n");
  ASSERT_NO_THROW(parser.Load(first));
  const std::string tokens_after_first = PrintTokensToString(parser);

  // Reload with a different input; should not crash.
  std::istringstream second("b: 2\n");
  ASSERT_NO_THROW(parser.Load(second));
  const std::string tokens_after_second = PrintTokensToString(parser);

  // Determinism check: loading the same second input into a fresh parser should match.
  YAML::Parser fresh;
  std::istringstream second_again("b: 2\n");
  ASSERT_NO_THROW(fresh.Load(second_again));
  const std::string tokens_fresh_second = PrintTokensToString(fresh);

  EXPECT_EQ(tokens_after_second, tokens_fresh_second);

  // Do not assume how tokens look; just ensure the operation produced *some* observable output
  // or not—both are acceptable. This check avoids overfitting.
  (void)tokens_after_first;
}

TEST_F(ParserLoadTest_505, StreamConstructorMatchesManualLoadForSameContent_505) {
  const std::string yaml = "root:\n  k: v\n";

  // Construct via stream constructor.
  std::istringstream in_ctor(yaml);
  YAML::Parser by_ctor(in_ctor);

  // Construct default then Load.
  YAML::Parser by_load;
  std::istringstream in_load(yaml);
  ASSERT_NO_THROW(by_load.Load(in_load));

  // Compare observable state via operator bool (without assuming what true/false means).
  EXPECT_EQ(static_cast<bool>(by_ctor), static_cast<bool>(by_load));

  // Compare observable output of PrintTokens.
  const std::string ctor_tokens = PrintTokensToString(by_ctor);
  const std::string load_tokens = PrintTokensToString(by_load);
  EXPECT_EQ(ctor_tokens, load_tokens);
}

TEST_F(ParserLoadTest_505, LoadHandlesLargeInputWithoutThrow_505) {
  // Boundary-ish: large-ish YAML-like input.
  std::string big;
  big.reserve(200000);
  for (int i = 0; i < 5000; ++i) {
    big += "k";
    big += std::to_string(i);
    big += ": ";
    big += std::to_string(i);
    big += "\n";
  }

  YAML::Parser parser;
  std::istringstream in(big);

  EXPECT_NO_THROW(parser.Load(in));
  EXPECT_NO_THROW({
    (void)PrintTokensToString(parser);
  });
}

}  // namespace