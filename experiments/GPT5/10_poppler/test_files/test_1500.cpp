#include <gtest/gtest.h>
#include <string_view>
#include <functional>
#include "NameToCharCode.h" // Assuming the class NameToCharCode is defined in this header

// TEST_ID: 1500
TEST_F(NameToCharCodeTest_1500, HashFunctionForCharPointer_1500) {
    NameToCharCode::string_hasher hasher;
    const char* testString = "test";
    size_t hashValue = hasher(testString);

    // Verifying the hash value is not zero, since hash functions should return a non-zero value for non-empty strings.
    EXPECT_NE(hashValue, 0);
}

// TEST_ID: 1501
TEST_F(NameToCharCodeTest_1501, HashFunctionForString_1501) {
    NameToCharCode::string_hasher hasher;
    std::string testString = "test";
    size_t hashValue = hasher(testString);

    // Verifying the hash value is not zero for non-empty strings.
    EXPECT_NE(hashValue, 0);
}

// TEST_ID: 1502
TEST_F(NameToCharCodeTest_1502, HashFunctionForEmptyCharPointer_1502) {
    NameToCharCode::string_hasher hasher;
    const char* emptyString = "";
    size_t hashValue = hasher(emptyString);

    // Hashing an empty string should still produce a non-zero value, as it is a valid input for the hash function.
    EXPECT_NE(hashValue, 0);
}

// TEST_ID: 1503
TEST_F(NameToCharCodeTest_1503, HashFunctionForEmptyString_1503) {
    NameToCharCode::string_hasher hasher;
    std::string emptyString = "";
    size_t hashValue = hasher(emptyString);

    // Similar to the previous test, empty strings should produce a valid hash value.
    EXPECT_NE(hashValue, 0);
}

// TEST_ID: 1504
TEST_F(NameToCharCodeTest_1504, ConsistentHashingForSameInput_1504) {
    NameToCharCode::string_hasher hasher;
    std::string testString = "test";

    size_t firstHashValue = hasher(testString);
    size_t secondHashValue = hasher(testString);

    // Verifying that the same input produces the same hash value
    EXPECT_EQ(firstHashValue, secondHashValue);
}

// TEST_ID: 1505
TEST_F(NameToCharCodeTest_1505, DifferentInputsProduceDifferentHashes_1505) {
    NameToCharCode::string_hasher hasher;
    std::string string1 = "test";
    std::string string2 = "test2";

    size_t hashValue1 = hasher(string1);
    size_t hashValue2 = hasher(string2);

    // Verifying that different inputs produce different hash values.
    EXPECT_NE(hashValue1, hashValue2);
}

// TEST_ID: 1506
TEST_F(NameToCharCodeTest_1506, HandlingNullPointerInHash_1506) {
    NameToCharCode::string_hasher hasher;
    
    // Verifying that passing a nullptr doesn't cause a crash
    EXPECT_NO_THROW(hasher(nullptr));
}