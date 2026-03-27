// unique_ptr_swap_tests_30.cpp
#include <gtest/gtest.h>
#include <utility> // for std::swap and ADL
// Adjust include path as needed:
#include "catch2/internal/catch_unique_ptr.hpp"

using Catch::Detail::unique_ptr;

// Helper type to observe destruction & basic identity.
struct Tracker {
    static int destroyed;
    static int live;

    int tag;

    explicit Tracker(int t) : tag(t) { ++live; }
    ~Tracker() { ++destroyed; --live; }

    int GetTag() const { return tag; }

    static void ResetCounts() { destroyed = 0; live = 0; }
};
int Tracker::destroyed = 0;
int Tracker::live = 0;

class UniquePtrSwapTest_30 : public ::testing::Test {
protected:
    void SetUp() override { Tracker::ResetCounts(); }
};

//
// Normal operation
//
TEST_F(UniquePtrSwapTest_30, BasicOwnershipExchange_30) {
    unique_ptr<Tracker> a(new Tracker(1));
    unique_ptr<Tracker> b(new Tracker(2));

    Tracker* p1 = a.get();
    Tracker* p2 = b.get();

    // Prefer ADL; std::swap is okay too because ADL will find friend swap.
    using std::swap;
    swap(a, b);

    EXPECT_EQ(a.get(), p2);
    EXPECT_EQ(b.get(), p1);
    ASSERT_TRUE(a);
    ASSERT_TRUE(b);
    EXPECT_EQ(a->GetTag(), 2);
    EXPECT_EQ((*b).GetTag(), 1);
    EXPECT_EQ(Tracker::destroyed, 0);
    EXPECT_EQ(Tracker::live, 2);
}

//
// Boundary: swap with nullptr
//
TEST_F(UniquePtrSwapTest_30, SwapWithNullptr_30) {
    unique_ptr<Tracker> empty;                // nullptr
    unique_ptr<Tracker> full(new Tracker(42));

    Tracker* raw = full.get();
    using std::swap;
    swap(empty, full);

    // Ownership should move to the previously-empty one
    EXPECT_EQ(empty.get(), raw);
    EXPECT_TRUE(static_cast<bool>(empty));
    EXPECT_FALSE(static_cast<bool>(full));
    EXPECT_EQ(full.get(), nullptr);
    EXPECT_EQ(empty->GetTag(), 42);
    EXPECT_EQ(Tracker::destroyed, 0);
    EXPECT_EQ(Tracker::live, 1);
}

//
// Boundary: self-swap should be a no-op (no premature deletes)
//
TEST_F(UniquePtrSwapTest_30, SelfSwap_NoSideEffects_30) {
    {
        unique_ptr<Tracker> u(new Tracker(7));
        Tracker* before = u.get();

        using std::swap;
        swap(u, u);

        EXPECT_EQ(u.get(), before);
        EXPECT_TRUE(u);
        EXPECT_EQ(Tracker::destroyed, 0) << "Self-swap must not destroy the object";
        EXPECT_EQ(Tracker::live, 1);
    }
    // After scope, exactly one destroy should have occurred.
    EXPECT_EQ(Tracker::destroyed, 1);
    EXPECT_EQ(Tracker::live, 0);
}

//
// Exceptional/error-ish observable: ensure no double delete through swap
//
TEST_F(UniquePtrSwapTest_30, Swap_DoesNotDoubleDelete_30) {
    {
        unique_ptr<Tracker> a(new Tracker(10));
        unique_ptr<Tracker> b(new Tracker(20));

        using std::swap;
        swap(a, b);

        // Let both go out of scope; exactly two destructions should occur.
        EXPECT_EQ(Tracker::destroyed, 0);
        EXPECT_EQ(Tracker::live, 2);
    }
    EXPECT_EQ(Tracker::destroyed, 2);
    EXPECT_EQ(Tracker::live, 0);
}

//
// Interaction: swap then reset deletes the correct pointee
//
TEST_F(UniquePtrSwapTest_30, SwapThenReset_DeletesSwappedObject_30) {
    {
        unique_ptr<Tracker> a(new Tracker(100));
        unique_ptr<Tracker> b; // nullptr

        using std::swap;
        swap(a, b); // b now owns 100, a is nullptr

        ASSERT_FALSE(a);
        ASSERT_TRUE(b);
        EXPECT_EQ(Tracker::destroyed, 0);
        EXPECT_EQ(Tracker::live, 1);

        b.reset(); // should delete the swapped-in object
        EXPECT_FALSE(b);
        EXPECT_EQ(Tracker::destroyed, 1);
        EXPECT_EQ(Tracker::live, 0);
    }
    // No additional deletes on scope exit
    EXPECT_EQ(Tracker::destroyed, 1);
    EXPECT_EQ(Tracker::live, 0);
}

//
// Move + swap interplay: moving out leaves nullptr, then swap reassigns ownership
//
TEST_F(UniquePtrSwapTest_30, MoveThenSwap_30) {
    unique_ptr<Tracker> a(new Tracker(1));
    unique_ptr<Tracker> b(new Tracker(2));

    unique_ptr<Tracker> c(std::move(a)); // a becomes nullptr
    ASSERT_FALSE(a);
    ASSERT_TRUE(c);
    ASSERT_TRUE(b);

    Tracker* oldB = b.get();
    Tracker* oldC = c.get();

    using std::swap;
    swap(b, c);

    EXPECT_EQ(b.get(), oldC); // b now owns what c used to own
    EXPECT_EQ(c.get(), oldB); // c now owns what b used to own
    EXPECT_FALSE(a);
    EXPECT_TRUE(b);
    EXPECT_TRUE(c);
    EXPECT_EQ((*b).GetTag(), 1);
    EXPECT_EQ(c->GetTag(), 2);
    EXPECT_EQ(Tracker::destroyed, 0);
    EXPECT_EQ(Tracker::live, 2);
}
