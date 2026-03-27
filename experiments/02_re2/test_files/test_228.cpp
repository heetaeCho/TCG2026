#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "re2/regexp.h"

#include "re2/tostring.cc"



using namespace re2;

using ::testing::Eq;

using ::testing::MockFunction;



class ToStringWalkerTest : public ::testing::Test {

protected:

    void SetUp() override {

        result.clear();

        walker = new ToStringWalker(&result);

    }



    void TearDown() override {

        delete walker;

    }



    std::string result;

    ToStringWalker* walker;

};



TEST_F(ToStringWalkerTest_NormalOperation_228, PostVisit_NoMatch_ReturnsCorrectString_228) {

    Regexp* re = Regexp::NoMatch();

    walker->PostVisit(re, 0, 0, nullptr, 0);

    EXPECT_EQ(result, "[^\\x00-\\x{10ffff}]");

    re->Decref();

}



TEST_F(ToStringWalkerTest_NormalOperation_228, PostVisit_EmptyMatch_ReturnsCorrectString_228) {

    Regexp* re = Regexp::EmptyMatch();

    walker->PostVisit(re, 5, 0, nullptr, 0);

    EXPECT_EQ(result, "(?:)");

    re->Decref();

}



TEST_F(ToStringWalkerTest_NormalOperation_228, PostVisit_Literal_ReturnsCorrectString_228) {

    Regexp* re = Regexp::NewLiteral('a', Regexp::NoParseFlags);

    walker->PostVisit(re, 0, 0, nullptr, 0);

    EXPECT_EQ(result, "a");

    re->Decref();

}



TEST_F(ToStringWalkerTest_NormalOperation_228, PostVisit_LiteralString_ReturnsCorrectString_228) {

    Rune runes[] = {'h', 'e', 'l', 'l', 'o'};

    Regexp* re = Regexp::LiteralString(runes, 5, Regexp::NoParseFlags);

    walker->PostVisit(re, 0, 0, nullptr, 0);

    EXPECT_EQ(result, "hello");

    re->Decref();

}



TEST_F(ToStringWalkerTest_NormalOperation_228, PostVisit_Concat_ReturnsCorrectString_228) {

    Regexp* sub1 = Regexp::NewLiteral('a', Regexp::NoParseFlags);

    Regexp* sub2 = Regexp::NewLiteral('b', Regexp::NoParseFlags);

    Regexp** subs = new Regexp*[2]{sub1, sub2};

    Regexp* re = Regexp::Concat(subs, 2, Regexp::NoParseFlags);

    walker->PostVisit(re, 0, 0, nullptr, 2);

    EXPECT_EQ(result, "");

    delete[] subs;

    sub1->Decref();

    sub2->Decref();

    re->Decref();

}



TEST_F(ToStringWalkerTest_NormalOperation_228, PostVisit_Alternate_ReturnsCorrectString_228) {

    Regexp* sub1 = Regexp::NewLiteral('a', Regexp::NoParseFlags);

    Regexp* sub2 = Regexp::NewLiteral('b', Regexp::NoParseFlags);

    Regexp** subs = new Regexp*[2]{sub1, sub2};

    Regexp* re = Regexp::Alternate(subs, 2, Regexp::NoParseFlags);

    walker->PostVisit(re, 0, 0, nullptr, 2);

    EXPECT_EQ(result, "a|b");

    delete[] subs;

    sub1->Decref();

    sub2->Decref();

    re->Decref();

}



TEST_F(ToStringWalkerTest_NormalOperation_228, PostVisit_Star_ReturnsCorrectString_228) {

    Regexp* sub = Regexp::NewLiteral('a', Regexp::NoParseFlags);

    Regexp* re = Regexp::Star(sub, Regexp::NonGreedy);

    walker->PostVisit(re, 0, 0, nullptr, 1);

    EXPECT_EQ(result, "a*?");

    sub->Decref();

    re->Decref();

}



TEST_F(ToStringWalkerTest_NormalOperation_228, PostVisit_Plus_ReturnsCorrectString_228) {

    Regexp* sub = Regexp::NewLiteral('a', Regexp::NoParseFlags);

    Regexp* re = Regexp::Plus(sub, Regexp::NonGreedy);

    walker->PostVisit(re, 0, 0, nullptr, 1);

    EXPECT_EQ(result, "a+?");

    sub->Decref();

    re->Decref();

}



TEST_F(ToStringWalkerTest_NormalOperation_228, PostVisit_Quest_ReturnsCorrectString_228) {

    Regexp* sub = Regexp::NewLiteral('a', Regexp::NoParseFlags);

    Regexp* re = Regexp::Quest(sub, Regexp::NonGreedy);

    walker->PostVisit(re, 0, 0, nullptr, 1);

    EXPECT_EQ(result, "a??");

    sub->Decref();

    re->Decref();

}



TEST_F(ToStringWalkerTest_NormalOperation_228, PostVisit_Repeat_ReturnsCorrectString_228) {

    Regexp* sub = Regexp::NewLiteral('a', Regexp::NoParseFlags);

    Regexp* re = Regexp::Repeat(sub, Regexp::NonGreedy, 2, -1);

    walker->PostVisit(re, 0, 0, nullptr, 1);

    EXPECT_EQ(result, "{2,}?");

    sub->Decref();

    re->Decref();

}



TEST_F(ToStringWalkerTest_NormalOperation_228, PostVisit_AnyChar_ReturnsCorrectString_228) {

    Regexp* re = Regexp::AnyChar();

    walker->PostVisit(re, 0, 0, nullptr, 0);

    EXPECT_EQ(result, ".");

    re->Decref();

}



