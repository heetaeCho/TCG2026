#include <gtest/gtest.h>

#include "regexp.h"



namespace re2 {



class CharClassBuilderTest_374 : public ::testing::Test {

protected:

    CharClassBuilder* builder;



    void SetUp() override {

        builder = new CharClassBuilder();

    }



    void TearDown() override {

        delete builder;

    }

};



TEST_F(CharClassBuilderTest_374, CopyCreatesIndependentInstance_374) {

    builder->AddRange(1, 5);

    auto copy = builder->Copy();



    // Modify the original and check that the copy is not affected

    builder->AddRange(6, 10);



    EXPECT_EQ(copy->size(), 1);

    delete copy;

}



TEST_F(CharClassBuilderTest_374, CopyPreservesRanges_374) {

    builder->AddRange(1, 5);

    auto copy = builder->Copy();



    // Check that the ranges are copied correctly

    EXPECT_EQ(copy->size(), 1);

    EXPECT_TRUE(copy->Contains(3));

    delete copy;

}



TEST_F(CharClassBuilderTest_374, AddRangeIncreasesSize_374) {

    int initial_size = builder->size();

    builder->AddRange(1, 5);



    EXPECT_EQ(builder->size(), initial_size + 1);

}



TEST_F(CharClassBuilderTest_374, AddRangeBoundaryCondition_374) {

    // Test adding a range that includes the boundary values

    builder->AddRange(std::numeric_limits<Rune>::min(), std::numeric_limits<Rune>::max());



    EXPECT_EQ(builder->size(), 1);

}



TEST_F(CharClassBuilderTest_374, ContainsReturnsFalseForEmpty_374) {

    // Check that Contains returns false for an empty builder

    EXPECT_FALSE(builder->Contains(5));

}



TEST_F(CharClassBuilderTest_374, ContainsReturnsTrueAfterAddingRange_374) {

    builder->AddRange(1, 5);



    EXPECT_TRUE(builder->Contains(3));

}



TEST_F(CharClassBuilderTest_374, ContainsReturnsFalseOutsideRange_374) {

    builder->AddRange(1, 5);



    EXPECT_FALSE(builder->Contains(6));

}



TEST_F(CharClassBuilderTest_374, RemoveAboveReducesSize_374) {

    builder->AddRange(1, 10);

    int initial_size = builder->size();



    builder->RemoveAbove(5);



    EXPECT_LT(builder->size(), initial_size);

}



TEST_F(CharClassBuilderTest_374, RemoveAboveBoundaryCondition_374) {

    builder->AddRange(1, std::numeric_limits<Rune>::max());

    builder->RemoveAbove(std::numeric_limits<Rune>::min());



    // Check that the size is reduced to 1 (the range from min to min)

    EXPECT_EQ(builder->size(), 1);

}



TEST_F(CharClassBuilderTest_374, NegateInvertsContents_374) {

    builder->AddRange(1, 5);

    builder->Negate();



    // After negation, the range should not be contained

    EXPECT_FALSE(builder->Contains(3));

}



TEST_F(CharClassBuilderTest_374, AddCharClassMergesRanges_374) {

    CharClassBuilder other;

    other.AddRange(6, 10);

    builder->AddRange(1, 5);



    builder->AddCharClass(&other);



    EXPECT_EQ(builder->size(), 2);

}



TEST_F(CharClassBuilderTest_374, AddCharClassBoundaryCondition_374) {

    CharClassBuilder other;

    other.AddRange(std::numeric_limits<Rune>::min(), std::numeric_limits<Rune>::max());

    builder->AddRange(1, 5);



    builder->AddCharClass(&other);



    // After adding a full range, the size should be 1

    EXPECT_EQ(builder->size(), 1);

}



}  // namespace re2
