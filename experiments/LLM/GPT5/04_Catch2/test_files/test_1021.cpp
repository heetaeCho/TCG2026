// File: tests/ITracker_AddChild_1021.tests.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "catch_amalgamated.hpp"  // Or the appropriate path that provides ITracker and NameAndLocation

using ::testing::NotNull;
using ::testing::IsNull;

namespace Catch {
namespace TestCaseTracking {

class ITracker_AddChild_Test : public ::testing::Test {
protected:
    // Helper: construct a NameAndLocation with a stable line info.
    static NameAndLocation makeNL(const std::string& name) {
        return NameAndLocation{name, SourceLineInfo{__FILE__, __LINE__}};
    }

    // Some builds have an alias ITrackerPtr already; if not, we alias it here.
    using ITrackerPtr = Catch::Detail::unique_ptr<ITracker>;

    // Minimal concrete tracker type if needed (inherits all behavior from ITracker).
    // We do not override any behavior — we treat ITracker as a black box.
    struct ConcreteTracker : ITracker {
        using ITracker::ITracker; // forward to ITracker(NameAndLocation&&, ITracker*)
        // No overrides — we test only public observable behavior.
    };
};

//
// Normal operation: adding a single child transfers ownership
// and marks the parent as having children.
//
TEST_F(ITracker_AddChild_Test, AddSingleChild_OwnershipTransferred_1021) { // TEST_ID = 1021
    ConcreteTracker parent{makeNL("parent"), /*parent*/nullptr};

    EXPECT_FALSE(parent.hasChildren()) << "Precondition: newly constructed parent should have no children";

    ITrackerPtr child{new ConcreteTracker{makeNL("child"), &parent}};
    ASSERT_TRUE(static_cast<bool>(child)) << "Precondition: child must be a valid non-null unique_ptr";

    parent.addChild(std::move(child));

    // Observable effects:
    // 1) Ownership should be transferred (moved-from unique_ptr becomes null).
    EXPECT_FALSE(static_cast<bool>(child)) << "After addChild(move), the source unique_ptr must be null";

    // 2) Parent now reports it has children (public observable behavior).
    EXPECT_TRUE(parent.hasChildren()) << "Parent should report it has children after addChild";
}

//
// Boundary: adding multiple children should be allowed;
// parent continues to report it has children; all ownership moves occur.
//
TEST_F(ITracker_AddChild_Test, AddMultipleChildren_AllOwnershipsTransferred_1021) { // TEST_ID = 1021
    ConcreteTracker parent{makeNL("parent"), nullptr};
    EXPECT_FALSE(parent.hasChildren());

    ITrackerPtr c1{new ConcreteTracker{makeNL("c1"), &parent}};
    ITrackerPtr c2{new ConcreteTracker{makeNL("c2"), &parent}};

    parent.addChild(std::move(c1));
    parent.addChild(std::move(c2));

    EXPECT_FALSE(static_cast<bool>(c1)) << "First child unique_ptr should be null after move";
    EXPECT_FALSE(static_cast<bool>(c2)) << "Second child unique_ptr should be null after move";
    EXPECT_TRUE(parent.hasChildren()) << "Parent should have children after adding multiple";
}

//
// Interaction verification via public lookup:
// If findChild(NameAndLocationRef) is part of the public interface,
// adding a child with a known name should make it discoverable.
// (If your build exposes NameAndLocationRef differently, adapt construction.)
//
TEST_F(ITracker_AddChild_Test, FindChild_ReturnsAddedChildByName_1021) { // TEST_ID = 1021
    ConcreteTracker parent{makeNL("parent"), nullptr};

    auto nlChild = makeNL("child-X");
    // Keep a copy of the name for constructing the lookup ref later.
    const std::string childName = nlChild.name;

    ITrackerPtr child{new ConcreteTracker{NameAndLocation{childName, nlChild.location}, &parent}};
    parent.addChild(std::move(child));

    // Construct a lookup ref; if your Catch2 version expects a different ctor,
    // adjust accordingly (e.g., NameAndLocationRef{childName, nlChild.location}).
    NameAndLocationRef lookupRef{childName, nlChild.location};

    ITracker* found = parent.findChild(lookupRef);
    EXPECT_THAT(found, NotNull()) << "findChild should return non-null for an added child with matching name/location";
}

//
// Edge behavior: moving a default-constructed (null) ITrackerPtr should be a no-op
// from the caller perspective (ownership is already null). This test only checks
// that the call is accepted and does not throw; it does not assert internal state.
//
TEST_F(ITracker_AddChild_Test, AddNullChildPointer_NoThrow_1021) { // TEST_ID = 1021
    ConcreteTracker parent{makeNL("parent"), nullptr};
    ITrackerPtr nullChild{}; // nullptr unique_ptr

    // The observable contract here is minimal: the function accepts rvalue unique_ptr.
    // We verify that calling it with a null unique_ptr does not throw.
    EXPECT_NO_THROW(parent.addChild(std::move(nullChild)));
    // We intentionally do NOT assert hasChildren(), as the behavior for null
    // children is not specified in the public contract.
}

} // namespace TestCaseTracking
} // namespace Catch
