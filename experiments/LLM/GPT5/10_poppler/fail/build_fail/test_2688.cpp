// parse_antialias_option_test_2688.cc
#include <gtest/gtest.h>

#include <string>

// pdftocairo.cc is a utility with its own main() in many builds.
// Rename main to avoid duplicate symbol when including the .cc in unit tests.
#define main pdftocairo_main_for_test_2688
#include "TestProjects/poppler/utils/pdftocairo.cc"
#undef main

namespace {

class ParseAntialiasOptionTest_2688 : public ::testing::Test {
protected:
  // Returns pointer to first option (if any), else nullptr.
  static const AntialiasOption *FirstOption() {
    const AntialiasOption *opt = antialiasOptions;
    return (opt && opt->name) ? opt : nullptr;
  }

  // Returns pointer to last named option (if any), else nullptr.
  static const AntialiasOption *LastNamedOption() {
    const AntialiasOption *opt = antialiasOptions;
    if (!opt || !opt->name) {
      return nullptr;
    }
    const AntialiasOption *last = opt;
    while (opt->name) {
      last = opt;
      ++opt;
    }
    return last;
  }

  // Counts the number of named options.
  static int CountNamedOptions() {
    int count = 0;
    const AntialiasOption *opt = antialiasOptions;
    while (opt && opt->name) {
      ++count;
      ++opt;
    }
    return count;
  }

  void SetUp() override {
    // Ensure deterministic starting point for antialiasEnum across tests.
    antialiasEnum = -1234567;
    antialias = GooString(""); // move-assign from temporary
  }
};

TEST_F(ParseAntialiasOptionTest_2688, ValidFirstOptionReturnsTrueAndSetsEnum_2688) {
  const AntialiasOption *opt = FirstOption();
  ASSERT_NE(opt, nullptr) << "antialiasOptions should contain at least one named option for this test.";

  antialiasEnum = -999;
  antialias = GooString(opt->name);

  const bool ok = parseAntialiasOption();

  EXPECT_TRUE(ok);
  EXPECT_EQ(antialiasEnum, opt->value);
}

TEST_F(ParseAntialiasOptionTest_2688, ValidLastOptionReturnsTrueAndSetsEnum_2688) {
  const AntialiasOption *opt = LastNamedOption();
  ASSERT_NE(opt, nullptr) << "antialiasOptions should contain at least one named option for this test.";

  antialiasEnum = -888;
  antialias = GooString(opt->name);

  const bool ok = parseAntialiasOption();

  EXPECT_TRUE(ok);
  EXPECT_EQ(antialiasEnum, opt->value);
}

TEST_F(ParseAntialiasOptionTest_2688, InvalidOptionReturnsFalseAndPrintsErrorToStderr_2688) {
  // Choose a value very unlikely to be a valid option name.
  antialias = GooString("___definitely_not_a_valid_antialias_option___2688");

  ::testing::internal::CaptureStderr();
  const bool ok = parseAntialiasOption();
  const std::string err = ::testing::internal::GetCapturedStderr();

  EXPECT_FALSE(ok);
  EXPECT_NE(err.find("Error: Invalid antialias option"), std::string::npos);
  EXPECT_NE(err.find("Valid options are:"), std::string::npos);

  // If there is at least one valid option, its name should appear in the printed list.
  const AntialiasOption *first = FirstOption();
  if (first) {
    EXPECT_NE(err.find(first->name), std::string::npos);
  }
}

TEST_F(ParseAntialiasOptionTest_2688, EmptyOptionStringReturnsFalseAndPrintsError_2688) {
  antialias = GooString("");

  ::testing::internal::CaptureStderr();
  const bool ok = parseAntialiasOption();
  const std::string err = ::testing::internal::GetCapturedStderr();

  EXPECT_FALSE(ok);
  EXPECT_NE(err.find("Error: Invalid antialias option"), std::string::npos);
  EXPECT_NE(err.find("Valid options are:"), std::string::npos);
}

TEST_F(ParseAntialiasOptionTest_2688, ValidOptionsListIsPrintedOnePerLineOnError_2688) {
  // This test focuses on the observable external interaction (stderr output),
  // without assuming specific option names.
  antialias = GooString("___invalid___2688");

  const int optionCount = CountNamedOptions();
  ASSERT_GE(optionCount, 0);

  ::testing::internal::CaptureStderr();
  (void)parseAntialiasOption();
  const std::string err = ::testing::internal::GetCapturedStderr();

  // "Valid options are:" plus at least that many lines prefixed with a space.
  EXPECT_NE(err.find("Valid options are:"), std::string::npos);

  // Count occurrences of "\n " (newline then a space) after the "Valid options are:" section.
  // This is a lightweight way to validate the per-line formatting.
  const std::string marker = "Valid options are:\n";
  const size_t pos = err.find(marker);
  ASSERT_NE(pos, std::string::npos);

  int lines = 0;
  for (size_t i = pos + marker.size(); i + 1 < err.size(); ++i) {
    if (err[i] == '\n' && err[i + 1] == ' ') {
      ++lines;
    }
  }

  // If there are N options, there should be at least N lines starting with " <name>".
  // (Some builds may include extra newlines; we only assert the lower bound.)
  EXPECT_GE(lines, optionCount);
}

} // namespace