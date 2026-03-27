// File: unique_ptr_move_assign_tests_22.cpp

#include <gtest/gtest.h>
#include <type_traits>
#include <utility>

// Include the class under test
#include "Catch2/src/catch2/internal/catch_unique_ptr.hpp"

namespace {

struct Tracker {
    static int alive;
    static int destroyed;

    int id;
    explicit Tracker(int i) : id(i) { ++alive; }
    ~Tracker() { ++destroyed; --alive; }
};

int Tracker::alive = 0;
int Tracker::destroyed = 0;

using UniquePtr = Catch::Detail::unique_ptr<Tracker>;

} // namespace

// --- Compile-time property: noexcept on move assignment
static_assert(noexcept(std::declval<UniquePtr&>() = std::declval<UniquePtr&&>()),
              "unique_ptr move assignment must be noexcept");

class UniquePtrMoveAssignTest_22 : public ::testing::Test {
protected:
    void SetUp() override {
        Tracker::alive = 0;
        Tracker::destroyed = 0;
    }
};

// Normal operation: ownership transfers and source becomes empty
TEST_F(UniquePtrMoveAssignTest_22, MoveAssign_TransfersOwnership_22) {
    UniquePtr rhs(new Tracker(1));
    auto* raw = rhs.get();
    UniquePtr lhs; // empty

    lhs = std::move(rhs);

    EXPECT_EQ(lhs.get(), raw);
    EXPECT_EQ(rhs.get(), nullptr);
    EXPECT_TRUE(lhs);
    EXPECT_FALSE(static_cast<bool>(rhs));
    EXPECT_EQ(Tracker::alive, 1);
    EXPECT_EQ(Tracker::destroyed, 0);
}

// Boundary: target already owns something; previous target must be destroyed
TEST_F(UniquePtrMoveAssignTest_22, MoveAssign_DeletesPreviousTarget_22) {
    UniquePtr lhs(new Tracker(1));         // will be discarded
    UniquePtr rhs(new Tracker(2));         // will be moved
    EXPECT_EQ(Tracker::alive, 2);

    lhs = std::move(rhs);

    // Previous (id=1) should be destroyed during assignment
    EXPECT_EQ(Tracker::destroyed, 1);
    EXPECT_EQ(Tracker::alive, 1);
    ASSERT_NE(lhs.get(), nullptr);
    EXPECT_EQ(lhs->id, 2);
    EXPECT_EQ(rhs.get(), nullptr);
}

// Boundary: moving from an empty source into non-empty target empties the target
TEST_F(UniquePtrMoveAssignTest_22, MoveAssign_FromEmpty_EmptiesTarget_22) {
    UniquePtr lhs(new Tracker(10)); // will be discarded
    UniquePtr rhs;                  // empty
    EXPECT_EQ(Tracker::alive, 1);

    lhs = std::move(rhs);

    EXPECT_EQ(lhs.get(), nullptr);
    EXPECT_EQ(rhs.get(), nullptr);
    EXPECT_EQ(Tracker::destroyed, 1); // old target deleted
    EXPECT_EQ(Tracker::alive, 0);
}

// Boundary: both empty stays empty and does not destroy anything
TEST_F(UniquePtrMoveAssignTest_22, MoveAssign_BothEmpty_22) {
    UniquePtr lhs;
    UniquePtr rhs;

    lhs = std::move(rhs);

    EXPECT_EQ(lhs.get(), nullptr);
    EXPECT_EQ(rhs.get(), nullptr);
    EXPECT_EQ(Tracker::alive, 0);
    EXPECT_EQ(Tracker::destroyed, 0);
}

// API contract: operator= returns *this (self reference)
TEST_F(UniquePtrMoveAssignTest_22, MoveAssign_ReturnsSelfReference_22) {
    UniquePtr lhs(new Tracker(1));
    UniquePtr rhs(new Tracker(2));

    UniquePtr& ret = (lhs = std::move(rhs));
    EXPECT_EQ(&ret, &lhs);
    ASSERT_NE(lhs.get(), nullptr);
    EXPECT_EQ(lhs->id, 2);
    EXPECT_EQ(rhs.get(), nullptr);
}

// Boundary: self-move should not throw and result in a valid state (owning or empty)
TEST_F(UniquePtrMoveAssignTest_22, MoveAssign_SelfMove_NoThrow_ValidState_22) {
    UniquePtr u(new Tracker(99));
    Tracker* before = u.get();

    EXPECT_NO_THROW(u = std::move(u));

    // We do not assume specific semantics for self-move; only that the object is left valid.
    EXPECT_TRUE(u.get() == nullptr || u.get() == before);
    // No specific assertion about destruction here; just the absence of crash/throw and valid state.
}

// Chaining: the returned reference should allow further assignments
TEST_F(UniquePtrMoveAssignTest_22, MoveAssign_Chaining_22) {
    UniquePtr a(new Tracker(1));
    UniquePtr b(new Tracker(2));
    UniquePtr c(new Tracker(3));

    // (a = std::move(b)) returns a&, so assigning from c should work
    (a = std::move(b)) = std::move(c);

    ASSERT_NE(a.get(), nullptr);
    EXPECT_EQ(a->id, 3);
    EXPECT_EQ(b.get(), nullptr);
    EXPECT_EQ(c.get(), nullptr);

    // Two previous owners (id=1 was replaced by id=2, then by id=3) should have been destroyed
    // at the moments they were replaced.
    // Exact count so far should be 2 (id=1 and id=2), with id=3 alive.
    EXPECT_EQ(Tracker::destroyed, 2);
    EXPECT_EQ(Tracker::alive, 1);
}
