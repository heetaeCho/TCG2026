#include <gtest/gtest.h>



// Mocking external collaborators if needed (none in this case)

class TextWord {

    // Assume TextWord has some implementation that we don't care about for testing purposes

};



// Assuming TextWordSelection class is already defined as per the known dependencies



class TextWordSelectionTest_1214 : public ::testing::Test {

protected:

    const TextWord* mockWord;

    TextWordSelection selection;



    void SetUp() override {

        mockWord = new TextWord();

        selection = TextWordSelection(mockWord, 0, 5);

    }



    void TearDown() override {

        delete mockWord;

    }

};



TEST_F(TextWordSelectionTest_1214, GetBeginReturnsCorrectValue_1214) {

    EXPECT_EQ(selection.getBegin(), 0);

}



TEST_F(TextWordSelectionTest_1214, GetEndReturnsCorrectValue_1214) {

    EXPECT_EQ(selection.getEnd(), 5);

}



TEST_F(TextWordSelectionTest_1214, BoundaryConditionGetBeginZero_1214) {

    TextWordSelection boundarySelection(mockWord, 0, 10);

    EXPECT_EQ(boundarySelection.getBegin(), 0);

}



TEST_F(TextWordSelectionTest_1214, BoundaryConditionGetEndMaxInt_1214) {

    TextWordSelection boundarySelection(mockWord, 0, std::numeric_limits<int>::max());

    EXPECT_EQ(boundarySelection.getEnd(), std::numeric_limits<int>::max());

}



TEST_F(TextWordSelectionTest_1214, GetWordReturnsCorrectPointer_1214) {

    EXPECT_EQ(selection.getWord(), mockWord);

}
