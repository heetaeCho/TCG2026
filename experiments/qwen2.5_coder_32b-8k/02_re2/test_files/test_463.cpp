#include <gtest/gtest.h>

#include "TestProjects/re2/re2/prefilter.h"



using namespace re2;



class PrefilterTest_463 : public ::testing::Test {

protected:

    void SetUp() override {

        prefilter_and = new Prefilter(Prefilter::AND);

        prefilter_or = new Prefilter(Prefilter::OR);

        prefilter_atom = new Prefilter(Prefilter::ATOM);

    }



    void TearDown() override {

        delete prefilter_and;

        delete prefilter_or;

        delete prefilter_atom;

    }



    Prefilter* prefilter_and;

    Prefilter* prefilter_or;

    Prefilter* prefilter_atom;

};



TEST_F(PrefilterTest_463, SubsReturnsNonNullForAND_463) {

    EXPECT_NE(prefilter_and->subs(), nullptr);

}



TEST_F(PrefilterTest_463, SubsReturnsNonNullForOR_463) {

    EXPECT_NE(prefilter_or->subs(), nullptr);

}



TEST_F(PrefilterTest_463, SubsReturnsNullForATOM_463) {

    EXPECT_EQ(prefilter_atom->subs(), nullptr);

}



TEST_F(PrefilterTest_463, OpReturnsCorrectValueForAND_463) {

    EXPECT_EQ(prefilter_and->op(), Prefilter::AND);

}



TEST_F(PrefilterTest_463, OpReturnsCorrectValueForOR_463) {

    EXPECT_EQ(prefilter_or->op(), Prefilter::OR);

}



TEST_F(PrefilterTest_463, OpReturnsCorrectValueForATOM_463) {

    EXPECT_EQ(prefilter_atom->op(), Prefilter::ATOM);

}



TEST_F(PrefilterTest_463, AtomInitiallyEmpty_463) {

    EXPECT_TRUE(prefilter_atom->atom().empty());

}



TEST_F(PrefilterTest_463, UniqueIdInitiallyZero_463) {

    EXPECT_EQ(prefilter_and->unique_id(), 0);

}



TEST_F(PrefilterTest_463, SetUniqueIdWorksCorrectly_463) {

    prefilter_and->set_unique_id(42);

    EXPECT_EQ(prefilter_and->unique_id(), 42);

}



TEST_F(PrefilterTest_463, SetSubsWorksCorrectly_463) {

    auto subs = new std::vector<Prefilter*>;

    prefilter_and->set_subs(subs);

    EXPECT_EQ(prefilter_and->subs(), subs);

    delete subs;

}
