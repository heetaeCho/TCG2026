#include <gtest/gtest.h>

#include "re2/re2.h"



using namespace re2;



class RE2Test_236 : public ::testing::Test {

protected:

    void SetUp() override {

        // Reset to default before each test

        FUZZING_ONLY_set_maximum_global_replace_count(-1);

    }

};



TEST_F(RE2Test_236, SetGlobalReplaceCount_Default_236) {

    EXPECT_EQ(maximum_global_replace_count, -1);

}



TEST_F(RE2Test_236, SetGlobalReplaceCount_NormalOperation_236) {

    FUZZING_ONLY_set_maximum_global_replace_count(10);

    EXPECT_EQ(maximum_global_replace_count, 10);

}



TEST_F(RE2Test_236, SetGlobalReplaceCount_Zero_236) {

    FUZZING_ONLY_set_maximum_global_replace_count(0);

    EXPECT_EQ(maximum_global_replace_count, 0);

}



TEST_F(RE2Test_236, SetGlobalReplaceCount_Negative_236) {

    FUZZING_ONLY_set_maximum_global_replace_count(-5);

    EXPECT_EQ(maximum_global_replace_count, -5);

}
