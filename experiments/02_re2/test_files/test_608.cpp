#include <gtest/gtest.h>

#include "prefilter.h"

#include "re2/re2.h"



using namespace re2;



TEST(PrefilterTest_608, ConstructorWithOpAll_608) {

    Prefilter prefilter(Op::ALL);

    EXPECT_EQ(prefilter.op(), Op::ALL);

}



TEST(PrefilterTest_608, ConstructorWithOpNone_608) {

    Prefilter prefilter(Op::NONE);

    EXPECT_EQ(prefilter.op(), Op::NONE);

}



TEST(PrefilterTest_608, ConstructorWithOpAtom_608) {

    Prefilter prefilter(Op::ATOM);

    EXPECT_EQ(prefilter.op(), Op::ATOM);

}



TEST(PrefilterTest_608, ConstructorWithOpAnd_608) {

    Prefilter prefilter(Op::AND);

    EXPECT_EQ(prefilter.op(), Op::AND);

    EXPECT_NE(prefilter.subs(), nullptr);

}



TEST(PrefilterTest_608, ConstructorWithOpOr_608) {

    Prefilter prefilter(Op::OR);

    EXPECT_EQ(prefilter.op(), Op::OR);

    EXPECT_NE(prefilter.subs(), nullptr);

}



TEST(PrefilterTest_608, SetAndGetUniqueId_608) {

    Prefilter prefilter(Op::ALL);

    int unique_id = 42;

    prefilter.set_unique_id(unique_id);

    EXPECT_EQ(prefilter.unique_id(), unique_id);

}



TEST(PrefilterTest_608, SubsInitializationForOpAnd_608) {

    Prefilter prefilter(Op::AND);

    EXPECT_NE(prefilter.subs(), nullptr);

}



TEST(PrefilterTest_608, SubsInitializationForOpOr_608) {

    Prefilter prefilter(Op::OR);

    EXPECT_NE(prefilter.subs(), nullptr);

}



TEST(PrefilterTest_608, SubsNotInitializedForOtherOps_608) {

    Prefilter prefilter(Op::ALL);

    EXPECT_EQ(prefilter.subs(), nullptr);



    Prefilter prefilter2(Op::NONE);

    EXPECT_EQ(prefilter2.subs(), nullptr);



    Prefilter prefilter3(Op::ATOM);

    EXPECT_EQ(prefilter3.subs(), nullptr);

}



TEST(PrefilterTest_608, DebugStringNotCrashingForAllOps_608) {

    Prefilter prefilter_all(Op::ALL);

    EXPECT_NO_THROW(prefilter_all.DebugString());



    Prefilter prefilter_none(Op::NONE);

    EXPECT_NO_THROW(prefilter_none.DebugString());



    Prefilter prefilter_atom(Op::ATOM);

    EXPECT_NO_THROW(prefilter_atom.DebugString());



    Prefilter prefilter_and(Op::AND);

    EXPECT_NO_THROW(prefilter_and.DebugString());



    Prefilter prefilter_or(Op::OR);

    EXPECT_NO_THROW(prefilter_or.DebugString());

}



TEST(PrefilterTest_608, FromRE2WithNullPointer_608) {

    const RE2* re2 = nullptr;

    EXPECT_EQ(Prefilter::FromRE2(re2), nullptr);

}
