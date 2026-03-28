#include "catch2/internal/catch_unique_ptr.hpp"
#include <gtest/gtest.h>
#include <type_traits>
#include <string>

// A simple test class to use with unique_ptr
struct TestObject {
    int value;
    explicit TestObject(int v = 0) : value(v) {}
    virtual ~TestObject() = default;
};

struct DerivedObject : public TestObject {
    double extra;
    explicit DerivedObject(int v = 0, double e = 0.0) : TestObject(v), extra(e) {}
};

// Track construction/destruction
struct LifetimeTracker {
    static int alive_count;
    int id;
    LifetimeTracker(int i = 0) : id(i) { ++alive_count; }
    ~LifetimeTracker() { --alive_count; }
};
int LifetimeTracker::alive_count = 0;

class UniquePtrTest_26 : public ::testing::Test {
protected:
    void SetUp() override {
        LifetimeTracker::alive_count = 0;
    }
};

// Default construction with nullptr
TEST_F(UniquePtrTest_26, DefaultConstructionIsNull_26) {
    Catch::Detail::unique_ptr<TestObject> ptr;
    EXPECT_EQ(ptr.get(), nullptr);
    EXPECT_FALSE(static_cast<bool>(ptr));
}

// Explicit nullptr construction
TEST_F(UniquePtrTest_26, NullptrConstruction_26) {
    Catch::Detail::unique_ptr<TestObject> ptr(nullptr);
    EXPECT_EQ(ptr.get(), nullptr);
    EXPECT_FALSE(static_cast<bool>(ptr));
}

// Construction with raw pointer
TEST_F(UniquePtrTest_26, ConstructionWithRawPointer_26) {
    auto* raw = new TestObject(42);
    Catch::Detail::unique_ptr<TestObject> ptr(raw);
    EXPECT_EQ(ptr.get(), raw);
    EXPECT_TRUE(static_cast<bool>(ptr));
    EXPECT_EQ(ptr->value, 42);
}

// Dereference operator
TEST_F(UniquePtrTest_26, DereferenceOperator_26) {
    Catch::Detail::unique_ptr<TestObject> ptr(new TestObject(99));
    EXPECT_EQ((*ptr).value, 99);
}

// Arrow operator
TEST_F(UniquePtrTest_26, ArrowOperator_26) {
    Catch::Detail::unique_ptr<TestObject> ptr(new TestObject(77));
    EXPECT_EQ(ptr->value, 77);
}

// get() returns managed pointer
TEST_F(UniquePtrTest_26, GetReturnsPointer_26) {
    auto* raw = new TestObject(10);
    Catch::Detail::unique_ptr<TestObject> ptr(raw);
    EXPECT_EQ(ptr.get(), raw);
}

// release() releases ownership
TEST_F(UniquePtrTest_26, ReleaseReleasesOwnership_26) {
    auto* raw = new TestObject(55);
    Catch::Detail::unique_ptr<TestObject> ptr(raw);
    TestObject* released = ptr.release();
    EXPECT_EQ(released, raw);
    EXPECT_EQ(ptr.get(), nullptr);
    EXPECT_FALSE(static_cast<bool>(ptr));
    delete released;
}

// reset() to nullptr
TEST_F(UniquePtrTest_26, ResetToNullptr_26) {
    Catch::Detail::unique_ptr<LifetimeTracker> ptr(new LifetimeTracker(1));
    EXPECT_EQ(LifetimeTracker::alive_count, 1);
    ptr.reset();
    EXPECT_EQ(ptr.get(), nullptr);
    EXPECT_EQ(LifetimeTracker::alive_count, 0);
}

// reset() to new pointer
TEST_F(UniquePtrTest_26, ResetToNewPointer_26) {
    auto* first = new LifetimeTracker(1);
    auto* second = new LifetimeTracker(2);
    EXPECT_EQ(LifetimeTracker::alive_count, 2);

    Catch::Detail::unique_ptr<LifetimeTracker> ptr(first);
    ptr.reset(second);
    EXPECT_EQ(LifetimeTracker::alive_count, 1);
    EXPECT_EQ(ptr.get(), second);
    EXPECT_EQ(ptr->id, 2);
}

// Destructor cleans up
TEST_F(UniquePtrTest_26, DestructorCleansUp_26) {
    {
        Catch::Detail::unique_ptr<LifetimeTracker> ptr(new LifetimeTracker(1));
        EXPECT_EQ(LifetimeTracker::alive_count, 1);
    }
    EXPECT_EQ(LifetimeTracker::alive_count, 0);
}

// Move constructor
TEST_F(UniquePtrTest_26, MoveConstructor_26) {
    auto* raw = new TestObject(33);
    Catch::Detail::unique_ptr<TestObject> ptr1(raw);
    Catch::Detail::unique_ptr<TestObject> ptr2(std::move(ptr1));

    EXPECT_EQ(ptr2.get(), raw);
    EXPECT_EQ(ptr2->value, 33);
    // After move, source should be null (typical unique_ptr semantics)
    EXPECT_EQ(ptr1.get(), nullptr);
}

// Move assignment
TEST_F(UniquePtrTest_26, MoveAssignment_26) {
    auto* raw1 = new LifetimeTracker(1);
    auto* raw2 = new LifetimeTracker(2);
    EXPECT_EQ(LifetimeTracker::alive_count, 2);

    Catch::Detail::unique_ptr<LifetimeTracker> ptr1(raw1);
    Catch::Detail::unique_ptr<LifetimeTracker> ptr2(raw2);

    ptr1 = std::move(ptr2);
    // raw1 should be deleted, ptr1 now owns raw2
    EXPECT_EQ(LifetimeTracker::alive_count, 1);
    EXPECT_EQ(ptr1.get(), raw2);
    EXPECT_EQ(ptr1->id, 2);
    EXPECT_EQ(ptr2.get(), nullptr);
}

