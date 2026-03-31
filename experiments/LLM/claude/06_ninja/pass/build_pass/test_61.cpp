#include "gtest/gtest.h"
#include "graph.h"

class EdgeIsOrderOnlyTest_61 : public ::testing::Test {
protected:
    Edge edge;

    void SetUp() override {
        // Reset edge state
        edge.inputs_.clear();
        edge.order_only_deps_ = 0;
    }

    void AddInputs(size_t count) {
        for (size_t i = 0; i < count; ++i) {
            edge.inputs_.push_back(nullptr);
        }
    }
};

// Test: When there are no order_only_deps, no index should be order-only
TEST_F(EdgeIsOrderOnlyTest_61, NoOrderOnlyDeps_AllInputsAreNotOrderOnly_61) {
    AddInputs(5);
    edge.order_only_deps_ = 0;

    for (size_t i = 0; i < 5; ++i) {
        EXPECT_FALSE(edge.is_order_only(i)) << "Index " << i << " should not be order-only";
    }
}

// Test: When all inputs are order-only deps
TEST_F(EdgeIsOrderOnlyTest_61, AllInputsAreOrderOnly_61) {
    AddInputs(3);
    edge.order_only_deps_ = 3;

    for (size_t i = 0; i < 3; ++i) {
        EXPECT_TRUE(edge.is_order_only(i)) << "Index " << i << " should be order-only";
    }
}

// Test: When only the last input is order-only
TEST_F(EdgeIsOrderOnlyTest_61, LastInputIsOrderOnly_61) {
    AddInputs(4);
    edge.order_only_deps_ = 1;

    // Indices 0, 1, 2 should NOT be order-only
    EXPECT_FALSE(edge.is_order_only(0));
    EXPECT_FALSE(edge.is_order_only(1));
    EXPECT_FALSE(edge.is_order_only(2));

    // Index 3 (last) should be order-only
    EXPECT_TRUE(edge.is_order_only(3));
}

// Test: Boundary - index exactly at the boundary between non-order-only and order-only
TEST_F(EdgeIsOrderOnlyTest_61, BoundaryIndex_61) {
    AddInputs(6);
    edge.order_only_deps_ = 2;

    // inputs_.size() - order_only_deps_ = 6 - 2 = 4
    // Indices 0-3 are not order-only, indices 4-5 are order-only

    EXPECT_FALSE(edge.is_order_only(3)); // Last non-order-only
    EXPECT_TRUE(edge.is_order_only(4));  // First order-only
    EXPECT_TRUE(edge.is_order_only(5));  // Second order-only
}

// Test: Single input that is order-only
TEST_F(EdgeIsOrderOnlyTest_61, SingleInputIsOrderOnly_61) {
    AddInputs(1);
    edge.order_only_deps_ = 1;

    EXPECT_TRUE(edge.is_order_only(0));
}

// Test: Single input that is NOT order-only
TEST_F(EdgeIsOrderOnlyTest_61, SingleInputIsNotOrderOnly_61) {
    AddInputs(1);
    edge.order_only_deps_ = 0;

    EXPECT_FALSE(edge.is_order_only(0));
}

// Test: Multiple inputs with some order-only - check each index
TEST_F(EdgeIsOrderOnlyTest_61, MultipleInputsMixedOrderOnly_61) {
    AddInputs(10);
    edge.order_only_deps_ = 3;

    // inputs_.size() - order_only_deps_ = 10 - 3 = 7
    // Indices 0-6 are not order-only, indices 7-9 are order-only

    for (size_t i = 0; i < 7; ++i) {
        EXPECT_FALSE(edge.is_order_only(i)) << "Index " << i << " should not be order-only";
    }
    for (size_t i = 7; i < 10; ++i) {
        EXPECT_TRUE(edge.is_order_only(i)) << "Index " << i << " should be order-only";
    }
}

// Test: Two inputs, one order-only
TEST_F(EdgeIsOrderOnlyTest_61, TwoInputsOneOrderOnly_61) {
    AddInputs(2);
    edge.order_only_deps_ = 1;

    EXPECT_FALSE(edge.is_order_only(0));
    EXPECT_TRUE(edge.is_order_only(1));
}

// Test: Large number of inputs with order-only at the end
TEST_F(EdgeIsOrderOnlyTest_61, LargeInputSet_61) {
    AddInputs(100);
    edge.order_only_deps_ = 25;

    // Boundary is at index 75
    EXPECT_FALSE(edge.is_order_only(74));
    EXPECT_TRUE(edge.is_order_only(75));
    EXPECT_TRUE(edge.is_order_only(99));
}
