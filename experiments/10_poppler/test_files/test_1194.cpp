#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/TextOutputDev.h"



class TextWordTest_1194 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup for each test case

        state = new GfxState();

        fontInfo = new TextFontInfo();

        textWord = new TextWord(state, 0, 12.0);

    }



    void TearDown() override {

        // Cleanup after each test case

        delete textWord;

        delete fontInfo;

        delete state;

    }



    GfxState* state;

    TextFontInfo* fontInfo;

    TextWord* textWord;

};



TEST_F(TextWordTest_1194, GetEdge_ValidIndex_1194) {

    // Add a character to the TextWord

    double x = 10.0, y = 20.0, dx = 5.0, dy = 0.0;

    int charPosA = 0, charLen = 1;

    CharCode c = 'A';

    Unicode u = L'A';

    Matrix textMatA;



    textWord->addChar(fontInfo, x, y, dx, dy, charPosA, charLen, c, u, textMatA);



    // Verify getEdge for a valid index

    EXPECT_DOUBLE_EQ(textWord->getEdge(0), 15.0); // Edge is calculated as x + dx

}



TEST_F(TextWordTest_1194, GetEdge_OutOfBoundsIndex_1194) {

    // Test behavior when index is out of bounds

    EXPECT_THROW(textWord->getEdge(0), std::out_of_range);

}



TEST_F(TextWordTest_1194, AddChar_NormalOperation_1194) {

    double x = 10.0, y = 20.0, dx = 5.0, dy = 0.0;

    int charPosA = 0, charLen = 1;

    CharCode c = 'A';

    Unicode u = L'A';

    Matrix textMatA;



    textWord->addChar(fontInfo, x, y, dx, dy, charPosA, charLen, c, u, textMatA);



    EXPECT_EQ(textWord->getLength(), 1);

}



TEST_F(TextWordTest_1194, AddCombining_NormalOperation_1194) {

    double fontSize = 12.0;

    double x = 10.0, y = 20.0, dx = 5.0, dy = 0.0;

    int charPosA = 0, charLen = 1;

    CharCode c = 'A';

    Unicode u = L'A';

    Matrix textMatA;



    bool result = textWord->addCombining(fontInfo, fontSize, x, y, dx, dy, charPosA, charLen, c, u, textMatA);



    EXPECT_TRUE(result); // Assuming addCombining always returns true for valid input

}



TEST_F(TextWordTest_1194, GetFontInfo_NormalOperation_1194) {

    double x = 10.0, y = 20.0, dx = 5.0, dy = 0.0;

    int charPosA = 0, charLen = 1;

    CharCode c = 'A';

    Unicode u = L'A';

    Matrix textMatA;



    textWord->addChar(fontInfo, x, y, dx, dy, charPosA, charLen, c, u, textMatA);



    const TextFontInfo* fontInfoResult = textWord->getFontInfo(0);

    EXPECT_EQ(fontInfoResult, fontInfo);

}



TEST_F(TextWordTest_1194, GetNext_NormalOperation_1194) {

    // Assuming no next word by default

    const TextWord* nextWord = textWord->getNext();

    EXPECT_EQ(nextWord, nullptr);

}



TEST_F(TextWordTest_1194, GetLength_EmptyTextWord_1194) {

    EXPECT_EQ(textWord->getLength(), 0);

}
