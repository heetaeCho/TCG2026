// File: set_match_test_235.cc

#include <gtest/gtest.h>
#include "re2/set.h"
#include "re2/re2.h"

namespace {

using re2::RE2;

// A minimal fixture to keep construction tidy.
class RE2SetMatchTest_235 : public ::testing::Test {
protected:
  // Helper to build a Set without compiling it, since we want to test
  // the "called before compiling" behavior explicitly.
  RE2::Set MakeUncompiledSet() {
    RE2::Options opts;                 // defaults are fine
    // Use any valid anchor; typical RE2 has UNANCHORED/ANCHOR_START, etc.
    // We only need a value to satisfy the constructor.
    return RE2::Set(opts, RE2::UNANCHORED);
  }
};

// ------------------------------------------------------------------
// Not compiled: error_info should be kNotCompiled and return false.
// ------------------------------------------------------------------

TEST_F(RE2SetMatchTest_235, MatchBeforeCompile_SetsNotCompiledAndReturnsFalse_235) {
  RE2::Set set = MakeUncompiledSet();

  std::vector<int> out;               // should remain unchanged by early return
  out.push_back(123);                 // sentinel to detect unintended clearing

  RE2::Set::ErrorInfo err{};
  const bool ok = set.Match("anything", &out, &err);

  EXPECT_FALSE(ok);
  EXPECT_EQ(RE2::Set::kNotCompiled, err.kind)
      << "Match() before Compile() must report kNotCompiled";

  // Because the function returns before allocating/clearing matches (see code),
  // the vector passed in must remain untouched.
  ASSERT_EQ(1u, out.size());
  EXPECT_EQ(123, out[0]);
}

// ------------------------------------------------------------------
// Not compiled: if error_info == nullptr, still returns false safely.
// ------------------------------------------------------------------

TEST_F(RE2SetMatchTest_235, MatchBeforeCompile_NullErrorInfo_IsSafeAndFalse_235) {
  RE2::Set set = MakeUncompiledSet();

  // Provide a pre-filled vector to ensure it's not cleared on early exit.
  std::vector<int> out(1, 7);

  const bool ok = set.Match("text", &out, /*error_info=*/nullptr);

  EXPECT_FALSE(ok);
  // The vector must not be cleared because the function exits before v->clear().
  ASSERT_EQ(1u, out.size());
  EXPECT_EQ(7, out[0]);
}

// ------------------------------------------------------------------
// Not compiled: when v == nullptr, still returns false and sets error.
// ------------------------------------------------------------------

TEST_F(RE2SetMatchTest_235, MatchBeforeCompile_NullVector_SetsNotCompiledAndFalse_235) {
  RE2::Set set = MakeUncompiledSet();

  RE2::Set::ErrorInfo err{};
  const bool ok = set.Match("input", /*v=*/nullptr, &err);

  EXPECT_FALSE(ok);
  EXPECT_EQ(RE2::Set::kNotCompiled, err.kind);
}

// ------------------------------------------------------------------
// Not compiled: both v == nullptr and error_info == nullptr.
// Should simply return false without crashing.
// ------------------------------------------------------------------

TEST_F(RE2SetMatchTest_235, MatchBeforeCompile_NullVectorAndNullErrorInfo_235) {
  RE2::Set set = MakeUncompiledSet();

  // Should not crash; should return false.
  const bool ok = set.Match("input", /*v=*/nullptr, /*error_info=*/nullptr);
  EXPECT_FALSE(ok);
}

}  // namespace
