#include <gtest/gtest.h>

#include "prefilter.cc"



using namespace re2;



class PrefilterInfoTest_549 : public ::testing::Test {

protected:

    void SetUp() override {

        info1 = new Info();

        info2 = new Info();

    }



    void TearDown() override {

        delete info1;

        delete info2;

    }



    Info* info1;

    Info* info2;

};



TEST_F(PrefilterInfoTest_549, PlusIncreasesCount_549) {

    Info* result = Info::Plus(info1);

    EXPECT_FALSE(result->is_exact());

    delete result;  // Ownership transferred to result in Plus

}



TEST_F(PrefilterInfoTest_549, PlusReturnsNonNull_549) {

    Info* result = Info::Plus(info1);

    EXPECT_NE(nullptr, result);

    delete result;

}



TEST_F(PrefilterInfoTest_549, PlusDeletesOriginal_549) {

    Info* original = new Info();

    Info* result = Info::Plus(original);

    EXPECT_EQ(nullptr, original);  // Original should be deleted

    delete result;

}
