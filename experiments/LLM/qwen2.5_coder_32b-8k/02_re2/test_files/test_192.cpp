#include <gtest/gtest.h>

#include "pcre.h"

#include "absl/strings/string_view.h"



using namespace re2;



class PCRETest_192 : public ::testing::Test {

protected:

    void SetUp() override {

        // Initialize any variables or state if necessary

    }



    void TearDown() override {

        // Clean up any resources if necessary

    }

};



TEST_F(PCRETest_192, DoMatch_SimplePattern_192) {

    PCRE pattern("hello");

    absl::string_view text = "hello world";

    size_t consumed = 0;

    EXPECT_TRUE(pattern.DoMatch(text, UNANCHORED, &consumed, nullptr, 0));

    EXPECT_EQ(consumed, 5);

}



TEST_F(PCRETest_192, DoMatch_NoMatch_192) {

    PCRE pattern("hello");

    absl::string_view text = "world";

    size_t consumed = 0;

    EXPECT_FALSE(pattern.DoMatch(text, UNANCHORED, &consumed, nullptr, 0));

}



TEST_F(PCRETest_192, DoMatch_Anchored_Start_192) {

    PCRE pattern("^hello");

    absl::string_view text = "hello world";

    size_t consumed = 0;

    EXPECT_TRUE(pattern.DoMatch(text, ANCHORED, &consumed, nullptr, 0));

    EXPECT_EQ(consumed, 5);

}



TEST_F(PCRETest_192, DoMatch_Anchored_End_192) {

    PCRE pattern("world$");

    absl::string_view text = "hello world";

    size_t consumed = 0;

    EXPECT_FALSE(pattern.DoMatch(text, ANCHORED, &consumed, nullptr, 0));

}



TEST_F(PCRETest_192, DoMatch_Args_Success_192) {

    PCRE pattern("(\\d+)-(\\d+)");

    absl::string_view text = "123-456";

    size_t consumed = 0;

    Arg args[2] = {Arg(), Arg()};

    EXPECT_TRUE(pattern.DoMatch(text, UNANCHORED, &consumed, args, 2));

    EXPECT_EQ(consumed, 7);

}



TEST_F(PCRETest_192, DoMatch_Args_Failure_192) {

    PCRE pattern("(\\d+)-(\\d+)");

    absl::string_view text = "abc-def";

    size_t consumed = 0;

    Arg args[2] = {Arg(), Arg()};

    EXPECT_FALSE(pattern.DoMatch(text, UNANCHORED, &consumed, args, 2));

}



TEST_F(PCRETest_192, NumberOfCapturingGroups_ValidPattern_192) {

    PCRE pattern("(a)(b)(c)");

    EXPECT_EQ(pattern.NumberOfCapturingGroups(), 3);

}



TEST_F(PCRETest_192, NumberOfCapturingGroups_NoCapturingGroups_192) {

    PCRE pattern("abc");

    EXPECT_EQ(pattern.NumberOfCapturingGroups(), 0);

}



TEST_F(PCRETest_192, HitLimit_Default_192) {

    PCRE pattern("a*");

    EXPECT_FALSE(pattern.HitLimit());

}



TEST_F(PCRETest_192, ClearHitLimit_AfterMatch_192) {

    PCRE pattern("a*", {PCRE::Option::kMatchLimit, 1});

    absl::string_view text = "aaaaaaaaaa";

    size_t consumed = 0;

    EXPECT_FALSE(pattern.DoMatch(text, UNANCHORED, &consumed, nullptr, 0));

    EXPECT_TRUE(pattern.HitLimit());

    pattern.ClearHitLimit();

    EXPECT_FALSE(pattern.HitLimit());

}



TEST_F(PCRETest_192, FindAndConsumeFunctor_Success_192) {

    PCRE pattern("hello");

    absl::string_view text = "hello world";

    size_t consumed = 0;

    Arg args[2] = {Arg(), Arg()};

    PCRE::FindAndConsumeFunctor functor;

    EXPECT_TRUE(functor(&text, pattern, args[0], args[1], no_more_args, no_more_args, no_more_args, no_more_args, no_more_args, no_more_args, no_more_args, no_more_args, no_more_args, no_more_args, no_more_args, no_more_args));

    EXPECT_EQ(text, " world");

}



TEST_F(PCRETest_192, FindAndConsumeFunctor_Failure_192) {

    PCRE pattern("hello");

    absl::string_view text = "world";

    size_t consumed = 0;

    Arg args[2] = {Arg(), Arg()};

    PCRE::FindAndConsumeFunctor functor;

    EXPECT_FALSE(functor(&text, pattern, args[0], args[1], no_more_args, no_more_args, no_more_args, no_more_args, no_more_args, no_more_args, no_more_args, no_more_args, no_more_args, no_more_args, no_more_args, no_more_args));

    EXPECT_EQ(text, "world");

}



TEST_F(PCRETest_192, FindAndConsumeFunctor_MaxArgs_192) {

    PCRE pattern("(\\d)-(\\d)-(\\d)-(\\d)-(\\d)-(\\d)-(\\d)-(\\d)-(\\d)-(\\d)-(\\d)-(\\d)-(\\d)-(\\d)-(\\d)-(\\d)");

    absl::string_view text = "1-2-3-4-5-6-7-8-9-0-1-2-3-4-5-6";

    size_t consumed = 0;

    Arg args[16] = {Arg(), Arg(), Arg(), Arg(), Arg(), Arg(), Arg(), Arg(), Arg(), Arg(), Arg(), Arg(), Arg(), Arg(), Arg(), Arg()};

    PCRE::FindAndConsumeFunctor functor;

    EXPECT_TRUE(functor(&text, pattern, args[0], args[1], args[2], args[3], args[4], args[5], args[6], args[7], args[8], args[9], args[10], args[11], args[12], args[13], args[14], args[15]));

    EXPECT_EQ(text, "");

}
