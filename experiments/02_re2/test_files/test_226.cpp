#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "re2/regexp.h"

#include "re2/tostring.cc"



using namespace re2;

using ::testing::_;

using ::testing::Return;



class ToStringWalkerTest_226 : public testing::Test {

protected:

    std::string t_;

    ToStringWalker walker_;



    ToStringWalkerTest_226() : walker_(&t_) {}



    void TestOp(Regexp* re, int parent_arg, int expected_prec) {

        bool stop = false;

        EXPECT_EQ(walker_.PreVisit(re, parent_arg, &stop), expected_prec);

        EXPECT_FALSE(stop);  // Assuming stop is not modified in this context

    }

};



TEST_F(ToStringWalkerTest_226, PreVisit_NoMatch_Op_226) {

    Regexp* re = Regexp::Parse("", Regexp::NoParseFlags(), nullptr);

    TestOp(re, PrecAlternate, PrecAtom);

    delete re;

}



TEST_F(ToStringWalkerTest_226, PreVisit_EmptyMatch_Op_226) {

    Regexp* re = Regexp::Parse("^", Regexp::NoParseFlags(), nullptr);

    TestOp(re, PrecConcat, PrecAtom);

    delete re;

}



TEST_F(ToStringWalkerTest_226, PreVisit_Literal_Op_226) {

    Regexp* re = Regexp::Parse("a", Regexp::NoParseFlags(), nullptr);

    TestOp(re, PrecAlternate, PrecAtom);

    delete re;

}



TEST_F(ToStringWalkerTest_226, PreVisit_Concat_Op_Lower_Prec_226) {

    Regexp* re = Regexp::Concat(nullptr, 0, Regexp::NoParseFlags());

    TestOp(re, PrecAlternate, PrecConcat);

    delete re;

}



TEST_F(ToStringWalkerTest_226, PreVisit_Concat_Op_Higher_Prec_226) {

    Regexp* re = Regexp::Concat(nullptr, 0, Regexp::NoParseFlags());

    TestOp(re, PrecConcat, PrecAtom);

    delete re;

}



TEST_F(ToStringWalkerTest_226, PreVisit_Alternate_Op_Lower_Prec_226) {

    Regexp* re = Regexp::Alternate(nullptr, 0, Regexp::NoParseFlags());

    TestOp(re, PrecConcat, PrecAlternate);

    delete re;

}



TEST_F(ToStringWalkerTest_226, PreVisit_Alternate_Op_Higher_Prec_226) {

    Regexp* re = Regexp::Alternate(nullptr, 0, Regexp::NoParseFlags());

    TestOp(re, PrecAlternate, PrecAtom);

    delete re;

}



TEST_F(ToStringWalkerTest_226, PreVisit_Capture_Op_226) {

    Regexp* sub_re = Regexp::Parse("a", Regexp::NoParseFlags(), nullptr);

    Regexp* re = Regexp::Capture(sub_re, Regexp::NoParseFlags(), 1);

    TestOp(re, PrecConcat, PrecParen);

    delete re;

}



TEST_F(ToStringWalkerTest_226, PreVisit_Star_Op_Lower_Prec_226) {

    Regexp* sub_re = Regexp::Parse("a", Regexp::NoParseFlags(), nullptr);

    Regexp* re = Regexp::Star(sub_re, Regexp::NoParseFlags());

    TestOp(re, PrecConcat, PrecAtom);

    delete re;

}



TEST_F(ToStringWalkerTest_226, PreVisit_Star_Op_Higher_Prec_226) {

    Regexp* sub_re = Regexp::Parse("a", Regexp::NoParseFlags(), nullptr);

    Regexp* re = Regexp::Star(sub_re, Regexp::NoParseFlags());

    TestOp(re, PrecAtom, PrecAtom);

    delete re;

}



TEST_F(ToStringWalkerTest_226, PreVisit_Plus_Op_Lower_Prec_226) {

    Regexp* sub_re = Regexp::Parse("a", Regexp::NoParseFlags(), nullptr);

    Regexp* re = Regexp::Plus(sub_re, Regexp::NoParseFlags());

    TestOp(re, PrecConcat, PrecAtom);

    delete re;

}



TEST_F(ToStringWalkerTest_226, PreVisit_Plus_Op_Higher_Prec_226) {

    Regexp* sub_re = Regexp::Parse("a", Regexp::NoParseFlags(), nullptr);

    Regexp* re = Regexp::Plus(sub_re, Regexp::NoParseFlags());

    TestOp(re, PrecAtom, PrecAtom);

    delete re;

}



TEST_F(ToStringWalkerTest_226, PreVisit_Quest_Op_Lower_Prec_226) {

    Regexp* sub_re = Regexp::Parse("a", Regexp::NoParseFlags(), nullptr);

    Regexp* re = Regexp::Quest(sub_re, Regexp::NoParseFlags());

    TestOp(re, PrecConcat, PrecAtom);

    delete re;

}



TEST_F(ToStringWalkerTest_226, PreVisit_Quest_Op_Higher_Prec_226) {

    Regexp* sub_re = Regexp::Parse("a", Regexp::NoParseFlags(), nullptr);

    Regexp* re = Regexp::Quest(sub_re, Regexp::NoParseFlags());

    TestOp(re, PrecAtom, PrecAtom);

    delete re;

}



TEST_F(ToStringWalkerTest_226, PreVisit_Repeat_Op_Lower_Prec_226) {

    Regexp* sub_re = Regexp::Parse("a", Regexp::NoParseFlags(), nullptr);

    Regexp* re = Regexp::Repeat(sub_re, Regexp::NoParseFlags(), 1, 3);

    TestOp(re, PrecConcat, PrecAtom);

    delete re;

}



TEST_F(ToStringWalkerTest_226, PreVisit_Repeat_Op_Higher_Prec_226) {

    Regexp* sub_re = Regexp::Parse("a", Regexp::NoParseFlags(), nullptr);

    Regexp* re = Regexp::Repeat(sub_re, Regexp::NoParseFlags(), 1, 3);

    TestOp(re, PrecAtom, PrecAtom);

    delete re;

}
