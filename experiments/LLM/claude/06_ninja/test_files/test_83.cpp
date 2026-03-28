#include "gtest/gtest.h"
#include "deps_log.h"
#include "graph.h"

// Test fixture for DepsLog::Deps
class DepsTest_83 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test normal construction with positive node_count
TEST_F(DepsTest_83, ConstructWithPositiveNodeCount_83) {
    DepsLog::Deps deps(12345, 5);
    EXPECT_EQ(deps.mtime, 12345);
    EXPECT_EQ(deps.node_count, 5);
    EXPECT_NE(deps.nodes, nullptr);
}

// Test construction with zero node_count
TEST_F(DepsTest_83, ConstructWithZeroNodeCount_83) {
    DepsLog::Deps deps(0, 0);
    EXPECT_EQ(deps.mtime, 0);
    EXPECT_EQ(deps.node_count, 0);
    // nodes is allocated with new Node*[0], which is valid but may return non-null
    // We just verify it doesn't crash
}

// Test construction with mtime of zero
TEST_F(DepsTest_83, ConstructWithZeroMtime_83) {
    DepsLog::Deps deps(0, 3);
    EXPECT_EQ(deps.mtime, 0);
    EXPECT_EQ(deps.node_count, 3);
    EXPECT_NE(deps.nodes, nullptr);
}

// Test construction with negative mtime
TEST_F(DepsTest_83, ConstructWithNegativeMtime_83) {
    DepsLog::Deps deps(-1, 2);
    EXPECT_EQ(deps.mtime, -1);
    EXPECT_EQ(deps.node_count, 2);
    EXPECT_NE(deps.nodes, nullptr);
}

// Test construction with large mtime value
TEST_F(DepsTest_83, ConstructWithLargeMtime_83) {
    int64_t large_mtime = INT64_MAX;
    DepsLog::Deps deps(large_mtime, 1);
    EXPECT_EQ(deps.mtime, large_mtime);
    EXPECT_EQ(deps.node_count, 1);
    EXPECT_NE(deps.nodes, nullptr);
}

// Test that node_count is stored correctly
TEST_F(DepsTest_83, NodeCountStoredCorrectly_83) {
    DepsLog::Deps deps(100, 10);
    EXPECT_EQ(deps.node_count, 10);
}

// Test that nodes array can be written to and read from
TEST_F(DepsTest_83, NodesArrayAccessible_83) {
    DepsLog::Deps deps(100, 3);
    // Set nodes to nullptr values (we don't own real Node objects here)
    for (int i = 0; i < deps.node_count; ++i) {
        deps.nodes[i] = nullptr;
    }
    for (int i = 0; i < deps.node_count; ++i) {
        EXPECT_EQ(deps.nodes[i], nullptr);
    }
}

// Test construction with node_count of 1 (boundary)
TEST_F(DepsTest_83, ConstructWithSingleNode_83) {
    DepsLog::Deps deps(42, 1);
    EXPECT_EQ(deps.mtime, 42);
    EXPECT_EQ(deps.node_count, 1);
    EXPECT_NE(deps.nodes, nullptr);
    deps.nodes[0] = nullptr;
    EXPECT_EQ(deps.nodes[0], nullptr);
}

// Test destructor doesn't crash (implicitly tested by going out of scope)
TEST_F(DepsTest_83, DestructorDoesNotCrash_83) {
    {
        DepsLog::Deps deps(0, 5);
        for (int i = 0; i < 5; ++i) {
            deps.nodes[i] = nullptr;
        }
    }
    // If we reach here, destructor didn't crash
    SUCCEED();
}

// Test that mtime field is accessible and correct for various int64_t values
TEST_F(DepsTest_83, MtimeFieldVariousValues_83) {
    {
        DepsLog::Deps deps(INT64_MIN, 1);
        EXPECT_EQ(deps.mtime, INT64_MIN);
    }
    {
        DepsLog::Deps deps(0, 1);
        EXPECT_EQ(deps.mtime, 0);
    }
    {
        DepsLog::Deps deps(INT64_MAX, 1);
        EXPECT_EQ(deps.mtime, INT64_MAX);
    }
}

// Test construction with a moderately large node_count
TEST_F(DepsTest_83, ConstructWithModerateNodeCount_83) {
    DepsLog::Deps deps(999, 100);
    EXPECT_EQ(deps.node_count, 100);
    EXPECT_NE(deps.nodes, nullptr);
    // Verify we can write to all entries without crashing
    for (int i = 0; i < 100; ++i) {
        deps.nodes[i] = nullptr;
    }
}
