#include <gtest/gtest.h>

#include "prefilter.h"



using namespace re2;



class PrefilterInfoTest_544 : public ::testing::Test {

protected:

    void SetUp() override {

        // Set up any common state here if necessary.

    }



    void TearDown() override {

        // Clean up after each test case if necessary.

    }

};



TEST_F(PrefilterInfoTest_544, ConcatNullFirst_544) {

    Prefilter::Info* b = new Prefilter::Info();

    Prefilter::Info* result = Prefilter::Info::Concat(nullptr, b);

    EXPECT_EQ(result, b);

}



TEST_F(PrefilterInfoTest_544, ConcatNullSecond_544) {

    Prefilter::Info* a = new Prefilter::Info();

    Prefilter::Info* result = Prefilter::Info::Concat(a, nullptr);

    EXPECT_EQ(result, a);

}



TEST_F(PrefilterInfoTest_544, ConcatBothExact_544) {

    Prefilter::Info* a = new Prefilter::Info();

    Prefilter::Info* b = new Prefilter::Info();

    a->is_exact_ = true;

    b->is_exact_ = true;

    Prefilter::Info* result = Prefilter::Info::Concat(a, b);

    EXPECT_TRUE(result->is_exact_);

    delete result;

}



TEST_F(PrefilterInfoTest_544, ConcatNonExactA_544) {

    Prefilter::Info* a = new Prefilter::Info();

    Prefilter::Info* b = new Prefilter::Info();

    a->is_exact_ = false;

    b->is_exact_ = true;

    EXPECT_DEATH(Prefilter::Info::Concat(a, b), ".*");

}



TEST_F(PrefilterInfoTest_544, ConcatNonExactB_544) {

    Prefilter::Info* a = new Prefilter::Info();

    Prefilter::Info* b = new Prefilter::Info();

    a->is_exact_ = true;

    b->is_exact_ = false;

    EXPECT_DEATH(Prefilter::Info::Concat(a, b), ".*");

}
