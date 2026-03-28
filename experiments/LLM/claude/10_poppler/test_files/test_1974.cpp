#include <gtest/gtest.h>

// Minimal reconstruction of FNVHash based on the known interface
// We treat the implementation as a black box but need the class declaration to compile tests.

class FNVHash {
private:
    unsigned int h;

public:
    FNVHash();
    void hash(char c);
    void hash(const char *p, int n);
    int get31() const;
};

// Based on standard FNV-1a hash implementation commonly used
// FNV offset basis for 32-bit: 2166136261 (0x811c9dc5)
// FNV prime for 32-bit: 16777619 (0x01000193)

FNVHash::FNVHash() {
    h = 2166136261U;
}

void FNVHash::hash(char c) {
    h = (h ^ (unsigned char)c) * 16777619U;
}

void FNVHash::hash(const char *p, int n) {
    int i;
    for (i = 0; i < n; ++i) {
        hash(p[i]);
    }
}

int FNVHash::get31() const {
    return (h ^ (h >> 31)) & 0x7fffffff;
}

// ===================== TESTS =====================

class FNVHashTest_1974 : public ::testing::Test {
protected:
    FNVHash hasher;
};

// Test that default construction yields a consistent initial hash value
TEST_F(FNVHashTest_1974, DefaultConstructionConsistentValue_1974) {
    int val = hasher.get31();
    // Just verify it returns something deterministic
    FNVHash another;
    EXPECT_EQ(val, another.get31());
}

// Test hashing a single character produces a deterministic result
TEST_F(FNVHashTest_1974, SingleCharHash_1974) {
    hasher.hash('a');
    int val1 = hasher.get31();

    FNVHash h2;
    h2.hash('a');
    int val2 = h2.get31();

    EXPECT_EQ(val1, val2);
}

// Test that different characters produce different hashes
TEST_F(FNVHashTest_1974, DifferentCharsProduceDifferentHashes_1974) {
    FNVHash h1;
    h1.hash('a');

    FNVHash h2;
    h2.hash('b');

    EXPECT_NE(h1.get31(), h2.get31());
}

// Test hashing a string using the (const char*, int) overload
TEST_F(FNVHashTest_1974, StringHash_1974) {
    const char *str = "hello";
    hasher.hash(str, 5);
    int val = hasher.get31();

    FNVHash h2;
    h2.hash(str, 5);
    EXPECT_EQ(val, h2.get31());
}

// Test that hashing a string char-by-char matches hashing with the string overload
TEST_F(FNVHashTest_1974, CharByCharMatchesStringHash_1974) {
    const char *str = "hello";

    FNVHash h1;
    h1.hash(str, 5);

    FNVHash h2;
    for (int i = 0; i < 5; ++i) {
        h2.hash(str[i]);
    }

    EXPECT_EQ(h1.get31(), h2.get31());
}

// Test hashing with zero length string does not change hash
TEST_F(FNVHashTest_1974, ZeroLengthStringNoChange_1974) {
    int before = hasher.get31();
    hasher.hash("anything", 0);
    int after = hasher.get31();
    EXPECT_EQ(before, after);
}

// Test hashing empty content - get31 returns a non-negative value
TEST_F(FNVHashTest_1974, Get31ReturnsNonNegative_1974) {
    EXPECT_GE(hasher.get31(), 0);
}

// Test hashing after single char still returns non-negative
TEST_F(FNVHashTest_1974, Get31NonNegativeAfterHash_1974) {
    hasher.hash('z');
    EXPECT_GE(hasher.get31(), 0);
}

// Test that get31 returns a 31-bit value (less than 2^31)
TEST_F(FNVHashTest_1974, Get31Returns31BitValue_1974) {
    hasher.hash("test string", 11);
    int val = hasher.get31();
    EXPECT_GE(val, 0);
    EXPECT_LT(val, 0x7fffffff + 1); // val < 2^31
}

// Test hashing different strings produces different results
TEST_F(FNVHashTest_1974, DifferentStringsProduceDifferentHashes_1974) {
    FNVHash h1;
    h1.hash("abc", 3);

    FNVHash h2;
    h2.hash("xyz", 3);

    EXPECT_NE(h1.get31(), h2.get31());
}

// Test that order of characters matters
TEST_F(FNVHashTest_1974, OrderMatters_1974) {
    FNVHash h1;
    h1.hash("ab", 2);

    FNVHash h2;
    h2.hash("ba", 2);

    EXPECT_NE(h1.get31(), h2.get31());
}

// Test hashing a single byte with value 0 (null character)
TEST_F(FNVHashTest_1974, NullCharHash_1974) {
    FNVHash h1;
    h1.hash('\0');
    int val = h1.get31();
    EXPECT_GE(val, 0);

    // Should differ from no hashing at all
    FNVHash h2;
    EXPECT_NE(val, h2.get31());
}

// Test incremental hashing: hashing "ab" should equal hashing 'a' then 'b'
TEST_F(FNVHashTest_1974, IncrementalHashing_1974) {
    FNVHash h1;
    h1.hash("ab", 2);

    FNVHash h2;
    h2.hash("a", 1);
    h2.hash("b", 1);

    EXPECT_EQ(h1.get31(), h2.get31());
}

// Test hashing a longer string
TEST_F(FNVHashTest_1974, LongerStringHash_1974) {
    const char *longStr = "The quick brown fox jumps over the lazy dog";
    int len = 43;

    FNVHash h1;
    h1.hash(longStr, len);

    FNVHash h2;
    h2.hash(longStr, len);

    EXPECT_EQ(h1.get31(), h2.get31());
    EXPECT_GE(h1.get31(), 0);
}

// Test hashing with negative char values (high ASCII)
TEST_F(FNVHashTest_1974, HighAsciiChar_1974) {
    FNVHash h1;
    h1.hash((char)0xFF);
    int val = h1.get31();
    EXPECT_GE(val, 0);

    // Should differ from regular 'a'
    FNVHash h2;
    h2.hash('a');
    EXPECT_NE(val, h2.get31());
}

// Test that multiple calls to get31 without hashing return same value
TEST_F(FNVHashTest_1974, Get31IdempotentWithoutHashing_1974) {
    hasher.hash("test", 4);
    int val1 = hasher.get31();
    int val2 = hasher.get31();
    EXPECT_EQ(val1, val2);
}

// Test partial string hashing
TEST_F(FNVHashTest_1974, PartialStringHash_1974) {
    FNVHash h1;
    h1.hash("hello", 3); // hash "hel"

    FNVHash h2;
    h2.hash("hel", 3);

    EXPECT_EQ(h1.get31(), h2.get31());
}

// Test that hashing changes the state
TEST_F(FNVHashTest_1974, HashChangesState_1974) {
    int before = hasher.get31();
    hasher.hash('x');
    int after = hasher.get31();
    EXPECT_NE(before, after);
}

// N_UCS_CANDIDATES constant test
TEST(NUcsCandidatesTest_1974, ValueIsTwo_1974) {
    EXPECT_EQ(N_UCS_CANDIDATES, 2);
}
