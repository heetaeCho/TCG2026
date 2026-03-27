// File: coalesce_walker_copy_test_424.cc

#include "gtest/gtest.h"
#include "re2/regexp.h"

// If CoalesceWalker is defined in a separate header in your tree, include it.
// Based on the provided partial code, it lives in namespace re2 and exposes Copy(Regexp*).
// #include "re2/simplify.h"  // (Use the actual header if available.)

namespace re2 {

// Minimal declaration matching the provided partial snippet to access Copy.
// In your real tree, prefer including the actual header that declares CoalesceWalker.
class CoalesceWalker {
 public:
  Regexp* Copy(Regexp* re) { return re->Incref(); }
};

}  // namespace re2

namespace {

using re2::CoalesceWalker;
using re2::Regexp;

// Helper to create a simple, valid Regexp instance via public factories.
static Regexp* MakeLiteral(char c) {
  // ParseFlags is an enum; using 0 as "no flags" keeps this black-box and portable.
  auto flags = static_cast<Regexp::ParseFlags>(0);
  return Regexp::NewLiteral(static_cast<int>(c), flags);
}

// TEST_ID: 424
TEST(CoalesceWalkerCopyTest_424, CopyIncrementsRefAndReturnsSamePointer_424) {
  Regexp* re = MakeLiteral('a');
  ASSERT_NE(re, nullptr);

  const int before = re->Ref();
  CoalesceWalker cw;

  Regexp* out = cw.Copy(re);

  EXPECT_EQ(out, re) << "Copy should return the same Regexp pointer";
  EXPECT_EQ(re->Ref(), before + 1) << "Copy should increase the reference count by 1";

  // Cleanup: balance references. We held one from construction and one from Copy.
  re->Decref();  // undo Copy
  re->Decref();  // release original
}

// TEST_ID: 424
TEST(CoalesceWalkerCopyTest_424, MultipleCopiesAccumulateRefCount_424) {
  Regexp* re = MakeLiteral('b');
  ASSERT_NE(re, nullptr);

  const int start = re->Ref();
  CoalesceWalker cw;

  Regexp* r1 = cw.Copy(re);
  Regexp* r2 = cw.Copy(re);
  Regexp* r3 = cw.Copy(re);

  EXPECT_EQ(r1, re);
  EXPECT_EQ(r2, re);
  EXPECT_EQ(r3, re);
  EXPECT_EQ(re->Ref(), start + 3) << "Three copies should add three references";

  // Cleanup: remove the three extra refs and the original.
  re->Decref();
  re->Decref();
  re->Decref();
  re->Decref();
}

// TEST_ID: 424
TEST(CoalesceWalkerCopyTest_424, DecrefRestoresRefCountAfterCopy_424) {
  Regexp* re = MakeLiteral('c');
  ASSERT_NE(re, nullptr);

  CoalesceWalker cw;
  const int before = re->Ref();

  cw.Copy(re);  // +1
  EXPECT_EQ(re->Ref(), before + 1);

  re->Decref();  // -1, should return to original count
  EXPECT_EQ(re->Ref(), before);

  // Final release of the original reference.
  re->Decref();
}

// TEST_ID: 424
TEST(CoalesceWalkerCopyTest_424, CopyAffectsOnlyTargetRegexp_424) {
  Regexp* a = MakeLiteral('x');
  Regexp* b = MakeLiteral('y');
  ASSERT_NE(a, nullptr);
  ASSERT_NE(b, nullptr);

  CoalesceWalker cw;
  const int a_before = a->Ref();
  const int b_before = b->Ref();

  cw.Copy(a);  // +1 to 'a' only

  EXPECT_EQ(a->Ref(), a_before + 1) << "Copy should affect target regexp 'a'";
  EXPECT_EQ(b->Ref(), b_before)     << "Copy should not affect unrelated regexp 'b'";

  // Cleanup: balance refs. 'a' has +1 from Copy in addition to original.
  a->Decref();  // undo Copy
  a->Decref();  // release original
  b->Decref();  // release original
}

}  // namespace
