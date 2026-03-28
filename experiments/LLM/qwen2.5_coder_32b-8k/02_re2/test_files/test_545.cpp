#include <gtest/gtest.h>

#include "re2/prefilter.h"



using namespace re2;



class PrefilterInfoTest_545 : public ::testing::Test {

protected:

    Info* info1;

    Info* info2;



    void SetUp() override {

        info1 = new Info();

        info2 = new Info();

    }



    void TearDown() override {

        delete info1;

        delete info2;

    }

};



TEST_F(PrefilterInfoTest_545, AndWithNullA_545) {

    Info* result = Info::And(nullptr, info2);

    EXPECT_EQ(result, info2);

}



TEST_F(PrefilterInfoTest_545, AndWithNullB_545) {

    Info* result = Info::And(info1, nullptr);

    EXPECT_EQ(result, info1);

}



TEST_F(PrefilterInfoTest_545, AndWithNonNullAandB_545) {

    Info* result = Info::And(info1, info2);

    EXPECT_NE(result, info1);

    EXPECT_NE(result, info2);

    EXPECT_FALSE(result->is_exact());

    delete result;

}



TEST_F(PrefilterInfoTest_545, AndWithSameObject_545) {

    Info* result = Info::And(info1, info1);

    EXPECT_NE(result, info1);

    EXPECT_FALSE(result->is_exact());

    delete result;

}
