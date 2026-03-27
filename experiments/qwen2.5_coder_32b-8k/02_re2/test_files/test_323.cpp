#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "re2/regexp.h"



namespace re2 {



class IsAnchorEndTest : public ::testing::Test {

protected:

    Regexp* CreateRegexp(RegexpOp op, int nsub = 0, Regexp** subs = nullptr) {

        Regexp* re = new Regexp(op, 0);

        if (nsub > 0 && subs != nullptr) {

            re->AllocSub(nsub);

            for (int i = 0; i < nsub; ++i) {

                re->sub()[i] = subs[i];

            }

        }

        return re;

    }



    void TearDown() override {

        // Clean up any allocated Regexp objects

    }

};



TEST_F(IsAnchorEndTest, NormalOperation_ConcatWithEndText_323) {

    Regexp* end_text = CreateRegexp(kRegexpEndText);

    Regexp* concat_subs[] = {CreateRegexp(kRegexpLiteral), end_text};

    Regexp* concat = CreateRegexp(kRegexpConcat, 2, concat_subs);



    EXPECT_TRUE(IsAnchorEnd(&concat, 0));



    for (auto sub : concat_subs) {

        sub->Decref();

    }

    concat->Decref();

}



TEST_F(IsAnchorEndTest, NormalOperation_CaptureWithEndText_323) {

    Regexp* end_text = CreateRegexp(kRegexpEndText);

    Regexp* capture = CreateRegexp(kRegexpCapture, 1, &end_text);



    EXPECT_TRUE(IsAnchorEnd(&capture, 0));



    end_text->Decref();

    capture->Decref();

}



TEST_F(IsAnchorEndTest, NormalOperation_EndText_323) {

    Regexp* end_text = CreateRegexp(kRegexpEndText);

    EXPECT_TRUE(IsAnchorEnd(&end_text, 0));

    end_text->Decref();

}



TEST_F(IsAnchorEndTest, BoundaryCondition_EmptyConcat_323) {

    Regexp* concat = CreateRegexp(kRegexpConcat);



    EXPECT_FALSE(IsAnchorEnd(&concat, 0));



    concat->Decref();

}



TEST_F(IsAnchorEndTest, BoundaryCondition_DepthLimitReached_323) {

    Regexp* end_text = CreateRegexp(kRegexpEndText);

    Regexp* sub = CreateRegexp(kRegexpCapture, 1, &end_text);



    EXPECT_FALSE(IsAnchorEnd(&sub, 4));



    sub->Decref();

}



TEST_F(IsAnchorEndTest, ExceptionalCase_NullRegexp_323) {

    Regexp* re = nullptr;

    EXPECT_FALSE(IsAnchorEnd(&re, 0));

}



TEST_F(IsAnchorEndTest, VerificationOfExternalInteractions_NoChangeOnFalse_323) {

    Regexp* literal = CreateRegexp(kRegexpLiteral);

    Regexp* concat_subs[] = {literal};

    Regexp* concat = CreateRegexp(kRegexpConcat, 1, concat_subs);



    EXPECT_FALSE(IsAnchorEnd(&concat, 0));



    for (auto sub : concat_subs) {

        sub->Decref();

    }

    concat->Decref();

}



TEST_F(IsAnchorEndTest, VerificationOfExternalInteractions_RegexpUnchangedOnFalse_323) {

    Regexp* literal = CreateRegexp(kRegexpLiteral);

    Regexp* concat_subs[] = {literal};

    Regexp* original_concat = CreateRegexp(kRegexpConcat, 1, concat_subs);



    EXPECT_FALSE(IsAnchorEnd(&original_concat, 0));



    // Verify the original regexp is unchanged

    EXPECT_EQ(original_concat->op(), kRegexpConcat);

    EXPECT_EQ(original_concat->nsub(), 1);

    EXPECT_EQ(original_concat->sub()[0], literal);



    for (auto sub : concat_subs) {

        sub->Decref();

    }

    original_concat->Decref();

}



} // namespace re2
