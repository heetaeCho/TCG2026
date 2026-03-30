#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/re2/re2/regexp.h"



using namespace re2;



class CharClassBuilderTest_163 : public ::testing::Test {

protected:

    void SetUp() override {

        char_class_builder = new CharClassBuilder();

    }



    void TearDown() override {

        delete char_class_builder;

    }



    CharClassBuilder* char_class_builder;

};



TEST_F(CharClassBuilderTest_163, AddRangeNormalOperation_163) {

    EXPECT_TRUE(char_class_builder->AddRange(0x0041, 0x005A));

    EXPECT_EQ(char_class_builder->size(), 1);

}



TEST_F(CharClassBuilderTest_163, AddRangeBoundaryConditions_163) {

    EXPECT_TRUE(char_class_builder->AddRange(0x0000, 0xFFFF));

    EXPECT_EQ(char_class_builder->size(), 1);

}



TEST_F(CharClassBuilderTest_163, AddRangeOverlap_163) {

    char_class_builder->AddRange(0x0041, 0x005A);

    char_class_builder->AddRange(0x0050, 0x0069);

    EXPECT_EQ(char_class_builder->size(), 1); // Overlapping ranges should merge

}



TEST_F(CharClassBuilderTest_163, AddRangeInvalidRange_163) {

    EXPECT_FALSE(char_class_builder->AddRange(0x005A, 0x0041)); // Invalid range

    EXPECT_EQ(char_class_builder->size(), 0);

}



TEST_F(CharClassBuilderTest_163, ContainsNormalOperation_163) {

    char_class_builder->AddRange(0x0041, 0x005A); // A-Z

    EXPECT_TRUE(char_class_builder->Contains(0x0041));

    EXPECT_FALSE(char_class_builder->Contains(0x0061)); // a

}



TEST_F(CharClassBuilderTest_163, ContainsEmptySet_163) {

    EXPECT_FALSE(char_class_builder->Contains(0x0041));

}



TEST_F(CharClassBuilderTest_163, NegateNormalOperation_163) {

    char_class_builder->AddRange(0x0041, 0x005A); // A-Z

    char_class_builder->Negate();

    EXPECT_FALSE(char_class_builder->Contains(0x0041));

    EXPECT_TRUE(char_class_builder->Contains(0x0061)); // a

}



TEST_F(CharClassBuilderTest_163, RemoveAboveNormalOperation_163) {

    char_class_builder->AddRange(0x0041, 0x007A); // A-Za-z

    char_class_builder->RemoveAbove(0x005A);

    EXPECT_TRUE(char_class_builder->Contains(0x0041));

    EXPECT_FALSE(char_class_builder->Contains(0x0061)); // a

}



TEST_F(CharClassBuilderTest_163, RemoveAboveFullSet_163) {

    char_class_builder->AddRange(0x0000, 0xFFFF);

    char_class_builder->RemoveAbove(0x005A);

    EXPECT_TRUE(char_class_builder->Contains(0x0041));

    EXPECT_FALSE(char_class_builder->Contains(0x0061)); // a

}



TEST_F(CharClassBuilderTest_163, FullSetCheck_163) {

    char_class_builder->AddRange(0x0000, 0xFFFF);

    EXPECT_TRUE(char_class_builder->full());

}



TEST_F(CharClassBuilderTest_163, EmptySetCheck_163) {

    EXPECT_TRUE(char_class_builder->empty());

}
