#include <gtest/gtest.h>

#include "prefilter.h"



using namespace re2;



class PrefilterInfoTest_556 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup if necessary

    }



    void TearDown() override {

        // Teardown if necessary

    }

};



TEST_F(PrefilterInfoTest_556, AnyMatch_ReturnsNewInfoObject_556) {

    Prefilter::Info* info = Prefilter::Info::AnyMatch();

    EXPECT_NE(info, nullptr);

    delete info;  // Clean up the allocated object

}



TEST_F(PrefilterInfoTest_556, TakeMatch_ReturnsMatchPointer_556) {

    Prefilter::Info* info = new Prefilter::Info();

    Prefilter* match = new Prefilter(Prefilter::Op::ALL);

    info->match_ = match;

    EXPECT_EQ(info->TakeMatch(), match);

    delete info;  // Clean up the allocated object

}



TEST_F(PrefilterInfoTest_556, TakeMatch_ReturnsNullWhenNoMatch_556) {

    Prefilter::Info* info = new Prefilter::Info();

    EXPECT_EQ(info->TakeMatch(), nullptr);

    delete info;  // Clean up the allocated object

}



TEST_F(PrefilterInfoTest_556, AnyMatch_MatchIsAllOp_556) {

    Prefilter::Info* info = Prefilter::Info::AnyMatch();

    Prefilter* match = info->TakeMatch();

    EXPECT_NE(match, nullptr);

    if (match != nullptr) {

        EXPECT_EQ(match->op(), Prefilter::Op::ALL);

        delete match;  // Clean up the allocated object

    }

    delete info;  // Clean up the allocated object

}



TEST_F(PrefilterInfoTest_556, DefaultConstructor_SetsIsExactToFalse_556) {

    Prefilter::Info* info = new Prefilter::Info();

    EXPECT_FALSE(info->is_exact());

    delete info;  // Clean up the allocated object

}



TEST_F(PrefilterInfoTest_556, DefaultConstructor_MatchIsNull_556) {

    Prefilter::Info* info = new Prefilter::Info();

    EXPECT_EQ(info->TakeMatch(), nullptr);

    delete info;  // Clean up the allocated object

}
