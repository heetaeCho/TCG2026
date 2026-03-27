// File: util/histogram_to_string_test.cc
#include <gtest/gtest.h>
#include <regex>
#include <string>

#include "util/histogram.h"

using leveldb::Histogram;

namespace {

// Small helper to count occurrences of a substring in a string.
static int CountOccurrences(const std::string& s, const std::string& needle) {
  int count = 0;
  std::string::size_type pos = 0;
  while ((pos = s.find(needle, pos)) != std::string::npos) {
    ++count;
    ++pos;
  }
  return count;
}

}  // namespace

// Verifies header formatting and single-sample stats/lines.
// Focus: Count/Average/StdDev/Min/Median/Max formatting, presence of separator,
// a single histogram line with 100% and a 20-# bar (per printed formula).
TEST(HistogramToStringTest_437, SingleValueFormatting_437) {
  Histogram h;
  h.Clear();
  h.Add(1.23);

  const std::string out = h.ToString();

  // Header line expectations (fixed formatting as printed by ToString()).
  // Count printed with "%.0f", Average with "%.4f", StdDev with "%.2f".
  EXPECT_NE(std::string::npos, out.find("Count: 1 Average: 1.2300 StdDev: 0.00"))
      << out;

  // Min/Median/Max line uses "%.4f" each (and min==median==max for single value).
  EXPECT_NE(std::string::npos, out.find("Min: 1.2300 Median: 1.2300 Max: 1.2300"))
      << out;

  // Separator line must be present exactly as emitted.
  EXPECT_NE(std::string::npos,
            out.find("------------------------------------------------------"))
      << out;

  // There should be exactly one non-empty bucket line for one sample.
  // Bucket lines contain percentages; we can count '%' characters.
  // A single line prints two percentages (bucket and cumulative): "100.000% 100.000%".
  EXPECT_EQ(2, CountOccurrences(out, "%")) << out;
  EXPECT_NE(std::string::npos, out.find("100.000% 100.000%")) << out;

  // The visual bar uses: marks = int(20 * (count/num_) + 0.5).
  // With one sample in one bucket => 20 '#'.
  // Grab the first line that has percentages and count trailing '#'.
  std::smatch m;
  std::regex line_with_pct(R"((\[.*\)\s+[0-9]+\s+[0-9]+\.[0-9]{3}%\s+[0-9]+\.[0-9]{3}%\s*#+))");
  ASSERT_TRUE(std::regex_search(out, m, line_with_pct)) << out;
  const std::string bar_line = m.str();
  const int hashes = CountOccurrences(bar_line, "#");
  EXPECT_EQ(20, hashes) << bar_line;
}

// Verifies repeated identical values aggregate in one bucket and keep stddev 0,
// with correct count and percentages.
TEST(HistogramToStringTest_437, RepeatedValueShowsCountAndStdDevZero_437) {
  Histogram h;
  h.Clear();

  for (int i = 0; i < 7; ++i) {
    h.Add(5.0);
  }

  const std::string out = h.ToString();

  // Count, Average, StdDev formatting.
  EXPECT_NE(std::string::npos, out.find("Count: 7 Average: 5.0000 StdDev: 0.00"))
      << out;

  // Min/Median/Max should all be 5.0000 for identical inputs.
  EXPECT_NE(std::string::npos, out.find("Min: 5.0000 Median: 5.0000 Max: 5.0000"))
      << out;

  // Single bucket should represent 100% of samples; two percent values on one line.
  EXPECT_EQ(2, CountOccurrences(out, "%")) << out;
  EXPECT_NE(std::string::npos, out.find("100.000% 100.000%")) << out;

  // The bucket line should show the exact count "7" in the "count" column.
  // We don't depend on bucket boundaries; we just assert the printed count exists.
  // The count column is printed as "%7.0f", so it may be padded. Search for " 7 " safely.
  // Use regex to find the bucket line and ensure the count token is 7.
  std::smatch m;
  // Capture the count field (group 1).
  std::regex count_capture(R"(\[.*\)\s+([0-9]+)\s+[0-9]+\.[0-9]{3}%\s+[0-9]+\.[0-9]{3}%\s*#+)");
  ASSERT_TRUE(std::regex_search(out, m, count_capture)) << out;
  ASSERT_GE(m.size(), 2u);
  EXPECT_EQ("7", m[1].str());
}

// Verifies that two widely separated values appear in (at least) two non-empty
// histogram lines, with cumulative percentage ending at 100% and multiple '%'
// tokens present. We do not assume specific bucket bounds or order beyond
// ascending traversal implied by ToString()'s loop.
TEST(HistogramToStringTest_437, TwoDistantValuesYieldTwoBucketLines_437) {
  Histogram h;
  h.Clear();

  // Two clearly distinct magnitudes to minimize chance of sharing a bucket,
  // without assuming specific bucket limits.
  h.Add(0.0001);
  h.Add(1e12);

  const std::string out = h.ToString();

  // Count header reflects two samples.
  EXPECT_NE(std::string::npos, out.find("Count: 2 ")) << out;

  // There should be at least two bucket lines (each line has two '%' tokens).
  // With two buckets non-empty, we'd expect 4 '%' tokens total.
  const int pct_tokens = CountOccurrences(out, "%");
  EXPECT_GE(pct_tokens, 4) << out;

  // The final line's cumulative percentage should reach 100%.
  EXPECT_NE(std::string::npos, out.find("100.000%")) << out;

  // Basic sanity: Average should be between the two values and StdDev non-zero.
  // We avoid computing expected numeric values; just assert formatting presence.
  EXPECT_NE(std::string::npos, out.find("Average: ")) << out;
  EXPECT_NE(std::string::npos, out.find("StdDev: ")) << out;
}
