#include "catch2/internal/catch_unique_ptr.hpp"
#include <gtest/gtest.h>
#include <string>
#include <type_traits>

// Test fixture
class UniquePtrTest_24 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Helper classes for testing
struct Base {
    virtual ~Base() = default;
    virtual int value() const { return 1; }
};

struct Derived : public Base {
    int value() const override { return 2; }
};

struct TrackDestruction {
    bool* destroyed;
    explicit TrackDestruction(bool* d) : destroyed(d) {}
    ~TrackDestruction() { *destroyed = true; }
};

// ============================================================
// Construction Tests
// ============================================================

TEST_F(UniquePtrTest_24, DefaultConstructionIsNull_24) {
    Catch::Detail::unique_ptr<int> ptr;
    EXPECT_FALSE(static_cast<bool>(ptr));
    EXPECT_EQ(ptr.get(), nullptr);
}

TEST_F(UniquePtrTest_24, NullptrConstructionIsNull_24) {
    Catch::Detail::unique_ptr<int> ptr(nullptr);
    EXPECT_FALSE(static_cast<bool>(ptr));
    EXPECT_EQ(ptr.get(), nullptr);
}

TEST_F(UniquePtrTest_24, ExplicitPointerConstruction_24) {
    int* raw = new int(42);
    Catch::Detail::unique_ptr<int> ptr(raw);
    EXPECT_TRUE(static_cast<bool>(ptr));
    EXPECT_EQ(ptr.get(), raw);
    EXPECT_EQ(*ptr, 42);
}

// ============================================================
// Move Construction Tests
// ============================================================

TEST_F(UniquePtrTest_24, MoveConstructionTransfersOwnership_24) {
    Catch::Detail::unique_ptr<int> ptr1(new int(100));
    int* raw = ptr1.get();
    Catch::Detail::unique_ptr<int> ptr2(std::move(ptr1));

    EXPECT_EQ(ptr2.get(), raw);
    EXPECT_EQ(*ptr2, 100);
    EXPECT_EQ(ptr1.get(), nullptr);
    EXPECT_FALSE(static_cast<bool>(ptr1));
}

TEST_F(UniquePtrTest_24, MoveConstructionFromDerived_24) {
    Catch::Detail::unique_ptr<Derived> derived(new Derived());
    Catch::Detail::unique_ptr<Base> base(std::move(derived));

    EXPECT_TRUE(static_cast<bool>(base));
    EXPECT_EQ(base->value(), 2);
    EXPECT_FALSE(static_cast<bool>(derived));
}

// ============================================================
// Move Assignment Tests
// ============================================================

TEST_F(UniquePtrTest_24, MoveAssignmentTransfersOwnership_24) {
    Catch::Detail::unique_ptr<int> ptr1(new int(200));
    Catch::Detail::unique_ptr<int> ptr2;

    int* raw = ptr1.get();
    ptr2 = std::move(ptr1);

    EXPECT_EQ(ptr2.get(), raw);
    EXPECT_EQ(*ptr2, 200);
    EXPECT_EQ(ptr1.get(), nullptr);
}

TEST_F(UniquePtrTest_24, MoveAssignmentDeletesPrevious_24) {
    bool destroyed = false;
    Catch::Detail::unique_ptr<TrackDestruction> ptr1(new TrackDestruction(&destroyed));
    Catch::Detail::unique_ptr<TrackDestruction> ptr2(new TrackDestruction(new bool(false)));

    ptr1 = std::move(ptr2);
    EXPECT_TRUE(destroyed);
}

TEST_F(UniquePtrTest_24, MoveAssignmentFromDerived_24) {
    Catch::Detail::unique_ptr<Derived> derived(new Derived());
    Catch::Detail::unique_ptr<Base> base;

    base = std::move(derived);
    EXPECT_TRUE(static_cast<bool>(base));
    EXPECT_EQ(base->value(), 2);
    EXPECT_FALSE(static_cast<bool>(derived));
}

// ============================================================
// Destructor Tests
// ============================================================

TEST_F(UniquePtrTest_24, DestructorDeletesOwnedObject_24) {
    bool destroyed = false;
    {
        Catch::Detail::unique_ptr<TrackDestruction> ptr(new TrackDestruction(&destroyed));
        EXPECT_FALSE(destroyed);
    }
    EXPECT_TRUE(destroyed);
}

