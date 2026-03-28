// TEST_ID: 112
#include <gtest/gtest.h>

#include <string>
#include <vector>

#include "regex_yaml.h"
#include "regeximpl.h"
#include "stringsource.h"

namespace YAML {
namespace {

class RegExMatchStringWrapperTest_112 : public ::testing::Test {};

TEST_F(RegExMatchStringWrapperTest_112, DelegatesToSourceMatchForSimpleInput_112) {
  const RegEx ex('a');

  const std::string s = "abc";
  const StringCharSource src(s.c_str(), s.size());

  const int via_string = ex.Match(s);
  const int via_source = ex.Match(src);

  EXPECT_EQ(via_string, via_source);
}

TEST_F(RegExMatchStringWrapperTest_112, WorksWithEmptyString_112) {
  const RegEx ex('a');

  const std::string s;
  const StringCharSource src(s.c_str(), s.size());

  EXPECT_EQ(ex.Match(s), ex.Match(src));
}

TEST_F(RegExMatchStringWrapperTest_112, HandlesEmbeddedNullCharacters_112) {
  // std::string may contain embedded '\0'. The wrapper uses c_str()+size, so the
  // size must be honored consistently vs. passing an explicit StringCharSource.
  const RegEx ex('a');

  const std::string s(std::string("a\0b", 3));
  const StringCharSource src(s.data(), s.size());  // explicit pointer+size

  EXPECT_EQ(ex.Match(s), ex.Match(src));
}

TEST_F(RegExMatchStringWrapperTest_112, HandlesVariousSizesConsistently_112) {
  const RegEx ex('x');

  const std::vector<std::string> inputs = {
      "", "x", "xyz", std::string(1024, 'x'), std::string(2048, 'y'),
  };

  for (const auto& s : inputs) {
    const StringCharSource src(s.c_str(), s.size());
    EXPECT_EQ(ex.Match(s), ex.Match(src)) << "size=" << s.size();
  }
}

TEST_F(RegExMatchStringWrapperTest_112, DoesNotThrowForValidStrings_112) {
  const RegEx ex('z');

  const std::vector<std::string> inputs = {
      "", "z", "no-match-here", std::string("z\0z", 3), std::string(4096, 'z'),
  };

  for (const auto& s : inputs) {
    EXPECT_NO_THROW({
      (void)ex.Match(s);
    }) << "input size=" << s.size();

    const StringCharSource src(s.data(), s.size());
    EXPECT_NO_THROW({
      (void)ex.Match(src);
    }) << "source size=" << s.size();
  }
}

}  // namespace
}  // namespace YAML
