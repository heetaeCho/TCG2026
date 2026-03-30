// File: coalesce_walker_shortvisit_test.cc

#include "gtest/gtest.h"
#include "re2/regexp.h"

// Forward declaration for the SUT (it's defined in simplify.cc, not a public header).
namespace re2 {
class CoalesceWalker {
 public:
  Regexp* ShortVisit(Regexp* re, Regexp* parent_arg);
};
}  // namespace re2

namespace {

using re2::CoalesceWalker;
using re2::Regexp;

static Regexp::ParseFlags kNoFlags =
    static_cast<Regexp::ParseFlags>(0);

// Helper that creates a simple Regexp (single literal) with refcount 1.
static Regexp* MakeLiteral(char ch) {
  // NewLiteral takes a Rune, but char is fine for ASCII.
  return Regexp::NewLiteral(static_cast<int>(static_cast<unsigned char>(ch)), kNoFlags);
}

// --- Tests ---

// Verifies: ShortVisit returns the same Regexp pointer and Incref() side effect
// is observable as refcount +1.
TEST(CoalesceWalker_ShortVisit_425, ReturnsSamePointerAndIncrementsRef_425) {
  Regexp* re = MakeLiteral('a');
  ASSERT_NE(re, nullptr);

  const int before = re->Ref();

  CoalesceWalker walker;
  Regexp* ret = walker.ShortVisit(re, /*parent_arg=*/nullptr);

  // Returns same pointer.
  EXPECT_EQ(ret, re);

  // Refcount increased by 1.
  EXPECT_EQ(re->Ref(), before + 1);

  // Clean up both references (the original + the incref from ShortVisit).
  ret->Decref();  // balances ShortVisit's Incref
  re->Decref();   // balances factory's initial ref
}

// Verifies: Passing a null parent is allowed and has the same observable effects.
TEST(CoalesceWalker_ShortVisit_425, AcceptsNullParent_425) {
  Regexp* re = MakeLiteral('x');
  ASSERT_NE(re, nullptr);

  const int before = re->Ref();

  CoalesceWalker walker;
  Regexp* ret = walker.ShortVisit(re, /*parent_arg=*/nullptr);

  EXPECT_EQ(ret, re);
  EXPECT_EQ(re->Ref(), before + 1);

  // Cleanup.
  ret->Decref();
  re->Decref();
}

// Verifies: ShortVisit does not change other observable properties of the
// Regexp object (besides reference count). We use ToString() as an observable.
TEST(CoalesceWalker_ShortVisit_425, DoesNotMutateRegexpContents_425) {
  Regexp* re = MakeLiteral('z');
  ASSERT_NE(re, nullptr);

  const std::string before_str = re->ToString();

  CoalesceWalker walker;
  Regexp* ret = walker.ShortVisit(re, /*parent_arg=*/nullptr);

  // The string representation remains the same (no observable mutation).
  EXPECT_EQ(ret->ToString(), before_str);

  // Cleanup.
  ret->Decref();
  re->Decref();
}

}  // namespace
