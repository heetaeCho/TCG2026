#include <gtest/gtest.h>

#include "TextOutputDev.h"



class TextWordSelectionTest_1213 : public ::testing::Test {

protected:

    const TextWord* mockWord;

    TextWordSelection selection;



    void SetUp() override {

        mockWord = reinterpret_cast<const TextWord*>(0x1); // Mock pointer

        selection = TextWordSelection(mockWord, 0, 5);

    }

};



TEST_F(TextWordSelectionTest_1213, GetWordReturnsCorrectPointer_1213) {

    EXPECT_EQ(selection.getWord(), mockWord);

}



TEST_F(TextWordSelectionTest_1213, BoundaryConditionBeginZero_1213) {

    TextWordSelection boundarySelection(mockWord, 0, 5);

    EXPECT_EQ(boundarySelection.getBegin(), 0);

}



TEST_F(TextWordSelectionTest_1213, BoundaryConditionEndNonZero_1213) {

    TextWordSelection boundarySelection(mockWord, 0, 5);

    EXPECT_EQ(boundarySelection.getEnd(), 5);

}



TEST_F(TextWordSelectionTest_1213, NormalOperationGetBegin_1213) {

    EXPECT_EQ(selection.getBegin(), 0);

}



TEST_F(TextWordSelectionTest_1213, NormalOperationGetEnd_1213) {

    EXPECT_EQ(selection.getEnd(), 5);

}
