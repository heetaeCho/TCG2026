// File: missing_deps_had_missing_deps_test_123.cc

#include <gtest/gtest.h>

#include "missing_deps.h"

// Test fixture for MissingDependencyScanner-related tests.
class MissingDependencyScannerTest_123 : public ::testing::Test {
protected:
    MissingDependencyScannerTest_123()
        : scanner_(nullptr, nullptr, nullptr, nullptr) // delegate, deps_log, state, disk_interface
    {
    }

    MissingDependencyScanner scanner_;
};

// Verifies that HadMissingDeps() returns false when there are no missing deps recorded.
TEST_F(MissingDependencyScannerTest_123, HadMissingDepsReturnsFalseWhenNoMissingDeps_123) {
    // Precondition: freshly constructed scanner should have no missing dependencies.
    EXPECT_TRUE(scanner_.nodes_missing_deps_.empty());

    // Behavior: HadMissingDeps() should report false.
    EXPECT_FALSE(scanner_.HadMissingDeps());
}

// Verifies that HadMissingDeps() returns true when at least one missing dep is present.
TEST_F(MissingDependencyScannerTest_123, HadMissingDepsReturnsTrueWhenMissingDepsPresent_123) {
    // Arrange: insert a dummy Node* into nodes_missing_deps_ to simulate a missing dependency.
    Node* fake_node = reinterpret_cast<Node*>(0x1);  // opaque, never dereferenced
    scanner_.nodes_missing_deps_.insert(fake_node);

    // Sanity check on observable state used by the method.
    EXPECT_FALSE(scanner_.nodes_missing_deps_.empty());

    // Behavior: HadMissingDeps() should now report true.
    EXPECT_TRUE(scanner_.HadMissingDeps());
}

// Verifies that HadMissingDeps() reflects changes when missing deps are added then cleared.
TEST_F(MissingDependencyScannerTest_123, HadMissingDepsReflectsClearedMissingDeps_123) {
    // Arrange: add a dummy missing dependency.
    Node* fake_node = reinterpret_cast<Node*>(0x1);
    scanner_.nodes_missing_deps_.insert(fake_node);
    ASSERT_TRUE(scanner_.HadMissingDeps());  // should be true after insertion

    // Act: clear the recorded missing dependencies.
    scanner_.nodes_missing_deps_.clear();

    // Assert: HadMissingDeps() should go back to false.
    EXPECT_FALSE(scanner_.HadMissingDeps());
}
