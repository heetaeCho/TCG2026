// File: ParseCCRangeTest_530.cc

#include <gtest/gtest.h>
#include <string>
#include "absl/strings/string_view.h"

// Access the nested ParseState and its method under test.
#include "re2/regexp.h"
#include "re2/parse.cc"

namespace {

using re2::Regexp;
using re2::RegexpStatus;
using re2::RuneRange;
using re2::kRegexpBadCharRange;

class ParseCCRangeTest_530 : public ::testing::Test {
 protected:
  // Helper to construct a ParseState. We keep status_ alive for the lifetime
  // of the ParseState instance to avoid dangling pointers.
  struct StateBundle {
    RegexpStatus status;
    Regexp::ParseState state;
    StateBundle(re2::ParseFlags flags, absl::string_view whole)
        : status(),
          state(flags, whole, &status) {}
  };
};

TEST_F(ParseCCRangeTest_530, SingleCharNoDashSetsHiEqualsLo_530) {
  ParseCCRangeTest_530::StateBundle bundle(static_cast<re2::ParseFlags>(0), "[]");
  absl::string_view s = "a]";
  RuneRange rr;
  RegexpStatus call_status;

  bool ok = bundle.state.ParseCCRange(&s, &rr, /*whole_class=*/"a]", &call_status);

  ASSERT_TRUE(ok);
  EXPECT_EQ(rr.lo, rr.hi);
  EXPECT_EQ(rr.lo, static_cast<int>('a'));
  EXPECT_EQ(s, absl::string_view("]"));  // input advanced by one char
  EXPECT_TRUE(call_status.ok());
}

TEST_F(ParseCCRangeTest_530, RangeParsesAscending_530) {
  ParseCCRangeTest_530::StateBundle bundle(static_cast<re2::ParseFlags>(0), "[a-b]");
  absl::string_view s = "a-b]";
  RuneRange rr;
  RegexpStatus call_status;

  bool ok = bundle.state.ParseCCRange(&s, &rr, /*whole_class=*/"a-b]", &call_status);

  ASSERT_TRUE(ok);
  EXPECT_EQ(rr.lo, static_cast<int>('a'));
  EXPECT_EQ(rr.hi, static_cast<int>('b'));
  EXPECT_EQ(s, absl::string_view("]"));  // consumed "-b"
  EXPECT_TRUE(call_status.ok());
}

TEST_F(ParseCCRangeTest_530, DashBeforeRightBracketIsNotRange_530) {
  ParseCCRangeTest_530::StateBundle bundle(static_cast<re2::ParseFlags>(0), "[a-]");
  absl::string_view s = "a-]";
  RuneRange rr;
  RegexpStatus call_status;

  bool ok = bundle.state.ParseCCRange(&s, &rr, /*whole_class=*/"a-]", &call_status);

  ASSERT_TRUE(ok);
  // Not treated as a range because the next char after '-' is ']'
  EXPECT_EQ(rr.lo, rr.hi);
  EXPECT_EQ(rr.lo, static_cast<int>('a'));
  EXPECT_EQ(s, absl::string_view("-]"));  // '-' left for caller to handle
  EXPECT_TRUE(call_status.ok());
}

TEST_F(ParseCCRangeTest_530, IncompleteTrailingDashIsNotRange_530) {
  ParseCCRangeTest_530::StateBundle bundle(static_cast<re2::ParseFlags>(0), "[a-");
  absl::string_view s = "a-";  // size after first char would be 1 (<2), so not a range
  RuneRange rr;
  RegexpStatus call_status;

  bool ok = bundle.state.ParseCCRange(&s, &rr, /*whole_class=*/"a-", &call_status);

  ASSERT_TRUE(ok);
  EXPECT_EQ(rr.lo, rr.hi);
  EXPECT_EQ(rr.lo, static_cast<int>('a'));
  EXPECT_EQ(s, absl::string_view("-"));  // '-' remains
  EXPECT_TRUE(call_status.ok());
}

TEST_F(ParseCCRangeTest_530, EqualEndpointsRangeAllowed_530) {
  ParseCCRangeTest_530::StateBundle bundle(static_cast<re2::ParseFlags>(0), "[a-a]");
  absl::string_view s = "a-a]";
  RuneRange rr;
  RegexpStatus call_status;

  bool ok = bundle.state.ParseCCRange(&s, &rr, /*whole_class=*/"a-a]", &call_status);

  ASSERT_TRUE(ok);
  EXPECT_EQ(rr.lo, static_cast<int>('a'));
  EXPECT_EQ(rr.hi, static_cast<int>('a'));
  EXPECT_EQ(s, absl::string_view("]"));
  EXPECT_TRUE(call_status.ok());
}

TEST_F(ParseCCRangeTest_530, DescendingRangeSetsStatusAndFails_530) {
  ParseCCRangeTest_530::StateBundle bundle(static_cast<re2::ParseFlags>(0), "[z-a]");
  absl::string_view s = "z-a]";
  RuneRange rr;
  RegexpStatus call_status;

  bool ok = bundle.state.ParseCCRange(&s, &rr, /*whole_class=*/"z-a]", &call_status);

  ASSERT_FALSE(ok);
  EXPECT_EQ(call_status.code(), kRegexpBadCharRange);
  // Error arg should include exactly the consumed portion ("z-a")
  EXPECT_EQ(std::string(call_status.error_arg()), "z-a");
  // After failure, s should point after the 'a' (i.e., at "]")
  EXPECT_EQ(s, absl::string_view("]"));
}

TEST_F(ParseCCRangeTest_530, EmptyInputFails_530) {
  ParseCCRangeTest_530::StateBundle bundle(static_cast<re2::ParseFlags>(0), "[]");
  absl::string_view s = "";  // No character to parse for lo
  RuneRange rr;
  RegexpStatus call_status;

  bool ok = bundle.state.ParseCCRange(&s, &rr, /*whole_class=*/"", &call_status);

  EXPECT_FALSE(ok);
  // We do not assert a specific error code here since it's delegated to ParseCCCharacter.
}

}  // namespace
