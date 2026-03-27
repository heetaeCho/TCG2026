#include <gtest/gtest.h>

#include "TextOutputDev.h"



// Test fixture for TextWord tests.

class TextWordTest_1188 : public ::testing::Test {

protected:

    GfxState state;

    const int rotation = 90; // Example rotation value

    const double fontSize = 12.0; // Example font size



    std::unique_ptr<TextWord> textWord;



    void SetUp() override {

        textWord = std::make_unique<TextWord>(&state, rotation, fontSize);

    }

};



// Test normal operation of getRotation.

TEST_F(TextWordTest_1188, GetRotation_ReturnsCorrectValue_1188) {

    EXPECT_EQ(textWord->getRotation(), rotation);

}



// Test boundary condition with zero rotation.

TEST_F(TextWordTest_1188, GetRotation_ZeroRotation_ReturnsZero_1188) {

    TextWord zeroRotTextWord(&state, 0, fontSize);

    EXPECT_EQ(zeroRotTextWord.getRotation(), 0);

}



// Test boundary condition with negative rotation.

TEST_F(TextWordTest_1188, GetRotation_NegativeRotation_ReturnsCorrectValue_1188) {

    const int negRotation = -90;

    TextWord negRotTextWord(&state, negRotation, fontSize);

    EXPECT_EQ(negRotTextWord.getRotation(), negRotation);

}



// Test boundary condition with positive rotation.

TEST_F(TextWordTest_1188, GetRotation_PositiveRotation_ReturnsCorrectValue_1188) {

    const int posRotation = 180;

    TextWord posRotTextWord(&state, posRotation, fontSize);

    EXPECT_EQ(posRotTextWord.getRotation(), posRotation);

}



// Test exceptional or error case with invalid rotation (if applicable).

// Since rotation is an integer and there's no explicit validation, this test may not be strictly necessary.

// However, if there were any known invalid values, they could be tested here.



// Test external interactions by mocking collaborators (none in this class).



// Additional tests for other public methods can be added as needed.
