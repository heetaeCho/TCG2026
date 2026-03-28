#include "graph.h"

#include <gtest/gtest.h>

class NodeResetStateTest_31 : public ::testing::Test {
protected:
    NodeResetStateTest_31()
        : node_("path/to/file", 0) {}

    Node node_;
};

// ResetState on a freshly constructed node should keep its initial observable state.
TEST_F(NodeResetStateTest_31, ResetStateOnPristineNodeKeepsState_31) {
    TimeStamp initial_mtime = node_.mtime();
    bool initial_status_known = node_.status_known();
    bool initial_exists = node_.exists();
    bool initial_dirty = node_.dirty();

    node_.ResetState();

    EXPECT_EQ(node_.mtime(), initial_mtime);
    EXPECT_EQ(node_.status_known(), initial_status_known);
    EXPECT_EQ(node_.exists(), initial_exists);
    EXPECT_EQ(node_.dirty(), initial_dirty);
}

// After mutating mtime, existence, and dirty flags, ResetState should restore
// them to the same observable state as right after construction.
TEST_F(NodeResetStateTest_31, ResetStateRestoresConstructorState_31) {
    // Record the initial observable state.
    TimeStamp initial_mtime = node_.mtime();
    bool initial_status_known = node_.status_known();
    bool initial_exists = node_.exists();
    bool initial_dirty = node_.dirty();

    // Mutate the node via public interface.
    TimeStamp new_mtime = initial_mtime == static_cast<TimeStamp>(123456)
                              ? static_cast<TimeStamp>(654321)
                              : static_cast<TimeStamp>(123456);
    node_.UpdatePhonyMtime(new_mtime);
    node_.MarkMissing();
    node_.MarkDirty();

    // Verify that state actually changed.
    EXPECT_NE(node_.mtime(), initial_mtime);
    EXPECT_NE(node_.status_known(), initial_status_known);
    EXPECT_NE(node_.dirty(), initial_dirty);
    // exists() may or may not differ depending on implementation, so we do not
    // assert inequality here.

    // Now reset and expect original observable state.
    node_.ResetState();

    EXPECT_EQ(node_.mtime(), initial_mtime);
    EXPECT_EQ(node_.status_known(), initial_status_known);
    EXPECT_EQ(node_.exists(), initial_exists);
    EXPECT_EQ(node_.dirty(), initial_dirty);
}

// ResetState should be idempotent: calling it multiple times, even after
// repeated mutations, should always bring the node back to the same state.
TEST_F(NodeResetStateTest_31, ResetStateIsIdempotentAfterMultipleMutations_31) {
    TimeStamp initial_mtime = node_.mtime();
    bool initial_status_known = node_.status_known();
    bool initial_exists = node_.exists();
    bool initial_dirty = node_.dirty();

    // First round of mutations.
    node_.UpdatePhonyMtime(static_cast<TimeStamp>(111111));
    node_.MarkDirty();
    node_.ResetState();

    EXPECT_EQ(node_.mtime(), initial_mtime);
    EXPECT_EQ(node_.status_known(), initial_status_known);
    EXPECT_EQ(node_.exists(), initial_exists);
    EXPECT_EQ(node_.dirty(), initial_dirty);

    // Second round of mutations with different pattern.
    node_.UpdatePhonyMtime(static_cast<TimeStamp>(222222));
    node_.MarkMissing();
    node_.set_dirty(true);

    // Ensure state changed before reset.
    EXPECT_NE(node_.mtime(), initial_mtime);
    EXPECT_NE(node_.dirty(), initial_dirty);

    node_.ResetState();

    EXPECT_EQ(node_.mtime(), initial_mtime);
    EXPECT_EQ(node_.status_known(), initial_status_known);
    EXPECT_EQ(node_.exists(), initial_exists);
    EXPECT_EQ(node_.dirty(), initial_dirty);
}
