// SPDX-License-Identifier: GPL-2.0-or-later
// File: version_test_991.cpp

#include <gtest/gtest.h>

#include <exiv2/exiv2.hpp>

#include <algorithm>
#include <cctype>
#include <cstdint>
#include <regex>
#include <set>
#include <sstream>
#include <string>
#include <vector>

namespace {

class VersionTest_991 : public ::testing::Test {
 protected:
  static std::string DumpInfo(const std::vector<std::regex>& keys) {
    std::ostringstream os;
    Exiv2::dumpLibraryInfo(os, keys);
    return os.str();
  }

  static std::vector<std::string> SplitLines(const std::string& s) {
    std::vector<std::string> lines;
    std::istringstream iss(s);
    for (std::string line; std::getline(iss, line);) {
      // std::getline strips '\n'
      if (!line.empty() && line.back() == '\r') line.pop_back();
      lines.push_back(line);
    }
    return lines;
  }

  static bool LooksLikeKeyValueLine(const std::string& line) {
    const auto pos = line.find('=');
    return pos != std::string::npos && pos != 0 && pos + 1 <= line.size();
  }

  static std::string ExtractKey(const std::string& line) {
    const auto pos = line.find('=');
    if (pos == std::string::npos) return {};
    return line.substr(0, pos);
  }

  static std::string ExtractValue(const std::string& line) {
    const auto pos = line.find('=');
    if (pos == std::string::npos) return {};
    return line.substr(pos + 1);
  }

