#include <gtest/gtest.h>

#include "regexp.h"



namespace re2 {



class RegexpTest : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup any state needed for tests here

    }



    void TearDown() override {

        // Cleanup any state modified by tests here

    }

};



TEST_F(RegexpTest_150, nsub_ReturnsZeroForDefaultConstructedRegexp_150) {

    Regexp* regexp = new Regexp(RegexpOp::kEmpty, ParseFlags::None);

    EXPECT_EQ(regexp->nsub(), 0);

    delete regexp;

}



TEST_F(RegexpTest_150, nsub_ReturnsExpectedValueAfterCapture_150) {

    Regexp* sub = new Regexp(RegexpOp::kLiteral, ParseFlags::None);

    Regexp* capture = Regexp::Capture(sub, ParseFlags::None, 1);

    EXPECT_EQ(capture->nsub(), 1);

    delete capture;

}



TEST_F(RegexpTest_150, nsub_ReturnsZeroForConcatWithNoCaptures_150) {

    Regexp* sub1 = new Regexp(RegexpOp::kLiteral, ParseFlags::None);

    Regexp* sub2 = new Regexp(RegexpOp::kLiteral, ParseFlags::None);

    Regexp** subs = new Regexp*[2]{sub1, sub2};

    Regexp* concat = Regexp::Concat(subs, 2, ParseFlags::None);

    EXPECT_EQ(concat->nsub(), 0);

    delete[] subs;

    delete concat;

}



TEST_F(RegexpTest_150, nsub_ReturnsCorrectValueForNestedCaptures_150) {

    Regexp* sub1 = new Regexp(RegexpOp::kLiteral, ParseFlags::None);

    Regexp* capture1 = Regexp::Capture(sub1, ParseFlags::None, 1);

    Regexp* sub2 = new Regexp(RegexpOp::kLiteral, ParseFlags::None);

    Regexp* capture2 = Regexp::Capture(sub2, ParseFlags::None, 2);



    Regexp** subs = new Regexp*[2]{capture1, capture2};

    Regexp* concat = Regexp::Concat(subs, 2, ParseFlags::None);



    EXPECT_EQ(concat->nsub(), 2);

    delete[] subs;

    delete concat;

}



TEST_F(RegexpTest_150, nsub_ReturnsCorrectValueForAlternatesWithCaptures_150) {

    Regexp* sub1 = new Regexp(RegexpOp::kLiteral, ParseFlags::None);

    Regexp* capture1 = Regexp::Capture(sub1, ParseFlags::None, 1);

    Regexp* sub2 = new Regexp(RegexpOp::kLiteral, ParseFlags::None);

    Regexp* capture2 = Regexp::Capture(sub2, ParseFlags::None, 2);



    Regexp** subs = new Regexp*[2]{capture1, capture2};

    Regexp* alternate = Regexp::Alternate(subs, 2, ParseFlags::None);



    EXPECT_EQ(alternate->nsub(), 2);

    delete[] subs;

    delete alternate;

}



TEST_F(RegexpTest_150, nsub_ReturnsZeroForSimpleLiteral_150) {

    Regexp* literal = Regexp::NewLiteral('a', ParseFlags::None);

    EXPECT_EQ(literal->nsub(), 0);

    delete literal;

}



} // namespace re2
