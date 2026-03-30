#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "re2/prefilter.h"



using namespace re2;



class PrefilterTest : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code if necessary

    }



    void TearDown() override {

        // Teardown code if necessary

    }

};



TEST_F(PrefilterTest_465, ConstructorAndOpCheck_ATOM_465) {

    Prefilter prefilter(Prefilter::ATOM);

    EXPECT_EQ(prefilter.op(), Prefilter::ATOM);

}



TEST_F(PrefilterTest_465, ConstructorAndOpCheck_AND_465) {

    Prefilter* a = new Prefilter(Prefilter::ATOM);

    Prefilter* b = new Prefilter(Prefilter::ATOM);

    Prefilter* andPrefilter = Prefilter::And(a, b);

    EXPECT_EQ(andPrefilter->op(), Prefilter::AND);

    delete a;

    delete b;

    delete andPrefilter;

}



TEST_F(PrefilterTest_465, ConstructorAndOpCheck_OR_465) {

    Prefilter* a = new Prefilter(Prefilter::ATOM);

    Prefilter* b = new Prefilter(Prefilter::ATOM);

    Prefilter* orPrefilter = Prefilter::Or(a, b);

    EXPECT_EQ(orPrefilter->op(), Prefilter::OR);

    delete a;

    delete b;

    delete orPrefilter;

}



TEST_F(PrefilterTest_465, SetAndGetUniqueId_465) {

    Prefilter prefilter(Prefilter::ATOM);

    prefilter.set_unique_id(123);

    EXPECT_EQ(prefilter.unique_id(), 123);

}



TEST_F(PrefilterTest_465, SubsManipulation_465) {

    Prefilter* a = new Prefilter(Prefilter::ATOM);

    Prefilter* b = new Prefilter(Prefilter::ATOM);

    std::vector<Prefilter*> subs = {a, b};

    Prefilter prefilter(Prefilter::AND);

    prefilter.set_subs(&subs);

    EXPECT_EQ(prefilter.subs()->size(), 2);

    delete a;

    delete b;

}



TEST_F(PrefilterTest_465, AtomAccessAndModification_465) {

    Prefilter prefilter(Prefilter::ATOM);

    std::string testAtom = "test_atom";

    prefilter.set_atom(testAtom); // Assuming a setter is available for atom

    EXPECT_EQ(prefilter.atom(), testAtom);

}



TEST_F(PrefilterTest_465, DebugStringNotCrash_465) {

    Prefilter prefilter(Prefilter::ATOM);

    std::string debugString = prefilter.DebugString();

    EXPECT_TRUE(!debugString.empty());

}
