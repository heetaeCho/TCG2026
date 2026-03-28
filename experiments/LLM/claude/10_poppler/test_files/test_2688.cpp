#include <gtest/gtest.h>
#include <string>
#include <cstdio>

// Forward declarations and definitions to match the code under test

struct AntialiasOption {
    const char *name;
    int value;
};

// Global variables matching those in pdftocairo.cc
static std::string antialias;
static int antialiasEnum = -1;

static const AntialiasOption antialiasOptions[] = {
    { "default", 0 },
    { "none", 1 },
    { "gray", 2 },
    { "subpixel", 3 },
    { "fast", 4 },
    { "good", 5 },
    { "best", 6 },
    { nullptr, 0 }
};

// Function under test
static bool parseAntialiasOption() {
    const AntialiasOption *option = antialiasOptions;
    while (option->name) {
        if (antialias.compare(option->name) == 0) {
            antialiasEnum = option->value;
            return true;
        }
        option++;
    }
    fprintf(stderr, "Error: Invalid antialias option \"%s\"\n", antialias.c_str());
    fprintf(stderr, "Valid options are:\n");
    option = antialiasOptions;
    while (option->name) {
        fprintf(stderr, "  %s\n", option->name);
        option++;
    }
    return false;
}

class ParseAntialiasOptionTest_2688 : public ::testing::Test {
protected:
    void SetUp() override {
        antialias = "";
        antialiasEnum = -1;
    }
};

// Normal operation tests

TEST_F(ParseAntialiasOptionTest_2688, ValidOption_Default_2688) {
    antialias = "default";
    EXPECT_TRUE(parseAntialiasOption());
    EXPECT_EQ(antialiasEnum, 0);
}

TEST_F(ParseAntialiasOptionTest_2688, ValidOption_None_2688) {
    antialias = "none";
    EXPECT_TRUE(parseAntialiasOption());
    EXPECT_EQ(antialiasEnum, 1);
}

TEST_F(ParseAntialiasOptionTest_2688, ValidOption_Gray_2688) {
    antialias = "gray";
    EXPECT_TRUE(parseAntialiasOption());
    EXPECT_EQ(antialiasEnum, 2);
}

TEST_F(ParseAntialiasOptionTest_2688, ValidOption_Subpixel_2688) {
    antialias = "subpixel";
    EXPECT_TRUE(parseAntialiasOption());
    EXPECT_EQ(antialiasEnum, 3);
}

TEST_F(ParseAntialiasOptionTest_2688, ValidOption_Fast_2688) {
    antialias = "fast";
    EXPECT_TRUE(parseAntialiasOption());
    EXPECT_EQ(antialiasEnum, 4);
}

TEST_F(ParseAntialiasOptionTest_2688, ValidOption_Good_2688) {
    antialias = "good";
    EXPECT_TRUE(parseAntialiasOption());
    EXPECT_EQ(antialiasEnum, 5);
}

TEST_F(ParseAntialiasOptionTest_2688, ValidOption_Best_2688) {
    antialias = "best";
    EXPECT_TRUE(parseAntialiasOption());
    EXPECT_EQ(antialiasEnum, 6);
}

// Error / invalid option tests

TEST_F(ParseAntialiasOptionTest_2688, InvalidOption_ReturnsFalse_2688) {
    antialias = "invalid";
    EXPECT_FALSE(parseAntialiasOption());
}

TEST_F(ParseAntialiasOptionTest_2688, InvalidOption_DoesNotChangeAntialiasEnum_2688) {
    antialias = "invalid";
    antialiasEnum = -1;
    parseAntialiasOption();
    EXPECT_EQ(antialiasEnum, -1);
}

TEST_F(ParseAntialiasOptionTest_2688, EmptyString_ReturnsFalse_2688) {
    antialias = "";
    EXPECT_FALSE(parseAntialiasOption());
}

TEST_F(ParseAntialiasOptionTest_2688, EmptyString_DoesNotChangeAntialiasEnum_2688) {
    antialias = "";
    antialiasEnum = -1;
    parseAntialiasOption();
    EXPECT_EQ(antialiasEnum, -1);
}

// Boundary / edge case tests

TEST_F(ParseAntialiasOptionTest_2688, CaseSensitive_UpperCase_2688) {
    antialias = "Default";
    EXPECT_FALSE(parseAntialiasOption());
}

TEST_F(ParseAntialiasOptionTest_2688, CaseSensitive_AllCaps_2688) {
    antialias = "NONE";
    EXPECT_FALSE(parseAntialiasOption());
}

TEST_F(ParseAntialiasOptionTest_2688, TrailingSpace_ReturnsFalse_2688) {
    antialias = "default ";
    EXPECT_FALSE(parseAntialiasOption());
}

TEST_F(ParseAntialiasOptionTest_2688, LeadingSpace_ReturnsFalse_2688) {
    antialias = " default";
    EXPECT_FALSE(parseAntialiasOption());
}

TEST_F(ParseAntialiasOptionTest_2688, SubstringOfValidOption_ReturnsFalse_2688) {
    antialias = "def";
    EXPECT_FALSE(parseAntialiasOption());
}

TEST_F(ParseAntialiasOptionTest_2688, SuperstringOfValidOption_ReturnsFalse_2688) {
    antialias = "defaults";
    EXPECT_FALSE(parseAntialiasOption());
}

TEST_F(ParseAntialiasOptionTest_2688, FirstOptionMatches_SetsCorrectValue_2688) {
    antialias = "default";
    EXPECT_TRUE(parseAntialiasOption());
    EXPECT_EQ(antialiasEnum, 0);
}

TEST_F(ParseAntialiasOptionTest_2688, LastOptionMatches_SetsCorrectValue_2688) {
    antialias = "best";
    EXPECT_TRUE(parseAntialiasOption());
    EXPECT_EQ(antialiasEnum, 6);
}

TEST_F(ParseAntialiasOptionTest_2688, SpecialCharacters_ReturnsFalse_2688) {
    antialias = "!@#$%";
    EXPECT_FALSE(parseAntialiasOption());
}

TEST_F(ParseAntialiasOptionTest_2688, NumericString_ReturnsFalse_2688) {
    antialias = "0";
    EXPECT_FALSE(parseAntialiasOption());
}

TEST_F(ParseAntialiasOptionTest_2688, SequentialCalls_OverwritePreviousValue_2688) {
    antialias = "none";
    EXPECT_TRUE(parseAntialiasOption());
    EXPECT_EQ(antialiasEnum, 1);

    antialias = "best";
    EXPECT_TRUE(parseAntialiasOption());
    EXPECT_EQ(antialiasEnum, 6);
}

TEST_F(ParseAntialiasOptionTest_2688, ValidThenInvalid_RetainsLastValidValue_2688) {
    antialias = "gray";
    EXPECT_TRUE(parseAntialiasOption());
    EXPECT_EQ(antialiasEnum, 2);

    antialias = "invalid";
    EXPECT_FALSE(parseAntialiasOption());
    // antialiasEnum should remain unchanged from the last valid call
    EXPECT_EQ(antialiasEnum, 2);
}
