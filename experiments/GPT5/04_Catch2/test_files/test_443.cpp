// File: tests/i_tracker_has_children_443_tests.cpp

#include <gtest/gtest.h>
#include <memory>
#include "catch2/internal/catch_test_case_tracker.hpp"

using Catch::TestCaseTracking::ITracker;

namespace {

// Minimal concrete tracker used only to create instances for tests.
// We do NOT touch any protected/private state; we only rely on public API.
struct DummyTracker : ITracker {
    using NameAndLocation   = decltype(std::declval<ITracker>().nameAndLocation()); // for type discovery
    using NameAndLocation_t = std::remove_reference_t<std::remove_cv_t<NameAndLocation>>;

    // Helper to make a NameAndLocation without depending on internal macros.
    // In Catch2, NameAndLocation typically stores a name and a SourceLineInfo.
    static NameAndLocation_t MakeNAL(const char* name = "dummy") {
        // Construct SourceLineInfo with arbitrary, stable values.
        // The concrete type lives in Catch2 and is available via ADL/headers.
        // We avoid assumptions about macros and pass simple values.
        Catch::SourceLineInfo sli{"i_tracker_has_children_443_tests.cpp", 1};
        return NameAndLocation_t{name, sli};
    }

    explicit DummyTracker(ITracker* parent = nullptr)
        : ITracker(MakeNAL(), parent) {}

    // Virtuals can keep base defaults; no overrides needed for these tests.
};

} // namespace

// ========== Tests ==========

// [443] No children by default -> hasChildren() is false
TEST(ITracker_HasChildren_443, DefaultIsFalse_443) {
    DummyTracker t; // no parent, no children attached
    EXPECT_FALSE(t.hasChildren());
}

// [443] After adding a single child via public API -> hasChildren() is true
TEST(ITracker_HasChildren_443, BecomesTrueAfterAddingOneChild_443) {
    DummyTracker parent;

    auto child = std::make_unique<DummyTracker>(&parent);
    parent.addChild(std::move(child));

    EXPECT_TRUE(parent.hasChildren());
}

// [443] After adding multiple children -> hasChildren() stays true
TEST(ITracker_HasChildren_443, StaysTrueWithMultipleChildren_443) {
    DummyTracker parent;

    parent.addChild(std::make_unique<DummyTracker>(&parent));
    parent.addChild(std::make_unique<DummyTracker>(&parent));
    parent.addChild(std::make_unique<DummyTracker>(&parent));

    EXPECT_TRUE(parent.hasChildren());
}

// [443] Nested children do not affect sibling state; each tracker reports based on its own children
TEST(ITracker_HasChildren_443, NestedChildrenAffectOnlyOwner_443) {
    DummyTracker parent;

    // Add a single child
    auto child = std::make_unique<DummyTracker>(&parent);
    DummyTracker* childRaw = child.get();
    parent.addChild(std::move(child));

    ASSERT_TRUE(parent.hasChildren()) << "Parent should see its single child";
    EXPECT_FALSE(childRaw->hasChildren()) << "Child initially has no children";

    // Now add a grandchild to the child; parent's hasChildren remains true,
    // child's hasChildren becomes true (owner-based reporting).
    auto grandChild = std::make_unique<DummyTracker>(childRaw);
    childRaw->addChild(std::move(grandChild));

    EXPECT_TRUE(parent.hasChildren());
    EXPECT_TRUE(childRaw->hasChildren());
}
