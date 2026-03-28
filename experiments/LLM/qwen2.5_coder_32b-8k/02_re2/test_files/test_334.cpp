#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "re2/regexp.h"



namespace re2 {

namespace {



class RegexpTest_334 : public ::testing::Test {

protected:

    void SetUp() override {

        status = new RegexpStatus();

    }



    void TearDown() override {

        delete status;

    }



    Regexp* ParseRegexp(const std::string& pattern, ParseFlags flags) {

        return Regexp::Parse(pattern, flags, status);

    }



    RegexpStatus* status;

};



TEST_F(RegexpTest_334, RefInitialValue_334) {

    Regexp* regexp = ParseRegexp("a", kNoParseFlags);

    ASSERT_NE(regexp, nullptr);

    EXPECT_EQ(regexp->Ref(), 1);

    delete regexp;

}



TEST_F(RegexpTest_334, IncrefIncreasesRef_334) {

    Regexp* regexp = ParseRegexp("a", kNoParseFlags);

    ASSERT_NE(regexp, nullptr);

    int initial_ref = regexp->Ref();

    regexp->Incref();

    EXPECT_EQ(regexp->Ref(), initial_ref + 1);

    delete regexp;

}



TEST_F(RegexpTest_334, DecrefDecreasesRef_334) {

    Regexp* regexp = ParseRegexp("a", kNoParseFlags);

    ASSERT_NE(regexp, nullptr);

    int initial_ref = regexp->Ref();

    regexp->Incref(); // Increment ref count to test decrement

    regexp->Decref();

    EXPECT_EQ(regexp->Ref(), initial_ref);

    delete regexp;

}



TEST_F(RegexpTest_334, ParseInvalidPattern_334) {

    Regexp* regexp = ParseRegexp("(", kNoParseFlags);

    EXPECT_EQ(regexp, nullptr);

    EXPECT_TRUE(status->IsError());

}



TEST_F(RegexpTest_334, SimplifyDoesNotChangeRef_334) {

    Regexp* regexp = ParseRegexp("a", kNoParseFlags);

    ASSERT_NE(regexp, nullptr);

    int initial_ref = regexp->Ref();

    Regexp* simplified_regexp = regexp->Simplify();

    EXPECT_EQ(simplified_regexp, regexp); // Simplify should not create a new object

    EXPECT_EQ(regexp->Ref(), initial_ref);

    delete regexp;

}



TEST_F(RegexpTest_334, NumCapturesReturnsZeroForNoCaptures_334) {

    Regexp* regexp = ParseRegexp("a", kNoParseFlags);

    ASSERT_NE(regexp, nullptr);

    EXPECT_EQ(regexp->NumCaptures(), 0);

    delete regexp;

}



TEST_F(RegexpTest_334, NumCapturesReturnsCorrectCount_334) {

    Regexp* regexp = ParseRegexp("(a)(b)", kNoParseFlags);

    ASSERT_NE(regexp, nullptr);

    EXPECT_EQ(regexp->NumCaptures(), 2);

    delete regexp;

}



TEST_F(RegexpTest_334, ToStringMatchesParsedPattern_334) {

    std::string pattern = "a|b";

    Regexp* regexp = ParseRegexp(pattern, kNoParseFlags);

    ASSERT_NE(regexp, nullptr);

    EXPECT_EQ(regexp->ToString(), pattern);

    delete regexp;

}



TEST_F(RegexpTest_334, CaptureCreatesNewCaptureGroup_334) {

    Regexp* sub_regexp = ParseRegexp("a", kNoParseFlags);

    ASSERT_NE(sub_regexp, nullptr);

    int capture_id = 1;

    Regexp* captured_regexp = Regexp::Capture(sub_regexp, kNoParseFlags, capture_id);

    EXPECT_EQ(captured_regexp->op(), kRegexpCap);

    EXPECT_EQ(captured_regexp->cap(), capture_id);

    delete captured_regexp;

}



TEST_F(RegexpTest_334, RepeatCreatesNewRepeatGroup_334) {

    Regexp* sub_regexp = ParseRegexp("a", kNoParseFlags);

    ASSERT_NE(sub_regexp, nullptr);

    int min = 1, max = 2;

    Regexp* repeated_regexp = Regexp::Repeat(sub_regexp, kNoParseFlags, min, max);

    EXPECT_EQ(repeated_regexp->op(), kRegexpRepeat);

    EXPECT_EQ(repeated_regexp->min(), min);

    EXPECT_EQ(repeated_regexp->max(), max);

    delete repeated_regexp;

}



TEST_F(RegexpTest_334, ConcatCreatesNewConcatGroup_334) {

    Regexp* sub1 = ParseRegexp("a", kNoParseFlags);

    Regexp* sub2 = ParseRegexp("b", kNoParseFlags);

    ASSERT_NE(sub1, nullptr);

    ASSERT_NE(sub2, nullptr);

    Regexp* subs[] = {sub1, sub2};

    int nsubs = 2;

    Regexp* concat_regexp = Regexp::Concat(subs, nsubs, kNoParseFlags);

    EXPECT_EQ(concat_regexp->op(), kRegexpConcat);

    delete concat_regexp;

}



TEST_F(RegexpTest_334, AlternateCreatesNewAlternateGroup_334) {

    Regexp* sub1 = ParseRegexp("a", kNoParseFlags);

    Regexp* sub2 = ParseRegexp("b", kNoParseFlags);

    ASSERT_NE(sub1, nullptr);

    ASSERT_NE(sub2, nullptr);

    Regexp* subs[] = {sub1, sub2};

    int nsubs = 2;

    Regexp* alternate_regexp = Regexp::Alternate(subs, nsubs, kNoParseFlags);

    EXPECT_EQ(alternate_regexp->op(), kRegexpAlternate);

    delete alternate_regexp;

}



} // namespace

} // namespace re2
