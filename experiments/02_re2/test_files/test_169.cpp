#include <gtest/gtest.h>

#include "re2/regexp.h"



using namespace re2;



class RegexpParseFlagsTest_169 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup if needed

    }



    void TearDown() override {

        // Teardown if needed

    }

};



TEST_F(RegexpParseFlagsTest_169, ParseFlagsXorWithSelfIsZero_169) {

    Regexp::ParseFlags flag = static_cast<Regexp::ParseFlags>(42); // Arbitrary flag value

    EXPECT_EQ(flag ^ flag, static_cast<Regexp::ParseFlags>(0));

}



TEST_F(RegexpParseFlagsTest_169, ParseFlagsXorWithZeroIsIdentity_169) {

    Regexp::ParseFlags flag = static_cast<Regexp::ParseFlags>(42); // Arbitrary flag value

    EXPECT_EQ(flag ^ static_cast<Regexp::ParseFlags>(0), flag);

}



TEST_F(RegexpParseFlagsTest_169, ParseFlagsXorCommutativeProperty_169) {

    Regexp::ParseFlags flag1 = static_cast<Regexp::ParseFlags>(42); // Arbitrary flag value

    Regexp::ParseFlags flag2 = static_cast<Regexp::ParseFlags>(24); // Another arbitrary flag value

    EXPECT_EQ(flag1 ^ flag2, flag2 ^ flag1);

}



TEST_F(RegexpParseFlagsTest_169, ParseFlagsXorAssociativeProperty_169) {

    Regexp::ParseFlags flag1 = static_cast<Regexp::ParseFlags>(42); // Arbitrary flag value

    Regexp::ParseFlags flag2 = static_cast<Regexp::ParseFlags>(24); // Another arbitrary flag value

    Regexp::ParseFlags flag3 = static_cast<Regexp::ParseFlags>(15); // Yet another arbitrary flag value

    EXPECT_EQ((flag1 ^ flag2) ^ flag3, flag1 ^ (flag2 ^ flag3));

}
