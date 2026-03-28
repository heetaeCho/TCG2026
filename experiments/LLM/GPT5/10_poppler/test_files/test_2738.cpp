// File: test_parseargs_printUsage_2738.cc
#include <gtest/gtest.h>

#include <cstddef>
#include <string>
#include <vector>

#include "parseargs.h" // from ./TestProjects/poppler/utils/parseargs.h

// printUsage is implemented in ./TestProjects/poppler/utils/parseargs.cc
void printUsage(const char *program, const char *otherArgs, const ArgDesc *args);

namespace {

static std::vector<std::string> SplitLines(const std::string &s) {
  std::vector<std::string> out;
  std::string cur;
  for (char c : s) {
    if (c == '\n') {
      out.push_back(cur);
      cur.clear();
    } else {
      cur.push_back(c);
    }
  }
  // Note: printUsage ends each line with '\n', so trailing cur is usually empty.
  if (!cur.empty()) out.push_back(cur);
  return out;
}

static size_t FindOrNpos(const std::string &haystack, const std::string &needle) {
  return haystack.find(needle);
}

static size_t FindCharOrNpos(const std::string &haystack, char c) {
  return haystack.find(c);
}

} // namespace

TEST(PrintUsageTest_2738, PrintsHeaderWithOtherArgs_2738) {
  ArgDesc args[] = {
      {"-i", argInt, nullptr, "an int"},
      {nullptr, argFlag, nullptr, nullptr},
  };

  testing::internal::CaptureStderr();
  printUsage("myprog", "FILE [FILE...]", args);
  std::string err = testing::internal::GetCapturedStderr();

  auto lines = SplitLines(err);
  ASSERT_GE(lines.size(), 2u);

  // Header line should include program name and otherArgs (if provided).
  EXPECT_NE(FindOrNpos(lines[0], "Usage: myprog [options] FILE [FILE...]"), std::string::npos);

  // Should list the arg token on its own line.
  EXPECT_NE(FindOrNpos(lines[1], " -i"), std::string::npos);
}

TEST(PrintUsageTest_2738, PrintsHeaderWithoutOtherArgs_2738) {
  ArgDesc args[] = {
      {"-v", argFlag, nullptr, "verbose"},
      {nullptr, argFlag, nullptr, nullptr},
  };

  testing::internal::CaptureStderr();
  printUsage("tool", nullptr, args);
  std::string err = testing::internal::GetCapturedStderr();

  auto lines = SplitLines(err);
  ASSERT_GE(lines.size(), 2u);

  // Header line should NOT contain extra trailing "other args".
  EXPECT_NE(FindOrNpos(lines[0], "Usage: tool [options]"), std::string::npos);
  // And it should end right after "[options]" (no extra token).
  // (We only check that there isn't a double-space or placeholder-like addition.)
  EXPECT_EQ(FindOrNpos(lines[0], "Usage: tool [options] "), std::string::npos);
}

TEST(PrintUsageTest_2738, MapsArgKindsToTypeSuffixes_2738) {
  ArgDesc args[] = {
      {"-n", argInt, nullptr, "count"},
      {"-nd", argIntDummy, nullptr, "count dummy"},
      {"-f", argFP, nullptr, "factor"},
      {"-fd", argFPDummy, nullptr, "factor dummy"},
      {"-s", argString, nullptr, "str"},
      {"-sd", argStringDummy, nullptr, "str dummy"},
      {"-g", argGooString, nullptr, "goo"},
      {"-flag", argFlag, nullptr, "flag"},
      {"-flagd", argFlagDummy, nullptr, "flag dummy"},
      {nullptr, argFlag, nullptr, nullptr},
  };

  testing::internal::CaptureStderr();
  printUsage("p", nullptr, args);
  std::string err = testing::internal::GetCapturedStderr();
  auto lines = SplitLines(err);

  // Expect: header + 9 arg lines = 10 lines
  ASSERT_GE(lines.size(), 10u);

  // Each line should include the arg token and the expected type marker (or not).
  EXPECT_NE(FindOrNpos(lines[1], " -n"), std::string::npos);
  EXPECT_NE(FindOrNpos(lines[1], "<int>"), std::string::npos);

  EXPECT_NE(FindOrNpos(lines[2], " -nd"), std::string::npos);
  EXPECT_NE(FindOrNpos(lines[2], "<int>"), std::string::npos);

  EXPECT_NE(FindOrNpos(lines[3], " -f"), std::string::npos);
  EXPECT_NE(FindOrNpos(lines[3], "<fp>"), std::string::npos);

  EXPECT_NE(FindOrNpos(lines[4], " -fd"), std::string::npos);
  EXPECT_NE(FindOrNpos(lines[4], "<fp>"), std::string::npos);

  EXPECT_NE(FindOrNpos(lines[5], " -s"), std::string::npos);
  EXPECT_NE(FindOrNpos(lines[5], "<string>"), std::string::npos);

  EXPECT_NE(FindOrNpos(lines[6], " -sd"), std::string::npos);
  EXPECT_NE(FindOrNpos(lines[6], "<string>"), std::string::npos);

  EXPECT_NE(FindOrNpos(lines[7], " -g"), std::string::npos);
  EXPECT_NE(FindOrNpos(lines[7], "<string>"), std::string::npos);

  EXPECT_NE(FindOrNpos(lines[8], " -flag"), std::string::npos);
  EXPECT_EQ(FindOrNpos(lines[8], "<int>"), std::string::npos);
  EXPECT_EQ(FindOrNpos(lines[8], "<fp>"), std::string::npos);
  EXPECT_EQ(FindOrNpos(lines[8], "<string>"), std::string::npos);

  EXPECT_NE(FindOrNpos(lines[9], " -flagd"), std::string::npos);
  EXPECT_EQ(FindOrNpos(lines[9], "<int>"), std::string::npos);
  EXPECT_EQ(FindOrNpos(lines[9], "<fp>"), std::string::npos);
  EXPECT_EQ(FindOrNpos(lines[9], "<string>"), std::string::npos);
}

