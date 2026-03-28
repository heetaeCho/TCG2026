// File: ./TestProjects/yaml-cpp/util/parse_test.cpp

#include <gtest/gtest.h>

#include <iostream>
#include <sstream>
#include <string>

// Function under test (defined in ./TestProjects/yaml-cpp/util/parse.cpp)
void parse(std::istream& input);

namespace {

class StreamRedirect {
public:
  explicit StreamRedirect(std::ostream& target)
      : target_(target), old_buf_(target.rdbuf(capture_.rdbuf())) {}

  ~StreamRedirect() { target_.rdbuf(old_buf_); }

  std::string str() const { return capture_.str(); }

private:
  std::ostream& target_;
  std::streambuf* old_buf_;
  std::ostringstream capture_;
};

static bool EndsWithNewline(const std::string& s) {
  return !s.empty() && s.back() == '\n';
}

class ParseTest_676 : public ::testing::Test {};

}  // namespace

TEST_F(ParseTest_676, PrintsScalarYamlToStdout_676) {
  std::istringstream input("hello");

  StreamRedirect out(std::cout);
  StreamRedirect err(std::cerr);

  EXPECT_NO_THROW(parse(input));

  const std::string stdout_text = out.str();
  const std::string stderr_text = err.str();

  EXPECT_TRUE(stderr_text.empty());
  EXPECT_FALSE(stdout_text.empty());
  EXPECT_NE(stdout_text.find("hello"), std::string::npos);
  EXPECT_TRUE(EndsWithNewline(stdout_text));
}

TEST_F(ParseTest_676, PrintsMapYamlToStdout_676) {
  std::istringstream input("a: 1\nb: two\n");

  StreamRedirect out(std::cout);
  StreamRedirect err(std::cerr);

  EXPECT_NO_THROW(parse(input));

  const std::string stdout_text = out.str();
  const std::string stderr_text = err.str();

  EXPECT_TRUE(stderr_text.empty());
  EXPECT_FALSE(stdout_text.empty());

  // Don't over-specify formatting (emitter may choose spacing/order),
  // but key/value content should be present for valid YAML.
  EXPECT_NE(stdout_text.find("a"), std::string::npos);
  EXPECT_NE(stdout_text.find("1"), std::string::npos);
  EXPECT_NE(stdout_text.find("b"), std::string::npos);
  EXPECT_NE(stdout_text.find("two"), std::string::npos);
  EXPECT_TRUE(EndsWithNewline(stdout_text));
}

TEST_F(ParseTest_676, PrintsSequenceYamlToStdout_676) {
  std::istringstream input("- x\n- y\n- z\n");

  StreamRedirect out(std::cout);
  StreamRedirect err(std::cerr);

  EXPECT_NO_THROW(parse(input));

  const std::string stdout_text = out.str();
  const std::string stderr_text = err.str();

  EXPECT_TRUE(stderr_text.empty());
  EXPECT_FALSE(stdout_text.empty());

  EXPECT_NE(stdout_text.find("x"), std::string::npos);
  EXPECT_NE(stdout_text.find("y"), std::string::npos);
  EXPECT_NE(stdout_text.find("z"), std::string::npos);
  EXPECT_TRUE(EndsWithNewline(stdout_text));
}

TEST_F(ParseTest_676, InvalidYamlPrintsErrorToStderr_676) {
  // Unclosed sequence bracket should be a parse error.
  std::istringstream input("a: [1, 2\n");

  StreamRedirect out(std::cout);
  StreamRedirect err(std::cerr);

  EXPECT_NO_THROW(parse(input));  // parse() catches YAML::Exception internally

  const std::string stdout_text = out.str();
  const std::string stderr_text = err.str();

  EXPECT_TRUE(stdout_text.empty());
  EXPECT_FALSE(stderr_text.empty());
  EXPECT_TRUE(EndsWithNewline(stderr_text));
}

TEST_F(ParseTest_676, EmptyInputDoesNotThrowAndWritesSomeOutput_676) {
  // yaml-cpp behavior for empty input can vary (may emit "null", may error);
  // the observable contract for parse() is: it should not throw and it should
  // write either a document to stdout or an error to stderr.
  std::istringstream input("");

  StreamRedirect out(std::cout);
  StreamRedirect err(std::cerr);

  EXPECT_NO_THROW(parse(input));

  const std::string stdout_text = out.str();
  const std::string stderr_text = err.str();

  EXPECT_TRUE(!stdout_text.empty() || !stderr_text.empty());
  if (!stdout_text.empty()) {
    EXPECT_TRUE(EndsWithNewline(stdout_text));
  }
  if (!stderr_text.empty()) {
    EXPECT_TRUE(EndsWithNewline(stderr_text));
  }
}