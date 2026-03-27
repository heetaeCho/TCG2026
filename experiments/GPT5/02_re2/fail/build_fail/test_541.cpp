// File: prefilter_info_destructor_test_541.cc

#include <gtest/gtest.h>
#include "re2/prefilter.h"  // Assumes Prefilter/Info are declared here

using re2::Prefilter;

class PrefilterInfoTest_541 : public ::testing::Test {};

// [Behavior] TakeMatch transfers ownership so Info's destructor must NOT delete the Prefilter.
// Verifies: non-null from TakeMatch; deleting Info first, then deleting Prefilter does not crash.
TEST_F(PrefilterInfoTest_541, TakeMatchTransfersOwnership_541) {
  // Create an Info instance via a public factory (black-box).
  Prefilter::Info* info = Prefilter::Info::LiteralLatin1('a');
  ASSERT_NE(info, nullptr);

  // Taking the match should yield a non-null Prefilter* when created from a literal.
  Prefilter* match = info->TakeMatch();
  ASSERT_NE(match, nullptr);

  // Now delete the Info; since ownership has been transferred, this must not delete 'match'.
  delete info;

  // Deleting the Prefilter separately must be safe (no double-free).
  delete match;
}

// [Behavior] TakeMatch is idempotent with respect to ownership transfer.
// Verifies: second TakeMatch returns nullptr after the first transfer.
TEST_F(PrefilterInfoTest_541, TakeMatchIsIdempotent_541) {
  Prefilter::Info* info = Prefilter::Info::LiteralLatin1('b');
  ASSERT_NE(info, nullptr);

  Prefilter* first = info->TakeMatch();
  ASSERT_NE(first, nullptr);

  Prefilter* second = info->TakeMatch();
  EXPECT_EQ(second, nullptr) << "Second TakeMatch() should yield nullptr once ownership is moved.";

  // Clean up.
  delete info;
  delete first;
}

// [Behavior] If ownership is NOT transferred, Info's destructor should clean up its internal Prefilter.
// This is a smoke test: creating and deleting should be safe.
TEST_F(PrefilterInfoTest_541, DestructorDeletesOwnedMatch_Smoke_541) {
  Prefilter::Info* info = Prefilter::Info::LiteralLatin1('c');
  ASSERT_NE(info, nullptr);

  // Do not call TakeMatch(); deleting Info should safely clean up internal state.
  // (We cannot observe internal deletion directly; we only assert no crash.)
  delete info;

  SUCCEED();  // Reached here without crashes or leaks detectable at runtime.
}

// [Behavior] Factories produce Info objects with consistent TakeMatch semantics.
// - For something that obviously can match (e.g., AnyCharOrAnyByte / LiteralLatin1), TakeMatch should be non-null.
// - For NoMatch(), TakeMatch may reasonably be null (black-box expectation for a "no match" prefilter).
TEST_F(PrefilterInfoTest_541, FactoriesReturnExpectedMatchPresence_541) {
  // Likely produces a viable prefilter.
  {
    Prefilter::Info* info = Prefilter::Info::AnyCharOrAnyByte();
    ASSERT_NE(info, nullptr);
    Prefilter* p = info->TakeMatch();
    EXPECT_NE(p, nullptr) << "AnyCharOrAnyByte() should usually yield a usable prefilter via TakeMatch().";
    delete info;
    delete p;
  }

  // LiteralLatin1 should also usually produce a usable prefilter.
  {
    Prefilter::Info* info = Prefilter::Info::LiteralLatin1('Z');
    ASSERT_NE(info, nullptr);
    Prefilter* p = info->TakeMatch();
    EXPECT_NE(p, nullptr);
    delete info;
    delete p;
  }

  // NoMatch() is expected to represent an unsatisfiable prefilter; TakeMatch may be nullptr.
  {
    Prefilter::Info* info = Prefilter::Info::NoMatch();
    ASSERT_NE(info, nullptr);
    Prefilter* p = info->TakeMatch();
    EXPECT_EQ(p, nullptr) << "NoMatch() should not yield a usable Prefilter via TakeMatch().";
    delete info;
    // p is nullptr; no delete needed.
  }
}
