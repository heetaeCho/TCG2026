#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "re2/prefilter.cc"



namespace re2 {



class PrefilterInfoTest : public ::testing::Test {

protected:

    Prefilter::Info* info;



    void SetUp() override {

        info = new Prefilter::Info();

    }



    void TearDown() override {

        delete info;

    }

};



TEST_F(PrefilterInfoTest_553, LiteralLatin1_NormalOperation_553) {

    Rune r = 'A';

    Prefilter::Info* result = Prefilter::Info::LiteralLatin1(r);

    EXPECT_EQ(result->exact_.size(), 1);

    EXPECT_TRUE(result->is_exact_);

    delete result;

}



TEST_F(PrefilterInfoTest_553, LiteralLatin1_BoundaryConditions_553) {

    Rune r_min = '\0';

    Prefilter::Info* result_min = Prefilter::Info::LiteralLatin1(r_min);

    EXPECT_EQ(result_min->exact_.size(), 1);

    EXPECT_TRUE(result_min->is_exact_);

    delete result_min;



    Rune r_max = '\xFF'; // Latin1 character range

    Prefilter::Info* result_max = Prefilter::Info::LiteralLatin1(r_max);

    EXPECT_EQ(result_max->exact_.size(), 1);

    EXPECT_TRUE(result_max->is_exact_);

    delete result_max;

}



TEST_F(PrefilterInfoTest_553, LiteralLatin1_LowercaseConversion_553) {

    Rune r = 'A';

    Prefilter::Info* result = Prefilter::Info::LiteralLatin1(r);

    EXPECT_EQ(result->exact_.count("a"), 1); // Should be converted to lowercase

    delete result;

}



TEST_F(PrefilterInfoTest_553, ExactAccess_553) {

    Rune r = 'B';

    Prefilter::Info* result = Prefilter::Info::LiteralLatin1(r);

    SSet& exact_set = result->exact();

    EXPECT_EQ(exact_set.count("b"), 1); // Should be converted to lowercase

    delete result;

}



TEST_F(PrefilterInfoTest_553, IsExactAccess_553) {

    Rune r = 'C';

    Prefilter::Info* result = Prefilter::Info::LiteralLatin1(r);

    EXPECT_TRUE(result->is_exact());

    delete result;

}



} // namespace re2
