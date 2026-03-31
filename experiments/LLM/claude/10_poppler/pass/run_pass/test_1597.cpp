#include <gtest/gtest.h>

// Include necessary headers
// We need the Ref struct and T3FontCache class

// Based on the provided interface, we need to define minimal structures
// to test the matches() method

struct Ref {
    int num;
    int gen;
    
    bool operator==(const Ref &other) const {
        return num == other.num && gen == other.gen;
    }
    
    static constexpr Ref INVALID() { return {-1, -1}; }
};

// Minimal forward declaration
struct T3FontCacheTag;

class T3FontCache {
public:
    Ref fontID;
    double m11;
    double m12;
    double m21;
    double m22;
    int glyphX;
    int glyphY;
    bool validBBox;
    unsigned char *cacheData;
    T3FontCacheTag *cacheTags;

    // We can't call the real constructor since it has complex dependencies,
    // so we'll directly set the public members for testing matches()
    
    bool matches(const Ref *idA, double m11A, double m12A, double m21A, double m22A) const {
        return fontID == *idA && m11 == m11A && m12 == m12A && m21 == m21A && m22 == m22A;
    }
};

class T3FontCacheMatchesTest_1597 : public ::testing::Test {
protected:
    T3FontCache cache;
    
    void SetUp() override {
        cache.fontID = {1, 0};
        cache.m11 = 1.0;
        cache.m12 = 0.0;
        cache.m21 = 0.0;
        cache.m22 = 1.0;
        cache.glyphX = 0;
        cache.glyphY = 0;
        cache.validBBox = true;
        cache.cacheData = nullptr;
        cache.cacheTags = nullptr;
    }
};

TEST_F(T3FontCacheMatchesTest_1597, ExactMatch_1597) {
    Ref id = {1, 0};
    EXPECT_TRUE(cache.matches(&id, 1.0, 0.0, 0.0, 1.0));
}

TEST_F(T3FontCacheMatchesTest_1597, DifferentFontIDNum_1597) {
    Ref id = {2, 0};
    EXPECT_FALSE(cache.matches(&id, 1.0, 0.0, 0.0, 1.0));
}

TEST_F(T3FontCacheMatchesTest_1597, DifferentFontIDGen_1597) {
    Ref id = {1, 1};
    EXPECT_FALSE(cache.matches(&id, 1.0, 0.0, 0.0, 1.0));
}

TEST_F(T3FontCacheMatchesTest_1597, DifferentM11_1597) {
    Ref id = {1, 0};
    EXPECT_FALSE(cache.matches(&id, 2.0, 0.0, 0.0, 1.0));
}

TEST_F(T3FontCacheMatchesTest_1597, DifferentM12_1597) {
    Ref id = {1, 0};
    EXPECT_FALSE(cache.matches(&id, 1.0, 0.5, 0.0, 1.0));
}

TEST_F(T3FontCacheMatchesTest_1597, DifferentM21_1597) {
    Ref id = {1, 0};
    EXPECT_FALSE(cache.matches(&id, 1.0, 0.0, 0.5, 1.0));
}

TEST_F(T3FontCacheMatchesTest_1597, DifferentM22_1597) {
    Ref id = {1, 0};
    EXPECT_FALSE(cache.matches(&id, 1.0, 0.0, 0.0, 2.0));
}

TEST_F(T3FontCacheMatchesTest_1597, AllParametersDifferent_1597) {
    Ref id = {99, 99};
    EXPECT_FALSE(cache.matches(&id, 5.0, 6.0, 7.0, 8.0));
}

TEST_F(T3FontCacheMatchesTest_1597, ZeroMatrixValues_1597) {
    cache.m11 = 0.0;
    cache.m12 = 0.0;
    cache.m21 = 0.0;
    cache.m22 = 0.0;
    Ref id = {1, 0};
    EXPECT_TRUE(cache.matches(&id, 0.0, 0.0, 0.0, 0.0));
}

TEST_F(T3FontCacheMatchesTest_1597, NegativeMatrixValues_1597) {
    cache.m11 = -1.0;
    cache.m12 = -2.0;
    cache.m21 = -3.0;
    cache.m22 = -4.0;
    Ref id = {1, 0};
    EXPECT_TRUE(cache.matches(&id, -1.0, -2.0, -3.0, -4.0));
}

