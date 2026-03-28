#include "gtest/gtest.h"
#include "graph.h"

class NodeTest_41 : public ::testing::Test {
};

// Normal operation: MarkDirty sets dirty flag to true from a clean state.
TEST_F(NodeTest_41, MarkDirtyFromCleanSetsDirtyTrue_41) {
    Node node("path", 0);

    // Ensure known starting state via public API.
    node.set_dirty(false);
    EXPECT_FALSE(node.dirty());

    node.MarkDirty();

    EXPECT_TRUE(node.dirty());
}

// Boundary: MarkDirty is idempotent when called multiple times.
TEST_F(NodeTest_41, MarkDirtyIsIdempotent_41) {
    Node node("path", 0);

    node.set_dirty(false);
    EXPECT_FALSE(node.dirty());

    node.MarkDirty();
    EXPECT_TRUE(node.dirty());
    bool dirty_after_first_call = node.dirty();

    node.MarkDirty();  // Call again; should remain dirty.
    EXPECT_TRUE(node.dirty());
    EXPECT_EQ(dirty_after_first_call, node.dirty());
}

// Boundary: Calling MarkDirty when already dirty keeps it dirty.
TEST_F(NodeTest_41, MarkDirtyKeepsAlreadyDirtyNodeDirty_41) {
    Node node("path", 0);

    node.set_dirty(true);
    EXPECT_TRUE(node.dirty());

    node.MarkDirty();

    EXPECT_TRUE(node.dirty());
}
