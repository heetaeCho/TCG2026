#include <gtest/gtest.h>

#include "regexp.h"



namespace re2 {



class CharClassBuilderTest_380 : public ::testing::Test {

protected:

    CharClassBuilder builder;

};



TEST_F(CharClassBuilderTest_380, GetCharClass_ReturnsValidCharClass_380) {

    CharClass* charClass = builder.GetCharClass();

    EXPECT_NE(charClass, nullptr);

    charClass->Delete();

}



TEST_F(CharClassBuilderTest_380, AddRange_IncreasesSize_380) {

    int initialSize = builder.size();

    builder.AddRange(1, 2);

    EXPECT_EQ(builder.size(), initialSize + 1);

}



TEST_F(CharClassBuilderTest_380, AddRange_OutOfOrderRangesHandledCorrectly_380) {

    builder.AddRange(5, 6);

    builder.AddRange(1, 2);

    builder.AddRange(3, 4);

    EXPECT_EQ(builder.size(), 3);

}



TEST_F(CharClassBuilderTest_380, GetCharClass_RangesCopiedCorrectly_380) {

    builder.AddRange(1, 2);

    builder.AddRange(3, 4);



    CharClass* charClass = builder.GetCharClass();

    EXPECT_EQ(charClass->size(), builder.size());



    auto it = charClass->begin();

    EXPECT_EQ((*it).lo, 1);

    EXPECT_EQ((*it).hi, 2);

    ++it;

    EXPECT_EQ((*it).lo, 3);

    EXPECT_EQ((*it).hi, 4);



    charClass->Delete();

}



TEST_F(CharClassBuilderTest_380, FoldsASCII_ReturnsFalseByDefault_380) {

    EXPECT_FALSE(builder.FoldsASCII());

}



TEST_F(CharClassBuilderTest_380, GetCharClass_FoldsASCIIInherited_380) {

    builder.AddRange(1, 2);

    builder.AddRange(3, 4);



    CharClass* charClass = builder.GetCharClass();

    EXPECT_EQ(charClass->FoldsASCII(), builder.FoldsASCII());



    charClass->Delete();

}



TEST_F(CharClassBuilderTest_380, AddRangeFlags_IgnoredInThisContext_380) {

    int initialSize = builder.size();

    builder.AddRangeFlags(1, 2, Regexp::ParseFlags());

    EXPECT_EQ(builder.size(), initialSize + 1);

}



TEST_F(CharClassBuilderTest_380, RemoveAbove_RemovesRangesAboveThreshold_380) {

    builder.AddRange(1, 5);

    builder.AddRange(6, 10);



    builder.RemoveAbove(5);

    EXPECT_EQ(builder.size(), 1);



    auto it = builder.begin();

    EXPECT_EQ((*it).lo, 1);

    EXPECT_EQ((*it).hi, 5);

}



TEST_F(CharClassBuilderTest_380, Negate_InvertsRange_380) {

    builder.AddRange(1, 2);

    builder.AddRange(4, 5);



    CharClass* charClass = builder.GetCharClass();

    builder.Negate();



    CharClass* negatedCharClass = builder.GetCharClass();

    EXPECT_NE(negatedCharClass->size(), charClass->size());



    charClass->Delete();

    negatedCharClass->Delete();

}



TEST_F(CharClassBuilderTest_380, Copy_ReturnsIndependentCopy_380) {

    builder.AddRange(1, 2);

    CharClassBuilder* copy = builder.Copy();



    EXPECT_EQ(copy->size(), builder.size());

    copy->AddRange(3, 4);

    EXPECT_NE(copy->size(), builder.size());



    delete copy;

}



TEST_F(CharClassBuilderTest_380, AddCharClass_MergesRanges_380) {

    CharClassBuilder otherBuilder;

    otherBuilder.AddRange(3, 4);



    builder.AddRange(1, 2);

    builder.AddCharClass(&otherBuilder);



    EXPECT_EQ(builder.size(), 2);



    auto it = builder.begin();

    EXPECT_EQ((*it).lo, 1);

    EXPECT_EQ((*it).hi, 2);

    ++it;

    EXPECT_EQ((*it).lo, 3);

    EXPECT_EQ((*it).hi, 4);

}



TEST_F(CharClassBuilderTest_380, AddCharClass_EmptyBuilderHandledCorrectly_380) {

    CharClassBuilder otherBuilder;



    builder.AddRange(1, 2);

    int initialSize = builder.size();

    builder.AddCharClass(&otherBuilder);



    EXPECT_EQ(builder.size(), initialSize);

}



}  // namespace re2
