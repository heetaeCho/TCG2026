// File: unique_ptr_tests_23.cpp
#include <gtest/gtest.h>
#include "catch2/internal/catch_unique_ptr.hpp"

using Catch::Detail::unique_ptr;

// -------- Test helpers (external to the class under test) --------
struct Tracker {
    static int alive;
    static int destroyed;

    int value;

    explicit Tracker(int v = 0) : value(v) { ++alive; }
    ~Tracker() { --alive; ++destroyed; }

    int inc() { return ++value; }

    static void ResetCounts() { alive = 0; destroyed = 0; }
};
int Tracker::alive = 0;
int Tracker::destroyed = 0;

struct Base {
    virtual ~Base() = default;                 // virtual to avoid UB on delete via base*
    virtual int kind() const { return 0; }
};
struct Derived : Base {
    static int destroyed;
    int x;
    explicit Derived(int xv = 0) : x(xv) {}
    ~Derived() override { ++destroyed; }
    int kind() const override { return 1; }

    static void ResetCounts() { destroyed = 0; }
};
int Derived::destroyed = 0;

// -------- Test fixture --------
class UniquePtrTest_23 : public ::testing::Test {
protected:
    void SetUp() override {
        Tracker::ResetCounts();
        Derived::ResetCounts();
    }
};

// -------- Tests --------

TEST_F(UniquePtrTest_23, DefaultConstructedIsNull_23) {
    unique_ptr<Tracker> p;                 // default/null
    EXPECT_EQ(0, Tracker::alive);
    EXPECT_FALSE(static_cast<bool>(p));
    EXPECT_EQ(nullptr, p.get());
}

TEST_F(UniquePtrTest_23, BoolConversionReflectsState_23) {
    unique_ptr<Tracker> empty;
    EXPECT_FALSE(static_cast<bool>(empty));

    unique_ptr<Tracker> p(new Tracker());
    EXPECT_TRUE(static_cast<bool>(p));
    EXPECT_EQ(1, Tracker::alive);
}

TEST_F(UniquePtrTest_23, DestructorDeletesManagedObject_23) {
    {
        unique_ptr<Tracker> p(new Tracker());
        EXPECT_EQ(1, Tracker::alive);
        EXPECT_EQ(0, Tracker::destroyed);
    }
    // After leaving scope, object must be deleted exactly once
    EXPECT_EQ(0, Tracker::alive);
    EXPECT_EQ(1, Tracker::destroyed);
}

TEST_F(UniquePtrTest_23, DereferenceAndArrowAccess_23) {
    unique_ptr<Tracker> p(new Tracker(5));
    EXPECT_EQ(5, (*p).value);
    EXPECT_EQ(6, p->inc());
    EXPECT_EQ(6, (*p).value);
}

TEST_F(UniquePtrTest_23, GetReturnsRawPointerWithoutTransfer_23) {
    Tracker::ResetCounts();
    Tracker* raw = nullptr;
    {
        unique_ptr<Tracker> p(new Tracker(7));
        raw = p.get();
        ASSERT_NE(nullptr, raw);
        EXPECT_TRUE(static_cast<bool>(p));
        EXPECT_EQ(1, Tracker::alive);
        // Do not delete raw here; ownership remains with unique_ptr
    }
    // unique_ptr went out of scope and should have deleted the object
    EXPECT_EQ(0, Tracker::alive);
    EXPECT_EQ(1, Tracker::destroyed);
}

TEST_F(UniquePtrTest_23, ResetToNullDeletesAndEmpties_23) {
    unique_ptr<Tracker> p(new Tracker());
    EXPECT_EQ(1, Tracker::alive);

    p.reset(nullptr);                      // release and delete current
    EXPECT_FALSE(static_cast<bool>(p));
    EXPECT_EQ(nullptr, p.get());
    EXPECT_EQ(0, Tracker::alive);
    EXPECT_EQ(1, Tracker::destroyed);
}

