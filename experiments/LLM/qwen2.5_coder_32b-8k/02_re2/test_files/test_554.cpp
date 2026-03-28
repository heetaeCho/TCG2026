#include <gtest/gtest.h>

#include "prefilter.cc"



using namespace re2;



class PrefilterInfoTest_554 : public ::testing::Test {

protected:

    void SetUp() override {}

    void TearDown() override {}



    Prefilter::Info* CreateInfoObject() {

        return new Prefilter::Info();

    }

};



TEST_F(PrefilterInfoTest_554, AnyCharOrAnyByte_ReturnsValidPointer_554) {

    Prefilter::Info* info = Prefilter::Info::AnyCharOrAnyByte();

    ASSERT_NE(info, nullptr);

    delete info;

}



TEST_F(PrefilterInfoTest_554, TakeMatch_ReturnsNullByDefault_554) {

    Prefilter::Info* info = CreateInfoObject();

    ASSERT_EQ(info->TakeMatch(), nullptr);

    delete info;

}



TEST_F(PrefilterInfoTest_554, IsExact_DefaultValueIsFalse_554) {

    Prefilter::Info* info = CreateInfoObject();

    EXPECT_FALSE(info->is_exact());

    delete info;

}



TEST_F(PrefilterInfoTest_554, AnyCharOrAnyByte_MatchIsAll_554) {

    Prefilter::Info* info = Prefilter::Info::AnyCharOrAnyByte();

    ASSERT_NE(info->TakeMatch(), nullptr);

    EXPECT_EQ(info->TakeMatch()->match_, static_cast<Prefilter*>(nullptr));

    delete info;

}



TEST_F(PrefilterInfoTest_554, ToString_ReturnsEmptyStringByDefault_554) {

    Prefilter::Info* info = CreateInfoObject();

    EXPECT_EQ(info->ToString(), "");

    delete info;

}
