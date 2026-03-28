// File: simplify_walker_copy_test.cc

#include <gtest/gtest.h>

#include "re2/regexp.h"
// If SimplifyWalker has no public header, include the .cc directly so the test
// can see its public interface. Adjust the include path to your tree layout.
#include "re2/simplify.cc"

namespace re2 {

class SimplifyWalkerCopyTest_427 : public ::testing::Test {
protected:
  // Produce a small, valid Regexp via the public API only.
  static Regexp* MakeSimpleRegexp() {
    // Use Parse with zeroed flags (treating flags as a black-box enum).
    RegexpStatus status;
    Regexp* re = Regexp::Parse("a", static_cast<Regexp::ParseFlags>(0), &status);
    return re;
  }

  // Helper to fully dispose of a Regexp* by Decref'ing n times.
  static void DecrefNTimes(Regexp* re, int n) {
    for (int i = 0; i < n; ++i) {
      if (re) re->Decref();
    }
  }
};

// Normal behavior: Copy returns the same pointer and increases the reference count by 1.
TEST_F(SimplifyWalkerCopyTest_427, CopyIncrementsRefCountAndReturnsSamePointer_427) {
  std::unique_ptr<Regexp, void(*)(Regexp*)> holder(nullptr, [](Regexp* p){ /* no-op; manual cleanup below */ });

  Regexp* re = MakeSimpleRegexp();
  ASSERT_NE(re, nullptr) << "Failed to construct test regexp via public API";
  holder.reset(re);

  const int before = re->Ref();

  SimplifyWalker walker;
  Regexp* out = walker.Copy(re);

  EXPECT_EQ(out, re) << "Copy should return the same Regexp pointer";
  EXPECT_EQ(re->Ref(), before + 1) << "Copy should increase ref count by exactly 1";

  // Cleanup: two refs are live now (original + copy).
  DecrefNTimes(re, 2);
}

// Non-destructive: After Copy and then one Decref on the returned pointer,
// the original object should still be valid and observable via public API.
TEST_F(SimplifyWalkerCopyTest_427, CopyIsNonDestructive_427) {
  Regexp* re = MakeSimpleRegexp();
  ASSERT_NE(re, nullptr);

  std::string before_str = re->ToString();  // observable property

  SimplifyWalker walker;
  Regexp* out = walker.Copy(re);
  ASSERT_EQ(out, re);

  // Drop the extra ref we just took.
  out->Decref();

  // Object should remain valid; observable string should be unchanged.
  EXPECT_EQ(re->ToString(), before_str);

  // Final cleanup for the original reference.
  re->Decref();
}

// Reference arithmetic: multiple Copy calls should stack reference counts additively.
TEST_F(SimplifyWalkerCopyTest_427, MultipleCopiesIncreaseRefCountAccurately_427) {
  Regexp* re = MakeSimpleRegexp();
  ASSERT_NE(re, nullptr);

  const int before = re->Ref();

  SimplifyWalker walker;
  const int copies = 3;
  for (int i = 0; i < copies; ++i) {
    Regexp* out = walker.Copy(re);
    ASSERT_EQ(out, re);
  }

  EXPECT_EQ(re->Ref(), before + copies) << "Each Copy should add exactly 1 to ref count";

  // Cleanup: original + 3 copies
  DecrefNTimes(re, 1 + copies);
}

// Boundary-ish via public API: Pre-increase the refcount using Incref(),
// then verify Copy still increases it by exactly 1.
TEST_F(SimplifyWalkerCopyTest_427, CopyOnAlreadyRetainedObjectStillAddsOneRef_427) {
  Regexp* re = MakeSimpleRegexp();
  ASSERT_NE(re, nullptr);

  // Increase refcount through public API (observable).
  re->Incref();
  re->Incref();
  const int before = re->Ref();

  SimplifyWalker walker;
  Regexp* out = walker.Copy(re);
  ASSERT_EQ(out, re);

  EXPECT_EQ(re->Ref(), before + 1);

  // Cleanup: we now hold original + 2 Incref + 1 Copy = 4 total refs
  DecrefNTimes(re, 4);
}

}  // namespace re2
