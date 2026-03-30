// File: tests/test_iTracker_openChild_1027.cpp
#include <gtest/gtest.h>

#include "catch2/internal/catch_test_case_tracker.hpp"  // Uses the real public interface

using namespace Catch::TestCaseTracking;

// A minimal concrete tracker so we can instantiate ITracker for tests.
// We do not re-implement any internal logic. We only implement required
// virtuals in a way that does NOT affect `openChild` behavior.
class MinimalTracker_1027 : public ITracker {
public:
    // Helper to make a trivial NameAndLocation for test use.
    static NameAndLocation makeNL(const char* name = "T", const char* file = "f.cpp", int line = 1) {
        return NameAndLocation{name, SourceLineInfo{file, line}};
    }

    explicit MinimalTracker_1027(NameAndLocation&& nl, ITracker* parent = nullptr)
        : ITracker(std::move(nl), parent) {}

    // Implement required virtuals as pass-throughs or safe no-ops.
    // These should not influence openChild() semantics.
    ~MinimalTracker_1027() override = default;
    bool isComplete() override { return ITracker::isComplete(); }
    void close() override { ITracker::close(); }
    void fail() override { ITracker::fail(); }

    // Keep default “not a section/generator” answers via base
    // (or explicitly return base values if required by signature).
    bool isSectionTracker() const override { return ITracker::isSectionTracker(); }
    bool isGeneratorTracker() const override { return ITracker::isGeneratorTracker(); }
};

// ------------------------------------------------------------------
// Normal operation: calling openChild on a tracker without a parent
// should not throw and should reflect as "started/open" via public API.
// ------------------------------------------------------------------
TEST(ITrackerOpenChild_1027, OpenChild_NoParent_SetsStartedAndOrOpen_1027) {
    MinimalTracker_1027 t(MinimalTracker_1027::makeNL("root"));

    // Precondition: not started/open yet (observable via public API)
    EXPECT_FALSE(t.hasStarted());
    EXPECT_FALSE(t.isOpen());

    // Act
    t.openChild();

    // Postconditions visible via public API
    // We assert that the tracker has started and is open,
    // which are observable effects of beginning child execution.
    EXPECT_TRUE(t.hasStarted());
    EXPECT_TRUE(t.isOpen());
}

// ------------------------------------------------------------------
// Interaction: when a child has a parent, calling openChild on the
// child should propagate to the parent (observable: parent's state).
// ------------------------------------------------------------------
TEST(ITrackerOpenChild_1027, OpenChild_PropagatesToParent_1027) {
    MinimalTracker_1027 parent(MinimalTracker_1027::makeNL("parent"));
    MinimalTracker_1027 child(MinimalTracker_1027::makeNL("child"), &parent);

    // Precondition checks
    EXPECT_FALSE(parent.hasStarted());
    EXPECT_FALSE(parent.isOpen());
    EXPECT_FALSE(child.hasStarted());
    EXPECT_FALSE(child.isOpen());

    // Act
    child.openChild();

    // Observable effects on both child and parent
    EXPECT_TRUE(child.hasStarted());
    EXPECT_TRUE(child.isOpen());

    EXPECT_TRUE(parent.hasStarted());
    EXPECT_TRUE(parent.isOpen());
}

// ------------------------------------------------------------------
// Boundary/idempotency: calling openChild multiple times should not
// regress or cause additional observable side-effects beyond "open".
// ------------------------------------------------------------------
TEST(ITrackerOpenChild_1027, OpenChild_IsIdempotent_1027) {
    MinimalTracker_1027 t(MinimalTracker_1027::makeNL("once"));

    // First call transitions to an "open/started" state.
    t.openChild();
    EXPECT_TRUE(t.hasStarted());
    EXPECT_TRUE(t.isOpen());

    // Second call should not regress nor throw.
    EXPECT_NO_THROW(t.openChild());
    EXPECT_TRUE(t.hasStarted());
    EXPECT_TRUE(t.isOpen());
}

// ------------------------------------------------------------------
// Deep propagation: in a chain (grandchild -> child -> parent),
// openChild on the deepest tracker should propagate up to the root.
// ------------------------------------------------------------------
TEST(ITrackerOpenChild_1027, OpenChild_PropagatesThroughChain_1027) {
    MinimalTracker_1027 root(MinimalTracker_1027::makeNL("root"));
    MinimalTracker_1027 mid(MinimalTracker_1027::makeNL("mid"), &root);
    MinimalTracker_1027 leaf(MinimalTracker_1027::makeNL("leaf"), &mid);

    // Precondition: all closed
    EXPECT_FALSE(root.hasStarted()); EXPECT_FALSE(root.isOpen());
    EXPECT_FALSE(mid.hasStarted());  EXPECT_FALSE(mid.isOpen());
    EXPECT_FALSE(leaf.hasStarted()); EXPECT_FALSE(leaf.isOpen());

    // Act
    leaf.openChild();

    // Observable: all should now be started/open via public API
    EXPECT_TRUE(leaf.hasStarted()); EXPECT_TRUE(leaf.isOpen());
    EXPECT_TRUE(mid.hasStarted());  EXPECT_TRUE(mid.isOpen());
    EXPECT_TRUE(root.hasStarted()); EXPECT_TRUE(root.isOpen());
}
