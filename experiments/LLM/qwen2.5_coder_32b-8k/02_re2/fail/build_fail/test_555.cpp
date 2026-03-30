#include <gtest/gtest.h>

#include "prefilter.h"



using namespace re2;



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



TEST_F(PrefilterInfoTest_555, NoMatch_ReturnsNonNullPointer_555) {

    Prefilter::Info* noMatchInfo = Prefilter::Info::NoMatch();

    EXPECT_NE(noMatchInfo, nullptr);

    delete noMatchInfo;

}



TEST_F(PrefilterInfoTest_555, TakeMatch_ReturnsNullInitially_555) {

    EXPECT_EQ(info->TakeMatch(), nullptr);

}



TEST_F(PrefilterInfoTest_555, Alt_CombinesTwoInfos_555) {

    Prefilter::Info* info1 = new Prefilter::Info();

    Prefilter::Info* info2 = new Prefilter::Info();

    Prefilter::Info* combinedInfo = Prefilter::Info::Alt(info1, info2);

    EXPECT_NE(combinedInfo, nullptr);

    delete info1;

    delete info2;

    delete combinedInfo;

}



TEST_F(PrefilterInfoTest_555, Concat_CombinesTwoInfos_555) {

    Prefilter::Info* info1 = new Prefilter::Info();

    Prefilter::Info* info2 = new Prefilter::Info();

    Prefilter::Info* combinedInfo = Prefilter::Info::Concat(info1, info2);

    EXPECT_NE(combinedInfo, nullptr);

    delete info1;

    delete info2;

    delete combinedInfo;

}



TEST_F(PrefilterInfoTest_555, And_CombinesTwoInfos_555) {

    Prefilter::Info* info1 = new Prefilter::Info();

    Prefilter::Info* info2 = new Prefilter::Info();

    Prefilter::Info* combinedInfo = Prefilter::Info::And(info1, info2);

    EXPECT_NE(combinedInfo, nullptr);

    delete info1;

    delete info2;

    delete combinedInfo;

}



TEST_F(PrefilterInfoTest_555, Star_ReturnsNonNullPointer_555) {

    Prefilter::Info* starInfo = Prefilter::Info::Star(info);

    EXPECT_NE(starInfo, nullptr);

    delete starInfo;

}



TEST_F(PrefilterInfoTest_555, Plus_ReturnsNonNullPointer_555) {

    Prefilter::Info* plusInfo = Prefilter::Info::Plus(info);

    EXPECT_NE(plusInfo, nullptr);

    delete plusInfo;

}



TEST_F(PrefilterInfoTest_555, Quest_ReturnsNonNullPointer_555) {

    Prefilter::Info* questInfo = Prefilter::Info::Quest(info);

    EXPECT_NE(questInfo, nullptr);

    delete questInfo;

}



TEST_F(PrefilterInfoTest_555, EmptyString_ReturnsNonNullPointer_555) {

    Prefilter::Info* emptyStringInfo = Prefilter::Info::EmptyString();

    EXPECT_NE(emptyStringInfo, nullptr);

    delete emptyStringInfo;

}



TEST_F(PrefilterInfoTest_555, AnyCharOrAnyByte_ReturnsNonNullPointer_555) {

    Prefilter::Info* anyCharInfo = Prefilter::Info::AnyCharOrAnyByte();

    EXPECT_NE(anyCharInfo, nullptr);

    delete anyCharInfo;

}



TEST_F(PrefilterInfoTest_555, Literal_ReturnsNonNullPointer_555) {

    Rune r = 'a';

    Prefilter::Info* literalInfo = Prefilter::Info::Literal(r);

    EXPECT_NE(literalInfo, nullptr);

    delete literalInfo;

}



TEST_F(PrefilterInfoTest_555, LiteralLatin1_ReturnsNonNullPointer_555) {

    Rune r = 'b';

    Prefilter::Info* literalLatin1Info = Prefilter::Info::LiteralLatin1(r);

    EXPECT_NE(literalLatin1Info, nullptr);

    delete literalLatin1Info;

}



TEST_F(PrefilterInfoTest_555, AnyMatch_ReturnsNonNullPointer_555) {

    Prefilter::Info* anyMatchInfo = Prefilter::Info::AnyMatch();

    EXPECT_NE(anyMatchInfo, nullptr);

    delete anyMatchInfo;

}
