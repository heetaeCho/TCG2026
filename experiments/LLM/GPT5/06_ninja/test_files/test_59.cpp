// File: edge_outputs_ready_test_59.cc

#include "graph.h"

#include <gtest/gtest.h>

// Fixture for Edge outputs_ready tests (TEST_ID = 59)
class EdgeOutputsReadyTest_59 : public ::testing::Test {
protected:
    Edge edge_;
};

// Normal operation: default-constructed Edge should have outputs_ready() == false.
TEST_F(EdgeOutputsReadyTest_59, DefaultIsFalse_59) {
    EXPECT_FALSE(edge_.outputs_ready());
}

// Normal operation: when outputs_ready_ is set to true, outputs_ready() should return true.
TEST_F(EdgeOutputsReadyTest_59, ReturnsTrueWhenFlagTrue_59) {
    edge_.outputs_ready_ = true;
    EXPECT_TRUE(edge_.outputs_ready());
}

// Boundary-like behavior for a boolean: outputs_ready() should reflect multiple state changes.
TEST_F(EdgeOutputsReadyTest_59, ReflectsMultipleChanges_59) {
    edge_.outputs_ready_ = false;
    EXPECT_FALSE(edge_.outputs_ready());

    edge_.outputs_ready_ = true;
    EXPECT_TRUE(edge_.outputs_ready());

    edge_.outputs_ready_ = false;
    EXPECT_FALSE(edge_.outputs_ready());
}

// Const-correctness: outputs_ready() should be callable on a const Edge instance.
TEST_F(EdgeOutputsReadyTest_59, WorksOnConstInstance_59) {
    edge_.outputs_ready_ = true;
    const Edge& const_edge_ref = edge_;
    EXPECT_TRUE(const_edge_ref.outputs_ready());
}
