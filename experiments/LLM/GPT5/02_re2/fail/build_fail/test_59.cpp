// File: re2_match_shim_test_59.cc

#include <gtest/gtest.h>
#include <pybind11/embed.h>
#include <pybind11/pybind11.h>
#include <pybind11/pytypes.h>

#include "re2/re2.h"

// SUT header (the function under test)
namespace re2_python {
  std::vector<std::pair<ssize_t, ssize_t>> RE2MatchShim(
      const RE2& self,
      RE2::Anchor anchor,
      pybind11::buffer buffer,
      ssize_t pos,
      ssize_t endpos);
}

namespace py = pybind11;
using re2_python::RE2MatchShim;

class RE2MatchShimTest_59 : public ::testing::Test {
protected:
  // Start/stop an embedded Python interpreter once for all tests.
  static void SetUpTestSuite() {
    guard_ = new py::scoped_interpreter{};
  }
  static void TearDownTestSuite() {
    delete guard_;
    guard_ = nullptr;
  }

  // Helper to build a py::buffer from raw bytes using Python's bytearray
  static py::buffer MakeBuffer(const std::string& bytes) {
    py::bytearray ba(bytes);
    return py::buffer(ba);
  }

  static py::scoped_interpreter* guard_;
};

py::scoped_interpreter* RE2MatchShimTest_59::guard_ = nullptr;

// --------------------------- Tests ---------------------------

TEST_F(RE2MatchShimTest_59, SingleGroup_MatchOffsets_59) {
  // Pattern with one capturing group -> total groups = 2 ($0 and $1)
  RE2 re("(\\d+)");
  const std::string text = "hello 123 world";
  auto buf = MakeBuffer(text);

  auto spans = RE2MatchShim(re, RE2::UNANCHORED, buf, /*pos=*/0, /*endpos=*/static_cast<ssize_t>(text.size()));

  ASSERT_EQ(spans.size(), 2u);
  // "123" is at byte offsets [6,9)
  EXPECT_EQ(spans[0].first, 6);  // whole match
  EXPECT_EQ(spans[0].second, 9);
  EXPECT_EQ(spans[1].first, 6);  // group 1
  EXPECT_EQ(spans[1].second, 9);
}

TEST_F(RE2MatchShimTest_59, NoMatch_AllGroupsAreMinusOne_59) {
  RE2 re("(\\d+)");
  const std::string text = "abcdef";
  auto buf = MakeBuffer(text);

  auto spans = RE2MatchShim(re, RE2::UNANCHORED, buf, /*pos=*/0, /*endpos=*/static_cast<ssize_t>(text.size()));

  // There is one capturing group -> expect two spans, both (-1,-1)
  ASSERT_EQ(spans.size(), 2u);
  EXPECT_EQ(spans[0].first, -1);
  EXPECT_EQ(spans[0].second, -1);
  EXPECT_EQ(spans[1].first, -1);
  EXPECT_EQ(spans[1].second, -1);
}

TEST_F(RE2MatchShimTest_59, OptionalGroup_UnmatchedGroupBecomesMinusOne_59) {
  // Optional group: (a)?b
  RE2 re("(a)?b");
  const std::string text = "bzzz";  // should match 'b' at the start, group (a) not present
  auto buf = MakeBuffer(text);

  auto spans = RE2MatchShim(re, RE2::UNANCHORED, buf, /*pos=*/0, /*endpos=*/static_cast<ssize_t>(text.size()));

  ASSERT_EQ(spans.size(), 2u);
  // Whole match is 'b' at [0,1)
  EXPECT_EQ(spans[0].first, 0);
  EXPECT_EQ(spans[0].second, 1);
  // Group 1 didn't match -> (-1,-1)
  EXPECT_EQ(spans[1].first, -1);
  EXPECT_EQ(spans[1].second, -1);
}

TEST_F(RE2MatchShimTest_59, ByteOffsets_WithUTF8Multibyte_59) {
  // UTF-8 '가' is 3 bytes. Ensure returned offsets are in BYTES, not characters.
  RE2 re("a");
  const std::string text = u8"가a";  // bytes: [0,1,2] = '가', [3] = 'a'
  auto buf = MakeBuffer(text);

  auto spans = RE2MatchShim(re, RE2::UNANCHORED, buf, /*pos=*/0, /*endpos=*/static_cast<ssize_t>(text.size()));

  ASSERT_EQ(spans.size(), 1u + 0u + re.NumberOfCapturingGroups());  // $0 only; no explicit groups
  ASSERT_EQ(spans.size(), 1u); // sanity check: pattern has 0 capturing groups -> only $0
  // 'a' is at byte offset 3..4
  EXPECT_EQ(spans[0].first, 3);
  EXPECT_EQ(spans[0].second, 4);
}

TEST_F(RE2MatchShimTest_59, RespectsSlice_PosEndpos_59) {
  // Restrict search to [pos, endpos)
  RE2 re("(\\d+)");
  const std::string text = "abc123def";
  // Choose a subrange that exposes only "12" (indexes 3..5)
  // full text indices: a0 b1 c2 1_3 2_4 3_5 d6 e7 f8
  ssize_t pos = 2;
  ssize_t endpos = 5;  // slice "c12"
  auto buf = MakeBuffer(text);

  auto spans = RE2MatchShim(re, RE2::UNANCHORED, buf, pos, endpos);

  ASSERT_EQ(spans.size(), 2u);
  // Expect "12" at [3,5)
  EXPECT_EQ(spans[0].first, 3);
  EXPECT_EQ(spans[0].second, 5);
  EXPECT_EQ(spans[1].first, 3);
  EXPECT_EQ(spans[1].second, 5);
}

TEST_F(RE2MatchShimTest_59, AnchorStart_RequiresMatchAtStart_59) {
  // With ANCHOR_START at pos, the match must begin exactly at 'pos'.
  RE2 re("b");
  const std::string text = "ab";
  auto buf = MakeBuffer(text);

  // 1) Anchored at start (pos = 0) -> should FAIL, as 'b' starts at index 1.
  {
    auto spans = RE2MatchShim(re, RE2::ANCHOR_START, buf, /*pos=*/0, /*endpos=*/static_cast<ssize_t>(text.size()));
    ASSERT_EQ(spans.size(), 1u); // no capturing groups => only $0
    EXPECT_EQ(spans[0].first, -1);
    EXPECT_EQ(spans[0].second, -1);
  }

  // 2) Anchored at start (pos = 1) -> should SUCCEED, as 'b' is exactly at index 1.
  {
    auto spans = RE2MatchShim(re, RE2::ANCHOR_START, buf, /*pos=*/1, /*endpos=*/static_cast<ssize_t>(text.size()));
    ASSERT_EQ(spans.size(), 1u);
    EXPECT_EQ(spans[0].first, 1);
    EXPECT_EQ(spans[0].second, 2);
  }
}
