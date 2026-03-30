// File: ./TestProjects/yaml-cpp/test/parser_bool_test_504.cpp

#include <gtest/gtest.h>

#include <sstream>

#include "yaml-cpp/parser.h"

namespace {

bool ToBool(const YAML::Parser& p) { return static_cast<bool>(p); }

class ParserBoolTest_504 : public ::testing::Test {};

TEST_F(ParserBoolTest_504, DefaultConstructedParserIsFalse_504) {
  YAML::Parser p;
  EXPECT_FALSE(ToBool(p));
}

TEST_F(ParserBoolTest_504, ConstructedWithStreamIsTrueEvenForEmptyInput_504) {
  // Even an empty YAML stream typically yields at least stream start/end tokens,
  // so the scanner shouldn't be empty if it exists.
  std::istringstream in("");
  YAML::Parser p(in);

  EXPECT_TRUE(ToBool(p));
}

TEST_F(ParserBoolTest_504, LoadOnDefaultConstructedMakesParserTruthy_504) {
  YAML::Parser p;
  EXPECT_FALSE(ToBool(p));  // no scanner yet

  std::istringstream in("key: value\n");
  ASSERT_NO_THROW(p.Load(in));
  EXPECT_TRUE(ToBool(p));
}

TEST_F(ParserBoolTest_504, OperatorBoolIsConstAndDoesNotThrow_504) {
  std::istringstream in("a: b\n");
  YAML::Parser p(in);

  const YAML::Parser& cp = p;
  EXPECT_NO_THROW({ (void)ToBool(cp); });
  EXPECT_TRUE(ToBool(cp));
}

TEST_F(ParserBoolTest_504, MultipleLoadsKeepParserInValidTruthyState_504) {
  YAML::Parser p;

  std::istringstream in1("a: 1\n");
  ASSERT_NO_THROW(p.Load(in1));
  EXPECT_TRUE(ToBool(p));

  std::istringstream in2("b: 2\n");
  ASSERT_NO_THROW(p.Load(in2));
  EXPECT_TRUE(ToBool(p));
}

}  // namespace