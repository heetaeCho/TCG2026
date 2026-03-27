// File: parse_string_view_to_rune_test.cc
#include <gtest/gtest.h>
#include <string_view>
#include <string>
#include <algorithm>

//
// Minimal surface-only dependencies to compile & observe behavior.
// These are collaborators or plain data/types — not re-implementations
// of the function under test.
//
namespace absl {
using string_view = std::string_view;
}  // namespace absl

namespace re2 {

// Common RE2 rune bits (values from provided snippet).
using Rune = int;
enum {
  UTFmax   = 4,
  Runesync = 128,
  Runeself = 128,
  Runeerror = 65533,
  Runemax   = 1114111,
};

// Public status code enum (from provided snippet).
enum RegexpStatusCode {
  kRegexpSuccess = 0,
  kRegexpInternalError = 1,
  kRegexpBadEscape = 2,
  kRegexpBadCharClass = 3,
  kRegexpBadCharRange = 4,
  kRegexpMissingBracket = 5,
  kRegexpMissingParen = 6,
  kRegexpUnexpectedParen = 7,
  kRegexpTrailingBackslash = 8,
  kRegexpRepeatArgument = 9,
  kRegexpRepeatSize = 10,
  kRegexpRepeatOp = 11,
  kRegexpBadPerlOp = 12,
  kRegexpBadUTF8 = 13,
  kRegexpBadNamedCapture = 14
};

// Minimal observable RegexpStatus to capture effects.
class RegexpStatus {
 public:
  RegexpStatus() : code_(kRegexpSuccess) {}
  void set_code(RegexpStatusCode c) { code_ = c; }
  void set_error_arg(absl::string_view a) { arg_ = a; }
  RegexpStatusCode code() const { return code_; }
  absl::string_view error_arg() const { return arg_; }
 private:
  RegexpStatusCode code_;
  absl::string_view arg_;
};

// ---------- Test doubles (stubs) for external collaborators ----------
namespace test_stubs {
  // Controls + captures for fullrune/chartorune.
  inline bool fullrune_result = false;
  inline const char* fullrune_last_p = nullptr;
  inline int fullrune_last_n = -1;

  inline int chartorune_next_n = 0;
  inline Rune chartorune_next_rune = 0;

  inline void Reset() {
    fullrune_result = false;
    fullrune_last_p = nullptr;
    fullrune_last_n = -1;
    chartorune_next_n = 0;
    chartorune_next_rune = 0;
  }
}  // namespace test_stubs

// Unqualified lookup inside re2:: will find these, matching the function under test.
inline int fullrune(const char* p, int n) {
  test_stubs::fullrune_last_p = p;
  test_stubs::fullrune_last_n = n;
  return test_stubs::fullrune_result ? 1 : 0;
}
inline int chartorune(Rune* r, const char* /*p*/) {
  *r = test_stubs::chartorune_next_rune;
  return test_stubs::chartorune_next_n;
}

}  // namespace re2

// Include the function under test exactly as implemented.
// Path matches the prompt's file layout (compile setup should add ./TestProjects/re2 to include paths).
#include "re2/parse.cc"

using namespace re2;

class StringViewToRuneTest_515 : public ::testing::Test {
 protected:
  void SetUp() override { test_stubs::Reset(); }
};

// Normal operation: ASCII-like success (n=1), advances view and returns count.
TEST_F(StringViewToRuneTest_515, ReturnsCountAndAdvancesOnSuccess_ASCII_515) {
  std::string backing = "ABC";
  absl::string_view sv(backing);
  Rune r = -1;
  RegexpStatus status;              // default success

  test_stubs::fullrune_result = true;
  test_stubs::chartorune_next_n = 1;
  test_stubs::chartorune_next_rune = 'A';

  int ret = StringViewToRune(&r, &sv, &status);
  EXPECT_EQ(ret, 1);
  EXPECT_EQ(r, 'A');
  EXPECT_EQ(sv, "BC");             // advanced by 1
  EXPECT_EQ(status.code(), kRegexpSuccess);  // untouched on success

  // Also verify fullrune was called with min(4, size)=3.
  EXPECT_EQ(test_stubs::fullrune_last_n, 3);
  EXPECT_EQ(test_stubs::fullrune_last_p, backing.data());
}

// Normal operation: multi-byte success (n=3), advances view and returns 3.
TEST_F(StringViewToRuneTest_515, ReturnsCountAndAdvancesOnSuccess_Multibyte_515) {
  std::string backing = "xyz...";
  absl::string_view sv(backing);
  Rune r = -1;
  RegexpStatus status;
  test_stubs::fullrune_result = true;
  test_stubs::chartorune_next_n = 3;
  test_stubs::chartorune_next_rune = 0x20AC; // any <= Runemax

  int ret = StringViewToRune(&r, &sv, &status);
  EXPECT_EQ(ret, 3);
  EXPECT_EQ(r, 0x20AC);
  EXPECT_EQ(sv, backing.substr(3));
  EXPECT_EQ(status.code(), kRegexpSuccess);
}

