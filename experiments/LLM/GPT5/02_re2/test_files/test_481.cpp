// File: parse_state_dtor_tests_481.cc
#include <gtest/gtest.h>
#include "re2/regexp.h"        // Provides re2::Regexp and nested ParseState (per project)
#include "absl/strings/string_view.h"

namespace {

using re2::Regexp;

// Helper to build a minimal ParseState safely.
static Regexp::ParseState MakeState() {
  // Flags treated as a black box; default-construct/zero-init is fine for interface tests.
  typename std::remove_reference<decltype(std::declval<Regexp::ParseState&>().flags())>::type flags{};
  absl::string_view whole("");
  RegexpStatus* status = nullptr;
  return Regexp::ParseState(flags, whole, status);
}

// 1) Destructor should safely handle an empty stack.
TEST(ParseStateDestructor_481, EmptyStateSafe_481) {
  {
    auto ps = MakeState();
    SUCCEED() << "Constructed ParseState; will leave scope to invoke destructor.";
  }
  SUCCEED() << "Destructor completed without crashes for empty state.";
}

// 2) Unmatched left-paren with a name should be safely cleaned up by destructor.
//    This exercises the code path that iterates the internal stack and disposes
//    of any pending markers/resources.
TEST(ParseStateDestructor_481, UnmatchedNamedLeftParenCleanedOnDestruction_481) {
  {
    auto ps = MakeState();
    // Black-box usage: request a named capture start, but intentionally don't close it.
    // We don't assert on return value semantics; we only verify no crash/UB on destruction.
    (void)ps.DoLeftParen(absl::string_view("groupName"));
  }
  SUCCEED() << "Destructor cleaned up after an unmatched named left-paren without crashing.";
}

// 3) Matched left/right paren sequence should also be fine when destroyed.
//    Ensures there is no double-free or post-pop cleanup mishap.
TEST(ParseStateDestructor_481, MatchedParenSequenceSafeOnDestruction_481) {
  {
    auto ps = MakeState();
    (void)ps.DoLeftParen(absl::string_view("cap"));
    // If the interface accepts right-paren, invoke it; treat return as black-box.
    (void)ps.DoRightParen();
  }
  SUCCEED() << "Destructor after matched paren sequence completed without crashes.";
}

// 4) A few common push operations should be callable and safe under destruction.
//    We do not assert specific return values (black-box), only that the calls are valid and
//    the final destruction path is safe.
TEST(ParseStateDestructor_481, MixedOperationsAreCallableAndDestructorSafe_481) {
  {
    auto ps = MakeState();
    (void)ps.PushCaret();
    (void)ps.PushDot();
    (void)ps.PushDollar();
    (void)ps.DoVerticalBar();   // Alternation marker
    // Do not force a full build/finish; we’re testing partial states as well.
  }
  SUCCEED() << "Destructor safely handled mixed, partially-built state.";
}

// 5) Calling DoFinish/FinishRegexp on an otherwise simple/empty state should be safe
//    and not leave the destructor with anything problematic.
//    We don't assert on exact return value or ownership semantics; just no crash.
TEST(ParseStateDestructor_481, FinishOperationsDoNotBreakDestructor_481) {
  {
    auto ps = MakeState();
    // DoFinish returns Regexp*, FinishRegexp takes a Regexp*; both are observable only
    // through their signatures, so we avoid assumptions and only exercise the calls.
    Regexp* built = ps.DoFinish();       // May return nullptr for empty/invalid; black-box.
    (void)ps.FinishRegexp(built);        // As interface allows.
    // Intentionally do not use 'built' further; destructor should cope with whatever state remains.
  }
  SUCCEED() << "Destructor remained safe after finish-related calls.";
}

}  // namespace