  static std::vector<int> ParseSemverTriplet(const std::string& vs) {
    // Best-effort: pick first three integer components separated by '.'.
    // If parsing fails, returns empty.
    std::vector<int> nums;
    std::string token;
    std::istringstream iss(vs);
    while (std::getline(iss, token, '.')) {
      if (token.empty()) return {};
      // Stop at first non-digit chunk.
      if (!std::all_of(token.begin(), token.end(), [](unsigned char c) { return std::isdigit(c); })) {
        return {};
      }
      try {
        nums.push_back(std::stoi(token));
      } catch (...) {
        return {};
      }
      if (nums.size() == 3) break;
    }
    if (nums.size() != 3) return {};
    return nums;
  }
};

TEST_F(VersionTest_991, VersionCStringIsNonNullAndNonEmpty_991) {
  const char* v = Exiv2::version();
  ASSERT_NE(v, nullptr);
  EXPECT_NE(std::string(v).size(), 0u);
}

TEST_F(VersionTest_991, VersionStringHasContentAndIsStableAcrossCalls_991) {
  const std::string a = Exiv2::versionString();
  const std::string b = Exiv2::versionString();
  EXPECT_FALSE(a.empty());
  EXPECT_EQ(a, b);
}

TEST_F(VersionTest_991, VersionNumberHexStringLooksLikeFixedWidthHex_991) {
  const std::string hx = Exiv2::versionNumberHexString();

  // Observable formatting expectations: fixed-length 6 hex chars (per API docs).
  EXPECT_EQ(hx.size(), 6u);

  const auto is_hex = [](unsigned char c) {
    return std::isdigit(c) || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F');
  };
  EXPECT_TRUE(std::all_of(hx.begin(), hx.end(), [&](unsigned char c) { return is_hex(c); }));
}

TEST_F(VersionTest_991, VersionNumberIsStableAcrossCalls_991) {
  const uint32_t a = Exiv2::versionNumber();
  const uint32_t b = Exiv2::versionNumber();
  EXPECT_EQ(a, b);
}

TEST_F(VersionTest_991, TestVersionAcceptsCurrentTriplet_991) {
  const std::string vs = Exiv2::versionString();
  const auto triplet = ParseSemverTriplet(vs);
  ASSERT_EQ(triplet.size(), 3u) << "versionString() did not look like 'major.minor.patch': " << vs;

  EXPECT_TRUE(Exiv2::testVersion(static_cast<uint32_t>(triplet[0]),
                                static_cast<uint32_t>(triplet[1]),
                                static_cast<uint32_t>(triplet[2])));
}

TEST_F(VersionTest_991, TestVersionRejectsClearlyNewerMajor_991) {
  const std::string vs = Exiv2::versionString();
  const auto triplet = ParseSemverTriplet(vs);
  ASSERT_EQ(triplet.size(), 3u) << "versionString() did not look like 'major.minor.patch': " << vs;

  const uint32_t newer_major = static_cast<uint32_t>(triplet[0] + 1);
  EXPECT_FALSE(Exiv2::testVersion(newer_major, 0u, 0u));
}

TEST_F(VersionTest_991, DumpLibraryInfoProducesKeyValueLines_991) {
  const std::string out = DumpInfo(/*keys=*/{});
  const auto lines = SplitLines(out);

  // At minimum, it should be safe to call and produce a formatted report (or be empty).
  // If non-empty, require key=value formatting for each line.
  for (const auto& line : lines) {
    EXPECT_TRUE(LooksLikeKeyValueLine(line)) << "Unexpected line format: '" << line << "'";
  }
}

TEST_F(VersionTest_991, DumpLibraryInfoFilteringCanNarrowOutput_991) {
  // Black-box strategy:
  // 1) Dump with no filter, discover a key that exists.
  // 2) Dump with a regex that matches exactly that key.
  // 3) Expect at least one line and that all lines are key=value.
  const std::string all_out = DumpInfo(/*keys=*/{});
  const auto all_lines = SplitLines(all_out);

  // If the implementation chooses to emit nothing in this build, just ensure no crash.
  if (all_lines.empty()) {
    SUCCEED();
    return;
  }

  // Find the first well-formed key=value line and use its key for filtering.
  std::string chosen_key;
  for (const auto& line : all_lines) {
    if (LooksLikeKeyValueLine(line)) {
      chosen_key = ExtractKey(line);
      if (!chosen_key.empty()) break;
    }
  }
  ASSERT_FALSE(chosen_key.empty());

  // Escape regex metacharacters in the key so we can match it exactly.
  const std::regex metachars(R"([.^$|()\\[\]{}*+?])");
  const std::string escaped = std::regex_replace(chosen_key, metachars, R"(\$&)");
  const std::regex exact("^" + escaped + "$");

  const std::string filtered_out = DumpInfo(/*keys=*/{exact});
  const auto filtered_lines = SplitLines(filtered_out);

  // Filtering should not introduce malformed output.
  for (const auto& line : filtered_lines) {
    EXPECT_TRUE(LooksLikeKeyValueLine(line)) << "Unexpected filtered line format: '" << line << "'";
  }

  // If anything is output, at least one line should correspond to the chosen key.
  if (!filtered_lines.empty()) {
    bool found = false;
    for (const auto& line : filtered_lines) {
      if (ExtractKey(line) == chosen_key) {
        found = true;
        break;
      }
    }
    EXPECT_TRUE(found) << "Filtered output did not include the requested key: " << chosen_key;
  }
}

TEST_F(VersionTest_991, DumpLibraryInfoNonMatchingFilterMayProduceEmptyOrSmallerOutput_991) {
  const std::string all_out = DumpInfo(/*keys=*/{});
  const std::string none_out = DumpInfo(/*keys=*/{std::regex("a^")});  // should match nothing in typical regex engines

  // Black-box, non-prescriptive check:
  // If unfiltered output exists, then applying a non-matching filter should not increase output size.
  if (!all_out.empty()) {
    EXPECT_LE(none_out.size(), all_out.size());
  }

  // Whatever it outputs, it should still be line-formatted.
  const auto lines = SplitLines(none_out);
  for (const auto& line : lines) {
    EXPECT_TRUE(LooksLikeKeyValueLine(line)) << "Unexpected line format: '" << line << "'";
  }
}

}  // namespace