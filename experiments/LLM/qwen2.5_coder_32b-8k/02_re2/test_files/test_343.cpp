#include "gtest/gtest.h"

#include "gmock/gmock.h"

#include "./TestProjects/re2/re2/regexp.h"



using namespace re2;



class RegexpTest_343 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code if needed

    }



    void TearDown() override {

        // Teardown code if needed

    }

};



TEST_F(RegexpTest_343, AlternateNoFactor_NormalOperation_343) {

    Regexp* sub1 = Regexp::NewLiteral('a', 0);

    Regexp* sub2 = Regexp::NewLiteral('b', 0);

    Regexp** subs = new Regexp*[2];

    subs[0] = sub1;

    subs[1] = sub2;



    Regexp* result = Regexp::AlternateNoFactor(subs, 2, 0);



    EXPECT_EQ(result->op(), kRegexpAlternate);

    EXPECT_EQ(result->nsub(), 2);

    delete[] subs;

    result->Decref();

}



TEST_F(RegexpTest_343, AlternateNoFactor_BoundaryConditions_NoSubexpressions_343) {

    Regexp** subs = new Regexp*[0];

    

    Regexp* result = Regexp::AlternateNoFactor(subs, 0, 0);



    EXPECT_EQ(result->op(), kRegexpNoMatch);

    delete[] subs;

    result->Decref();

}



TEST_F(RegexpTest_343, AlternateNoFactor_BoundaryConditions_OneSubexpression_343) {

    Regexp* sub1 = Regexp::NewLiteral('a', 0);

    Regexp** subs = new Regexp*[1];

    subs[0] = sub1;



    Regexp* result = Regexp::AlternateNoFactor(subs, 1, 0);



    EXPECT_EQ(result->op(), kRegexpLiteral);

    EXPECT_EQ(result->rune(), 'a');

    delete[] subs;

    result->Decref();

}



TEST_F(RegexpTest_343, AlternateNoFactor_ExceptionalCases_NullSubarray_343) {

    Regexp** subs = nullptr;



    Regexp* result = Regexp::AlternateNoFactor(subs, 2, 0);



    EXPECT_EQ(result->op(), kRegexpNoMatch);

    result->Decref();

}



TEST_F(RegexpTest_343, AlternateNoFactor_ExceptionalCases_NegativeSubexpressionCount_343) {

    Regexp* sub1 = Regexp::NewLiteral('a', 0);

    Regexp** subs = new Regexp*[2];

    subs[0] = sub1;

    subs[1] = nullptr;



    Regexp* result = Regexp::AlternateNoFactor(subs, -1, 0);



    EXPECT_EQ(result->op(), kRegexpNoMatch);

    delete[] subs;

    result->Decref();

}



TEST_F(RegexpTest_343, AlternateNoFactor_ExceptionalCases_NullSubexpression_343) {

    Regexp** subs = new Regexp*[2];

    subs[0] = nullptr;

    subs[1] = nullptr;



    Regexp* result = Regexp::AlternateNoFactor(subs, 2, 0);



    EXPECT_EQ(result->op(), kRegexpNoMatch);

    delete[] subs;

    result->Decref();

}
