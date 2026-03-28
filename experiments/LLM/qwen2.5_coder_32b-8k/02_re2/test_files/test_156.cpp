#include <gtest/gtest.h>

#include "regexp.h"



using namespace re2;



class RegexpTest_156 : public ::testing::Test {

protected:

    void SetUp() override {

        status = new RegexpStatus();

    }



    void TearDown() override {

        delete status;

    }



    RegexpStatus* status;

};



TEST_F(RegexpTest_156, ParseValidLiteral_156) {

    Regexp* regexp = Regexp::Parse("a", Regexp::ParseFlags(0), status);

    ASSERT_TRUE(regexp != nullptr);

    EXPECT_EQ(regexp->op(), kRegexpLiteral);

    EXPECT_EQ(regexp->rune(), 'a');

    regexp->Decref();

}



TEST_F(RegexpTest_156, ParseInvalidExpression_156) {

    Regexp* regexp = Regexp::Parse("[", Regexp::ParseFlags(0), status);

    EXPECT_TRUE(regexp == nullptr);

    EXPECT_FALSE(status->ok());

}



TEST_F(RegexpTest_156, NumCapturesZero_156) {

    Regexp* regexp = Regexp::NewLiteral('a', Regexp::ParseFlags(0));

    ASSERT_TRUE(regexp != nullptr);

    EXPECT_EQ(regexp->NumCaptures(), 0);

    regexp->Decref();

}



TEST_F(RegexpTest_156, NumCapturesPositive_156) {

    Regexp* sub = Regexp::NewLiteral('a', Regexp::ParseFlags(0));

    ASSERT_TRUE(sub != nullptr);

    Regexp* regexp = Regexp::Capture(sub, Regexp::ParseFlags(0), 1);

    ASSERT_TRUE(regexp != nullptr);

    EXPECT_EQ(regexp->NumCaptures(), 1);

    regexp->Decref();

}



TEST_F(RegexpTest_156, CaptureNameMapping_156) {

    Regexp* sub = Regexp::NewLiteral('a', Regexp::ParseFlags(0));

    ASSERT_TRUE(sub != nullptr);

    Regexp* regexp = Regexp::Capture(sub, Regexp::ParseFlags(0), 1);

    ASSERT_TRUE(regexp != nullptr);

    std::map<int, std::string>* capture_names = regexp->CaptureNames();

    EXPECT_EQ(capture_names->size(), 0); // Capture name mapping is not set in this context

    delete capture_names;

    regexp->Decref();

}



TEST_F(RegexpTest_156, RequiredPrefixNone_156) {

    Regexp* regexp = Regexp::NewLiteral('a', Regexp::ParseFlags(0));

    ASSERT_TRUE(regexp != nullptr);

    std::string prefix;

    bool foldcase;

    Regexp* suffix;

    EXPECT_FALSE(regexp->RequiredPrefix(&prefix, &foldcase, &suffix));

    EXPECT_EQ(prefix, "");

    regexp->Decref();

}



TEST_F(RegexpTest_156, RuneLiteral_156) {

    Regexp* regexp = Regexp::NewLiteral('a', Regexp::ParseFlags(0));

    ASSERT_TRUE(regexp != nullptr);

    EXPECT_EQ(regexp->rune(), 'a');

    regexp->Decref();

}



TEST_F(RegexpTest_156, RefCountingIncrement_156) {

    Regexp* regexp = Regexp::NewLiteral('a', Regexp::ParseFlags(0));

    ASSERT_TRUE(regexp != nullptr);

    int initial_ref_count = regexp->Ref();

    regexp->Incref();

    EXPECT_EQ(regexp->Ref(), initial_ref_count + 1);

    regexp->Decref(); // Decrease to initial ref count

    regexp->Decref(); // Clean up

}



TEST_F(RegexpTest_156, RefCountingDecrement_156) {

    Regexp* regexp = Regexp::NewLiteral('a', Regexp::ParseFlags(0));

    ASSERT_TRUE(regexp != nullptr);

    regexp->Incref();

    int initial_ref_count = regexp->Ref();

    regexp->Decref();

    EXPECT_EQ(regexp->Ref(), initial_ref_count - 1);

    // No need to Decref again as the ref count is back to 1

}
