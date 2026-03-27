#include <gtest/gtest.h>

#include "TextOutputDev.h"



// Test fixture for TextWord

class TextWordTest_1198 : public ::testing::Test {

protected:

    GfxState state;

    TextWord word;



    TextWordTest_1198() : word(&state, 0, 12.0) {}

};



// Normal operation: Test len() function after adding characters

TEST_F(TextWordTest_1198, LenAfterAddingChar_1198) {

    TextFontInfo font;

    double x = 0.0, y = 0.0, dx = 1.0, dy = 0.0;

    int charPos = 0, charLen = 2;

    CharCode c = 'A';

    Unicode u = 'A';

    Matrix textMat;



    word.addChar(&font, x, y, dx, dy, charPos, charLen, c, u, textMat);

    EXPECT_EQ(word.len(), 1);

}



// Normal operation: Test len() function after merging another TextWord

TEST_F(TextWordTest_1198, LenAfterMerging_1198) {

    GfxState state2;

    TextWord word2(&state2, 0, 12.0);



    TextFontInfo font;

    double x = 0.0, y = 0.0, dx = 1.0, dy = 0.0;

    int charPos = 0, charLen = 2;

    CharCode c = 'A';

    Unicode u = 'A';

    Matrix textMat;



    word.addChar(&font, x, y, dx, dy, charPos, charLen, c, u, textMat);

    word2.addChar(&font, x+1.0, y, dx, dy, charPos+1, charLen, c, u, textMat);



    word.merge(&word2);

    EXPECT_EQ(word.len(), 2);

}



// Boundary condition: Test len() function with no characters added

TEST_F(TextWordTest_1198, LenWithNoChars_1198) {

    EXPECT_EQ(word.len(), 0);

}



// Exceptional case: Test len() function after adding combining character

TEST_F(TextWordTest_1198, LenAfterAddingCombiningChar_1198) {

    TextFontInfo font;

    double fontSize = 12.0, x = 0.0, y = 0.0, dx = 1.0, dy = 0.0;

    int charPos = 0, charLen = 2;

    CharCode c = '\u0301'; // Combining acute accent

    Unicode u = '\u0301';

    Matrix textMat;



    word.addChar(&font, x, y, dx, dy, charPos, charLen, 'A', 'A', textMat);

    bool result = word.addCombining(&font, fontSize, x, y, dx, dy, charPos+1, charLen, c, u, textMat);

    EXPECT_TRUE(result);

    EXPECT_EQ(word.len(), 1); // Length should still be 1 as combining characters are part of the same character

}
