// File: set_dtor_tests_230.cc
#include <gtest/gtest.h>
#include <string>
#include <vector>

// Use the project headers as provided by the codebase layout in the prompt.
#include "re2/set.h"     // RE2::Set (per prompt's path)
#include "re2/re2.h"     // RE2, RE2::Options, RE2::Anchor (usual RE2 entrypoint)

using ::re2::RE2;

// A tiny helper to build a default Set without leaking re2 internals.
static RE2::Set MakeDefaultSet(RE2::Anchor anchor = RE2::UNANCHORED) {
  RE2::Options options;
  return RE2::Set(options, anchor);
}

// ----------------------------------------------------------------------------
// Empty set goes out of scope (destructor) -> no crash / UB.
// ----------------------------------------------------------------------------
TEST(RE2_Set_Destructor_Empty_230, DestroyEmptySet_NoCrash_230) {
  {
    auto set = MakeDefaultSet();
    // Nothing added; just ensure destruction at scope exit is safe.
  }
  SUCCEED();  // If we got here, destructor did not crash.
}

// ----------------------------------------------------------------------------
// Add a handful of simple patterns; ensure Add returns distinct, increasing ids,
// optional Compile succeeds; then let the set be destroyed without issues.
// ----------------------------------------------------------------------------
TEST(RE2_Set_Destructor_WithAddedPatterns_230, AddAndDestroy_NoCrash_230) {
  int id0 = -1, id1 = -1, id2 = -1, id3 = -1;
  {
    auto set = MakeDefaultSet();

    // Normal operation: Add valid patterns; verify observable return values.
    id0 = set.Add("a", /*error=*/nullptr);
    id1 = set.Add("b|c", /*error=*/nullptr);
    id2 = set.Add(".*", /*error=*/nullptr);
    id3 = set.Add("\\d+", /*error=*/nullptr);

    ASSERT_GE(id0, 0);
    EXPECT_EQ(id1, id0 + 1);
    EXPECT_EQ(id2, id1 + 1);
    EXPECT_EQ(id3, id2 + 1);

    // Boundary-ish: compile after a few patterns; should be okay to destroy later.
    EXPECT_TRUE(set Compile());
  }
  SUCCEED();
}

// ----------------------------------------------------------------------------
// Compile first, then destroy. Ensures destructor behaves in compiled state.
// ----------------------------------------------------------------------------
TEST(RE2_Set_Destructor_AfterCompile_230, CompileThenDestroy_NoCrash_230) {
  {
    auto set = MakeDefaultSet(RE2::UNANCHORED);
    ASSERT_GE(set.Add("hello", nullptr), 0);
    ASSERT_GE(set.Add("world|earth", nullptr), 0);

    // After compile, object is in a different observable state; still must destruct cleanly.
    ASSERT_TRUE(set.Compile());

    // Optional observable: run a match just to ensure compiled set is usable.
    std::vector<int> matches;
    EXPECT_TRUE(set.Match("helloworld", &matches));
  }  // destructor should run cleanly here
  SUCCEED();
}

// ----------------------------------------------------------------------------
// Move-construct a set and destroy both (moved-from, moved-to) cleanly.
// This verifies safe transfer of ownership of any internal elements and that
// neither double-frees nor leaks are observable via crashes.
// ----------------------------------------------------------------------------
TEST(RE2_Set_Destructor_MoveConstruct_230, MoveThenDestroy_NoCrash_230) {
  {
    auto original = MakeDefaultSet(RE2::UNANCHORED);
    ASSERT_GE(original.Add("x+", nullptr), 0);
    ASSERT_GE(original.Add("(ab)?c", nullptr), 0);
    ASSERT_TRUE(original.Compile());

    // Move-construct
    RE2::Set moved(std::move(original));

    // Use the moved-to set to confirm it remains functional.
    std::vector<int> v;
    EXPECT_TRUE(moved.Match("xxabcc", &v) || moved.Match("xxc", &v));

    // Both 'original' (moved-from) and 'moved' will be destroyed at scope end.
    // The test ensures no crashes or UB on destruction paths.
  }
  SUCCEED();
}

// ----------------------------------------------------------------------------
/*
  Edge-ish path: Add a mix of likely-valid and likely-invalid patterns.
  Observable behavior: Add returns an index for accepted patterns; for invalid
  ones, typical RE2::Set::Add behavior is to return -1 and optionally fill error.
  We do not assert specific parsing logic beyond return codes; we only assert
  destruction safety after such operations.
*/
// ----------------------------------------------------------------------------
TEST(RE2_Set_Destructor_WithInvalidPatterns_230, InvalidThenDestroy_NoCrash_230) {
  {
    auto set = MakeDefaultSet();

    std::string err;
    const int ok_id = set.Add("[a-z]+", &err);
    ASSERT_GE(ok_id, 0);
    EXPECT_TRUE(err.empty());

    // Try a (likely) invalid pattern; do not assume internal parse logic—just
    // observe return value and that error may be populated.
    const int bad_id = set.Add("(*invalid_syntax", &err);
    // We accept either behavior (depending on actual parser): -1 with error set,
    // or non-negative if the engine accepts it. We only check invariants we can rely on.
    if (bad_id < 0) {
      EXPECT_FALSE(err.empty());
    }

    // Whether or not compile succeeds, destructor must be safe.
    (void)set.Compile();
  }
  SUCCEED();
}
