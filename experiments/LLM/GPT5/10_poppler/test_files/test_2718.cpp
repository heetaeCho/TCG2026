// File: printencodings_test_2718.cc
#include <gtest/gtest.h>

#include <algorithm>
#include <cstddef>
#include <memory>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include "poppler/GlobalParams.h"

// Function under test (implemented in utils/printencodings.cc)
void printEncodings();

// globalParams is a global owned pointer used by printEncodings().
extern std::unique_ptr<GlobalParams> globalParams;

namespace {

class ScopedGlobalParamsSwap {
public:
  explicit ScopedGlobalParamsSwap(std::unique_ptr<GlobalParams> replacement)
      : saved_(std::move(globalParams))
  {
    globalParams = std::move(replacement);
  }

  ScopedGlobalParamsSwap(const ScopedGlobalParamsSwap &) = delete;
  ScopedGlobalParamsSwap &operator=(const ScopedGlobalParamsSwap &) = delete;

  ~ScopedGlobalParamsSwap() { globalParams = std::move(saved_); }

private:
  std::unique_ptr<GlobalParams> saved_;
};

static std::vector<std::string> SplitLines(const std::string &s)
{
  std::vector<std::string> out;
  std::istringstream iss(s);
  std::string line;
  while (std::getline(iss, line)) {
    if (!line.empty() && line.back() == '\r') {
      line.pop_back();
    }
    out.push_back(line);
  }
  // Note: std::getline drops the final empty line if the input ends with '\n'.
  return out;
}

static std::vector<std::string> SortedCopy(std::vector<std::string> v)
{
  std::sort(v.begin(), v.end());
  return v;
}

class PrintEncodingsTest_2718 : public ::testing::Test {};

} // namespace

TEST_F(PrintEncodingsTest_2718, PrintsHeaderAndEncodingsMatchSortedGetEncodingNames_2718)
{
  // Ensure globalParams is set for the test, but don't assume anything about its internal behavior.
  // Use a fresh instance to avoid cross-test interference from other tests.
  auto gp = std::make_unique<GlobalParams>(std::string{});
  ScopedGlobalParamsSwap swap(std::move(gp));

  ASSERT_NE(globalParams, nullptr);

  const std::vector<std::string> names = globalParams->getEncodingNames();
  const std::vector<std::string> expected_sorted = SortedCopy(names);

  testing::internal::CaptureStdout();
  EXPECT_NO_THROW(printEncodings());
  const std::string output = testing::internal::GetCapturedStdout();

  const std::vector<std::string> lines = SplitLines(output);
  ASSERT_GE(lines.size(), 1u);
  EXPECT_EQ(lines[0], "Available encodings are:");

  // Remaining lines should be exactly the sorted encoding names.
  std::vector<std::string> printed;
  for (size_t i = 1; i < lines.size(); ++i) {
    // Each encoding is printed on its own line; empty encoding names (if any) would appear as empty.
    printed.push_back(lines[i]);
  }

  EXPECT_EQ(printed, expected_sorted);
  // Also validate the count relationship: 1 header line + N names.
  EXPECT_EQ(printed.size(), names.size());
}

TEST_F(PrintEncodingsTest_2718, OutputIsLexicographicallyNonDecreasingAfterHeader_2718)
{
  auto gp = std::make_unique<GlobalParams>(std::string{});
  ScopedGlobalParamsSwap swap(std::move(gp));

  ASSERT_NE(globalParams, nullptr);

  testing::internal::CaptureStdout();
  printEncodings();
  const std::string output = testing::internal::GetCapturedStdout();
  const std::vector<std::string> lines = SplitLines(output);

  ASSERT_GE(lines.size(), 1u);
  ASSERT_EQ(lines[0], "Available encodings are:");

  // Boundary-friendly property check: regardless of how many encodings exist,
  // lines after the header should be in nondecreasing lexicographic order.
  for (size_t i = 2; i < lines.size(); ++i) {
    EXPECT_LE(lines[i - 1], lines[i]);
  }
}

TEST_F(PrintEncodingsTest_2718, PrintsExactlyOneLinePerEncodingPlusHeader_2718)
{
  auto gp = std::make_unique<GlobalParams>(std::string{});
  ScopedGlobalParamsSwap swap(std::move(gp));

  ASSERT_NE(globalParams, nullptr);

  const std::vector<std::string> names = globalParams->getEncodingNames();

  testing::internal::CaptureStdout();
  printEncodings();
  const std::string output = testing::internal::GetCapturedStdout();
  const std::vector<std::string> lines = SplitLines(output);

  // 1 header line + one line per encoding name.
  ASSERT_EQ(lines.size(), 1u + names.size());
  EXPECT_EQ(lines.front(), "Available encodings are:");
}