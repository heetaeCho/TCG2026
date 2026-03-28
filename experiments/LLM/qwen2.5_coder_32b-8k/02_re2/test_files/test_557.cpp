#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "prefilter.cc"



using namespace re2;



class PrefilterInfoTest_557 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code, if needed.

    }



    void TearDown() override {

        // Teardown code, if needed.

    }

};



TEST_F(PrefilterInfoTest_557, EmptyString_IsExact_557) {

    Prefilter::Info* info = Prefilter::Info::EmptyString();

    EXPECT_TRUE(info->is_exact());

    delete info;

}



TEST_F(PrefilterInfoTest_557, EmptyString_ContainsEmptyString_557) {

    Prefilter::Info* info = Prefilter::Info::EmptyString();

    EXPECT_EQ(1, info->exact().size());

    EXPECT_TRUE(info->exact().find("") != info->exact().end());

    delete info;

}



TEST_F(PrefilterInfoTest_557, DefaultConstructor_IsNotExact_557) {

    Prefilter::Info* info = new Prefilter::Info();

    EXPECT_FALSE(info->is_exact());

    delete info;

}



TEST_F(PrefilterInfoTest_557, NoMatch_ReturnsNonNullPointer_557) {

    Prefilter::Info* info = Prefilter::Info::NoMatch();

    EXPECT_NE(nullptr, info);

    delete info;

}



TEST_F(PrefilterInfoTest_557, AnyCharOrAnyByte_ReturnsNonNullPointer_557) {

    Prefilter::Info* info = Prefilter::Info::AnyCharOrAnyByte();

    EXPECT_NE(nullptr, info);

    delete info;

}



TEST_F(PrefilterInfoTest_557, AnyMatch_ReturnsNonNullPointer_557) {

    Prefilter::Info* info = Prefilter::Info::AnyMatch();

    EXPECT_NE(nullptr, info);

    delete info;

}
