#include <gtest/gtest.h>

#include "re2/regexp.h"

#include "re2/mimics_pcre.cc"



using namespace re2;



class PCREWalkerTest : public ::testing::Test {

protected:

    PCREWalker walker;

};



TEST_F(PCREWalkerTest, PostVisitStarWithEmptyStringChild_219) {

    Regexp* child = Regexp::NewLiteral('\0', Regexp::NoParseFlags);

    bool child_args[] = {true};

    EXPECT_FALSE(walker.PostVisit(Regexp::Star(child, Regexp::NoParseFlags), true, true, child_args, 1));

    child->Decref();

}



TEST_F(PCREWalkerTest, PostVisitPlusWithEmptyStringChild_219) {

    Regexp* child = Regexp::NewLiteral('\0', Regexp::NoParseFlags);

    bool child_args[] = {true};

    EXPECT_FALSE(walker.PostVisit(Regexp::Plus(child, Regexp::NoParseFlags), true, true, child_args, 1));

    child->Decref();

}



TEST_F(PCREWalkerTest, PostVisitQuestWithEmptyStringChild_219) {

    Regexp* child = Regexp::NewLiteral('\0', Regexp::NoParseFlags);

    bool child_args[] = {true};

    EXPECT_FALSE(walker.PostVisit(Regexp::Quest(child, Regexp::NoParseFlags), true, true, child_args, 1));

    child->Decref();

}



TEST_F(PCREWalkerTest, PostVisitRepeatWithMaxUnlimitedAndEmptyStringChild_219) {

    Regexp* child = Regexp::NewLiteral('\0', Regexp::NoParseFlags);

    bool child_args[] = {true};

    EXPECT_FALSE(walker.PostVisit(Regexp::Repeat(child, Regexp::NoParseFlags, 0, -1), true, true, child_args, 1));

    child->Decref();

}



TEST_F(PCREWalkerTest, PostVisitLiteralWithVerticalTab_219) {

    Regexp* literal = Regexp::NewLiteral('\v', Regexp::NoParseFlags);

    bool child_args[] = {true};

    EXPECT_FALSE(walker.PostVisit(literal, true, true, child_args, 0));

    literal->Decref();

}



TEST_F(PCREWalkerTest, PostVisitEndTextWithWasDollar_219) {

    Regexp* end_text = Regexp::NewLiteral('\0', Regexp::WasDollar);

    bool child_args[] = {true};

    EXPECT_FALSE(walker.PostVisit(end_text, true, true, child_args, 0));

    end_text->Decref();

}



TEST_F(PCREWalkerTest, PostVisitEmptyMatchWithWasDollar_219) {

    Regexp* empty_match = Regexp::HaveMatch(0, Regexp::WasDollar);

    bool child_args[] = {true};

    EXPECT_FALSE(walker.PostVisit(empty_match, true, true, child_args, 0));

    empty_match->Decref();

}



TEST_F(PCREWalkerTest, PostVisitBeginLine_219) {

    Regexp* begin_line = Regexp::HaveMatch(0, Regexp::NoParseFlags);

    bool child_args[] = {true};

    EXPECT_FALSE(walker.PostVisit(begin_line, true, true, child_args, 0));

    begin_line->Decref();

}



TEST_F(PCREWalkerTest, PostVisitConcatWithAllTrueChildren_219) {

    Regexp* child1 = Regexp::NewLiteral('a', Regexp::NoParseFlags);

    Regexp* child2 = Regexp::NewLiteral('b', Regexp::NoParseFlags);

    Regexp** subs = new Regexp*[2]{child1, child2};

    bool child_args[] = {true, true};

    EXPECT_TRUE(walker.PostVisit(Regexp::Concat(subs, 2, Regexp::NoParseFlags), true, true, child_args, 2));

    delete[] subs;

    child1->Decref();

    child2->Decref();

}



TEST_F(PCREWalkerTest, PostVisitConcatWithOneFalseChild_219) {

    Regexp* child1 = Regexp::NewLiteral('a', Regexp::NoParseFlags);

    Regexp* child2 = Regexp::NewLiteral('\0', Regexp::NoParseFlags);

    Regexp** subs = new Regexp*[2]{child1, child2};

    bool child_args[] = {true, false};

    EXPECT_FALSE(walker.PostVisit(Regexp::Concat(subs, 2, Regexp::NoParseFlags), true, true, child_args, 2));

    delete[] subs;

    child1->Decref();

    child2->Decref();

}



TEST_F(PCREWalkerTest, PostVisitAlternateWithAllTrueChildren_219) {

    Regexp* child1 = Regexp::NewLiteral('a', Regexp::NoParseFlags);

    Regexp* child2 = Regexp::NewLiteral('b', Regexp::NoParseFlags);

    Regexp** subs = new Regexp*[2]{child1, child2};

    bool child_args[] = {true, true};

    EXPECT_TRUE(walker.PostVisit(Regexp::Alternate(subs, 2, Regexp::NoParseFlags), true, true, child_args, 2));

    delete[] subs;

    child1->Decref();

    child2->Decref();

}



TEST_F(PCREWalkerTest, PostVisitAlternateWithOneFalseChild_219) {

    Regexp* child1 = Regexp::NewLiteral('a', Regexp::NoParseFlags);

    Regexp* child2 = Regexp::NewLiteral('\0', Regexp::NoParseFlags);

    Regexp** subs = new Regexp*[2]{child1, child2};

    bool child_args[] = {true, false};

    EXPECT_TRUE(walker.PostVisit(Regexp::Alternate(subs, 2, Regexp::NoParseFlags), true, true, child_args, 2));

    delete[] subs;

    child1->Decref();

    child2->Decref();

}