// Boundary: fullrune is called with at most 4 bytes even if input is longer.
TEST_F(StringViewToRuneTest_515, FullruneReceivesAtMostFourBytes_515) {
  std::string backing = "0123456789";
  absl::string_view sv(backing);
  Rune r = 0;
  RegexpStatus status;

  test_stubs::fullrune_result = true;
  test_stubs::chartorune_next_n = 2;
  test_stubs::chartorune_next_rune = 0x7FF;

  (void)StringViewToRune(&r, &sv, &status);
  EXPECT_EQ(test_stubs::fullrune_last_n, 4); // min(4, size=10) -> 4
}

// Boundary: fullrune sees the true (small) size when input shorter than 4.
TEST_F(StringViewToRuneTest_515, FullruneReceivesExactShortSize_515) {
  std::string backing = "ab";
  absl::string_view sv(backing);
  Rune r = 0;
  RegexpStatus status;

  test_stubs::fullrune_result = true;
  test_stubs::chartorune_next_n = 2;
  test_stubs::chartorune_next_rune = 0x1234;

  (void)StringViewToRune(&r, &sv, &status);
  EXPECT_EQ(test_stubs::fullrune_last_n, 2);
}

// Error: fullrune reports not enough bytes -> returns -1, sets status, view unchanged.
TEST_F(StringViewToRuneTest_515, ReturnsErrorWhenFullruneFalse_515) {
  std::string backing = "incomplete";
  absl::string_view sv(backing);
  Rune r = 12345; // ensure not modified on this path
  RegexpStatus status;

  test_stubs::fullrune_result = false; // triggers error path

  int ret = StringViewToRune(&r, &sv, &status);
  EXPECT_EQ(ret, -1);
  EXPECT_EQ(sv, backing);  // no advancement
  EXPECT_EQ(r, 12345);     // unchanged
  EXPECT_EQ(status.code(), kRegexpBadUTF8);
  EXPECT_TRUE(status.error_arg().empty());
}

// Error: chartorune signals decoding error via (n==1 && r==Runeerror).
TEST_F(StringViewToRuneTest_515, ReturnsErrorOnChartoruneRuneerrorLen1_515) {
  std::string backing = "\xFFoops"; // content irrelevant to stub behavior
  absl::string_view sv(backing);
  Rune r = 0;
  RegexpStatus status;

  test_stubs::fullrune_result = true;
  test_stubs::chartorune_next_n = 1;
  test_stubs::chartorune_next_rune = Runeerror;

  int ret = StringViewToRune(&r, &sv, &status);
  EXPECT_EQ(ret, -1);
  EXPECT_EQ(sv, backing);             // no advancement on error
  EXPECT_EQ(r, Runeerror);            // set by chartorune
  EXPECT_EQ(status.code(), kRegexpBadUTF8);
  EXPECT_TRUE(status.error_arg().empty());
}

// Error: chartorune returns rune > Runemax -> coerced to Runeerror & error returned.
TEST_F(StringViewToRuneTest_515, ReturnsErrorWhenRuneExceedsRunemax_515) {
  std::string backing = "validprefix";
  absl::string_view sv(backing);
  Rune r = 0;
  RegexpStatus status;

  test_stubs::fullrune_result = true;
  test_stubs::chartorune_next_n = 3;                 // any length
  test_stubs::chartorune_next_rune = Runemax + 1;    // force > Runemax

  int ret = StringViewToRune(&r, &sv, &status);
  EXPECT_EQ(ret, -1);
  EXPECT_EQ(sv, backing);          // no advancement on error
  EXPECT_EQ(r, Runeerror);         // coerced by function under test
  EXPECT_EQ(status.code(), kRegexpBadUTF8);
  EXPECT_TRUE(status.error_arg().empty());
}

// Corner: (n==2 && r==Runeerror) should be treated as success (only (1 && Runeerror) is error).
TEST_F(StringViewToRuneTest_515, RuneerrorWithLenGreaterThanOneIsSuccess_515) {
  std::string backing = "zzzz";
  absl::string_view sv(backing);
  Rune r = 0;
  RegexpStatus status;
  // Pre-set status to a non-success to verify it remains unchanged on success.
  status.set_code(kRegexpInternalError);

  test_stubs::fullrune_result = true;
  test_stubs::chartorune_next_n = 2;
  test_stubs::chartorune_next_rune = Runeerror;  // but n != 1

  int ret = StringViewToRune(&r, &sv, &status);
  EXPECT_EQ(ret, 2);
  EXPECT_EQ(r, Runeerror);
  EXPECT_EQ(sv, backing.substr(2));
  EXPECT_EQ(status.code(), kRegexpInternalError); // unchanged on success
}

// Error path with nullptr status: should not crash and should just return -1.
TEST_F(StringViewToRuneTest_515, NullStatusPointerIsHandled_515) {
  std::string backing = "x";
  absl::string_view sv(backing);
  Rune r = 0;

  test_stubs::fullrune_result = false; // force error

  int ret = StringViewToRune(&r, &sv, /*status=*/nullptr);
  EXPECT_EQ(ret, -1);
  EXPECT_EQ(sv, backing); // unchanged
}
