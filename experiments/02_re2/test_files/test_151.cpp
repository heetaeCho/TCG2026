#include <gtest/gtest.h>

#include "re2/regexp.h"

#include "absl/strings/string_view.h"



namespace re2 {



class RegexpTest_151 : public ::testing::Test {

protected:

    RegexpStatus status;

};



TEST_F(RegexpTest_151, SimpleLiteral_151) {

    Regexp* literal = Regexp::NewLiteral('a', 0);

    EXPECT_TRUE(literal->simple());

    literal->Decref();

}



TEST_F(RegexpTest_151, SimpleConcatenation_151) {

    Regexp* sub1 = Regexp::NewLiteral('a', 0);

    Regexp* sub2 = Regexp::NewLiteral('b', 0);

    Regexp** subs = new Regexp*[2]{sub1, sub2};

    Regexp* concat = Regexp::Concat(subs, 2, 0);

    EXPECT_FALSE(concat->simple());

    concat->Decref();

    delete[] subs;

}



TEST_F(RegexpTest_151, SimpleAlternation_151) {

    Regexp* sub1 = Regexp::NewLiteral('a', 0);

    Regexp* sub2 = Regexp::NewLiteral('b', 0);

    Regexp** subs = new Regexp*[2]{sub1, sub2};

    Regexp* alternation = Regexp::Alternate(subs, 2, 0);

    EXPECT_FALSE(alternation->simple());

    alternation->Decref();

    delete[] subs;

}



TEST_F(RegexpTest_151, SimpleStar_151) {

    Regexp* sub = Regexp::NewLiteral('a', 0);

    Regexp* star = Regexp::Star(sub, 0);

    EXPECT_FALSE(star->simple());

    star->Decref();

}



TEST_F(RegexpTest_151, SimplePlus_151) {

    Regexp* sub = Regexp::NewLiteral('a', 0);

    Regexp* plus = Regexp::Plus(sub, 0);

    EXPECT_FALSE(plus->simple());

    plus->Decref();

}



TEST_F(RegexpTest_151, SimpleQuest_151) {

    Regexp* sub = Regexp::NewLiteral('a', 0);

    Regexp* quest = Regexp::Quest(sub, 0);

    EXPECT_FALSE(quest->simple());

    quest->Decref();

}



TEST_F(RegexpTest_151, SimpleCapture_151) {

    Regexp* sub = Regexp::NewLiteral('a', 0);

    Regexp* capture = Regexp::Capture(sub, 0, 1);

    EXPECT_FALSE(capture->simple());

    capture->Decref();

}



TEST_F(RegexpTest_151, SimpleRepeat_151) {

    Regexp* sub = Regexp::NewLiteral('a', 0);

    Regexp* repeat = Regexp::Repeat(sub, 0, 2, 3);

    EXPECT_FALSE(repeat->simple());

    repeat->Decref();

}



TEST_F(RegexpTest_151, SimpleParseEmptyString_151) {

    Regexp* empty = Regexp::Parse("", 0, &status);

    EXPECT_TRUE(empty != nullptr);

    EXPECT_TRUE(empty->simple());

    empty->Decref();

}



TEST_F(RegexpTest_151, SimpleParseLiteral_151) {

    Regexp* literal = Regexp::Parse("a", 0, &status);

    EXPECT_TRUE(literal != nullptr);

    EXPECT_TRUE(literal->simple());

    literal->Decref();

}



TEST_F(RegexpTest_151, SimpleParseComplexString_151) {

    Regexp* complex = Regexp::Parse("(a|b)*", 0, &status);

    EXPECT_TRUE(complex != nullptr);

    EXPECT_FALSE(complex->simple());

    complex->Decref();

}



TEST_F(RegexpTest_151, ParseInvalidRegex_151) {

    Regexp* invalid = Regexp::Parse("(", 0, &status);

    EXPECT_TRUE(invalid == nullptr);

}



TEST_F(RegexpTest_151, SimpleAfterSimplify_151) {

    Regexp* complex = Regexp::Parse("(a|b)*", 0, &status);

    EXPECT_TRUE(complex != nullptr);

    Regexp* simplified = complex->Simplify();

    EXPECT_FALSE(simplified->simple());

    simplified->Decref();

    complex->Decref();

}



TEST_F(RegexpTest_151, SimpleAfterCapture_151) {

    Regexp* literal = Regexp::NewLiteral('a', 0);

    Regexp* capture = Regexp::Capture(literal, 0, 1);

    EXPECT_FALSE(capture->simple());

    capture->Decref();

}



TEST_F(RegexpTest_151, RefCounting_151) {

    Regexp* literal = Regexp::NewLiteral('a', 0);

    EXPECT_EQ(literal->Ref(), 1);



    Regexp* incremented = literal->Incref();

    EXPECT_EQ(incremented->Ref(), 2);



    literal->Decref();

    EXPECT_EQ(literal->Ref(), 1);

    literal->Decref();

}



TEST_F(RegexpTest_151, NumCapturesZero_151) {

    Regexp* literal = Regexp::NewLiteral('a', 0);

    EXPECT_EQ(literal->NumCaptures(), 0);

    literal->Decref();

}



TEST_F(RegexpTest_151, NumCapturesOne_151) {

    Regexp* literal = Regexp::NewLiteral('a', 0);

    Regexp* capture = Regexp::Capture(literal, 0, 1);

    EXPECT_EQ(capture->NumCaptures(), 1);

    capture->Decref();

}



TEST_F(RegexpTest_151, NumCapturesMultiple_151) {

    Regexp* sub1 = Regexp::NewLiteral('a', 0);

    Regexp* cap1 = Regexp::Capture(sub1, 0, 1);



    Regexp* sub2 = Regexp::NewLiteral('b', 0);

    Regexp* cap2 = Regexp::Capture(sub2, 0, 2);



    Regexp** subs = new Regexp*[2]{cap1, cap2};

    Regexp* concat = Regexp::Concat(subs, 2, 0);

    EXPECT_EQ(concat->NumCaptures(), 2);

    concat->Decref();

    delete[] subs;

}



TEST_F(RegexpTest_151, NamedCapturesEmpty_151) {

    Regexp* literal = Regexp::NewLiteral('a', 0);

    std::map<std::string, int>* named_captures = literal->NamedCaptures();

    EXPECT_TRUE(named_captures->empty());

    delete named_captures;

    literal->Decref();

}



TEST_F(RegexpTest_151, CaptureNamesEmpty_151) {

    Regexp* literal = Regexp::NewLiteral('a', 0);

    std::map<int, std::string>* capture_names = literal->CaptureNames();

    EXPECT_TRUE(capture_names->empty());

    delete capture_names;

    literal->Decref();

}



TEST_F(RegexpTest_151, MimicsPCREFalse_151) {

    Regexp* literal = Regexp::NewLiteral('a', 0);

    EXPECT_FALSE(literal->MimicsPCRE());

    literal->Decref();

}



}  // namespace re2
