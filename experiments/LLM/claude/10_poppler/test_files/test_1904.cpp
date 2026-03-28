#include <gtest/gtest.h>

// Unicode type as used in poppler
typedef unsigned int Unicode;

// Forward declaration of the struct
struct CombiningTable {
    Unicode base;
    Unicode comb;
};

// The combiningTable as provided
static const CombiningTable combiningTable[12] = {
    {96, 768}, {168, 776}, {175, 772}, {180, 769}, {184, 807},
    {710, 770}, {711, 780}, {728, 774}, {729, 775}, {730, 778},
    {732, 771}, {733, 779}
};

// Re-declare the function under test (static function from the source file)
static Unicode getCombiningChar(Unicode u) {
    for (const CombiningTable &combining : combiningTable) {
        if (u == combining.base) {
            return combining.comb;
        }
    }
    return 0;
}

class GetCombiningCharTest_1904 : public ::testing::Test {};

// Test that the first entry (base=96) returns correct combining char 768
TEST_F(GetCombiningCharTest_1904, FirstEntry_Base96_ReturnsComb768_1904) {
    EXPECT_EQ(768u, getCombiningChar(96));
}

// Test that the second entry (base=168) returns correct combining char 776
TEST_F(GetCombiningCharTest_1904, SecondEntry_Base168_ReturnsComb776_1904) {
    EXPECT_EQ(776u, getCombiningChar(168));
}

// Test that the third entry (base=175) returns correct combining char 772
TEST_F(GetCombiningCharTest_1904, ThirdEntry_Base175_ReturnsComb772_1904) {
    EXPECT_EQ(772u, getCombiningChar(175));
}

// Test that the fourth entry (base=180) returns correct combining char 769
TEST_F(GetCombiningCharTest_1904, FourthEntry_Base180_ReturnsComb769_1904) {
    EXPECT_EQ(769u, getCombiningChar(180));
}

// Test that the fifth entry (base=184) returns correct combining char 807
TEST_F(GetCombiningCharTest_1904, FifthEntry_Base184_ReturnsComb807_1904) {
    EXPECT_EQ(807u, getCombiningChar(184));
}

// Test that the sixth entry (base=710) returns correct combining char 770
TEST_F(GetCombiningCharTest_1904, SixthEntry_Base710_ReturnsComb770_1904) {
    EXPECT_EQ(770u, getCombiningChar(710));
}

// Test that the seventh entry (base=711) returns correct combining char 780
TEST_F(GetCombiningCharTest_1904, SeventhEntry_Base711_ReturnsComb780_1904) {
    EXPECT_EQ(780u, getCombiningChar(711));
}

// Test that the eighth entry (base=728) returns correct combining char 774
TEST_F(GetCombiningCharTest_1904, EighthEntry_Base728_ReturnsComb774_1904) {
    EXPECT_EQ(774u, getCombiningChar(728));
}

// Test that the ninth entry (base=729) returns correct combining char 775
TEST_F(GetCombiningCharTest_1904, NinthEntry_Base729_ReturnsComb775_1904) {
    EXPECT_EQ(775u, getCombiningChar(729));
}

// Test that the tenth entry (base=730) returns correct combining char 778
TEST_F(GetCombiningCharTest_1904, TenthEntry_Base730_ReturnsComb778_1904) {
    EXPECT_EQ(778u, getCombiningChar(730));
}

// Test that the eleventh entry (base=732) returns correct combining char 771
TEST_F(GetCombiningCharTest_1904, EleventhEntry_Base732_ReturnsComb771_1904) {
    EXPECT_EQ(771u, getCombiningChar(732));
}

// Test that the last entry (base=733) returns correct combining char 779
TEST_F(GetCombiningCharTest_1904, LastEntry_Base733_ReturnsComb779_1904) {
    EXPECT_EQ(779u, getCombiningChar(733));
}

// Test that a value not in the table returns 0
TEST_F(GetCombiningCharTest_1904, NotInTable_Returns0_1904) {
    EXPECT_EQ(0u, getCombiningChar(0));
}

// Test with value 1 (not in table)
TEST_F(GetCombiningCharTest_1904, ValueOne_NotInTable_Returns0_1904) {
    EXPECT_EQ(0u, getCombiningChar(1));
}

// Test with a large value not in the table
TEST_F(GetCombiningCharTest_1904, LargeValue_NotInTable_Returns0_1904) {
    EXPECT_EQ(0u, getCombiningChar(100000));
}

// Test with value just below first base (95)
TEST_F(GetCombiningCharTest_1904, JustBelowFirstBase_Returns0_1904) {
    EXPECT_EQ(0u, getCombiningChar(95));
}

// Test with value just above first base (97)
TEST_F(GetCombiningCharTest_1904, JustAboveFirstBase_Returns0_1904) {
    EXPECT_EQ(0u, getCombiningChar(97));
}

// Test with value just below last base (732 is in table, 731 is not)
TEST_F(GetCombiningCharTest_1904, JustBelowSecondToLastBase_Returns0_1904) {
    EXPECT_EQ(0u, getCombiningChar(731));
}

// Test with value just above last base (734)
TEST_F(GetCombiningCharTest_1904, JustAboveLastBase_Returns0_1904) {
    EXPECT_EQ(0u, getCombiningChar(734));
}

// Test with maximum Unicode value
TEST_F(GetCombiningCharTest_1904, MaxUnicodeValue_Returns0_1904) {
    EXPECT_EQ(0u, getCombiningChar(0xFFFFFFFF));
}

// Test that a combining value itself (768) is not treated as a base
TEST_F(GetCombiningCharTest_1904, CombValueAsInput_Returns0_1904) {
    EXPECT_EQ(0u, getCombiningChar(768));
}

// Test with value between entries in the table (e.g., 169, between 168 and 175)
TEST_F(GetCombiningCharTest_1904, BetweenEntries_Returns0_1904) {
    EXPECT_EQ(0u, getCombiningChar(169));
}

// Test with value 500 (not in table, between ranges)
TEST_F(GetCombiningCharTest_1904, MidRangeNotInTable_Returns0_1904) {
    EXPECT_EQ(0u, getCombiningChar(500));
}