TEST_F(UniquePtrTest_24, DestructorOnNullIsNoOp_24) {
    // Should not crash
    {
        Catch::Detail::unique_ptr<int> ptr;
    }
    // If we get here, it didn't crash
    SUCCEED();
}

// ============================================================
// Dereference Operator Tests
// ============================================================

TEST_F(UniquePtrTest_24, DereferenceReturnsValue_24) {
    Catch::Detail::unique_ptr<int> ptr(new int(55));
    EXPECT_EQ(*ptr, 55);
}

TEST_F(UniquePtrTest_24, DereferenceAllowsModification_24) {
    Catch::Detail::unique_ptr<int> ptr(new int(10));
    *ptr = 20;
    EXPECT_EQ(*ptr, 20);
}

// ============================================================
// Arrow Operator Tests
// ============================================================

TEST_F(UniquePtrTest_24, ArrowOperatorAccessesMember_24) {
    Catch::Detail::unique_ptr<std::string> ptr(new std::string("hello"));
    EXPECT_EQ(ptr->size(), 5u);
}

TEST_F(UniquePtrTest_24, ArrowOperatorOnBaseCallsVirtual_24) {
    Catch::Detail::unique_ptr<Base> ptr(new Derived());
    EXPECT_EQ(ptr->value(), 2);
}

// ============================================================
// get() Tests
// ============================================================

TEST_F(UniquePtrTest_24, GetReturnsRawPointer_24) {
    int* raw = new int(77);
    Catch::Detail::unique_ptr<int> ptr(raw);
    EXPECT_EQ(ptr.get(), raw);
}

TEST_F(UniquePtrTest_24, GetReturnsNullForDefault_24) {
    Catch::Detail::unique_ptr<int> ptr;
    EXPECT_EQ(ptr.get(), nullptr);
}

// ============================================================
// reset() Tests
// ============================================================

TEST_F(UniquePtrTest_24, ResetToNullDeletesObject_24) {
    bool destroyed = false;
    Catch::Detail::unique_ptr<TrackDestruction> ptr(new TrackDestruction(&destroyed));
    ptr.reset();
    EXPECT_TRUE(destroyed);
    EXPECT_EQ(ptr.get(), nullptr);
    EXPECT_FALSE(static_cast<bool>(ptr));
}

TEST_F(UniquePtrTest_24, ResetToNewPointer_24) {
    bool destroyed1 = false;
    bool destroyed2 = false;
    Catch::Detail::unique_ptr<TrackDestruction> ptr(new TrackDestruction(&destroyed1));
    ptr.reset(new TrackDestruction(&destroyed2));

    EXPECT_TRUE(destroyed1);
    EXPECT_FALSE(destroyed2);
    EXPECT_TRUE(static_cast<bool>(ptr));
}

TEST_F(UniquePtrTest_24, ResetNullPtrOnAlreadyNull_24) {
    Catch::Detail::unique_ptr<int> ptr;
    ptr.reset(nullptr);
    EXPECT_EQ(ptr.get(), nullptr);
}

TEST_F(UniquePtrTest_24, ResetWithExplicitNullptr_24) {
    Catch::Detail::unique_ptr<int> ptr(new int(5));
    ptr.reset(nullptr);
    EXPECT_EQ(ptr.get(), nullptr);
}

// ============================================================
// release() Tests
// ============================================================

TEST_F(UniquePtrTest_24, ReleaseReturnsPointerAndSetsNull_24) {
    int* raw = new int(99);
    Catch::Detail::unique_ptr<int> ptr(raw);

    int* released = ptr.release();
    EXPECT_EQ(released, raw);
    EXPECT_EQ(ptr.get(), nullptr);
    EXPECT_FALSE(static_cast<bool>(ptr));

    delete released; // manual cleanup
}

TEST_F(UniquePtrTest_24, ReleaseOnNullReturnsNull_24) {
    Catch::Detail::unique_ptr<int> ptr;
    int* released = ptr.release();
    EXPECT_EQ(released, nullptr);
}

