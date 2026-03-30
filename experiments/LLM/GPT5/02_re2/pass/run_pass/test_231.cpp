// File: set_move_assignment_test_231.cc

#include <gtest/gtest.h>
#include <string>
#include <vector>

// RE2 headers (interface-only usage)
#include "re2/re2.h"
#include "re2/set.h"

using re2::RE2;

class SetMoveAssignmentTest_231 : public ::testing::Test {
protected:
  RE2::Options DefaultOptions() {
    RE2::Options opt;
    return opt; // default options; we don't depend on internals
  }
  RE2::Anchor DefaultAnchor() { return RE2::UNANCHORED; }
};

// Normal operation: after move-assigning, the destination behaves like the source
// (patterns and matching results come from the moved-from source, not the old dest).
TEST_F(SetMoveAssignmentTest_231, MoveAssign_CarriesPatternsAndBehavior_231) {
  RE2::Options opt = DefaultOptions();

  // Source setA with patterns "cat" and "dog"
  RE2::Set setA(opt, DefaultAnchor());
  int idx_cat = setA.Add("cat", /*error=*/nullptr);
  int idx_dog = setA.Add("dog", /*error=*/nullptr);
  ASSERT_GE(idx_cat, 0);
  ASSERT_GE(idx_dog, 0);
  ASSERT_TRUE(setA.Compile());

  // Destination setB with a different pattern "bird"
  RE2::Set setB(opt, DefaultAnchor());
  int idx_bird = setB.Add("bird", /*error=*/nullptr);
  ASSERT_GE(idx_bird, 0);
  ASSERT_TRUE(setB.Compile());

  // Move-assign: setB should now reflect setA's behavior
  setB = std::move(setA);

  // Matches should reflect the moved-from setA: "hotdog" should match "dog"
  {
    std::vector<int> hits;
    bool ok = setB.Match("hotdog", &hits);
    ASSERT_TRUE(ok);
    // We expect index 'idx_dog' to be among matches (observable via returned indices)
    EXPECT_NE(std::find(hits.begin(), hits.end(), idx_dog), hits.end());
  }

  // Text that previously matched only setB's old pattern should no longer match
  {
    std::vector<int> hits;
    bool ok = setB.Match("bird", &hits);
    // After move-assign, old "bird" pattern from setB should be gone
    EXPECT_FALSE(ok) << "Moved-to set should not retain pre-move patterns";
    EXPECT_TRUE(hits.empty());
  }
}

// Boundary: move-assign a *non-compiled* source into an empty destination,
// then compile and verify observable behavior works as expected.
TEST_F(SetMoveAssignmentTest_231, MoveAssign_FromUncompiled_ThenCompile_231) {
  RE2::Options opt = DefaultOptions();

  // Source setA has patterns but is NOT compiled
  RE2::Set setA(opt, DefaultAnchor());
  int idx_foo = setA.Add("foo", /*error=*/nullptr);
  int idx_bar = setA.Add("bar", /*error=*/nullptr);
  ASSERT_GE(idx_foo, 0);
  ASSERT_GE(idx_bar, 0);

  // Destination setB is empty and uncompiled
  RE2::Set setB(opt, DefaultAnchor());

  // Move-assign (no compilation yet)
  setB = std::move(setA);

  // Now compile the moved-to set and check behavior
  ASSERT_TRUE(setB.Compile());
  {
    std::vector<int> hits;
    EXPECT_TRUE(setB.Match("xxxbarzzz", &hits));
    EXPECT_NE(std::find(hits.begin(), hits.end(), idx_bar), hits.end());
  }
  {
    std::vector<int> hits;
    EXPECT_FALSE(setB.Match("nope", &hits));
    EXPECT_TRUE(hits.empty());
  }
}

// Overwrite an already-compiled destination with another compiled source.
// After move-assign, destination should match the source's patterns only.
TEST_F(SetMoveAssignmentTest_231, MoveAssign_OverwritesCompiledProgram_231) {
  RE2::Options opt = DefaultOptions();

  // Source setA compiled with "abc"
  RE2::Set setA(opt, DefaultAnchor());
  int idx_abc = setA.Add("abc", /*error=*/nullptr);
  ASSERT_GE(idx_abc, 0);
  ASSERT_TRUE(setA.Compile());

  // Destination setB compiled with "xyz"
  RE2::Set setB(opt, DefaultAnchor());
  int idx_xyz = setB.Add("xyz", /*error=*/nullptr);
  ASSERT_GE(idx_xyz, 0);
  ASSERT_TRUE(setB.Compile());

  // Move-assign
  setB = std::move(setA);

  // Should match "abc" (from source)
  {
    std::vector<int> hits;
    EXPECT_TRUE(setB.Match("123abc456", &hits));
    EXPECT_NE(std::find(hits.begin(), hits.end(), idx_abc), hits.end());
  }

  // Should NOT match "xyz" anymore (since setB's old program is gone)
  {
    std::vector<int> hits;
    EXPECT_FALSE(setB.Match("xyz", &hits));
    EXPECT_TRUE(hits.empty());
  }
}

// Exceptional/edge case: self move-assignment should not crash.
// Behavior after self-move is unspecified; we only assert that it remains usable
// in some observable way (e.g., can Compile and perform a Match call without crashing).
TEST_F(SetMoveAssignmentTest_231, SelfMoveAssignment_DoesNotCrash_231) {
  RE2::Options opt = DefaultOptions();
  RE2::Set s(opt, DefaultAnchor());
  int idx = s.Add("hello", /*error=*/nullptr);
  ASSERT_GE(idx, 0);

  // Self move-assignment
  // This is an edge case; we only verify it doesn't crash and the object remains usable.
  s = std::move(s);

  // Try to compile and match; if implementation doesn't support this, it may fail —
  // but the call should not crash. We accept either outcome as long as it’s observable.
  bool compiled = s.Compile();  // observable return
  std::vector<int> hits;
  (void) s.Match("hello", &hits);  // observable call; we do not assert the outcome
  SUCCEED();  // If we reach here without crashing, the edge case is handled gracefully.
}
