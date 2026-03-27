#include <gtest/gtest.h>

#include "GfxFont.cc"



class FNVHashTest_1975 : public ::testing::Test {

protected:

    FNVHash hash;

};



TEST_F(FNVHashTest_1975, InitialHashValueIsZero_1975) {

    EXPECT_EQ(hash.get31(), 0);

}



TEST_F(FNVHashTest_1975, HashSingleCharacter_1975) {

    hash.hash('a');

    int result = hash.get31();

    EXPECT_NE(result, 0); // Assuming 'a' does not hash to 0

}



TEST_F(FNVHashTest_1975, HashMultipleCharacters_1975) {

    hash.hash("abc", 3);

    int result = hash.get31();

    EXPECT_NE(result, 0); // Assuming "abc" does not hash to 0

}



TEST_F(FNVHashTest_1975, HashEmptyString_1975) {

    hash.hash("", 0);

    int result = hash.get31();

    EXPECT_EQ(result, 0); // Empty string should not change the hash value from initial state

}



TEST_F(FNVHashTest_1975, ConsistentHashing_1975) {

    hash.hash("test", 4);

    int firstResult = hash.get31();

    FNVHash newHash;

    newHash.hash("test", 4);

    int secondResult = newHash.get31();

    EXPECT_EQ(firstResult, secondResult); // Same input should produce same hash

}



TEST_F(FNVHashTest_1975, DifferentStringsDifferentHashes_1975) {

    hash.hash("hello", 5);

    int firstResult = hash.get31();

    FNVHash newHash;

    newHash.hash("world", 5);

    int secondResult = newHash.get31();

    EXPECT_NE(firstResult, secondResult); // Different inputs should produce different hashes

}
