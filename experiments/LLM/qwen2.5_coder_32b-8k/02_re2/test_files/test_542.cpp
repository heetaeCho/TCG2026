#include <gtest/gtest.h>

#include "re2/prefilter.h"



using namespace re2;



class PrefilterTest_542 : public ::testing::Test {

protected:

    Prefilter* prefilter;

    

    void SetUp() override {

        // Initialize any objects or state needed for the tests

        prefilter = new Prefilter(Prefilter::Op(0));

    }



    void TearDown() override {

        // Clean up any objects or state after each test

        delete prefilter;

    }

};



TEST_F(PrefilterTest_542, TakeMatch_ReturnsNullInitially_542) {

    EXPECT_EQ(prefilter->Info().TakeMatch(), nullptr);

}



TEST_F(PrefilterTest_542, TakeMatch_ReturnsMatchAfterSetting_542) {

    Prefilter* expected_match = new Prefilter(Prefilter::Op(0));

    prefilter->Info().match_ = expected_match;

    EXPECT_EQ(prefilter->Info().TakeMatch(), expected_match);

    EXPECT_EQ(prefilter->Info().match_, nullptr); // match should be reset to NULL after TakeMatch

    delete expected_match; // Clean up the allocated Prefilter object

}



TEST_F(PrefilterTest_542, TakeMatch_HandlesExactFlag_542) {

    prefilter->Info().is_exact_ = true;

    EXPECT_EQ(prefilter->Info().TakeMatch(), nullptr); // No match set yet

    EXPECT_FALSE(prefilter->Info().is_exact_); // is_exact_ should be reset to false after TakeMatch

}



TEST_F(PrefilterTest_542, Info_ConstructorInitializesCorrectly_542) {

    Prefilter::Info info;

    EXPECT_TRUE(info.is_exact() == false);

    EXPECT_EQ(info.match_, nullptr);

}
