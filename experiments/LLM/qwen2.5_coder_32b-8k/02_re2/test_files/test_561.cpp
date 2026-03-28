#include <gtest/gtest.h>

#include "re2/prefilter.h"

#include "re2/regexp.h"



namespace re2 {



class PrefilterTest : public ::testing::Test {

protected:

    Prefilter prefilter;

};



TEST_F(PrefilterTest_561, PostVisit_NoMatch_561) {

    Regexp* re = Regexp::NewLiteral(0, kNoParseFlags);

    Prefilter::Info** child_args = nullptr;

    int nchild_args = 0;

    re->op_ = kRegexpNoMatch;



    Prefilter::Info* info = prefilter.Walker(false).PostVisit(re, nullptr, nullptr, child_args, nchild_args);



    EXPECT_NE(info, nullptr);

    EXPECT_EQ(info->is_exact(), false);

}



TEST_F(PrefilterTest_561, PostVisit_EmptyMatch_561) {

    Regexp* re = Regexp::NewLiteral(0, kNoParseFlags);

    Prefilter::Info** child_args = nullptr;

    int nchild_args = 0;

    re->op_ = kRegexpEmptyMatch;



    Prefilter::Info* info = prefilter.Walker(false).PostVisit(re, nullptr, nullptr, child_args, nchild_args);



    EXPECT_NE(info, nullptr);

    EXPECT_EQ(info->is_exact(), false);

}



TEST_F(PrefilterTest_561, PostVisit_LiteralLatin1_561) {

    Regexp* re = Regexp::NewLiteral('a', kNoParseFlags);

    Prefilter::Info** child_args = nullptr;

    int nchild_args = 0;

    re->op_ = kRegexpLiteral;



    Prefilter::Info* info = prefilter.Walker(true).PostVisit(re, nullptr, nullptr, child_args, nchild_args);



    EXPECT_NE(info, nullptr);

    EXPECT_EQ(info->is_exact(), true);

}



TEST_F(PrefilterTest_561, PostVisit_Literal_561) {

    Regexp* re = Regexp::NewLiteral('a', kNoParseFlags);

    Prefilter::Info** child_args = nullptr;

    int nchild_args = 0;

    re->op_ = kRegexpLiteral;



    Prefilter::Info* info = prefilter.Walker(false).PostVisit(re, nullptr, nullptr, child_args, nchild_args);



    EXPECT_NE(info, nullptr);

    EXPECT_EQ(info->is_exact(), true);

}



TEST_F(PrefilterTest_561, PostVisit_LiteralString_Empty_561) {

    Regexp* re = Regexp::LiteralString(nullptr, 0, kNoParseFlags);

    Prefilter::Info** child_args = nullptr;

    int nchild_args = 0;

    re->op_ = kRegexpLiteralString;



    Prefilter::Info* info = prefilter.Walker(false).PostVisit(re, nullptr, nullptr, child_args, nchild_args);



    EXPECT_NE(info, nullptr);

    EXPECT_EQ(info->is_exact(), false);

}



TEST_F(PrefilterTest_561, PostVisit_LiteralString_SingleChar_561) {

    Rune runes[] = {'a'};

    Regexp* re = Regexp::LiteralString(runes, 1, kNoParseFlags);

    Prefilter::Info** child_args = nullptr;

    int nchild_args = 0;

    re->op_ = kRegexpLiteralString;



    Prefilter::Info* info = prefilter.Walker(false).PostVisit(re, nullptr, nullptr, child_args, nchild_args);



    EXPECT_NE(info, nullptr);

    EXPECT_EQ(info->is_exact(), true);

}



TEST_F(PrefilterTest_561, PostVisit_LiteralString_MultiChar_561) {

    Rune runes[] = {'a', 'b'};

    Regexp* re = Regexp::LiteralString(runes, 2, kNoParseFlags);

    Prefilter::Info** child_args = nullptr;

    int nchild_args = 0;

    re->op_ = kRegexpLiteralString;



    Prefilter::Info* info = prefilter.Walker(false).PostVisit(re, nullptr, nullptr, child_args, nchild_args);



    EXPECT_NE(info, nullptr);

    EXPECT_EQ(info->is_exact(), true);

}



TEST_F(PrefilterTest_561, PostVisit_Concat_TwoChildren_561) {

    Regexp* re1 = Regexp::NewLiteral('a', kNoParseFlags);

    Regexp* re2 = Regexp::NewLiteral('b', kNoParseFlags);

    Regexp* subs[] = {re1, re2};

    Regexp* re = Regexp::Concat(subs, 2, kNoParseFlags);

    Prefilter::Info** child_args = new Prefilter::Info*[2];

    child_args[0] = Prefilter::Info::Literal('a');

    child_args[1] = Prefilter::Info::Literal('b');

    int nchild_args = 2;

    re->op_ = kRegexpConcat;



    Prefilter::Info* info = prefilter.Walker(false).PostVisit(re, nullptr, nullptr, child_args, nchild_args);



    EXPECT_NE(info, nullptr);

    EXPECT_EQ(info->is_exact(), true);



    delete[] child_args;

}



TEST_F(PrefilterTest_561, PostVisit_Alternate_TwoChildren_561) {

    Regexp* re1 = Regexp::NewLiteral('a', kNoParseFlags);

    Regexp* re2 = Regexp::NewLiteral('b', kNoParseFlags);

    Regexp* subs[] = {re1, re2};

    Regexp* re = Regexp::Alternate(subs, 2, kNoParseFlags);

    Prefilter::Info** child_args = new Prefilter::Info*[2];

    child_args[0] = Prefilter::Info::Literal('a');

    child_args[1] = Prefilter::Info::Literal('b');

    int nchild_args = 2;

    re->op_ = kRegexpAlternate;



    Prefilter::Info* info = prefilter.Walker(false).PostVisit(re, nullptr, nullptr, child_args, nchild_args);



    EXPECT_NE(info, nullptr);

    EXPECT_EQ(info->is_exact(), false);



    delete[] child_args;

}



TEST_F(PrefilterTest_561, PostVisit_Star_561) {

    Regexp* re = Regexp::NewLiteral('a', kNoParseFlags);

    Prefilter::Info** child_args = new Prefilter::Info*[1];

    child_args[0] = Prefilter::Info::Literal('a');

    int nchild_args = 1;

    re->op_ = kRegexpStar;



    Prefilter::Info* info = prefilter.Walker(false).PostVisit(re, nullptr, nullptr, child_args, nchild_args);



    EXPECT_NE(info, nullptr);

    EXPECT_EQ(info->is_exact(), false);



    delete[] child_args;

}



TEST_F(PrefilterTest_561, PostVisit_Plus_561) {

    Regexp* re = Regexp::NewLiteral('a', kNoParseFlags);

    Prefilter::Info** child_args = new Prefilter::Info*[1];

    child_args[0] = Prefilter::Info::Literal('a');

    int nchild_args = 1;

    re->op_ = kRegexpPlus;



    Prefilter::Info* info = prefilter.Walker(false).PostVisit(re, nullptr, nullptr, child_args, nchild_args);



    EXPECT_NE(info, nullptr);

    EXPECT_EQ(info->is_exact(), false);



    delete[] child_args;

}



TEST_F(PrefilterTest_561, PostVisit_Quest_561) {

    Regexp* re = Regexp::NewLiteral('a', kNoParseFlags);

    Prefilter::Info** child_args = new Prefilter::Info*[1];

    child_args[0] = Prefilter::Info::Literal('a');

    int nchild_args = 1;

    re->op_ = kRegexpQuest;



    Prefilter::Info* info = prefilter.Walker(false).PostVisit(re, nullptr, nullptr, child_args, nchild_args);



    EXPECT_NE(info, nullptr);

    EXPECT_EQ(info->is_exact(), false);



    delete[] child_args;

}



TEST_F(PrefilterTest_561, PostVisit_AnyCharOrAnyByte_561) {

    Regexp* re = Regexp::NewLiteral(0, kNoParseFlags);

    Prefilter::Info** child_args = nullptr;

    int nchild_args = 0;

    re->op_ = kRegexpAnyChar;



    Prefilter::Info* info = prefilter.Walker(false).PostVisit(re, nullptr, nullptr, child_args, nchild_args);



    EXPECT_NE(info, nullptr);

    EXPECT_EQ(info->is_exact(), false);

}



TEST_F(PrefilterTest_561, PostVisit_CharClass_561) {

    CharClass* cc = new CharClass();

    Regexp* re = Regexp::NewCharClass(cc, kNoParseFlags);

    Prefilter::Info** child_args = nullptr;

    int nchild_args = 0;

    re->op_ = kRegexpCharClass;



    Prefilter::Info* info = prefilter.Walker(false).PostVisit(re, nullptr, nullptr, child_args, nchild_args);



    EXPECT_NE(info, nullptr);

    EXPECT_EQ(info->is_exact(), false);

}



TEST_F(PrefilterTest_561, PostVisit_Capture_561) {

    Regexp* re = Regexp::NewLiteral('a', kNoParseFlags);

    Prefilter::Info** child_args = new Prefilter::Info*[1];

    child_args[0] = Prefilter::Info::Literal('a');

    int nchild_args = 1;

    re->op_ = kRegexpCapture;



    Prefilter::Info* info = prefilter.Walker(false).PostVisit(re, nullptr, nullptr, child_args, nchild_args);



    EXPECT_NE(info, nullptr);

    EXPECT_EQ(info->is_exact(), true);



    delete[] child_args;

}



}  // namespace re2
