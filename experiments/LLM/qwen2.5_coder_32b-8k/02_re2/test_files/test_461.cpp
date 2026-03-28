#include <gtest/gtest.h>

#include "re2/prefilter.h"



using namespace re2;



class PrefilterTest_461 : public ::testing::Test {

protected:

    Prefilter* prefilter_;



    void SetUp() override {

        prefilter_ = new Prefilter(Prefilter::Op(0));

    }



    void TearDown() override {

        delete prefilter_;

    }

};



TEST_F(PrefilterTest_461, SetAndGetUniqueId_NormalOperation_461) {

    int test_id = 42;

    prefilter_->set_unique_id(test_id);

    EXPECT_EQ(prefilter_->unique_id(), test_id);

}



TEST_F(PrefilterTest_461, UniqueId_DefaultValue_461) {

    EXPECT_EQ(prefilter_->unique_id(), 0); // Assuming default value is 0

}



TEST_F(PrefilterTest_461, Atom_DefaultValue_461) {

    EXPECT_TRUE(prefilter_->atom().empty());

}



TEST_F(PrefilterTest_461, Subs_DefaultValue_461) {

    EXPECT_EQ(prefilter_->subs(), nullptr);

}



TEST_F(PrefilterTest_461, Op_DefaultValue_461) {

    EXPECT_EQ(prefilter_->op(), Prefilter::Op(0));

}
