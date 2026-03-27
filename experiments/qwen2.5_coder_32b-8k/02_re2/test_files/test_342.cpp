#include <gtest/gtest.h>

#include "re2/regexp.h"



using namespace re2;



class RegexpTest_342 : public ::testing::Test {

protected:

    Regexp* CreateLiteralRegexp(const std::string& literal) {

        return Regexp::Parse(literal, Regexp::NoParseFlags(), nullptr);

    }



    void TearDown() override {

        // Clean up any allocated Regexp objects

    }

};



TEST_F(RegexpTest_342, AlternateTwoLiterals_342) {

    Regexp* sub1 = CreateLiteralRegexp("foo");

    Regexp* sub2 = CreateLiteralRegexp("bar");



    Regexp** subs = new Regexp*[2];

    subs[0] = sub1;

    subs[1] = sub2;



    Regexp* result = sub1->Alternate(subs, 2, Regexp::NoParseFlags());



    EXPECT_EQ(result->op(), kRegexpAlternate);

    EXPECT_EQ(result->nsub(), 2);



    // Clean up

    result->Decref();

    delete[] subs;

}



TEST_F(RegexpTest_342, AlternateZeroSubs_342) {

    Regexp** subs = nullptr;



    Regexp* result = Regexp::Alternate(subs, 0, Regexp::NoParseFlags());



    EXPECT_EQ(result->op(), kRegexpNoMatch);

    EXPECT_EQ(result->nsub(), 0);



    // Clean up

    result->Decref();

}



TEST_F(RegexpTest_342, AlternateSingleSub_342) {

    Regexp* sub1 = CreateLiteralRegexp("foo");



    Regexp** subs = new Regexp*[1];

    subs[0] = sub1;



    Regexp* result = sub1->Alternate(subs, 1, Regexp::NoParseFlags());



    EXPECT_EQ(result->op(), kRegexpLiteral);

    EXPECT_STREQ(result->ToString().c_str(), "foo");



    // Clean up

    result->Decref();

    delete[] subs;

}



TEST_F(RegexpTest_342, AlternateWithNullSub_342) {

    Regexp** subs = new Regexp*[1];

    subs[0] = nullptr;



    EXPECT_DEATH(subs[0]->Alternate(subs, 1, Regexp::NoParseFlags()), "");



    delete[] subs;

}



TEST_F(RegexpTest_342, AlternateMultipleSubs_342) {

    Regexp* sub1 = CreateLiteralRegexp("foo");

    Regexp* sub2 = CreateLiteralRegexp("bar");

    Regexp* sub3 = CreateLiteralRegexp("baz");



    Regexp** subs = new Regexp*[3];

    subs[0] = sub1;

    subs[1] = sub2;

    subs[2] = sub3;



    Regexp* result = sub1->Alternate(subs, 3, Regexp::NoParseFlags());



    EXPECT_EQ(result->op(), kRegexpAlternate);

    EXPECT_EQ(result->nsub(), 3);



    // Clean up

    result->Decref();

    delete[] subs;

}
