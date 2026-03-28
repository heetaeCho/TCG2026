// TEST_ID: 4
#include <gtest/gtest.h>

#include <sstream>
#include <string>
#include <vector>

#include "token.h"  // from ./TestProjects/yaml-cpp/src/token.h

namespace {

TEST(TokenOstreamTest_4, OutputsTypeAndValueWithoutParams_4) {
  YAML::Mark mark;  // assume default-constructible in the codebase
  YAML::Token token(YAML::DIRECTIVE, mark);

  token.value = "hello";

  std::ostringstream oss;
  oss << token;

  const std::string expected =
      std::string(YAML::TokenNames[token.type]) + ": " + token.value;
  EXPECT_EQ(oss.str(), expected);
}

TEST(TokenOstreamTest_4, OutputsTypeValueAndParamsSeparatedBySpaces_4) {
  YAML::Mark mark;
  YAML::Token token(YAML::SCALAR, mark);

  token.value = "v";
  token.params = {"p1", "p2"};

  std::ostringstream oss;
  oss << token;

  const std::string expected =
      std::string(YAML::TokenNames[token.type]) + ": " + token.value + " p1 p2";
  EXPECT_EQ(oss.str(), expected);
}

TEST(TokenOstreamTest_4, EmptyValueStillPrintsColonSpace_4) {
  YAML::Mark mark;
  YAML::Token token(YAML::DOC_START, mark);

  token.value.clear();
  token.params.clear();

  std::ostringstream oss;
  oss << token;

  const std::string expected =
      std::string(YAML::TokenNames[token.type]) + ": ";
  EXPECT_EQ(oss.str(), expected);
}

TEST(TokenOstreamTest_4, EmptyParamProducesTrailingSpace_4) {
  YAML::Mark mark;
  YAML::Token token(YAML::TAG, mark);

  token.value = "x";
  token.params = {""};

  std::ostringstream oss;
  oss << token;

  // A space is always printed before each param, even if the param itself is empty.
  const std::string expected =
      std::string(YAML::TokenNames[token.type]) + ": " + token.value + " ";
  EXPECT_EQ(oss.str(), expected);
}

TEST(TokenOstreamTest_4, StreamingTwiceAppendsTextTwice_4) {
  YAML::Mark mark;
  YAML::Token token(YAML::ALIAS, mark);

  token.value = "name";
  token.params = {"p"};

  std::ostringstream oss;
  oss << token << token;

  const std::string once =
      std::string(YAML::TokenNames[token.type]) + ": " + token.value + " p";
  EXPECT_EQ(oss.str(), once + once);
}

}  // namespace
