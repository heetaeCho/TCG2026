// File: ansi_skipping_string_const_iterator_postdec_test.cpp

#include <gtest/gtest.h>
#include "catch2/internal/catch_textflow.hpp"

using Catch::TextFlow::AnsiSkippingString;

namespace {

// A few colored segments to ensure ANSI escapes are present.
// "\x1b[31m" = SGR Red, "\x1b[0m" = reset.
constexpr const char* kAnsiRedOn  = "\x1b[31m";
constexpr const char* kAnsiReset  = "\x1b[0m";

// Helper to build a sample string containing ANSI sequences but with
// predictable visible characters: "A B C"
std::string MakeAnsiSample() {
  std::string s;
  s += 'A';
  s += ' ';
  s += kAnsiRedOn;   // start color (should be skipped)
  s += 'B';
  s += kAnsiReset;   // reset color (should be skipped)
  s += ' ';
  s += 'C';
  return s;
}

} // namespace

// Fixture to hold a common sample under test.
class AnsiConstIterPostDecTest_40 : public ::testing::Test {
protected:
  void SetUp() override {
    sample_ = MakeAnsiSample();          // Visible chars should be: A ' ' B ' ' C
    flow_   = AnsiSkippingString(sample_);
  }

  // Convenience: materialize all visible chars by forward-iterating.
  static std::string Visible(const AnsiSkippingString& as) {
    std::string out;
    for (auto it = as.cbegin(); it != as.cend(); ++it) out.push_back(*it);
    return out;
  }

  std::string sample_;
  AnsiSkippingString flow_{""};
};

// Confirms our forward-visible baseline so subsequent expectations are meaningful.
TEST_F(AnsiConstIterPostDecTest_40, ForwardVisibilityBaseline_40) {
  EXPECT_EQ(Visible(flow_), "A B C");
}

// Post-decrement returns the old iterator, while the iterator itself moves back by one.
TEST_F(AnsiConstIterPostDecTest_40, PostDecrement_ReturnsOldIteratorAndMovesBack_40) {
  auto it = flow_.cbegin();   // points to 'A'
  ++it;                       // now at ' ' (the first space)
  ++it;                       // now at 'B'

  auto before = it;           // snapshot
  auto ret = it--;            // post-decrement: ret should be old position ('B'), it should move to ' '

  // Returned iterator equals the snapshot (old position).
  EXPECT_EQ(ret, before);

  // Deref checks (ret still at 'B', it moved back to ' ').
  EXPECT_EQ(*ret, 'B');
  EXPECT_EQ(*it,  ' ');
}

// Post-decrement from cend(): returned value equals cend(), iterator moves to last visible char.
TEST_F(AnsiConstIterPostDecTest_40, PostDecrement_FromCEnd_YieldsLastChar_40) {
  auto it = flow_.cend();        // one past last
  auto ret = it--;               // ret should equal cend(), it should now be at last visible char 'C'

  EXPECT_EQ(ret, flow_.cend());
  ASSERT_NE(it, flow_.cend());   // now valid position
  EXPECT_EQ(*it, 'C');
}

// Multiple post-decrements traverse visible chars backwards, skipping ANSI escapes.
TEST_F(AnsiConstIterPostDecTest_40, PostDecrement_BackwardsSequence_SkipsAnsi_40) {
  auto it = flow_.cend();   // past-the-end

  // Move: C, ' ', B, ' ', A
  it--; EXPECT_EQ(*it, 'C');  // from end -> 'C'
  it--; EXPECT_EQ(*it, ' ');  // -> space
  it--; EXPECT_EQ(*it, 'B');  // -> 'B' (ANSI sequences skipped)
  it--; EXPECT_EQ(*it, ' ');  // -> space
  it--; EXPECT_EQ(*it, 'A');  // -> 'A'
}

// Equality semantics around post-decrement: returned iterator equals the "before" snapshot,
// while the decremented iterator does not.
TEST_F(AnsiConstIterPostDecTest_40, PostDecrement_EqualitySemantics_40) {
  auto it = flow_.cbegin();   // 'A'
  ++it;                       // ' '
  ++it;                       // 'B'

  auto snapshot = it;
  auto ret = it--;            // ret == snapshot; it moved back

  EXPECT_EQ(ret, snapshot);
  EXPECT_NE(it,  snapshot);
  // Sanity: contents line up with expectations.
  EXPECT_EQ(*ret, 'B');
  EXPECT_EQ(*it,  ' ');
}

// Two successive post-decrements step twice and each returned value reflects the old position.
TEST_F(AnsiConstIterPostDecTest_40, PostDecrement_Twice_ReturnsEachOldPosition_40) {
  auto it = flow_.cbegin(); // 'A'
  ++it;                     // ' '
  ++it;                     // 'B'
  ++it;                     // ' '

  // it is at the second space (between B and C)
  auto old1 = it--;   // old1 at ' ', it -> 'B'
  auto old2 = it--;   // old2 at 'B', it -> ' '

  EXPECT_EQ(*old1, ' ');
  EXPECT_EQ(*old2, 'B');
  EXPECT_EQ(*it,   ' ');
}

// Safety: we do NOT dereference cend(); we also avoid decrementing begin() (which would be UB).
// This test confirms that taking a post-decrement at begin() is avoided in our suite and
// that begin() is indeed the first visible character.
TEST_F(AnsiConstIterPostDecTest_40, BeginPointsToFirstVisibleChar_40) {
  auto b = flow_.cbegin();
  ASSERT_NE(b, flow_.cend());
  EXPECT_EQ(*b, 'A');
  // No decrement of begin() performed here to avoid undefined behavior.
}
