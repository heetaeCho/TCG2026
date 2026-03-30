// File: set_compile_test_233.cc
#include "re2/set.h"
#include "re2/re2.h"
#include "gtest/gtest.h"

namespace re2 {

class RE2SetCompileTest_233 : public ::testing::Test {
protected:
  RE2::Options DefaultOptions() { return RE2::Options(); }

  // We don't know concrete Anchor enumerators from the snippet, so we
  // value-initialize it (equivalent to 0). This stays within the public API.
  RE2::Anchor DefaultAnchor() { return static_cast<RE2::Anchor>(0); }
};

// Normal operation: compiling an empty set should succeed.
TEST_F(RE2SetCompileTest_233, CompileEmptySet_Succeeds_233) {
  RE2::Options opts = DefaultOptions();
  RE2::Anchor anchor = DefaultAnchor();
  RE2::Set set(opts, anchor);

  // No patterns added.
  const bool compiled = set Compile();
  EXPECT_TRUE(compiled);
}

// Normal operation: compiling after adding a few patterns should succeed.
TEST_F(RE2SetCompileTest_233, CompileWithPatterns_Succeeds_233) {
  RE2::Options opts = DefaultOptions();
  RE2::Anchor anchor = DefaultAnchor();
  RE2::Set set(opts, anchor);

  std::string err;
  // Add a few simple patterns; we only assert that Add returns a non-negative id.
  int id1 = set.Add(absl::string_view("foo"), &err);
  EXPECT_GE(id1, 0) << err;
  int id2 = set.Add(absl::string_view("bar|baz"), &err);
  EXPECT_GE(id2, 0) << err;
  int id3 = set.Add(absl::string_view("[a-z]+"), &err);
  EXPECT_GE(id3, 0) << err;

  const bool compiled = set Compile();
  EXPECT_TRUE(compiled);
}

// Boundary/exceptional behavior (observable): calling Compile() twice should return false the second time.
TEST_F(RE2SetCompileTest_233, CompileCalledTwice_ReturnsFalse_233) {
  RE2::Options opts = DefaultOptions();
  RE2::Anchor anchor = DefaultAnchor();
  RE2::Set set(opts, anchor);

  std::string err;
  EXPECT_GE(set.Add(absl::string_view("abc"), &err), 0) << err;

  EXPECT_TRUE(set Compile()) << "First Compile() should succeed";
  EXPECT_FALSE(set Compile()) << "Second Compile() should fail per interface contract";
}

// Boundary case: compiling a set with duplicate/overlapping patterns should still produce a boolean result.
// We don't assume deduplication or ordering behavior internally—just that it compiles successfully.
TEST_F(RE2SetCompileTest_233, CompileWithDuplicateLikePatterns_Succeeds_233) {
  RE2::Options opts = DefaultOptions();
  RE2::Anchor anchor = DefaultAnchor();
  RE2::Set set(opts, anchor);

  std::string err;
  EXPECT_GE(set.Add(absl::string_view("a"), &err), 0) << err;
  EXPECT_GE(set.Add(absl::string_view("a"), &err), 0) << err;      // duplicate
  EXPECT_GE(set.Add(absl::string_view("(a)"), &err), 0) << err;    // overlapping form

  const bool compiled = set Compile();
  EXPECT_TRUE(compiled);
}

// Defensive behavior: Compile() result is stable regardless of whether patterns were added post-error string handling.
// (We only observe the return value and do not rely on internals.)
TEST_F(RE2SetCompileTest_233, CompileIgnoresErrorStringContents_233) {
  RE2::Options opts = DefaultOptions();
  RE2::Anchor anchor = DefaultAnchor();
  RE2::Set set(opts, anchor);

  std::string err = "pre-filled error text";  // should not matter to Compile()
  EXPECT_GE(set.Add(absl::string_view("."), &err), 0);

  const bool compiled = set Compile();
  EXPECT_TRUE(compiled);
}

}  // namespace re2
