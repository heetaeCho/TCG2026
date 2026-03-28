#include <gtest/gtest.h>

#include "prefilter.h"



using namespace re2;



class PrefilterTest_459 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup if needed

    }



    void TearDown() override {

        // Teardown if needed

    }

};



TEST_F(PrefilterTest_459, Constructor_SetsOp_459) {

    Op testOp = kOpLiteral;

    Prefilter prefilter(testOp);

    EXPECT_EQ(prefilter.op(), testOp);

}



TEST_F(PrefilterTest_459, DebugString_ReturnsValidString_459) {

    Prefilter prefilter(kOpLiteral);

    std::string debugStr = prefilter.DebugString();

    EXPECT_FALSE(debugStr.empty());

}



TEST_F(PrefilterTest_459, SetUniqueIdAndGetUniqueId_CorrectlySetsAndReturnsId_459) {

    Prefilter prefilter(kOpLiteral);

    int testId = 123;

    prefilter.set_unique_id(testId);

    EXPECT_EQ(prefilter.unique_id(), testId);

}



TEST_F(PrefilterTest_459, SetSubsAndGetSubs_CorrectlySetsAndReturnsSubs_459) {

    Prefilter prefilter(kOpLiteral);

    std::vector<Prefilter*> subs;

    subs.push_back(new Prefilter(kOpLiteral));

    prefilter.set_subs(&subs);

    EXPECT_EQ(prefilter.subs(), &subs);

}



TEST_F(PrefilterTest_459, Atom_ReturnsEmptyStringByDefault_459) {

    Prefilter prefilter(kOpLiteral);

    EXPECT_TRUE(prefilter.atom().empty());

}
