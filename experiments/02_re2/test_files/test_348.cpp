#include <gtest/gtest.h>

#include "re2/regexp.h"



using namespace re2;



class RegexpTest_348 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code if needed

    }



    void TearDown() override {

        // Teardown code if needed

    }

};



TEST_F(RegexpTest_348, NewCharClassValidInput_348) {

    CharClass* cc = new CharClass();

    ParseFlags flags = 0;

    Regexp* re = Regexp::NewCharClass(cc, flags);

    

    EXPECT_NE(re, nullptr);

    EXPECT_EQ(re->op(), kRegexpCharClass);

    EXPECT_EQ(re->parse_flags(), flags);

    EXPECT_EQ(re->cc_, cc);



    delete re;

    cc->Delete();

}



TEST_F(RegexpTest_348, NewCharClassNullCharClass_348) {

    CharClass* cc = nullptr;

    ParseFlags flags = 0;



    Regexp* re = Regexp::NewCharClass(cc, flags);



    EXPECT_EQ(re, nullptr);

}



// Assuming that there are no specific boundary conditions for ParseFlags in the provided interface.

// If there are any known constraints on ParseFlags, additional tests should be added.



TEST_F(RegexpTest_348, NewCharClassDifferentParseFlags_348) {

    CharClass* cc = new CharClass();

    ParseFlags flags1 = 0;

    ParseFlags flags2 = RE2::UNANCHORED | RE2::CASELESS;



    Regexp* re1 = Regexp::NewCharClass(cc, flags1);

    Regexp* re2 = Regexp::NewCharClass(cc, flags2);



    EXPECT_NE(re1, nullptr);

    EXPECT_EQ(re1->op(), kRegexpCharClass);

    EXPECT_EQ(re1->parse_flags(), flags1);

    EXPECT_EQ(re1->cc_, cc);



    EXPECT_NE(re2, nullptr);

    EXPECT_EQ(re2->op(), kRegexpCharClass);

    EXPECT_EQ(re2->parse_flags(), flags2);

    EXPECT_EQ(re2->cc_, cc);



    delete re1;

    delete re2;

    cc->Delete();

}
