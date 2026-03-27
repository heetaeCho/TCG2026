// File: parse_do_left_paren_no_capture_test.cc
#include <gtest/gtest.h>
#include "re2/parse.cc"     // Provides re2::Regexp::ParseState body per project layout
#include "re2/regexp.h"     // Provides re2::Regexp with public cap_ field variant in this project

namespace re2 {

// A testable subclass that shadows PushRegexp to observe the argument.
// This does not re-implement internal logic; it only records the observable
// interaction (the Regexp* passed in) and returns a preset value.
class TestableParseState_502 : public Regexp::ParseState {
 public:
  TestableParseState_502(ParseFlags flags,
                         absl::string_view whole,
                         RegexpStatus* status)
      : Regexp::ParseState(flags, whole, status),
        last_re_(nullptr),
        push_return_(true) {}

  // Shadowing method with the exact same signature to capture the call.
  bool PushRegexp(Regexp* re) {
    last_re_ = re;
    return push_return_;
  }

  void SetPushReturn(bool v) { push_return_ = v; }
  Regexp* last_re() const { return last_re_; }

 private:
  Regexp* last_re_;
  bool push_return_;
};

// ---- Tests ----

TEST(DoLeftParenNoCapture_502, ReturnsTrueWhenUnderlyingPushSucceeds_502) {
  RegexpStatus status;
  TestableParseState_502 ps(static_cast<ParseFlags>(0), /*whole=*/"", &status);
  ps.SetPushReturn(true);

  const bool ok = ps.DoLeftParenNoCapture();

  ASSERT_TRUE(ok) << "DoLeftParenNoCapture should return what PushRegexp returns";
  ASSERT_NE(ps.last_re(), nullptr) << "Must push a non-null Regexp*";
  // Observable property from provided interface variant: cap_ is public.
  EXPECT_EQ(ps.last_re()->cap_, -1) << "Pushed Regexp must have cap_ == -1";
}

TEST(DoLeftParenNoCapture_502, ReturnsFalseWhenUnderlyingPushFails_502) {
  RegexpStatus status;
  TestableParseState_502 ps(static_cast<ParseFlags>(0), /*whole=*/"", &status);
  ps.SetPushReturn(false);

  const bool ok = ps.DoLeftParenNoCapture();

  ASSERT_FALSE(ok) << "DoLeftParenNoCapture should propagate PushRegexp failure";
  ASSERT_NE(ps.last_re(), nullptr) << "Should still attempt to push a Regexp*";
  EXPECT_EQ(ps.last_re()->cap_, -1) << "Even on failure, the constructed Regexp must have cap_ == -1";
}

TEST(DoLeftParenNoCapture_502, ConstructsNewRegexpEachCall_502) {
  RegexpStatus status;
  TestableParseState_502 ps(static_cast<ParseFlags>(0), /*whole=*/"", &status);
  ps.SetPushReturn(true);

  ASSERT_TRUE(ps.DoLeftParenNoCapture());
  Regexp* first = ps.last_re();
  ASSERT_NE(first, nullptr);
  EXPECT_EQ(first->cap_, -1);

  ASSERT_TRUE(ps.DoLeftParenNoCapture());
  Regexp* second = ps.last_re();
  ASSERT_NE(second, nullptr);
  EXPECT_EQ(second->cap_, -1);

  // Two calls should not reuse the same object pointer.
  EXPECT_NE(first, second) << "Each DoLeftParenNoCapture call should push a distinct Regexp instance";
}

}  // namespace re2
