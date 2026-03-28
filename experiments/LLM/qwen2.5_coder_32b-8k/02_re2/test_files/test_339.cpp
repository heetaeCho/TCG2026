#include "gtest/gtest.h"

#include "gmock/gmock.h"

#include "./TestProjects/re2/re2/regexp.h"



using namespace re2;



class RegexpTest_339 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code, if needed

    }



    void TearDown() override {

        // Teardown code, if needed

    }

};



TEST_F(RegexpTest_339, StarNormalOperation_339) {

    Regexp* sub = Regexp::NewLiteral('a', 0);

    Regexp* result = sub->Star(sub, 0);



    EXPECT_EQ(result->op(), kRegexpStar);

    EXPECT_EQ(result->sub()[0], sub);



    result->Decref();

}



TEST_F(RegexpTest_339, StarBoundaryConditionNullSub_339) {

    Regexp* sub = nullptr;

    Regexp* result = Regexp::Star(sub, 0);



    EXPECT_EQ(result, nullptr);

}



TEST_F(RegexpTest_339, StarBoundaryConditionEmptyStringSub_339) {

    Regexp* sub = Regexp::LiteralString(nullptr, 0, 0);

    Regexp* result = sub->Star(sub, 0);



    EXPECT_EQ(result->op(), kRegexpStar);

    EXPECT_EQ(result->sub()[0], sub);



    result->Decref();

}



TEST_F(RegexpTest_339, StarVerificationOfExternalInteractions_339) {

    Regexp* sub = Regexp::NewLiteral('a', 0);

    Regexp* result = sub->Star(sub, 0);



    EXPECT_EQ(result->op(), kRegexpStar);

    EXPECT_EQ(result->sub()[0], sub);



    result->Decref();

}



TEST_F(RegexpTest_339, StarRefCounting_339) {

    Regexp* sub = Regexp::NewLiteral('a', 0);

    Regexp* result = sub->Star(sub, 0);



    EXPECT_EQ(result->Ref(), 1);

    EXPECT_EQ(sub->Ref(), 2); // One ref from the star and one explicit



    result->Decref();

    EXPECT_EQ(sub->Ref(), 1); // Decrement the ref count of the sub

}



TEST_F(RegexpTest_339, StarExceptionalCaseNullSub_339) {

    Regexp* sub = nullptr;

    Regexp* result = Regexp::Star(sub, 0);



    EXPECT_EQ(result, nullptr);

}
