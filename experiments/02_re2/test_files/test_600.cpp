#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "regexp.h"



namespace re2 {



class CharClassBuilderTest : public ::testing::Test {

protected:

    CharClassBuilder* builder;



    void SetUp() override {

        builder = new CharClassBuilder();

    }



    void TearDown() override {

        delete builder;

    }

};



TEST_F(CharClassBuilderTest_600, AddRange_NormalOperation_600) {

    EXPECT_TRUE(builder->AddRange(10, 20));

}



TEST_F(CharClassBuilderTest_600, AddRange_BoundaryCondition_EmptyRange_600) {

    EXPECT_FALSE(builder->AddRange(10, 9));

}



TEST_F(CharClassBuilderTest_600, Contains_NormalOperation_600) {

    builder->AddRange(10, 20);

    EXPECT_TRUE(builder->Contains(15));

    EXPECT_FALSE(builder->Contains(25));

}



TEST_F(CharClassBuilderTest_600, FoldsASCII_NormalOperation_600) {

    EXPECT_FALSE(builder->FoldsASCII());

}



TEST_F(CharClassBuilderTest_600, AddCharClass_NormalOperation_600) {

    CharClassBuilder* anotherBuilder = new CharClassBuilder();

    anotherBuilder->AddRange(30, 40);

    builder->AddCharClass(anotherBuilder);

    delete anotherBuilder;

    EXPECT_TRUE(builder->Contains(35));

}



TEST_F(CharClassBuilderTest_600, Negate_NormalOperation_600) {

    builder->AddRange(10, 20);

    builder->Negate();

    EXPECT_FALSE(builder->Contains(15));

    EXPECT_TRUE(builder->Contains(9));

}



TEST_F(CharClassBuilderTest_600, RemoveAbove_NormalOperation_600) {

    builder->AddRange(10, 30);

    builder->RemoveAbove(20);

    EXPECT_TRUE(builder->Contains(15));

    EXPECT_FALSE(builder->Contains(25));

}



TEST_F(CharClassBuilderTest_600, GetCharClass_NormalOperation_600) {

    builder->AddRange(10, 20);

    CharClass* charClass = builder->GetCharClass();

    EXPECT_NE(charClass, nullptr);

    delete charClass;

}



TEST_F(CharClassBuilderTest_600, AddRangeFlags_NormalOperation_600) {

    builder->AddRangeFlags(10, 20, Regexp::ParseFlags());

}



TEST_F(CharClassBuilderTest_600, Iterator_Test_600) {

    builder->AddRange(10, 20);

    builder->AddRange(30, 40);

    int count = 0;

    for (CharClassBuilder::iterator it = builder->begin(); it != builder->end(); ++it) {

        count++;

    }

    EXPECT_EQ(count, 2);

}



TEST_F(CharClassBuilderTest_600, Size_Test_600) {

    builder->AddRange(10, 20);

    builder->AddRange(30, 40);

    EXPECT_EQ(builder->size(), 2);

}



TEST_F(CharClassBuilderTest_600, Empty_Test_Empty_600) {

    EXPECT_TRUE(builder->empty());

}



TEST_F(CharClassBuilderTest_600, Empty_Test_NotEmpty_600) {

    builder->AddRange(10, 20);

    EXPECT_FALSE(builder->empty());

}



TEST_F(CharClassBuilderTest_600, Full_Test_Empty_600) {

    EXPECT_FALSE(builder->full());

}



} // namespace re2
