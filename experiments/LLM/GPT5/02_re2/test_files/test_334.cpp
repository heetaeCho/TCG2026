// File: regexp_ref_test_334.cc
#include <gtest/gtest.h>
#include "re2/regexp.h"

namespace re2 {

class RegexpRefTest_334 : public ::testing::Test {
protected:
  Regexp* re_ = nullptr;

  void SetUp() override {
    RegexpStatus status;
    // Use the public Parse factory to obtain a valid Regexp instance.
    // Choose a trivially valid pattern: "a".
    re_ = Regexp::Parse("a", Regexp::LikePerl, &status);
    ASSERT_NE(re_, nullptr) << "Parse should return a valid Regexp for a simple pattern";
  }

  void TearDown() override {
    if (re_ != nullptr) {
      // Balance the fixture's ownership reference.
      re_->Decref();
      re_ = nullptr;
    }
  }
};

// Verifies: Ref() returns a sensible positive count on a fresh, valid object.
TEST_F(RegexpRefTest_334, InitialRefIsPositive_334) {
  int r = re_->Ref();
  EXPECT_GE(r, 1) << "Initial reference count should be at least 1";
}

// Verifies: Calling Ref() twice without any intervening Incref/Decref returns the same value.
TEST_F(RegexpRefTest_334, RefIsStableWithoutChanges_334) {
  int r1 = re_->Ref();
  int r2 = re_->Ref();
  EXPECT_EQ(r1, r2) << "Ref() should be stable when no modifications occur";
}

// Verifies: Incref() observably increases the count seen via Ref(), and Decref() restores it.
TEST_F(RegexpRefTest_334, IncrefThenDecrefRestoresCount_334) {
  int base = re_->Ref();

  re_->Incref();  // public API; observable effect should be increased Ref()
  int after_inc = re_->Ref();
  EXPECT_EQ(after_inc, base + 1) << "Incref() should increase the reference count by one";

  re_->Decref();  // balance the incref
  int after_dec = re_->Ref();
  EXPECT_EQ(after_dec, base) << "Decref() should restore the previous count when balanced";
}

// Verifies: Multiple Incref() calls stack, and corresponding Decref() calls bring the count back down.
TEST_F(RegexpRefTest_334, MultipleIncrefDecrefBalance_334) {
  int base = re_->Ref();

  constexpr int kN = 5;
  for (int i = 0; i < kN; ++i) re_->Incref();
  EXPECT_EQ(re_->Ref(), base + kN) << "Reference count should reflect multiple increments";

  for (int i = 0; i < kN; ++i) re_->Decref();
  EXPECT_EQ(re_->Ref(), base) << "Reference count should return to base after balanced decrements";
}

// Verifies: Decref() does not destroy the object when the count remains >= 1 (observable: we can still call Ref()).
TEST_F(RegexpRefTest_334, DecrefDoesNotDestroyWhenCountAboveOne_334) {
  int base = re_->Ref();

  re_->Incref();  // ensure count > base, and therefore >= 2 in typical semantics
  re_->Decref();  // bring it back down; object should remain valid

  // If the object were destroyed, the next call would be UB; as an observable check,
  // we assert we can still call Ref() and get a sensible value.
  int now = re_->Ref();
  EXPECT_EQ(now, base) << "Object should remain valid with count >= 1";
}

}  // namespace re2
