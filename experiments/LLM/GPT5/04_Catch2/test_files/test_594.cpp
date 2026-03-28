// replace_in_place_tests_594.cpp
#include <gtest/gtest.h>
#include <string>

// Forward declaration of the function under test.
// (We only rely on the public signature & observable behavior.)
namespace Catch {
    bool replaceInPlace(std::string& str,
                        std::string const& replaceThis,
                        std::string const& withThis);
}

// ---------- Normal operation ----------

TEST(ReplaceInPlaceTest_594, ReturnsFalseWhenNoMatch_594) {
    std::string s = "hello world";
    const std::string original = s;

    bool changed = Catch::replaceInPlace(s, "xyz", "123");

    EXPECT_FALSE(changed);
    EXPECT_EQ(s, original); // unchanged
}

TEST(ReplaceInPlaceTest_594, ReplacesSingleOccurrenceInMiddle_594) {
    std::string s = "hello world";
    bool changed = Catch::replaceInPlace(s, "lo w", "–");
    EXPECT_TRUE(changed);
    EXPECT_EQ(s, "hel–orld");
}

TEST(ReplaceInPlaceTest_594, ReplacesAllOccurrencesNonOverlapping_594) {
    std::string s = "one one one";
    bool changed = Catch::replaceInPlace(s, "one", "1");
    EXPECT_TRUE(changed);
    EXPECT_EQ(s, "1 1 1");
}

TEST(ReplaceInPlaceTest_594, ReplacesAtStartAndEnd_594) {
    std::string s = "abXab";
    bool changed = Catch::replaceInPlace(s, "ab", "ZZ");
    EXPECT_TRUE(changed);
    EXPECT_EQ(s, "ZZXZZ");
}

// ---------- Boundary conditions ----------

TEST(ReplaceInPlaceTest_594, EntireStringReplaced_594) {
    std::string s = "aaa";
    bool changed = Catch::replaceInPlace(s, "aaa", "b");
    EXPECT_TRUE(changed);
    EXPECT_EQ(s, "b");
}

TEST(ReplaceInPlaceTest_594, MultipleAdjacentOccurrences_594) {
    std::string s = "xxxx";
    bool changed = Catch::replaceInPlace(s, "xx", "y");
    EXPECT_TRUE(changed);
    EXPECT_EQ(s, "yy");  // two adjacent "xx" -> "y" + "y"
}

TEST(ReplaceInPlaceTest_594, ReplacementCanBeEmpty_DeletesMatches_594) {
    std::string s = "banana";
    bool changed = Catch::replaceInPlace(s, "na", "");
    EXPECT_TRUE(changed);
    EXPECT_EQ(s, "ba");
}

TEST(ReplaceInPlaceTest_594, WithThisSameAsReplaceThis_StillReportsChange_594) {
    std::string s = "repeat repeat";
    const std::string original = s;
    bool changed = Catch::replaceInPlace(s, "repeat", "repeat");
    EXPECT_TRUE(changed);       // at least one match was found
    EXPECT_EQ(s, original);     // content remains textually identical
}

// ---------- Additional observable scenarios ----------

TEST(ReplaceInPlaceTest_594, ReplacementLongerThanMatch_594) {
    std::string s = "cat";
    bool changed = Catch::replaceInPlace(s, "a", "alphabet");
    EXPECT_TRUE(changed);
    EXPECT_EQ(s, "calphabett");
}

TEST(ReplaceInPlaceTest_594, WorksWithUTF8ByteSequences_594) {
    // Treats std::string as a byte container; should replace matching byte sequences.
    std::string s = u8"안녕하세요";
    bool changed = Catch::replaceInPlace(s, u8"안녕", "hi");
    EXPECT_TRUE(changed);
    EXPECT_EQ(s, u8"hi하세요");
}
