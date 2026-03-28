// File: re2_destructor_test_243.cc
#include <gtest/gtest.h>
#include "re2/re2.h"

using re2::RE2;

class RE2DestructorTest_243 : public ::testing::Test {};

// [Normal] Simple pattern compiles, can be used, and destroys cleanly.
TEST_F(RE2DestructorTest_243, BasicLifecycle_SimplePattern_243) {
  RE2 re("abc");
  ASSERT_TRUE(re.ok());
  EXPECT_EQ(re.pattern(), "abc");

  // Basic observable behavior checks (no assumptions about internals).
  EXPECT_TRUE(RE2::FullMatch("xxabcxx", re));   // Partial vs Full: RE2::FullMatch matches whole text
  EXPECT_FALSE(RE2::FullMatch("xxabcxx", RE2("abc"))); // temporary, also validates ctor/dtor path

  // Program metrics are observable functions; only assert they are non-negative.
  EXPECT_GE(re.ProgramSize(), 0);
  EXPECT_GE(re.ReverseProgramSize(), 0);

  // Fanout APIs should be callable and return non-negative counts.
  std::vector<int> hist, rhist;
  EXPECT_GE(re.ProgramFanout(&hist), 0);
  EXPECT_GE(re.ReverseProgramFanout(&rhist), 0);
}

// [Normal + Named groups] Ensure maps exist and are consistent; destruction must be safe.
TEST_F(RE2DestructorTest_243, Lifecycle_NamedGroups_243) {
  RE2 re("(?P<word>\\w+)-(\\d+)");
  ASSERT_TRUE(re.ok());

  const auto& by_name = re.NamedCapturingGroups();
  const auto& by_index = re.CapturingGroupNames();

  // NamedCapturingGroups should contain our name "word" -> index (commonly 1).
  ASSERT_TRUE(by_name.find("word") != by_name.end());
  int idx = by_name.at("word");
  EXPECT_GE(idx, 1);                   // index is observable but don't over-specify
  ASSERT_TRUE(by_index.find(idx) != by_index.end());
  EXPECT_EQ(by_index.at(idx), "word"); // round-trip consistency
}

// [Error/Exceptional] Invalid pattern produces non-ok(), with observable error string.
TEST_F(RE2DestructorTest_243, Lifecycle_ErrorState_243) {
  RE2 re("(");           // Unbalanced parenthesis should fail to compile
  EXPECT_FALSE(re.ok()); // Observable failure

  // error() should be non-empty (do not assume specific wording).
  EXPECT_FALSE(re.error().empty());

  // error_arg() may or may not be set depending on failure path; just ensure callable.
  (void)re.error_arg();  // No assertion beyond being accessible without crash
}

// [Boundary/Stress] Create and destroy many RE2 objects across success/failure paths.
TEST_F(RE2DestructorTest_243, Stress_CreateDestroyMany_243) {
  for (int i = 0; i < 100; ++i) {
    // Alternate valid/invalid patterns to touch different destructor branches.
    if (i % 3 == 0) {
      RE2 re("a(b)c");                // capturing
      ASSERT_TRUE(re.ok());
      EXPECT_TRUE(RE2::PartialMatch("xxabcxx", re));
    } else if (i % 3 == 1) {
      RE2 re("(?P<n>\\d{2,4})");      // named group
      ASSERT_TRUE(re.ok());
      const auto& by_name = re.NamedCapturingGroups();
      ASSERT_TRUE(by_name.find("n") != by_name.end());
    } else {
      RE2 re("(");                    // invalid
      EXPECT_FALSE(re.ok());
      EXPECT_FALSE(re.error().empty());
    }
    // Loop scope exit triggers destructor for each instance; test passes if no crash.
  }
}
