#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "regexp.h"



using namespace re2;



class CharClassBuilderTest_164 : public ::testing::Test {

protected:

    CharClassBuilder *builder;



    void SetUp() override {

        builder = new CharClassBuilder();

    }



    void TearDown() override {

        delete builder;

    }

};



TEST_F(CharClassBuilderTest_164, AddRange_SingleCharacter_164) {

    EXPECT_TRUE(builder->AddRange('a', 'a'));

}



TEST_F(CharClassBuilderTest_164, AddRange_CharacterRange_164) {

    EXPECT_TRUE(builder->AddRange('a', 'z'));

}



TEST_F(CharClassBuilderTest_164, AddRange_EmptyRange_164) {

    EXPECT_FALSE(builder->AddRange('b', 'a'));

}



TEST_F(CharClassBuilderTest_164, Contains_CharacterInRange_164) {

    builder->AddRange('a', 'z');

    EXPECT_TRUE(builder->Contains('m'));

}



TEST_F(CharClassBuilderTest_164, Contains_CharacterOutsideRange_164) {

    builder->AddRange('a', 'z');

    EXPECT_FALSE(builder->Contains('A'));

}



TEST_F(CharClassBuilderTest_164, FoldsASCII_DefaultBehavior_164) {

    EXPECT_FALSE(builder->FoldsASCII());

}



TEST_F(CharClassBuilderTest_164, Negate_EmptySet_164) {

    builder->Negate();

    EXPECT_TRUE(builder->full());

}



TEST_F(CharClassBuilderTest_164, Negate_NonEmptySet_164) {

    builder->AddRange('a', 'z');

    builder->Negate();

    EXPECT_FALSE(builder->Contains('m'));

    EXPECT_TRUE(builder->Contains('A'));

}



TEST_F(CharClassBuilderTest_164, RemoveAbove_CharacterInRange_164) {

    builder->AddRange('a', 'z');

    builder->RemoveAbove('m');

    EXPECT_TRUE(builder->Contains('l'));

    EXPECT_FALSE(builder->Contains('n'));

}



TEST_F(CharClassBuilderTest_164, RemoveAbove_AllCharacters_164) {

    builder->AddRange('a', 'z');

    builder->RemoveAbove('z');

    EXPECT_FALSE(builder->Contains('m'));

}



TEST_F(CharClassBuilderTest_164, AddCharClass_MergeRanges_164) {

    CharClassBuilder other;

    other.AddRange('a', 'm');

    builder->AddRange('n', 'z');

    builder->AddCharClass(&other);

    EXPECT_TRUE(builder->Contains('l'));

    EXPECT_TRUE(builder->Contains('q'));

}



TEST_F(CharClassBuilderTest_164, GetCharClass_NotNull_164) {

    CharClass* charClass = builder->GetCharClass();

    EXPECT_NE(charClass, nullptr);

}



TEST_F(CharClassBuilderTest_164, Size_EmptySet_164) {

    EXPECT_EQ(builder->size(), 0);

}



TEST_F(CharClassBuilderTest_164, Size_NonEmptySet_164) {

    builder->AddRange('a', 'z');

    EXPECT_GT(builder->size(), 0);

}



TEST_F(CharClassBuilderTest_164, Empty_EmptySet_164) {

    EXPECT_TRUE(builder->empty());

}



TEST_F(CharClassBuilderTest_164, Empty_NonEmptySet_164) {

    builder->AddRange('a', 'z');

    EXPECT_FALSE(builder->empty());

}



TEST_F(CharClassBuilderTest_164, Full_EmptySet_164) {

    EXPECT_FALSE(builder->full());

}



TEST_F(CharClassBuilderTest_164, Full_NegatedSet_164) {

    builder->Negate();

    EXPECT_TRUE(builder->full());

}
