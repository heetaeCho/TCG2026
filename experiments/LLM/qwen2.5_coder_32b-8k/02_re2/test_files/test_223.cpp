#include <gtest/gtest.h>

#include "re2/regexp.h"

#include "re2/mimics_pcre.cc"



namespace re2 {



class CanBeEmptyStringTest_223 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code if needed

    }



    void TearDown() override {

        // Teardown code if needed

    }

};



TEST_F(CanBeEmptyStringTest_223, NormalOperation_EmptyStringLiteral_223) {

    Regexp* re = Regexp::NewLiteral(0, kNoParseFlags); // 0 represents empty string in Rune context

    bool result = CanBeEmptyString(re);

    EXPECT_TRUE(result);

    re->Decref();

}



TEST_F(CanBeEmptyStringTest_223, NormalOperation_NonEmptyStringLiteral_223) {

    Regexp* re = Regexp::NewLiteral('a', kNoParseFlags);

    bool result = CanBeEmptyString(re);

    EXPECT_FALSE(result);

    re->Decref();

}



TEST_F(CanBeEmptyStringTest_223, BoundaryCondition_EmptyConcatenation_223) {

    Regexp* sub1 = Regexp::NewLiteral(0, kNoParseFlags); // Empty string

    Regexp* subs[] = {sub1};

    Regexp* re = Regexp::Concat(subs, 1, kNoParseFlags);

    bool result = CanBeEmptyString(re);

    EXPECT_TRUE(result);

    re->Decref();

}



TEST_F(CanBeEmptyStringTest_223, BoundaryCondition_NonEmptyConcatenation_223) {

    Regexp* sub1 = Regexp::NewLiteral('a', kNoParseFlags);

    Regexp* subs[] = {sub1};

    Regexp* re = Regexp::Concat(subs, 1, kNoParseFlags);

    bool result = CanBeEmptyString(re);

    EXPECT_FALSE(result);

    re->Decref();

}



TEST_F(CanBeEmptyStringTest_223, BoundaryCondition_EmptyAlternation_223) {

    Regexp* sub1 = Regexp::NewLiteral(0, kNoParseFlags); // Empty string

    Regexp* subs[] = {sub1};

    Regexp* re = Regexp::Alternate(subs, 1, kNoParseFlags);

    bool result = CanBeEmptyString(re);

    EXPECT_TRUE(result);

    re->Decref();

}



TEST_F(CanBeEmptyStringTest_223, BoundaryCondition_NonEmptyAlternation_223) {

    Regexp* sub1 = Regexp::NewLiteral('a', kNoParseFlags);

    Regexp* subs[] = {sub1};

    Regexp* re = Regexp::Alternate(subs, 1, kNoParseFlags);

    bool result = CanBeEmptyString(re);

    EXPECT_FALSE(result);

    re->Decref();

}



TEST_F(CanBeEmptyStringTest_223, ExceptionalCase_NullRegexpPointer_223) {

    Regexp* re = nullptr;

    bool result = CanBeEmptyString(re);

    // Assuming the function handles null gracefully

    EXPECT_FALSE(result);

}



TEST_F(CanBeEmptyStringTest_223, NormalOperation_QuestOperator_223) {

    Regexp* sub1 = Regexp::NewLiteral('a', kNoParseFlags);

    Regexp* re = Regexp::Quest(sub1, kNoParseFlags);

    bool result = CanBeEmptyString(re);

    EXPECT_TRUE(result);

    re->Decref();

}



TEST_F(CanBeEmptyStringTest_223, NormalOperation_StarOperator_223) {

    Regexp* sub1 = Regexp::NewLiteral('a', kNoParseFlags);

    Regexp* re = Regexp::Star(sub1, kNoParseFlags);

    bool result = CanBeEmptyString(re);

    EXPECT_TRUE(result);

    re->Decref();

}



TEST_F(CanBeEmptyStringTest_223, NormalOperation_PlusOperator_223) {

    Regexp* sub1 = Regexp::NewLiteral('a', kNoParseFlags);

    Regexp* re = Regexp::Plus(sub1, kNoParseFlags);

    bool result = CanBeEmptyString(re);

    EXPECT_FALSE(result);

    re->Decref();

}



} // namespace re2
