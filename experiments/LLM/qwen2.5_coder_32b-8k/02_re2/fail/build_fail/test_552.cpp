#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "re2/prefilter.cc"



using namespace re2;



class PrefilterInfoTest : public ::testing::Test {

protected:

    void SetUp() override {}

    void TearDown() override {}

};



TEST_F(PrefilterInfoTest_552, LiteralCreatesExactInfo_552) {

    Rune r = 'a';

    Info* info = Info::Literal(r);

    EXPECT_TRUE(info->is_exact());

    EXPECT_EQ(*info->exact().begin(), "a");

    delete info;

}



TEST_F(PrefilterInfoTest_552, LiteralHandlesUppercaseRune_552) {

    Rune r = 'A';

    Info* info = Info::Literal(r);

    EXPECT_TRUE(info->is_exact());

    EXPECT_EQ(*info->exact().begin(), "a");

    delete info;

}



TEST_F(PrefilterInfoTest_552, LiteralCreatesNewInstanceEachCall_552) {

    Rune r = 'b';

    Info* info1 = Info::Literal(r);

    Info* info2 = Info::Literal(r);

    EXPECT_NE(info1, info2);

    delete info1;

    delete info2;

}



TEST_F(PrefilterInfoTest_552, LiteralDoesNotModifyMatchPointer_552) {

    Rune r = 'c';

    Info* info = Info::Literal(r);

    EXPECT_EQ(info->TakeMatch(), nullptr);

    delete info;

}
