#include "gtest/gtest.h"
#include "graph.h"

class EdgeCmpTest_63 : public ::testing::Test {
protected:
    Edge edge_a;
    Edge edge_b;
    EdgeCmp cmp;
};

TEST_F(EdgeCmpTest_63, LessThanReturnsTrue_63) {
    edge_a.id_ = 1;
    edge_b.id_ = 2;
    EXPECT_TRUE(cmp(&edge_a, &edge_b));
}

TEST_F(EdgeCmpTest_63, GreaterThanReturnsFalse_63) {
    edge_a.id_ = 5;
    edge_b.id_ = 3;
    EXPECT_FALSE(cmp(&edge_a, &edge_b));
}

TEST_F(EdgeCmpTest_63, EqualIdsReturnsFalse_63) {
    edge_a.id_ = 4;
    edge_b.id_ = 4;
    EXPECT_FALSE(cmp(&edge_a, &edge_b));
}

TEST_F(EdgeCmpTest_63, ZeroIds_63) {
    edge_a.id_ = 0;
    edge_b.id_ = 0;
    EXPECT_FALSE(cmp(&edge_a, &edge_b));
}

TEST_F(EdgeCmpTest_63, ZeroLessThanOne_63) {
    edge_a.id_ = 0;
    edge_b.id_ = 1;
    EXPECT_TRUE(cmp(&edge_a, &edge_b));
}

TEST_F(EdgeCmpTest_63, OnNotLessThanZero_63) {
    edge_a.id_ = 1;
    edge_b.id_ = 0;
    EXPECT_FALSE(cmp(&edge_a, &edge_b));
}

TEST_F(EdgeCmpTest_63, LargeIds_63) {
    edge_a.id_ = 999999;
    edge_b.id_ = 1000000;
    EXPECT_TRUE(cmp(&edge_a, &edge_b));
}

TEST_F(EdgeCmpTest_63, LargeIdsReverse_63) {
    edge_a.id_ = 1000000;
    edge_b.id_ = 999999;
    EXPECT_FALSE(cmp(&edge_a, &edge_b));
}

TEST_F(EdgeCmpTest_63, SamePointerReturnsFalse_63) {
    edge_a.id_ = 42;
    EXPECT_FALSE(cmp(&edge_a, &edge_a));
}

TEST_F(EdgeCmpTest_63, ConsecutiveIds_63) {
    edge_a.id_ = 10;
    edge_b.id_ = 11;
    EXPECT_TRUE(cmp(&edge_a, &edge_b));
    EXPECT_FALSE(cmp(&edge_b, &edge_a));
}

TEST_F(EdgeCmpTest_63, StrictWeakOrdering_Irreflexive_63) {
    edge_a.id_ = 7;
    EXPECT_FALSE(cmp(&edge_a, &edge_a));
}

TEST_F(EdgeCmpTest_63, StrictWeakOrdering_Asymmetric_63) {
    edge_a.id_ = 3;
    edge_b.id_ = 9;
    // If a < b, then !(b < a)
    EXPECT_TRUE(cmp(&edge_a, &edge_b));
    EXPECT_FALSE(cmp(&edge_b, &edge_a));
}

TEST_F(EdgeCmpTest_63, StrictWeakOrdering_Transitive_63) {
    Edge edge_c;
    edge_a.id_ = 1;
    edge_b.id_ = 2;
    edge_c.id_ = 3;
    // a < b and b < c implies a < c
    EXPECT_TRUE(cmp(&edge_a, &edge_b));
    EXPECT_TRUE(cmp(&edge_b, &edge_c));
    EXPECT_TRUE(cmp(&edge_a, &edge_c));
}

TEST_F(EdgeCmpTest_63, MaxSizeTId_63) {
    edge_a.id_ = static_cast<size_t>(-1) - 1;
    edge_b.id_ = static_cast<size_t>(-1);
    EXPECT_TRUE(cmp(&edge_a, &edge_b));
    EXPECT_FALSE(cmp(&edge_b, &edge_a));
}
