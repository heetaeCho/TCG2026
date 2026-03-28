// File: util/histogram_add_test.cc

#include <gtest/gtest.h>
#include <regex>
#include <string>
#include "util/histogram.h"  // assumes this declares leveldb::Histogram

namespace {

using std::string;

// Small helper to robustly extract numbers from Histogram::ToString() output.
// We keep this in the test (not production) and only parse observable text.
static bool ExtractInt(const string& s, const string& key, int* out) {
  // e.g. "Count: 12"
  std::regex re(key + R"(\s*:\s*([0-9]+))", std::regex::icase);
  std::smatch m;
  if (std::regex_search(s, m, re) && m.size() > 1) {
    *out = std::stoi(m[1].str());
    return true;
  }
  return false;
}

static bool ExtractDouble(const string& s, const string& key, double* out) {
  // Accept regular and scientific notation, with optional sign.
  std::regex re(
      key + R"(\s*:\s*([+-]?\d+(?:\.\d+)?(?:[eE][+-]?\d+)?))",
      std::regex::icase);
  std::smatch m;
  if (std::regex_search(s, m, re) && m.size() > 1) {
    *out = std::stod(m[1].str());
    return true;
  }
  return false;
}

class HistogramAddTest_435 : public ::testing::Test {
 protected:
  leveldb::Histogram h_;
};

}  // namespace

// --- Tests ---

// Verifies that a newly cleared histogram reports zero count via ToString()
// and that a single Add(value) sets Count=1 and Min=Max=Average=value.
TEST_F(HistogramAddTest_435, ClearThenAddSingle_SetsCountMinMaxAvg_435) {
  h_.Clear();
  std::string before = h_.ToString();

  // When empty, Count should be present and equal to 0 (observable via text).
  int count_before = -1;
  ASSERT_TRUE(ExtractInt(before, "Count", &count_before))
      << "ToString() should include 'Count:' field for an empty histogram";
  EXPECT_EQ(0, count_before);

  // After adding a single value, statistics should reflect that value.
  const double v = 5.0;
  h_.Add(v);
  std::string after = h_.ToString();

  int count_after = -1;
  double min_after = 0, max_after = 0, avg_after = 0;

  ASSERT_TRUE(ExtractInt(after, "Count", &count_after));
  ASSERT_TRUE(ExtractDouble(after, "Min", &min_after));
  ASSERT_TRUE(ExtractDouble(after, "Max", &max_after));
  ASSERT_TRUE(ExtractDouble(after, "Average", &avg_after));

  EXPECT_EQ(1, count_after);
  EXPECT_DOUBLE_EQ(v, min_after);
  EXPECT_DOUBLE_EQ(v, max_after);
  EXPECT_DOUBLE_EQ(v, avg_after);
}

// Verifies that adding multiple values updates observable stats:
// Count increases; Min, Max, and Average reflect the inserted values.
TEST_F(HistogramAddTest_435, AddMultiple_UpdatesCountMinMaxAvg_435) {
  h_.Clear();

  h_.Add(2.0);
  h_.Add(8.0);

  std::string s = h_.ToString();
  int count = -1;
  double minv = 0, maxv = 0, avgv = 0;

  ASSERT_TRUE(ExtractInt(s, "Count", &count));
  ASSERT_TRUE(ExtractDouble(s, "Min", &minv));
  ASSERT_TRUE(ExtractDouble(s, "Max", &maxv));
  ASSERT_TRUE(ExtractDouble(s, "Average", &avgv));

  EXPECT_EQ(2, count);
  EXPECT_DOUBLE_EQ(2.0, minv);
  EXPECT_DOUBLE_EQ(8.0, maxv);
  // Average of {2,8} is 5.0
  EXPECT_DOUBLE_EQ(5.0, avgv);
}

// Verifies Add handles negative and very large values and that extremes are
// reflected through observable Min/Max fields.
TEST_F(HistogramAddTest_435, AddNegativeAndLarge_TracksExtremes_435) {
  h_.Clear();

  h_.Add(-10.0);
  h_.Add(1e9);

  std::string s = h_.ToString();
  int count = -1;
  double minv = 0, maxv = 0;

  ASSERT_TRUE(ExtractInt(s, "Count", &count));
  ASSERT_TRUE(ExtractDouble(s, "Min", &minv));
  ASSERT_TRUE(ExtractDouble(s, "Max", &maxv));

  EXPECT_EQ(2, count);
  EXPECT_DOUBLE_EQ(-10.0, minv);
  EXPECT_DOUBLE_EQ(1e9, maxv);
}

// Sanity check that Count increases monotonically with repeated Add calls,
// observable purely through ToString() without relying on internals.
TEST_F(HistogramAddTest_435, AddRepeatedly_IncrementsCount_435) {
  h_.Clear();

  for (int i = 0; i < 5; ++i) {
    h_.Add(static_cast<double>(i));
    std::string s = h_.ToString();
    int count = -1;
    ASSERT_TRUE(ExtractInt(s, "Count", &count));
    EXPECT_EQ(i + 1, count) << "Count should equal number of Add calls made";
  }
}