TEST(PrintUsageTest_2738, OmitsUsageTextWhenNull_2738) {
  ArgDesc args[] = {
      {"-x", argInt, nullptr, nullptr},          // no usage
      {"-y", argString, nullptr, "has usage"},   // has usage
      {nullptr, argFlag, nullptr, nullptr},
  };

  testing::internal::CaptureStderr();
  printUsage("p", nullptr, args);
  std::string err = testing::internal::GetCapturedStderr();
  auto lines = SplitLines(err);

  ASSERT_GE(lines.size(), 3u);

  // Line for -x should not contain ":"
  EXPECT_NE(FindOrNpos(lines[1], " -x"), std::string::npos);
  EXPECT_NE(FindOrNpos(lines[1], "<int>"), std::string::npos);
  EXPECT_EQ(FindCharOrNpos(lines[1], ':'), std::string::npos);

  // Line for -y should contain ": has usage"
  EXPECT_NE(FindOrNpos(lines[2], " -y"), std::string::npos);
  EXPECT_NE(FindOrNpos(lines[2], "<string>"), std::string::npos);
  EXPECT_NE(FindOrNpos(lines[2], ": has usage"), std::string::npos);
}

TEST(PrintUsageTest_2738, AlignsUsageColonsForDifferentArgLengths_2738) {
  // Boundary-ish formatting check: args with different token lengths but both with usage.
  ArgDesc args[] = {
      {"-a", argInt, nullptr, "short"},
      {"--a-very-long-option", argInt, nullptr, "long"},
      {nullptr, argFlag, nullptr, nullptr},
  };

  testing::internal::CaptureStderr();
  printUsage("p", nullptr, args);
  std::string err = testing::internal::GetCapturedStderr();
  auto lines = SplitLines(err);

  ASSERT_GE(lines.size(), 3u);

  const std::string &lineShort = lines[1];
  const std::string &lineLong = lines[2];

  // Both should have a ':' since usage is non-null.
  size_t colonShort = FindCharOrNpos(lineShort, ':');
  size_t colonLong = FindCharOrNpos(lineLong, ':');
  ASSERT_NE(colonShort, std::string::npos);
  ASSERT_NE(colonLong, std::string::npos);

  // Observable behavior: usage text columns should be aligned across options.
  EXPECT_EQ(colonShort, colonLong);

  // And both should include the expected type marker for argInt.
  EXPECT_NE(FindOrNpos(lineShort, "<int>"), std::string::npos);
  EXPECT_NE(FindOrNpos(lineLong, "<int>"), std::string::npos);
}

TEST(PrintUsageTest_2738, HandlesSingleArgumentList_2738) {
  // Boundary: only one argument plus terminator.
  ArgDesc args[] = {
      {"--only", argFlag, nullptr, "just one"},
      {nullptr, argFlag, nullptr, nullptr},
  };

  testing::internal::CaptureStderr();
  printUsage("solo", nullptr, args);
  std::string err = testing::internal::GetCapturedStderr();
  auto lines = SplitLines(err);

  ASSERT_EQ(lines.size(), 2u);
  EXPECT_NE(FindOrNpos(lines[0], "Usage: solo [options]"), std::string::npos);
  EXPECT_NE(FindOrNpos(lines[1], " --only"), std::string::npos);
  EXPECT_NE(FindOrNpos(lines[1], ": just one"), std::string::npos);
}