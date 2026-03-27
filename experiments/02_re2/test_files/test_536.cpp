#include <gtest/gtest.h>

#include "prefilter.h"

#include "re2/re2.h"



using namespace re2;



class PrefilterTest_536 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code if needed

    }



    void TearDown() override {

        // Teardown code if needed

    }

};



TEST_F(PrefilterTest_536, CreateAndDestroy_536) {

    Prefilter* prefilter = new Prefilter(Prefilter::Op::kAtom);

    delete prefilter;

}



TEST_F(PrefilterTest_536, FromRE2_ReturnsNonNull_536) {

    RE2 re("(a|b)");

    Prefilter* prefilter = Prefilter::FromRE2(&re);

    EXPECT_NE(prefilter, nullptr);

    delete prefilter;

}



TEST_F(PrefilterTest_536, DebugString_NotEmptyForAtom_536) {

    Prefilter* prefilter = new Prefilter(Prefilter::Op::kAtom);

    prefilter->set_subs(new std::vector<Prefilter*>());

    EXPECT_FALSE(prefilter->DebugString().empty());

    delete prefilter;

}



TEST_F(PrefilterTest_536, SetAndGetUniqueId_536) {

    Prefilter* prefilter = new Prefilter(Prefilter::Op::kAtom);

    prefilter->set_unique_id(42);

    EXPECT_EQ(prefilter->unique_id(), 42);

    delete prefilter;

}



TEST_F(PrefilterTest_536, SetAndGetSubs_536) {

    Prefilter* prefilter = new Prefilter(Prefilter::Op::kAtom);

    std::vector<Prefilter*>* subs = new std::vector<Prefilter*>();

    prefilter->set_subs(subs);

    EXPECT_EQ(prefilter->subs(), subs);

    delete prefilter;

}



TEST_F(PrefilterTest_536, Op_ReturnsCorrectValue_536) {

    Prefilter* prefilter = new Prefilter(Prefilter::Op::kOr);

    EXPECT_EQ(prefilter->op(), Prefilter::Op::kOr);

    delete prefilter;

}



TEST_F(PrefilterTest_536, Atom_ReturnsExpectedString_536) {

    Prefilter* prefilter = new Prefilter(Prefilter::Op::kAtom);

    std::string test_atom = "test";

    prefilter->set_subs(new std::vector<Prefilter*>());

    prefilter->atom() = test_atom;

    EXPECT_EQ(prefilter->atom(), test_atom);

    delete prefilter;

}



TEST_F(PrefilterTest_536, DebugString_NotEmptyForComplexExpression_536) {

    RE2 re("(a|b)(c|d)");

    Prefilter* prefilter = Prefilter::FromRE2(&re);

    EXPECT_FALSE(prefilter->DebugString().empty());

    delete prefilter;

}
