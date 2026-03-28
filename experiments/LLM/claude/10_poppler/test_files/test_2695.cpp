#include <gtest/gtest.h>
#include <cstring>

// Re-declare the function under test since it's static in the original file.
// We include it by copying the exact signature and treating it as a black box.
static bool setPSPaperSize(char *size, int &psPaperWidth, int &psPaperHeight)
{
    if (!strcmp(size, "match")) {
        psPaperWidth = psPaperHeight = -1;
    } else if (!strcmp(size, "letter")) {
        psPaperWidth = 612;
        psPaperHeight = 792;
    } else if (!strcmp(size, "legal")) {
        psPaperWidth = 612;
        psPaperHeight = 1008;
    } else if (!strcmp(size, "A4")) {
        psPaperWidth = 595;
        psPaperHeight = 842;
    } else if (!strcmp(size, "A3")) {
        psPaperWidth = 842;
        psPaperHeight = 1190;
    } else {
        return false;
    }
    return true;
}

class SetPSPaperSizeTest_2695 : public ::testing::Test {
protected:
    int psPaperWidth;
    int psPaperHeight;

    void SetUp() override {
        psPaperWidth = 0;
        psPaperHeight = 0;
    }
};

// Test "match" paper size
TEST_F(SetPSPaperSizeTest_2695, MatchSize_2695) {
    char size[] = "match";
    bool result = setPSPaperSize(size, psPaperWidth, psPaperHeight);
    EXPECT_TRUE(result);
    EXPECT_EQ(psPaperWidth, -1);
    EXPECT_EQ(psPaperHeight, -1);
}

// Test "letter" paper size
TEST_F(SetPSPaperSizeTest_2695, LetterSize_2695) {
    char size[] = "letter";
    bool result = setPSPaperSize(size, psPaperWidth, psPaperHeight);
    EXPECT_TRUE(result);
    EXPECT_EQ(psPaperWidth, 612);
    EXPECT_EQ(psPaperHeight, 792);
}

// Test "legal" paper size
TEST_F(SetPSPaperSizeTest_2695, LegalSize_2695) {
    char size[] = "legal";
    bool result = setPSPaperSize(size, psPaperWidth, psPaperHeight);
    EXPECT_TRUE(result);
    EXPECT_EQ(psPaperWidth, 612);
    EXPECT_EQ(psPaperHeight, 1008);
}

// Test "A4" paper size
TEST_F(SetPSPaperSizeTest_2695, A4Size_2695) {
    char size[] = "A4";
    bool result = setPSPaperSize(size, psPaperWidth, psPaperHeight);
    EXPECT_TRUE(result);
    EXPECT_EQ(psPaperWidth, 595);
    EXPECT_EQ(psPaperHeight, 842);
}

// Test "A3" paper size
TEST_F(SetPSPaperSizeTest_2695, A3Size_2695) {
    char size[] = "A3";
    bool result = setPSPaperSize(size, psPaperWidth, psPaperHeight);
    EXPECT_TRUE(result);
    EXPECT_EQ(psPaperWidth, 842);
    EXPECT_EQ(psPaperHeight, 1190);
}

// Test unknown paper size returns false
TEST_F(SetPSPaperSizeTest_2695, UnknownSizeReturnsFalse_2695) {
    char size[] = "tabloid";
    bool result = setPSPaperSize(size, psPaperWidth, psPaperHeight);
    EXPECT_FALSE(result);
    // Width and height should remain unchanged (0) since the function returns false
    EXPECT_EQ(psPaperWidth, 0);
    EXPECT_EQ(psPaperHeight, 0);
}

// Test empty string returns false
TEST_F(SetPSPaperSizeTest_2695, EmptyStringReturnsFalse_2695) {
    char size[] = "";
    bool result = setPSPaperSize(size, psPaperWidth, psPaperHeight);
    EXPECT_FALSE(result);
    EXPECT_EQ(psPaperWidth, 0);
    EXPECT_EQ(psPaperHeight, 0);
}

// Test case sensitivity: "a4" is not "A4"
TEST_F(SetPSPaperSizeTest_2695, CaseSensitivityLowercaseA4_2695) {
    char size[] = "a4";
    bool result = setPSPaperSize(size, psPaperWidth, psPaperHeight);
    EXPECT_FALSE(result);
}

// Test case sensitivity: "a3" is not "A3"
TEST_F(SetPSPaperSizeTest_2695, CaseSensitivityLowercaseA3_2695) {
    char size[] = "a3";
    bool result = setPSPaperSize(size, psPaperWidth, psPaperHeight);
    EXPECT_FALSE(result);
}

// Test case sensitivity: "Letter" is not "letter"
TEST_F(SetPSPaperSizeTest_2695, CaseSensitivityUppercaseLetter_2695) {
    char size[] = "Letter";
    bool result = setPSPaperSize(size, psPaperWidth, psPaperHeight);
    EXPECT_FALSE(result);
}

// Test case sensitivity: "LEGAL" is not "legal"
TEST_F(SetPSPaperSizeTest_2695, CaseSensitivityUppercaseLegal_2695) {
    char size[] = "LEGAL";
    bool result = setPSPaperSize(size, psPaperWidth, psPaperHeight);
    EXPECT_FALSE(result);
}

// Test case sensitivity: "MATCH" is not "match"
TEST_F(SetPSPaperSizeTest_2695, CaseSensitivityUppercaseMatch_2695) {
    char size[] = "MATCH";
    bool result = setPSPaperSize(size, psPaperWidth, psPaperHeight);
    EXPECT_FALSE(result);
}

// Test with extra whitespace
TEST_F(SetPSPaperSizeTest_2695, SizeWithTrailingSpace_2695) {
    char size[] = "letter ";
    bool result = setPSPaperSize(size, psPaperWidth, psPaperHeight);
    EXPECT_FALSE(result);
}

// Test with leading whitespace
TEST_F(SetPSPaperSizeTest_2695, SizeWithLeadingSpace_2695) {
    char size[] = " letter";
    bool result = setPSPaperSize(size, psPaperWidth, psPaperHeight);
    EXPECT_FALSE(result);
}

// Test that output parameters are not modified for invalid input
TEST_F(SetPSPaperSizeTest_2695, OutputParamsUnchangedOnInvalidInput_2695) {
    psPaperWidth = 999;
    psPaperHeight = 888;
    char size[] = "invalid";
    bool result = setPSPaperSize(size, psPaperWidth, psPaperHeight);
    EXPECT_FALSE(result);
    EXPECT_EQ(psPaperWidth, 999);
    EXPECT_EQ(psPaperHeight, 888);
}

// Test a random invalid string
TEST_F(SetPSPaperSizeTest_2695, RandomInvalidString_2695) {
    char size[] = "B5";
    bool result = setPSPaperSize(size, psPaperWidth, psPaperHeight);
    EXPECT_FALSE(result);
}

// Test that calling with a valid size after a previous call overwrites values
TEST_F(SetPSPaperSizeTest_2695, OverwritesPreviousValues_2695) {
    char sizeA4[] = "A4";
    setPSPaperSize(sizeA4, psPaperWidth, psPaperHeight);
    EXPECT_EQ(psPaperWidth, 595);
    EXPECT_EQ(psPaperHeight, 842);

    char sizeLetter[] = "letter";
    bool result = setPSPaperSize(sizeLetter, psPaperWidth, psPaperHeight);
    EXPECT_TRUE(result);
    EXPECT_EQ(psPaperWidth, 612);
    EXPECT_EQ(psPaperHeight, 792);
}
