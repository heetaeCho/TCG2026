// File: unique_ptr_release_tests_28.cpp
#include <gtest/gtest.h>

// Include the interface under test (treat as black box)
#include "Catch2/src/catch2/internal/catch_unique_ptr.hpp"

using Catch::Detail::unique_ptr;

namespace {

// A small helper to observe lifetime via externally visible side effects.
struct Tracker {
    static int alive;
    static int destroyed;

    explicit Tracker(int /*id*/ = 0) { ++alive; }
    ~Tracker() { ++destroyed; --alive; }

    // Disallow copying to avoid accidental duplicates in tests.
    Tracker(const Tracker&) = delete;
    Tracker& operator=(const Tracker&) = delete;
};

int Tracker::alive = 0;
int Tracker::destroyed = 0;

struct UniquePtrReleaseTest_28 : ::testing::Test {
    void SetUp() override {
        // Reset counters before each test to make observations independent.
        Tracker::alive = 0;
        Tracker::destroyed = 0;
    }
};

} // namespace

// Normal operation: release returns the raw pointer and resets ownership.
TEST_F(UniquePtrReleaseTest_28, ReleaseReturnsPointerAndResets_28) {
    unique_ptr<Tracker> uptr(new Tracker());

    // Precondition: one object is alive and owned.
    EXPECT_EQ(Tracker::alive, 1);
    EXPECT_TRUE(static_cast<bool>(uptr));

    Tracker* before = uptr.get();
    Tracker* released = uptr.release();

    // Returned pointer is the previously owned one.
    EXPECT_EQ(released, before);

    // After release, unique_ptr no longer owns anything.
    EXPECT_FALSE(static_cast<bool>(uptr));
    EXPECT_EQ(uptr.get(), nullptr);

    // Object should not be destroyed by release itself.
    EXPECT_EQ(Tracker::destroyed, 0);
    EXPECT_EQ(Tracker::alive, 1);

    // Manual delete of the released resource should destroy exactly once.
    delete released;
    EXPECT_EQ(Tracker::destroyed, 1);
    EXPECT_EQ(Tracker::alive, 0);
}

// Boundary: releasing a null unique_ptr returns nullptr and keeps it null.
TEST_F(UniquePtrReleaseTest_28, ReleaseOnNullReturnsNull_28) {
    unique_ptr<Tracker> uptr(nullptr);

    EXPECT_FALSE(static_cast<bool>(uptr));
    EXPECT_EQ(uptr.get(), nullptr);

    Tracker* released = uptr.release();
    EXPECT_EQ(released, nullptr);
    EXPECT_FALSE(static_cast<bool>(uptr));
    EXPECT_EQ(uptr.get(), nullptr);

    // No objects were created or destroyed.
    EXPECT_EQ(Tracker::alive, 0);
    EXPECT_EQ(Tracker::destroyed, 0);
}

// Ownership interaction: after move, release operates on the new owner only.
TEST_F(UniquePtrReleaseTest_28, ReleaseAfterMoveTransfersOwnership_28) {
    unique_ptr<Tracker> src(new Tracker());
    EXPECT_TRUE(static_cast<bool>(src));
    EXPECT_EQ(Tracker::alive, 1);

    unique_ptr<Tracker> dst(std::move(src));
    EXPECT_FALSE(static_cast<bool>(src)); // moved-from should be empty (observable)
    EXPECT_TRUE(static_cast<bool>(dst));

    // Release from the new owner.
    Tracker* released = dst.release();
    EXPECT_NE(released, nullptr);
    EXPECT_FALSE(static_cast<bool>(dst));
    EXPECT_FALSE(static_cast<bool>(src)); // remains empty

    // Not destroyed yet; still alive until we delete.
    EXPECT_EQ(Tracker::destroyed, 0);
    EXPECT_EQ(Tracker::alive, 1);

    delete released;
    EXPECT_EQ(Tracker::destroyed, 1);
    EXPECT_EQ(Tracker::alive, 0);
}

// Boundary: calling release() twice should return the pointer once, then nullptr.
TEST_F(UniquePtrReleaseTest_28, ReleaseTwiceSecondIsNull_28) {
    unique_ptr<Tracker> uptr(new Tracker());
    EXPECT_EQ(Tracker::alive, 1);

    Tracker* first = uptr.release();
    EXPECT_NE(first, nullptr);
    EXPECT_FALSE(static_cast<bool>(uptr));

    Tracker* second = uptr.release();
    EXPECT_EQ(second, nullptr); // already empty

    // Clean up the first released pointer; observe single destruction.
    delete first;
    EXPECT_EQ(Tracker::destroyed, 1);
    EXPECT_EQ(Tracker::alive, 0);
}

// Safety: after release and manual delete, unique_ptr dtor must not double-delete.
TEST_F(UniquePtrReleaseTest_28, NoDoubleDeleteAfterRelease_28) {
    Tracker* raw = nullptr;
    {
        unique_ptr<Tracker> uptr(new Tracker());
        raw = uptr.release(); // relinquish ownership
        EXPECT_FALSE(static_cast<bool>(uptr));
        EXPECT_NE(raw, nullptr);
        // Manually destroy now while uptr is still in scope.
        delete raw;
        raw = nullptr;
        EXPECT_EQ(Tracker::destroyed, 1);
        EXPECT_EQ(Tracker::alive, 0);
    } // uptr dtor runs here; must not attempt to delete again.

    // Still exactly one destruction.
    EXPECT_EQ(Tracker::destroyed, 1);
    EXPECT_EQ(Tracker::alive, 0);
}
