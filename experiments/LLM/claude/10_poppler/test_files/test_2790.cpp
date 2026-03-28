#include <gtest/gtest.h>

// We need to include the header that declares FNVHash.
// Based on the provided code, FNVHash is defined in GfxFont.cc.
// We'll include the relevant header.
#include "GfxFont.h"

// If FNVHash is not exposed via header, we may need to replicate the minimal
// declaration. Based on the known dependencies, FNVHash has:
//   - FNVHash() constructor (initializes h = 2166136261U)
//   - void hash(char c)
//   - void hash(const char *p, int n)
//   - int get31() const

// Since FNVHash might be internal to GfxFont.cc and not exposed in the header,
// we include the .cc file directly to access it for testing purposes.
// This is a common technique for testing file-local classes.
#ifndef FNVHASH_DECLARED
#include "GfxFont.cc"
#define FNVHASH_DECLARED
#endif

class FNVHashTest_2790 : public ::testing::Test {
protected:
    FNVHash hash_obj;
};

// Test that a freshly constructed FNVHash returns a deterministic value from get31()
TEST_F(FNVHashTest_2790, DefaultConstructor_Get31ReturnsConsistentValue_2790) {
    int val = hash_obj.get31();
    // get31() should return a non-negative value (31-bit)
    EXPECT_GE(val, 0);
    
    // Creating another instance should give the same initial value
    FNVHash another;
    EXPECT_EQ(val, another.get31());
}

// Test that get31() returns a 31-bit value (non-negative int)
TEST_F(FNVHashTest_2790, Get31ReturnsNonNegative_2790) {
    int val = hash_obj.get31();
    EXPECT_GE(val, 0);
    // 31 bits means max value is 2^31 - 1 = 2147483647
    EXPECT_LE(val, 2147483647);
}

// Test hashing a single character changes the hash value
TEST_F(FNVHashTest_2790, HashSingleCharChangesValue_2790) {
    int initial_val = hash_obj.get31();
    hash_obj.hash('A');
    int after_hash = hash_obj.get31();
    // After hashing a character, the value should (almost certainly) change
    EXPECT_NE(initial_val, after_hash);
}

// Test hashing different single characters produces different results
TEST_F(FNVHashTest_2790, DifferentCharsProduceDifferentHashes_2790) {
    FNVHash h1;
    FNVHash h2;
    h1.hash('A');
    h2.hash('B');
    EXPECT_NE(h1.get31(), h2.get31());
}

// Test hashing the same character produces the same result
TEST_F(FNVHashTest_2790, SameCharProducesSameHash_2790) {
    FNVHash h1;
    FNVHash h2;
    h1.hash('X');
    h2.hash('X');
    EXPECT_EQ(h1.get31(), h2.get31());
}

// Test hashing a string via hash(const char*, int)
TEST_F(FNVHashTest_2790, HashStringChangesValue_2790) {
    int initial_val = hash_obj.get31();
    const char* str = "Hello";
    hash_obj.hash(str, 5);
    int after_hash = hash_obj.get31();
    EXPECT_NE(initial_val, after_hash);
}

// Test hashing the same string produces the same result
TEST_F(FNVHashTest_2790, SameStringProducesSameHash_2790) {
    FNVHash h1;
    FNVHash h2;
    const char* str = "TestString";
    h1.hash(str, 10);
    h2.hash(str, 10);
    EXPECT_EQ(h1.get31(), h2.get31());
}

// Test hashing different strings produces different results
TEST_F(FNVHashTest_2790, DifferentStringsProduceDifferentHashes_2790) {
    FNVHash h1;
    FNVHash h2;
    h1.hash("abc", 3);
    h2.hash("def", 3);
    EXPECT_NE(h1.get31(), h2.get31());
}

// Test that hashing character by character is equivalent to hashing a string
TEST_F(FNVHashTest_2790, CharByCharEqualsStringHash_2790) {
    FNVHash h1;
    FNVHash h2;
    
    const char* str = "Hello";
    // Hash character by character
    for (int i = 0; i < 5; i++) {
        h1.hash(str[i]);
    }
    // Hash as string
    h2.hash(str, 5);
    
    EXPECT_EQ(h1.get31(), h2.get31());
}

// Test hashing with zero length string doesn't change the hash
TEST_F(FNVHashTest_2790, HashZeroLengthStringNoChange_2790) {
    int initial_val = hash_obj.get31();
    hash_obj.hash("anything", 0);
    int after_hash = hash_obj.get31();
    EXPECT_EQ(initial_val, after_hash);
}

// Test that hash order matters
TEST_F(FNVHashTest_2790, OrderMatters_2790) {
    FNVHash h1;
    FNVHash h2;
    h1.hash('A');
    h1.hash('B');
    h2.hash('B');
    h2.hash('A');
    EXPECT_NE(h1.get31(), h2.get31());
}

// Test hashing the null character
TEST_F(FNVHashTest_2790, HashNullChar_2790) {
    int initial_val = hash_obj.get31();
    hash_obj.hash('\0');
    int after_hash = hash_obj.get31();
    // Null character should still change the hash
    EXPECT_NE(initial_val, after_hash);
}

// Test hashing multiple times accumulates
TEST_F(FNVHashTest_2790, MultipleHashCallsAccumulate_2790) {
    hash_obj.hash('A');
    int after_one = hash_obj.get31();
    hash_obj.hash('B');
    int after_two = hash_obj.get31();
    EXPECT_NE(after_one, after_two);
}

// Test get31 is idempotent (calling it multiple times returns same value)
TEST_F(FNVHashTest_2790, Get31IsIdempotent_2790) {
    hash_obj.hash("test", 4);
    int val1 = hash_obj.get31();
    int val2 = hash_obj.get31();
    EXPECT_EQ(val1, val2);
}

// Test hashing a longer string
TEST_F(FNVHashTest_2790, HashLongerString_2790) {
    const char* long_str = "This is a somewhat longer string for testing FNV hash behavior";
    int len = strlen(long_str);
    hash_obj.hash(long_str, len);
    int val = hash_obj.get31();
    EXPECT_GE(val, 0);
    EXPECT_LE(val, 2147483647);
}

// Test partial string hashing produces different result from full string
TEST_F(FNVHashTest_2790, PartialStringDiffersFromFull_2790) {
    FNVHash h1;
    FNVHash h2;
    const char* str = "Hello World";
    h1.hash(str, 5);   // "Hello"
    h2.hash(str, 11);  // "Hello World"
    EXPECT_NE(h1.get31(), h2.get31());
}

// Test hashing with single length string via hash(const char*, int)
TEST_F(FNVHashTest_2790, HashSingleCharString_2790) {
    FNVHash h1;
    FNVHash h2;
    h1.hash('A');
    h2.hash("A", 1);
    EXPECT_EQ(h1.get31(), h2.get31());
}
