#include <gtest/gtest.h>

#include "TextOutputDev.h"



class TextWordSelectionTest : public ::testing::Test {

protected:

    const TextWord *dummyWord = nullptr;

    TextWordSelection selection;



    void SetUp() override {

        dummyWord = new TextWord(); // Assuming a default constructor for TextWord exists

        selection = TextWordSelection(dummyWord, 10, 20);

    }



    void TearDown() override {

        delete dummyWord;

    }

};



TEST_F(TextWordSelectionTest_1215, GetEndReturnsCorrectValue_1215) {

    EXPECT_EQ(selection.getEnd(), 20);

}



TEST_F(TextWordSelectionTest_1215, GetBeginReturnsCorrectValue_1215) {

    EXPECT_EQ(selection.getBegin(), 10);

}



TEST_F(TextWordSelectionTest_1215, GetWordReturnsSamePointer_1215) {

    EXPECT_EQ(selection.getWord(), dummyWord);

}



TEST_F(TextWordSelectionTest_1215, BoundaryConditionZeroLength_1215) {

    TextWordSelection zeroLengthSelection(dummyWord, 10, 10);

    EXPECT_EQ(zeroLengthSelection.getEnd(), 10);

    EXPECT_EQ(zeroLengthSelection.getBegin(), 10);

}



TEST_F(TextWordSelectionTest_1215, BoundaryConditionNegativeValues_1215) {

    TextWordSelection negativeSelection(dummyWord, -5, -1);

    EXPECT_EQ(negativeSelection.getEnd(), -1);

    EXPECT_EQ(negativeSelection.getBegin(), -5);

}