// bool conversion - true when non-null
TEST_F(UniquePtrTest_26, BoolConversionTrue_26) {
    Catch::Detail::unique_ptr<TestObject> ptr(new TestObject(1));
    EXPECT_TRUE(static_cast<bool>(ptr));
}

// bool conversion - false when null
TEST_F(UniquePtrTest_26, BoolConversionFalse_26) {
    Catch::Detail::unique_ptr<TestObject> ptr;
    EXPECT_FALSE(static_cast<bool>(ptr));
}

// Move construction from derived type
TEST_F(UniquePtrTest_26, MoveConstructFromDerived_26) {
    auto* derived = new DerivedObject(10, 3.14);
    Catch::Detail::unique_ptr<DerivedObject> derivedPtr(derived);
    Catch::Detail::unique_ptr<TestObject> basePtr(std::move(derivedPtr));

    EXPECT_EQ(basePtr.get(), derived);
    EXPECT_EQ(basePtr->value, 10);
    EXPECT_EQ(derivedPtr.get(), nullptr);
}

// Move assignment from derived type
TEST_F(UniquePtrTest_26, MoveAssignFromDerived_26) {
    auto* derived = new DerivedObject(20, 2.71);
    Catch::Detail::unique_ptr<DerivedObject> derivedPtr(derived);
    Catch::Detail::unique_ptr<TestObject> basePtr(new TestObject(5));

    basePtr = std::move(derivedPtr);
    EXPECT_EQ(basePtr.get(), derived);
    EXPECT_EQ(basePtr->value, 20);
    EXPECT_EQ(derivedPtr.get(), nullptr);
}

// Copy constructor is deleted (compile-time check via type traits)
TEST_F(UniquePtrTest_26, CopyConstructorIsDeleted_26) {
    EXPECT_FALSE(std::is_copy_constructible<Catch::Detail::unique_ptr<TestObject>>::value);
}

// Copy assignment is deleted
TEST_F(UniquePtrTest_26, CopyAssignmentIsDeleted_26) {
    EXPECT_FALSE(std::is_copy_assignable<Catch::Detail::unique_ptr<TestObject>>::value);
}

// Multiple resets
TEST_F(UniquePtrTest_26, MultipleResets_26) {
    Catch::Detail::unique_ptr<LifetimeTracker> ptr(new LifetimeTracker(1));
    EXPECT_EQ(LifetimeTracker::alive_count, 1);

    ptr.reset(new LifetimeTracker(2));
    EXPECT_EQ(LifetimeTracker::alive_count, 1);
    EXPECT_EQ(ptr->id, 2);

    ptr.reset(new LifetimeTracker(3));
    EXPECT_EQ(LifetimeTracker::alive_count, 1);
    EXPECT_EQ(ptr->id, 3);

    ptr.reset();
    EXPECT_EQ(LifetimeTracker::alive_count, 0);
    EXPECT_EQ(ptr.get(), nullptr);
}

// Release on null pointer
TEST_F(UniquePtrTest_26, ReleaseOnNullPtr_26) {
    Catch::Detail::unique_ptr<TestObject> ptr;
    TestObject* released = ptr.release();
    EXPECT_EQ(released, nullptr);
    EXPECT_EQ(ptr.get(), nullptr);
}

// Reset null pointer with nullptr
TEST_F(UniquePtrTest_26, ResetNullWithNullptr_26) {
    Catch::Detail::unique_ptr<TestObject> ptr;
    ptr.reset(nullptr);
    EXPECT_EQ(ptr.get(), nullptr);
    EXPECT_FALSE(static_cast<bool>(ptr));
}

// Move is noexcept
TEST_F(UniquePtrTest_26, MoveConstructorIsNoexcept_26) {
    EXPECT_TRUE(std::is_nothrow_move_constructible<Catch::Detail::unique_ptr<TestObject>>::value);
}

// Self-move scenario - after move, the pointer should still be in a valid state
TEST_F(UniquePtrTest_26, GetAfterRelease_26) {
    Catch::Detail::unique_ptr<TestObject> ptr(new TestObject(100));
    TestObject* raw = ptr.release();
    EXPECT_EQ(ptr.get(), nullptr);
    EXPECT_FALSE(static_cast<bool>(ptr));
    EXPECT_EQ(raw->value, 100);
    delete raw;
}

// Verify destruction through base pointer for derived type
TEST_F(UniquePtrTest_26, DestructionThroughBasePointer_26) {
    struct DerivedTracker : public LifetimeTracker {
        static int derived_destroyed;
        DerivedTracker() : LifetimeTracker(99) {}
        ~DerivedTracker() { ++derived_destroyed; }
    };
    DerivedTracker::derived_destroyed = 0;

    {
        Catch::Detail::unique_ptr<LifetimeTracker> ptr(new DerivedTracker());
        EXPECT_EQ(LifetimeTracker::alive_count, 1);
    }
    // Virtual destructor ensures proper cleanup
    EXPECT_EQ(LifetimeTracker::alive_count, 0);
    EXPECT_EQ(DerivedTracker::derived_destroyed, 1);
}
