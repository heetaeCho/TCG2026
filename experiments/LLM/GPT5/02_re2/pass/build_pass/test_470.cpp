// File: filtered_re2_tests_470.cc

#include <gtest/gtest.h>
#include "re2/re2.h"
#include "re2/filtered_re2.h"

using re2::FilteredRE2;
using re2::RE2;

namespace {

// --- Normal operation: Add valid patterns, retrieve via API, and count ----
TEST(FilteredRE2_470, AddAndGetRE2_ReturnsIdsAndPatterns_470) {
  FilteredRE2 f;
  RE2::Options opts;

  int id1 = -1;
  int id2 = -1;

  auto ec1 = f.Add("foo", opts, &id1);
  auto ec2 = f.Add("bar", opts, &id2);

  EXPECT_EQ(ec1, RE2::NoError);
  EXPECT_EQ(ec2, RE2::NoError);

  // IDs should be non-negative and distinct (observable via interface).
  EXPECT_GE(id1, 0);
  EXPECT_GE(id2, 0);
  EXPECT_NE(id1, id2);

  // NumRegexps should reflect how many we added.
  EXPECT_EQ(f.NumRegexps(), 2);

  // GetRE2 should return objects whose patterns match what we added.
  const RE2& r1 = f.GetRE2(id1);
  const RE2& r2 = f.GetRE2(id2);
  EXPECT_EQ(r1.pattern(), "foo");
  EXPECT_EQ(r2.pattern(), "bar");
}

// --- Error case: adding an invalid pattern should report an error and not increase count ---
TEST(FilteredRE2_470, AddInvalidPattern_ReportsErrorAndDoesNotIncreaseCount_470) {
  FilteredRE2 f;
  RE2::Options opts;

  EXPECT_EQ(f.NumRegexps(), 0);

  int bad_id = 12345; // sentinel; we won't assert its value post-call (black-box)
  auto ec = f.Add("(", opts, &bad_id);  // invalid regex

  // Do not assert specific error code—only that it's not NoError (observable behavior).
  EXPECT_NE(ec, RE2::NoError);

  // Count should still be zero since the pattern wasn't added (observable via interface).
  EXPECT_EQ(f.NumRegexps(), 0);
}

// --- Move constructor should transfer ownership/contents in an observable way ---
TEST(FilteredRE2_470, MoveConstructor_TransfersPatternsAndIds_470) {
  RE2::Options opts;

  int id_a = -1;
  int id_b = -1;

  {
    FilteredRE2 source;
    ASSERT_EQ(source.Add("alpha", opts, &id_a), RE2::NoError);
    ASSERT_EQ(source.Add("beta",  opts, &id_b), RE2::NoError);
    ASSERT_EQ(source.NumRegexps(), 2);

    // Move-construct target from source.
    FilteredRE2 target(std::move(source));

    // Target should expose the patterns by their ids.
    EXPECT_EQ(target.NumRegexps(), 2);
    EXPECT_EQ(target.GetRE2(id_a).pattern(), "alpha");
    EXPECT_EQ(target.GetRE2(id_b).pattern(), "beta");

    // We intentionally do NOT assert anything about the moved-from object,
    // as its state is unspecified by the public interface.
  }
}

// --- Move assignment should transfer ownership/contents in an observable way ---
TEST(FilteredRE2_470, MoveAssignment_TransfersPatternsAndIds_470) {
  RE2::Options opts;

  int id_x = -1;
  int id_y = -1;

  FilteredRE2 lhs;  // Will receive via move assignment
  {
    FilteredRE2 rhs;
    ASSERT_EQ(rhs.Add("xray",  opts, &id_x), RE2::NoError);
    ASSERT_EQ(rhs.Add("yankee",opts, &id_y), RE2::NoError);
    ASSERT_EQ(rhs.NumRegexps(), 2);

    // Move-assign into lhs.
    lhs = std::move(rhs);
  }

  // After move assignment, lhs should present the transferred regexps.
  EXPECT_EQ(lhs.NumRegexps(), 2);
  EXPECT_EQ(lhs.GetRE2(id_x).pattern(), "xray");
  EXPECT_EQ(lhs.GetRE2(id_y).pattern(), "yankee");
}

// --- Destructor safety: object with added regexps goes out of scope without issues ---
TEST(FilteredRE2_470, Destructor_DestroysInternalsWithoutCrashing_470) {
  RE2::Options opts;

  // Create a nested scope to force deterministic destruction and ensure no crash.
  {
    FilteredRE2 f;
    int id = -1;
    ASSERT_EQ(f.Add("quux", opts, &id), RE2::NoError);
    ASSERT_EQ(f.NumRegexps(), 1);

    // Access the RE2 before destruction to ensure it exists.
    const RE2& r = f.GetRE2(id);
    EXPECT_EQ(r.pattern(), "quux");
  }

  // If destructor mismanages resources, sanitizers or the test run would reveal it.
  SUCCEED() << "FilteredRE2 destroyed cleanly without observable issues.";
}

}  // namespace
