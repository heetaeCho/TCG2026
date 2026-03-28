// File: prefilter_walker_shortvisit_test_560.cc

#include <gtest/gtest.h>
#include "re2/regexp.h"      // for Rune typedef and general RE2 types
// If there is a dedicated header for Prefilter, include it instead.
// The partials indicate the types live under re2::Prefilter::Info::Walker.
#include "re2/prefilter.h"   // adjust include path if needed

namespace {

using re2::Prefilter;
using re2::Rune;

// Helper that returns the canonical string representation for AnyMatch()
// without assuming what the string actually is.
static std::string AnyMatchString() {
  std::unique_ptr<Prefilter::Info> any(Prefilter::Info::AnyMatch());
  return any->ToString();
}

// --- Tests ---

// Verifies: ShortVisit returns a non-null Info* that is equivalent (by ToString())
// to Info::AnyMatch(), when constructed with latin1=true, and given nullptr args.
TEST(PrefilterWalkerTest_560, ShortVisit_ReturnsAnyMatch_Latin1True_560) {
  Prefilter::Info::Walker walker(/*latin1=*/true);

  Prefilter::Info* result = walker.ShortVisit(/*re=*/nullptr, /*parent_arg=*/nullptr);

  ASSERT_NE(result, nullptr);
  EXPECT_EQ(result->ToString(), AnyMatchString());
}

// Verifies: ShortVisit returns a non-null Info* that is equivalent to AnyMatch()
// when constructed with latin1=false, and given nullptr args.
TEST(PrefilterWalkerTest_560, ShortVisit_ReturnsAnyMatch_Latin1False_560) {
  Prefilter::Info::Walker walker(/*latin1=*/false);

  Prefilter::Info* result = walker.ShortVisit(/*re=*/nullptr, /*parent_arg=*/nullptr);

  ASSERT_NE(result, nullptr);
  EXPECT_EQ(result->ToString(), AnyMatchString());
}

// Verifies: ShortVisit ignores the parent_arg value (observable as it still
// returns the AnyMatch-equivalent object). We pass a concrete parent Info and
// ensure the returned object matches AnyMatch() rather than the parent's string.
TEST(PrefilterWalkerTest_560, ShortVisit_IgnoresParentArg_AndStillReturnsAnyMatch_560) {
  Prefilter::Info::Walker walker(/*latin1=*/true);

  // Create a distinct parent Info (choose any available constructor).
  std::unique_ptr<Prefilter::Info> parent(Prefilter::Info::LiteralLatin1(static_cast<Rune>('X')));
  ASSERT_NE(parent, nullptr);
  const std::string parent_str = parent->ToString();

  Prefilter::Info* result = walker.ShortVisit(/*re=*/nullptr, /*parent_arg=*/parent.get());

  ASSERT_NE(result, nullptr);
  const std::string anymatch_str = AnyMatchString();

  // Returned value must look like AnyMatch().
  EXPECT_EQ(result->ToString(), anymatch_str);

  // And it should differ from the parent's representation (showing parent_arg is not propagated).
  // (If an implementation ever made LiteralLatin1('X') stringify like AnyMatch, this would still pass
  // the primary equality check above and this inequality would catch an accidental collision.)
  EXPECT_NE(parent_str, anymatch_str);
}

}  // namespace
