// File: unique_ptr_tests_27.cpp
#include <gtest/gtest.h>
#include <type_traits>
#include "catch2/internal/catch_unique_ptr.hpp"

namespace {

using Catch::Detail::unique_ptr;

// ---------- Test helpers (observe only via public behavior) ----------
struct Probe {
    static int dtor_count;
    int x{0};
    Probe() = default;
    explicit Probe(int v) : x(v) {}
    ~Probe() { ++dtor_count; }
    void inc() { ++x; }
    int twice() const { return 2 * x; }
};
int Probe::dtor_count = 0;

struct Base {
    static int dtor_count;
    virtual ~Base() { ++dtor_count; }
};
int Base::dtor_count = 0;

struct Derived : Base {
    static int dtor_count;
    ~Derived() override { ++dtor_count; }
};
int Derived::dtor_count = 0;

// ---------- Fixture ----------
class UniquePtrTest_27 : public ::testing::Test {
protected:
    void SetUp() override {
        Probe::dtor_count   = 0;
        Base::dtor_count    = 0;
        Derived::dtor_count = 0;
    }
};

} // namespace

// ---------- Tests ----------

TEST_F(UniquePtrTest_27, DefaultConstructedIsEmpty_27) {
    unique_ptr<Probe> p;
    EXPECT_FALSE(static_cast<bool>(p));
    EXPECT_EQ(p.get(), nullptr);
}

TEST_F(UniquePtrTest_27, ConstructWithPointer_OwnsAndAccessorsWork_27) {
    unique_ptr<Probe> p(new Probe(5));
    ASSERT_TRUE(p);
    ASSERT_NE(p.get(), nullptr);

    // operator* and operator-> observable behavior
    EXPECT_EQ((*p).x, 5);
    p->inc();
    EXPECT_EQ(p->x, 6);
    EXPECT_EQ(p->twice(), 12);
}

TEST_F(UniquePtrTest_27, ResetToNull_DeletesAndBecomesEmpty_27) {
    {
        unique_ptr<Probe> p(new Probe());
        EXPECT_EQ(Probe::dtor_count, 0);
        p.reset(nullptr);  // observable: previously held object destroyed
        EXPECT_EQ(Probe::dtor_count, 1);
        EXPECT_FALSE(p);
        EXPECT_EQ(p.get(), nullptr);
        // leaving scope should not destroy anything further
    }
    EXPECT_EQ(Probe::dtor_count, 1);
}

TEST_F(UniquePtrTest_27, ResetReplacesOld_27) {
    {
        unique_ptr<Probe> p(new Probe());
        EXPECT_EQ(Probe::dtor_count, 0);
        p.reset(new Probe());          // old destroyed now
        EXPECT_EQ(Probe::dtor_count, 1);
        ASSERT_TRUE(p);
        EXPECT_NE(p.get(), nullptr);
        // on scope exit, the new one is destroyed
    }
    EXPECT_EQ(Probe::dtor_count, 2);
}

TEST_F(UniquePtrTest_27, ReleaseReturnsAndClears_27) {
    Probe* raw = nullptr;
    {
        unique_ptr<Probe> p(new Probe(3));
        EXPECT_EQ(Probe::dtor_count, 0);
        raw = p.release();             // ownership released, no destruction
        EXPECT_FALSE(p);
        EXPECT_EQ(p.get(), nullptr);
        EXPECT_NE(raw, nullptr);
        EXPECT_EQ(Probe::dtor_count, 0);
    }
    // Still not destroyed because we hold raw
    EXPECT_EQ(Probe::dtor_count, 0);
    delete raw;                        // now destruction is observable
    EXPECT_EQ(Probe::dtor_count, 1);
}

TEST_F(UniquePtrTest_27, MoveConstructor_TransfersOwnership_27) {
    EXPECT_EQ(Probe::dtor_count, 0);
    {
        unique_ptr<Probe> a(new Probe());
        unique_ptr<Probe> b(std::move(a));
        EXPECT_FALSE(a);
        ASSERT_TRUE(b);
        EXPECT_NE(b.get(), nullptr);
    }
    // b went out of scope and should have destroyed the object exactly once
    EXPECT_EQ(Probe::dtor_count, 1);
}

TEST_F(UniquePtrTest_27, MoveAssignment_TransfersOwnership_27) {
    EXPECT_EQ(Probe::dtor_count, 0);
    {
        unique_ptr<Probe> a(new Probe());
        unique_ptr<Probe> b;
        b = std::move(a);
        EXPECT_FALSE(a);
        ASSERT_TRUE(b);
        EXPECT_NE(b.get(), nullptr);
    }
    EXPECT_EQ(Probe::dtor_count, 1);
}

TEST_F(UniquePtrTest_27, MoveAssignment_ReleasesOldTarget_27) {
    EXPECT_EQ(Probe::dtor_count, 0);
    {
        unique_ptr<Probe> a(new Probe());     // will become new target of b
        unique_ptr<Probe> b(new Probe());     // will be released during move=
        EXPECT_EQ(Probe::dtor_count, 0);
        b = std::move(a);
        // The previously owned object by b should be destroyed at assignment time
        EXPECT_EQ(Probe::dtor_count, 1);
        EXPECT_FALSE(a);
        ASSERT_TRUE(b);
        EXPECT_NE(b.get(), nullptr);
        // On scope exit, the (moved-from a's) object is destroyed
    }
    EXPECT_EQ(Probe::dtor_count, 2);
}

TEST_F(UniquePtrTest_27, ConvertingMoveConstructor_DerivedToBase_27) {
    EXPECT_EQ(Derived::dtor_count, 0);
    {
        unique_ptr<Derived> d(new Derived());
        unique_ptr<Base>    b(std::move(d));  // signature permits base-of conversions
        EXPECT_FALSE(d);
        ASSERT_TRUE(b);
        EXPECT_NE(b.get(), nullptr);
        // On scope exit, deleting through Base* must invoke Derived dtor
    }
    EXPECT_EQ(Derived::dtor_count, 1);
    // Base subobject also destroyed once
    EXPECT_EQ(Base::dtor_count, 1);
}

TEST_F(UniquePtrTest_27, ConvertingMoveAssignment_DerivedToBase_27) {
    EXPECT_EQ(Derived::dtor_count, 0);
    {
        unique_ptr<Base>    b;
        unique_ptr<Derived> d(new Derived());
        b = std::move(d);              // conversion move assignment
        EXPECT_FALSE(d);
        ASSERT_TRUE(b);
        EXPECT_NE(b.get(), nullptr);
    }
    EXPECT_EQ(Derived::dtor_count, 1);
    EXPECT_EQ(Base::dtor_count, 1);
}

TEST_F(UniquePtrTest_27, DestructorDeletesManagedObject_27) {
    EXPECT_EQ(Probe::dtor_count, 0);
    {
        unique_ptr<Probe> p(new Probe());
        EXPECT_EQ(Probe::dtor_count, 0);
    }
    EXPECT_EQ(Probe::dtor_count, 1);
}

TEST_F(UniquePtrTest_27, GetDoesNotTransferOwnership_27) {
    EXPECT_EQ(Probe::dtor_count, 0);
    Probe* raw = nullptr;
    {
        unique_ptr<Probe> p(new Probe());
        raw = p.get();
        ASSERT_NE(raw, nullptr);
        // Still owned by p; leaving scope should destroy it
    }
    EXPECT_EQ(Probe::dtor_count, 1);
    // Do not delete raw; it was already deleted by unique_ptr on scope exit
}
