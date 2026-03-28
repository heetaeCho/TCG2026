#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/poppler/poppler/XRef.h"



using namespace testing;



class XRefEntryTest_256 : public Test {

protected:

    XRefEntry entry;

};



TEST_F(XRefEntryTest_256, SetFlagTrueAndGetFlagReturnsTrue_256) {

    entry.setFlag(Flag::Used, true);

    EXPECT_TRUE(entry.getFlag(Flag::Used));

}



TEST_F(XRefEntryTest_256, SetFlagFalseAndGetFlagReturnsFalse_256) {

    entry.setFlag(Flag::Used, false);

    EXPECT_FALSE(entry.getFlag(Flag::Used));

}



TEST_F(XRefEntryTest_256, SetMultipleFlagsAndCheckIndividualFlags_256) {

    entry.setFlag(Flag::Used, true);

    entry.setFlag(Flag::Referenced, true);

    entry.setFlag(Flag::Compressed, false);



    EXPECT_TRUE(entry.getFlag(Flag::Used));

    EXPECT_TRUE(entry.getFlag(Flag::Referenced));

    EXPECT_FALSE(entry.getFlag(Flag::Compressed));

}



TEST_F(XRefEntryTest_256, SetSameFlagMultipleTimesAndGetFlagReturnsCorrectValue_256) {

    entry.setFlag(Flag::Used, true);

    entry.setFlag(Flag::Used, false);



    EXPECT_FALSE(entry.getFlag(Flag::Used));



    entry.setFlag(Flag::Referenced, false);

    entry.setFlag(Flag::Referenced, true);



    EXPECT_TRUE(entry.getFlag(Flag::Referenced));

}



TEST_F(XRefEntryTest_256, SetFlagToTrueAndThenBackToFalseAndGetFlagReturnsFalse_256) {

    entry.setFlag(Flag::Used, true);

    entry.setFlag(Flag::Used, false);



    EXPECT_FALSE(entry.getFlag(Flag::Used));

}
