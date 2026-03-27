#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "re2/prefilter.h"



namespace re2 {



class PrefilterTest_462 : public ::testing::Test {

protected:

    Prefilter* prefilter;



    void SetUp() override {

        prefilter = new Prefilter(Prefilter::Op::kNone);

    }



    void TearDown() override {

        delete prefilter;

    }

};



TEST_F(PrefilterTest_462, UniqueIdInitialization_462) {

    EXPECT_EQ(prefilter->unique_id(), 0);

}



TEST_F(PrefilterTest_462, SetUniqueIdChangesValue_462) {

    int test_id = 123;

    prefilter->set_unique_id(test_id);

    EXPECT_EQ(prefilter->unique_id(), test_id);

}



TEST_F(PrefilterTest_462, AtomDefaultIsEmptyString_462) {

    EXPECT_EQ(prefilter->atom(), "");

}



TEST_F(PrefilterTest_462, SubsDefaultIsNullptr_462) {

    EXPECT_EQ(prefilter->subs(), nullptr);

}



TEST_F(PrefilterTest_462, SetSubsChangesValue_462) {

    std::vector<Prefilter*> subs;

    prefilter->set_subs(&subs);

    EXPECT_EQ(prefilter->subs(), &subs);

}



TEST_F(PrefilterTest_462, OpInitializationIsCorrect_462) {

    Prefilter another_prefilter(Prefilter::Op::kConcatenate);

    EXPECT_EQ(another_prefilter.op(), Prefilter::Op::kConcatenate);

}



}  // namespace re2
