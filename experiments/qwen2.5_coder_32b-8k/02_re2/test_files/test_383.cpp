#include <gtest/gtest.h>

#include "re2/regexp.h"

#include "re2/fuzzing/re2_fuzzer.cc"



using namespace re2;



class SubstringWalkerTest_383 : public ::testing::Test {

protected:

    SubstringWalker walker;

};



TEST_F(SubstringWalkerTest_383, LiteralString_ReturnsLength_383) {

    Rune runes[] = {'a', 'b', 'c'};

    Regexp* re = Regexp::LiteralString(runes, 3, Regexp::NoParseFlags);

    int result = walker.PostVisit(re, 0, 0, nullptr, 0);

    EXPECT_EQ(result, 3);

    delete re;

}



TEST_F(SubstringWalkerTest_383, Concat_ReturnsMaxChildValue_383) {

    Rune runes[] = {'a', 'b'};

    Regexp* child1 = Regexp::LiteralString(runes, 2, Regexp::NoParseFlags);

    Regexp* child2 = Regexp::LiteralString(runes + 2, 1, Regexp::NoParseFlags);

    Regexp** subs = new Regexp*[2];

    subs[0] = child1;

    subs[1] = child2;

    Regexp* re = Regexp::Concat(subs, 2, Regexp::NoParseFlags);



    int child_args[] = {2, 1};

    int result = walker.PostVisit(re, 0, 0, child_args, 2);

    EXPECT_EQ(result, 2);



    delete[] subs;

    delete re;

}



TEST_F(SubstringWalkerTest_383, Alternate_ReturnsMaxChildValue_383) {

    Rune runes[] = {'a', 'b'};

    Regexp* child1 = Regexp::LiteralString(runes, 2, Regexp::NoParseFlags);

    Regexp* child2 = Regexp::LiteralString(runes + 2, 1, Regexp::NoParseFlags);

    Regexp** subs = new Regexp*[2];

    subs[0] = child1;

    subs[1] = child2;

    Regexp* re = Regexp::Alternate(subs, 2, Regexp::NoParseFlags);



    int child_args[] = {2, 1};

    int result = walker.PostVisit(re, 0, 0, child_args, 2);

    EXPECT_EQ(result, 2);



    delete[] subs;

    delete re;

}



TEST_F(SubstringWalkerTest_383, Star_ReturnsNegativeOne_383) {

    Rune runes[] = {'a'};

    Regexp* child = Regexp::LiteralString(runes, 1, Regexp::NoParseFlags);

    Regexp* re = Regexp::Star(child, Regexp::NoParseFlags);



    int child_args[] = {1};

    int result = walker.PostVisit(re, 0, 0, child_args, 1);

    EXPECT_EQ(result, -1);



    delete re;

}



TEST_F(SubstringWalkerTest_383, Plus_ReturnsNegativeOne_383) {

    Rune runes[] = {'a'};

    Regexp* child = Regexp::LiteralString(runes, 1, Regexp::NoParseFlags);

    Regexp* re = Regexp::Plus(child, Regexp::NoParseFlags);



    int child_args[] = {1};

    int result = walker.PostVisit(re, 0, 0, child_args, 1);

    EXPECT_EQ(result, -1);



    delete re;

}



TEST_F(SubstringWalkerTest_383, Quest_ReturnsNegativeOne_383) {

    Rune runes[] = {'a'};

    Regexp* child = Regexp::LiteralString(runes, 1, Regexp::NoParseFlags);

    Regexp* re = Regexp::Quest(child, Regexp::NoParseFlags);



    int child_args[] = {1};

    int result = walker.PostVisit(re, 0, 0, child_args, 1);

    EXPECT_EQ(result, -1);



    delete re;

}



TEST_F(SubstringWalkerTest_383, Repeat_ReturnsNegativeOne_383) {

    Rune runes[] = {'a'};

    Regexp* child = Regexp::LiteralString(runes, 1, Regexp::NoParseFlags);

    Regexp* re = Regexp::Repeat(child, Regexp::NoParseFlags, 2, 4);



    int child_args[] = {1};

    int result = walker.PostVisit(re, 0, 0, child_args, 1);

    EXPECT_EQ(result, -1);



    delete re;

}



TEST_F(SubstringWalkerTest_383, Capture_ReturnsNegativeOne_383) {

    Rune runes[] = {'a'};

    Regexp* child = Regexp::LiteralString(runes, 1, Regexp::NoParseFlags);

    Regexp* re = Regexp::Capture(child, Regexp::NoParseFlags, 1);



    int child_args[] = {1};

    int result = walker.PostVisit(re, 0, 0, child_args, 1);

    EXPECT_EQ(result, -1);



    delete re;

}



TEST_F(SubstringWalkerTest_383, Default_ReturnsNegativeOne_383) {

    Regexp* re = new Regexp(kRegexpNoMatch, Regexp::NoParseFlags);



    int result = walker.PostVisit(re, 0, 0, nullptr, 0);

    EXPECT_EQ(result, -1);



    delete re;

}



TEST_F(SubstringWalkerTest_383, NoChildren_ReturnsNegativeOne_383) {

    Regexp* re = new Regexp(kRegexpEmptyMatch, Regexp::NoParseFlags);



    int result = walker.PostVisit(re, 0, 0, nullptr, 0);

    EXPECT_EQ(result, -1);



    delete re;

}
