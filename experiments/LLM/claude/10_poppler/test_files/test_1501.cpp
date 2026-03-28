#include <gtest/gtest.h>
#include <string>
#include "NameToCharCode.h"

// Tests for the string_hasher nested struct
class NameToCharCodeStringHasherTest_1501 : public ::testing::Test {
protected:
    NameToCharCode::string_hasher hasher;
};

TEST_F(NameToCharCodeStringHasherTest_1501, HashStdStringProducesConsistentResult_1501) {
    std::string txt = "hello";
    size_t hash1 = hasher(txt);
    size_t hash2 = hasher(txt);
    EXPECT_EQ(hash1, hash2);
}

TEST_F(NameToCharCodeStringHasherTest_1501, HashStdStringDifferentStringsProduceDifferentHashes_1501) {
    std::string txt1 = "hello";
    std::string txt2 = "world";
    size_t hash1 = hasher(txt1);
    size_t hash2 = hasher(txt2);
    // Different strings should generally produce different hashes (not guaranteed but highly likely)
    EXPECT_NE(hash1, hash2);
}

TEST_F(NameToCharCodeStringHasherTest_1501, HashStdStringEmptyString_1501) {
    std::string txt = "";
    size_t hash = hasher(txt);
    // Just verify it doesn't crash and produces a value
    (void)hash;
    SUCCEED();
}

TEST_F(NameToCharCodeStringHasherTest_1501, HashStdStringSameContentSameHash_1501) {
    std::string txt1 = "test_string";
    std::string txt2 = "test_string";
    EXPECT_EQ(hasher(txt1), hasher(txt2));
}

TEST_F(NameToCharCodeStringHasherTest_1501, HashCStringProducesConsistentResult_1501) {
    const char *txt = "hello";
    size_t hash1 = hasher(txt);
    size_t hash2 = hasher(txt);
    EXPECT_EQ(hash1, hash2);
}

TEST_F(NameToCharCodeStringHasherTest_1501, HashCStringDifferentStringsProduceDifferentHashes_1501) {
    const char *txt1 = "hello";
    const char *txt2 = "world";
    size_t hash1 = hasher(txt1);
    size_t hash2 = hasher(txt2);
    EXPECT_NE(hash1, hash2);
}

TEST_F(NameToCharCodeStringHasherTest_1501, HashCStringEmptyString_1501) {
    const char *txt = "";
    size_t hash = hasher(txt);
    (void)hash;
    SUCCEED();
}

TEST_F(NameToCharCodeStringHasherTest_1501, HashCStringSameContentSameHash_1501) {
    const char *txt1 = "test_string";
    const char *txt2 = "test_string";
    EXPECT_EQ(hasher(txt1), hasher(txt2));
}

TEST_F(NameToCharCodeStringHasherTest_1501, HashCStringAndStdStringWithSameContentMatch_1501) {
    const char *cstr = "matching";
    std::string stdstr = "matching";
    // Both overloads should produce the same hash for the same content
    EXPECT_EQ(hasher(cstr), hasher(stdstr));
}

TEST_F(NameToCharCodeStringHasherTest_1501, HashLongString_1501) {
    std::string longStr(10000, 'a');
    size_t hash1 = hasher(longStr);
    size_t hash2 = hasher(longStr);
    EXPECT_EQ(hash1, hash2);
}

TEST_F(NameToCharCodeStringHasherTest_1501, HashSingleCharacterStrings_1501) {
    std::string a = "a";
    std::string b = "b";
    EXPECT_NE(hasher(a), hasher(b));
}

// Tests for NameToCharCode class itself
class NameToCharCodeTest_1501 : public ::testing::Test {
protected:
    NameToCharCode ntcc;
};

TEST_F(NameToCharCodeTest_1501, LookupNonExistentNameReturnsZero_1501) {
    // Looking up a name that was never added
    CharCode result = ntcc.lookup("nonexistent");
    EXPECT_EQ(result, 0u);
}

TEST_F(NameToCharCodeTest_1501, AddAndLookup_1501) {
    ntcc.add("space", 0x20);
    CharCode result = ntcc.lookup("space");
    EXPECT_EQ(result, 0x20u);
}

TEST_F(NameToCharCodeTest_1501, AddMultipleAndLookup_1501) {
    ntcc.add("A", 65);
    ntcc.add("B", 66);
    ntcc.add("C", 67);
    EXPECT_EQ(ntcc.lookup("A"), 65u);
    EXPECT_EQ(ntcc.lookup("B"), 66u);
    EXPECT_EQ(ntcc.lookup("C"), 67u);
}

TEST_F(NameToCharCodeTest_1501, LookupAfterAddDoesNotAffectOtherEntries_1501) {
    ntcc.add("first", 1);
    ntcc.add("second", 2);
    EXPECT_EQ(ntcc.lookup("first"), 1u);
    EXPECT_EQ(ntcc.lookup("second"), 2u);
    EXPECT_EQ(ntcc.lookup("third"), 0u);
}
