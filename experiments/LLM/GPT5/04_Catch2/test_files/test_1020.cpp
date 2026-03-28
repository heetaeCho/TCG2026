// File: tests/ITracker_MarkAsNeedingAnotherRun_1020.cpp

#include <gtest/gtest.h>
#include <memory>
#include <string>

// Prefer the non-amalgamated header if available; otherwise include amalgamated.
#include <catch2/internal/catch_test_case_tracker.hpp>
// #include <catch_amalgamated.hpp> // fallback if your setup uses the amalgamated header

using namespace Catch;
using namespace Catch::TestCaseTracking;

namespace {

// Helper to create a dummy NameAndLocation.
// We avoid depending on internal fields, and just use the public constructor(s)
// that your codebase provides. If your NameAndLocation requires a SourceLineInfo,
// we pass __FILE__/__LINE__ in a minimal, observable-safe way.
inline NameAndLocation makeNameAndLocation(const std::string& name) {
    // These overloads exist in Catch2, but if your exact signature differs,
    // adjust the arguments while still treating it as a black box constructor.
    return NameAndLocation{name, SourceLineInfo{__FILE__, static_cast<std::size_t>(__LINE__)}};
}

// Small helper to construct a tracker instance.
// We do not peek into internals; we only use the public constructor.
inline std::unique_ptr<ITracker> makeTracker(const std::string& name, ITracker* parent = nullptr) {
    return std::unique_ptr<ITracker>(new ITracker(makeNameAndLocation(name), parent));
}

// Small helper to add a child by using only public APIs.
inline void addChildTracker(ITracker& parent, const std::string& childName) {
    auto child = std::unique_ptr<ITracker>(new ITracker(makeNameAndLocation(childName), &parent));
    parent.addChild(CATCH_MOVE(child));
}

} // namespace

// ------------------------- TESTS -------------------------

// Normal operation: calling markAsNeedingAnotherRun transitions the tracker into a state
// that (from the outside) is "not complete" and requires another run (i.e., remains open).
TEST(ITracker_MarkAnotherRun_1020, MarkSetsNeedsAnotherRun_1020) {
    auto t = makeTracker("root");
    // Pre-conditions should be observable via public predicates
    // (we don't assert exact initial state beyond "not complete").
    EXPECT_FALSE(t->isComplete());

    // Act
    t->markAsNeedingAnotherRun();

    // Assert observable behavior only
    EXPECT_FALSE(t->isComplete());              // should not be considered complete
    EXPECT_TRUE(t->isOpen());                   // remains open because it needs another run
    EXPECT_FALSE(t->isSuccessfullyCompleted()); // not a successful completion
}

// Boundary: idempotency — multiple calls should be safe and preserve the same externally
// observable behavior (still open, still not complete).
TEST(ITracker_MarkAnotherRun_1020, MultipleMarksAreIdempotent_1020) {
    auto t = makeTracker("root");

    t->markAsNeedingAnotherRun();
    // State after first mark
    EXPECT_TRUE(t->isOpen());
    EXPECT_FALSE(t->isComplete());
    EXPECT_FALSE(t->isSuccessfullyCompleted());

    // Call again — should not throw and should not regress to "complete"
    t->markAsNeedingAnotherRun();
    EXPECT_TRUE(t->isOpen());
    EXPECT_FALSE(t->isComplete());
    EXPECT_FALSE(t->isSuccessfullyCompleted());
}

// Interaction with children (verification of external interactions):
// Ensure that marking the tracker as needing another run does not alter child relationships,
// and lookups through the public API keep working.
TEST(ITracker_MarkAnotherRun_1020, ChildrenRemainIntactAfterMark_1020) {
    auto root = makeTracker("root");
    addChildTracker(*root, "childA");
    addChildTracker(*root, "childB");

    // Sanity: children are observable through hasChildren() and findChild()
    EXPECT_TRUE(root->hasChildren());
    auto* childA = root->findChild(NameAndLocationRef{makeNameAndLocation("childA")});
    auto* childB = root->findChild(NameAndLocationRef{makeNameAndLocation("childB")});
    EXPECT_NE(childA, nullptr);
    EXPECT_NE(childB, nullptr);

    // Act
    root->markAsNeedingAnotherRun();

    // Assert: external child relationships remain visible/unchanged
    EXPECT_TRUE(root->hasChildren());
    EXPECT_NE(root->findChild(NameAndLocationRef{makeNameAndLocation("childA")}), nullptr);
    EXPECT_NE(root->findChild(NameAndLocationRef{makeNameAndLocation("childB")}), nullptr);

    // And the root still needs another run (externally visible)
    EXPECT_TRUE(root->isOpen());
    EXPECT_FALSE(root->isComplete());
}

// Exceptional/error-ish case (observable): After marking as needing another run,
// closing should not report success. We do not assert *how* close() behaves internally,
// only that it does not convert the state into "successfully completed" immediately.
TEST(ITracker_MarkAnotherRun_1020, CloseAfterMarkDoesNotReportSuccess_1020) {
    auto t = makeTracker("root");
    t->markAsNeedingAnotherRun();

    // Act
    t->close();

    // Assert: do not infer internal logic; just verify the tracker does not suddenly
    // report successful completion as an observable outcome.
    EXPECT_FALSE(t->isSuccessfullyCompleted());
}

