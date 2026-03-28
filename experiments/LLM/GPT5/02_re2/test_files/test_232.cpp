// File: set_add_test_232.cc
#include "gtest/gtest.h"
#include "re2/re2.h"
#include "re2/set.h"

using re2::RE2;

class RE2SetAddTest_232 : public ::testing::Test {
protected:
  RE2::Options DefaultOpts(bool log_errors = false) {
    RE2::Options opts;
    opts.set_log_errors(log_errors);
    return opts;
  }
};

// Normal operation: first successful Add returns index 0.
TEST_F(RE2SetAddTest_232, Add_ReturnsZeroForFirstPattern_232) {
  RE2::Set set(DefaultOpts(), RE2::UNANCHORED);
  std::string error;
  int idx = set.Add("a", &error);
  EXPECT_EQ(idx, 0);
}

// Normal operation: multiple successful Adds return sequential indices.
TEST_F(RE2SetAddTest_232, Add_ReturnsSequentialIndicesForMultipleAdds_232) {
  RE2::Set set(DefaultOpts(), RE2::UNANCHORED);
  EXPECT_EQ(set.Add("foo", nullptr), 0);
  EXPECT_EQ(set.Add("bar", nullptr), 1);
  EXPECT_EQ(set.Add("baz", nullptr), 2);
}

// Boundary condition: empty pattern should be accepted and return next index.
TEST_F(RE2SetAddTest_232, Add_AllowsEmptyPattern_232) {
  RE2::Set set(DefaultOpts(), RE2::UNANCHORED);
  EXPECT_EQ(set.Add("", nullptr), 0);
  EXPECT_EQ(set.Add("x", nullptr), 1);
}

// Normal operation: adding the same pattern twice returns distinct indices.
TEST_F(RE2SetAddTest_232, Add_AllowsDuplicatePatternsAndReturnsNewIndex_232) {
  RE2::Set set(DefaultOpts(), RE2::UNANCHORED);
  EXPECT_EQ(set.Add("dup", nullptr), 0);
  EXPECT_EQ(set.Add("dup", nullptr), 1);
}

// Exceptional case: invalid pattern returns -1 and populates error (if provided).
TEST_F(RE2SetAddTest_232, Add_InvalidPatternReturnsMinusOneAndSetsError_232) {
  RE2::Set set(DefaultOpts(), RE2::UNANCHORED);
  std::string error;
  int idx = set.Add("(", &error);  // Unbalanced parenthesis should fail to parse.
  EXPECT_EQ(idx, -1);
  // We only assert that an error message was provided (content is implementation-defined).
  EXPECT_FALSE(error.empty());
}

// Post-compile behavior: Add after Compile() should fail with -1.
TEST_F(RE2SetAddTest_232, Add_AfterCompileReturnsMinusOne_232) {
  RE2::Set set(DefaultOpts(), RE2::UNANCHORED);
  ASSERT_EQ(set.Add("a", nullptr), 0);
  ASSERT_TRUE(set.Compile());  // Treat as black box; only observable effect we rely on is Add() now failing.
  std::string error;
  EXPECT_EQ(set.Add("b", &error), -1);
}

// Exceptional case: invalid pattern with nullptr error pointer should not crash and returns -1.
TEST_F(RE2SetAddTest_232, Add_NullErrorPointerOnParseError_ReturnsMinusOne_232) {
  RE2::Set set(DefaultOpts(), RE2::UNANCHORED);
  int idx = set.Add("(", nullptr);
  EXPECT_EQ(idx, -1);
}