TEST_F(UniquePtrTest_23, ResetReplacesOldAndDeletesOld_23) {
    unique_ptr<Tracker> p(new Tracker(1));
    EXPECT_EQ(1, Tracker::alive);

    p.reset(new Tracker(2));               // old must be deleted, new alive
    EXPECT_EQ(1, Tracker::alive);
    EXPECT_EQ(1, Tracker::destroyed);
    EXPECT_EQ(2, p->value);
}

TEST_F(UniquePtrTest_23, ReleaseRelinquishesOwnership_23) {
    Tracker::ResetCounts();
    unique_ptr<Tracker> p(new Tracker(3));
    EXPECT_EQ(1, Tracker::alive);

    Tracker* raw = p.release();            // no deletion should occur
    EXPECT_FALSE(static_cast<bool>(p));
    EXPECT_EQ(nullptr, p.get());
    EXPECT_EQ(1, Tracker::alive);
    EXPECT_EQ(0, Tracker::destroyed);

    delete raw;                            // caller is responsible to delete
    EXPECT_EQ(0, Tracker::alive);
    EXPECT_EQ(1, Tracker::destroyed);
}

TEST_F(UniquePtrTest_23, MoveConstructorTransfersOwnership_23) {
    Tracker::ResetCounts();
    unique_ptr<Tracker> src(new Tracker());
    EXPECT_TRUE(static_cast<bool>(src));
    EXPECT_EQ(1, Tracker::alive);

    unique_ptr<Tracker> dst(std::move(src));
    EXPECT_FALSE(static_cast<bool>(src));
    EXPECT_TRUE(static_cast<bool>(dst));
    EXPECT_EQ(1, Tracker::alive);

    // Only one destruction on scope exit
    // (implicitly verified by counts)
}

TEST_F(UniquePtrTest_23, MoveAssignmentTransfersAndClearsSource_23) {
    Tracker::ResetCounts();
    unique_ptr<Tracker> src(new Tracker(10));
    unique_ptr<Tracker> dst;               // empty

    dst = std::move(src);
    EXPECT_FALSE(static_cast<bool>(src));
    EXPECT_TRUE(static_cast<bool>(dst));
    EXPECT_EQ(1, Tracker::alive);
    EXPECT_EQ(10, dst->value);
}

TEST_F(UniquePtrTest_23, MoveAssignmentOverwritesAndDeletesExisting_23) {
    Tracker::ResetCounts();
    unique_ptr<Tracker> src(new Tracker(1));
    unique_ptr<Tracker> dst(new Tracker(2));
    EXPECT_EQ(2, Tracker::alive);

    dst = std::move(src);                  // old (value=2) must be deleted
    EXPECT_FALSE(static_cast<bool>(src));
    EXPECT_TRUE(static_cast<bool>(dst));
    EXPECT_EQ(1, Tracker::alive);
    EXPECT_EQ(1, Tracker::destroyed);      // the overwritten one
    EXPECT_EQ(1, dst->value);
}

TEST_F(UniquePtrTest_23, CrossTypeMoveFromDerivedToBase_23) {
    Derived::ResetCounts();
    {
        unique_ptr<Derived> pd(new Derived(7));
        unique_ptr<Base>    pb(std::move(pd));  // cross-type move-construct

        EXPECT_FALSE(static_cast<bool>(pd));
        EXPECT_TRUE(static_cast<bool>(pb));
        EXPECT_EQ(1, pb->kind());               // virtual dispatch works
        // Verify the actual dynamic type is Derived
        EXPECT_NE(nullptr, dynamic_cast<Derived*>(pb.get()));
    }
    // Deleting via base pointer should call Derived destructor
    EXPECT_EQ(1, Derived::destroyed);
}

TEST_F(UniquePtrTest_23, ResetOnEmptyIsNoop_23) {
    unique_ptr<Tracker> p;                  // empty
    p.reset(nullptr);                       // should not change counts
    EXPECT_FALSE(static_cast<bool>(p));
    EXPECT_EQ(0, Tracker::alive);
    EXPECT_EQ(0, Tracker::destroyed);
}
