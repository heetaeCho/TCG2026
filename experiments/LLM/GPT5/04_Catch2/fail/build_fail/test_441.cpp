// File: itracker_parent_tests_441.cpp
#include <gtest/gtest.h>

// Include the provided header with ITracker::parent() declaration
#include "Catch2/src/catch2/internal/catch_test_case_tracker.hpp"

namespace Catch { namespace TestCaseTracking {

// Minimal concrete subclass to enable instantiation for testing.
// We do not reimplement or infer any internal logic; we only use
// the protected constructor access to set up the parent relationship.
class TestableTracker : public ITracker {
public:
    explicit TestableTracker(ITracker* parentPtr) {
        // Only establish the relationship needed to observe parent().
        // No other behavior is touched/assumed.
        this->m_parent = parentPtr;
    }
    // Provide a virtual destructor since base has virtual destructor.
    ~TestableTracker() override = default;
};

}} // namespace Catch::TestCaseTracking

using Catch::TestCaseTracking::ITracker;
using Catch::TestCaseTracking::TestableTracker;

class ITrackerParentTest_441 : public ::testing::Test {
protected:
    // Helper that creates a tracker with a specific parent
    static TestableTracker MakeWithParent(ITracker* p) { return TestableTracker{p}; }
};

// [Normal] When constructed with a non-null parent, parent() returns the same pointer.
TEST_F(ITrackerParentTest_441, ParentReturnsSamePointerWhenSet_441) {
    TestableTracker parent(nullptr);
    TestableTracker child(&parent);

    ITracker* observed = child.parent();
    EXPECT_EQ(observed, &parent) << "parent() must return the exact parent pointer that was set";
}

// [Boundary] When constructed with nullptr, parent() returns nullptr.
TEST_F(ITrackerParentTest_441, ParentReturnsNullptrWhenNoParent_441) {
    TestableTracker leaf(nullptr);

    ITracker* observed = leaf.parent();
    EXPECT_EQ(observed, nullptr) << "parent() must return nullptr when no parent was provided";
}

// [Stability] Multiple calls to parent() are consistent (idempotent).
TEST_F(ITrackerParentTest_441, ParentResultIsStableAcrossCalls_441) {
    TestableTracker parent(nullptr);
    TestableTracker child(&parent);

    ITracker* first = child.parent();
    ITracker* second = child.parent();
    EXPECT_EQ(first, &parent);
    EXPECT_EQ(second, &parent);
    EXPECT_EQ(first, second) << "parent() should consistently return the same pointer across calls";
}

// [Const-correctness] parent() is callable on const objects and returns the same pointer.
TEST_F(ITrackerParentTest_441, ParentCallableOnConstObject_441) {
    TestableTracker parent(nullptr);
    const TestableTracker child_const(&parent);

    const ITracker* observed = child_const.parent();
    EXPECT_EQ(observed, &parent) << "parent() on const object should return the same parent pointer";
}