TEST_F(UniquePtrTest_24, ReleaseDoesNotDeleteObject_24) {
    bool destroyed = false;
    Catch::Detail::unique_ptr<TrackDestruction> ptr(new TrackDestruction(&destroyed));

    TrackDestruction* released = ptr.release();
    EXPECT_FALSE(destroyed);

    delete released; // manual cleanup
    EXPECT_TRUE(destroyed);
}

// ============================================================
// operator bool() Tests
// ============================================================

TEST_F(UniquePtrTest_24, BoolOperatorTrueWhenNonNull_24) {
    Catch::Detail::unique_ptr<int> ptr(new int(1));
    EXPECT_TRUE(static_cast<bool>(ptr));
}

TEST_F(UniquePtrTest_24, BoolOperatorFalseWhenNull_24) {
    Catch::Detail::unique_ptr<int> ptr;
    EXPECT_FALSE(static_cast<bool>(ptr));
}

TEST_F(UniquePtrTest_24, BoolOperatorAfterReset_24) {
    Catch::Detail::unique_ptr<int> ptr(new int(1));
    EXPECT_TRUE(static_cast<bool>(ptr));
    ptr.reset();
    EXPECT_FALSE(static_cast<bool>(ptr));
}

TEST_F(UniquePtrTest_24, BoolOperatorAfterRelease_24) {
    Catch::Detail::unique_ptr<int> ptr(new int(1));
    EXPECT_TRUE(static_cast<bool>(ptr));
    int* raw = ptr.release();
    EXPECT_FALSE(static_cast<bool>(ptr));
    delete raw;
}

// ============================================================
// Copy Semantics (Deleted) - compile-time check
// ============================================================

TEST_F(UniquePtrTest_24, CopyConstructorIsDeleted_24) {
    EXPECT_FALSE(std::is_copy_constructible<Catch::Detail::unique_ptr<int>>::value);
}

TEST_F(UniquePtrTest_24, CopyAssignmentIsDeleted_24) {
    EXPECT_FALSE(std::is_copy_assignable<Catch::Detail::unique_ptr<int>>::value);
}

// ============================================================
// Complex Scenario Tests
// ============================================================

TEST_F(UniquePtrTest_24, MultipleResets_24) {
    bool d1 = false, d2 = false, d3 = false;
    Catch::Detail::unique_ptr<TrackDestruction> ptr(new TrackDestruction(&d1));
    ptr.reset(new TrackDestruction(&d2));
    EXPECT_TRUE(d1);
    EXPECT_FALSE(d2);

    ptr.reset(new TrackDestruction(&d3));
    EXPECT_TRUE(d2);
    EXPECT_FALSE(d3);

    ptr.reset();
    EXPECT_TRUE(d3);
}

TEST_F(UniquePtrTest_24, MoveChain_24) {
    Catch::Detail::unique_ptr<int> a(new int(42));
    Catch::Detail::unique_ptr<int> b(std::move(a));
    Catch::Detail::unique_ptr<int> c;
    c = std::move(b);

    EXPECT_FALSE(static_cast<bool>(a));
    EXPECT_FALSE(static_cast<bool>(b));
    EXPECT_TRUE(static_cast<bool>(c));
    EXPECT_EQ(*c, 42);
}

TEST_F(UniquePtrTest_24, PolymorphicDeletion_24) {
    bool destroyed = false;

    struct DerivedTrack : public Base {
        bool* flag;
        DerivedTrack(bool* f) : flag(f) {}
        ~DerivedTrack() override { *flag = true; }
    };

    {
        Catch::Detail::unique_ptr<Base> ptr(new DerivedTrack(&destroyed));
        EXPECT_FALSE(destroyed);
    }
    EXPECT_TRUE(destroyed);
}

TEST_F(UniquePtrTest_24, GetAfterMoveIsNull_24) {
    Catch::Detail::unique_ptr<int> ptr(new int(7));
    Catch::Detail::unique_ptr<int> other(std::move(ptr));
    EXPECT_EQ(ptr.get(), nullptr);
}

TEST_F(UniquePtrTest_24, ResetToSameTypeNewValue_24) {
    Catch::Detail::unique_ptr<int> ptr(new int(1));
    ptr.reset(new int(2));
    EXPECT_EQ(*ptr, 2);
}