TEST_F(ToStringWalkerTest_NormalOperation_228, PostVisit_AnyByte_ReturnsCorrectString_228) {

    Regexp* re = Regexp::AnyByte();

    walker->PostVisit(re, 0, 0, nullptr, 0);

    EXPECT_EQ(result, "\\C");

    re->Decref();

}



TEST_F(ToStringWalkerTest_NormalOperation_228, PostVisit_BeginLine_ReturnsCorrectString_228) {

    Regexp* re = Regexp::BeginLine();

    walker->PostVisit(re, 0, 0, nullptr, 0);

    EXPECT_EQ(result, "^");

    re->Decref();

}



TEST_F(ToStringWalkerTest_NormalOperation_228, PostVisit_EndLine_ReturnsCorrectString_228) {

    Regexp* re = Regexp::EndLine();

    walker->PostVisit(re, 0, 0, nullptr, 0);

    EXPECT_EQ(result, "$");

    re->Decref();

}



TEST_F(ToStringWalkerTest_NormalOperation_228, PostVisit_BeginText_ReturnsCorrectString_228) {

    Regexp* re = Regexp::BeginText();

    walker->PostVisit(re, 0, 0, nullptr, 0);

    EXPECT_EQ(result, "(?-m:^)");

    re->Decref();

}



TEST_F(ToStringWalkerTest_NormalOperation_228, PostVisit_EndText_ReturnsCorrectString_228) {

    Regexp* re = Regexp::EndText();

    walker->PostVisit(re, 0, 0, nullptr, 0);

    EXPECT_EQ(result, "\\z");

    re->Decref();

}



TEST_F(ToStringWalkerTest_NormalOperation_228, PostVisit_WordBoundary_ReturnsCorrectString_228) {

    Regexp* re = Regexp::WordBoundary();

    walker->PostVisit(re, 0, 0, nullptr, 0);

    EXPECT_EQ(result, "\\b");

    re->Decref();

}



TEST_F(ToStringWalkerTest_NormalOperation_228, PostVisit_NoWordBoundary_ReturnsCorrectString_228) {

    Regexp* re = Regexp::NoWordBoundary();

    walker->PostVisit(re, 0, 0, nullptr, 0);

    EXPECT_EQ(result, "\\B");

    re->Decref();

}



TEST_F(ToStringWalkerTest_NormalOperation_228, PostVisit_CharClass_ReturnsCorrectString_228) {

    CharClass* cc = CharClass::New(10);

    cc->Insert(97, 97); // Insert 'a'

    Regexp* re = Regexp::NewCharClass(cc, Regexp::NoParseFlags);

    walker->PostVisit(re, 0, 0, nullptr, 0);

    EXPECT_EQ(result, "[a]");

    cc->Delete();

    re->Decref();

}



TEST_F(ToStringWalkerTest_NormalOperation_228, PostVisit_Capture_ReturnsCorrectString_228) {

    Regexp* sub = Regexp::NewLiteral('a', Regexp::NoParseFlags);

    Regexp* re = Regexp::Capture(sub, Regexp::NoParseFlags, 1);

    walker->PostVisit(re, 0, 0, nullptr, 1);

    EXPECT_EQ(result, "a)");

    sub->Decref();

    re->Decref();

}



TEST_F(ToStringWalkerTest_NormalOperation_228, PostVisit_HaveMatch_ReturnsCorrectString_228) {

    Regexp* re = Regexp::HaveMatch(1, Regexp::NoParseFlags);

    walker->PostVisit(re, 0, 0, nullptr, 0);

    EXPECT_EQ(result, "(?HaveMatch:1)");

    re->Decref();

}



TEST_F(ToStringWalkerTest_BoundaryConditions_228, PostVisit_NoMatch_PrecLessThanPrecEmpty_ReturnsCorrectString_228) {

    Regexp* re = Regexp::NoMatch();

    walker->PostVisit(re, PrecEmpty - 1, 0, nullptr, 0);

    EXPECT_EQ(result, "[^\\x00-\\x{10ffff}]");

    re->Decref();

}



TEST_F(ToStringWalkerTest_BoundaryConditions_228, PostVisit_LiteralString_PrecLessThanPrecConcat_ReturnsCorrectString_228) {

    Rune runes[] = {'h', 'e', 'l', 'l', 'o'};

    Regexp* re = Regexp::LiteralString(runes, 5, Regexp::NoParseFlags);

    walker->PostVisit(re, PrecConcat - 1, 0, nullptr, 0);

    EXPECT_EQ(result, "hello)");

    re->Decref();

}



TEST_F(ToStringWalkerTest_BoundaryConditions_228, PostVisit_Alternate_PrecLessThanPrecAlternate_ReturnsCorrectString_228) {

    Regexp* sub1 = Regexp::NewLiteral('a', Regexp::NoParseFlags);

    Regexp* sub2 = Regexp::NewLiteral('b', Regexp::NoParseFlags);

    Regexp** subs = new Regexp*[2]{sub1, sub2};

    Regexp* re = Regexp::Alternate(subs, 2, Regexp::NoParseFlags);

    walker->PostVisit(re, PrecAlternate - 1, 0, nullptr, 2);

    EXPECT_EQ(result, "a|b)");

    delete[] subs;

    sub1->Decref();

    sub2->Decref();

    re->Decref();

}



TEST_F(ToStringWalkerTest_BoundaryConditions_228, PostVisit_UnaryOperators_PrecLessThanPrecUnary_ReturnsCorrectString_228) {

    Regexp* sub = Regexp::NewLiteral('a', Regexp::NoParseFlags);

    Regexp* re = Regexp::Star(sub, Regexp::NonGreedy);

    walker->PostVisit(re, PrecUnary - 1, 0, nullptr, 1);

    EXPECT_EQ(result, "a*?)");

    sub->Decref();

    re->Decref();

}
