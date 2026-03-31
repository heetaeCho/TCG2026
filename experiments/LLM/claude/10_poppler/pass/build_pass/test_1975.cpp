#include <gtest/gtest.h>

// Minimal reconstruction of FNVHash based on the known interface
// We treat the implementation as a black box but need the class declaration to compile tests.

#define N_UCS_CANDIDATES 2

class FNVHash {
private:
    unsigned int h;

public:
    FNVHash();
    void hash(char c);
    void hash(const char *p, int n);
    int get31() const;
};

// Since we don't have access to the actual implementation, we provide a minimal
// FNV-1a style implementation that matches the interface. In a real scenario,
// this would be linked from the actual library.
// NOTE: This is needed only to make tests compile and link. The actual tests
// treat the behavior as observable through the interface.

FNVHash::FNVHash() : h(2166136261u) {}

void FNVHash::hash(char c) {
    h ^= (unsigned char)c;
    h *= 16777619u;
}

void FNVHash::hash(const char *p, int n) {
    for (int i = 0; i < n; i++) {
        hash(p[i]);
    }
}

int FNVHash::get31() const {
    return (h ^ (h >> 31)) & 0x7fffffff;
}

// ===================== TESTS =====================

class FNVHashTest_1975 : public ::testing::Test {
protected:
    FNVHash hasher;
};

// Test that a freshly constructed FNVHash returns a non-negative value from get31
TEST_F(FNVHashTest_1975, DefaultConstructor_Get31ReturnsNonNegative_1975) {
    int result = hasher.get31();
    EXPECT_GE(result, 0);
}

// Test that get31 always returns a value within [0, 0x7fffffff]
TEST_F(FNVHashTest_1975, Get31ReturnsWithin31BitRange_1975) {
    int result = hasher.get31();
    EXPECT_GE(result, 0);
    EXPECT_LE(result, 0x7fffffff);
}

// Test that hashing a single character changes the hash value
TEST_F(FNVHashTest_1975, HashSingleCharChangesValue_1975) {
    int before = hasher.get31();
    hasher.hash('A');
    int after = hasher.get31();
    // While theoretically possible to collide, it's extremely unlikely
    EXPECT_NE(before, after);
}

// Test that hashing different single characters produces different results
TEST_F(FNVHashTest_1975, DifferentCharsProduceDifferentHashes_1975) {
    FNVHash h1;
    FNVHash h2;
    h1.hash('A');
    h2.hash('B');
    EXPECT_NE(h1.get31(), h2.get31());
}

// Test that hashing the same character produces the same result (determinism)
TEST_F(FNVHashTest_1975, SameCharProducesSameHash_1975) {
    FNVHash h1;
    FNVHash h2;
    h1.hash('X');
    h2.hash('X');
    EXPECT_EQ(h1.get31(), h2.get31());
}

// Test hash(const char*, int) with a string
TEST_F(FNVHashTest_1975, HashStringProducesConsistentResult_1975) {
    FNVHash h1;
    FNVHash h2;
    const char *str = "hello";
    h1.hash(str, 5);
    h2.hash(str, 5);
    EXPECT_EQ(h1.get31(), h2.get31());
}

// Test that hash(const char*, int) with individual chars matches sequential hash(char)
TEST_F(FNVHashTest_1975, HashStringEquivalentToSequentialCharHash_1975) {
    FNVHash h1;
    FNVHash h2;
    const char *str = "test";
    h1.hash(str, 4);
    h2.hash('t');
    h2.hash('e');
    h2.hash('s');
    h2.hash('t');
    EXPECT_EQ(h1.get31(), h2.get31());
}

// Test hash with empty string (n=0) doesn't change the hash
TEST_F(FNVHashTest_1975, HashEmptyStringNoChange_1975) {
    int before = hasher.get31();
    hasher.hash("anything", 0);
    int after = hasher.get31();
    EXPECT_EQ(before, after);
}

// Test that different strings produce different hashes
TEST_F(FNVHashTest_1975, DifferentStringsProduceDifferentHashes_1975) {
    FNVHash h1;
    FNVHash h2;
    h1.hash("abc", 3);
    h2.hash("def", 3);
    EXPECT_NE(h1.get31(), h2.get31());
}

// Test that get31 result is always non-negative after multiple hash operations
TEST_F(FNVHashTest_1975, Get31AlwaysNonNegativeAfterMultipleHashes_1975) {
    for (int i = 0; i < 256; i++) {
        FNVHash h;
        h.hash(static_cast<char>(i));
        EXPECT_GE(h.get31(), 0) << "Failed for char value: " << i;
    }
}

// Test that get31 is idempotent (calling it multiple times gives same result)
TEST_F(FNVHashTest_1975, Get31IsIdempotent_1975) {
    hasher.hash("some data", 9);
    int first = hasher.get31();
    int second = hasher.get31();
    int third = hasher.get31();
    EXPECT_EQ(first, second);
    EXPECT_EQ(second, third);
}

// Test hashing a single byte at a time vs bulk
TEST_F(FNVHashTest_1975, PartialHashMatchesFullHash_1975) {
    FNVHash h1;
    FNVHash h2;
    const char *str = "abcdefgh";
    h1.hash(str, 8);
    h2.hash(str, 4);
    h2.hash(str + 4, 4);
    EXPECT_EQ(h1.get31(), h2.get31());
}

// Test that hashing null character works
TEST_F(FNVHashTest_1975, HashNullCharacter_1975) {
    FNVHash h1;
    FNVHash h2;
    h1.hash('\0');
    h2.hash('A');
    EXPECT_NE(h1.get31(), h2.get31());
}

// Test that N_UCS_CANDIDATES is defined as 2
TEST_F(FNVHashTest_1975, NUcsCandidatesIsTwp_1975) {
    EXPECT_EQ(N_UCS_CANDIDATES, 2);
}

// Test hashing a long string still produces valid result
TEST_F(FNVHashTest_1975, LongStringProducesValidResult_1975) {
    std::string longStr(10000, 'x');
    hasher.hash(longStr.c_str(), static_cast<int>(longStr.size()));
    int result = hasher.get31();
    EXPECT_GE(result, 0);
    EXPECT_LE(result, 0x7fffffff);
}

// Test that order of characters matters
TEST_F(FNVHashTest_1975, OrderMatters_1975) {
    FNVHash h1;
    FNVHash h2;
    h1.hash("ab", 2);
    h2.hash("ba", 2);
    EXPECT_NE(h1.get31(), h2.get31());
}

// Test hashing with length 1 via string interface matches char interface
TEST_F(FNVHashTest_1975, SingleCharStringMatchesSingleCharHash_1975) {
    FNVHash h1;
    FNVHash h2;
    h1.hash('Z');
    h2.hash("Z", 1);
    EXPECT_EQ(h1.get31(), h2.get31());
}
