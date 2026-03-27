#include <gtest/gtest.h>

#include "re2/prefilter.h"



using namespace re2;



class PrefilterInfoTest_540 : public ::testing::Test {

protected:

    void SetUp() override {

        info = new Prefilter::Info();

    }



    void TearDown() override {

        delete info;

    }



    Prefilter::Info* info;

};



TEST_F(PrefilterInfoTest_540, IsExact_DefaultConstructor_540) {

    EXPECT_FALSE(info->is_exact());

}



TEST_F(PrefilterInfoTest_540, TakeMatch_ReturnsNullptr_540) {

    EXPECT_EQ(info->TakeMatch(), nullptr);

}



TEST_F(PrefilterInfoTest_540, ToString_EmptyString_540) {

    EXPECT_EQ(info->ToString(), "");

}



TEST_F(PrefilterInfoTest_540, StaticMethods_ReturnNonNullPtr_540) {

    EXPECT_NE(Prefilter::Info::Alt(nullptr, nullptr), nullptr);

    EXPECT_NE(Prefilter::Info::Concat(nullptr, nullptr), nullptr);

    EXPECT_NE(Prefilter::Info::And(nullptr, nullptr), nullptr);

    EXPECT_NE(Prefilter::Info::Star(nullptr), nullptr);

    EXPECT_NE(Prefilter::Info::Plus(nullptr), nullptr);

    EXPECT_NE(Prefilter::Info::Quest(nullptr), nullptr);

    EXPECT_NE(Prefilter::Info::EmptyString(), nullptr);

    EXPECT_NE(Prefilter::Info::NoMatch(), nullptr);

    EXPECT_NE(Prefilter::Info::AnyCharOrAnyByte(), nullptr);

    EXPECT_NE(Prefilter::Info::Literal(0), nullptr);

    EXPECT_NE(Prefilter::Info::LiteralLatin1(0), nullptr);

    EXPECT_NE(Prefilter::Info::CClass(nullptr, false), nullptr);

}



TEST_F(PrefilterInfoTest_540, StaticMethods_MultipleCalls_ReturnDifferentInstances_540) {

    EXPECT_NE(Prefilter::Info::EmptyString(), Prefilter::Info::NoMatch());

}
