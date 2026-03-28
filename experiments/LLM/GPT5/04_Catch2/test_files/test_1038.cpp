// File: test_sectiontracker_acquire_1038.cpp

#include <gtest/gtest.h>
#include <memory>
#include <string>

// Include the headers providing the tested interfaces.
// Adjust include paths to your project layout if needed.
#include "catch2/internal/catch_test_case_tracker.hpp"
#include "catch2/internal/catch_stringref.hpp"

using namespace Catch::TestCaseTracking;
using Catch::StringRef;

namespace {

// Minimal helper to build NameAndLocation/Ref without relying on internals.
// Assuming SourceLineInfo is constructible from file & line (typical in Catch2).
// If your project provides a different constructor/helper, adapt accordingly.
static inline SourceLineInfo makeLine(const char* file = "file.cpp", std::size_t line = 123) {
    return SourceLineInfo{ file, static_cast<std::size_t>(line) };
}

static inline NameAndLocation makeNAL(const std::string& name,
                                      const char* file = "file.cpp",
                                      std::size_t line = 123) {
    NameAndLocation nal{ StringRef{name}, makeLine(file, line) };
    return nal;
}

static inline NameAndLocationRef makeNALRef(const std::string& name,
                                            const char* file = "file.cpp",
                                            std::size_t line = 123) {
    return NameAndLocationRef{ StringRef{name}, makeLine(file, line) };
}

// Simple holder for a root SectionTracker we can use as current tracker.
struct RootSectionHolder {
    TrackerContext ctx;
    std::unique_ptr<SectionTracker> root; // keep ownership if we need
    SectionTracker* rootPtr = nullptr;

    explicit RootSectionHolder(const std::string& name = "Root") {
        // Build a root SectionTracker and set it as the current tracker
        root = std::make_unique<SectionTracker>( makeNAL(name), ctx, /*parent*/ nullptr );
        rootPtr = root.get();
        // TrackerContext expects to manage the current tracker (interface is public),
        // we set it directly so acquire() sees our root as current.
        ctx.setCurrentTracker(rootPtr);
    }
};

} // namespace

// ---- Tests ----

TEST(SectionTrackerAcquire_1038, ReusesExistingChildWhenFound_1038) {
    RootSectionHolder env("Top");

    // Prepare a child with a given name, add it under current tracker (root)
    const std::string childName = "ExistingSection";
    auto preExisting = std::make_unique<SectionTracker>( makeNAL(childName), env.ctx, env.rootPtr );
    SectionTracker* preExistingPtr = preExisting.get();
    // Attach via the public API only
    env.rootPtr->addChild( std::move(preExisting) );

    // Sanity: current tracker should be our root, and it can find the child
    ASSERT_EQ(&env.ctx.currentTracker(), env.rootPtr);
    ITracker* foundBefore = env.rootPtr->findChild( makeNALRef(childName) );
    ASSERT_NE(foundBefore, nullptr);
    ASSERT_EQ(foundBefore, preExistingPtr);

    // Call acquire for the same name — should return the same tracker (reuse)
    SectionTracker& acquired =
        SectionTracker::acquire(env.ctx, makeNALRef(childName));

    // We expect the very same instance to be returned
    EXPECT_EQ(&acquired, preExistingPtr);

    // The child's parent should be the root current tracker (observable via public API)
    EXPECT_EQ(acquired.parent(), env.rootPtr);

    // And it should still be discoverable via findChild
    ITracker* foundAfter = env.rootPtr->findChild( makeNALRef(childName) );
    EXPECT_EQ(foundAfter, &acquired);
}

TEST(SectionTrackerAcquire_1038, CreatesAndAttachesNewChildWhenMissing_1038) {
    RootSectionHolder env("Top");

    const std::string newChildName = "BrandNewSection";

    // Verify no child with that name exists beforehand
    ITracker* none = env.rootPtr->findChild( makeNALRef(newChildName) );
    ASSERT_EQ(none, nullptr);

    // Ensure we are in a normal (not-completed) cycle so acquire may try to open the section.
    // We do not assert on "open" state, as that would depend on internal behavior.
    // The important observable behavior here is that a new child is created and attached.
    SectionTracker& acquired =
        SectionTracker::acquire(env.ctx, makeNALRef(newChildName));

    // The returned tracker must now be discoverable as a child of current
    ITracker* found = env.rootPtr->findChild( makeNALRef(newChildName) );
    ASSERT_NE(found, nullptr);
    EXPECT_EQ(found, &acquired);

    // Parent link is observable
    EXPECT_EQ(acquired.parent(), env.rootPtr);

    // Name is observable through public getter
    EXPECT_TRUE(acquired.nameAndLocation().name == StringRef(newChildName));
}

TEST(SectionTrackerAcquire_1038, MultipleChildrenWithDifferentNamesAreIndependent_1038) {
    RootSectionHolder env("Top");

    const std::string nameA = "SectionA";
    const std::string nameB = "SectionB";

    // Acquire first (creates it)
    SectionTracker& a =
        SectionTracker::acquire(env.ctx, makeNALRef(nameA));
    // Acquire second (creates it)
    SectionTracker& b =
        SectionTracker::acquire(env.ctx, makeNALRef(nameB));

    // Both should be retrievable independently
    ITracker* foundA = env.rootPtr->findChild( makeNALRef(nameA) );
    ITracker* foundB = env.rootPtr->findChild( makeNALRef(nameB) );

    ASSERT_NE(foundA, nullptr);
    ASSERT_NE(foundB, nullptr);

    EXPECT_EQ(foundA, &a);
    EXPECT_EQ(foundB, &b);

    // And they should not alias
    EXPECT_NE(&a, &b);
    EXPECT_EQ(a.parent(), env.rootPtr);
    EXPECT_EQ(b.parent(), env.rootPtr);
}

