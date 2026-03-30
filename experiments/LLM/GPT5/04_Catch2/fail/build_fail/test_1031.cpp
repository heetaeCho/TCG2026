// File: tests/tracker_context_set_current_tracker_1031.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Use the real public interfaces from Catch2
#include <catch2/internal/catch_test_case_tracker.hpp>
#include <catch2/internal/catch_source_line_info.hpp>
#include <catch2/internal/catch_stringref.hpp>

using namespace Catch::TestCaseTracking;

// A minimal concrete tracker we can instantiate and pass by pointer.
// We do not rely on any internal behavior — just need an addressable object.
class DummyTracker_1031 : public ITracker {
public:
    // Construct with arbitrary, valid NameAndLocation and optional parent
    DummyTracker_1031(Catch::NameAndLocation&& nl, ITracker* parent = nullptr)
        : ITracker(CATCH_MOVE(nl), parent) {}

    // Do not override behavior; we keep it a black box.
    ~DummyTracker_1031() override = default;
};

// Test fixture
class TrackerContextSetCurrent_1031 : public ::testing::Test {
protected:
    TrackerContext ctx;

    static Catch::NameAndLocation makeNL(const char* name = "dummy.section") {
        return Catch::NameAndLocation{
            Catch::StringRef{name},
            Catch::SourceLineInfo{__FILE__, static_cast<std::size_t>(__LINE__)}
        };
    }
};

// Normal operation: setting a non-null tracker makes currentTracker() refer to it.
TEST_F(TrackerContextSetCurrent_1031, SetsAndReturnsSameTracker_1031) {
    DummyTracker_1031 t1{makeNL("t1")};
    ctx.setCurrentTracker(&t1);

    // Observable behavior: currentTracker() should return the same object
    ITracker& current = ctx.currentTracker();
    EXPECT_EQ(&current, &t1);
}

// Boundary: setting current tracker multiple times swaps to the latest.
TEST_F(TrackerContextSetCurrent_1031, CanUpdateMultipleTimes_1031) {
    DummyTracker_1031 t1{makeNL("t1")};
    DummyTracker_1031 t2{makeNL("t2")};
    DummyTracker_1031 t3{makeNL("t3")};

    ctx.setCurrentTracker(&t1);
    EXPECT_EQ(&ctx.currentTracker(), &t1);

    ctx.setCurrentTracker(&t2);
    EXPECT_EQ(&ctx.currentTracker(), &t2);

    ctx.setCurrentTracker(&t3);
    EXPECT_EQ(&ctx.currentTracker(), &t3);
}

// Exceptional/boundary: setting nullptr should be a permissible call,
// but since currentTracker() returns a reference, we must not dereference it
// after a nullptr set. We only verify the call does not throw or crash, and
// that a subsequent valid set restores a usable currentTracker().
TEST_F(TrackerContextSetCurrent_1031, NullThenValidIsUsable_1031) {
    // Calling with nullptr should not crash; we won't call currentTracker() here.
    ctx.setCurrentTracker(nullptr);

    DummyTracker_1031 t1{makeNL("t1")};
    ctx.setCurrentTracker(&t1);

    // After setting a valid tracker again, currentTracker() should be usable.
    EXPECT_EQ(&ctx.currentTracker(), &t1);
}
