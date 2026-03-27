#include <gtest/gtest.h>

#include <cstring>



// Assuming setPSPaperSize is part of a class or namespace, otherwise it can be called directly.

extern bool setPSPaperSize(char *size, int &psPaperWidth, int &psPaperHeight);



TEST(setPSPaperSizeTest_2695, MatchSetsNegativeValues_2695) {

    char size[] = "match";

    int width = 0;

    int height = 0;

    EXPECT_TRUE(setPSPaperSize(size, width, height));

    EXPECT_EQ(width, -1);

    EXPECT_EQ(height, -1);

}



TEST(setPSPaperSizeTest_2695, LetterSetsCorrectValues_2695) {

    char size[] = "letter";

    int width = 0;

    int height = 0;

    EXPECT_TRUE(setPSPaperSize(size, width, height));

    EXPECT_EQ(width, 612);

    EXPECT_EQ(height, 792);

}



TEST(setPSPaperSizeTest_2695, LegalSetsCorrectValues_2695) {

    char size[] = "legal";

    int width = 0;

    int height = 0;

    EXPECT_TRUE(setPSPaperSize(size, width, height));

    EXPECT_EQ(width, 612);

    EXPECT_EQ(height, 1008);

}



TEST(setPSPaperSizeTest_2695, A4SetsCorrectValues_2695) {

    char size[] = "A4";

    int width = 0;

    int height = 0;

    EXPECT_TRUE(setPSPaperSize(size, width, height));

    EXPECT_EQ(width, 595);

    EXPECT_EQ(height, 842);

}



TEST(setPSPaperSizeTest_2695, A3SetsCorrectValues_2695) {

    char size[] = "A3";

    int width = 0;

    int height = 0;

    EXPECT_TRUE(setPSPaperSize(size, width, height));

    EXPECT_EQ(width, 842);

    EXPECT_EQ(height, 1190);

}



TEST(setPSPaperSizeTest_2695, UnknownSizeReturnsFalse_2695) {

    char size[] = "unknown";

    int width = 0;

    int height = 0;

    EXPECT_FALSE(setPSPaperSize(size, width, height));

}



TEST(setPSPaperSizeTest_2695, EmptyStringReturnsFalse_2695) {

    char size[] = "";

    int width = 0;

    int height = 0;

    EXPECT_FALSE(setPSPaperSize(size, width, height));

}



TEST(setPSPaperSizeTest_2695, NullPointerReturnsFalse_2695) {

    int width = 0;

    int height = 0;

    EXPECT_FALSE(setPSPaperSize(nullptr, width, height));

}
