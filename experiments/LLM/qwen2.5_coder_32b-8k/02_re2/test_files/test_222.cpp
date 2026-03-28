#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "re2/regexp.h"

#include "mimics_pcre.cc"



namespace re2 {



class EmptyStringWalkerTest : public ::testing::Test {

protected:

    EmptyStringWalker walker;

};



TEST_F(EmptyStringWalkerTest, PostVisit_NoMatch_222) {

    Regexp* re = Regexp::Parse(".*", 0, nullptr);

    bool child_args[] = {true};

    EXPECT_FALSE(walker.PostVisit(re, false, false, child_args, 1));

    re->Decref();

}



TEST_F(EmptyStringWalkerTest, PostVisit_EmptyMatch_222) {

    Regexp* re = Regexp::Parse("()", 0, nullptr);

    bool child_args[] = {true};

    EXPECT_TRUE(walker.PostVisit(re, false, false, child_args, 1));

    re->Decref();

}



TEST_F(EmptyStringWalkerTest, PostVisit_Literal_222) {

    Regexp* re = Regexp::Parse("a", 0, nullptr);

    bool child_args[] = {true};

    EXPECT_FALSE(walker.PostVisit(re, false, false, child_args, 1));

    re->Decref();

}



TEST_F(EmptyStringWalkerTest, PostVisit_Concat_AllChildrenTrue_222) {

    Regexp* sub1 = Regexp::Parse("a*", 0, nullptr);

    Regexp* sub2 = Regexp::Parse("b?", 0, nullptr);

    Regexp* re = Regexp::Concat(new Regexp*[2]{sub1, sub2}, 2, 0);



    bool child_args[] = {true, true};

    EXPECT_TRUE(walker.PostVisit(re, false, false, child_args, 2));



    re->Decref();

}



TEST_F(EmptyStringWalkerTest, PostVisit_Concat_OneChildFalse_222) {

    Regexp* sub1 = Regexp::Parse("a", 0, nullptr);

    Regexp* sub2 = Regexp::Parse("b?", 0, nullptr);

    Regexp* re = Regexp::Concat(new Regexp*[2]{sub1, sub2}, 2, 0);



    bool child_args[] = {false, true};

    EXPECT_FALSE(walker.PostVisit(re, false, false, child_args, 2));



    re->Decref();

}



TEST_F(EmptyStringWalkerTest, PostVisit_Alternate_OneChildTrue_222) {

    Regexp* sub1 = Regexp::Parse("a", 0, nullptr);

    Regexp* sub2 = Regexp::Parse("b?", 0, nullptr);

    Regexp* re = Regexp::Alternate(new Regexp*[2]{sub1, sub2}, 2, 0);



    bool child_args[] = {false, true};

    EXPECT_TRUE(walker.PostVisit(re, false, false, child_args, 2));



    re->Decref();

}



TEST_F(EmptyStringWalkerTest, PostVisit_Alternate_AllChildrenFalse_222) {

    Regexp* sub1 = Regexp::Parse("a", 0, nullptr);

    Regexp* sub2 = Regexp::Parse("b+", 0, nullptr);

    Regexp* re = Regexp::Alternate(new Regexp*[2]{sub1, sub2}, 2, 0);



    bool child_args[] = {false, false};

    EXPECT_FALSE(walker.PostVisit(re, false, false, child_args, 2));



    re->Decref();

}



TEST_F(EmptyStringWalkerTest, PostVisit_Star_222) {

    Regexp* sub = Regexp::Parse("a", 0, nullptr);

    Regexp* re = Regexp::Star(sub, 0);



    bool child_args[] = {true};

    EXPECT_TRUE(walker.PostVisit(re, false, false, child_args, 1));



    re->Decref();

}



TEST_F(EmptyStringWalkerTest, PostVisit_Repeat_ZeroMin_222) {

    Regexp* sub = Regexp::Parse("a", 0, nullptr);

    Regexp* re = Regexp::Repeat(sub, 0, 3);



    bool child_args[] = {false};

    EXPECT_TRUE(walker.PostVisit(re, false, false, child_args, 1));



    re->Decref();

}



TEST_F(EmptyStringWalkerTest, PostVisit_Repeat_NonZeroMin_222) {

    Regexp* sub = Regexp::Parse("a", 0, nullptr);

    Regexp* re = Regexp::Repeat(sub, 1, 3);



    bool child_args[] = {true};

    EXPECT_TRUE(walker.PostVisit(re, false, false, child_args, 1));



    re->Decref();

}



TEST_F(EmptyStringWalkerTest, PostVisit_Capture_222) {

    Regexp* sub = Regexp::Parse("a?", 0, nullptr);

    Regexp* re = Regexp::Capture(sub, 0, 1);



    bool child_args[] = {true};

    EXPECT_TRUE(walker.PostVisit(re, false, false, child_args, 1));



    re->Decref();

}



TEST_F(EmptyStringWalkerTest, PostVisit_Plus_222) {

    Regexp* sub = Regexp::Parse("a", 0, nullptr);

    Regexp* re = Regexp::Plus(sub, 0);



    bool child_args[] = {true};

    EXPECT_TRUE(walker.PostVisit(re, false, false, child_args, 1));



    re->Decref();

}



TEST_F(EmptyStringWalkerTest, PostVisit_Quest_222) {

    Regexp* sub = Regexp::Parse("a", 0, nullptr);

    Regexp* re = Regexp::Quest(sub, 0);



    bool child_args[] = {true};

    EXPECT_TRUE(walker.PostVisit(re, false, false, child_args, 1));



    re->Decref();

}



} // namespace re2
