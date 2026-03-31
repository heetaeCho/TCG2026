#include <gtest/gtest.h>
#include <functional>
#include <unordered_map>
#include <unordered_set>
#include "Object.h"

// Test the hash function for Ref through observable behavior
// (using it in standard containers that require hashing)

class RefHashTest_63 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that hash produces consistent results for the same Ref
TEST_F(RefHashTest_63, SameRefProducesSameHash_63) {
    Ref ref1;
    ref1.num = 10;
    ref1.gen = 20;

    Ref ref2;
    ref2.num = 10;
    ref2.gen = 20;

    std::hash<Ref> hasher;
    EXPECT_EQ(hasher(ref1), hasher(ref2));
}

// Test that different Refs (different num) likely produce different hashes
TEST_F(RefHashTest_63, DifferentNumProducesDifferentHash_63) {
    Ref ref1;
    ref1.num = 10;
    ref1.gen = 20;

    Ref ref2;
    ref2.num = 11;
    ref2.gen = 20;

    std::hash<Ref> hasher;
    // While hash collisions are theoretically possible, these simple cases should differ
    EXPECT_NE(hasher(ref1), hasher(ref2));
}

// Test that different Refs (different gen) likely produce different hashes
TEST_F(RefHashTest_63, DifferentGenProducesDifferentHash_63) {
    Ref ref1;
    ref1.num = 10;
    ref1.gen = 20;

    Ref ref2;
    ref2.num = 10;
    ref2.gen = 21;

    std::hash<Ref> hasher;
    EXPECT_NE(hasher(ref1), hasher(ref2));
}

// Test that Ref can be used as a key in unordered_map
TEST_F(RefHashTest_63, RefUsableAsUnorderedMapKey_63) {
    std::unordered_map<Ref, int> refMap;

    Ref ref1;
    ref1.num = 1;
    ref1.gen = 0;

    Ref ref2;
    ref2.num = 2;
    ref2.gen = 0;

    refMap[ref1] = 100;
    refMap[ref2] = 200;

    EXPECT_EQ(refMap.size(), 2u);
    EXPECT_EQ(refMap[ref1], 100);
    EXPECT_EQ(refMap[ref2], 200);
}

// Test that Ref can be used in unordered_set
TEST_F(RefHashTest_63, RefUsableInUnorderedSet_63) {
    std::unordered_set<Ref> refSet;

    Ref ref1;
    ref1.num = 5;
    ref1.gen = 3;

    refSet.insert(ref1);
    EXPECT_EQ(refSet.size(), 1u);

    // Insert same ref again
    Ref ref1Copy;
    ref1Copy.num = 5;
    ref1Copy.gen = 3;
    refSet.insert(ref1Copy);
    EXPECT_EQ(refSet.size(), 1u);

    // Insert different ref
    Ref ref2;
    ref2.num = 6;
    ref2.gen = 3;
    refSet.insert(ref2);
    EXPECT_EQ(refSet.size(), 2u);
}

// Test hash with zero values
TEST_F(RefHashTest_63, ZeroValuesHash_63) {
    Ref ref;
    ref.num = 0;
    ref.gen = 0;

    std::hash<Ref> hasher;
    // Should not throw, just compute a hash
    size_t h = hasher(ref);
    (void)h; // suppress unused warning
    SUCCEED();
}

// Test hash with negative values
TEST_F(RefHashTest_63, NegativeValuesHash_63) {
    Ref ref;
    ref.num = -1;
    ref.gen = -1;

    std::hash<Ref> hasher;
    size_t h = hasher(ref);
    (void)h;
    SUCCEED();
}

// Test hash with large values
TEST_F(RefHashTest_63, LargeValuesHash_63) {
    Ref ref;
    ref.num = INT_MAX;
    ref.gen = INT_MAX;

    std::hash<Ref> hasher;
    size_t h = hasher(ref);
    (void)h;
    SUCCEED();
}

// Test hash with min int values
TEST_F(RefHashTest_63, MinIntValuesHash_63) {
    Ref ref;
    ref.num = INT_MIN;
    ref.gen = INT_MIN;

    std::hash<Ref> hasher;
    size_t h = hasher(ref);
    (void)h;
    SUCCEED();
}

// Test that swapping num and gen produces different hash (asymmetry)
TEST_F(RefHashTest_63, SwappedNumGenDifferentHash_63) {
    Ref ref1;
    ref1.num = 1;
    ref1.gen = 2;

    Ref ref2;
    ref2.num = 2;
    ref2.gen = 1;

    std::hash<Ref> hasher;
    // Due to the shift in the hash formula, swapping should give different results
    EXPECT_NE(hasher(ref1), hasher(ref2));
}

// Test INVALID ref can be hashed
TEST_F(RefHashTest_63, InvalidRefCanBeHashed_63) {
    Ref invalidRef = Ref::INVALID();

    std::hash<Ref> hasher;
    size_t h = hasher(invalidRef);
    (void)h;
    SUCCEED();
}

// Test that the hash is noexcept as declared
TEST_F(RefHashTest_63, HashIsNoexcept_63) {
    Ref ref;
    ref.num = 1;
    ref.gen = 1;

    std::hash<Ref> hasher;
    EXPECT_TRUE(noexcept(hasher(ref)));
}

// Test multiple distinct refs in unordered_map
TEST_F(RefHashTest_63, MultipleDistinctRefsInMap_63) {
    std::unordered_map<Ref, std::string> refMap;

    for (int i = 0; i < 100; ++i) {
        Ref ref;
        ref.num = i;
        ref.gen = i * 2;
        refMap[ref] = "value_" + std::to_string(i);
    }

    EXPECT_EQ(refMap.size(), 100u);

    // Verify retrieval
    Ref lookupRef;
    lookupRef.num = 50;
    lookupRef.gen = 100;
    auto it = refMap.find(lookupRef);
    ASSERT_NE(it, refMap.end());
    EXPECT_EQ(it->second, "value_50");
}

// Test hash determinism across multiple calls
TEST_F(RefHashTest_63, HashDeterministic_63) {
    Ref ref;
    ref.num = 42;
    ref.gen = 7;

    std::hash<Ref> hasher;
    size_t h1 = hasher(ref);
    size_t h2 = hasher(ref);
    size_t h3 = hasher(ref);

    EXPECT_EQ(h1, h2);
    EXPECT_EQ(h2, h3);
}
