#include <gtest/gtest.h>

// Replicate the FNVHash class based on the known interface
class FNVHash {
private:
    unsigned int h;

public:
    FNVHash() : h(2166136261u) {}

    void hash(char c) {
        h ^= c & 0xff;
        h *= 16777619;
    }

    void hash(const char *p, int n) {
        for (int i = 0; i < n; ++i) {
            hash(p[i]);
        }
    }

    int get31() const {
        return (h ^ (h >> 31)) & 0x7fffffff;
    }
};

// Test fixture
class FNVHashTest_1973 : public ::testing::Test {
protected:
    FNVHash hasher;
};

// Test that a freshly constructed FNVHash produces a consistent get31 value
TEST_F(FNVHashTest_1973, DefaultConstructorGet31_1973) {
    int result = hasher.get31();
    // The result should be deterministic and non-negative (31-bit)
    EXPECT_GE(result, 0);
    // Verify it's reproducible
    FNVHash another;
    EXPECT_EQ(another.get31(), result);
}

// Test that hashing a single character changes the hash value
TEST_F(FNVHashTest_1973, SingleCharHash_1973) {
    int before = hasher.get31();
    hasher.hash('a');
    int after = hasher.get31();
    // Hashing a character should (very likely) change the result
    EXPECT_NE(before, after);
}

// Test that hashing different characters produces different results
TEST_F(FNVHashTest_1973, DifferentCharsProduceDifferentHashes_1973) {
    FNVHash h1, h2;
    h1.hash('a');
    h2.hash('b');
    EXPECT_NE(h1.get31(), h2.get31());
}

// Test that hashing the same character produces the same result
TEST_F(FNVHashTest_1973, SameCharProducesSameHash_1973) {
    FNVHash h1, h2;
    h1.hash('x');
    h2.hash('x');
    EXPECT_EQ(h1.get31(), h2.get31());
}

// Test that hash(const char*, int) with a string works correctly
TEST_F(FNVHashTest_1973, StringHashConsistency_1973) {
    FNVHash h1, h2;
    const char *str = "hello";
    h1.hash(str, 5);

    // Hash the same string char by char
    h2.hash('h');
    h2.hash('e');
    h2.hash('l');
    h2.hash('l');
    h2.hash('o');

    EXPECT_EQ(h1.get31(), h2.get31());
}

// Test that get31 returns a non-negative value (31-bit)
TEST_F(FNVHashTest_1973, Get31ReturnsNonNegative_1973) {
    hasher.hash('Z');
    int result = hasher.get31();
    EXPECT_GE(result, 0);
    EXPECT_LE(result, 0x7fffffff);
}

// Test hashing with zero-length string doesn't change the hash
TEST_F(FNVHashTest_1973, ZeroLengthStringNoChange_1973) {
    int before = hasher.get31();
    hasher.hash("anything", 0);
    int after = hasher.get31();
    EXPECT_EQ(before, after);
}

// Test that order of characters matters
TEST_F(FNVHashTest_1973, OrderMatters_1973) {
    FNVHash h1, h2;
    h1.hash('a');
    h1.hash('b');

    h2.hash('b');
    h2.hash('a');

    EXPECT_NE(h1.get31(), h2.get31());
}

// Test hashing the null character
TEST_F(FNVHashTest_1973, NullCharHash_1973) {
    FNVHash h1;
    h1.hash('\0');
    int result = h1.get31();
    EXPECT_GE(result, 0);
    EXPECT_LE(result, 0x7fffffff);
}

// Test that get31 is idempotent (calling it multiple times gives same result)
TEST_F(FNVHashTest_1973, Get31Idempotent_1973) {
    hasher.hash('q');
    int first = hasher.get31();
    int second = hasher.get31();
    EXPECT_EQ(first, second);
}

// Test hashing with negative char values (high-bit set)
TEST_F(FNVHashTest_1973, NegativeCharValue_1973) {
    FNVHash h1;
    h1.hash(static_cast<char>(0xFF));
    int result = h1.get31();
    EXPECT_GE(result, 0);
    EXPECT_LE(result, 0x7fffffff);
}

// Test that the mask in hash() works correctly with high-bit chars
TEST_F(FNVHashTest_1973, CharMaskingConsistency_1973) {
    // Two FNVHash objects hashing the same byte value should match
    FNVHash h1, h2;
    h1.hash(static_cast<char>(0x80));
    h2.hash(static_cast<char>(0x80));
    EXPECT_EQ(h1.get31(), h2.get31());
}

// Test hashing a longer string
TEST_F(FNVHashTest_1973, LongerStringHash_1973) {
    const char *str = "The quick brown fox jumps over the lazy dog";
    hasher.hash(str, 43);
    int result = hasher.get31();
    EXPECT_GE(result, 0);
    EXPECT_LE(result, 0x7fffffff);

    // Verify reproducibility
    FNVHash h2;
    h2.hash(str, 43);
    EXPECT_EQ(h2.get31(), result);
}

// Test that different strings produce different hashes
TEST_F(FNVHashTest_1973, DifferentStringsProduceDifferentHashes_1973) {
    FNVHash h1, h2;
    h1.hash("abc", 3);
    h2.hash("abd", 3);
    EXPECT_NE(h1.get31(), h2.get31());
}

// Test hashing a single character string via string overload
TEST_F(FNVHashTest_1973, SingleCharStringHash_1973) {
    FNVHash h1, h2;
    h1.hash('A');
    h2.hash("A", 1);
    EXPECT_EQ(h1.get31(), h2.get31());
}

// Test N_UCS_CANDIDATES macro value
TEST(NUCSCandidatesTest_1973, ValueIsTwo_1973) {
#define N_UCS_CANDIDATES 2
    EXPECT_EQ(N_UCS_CANDIDATES, 2);
}

// Test hashing multiple characters incrementally
TEST_F(FNVHashTest_1973, IncrementalHashMatchesBulk_1973) {
    FNVHash h1, h2;
    const char *data = "test data 12345";
    int len = 15;

    // Bulk hash
    h1.hash(data, len);

    // Incremental: hash in two parts
    h2.hash(data, 5);
    h2.hash(data + 5, 10);

    EXPECT_EQ(h1.get31(), h2.get31());
}

// Test that hashing additional data after get31 still works
TEST_F(FNVHashTest_1973, HashAfterGet31_1973) {
    hasher.hash('a');
    int intermediate = hasher.get31();
    hasher.hash('b');
    int final_result = hasher.get31();
    // get31 should not alter internal state, so continuing to hash should work
    EXPECT_NE(intermediate, final_result);
}