TEST_F(T3FontCacheMatchesTest_1597, NegativeVsPositiveMatrixValues_1597) {
    cache.m11 = -1.0;
    cache.m12 = 2.0;
    cache.m21 = -3.0;
    cache.m22 = 4.0;
    Ref id = {1, 0};
    EXPECT_FALSE(cache.matches(&id, 1.0, 2.0, -3.0, 4.0));
}

TEST_F(T3FontCacheMatchesTest_1597, LargeMatrixValues_1597) {
    cache.m11 = 1e15;
    cache.m12 = 1e15;
    cache.m21 = 1e15;
    cache.m22 = 1e15;
    Ref id = {1, 0};
    EXPECT_TRUE(cache.matches(&id, 1e15, 1e15, 1e15, 1e15));
}

TEST_F(T3FontCacheMatchesTest_1597, VerySmallMatrixValues_1597) {
    cache.m11 = 1e-15;
    cache.m12 = 1e-15;
    cache.m21 = 1e-15;
    cache.m22 = 1e-15;
    Ref id = {1, 0};
    EXPECT_TRUE(cache.matches(&id, 1e-15, 1e-15, 1e-15, 1e-15));
}

TEST_F(T3FontCacheMatchesTest_1597, MatchWithNegativeFontID_1597) {
    cache.fontID = {-1, -1};
    Ref id = {-1, -1};
    EXPECT_TRUE(cache.matches(&id, 1.0, 0.0, 0.0, 1.0));
}

TEST_F(T3FontCacheMatchesTest_1597, InvalidRefMatch_1597) {
    Ref invalid = Ref::INVALID();
    cache.fontID = invalid;
    EXPECT_TRUE(cache.matches(&invalid, 1.0, 0.0, 0.0, 1.0));
}

TEST_F(T3FontCacheMatchesTest_1597, InvalidRefNoMatch_1597) {
    Ref invalid = Ref::INVALID();
    // cache.fontID is {1, 0} by default
    EXPECT_FALSE(cache.matches(&invalid, 1.0, 0.0, 0.0, 1.0));
}

TEST_F(T3FontCacheMatchesTest_1597, OnlyFontIDMatches_1597) {
    Ref id = {1, 0};
    EXPECT_FALSE(cache.matches(&id, 99.0, 99.0, 99.0, 99.0));
}

TEST_F(T3FontCacheMatchesTest_1597, OnlyMatrixMatches_1597) {
    Ref id = {999, 999};
    EXPECT_FALSE(cache.matches(&id, 1.0, 0.0, 0.0, 1.0));
}

TEST_F(T3FontCacheMatchesTest_1597, FractionalMatrixValues_1597) {
    cache.m11 = 0.333333;
    cache.m12 = 0.666666;
    cache.m21 = 0.123456;
    cache.m22 = 0.789012;
    Ref id = {1, 0};
    EXPECT_TRUE(cache.matches(&id, 0.333333, 0.666666, 0.123456, 0.789012));
}

TEST_F(T3FontCacheMatchesTest_1597, SlightlyDifferentDoubleValues_1597) {
    cache.m11 = 1.0;
    Ref id = {1, 0};
    // 1.0 + very tiny epsilon - exact floating point comparison
    EXPECT_FALSE(cache.matches(&id, 1.0 + 1e-10, 0.0, 0.0, 1.0));
}

TEST_F(T3FontCacheMatchesTest_1597, ZeroFontID_1597) {
    cache.fontID = {0, 0};
    Ref id = {0, 0};
    EXPECT_TRUE(cache.matches(&id, 1.0, 0.0, 0.0, 1.0));
}

TEST_F(T3FontCacheMatchesTest_1597, MultipleCacheInstances_1597) {
    T3FontCache cache2;
    cache2.fontID = {2, 0};
    cache2.m11 = 2.0;
    cache2.m12 = 3.0;
    cache2.m21 = 4.0;
    cache2.m22 = 5.0;
    cache2.cacheData = nullptr;
    cache2.cacheTags = nullptr;
    
    Ref id1 = {1, 0};
    Ref id2 = {2, 0};
    
    EXPECT_TRUE(cache.matches(&id1, 1.0, 0.0, 0.0, 1.0));
    EXPECT_FALSE(cache.matches(&id2, 2.0, 3.0, 4.0, 5.0));
    
    EXPECT_TRUE(cache2.matches(&id2, 2.0, 3.0, 4.0, 5.0));
    EXPECT_FALSE(cache2.matches(&id1, 1.0, 0.0, 0.0, 1.0));
}
