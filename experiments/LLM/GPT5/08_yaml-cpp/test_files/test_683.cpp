// TEST_ID: 683
#include <gtest/gtest.h>

#include <sstream>
#include <string>
#include <type_traits>

#include <yaml-cpp/parser.h>

namespace {

class ParserCtorTest_683 : public ::testing::Test {
 protected:
  static std::string PrintTokensToString(YAML::Parser& p) {
    std::ostringstream out;
    p.PrintTokens(out);
    return out.str();
  }
};

TEST_F(ParserCtorTest_683, TypeTraits_CopyAndMoveAreDeleted_683) {
  EXPECT_FALSE((std::is_copy_constructible<YAML::Parser>::value));
  EXPECT_FALSE((std::is_copy_assignable<YAML::Parser>::value));
  EXPECT_FALSE((std::is_move_constructible<YAML::Parser>::value));
  EXPECT_FALSE((std::is_move_assignable<YAML::Parser>::value));
}

TEST_F(ParserCtorTest_683, CtorWithStreamMatchesDefaultThenLoad_ForSimpleYaml_683) {
  const std::string yaml = "a: b\n";

  std::istringstream in1(yaml);
  YAML::Parser p_from_ctor(in1);

  std::istringstream in2(yaml);
  YAML::Parser p_from_load;
  p_from_load.Load(in2);

  // Observable behavior should match between:
  //   Parser(in)  vs  Parser(); Load(in)
  EXPECT_EQ(static_cast<bool>(p_from_ctor), static_cast<bool>(p_from_load));

  const std::string tokens_ctor = PrintTokensToString(p_from_ctor);
  const std::string tokens_load = PrintTokensToString(p_from_load);
  EXPECT_EQ(tokens_ctor, tokens_load);
}

TEST_F(ParserCtorTest_683, CtorWithStreamMatchesDefaultThenLoad_ForEmptyStream_683) {
  const std::string yaml = "";

  std::istringstream in1(yaml);
  YAML::Parser p_from_ctor(in1);

  std::istringstream in2(yaml);
  YAML::Parser p_from_load;
  p_from_load.Load(in2);

  EXPECT_EQ(static_cast<bool>(p_from_ctor), static_cast<bool>(p_from_load));

  const std::string tokens_ctor = PrintTokensToString(p_from_ctor);
  const std::string tokens_load = PrintTokensToString(p_from_load);
  EXPECT_EQ(tokens_ctor, tokens_load);
}

TEST_F(ParserCtorTest_683, CtorWithStreamThrowsWhenLoadWouldThrow_ForMalformedYaml_683) {
  // Use an obviously malformed YAML snippet. We don't assume exception types here,
  // only that behavior is consistent between the two entry points.
  const std::string yaml = "a: [\n";

  {
    std::istringstream in_ctor(yaml);
    EXPECT_ANY_THROW({
      YAML::Parser p(in_ctor);
      (void)p;
    });
  }

  {
    std::istringstream in_load(yaml);
    YAML::Parser p;
    EXPECT_ANY_THROW({
      p.Load(in_load);
    });
  }
}

TEST_F(ParserCtorTest_683, OperatorBoolIsCallableBeforeAndAfterLoad_683) {
  // This is a pure interface smoke test: we don't assert a specific value.
  YAML::Parser p;
  const bool before = static_cast<bool>(p);
  (void)before;

  std::istringstream in("k: v\n");
  EXPECT_NO_THROW(p.Load(in));

  const bool after = static_cast<bool>(p);
  (void)after;
}

}  // namespace