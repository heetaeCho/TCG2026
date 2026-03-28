// File: prog_dumpbytemap_test_404.cc
#include <gtest/gtest.h>
#include <regex>
#include <string>
#include <vector>
#include <utility>
#include "re2/prog.h"

using re2::Prog;

class ProgDumpByteMapTest_404 : public ::testing::Test {
protected:
  // Parses lines like "[00-1f] -> 3" and returns (lo, hi, b).
  // Returns true on success; false otherwise.
  static bool ParseLine(const std::string& line, int& lo, int& hi, int& b) {
    static const std::regex kPat(
        R"(^\[([0-9a-f]{2})-([0-9a-f]{2})\] -> ([0-9]+)\n?$)");
    std::smatch m;
    if (!std::regex_match(line, m, kPat) || m.size() != 4) return false;
    lo = std::stoi(m[1].str(), nullptr, 16);
    hi = std::stoi(m[2].str(), nullptr, 16);
    b  = std::stoi(m[3].str(), nullptr, 10);
    return true;
  }

  static std::vector<std::string> SplitLines(const std::string& s) {
    std::vector<std::string> out;
    size_t start = 0;
    while (true) {
      size_t pos = s.find('\n', start);
      if (pos == std::string::npos) break;
      out.emplace_back(s.substr(start, pos - start + 1)); // keep '\n'
      start = pos + 1;
    }
    // If there is trailing content without '\n', include it as last line
    if (start < s.size()) out.emplace_back(s.substr(start));
    return out;
  }
};

// Verifies the basic format and full coverage [00..ff], with contiguous ranges.
TEST_F(ProgDumpByteMapTest_404, DumpByteMap_FormatAndCoverage_404) {
  Prog p;
  const std::string map = p.DumpByteMap();

  // The output should not be empty.
  ASSERT_FALSE(map.empty());

  // Every line must match the expected pattern and ranges must be contiguous.
  const auto lines = SplitLines(map);
  ASSERT_GE(lines.size(), 1u);
  ASSERT_LE(lines.size(), 256u);

  int total_span = 0;
  int prev_hi = -1;

  for (size_t i = 0; i < lines.size(); ++i) {
    int lo = -1, hi = -1, b = -1;
    ASSERT_TRUE(ParseLine(lines[i], lo, hi, b))
        << "Line did not match pattern: " << lines[i];

    // First range must start at 0x00.
    if (i == 0) {
      EXPECT_EQ(lo, 0) << "First range should start at 00";
    } else {
      // Subsequent ranges must start at previous hi + 1 (contiguity).
      EXPECT_EQ(lo, prev_hi + 1)
          << "Ranges must be contiguous. Prev hi=" << prev_hi
          << ", current lo=" << lo;
    }

    // Each range must be non-empty and within [00..ff].
    EXPECT_LE(lo, hi);
    EXPECT_GE(lo, 0);
    EXPECT_LE(hi, 255);

    total_span += (hi - lo + 1);
    prev_hi = hi;
    (void)b;  // We don't assert the bucket number value; only formatting.
  }

  // Entire coverage must span all 256 byte values.
  EXPECT_EQ(total_span, 256);
  // Last range must end at 0xff.
  EXPECT_EQ(prev_hi, 255);
}

// Ensures lowercase hex and absence of uppercase A–F in the output.
TEST_F(ProgDumpByteMapTest_404, DumpByteMap_LowercaseHex_404) {
  Prog p;
  const std::string map = p.DumpByteMap();

  // Expect no uppercase hex letters in the output.
  for (char ch : map) {
    EXPECT_TRUE(!(ch >= 'A' && ch <= 'F'))
        << "Expected lowercase hex formatting, found uppercase: " << ch;
  }

  // Spot-check that hex digits appear somewhere.
  // (e.g., "0a", "ff", "00" style tokens should exist in a typical map)
  // We do not depend on specific bucket values.
  std::regex hex_token(R"(\[[0-9a-f]{2}-[0-9a-f]{2}\])");
  EXPECT_TRUE(std::regex_search(map, hex_token));
}

// Ensures each emitted mapping line ends with a newline and the final output
// also ends with a newline (since each appended line adds '\n').
TEST_F(ProgDumpByteMapTest_404, DumpByteMap_TrailingNewlines_404) {
  Prog p;
  const std::string map = p.DumpByteMap();

  ASSERT_FALSE(map.empty());
  EXPECT_EQ(map.back(), '\n') << "Expected final newline at end of output";

  const auto lines = SplitLines(map);
  ASSERT_GE(lines.size(), 1u);
  for (const auto& line : lines) {
    // All lines except possibly the last fragment should include '\n'.
    // SplitLines keeps '\n' for all newline-terminated lines.
    EXPECT_FALSE(line.empty());
    EXPECT_EQ(line.back(), '\n') << "Each mapping line should end with '\\n'";
  }
}

// Calling DumpByteMap repeatedly without mutating the object should be stable.
TEST_F(ProgDumpByteMapTest_404, DumpByteMap_StableAcrossCalls_404) {
  Prog p;
  const std::string first = p.DumpByteMap();
  const std::string second = p.DumpByteMap();
  EXPECT_EQ(first, second) << "DumpByteMap should be stable across calls";
}
