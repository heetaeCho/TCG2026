#include <gtest/gtest.h>

#include "re2/regexp.h"



using namespace re2;



class CharClassBuilderTest_370 : public ::testing::Test {

protected:

    CharClassBuilder* builder;



    void SetUp() override {

        builder = new CharClassBuilder();

    }



    void TearDown() override {

        delete builder;

    }

};



TEST_F(CharClassBuilderTest_370, AddRange_NormalCase_370) {

    EXPECT_TRUE(builder->AddRange('a', 'z'));

    EXPECT_TRUE(builder->AddRange('A', 'Z'));

}



TEST_F(CharClassBuilderTest_370, AddRange_Overlap_370) {

    EXPECT_TRUE(builder->AddRange('a', 'm'));

    EXPECT_TRUE(builder->AddRange('l', 'z'));

}



TEST_F(CharClassBuilderTest_370, AddRange_OutOfOrder_370) {

    EXPECT_FALSE(builder->AddRange('z', 'a'));

}



TEST_F(CharClassBuilderTest_370, AddRange_BoundaryCase_370) {

    EXPECT_TRUE(builder->AddRange(0, 0));

    EXPECT_TRUE(builder->AddRange(Runemax, Runemax));

}



TEST_F(CharClassBuilderTest_370, AddRange_EmptyRange_370) {

    EXPECT_FALSE(builder->AddRange('a', 'a' - 1));

}



TEST_F(CharClassBuilderTest_370, AddRange_LowerToUpperOverlap_370) {

    EXPECT_TRUE(builder->AddRange('z', 'A'));

    EXPECT_EQ(builder->size(), 2);

}
