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
    int extra;
    explicit DerivedObject(int v = 0, int e = 0) : TestObject(v), extra(e) {}
};

// Track construction/destruction
struct LifetimeTracker {
    static int alive_count;
    int id;
    explicit LifetimeTracker(int i = 0) : id(i) { ++alive_count; }
    ~LifetimeTracker() { --alive_count; }
};
int LifetimeTracker::alive_count = 0;

class UniquePtrTest_28 : public ::testing::Test {
protected:
    void SetUp() override {
        LifetimeTracker::alive_count = 0;
    }
    void TearDown() override {
    }
};

// Test default construction with nullptr
TEST_F(UniquePtrTest_28, DefaultConstructionIsNull_28) {
    Catch::Detail::unique_ptr<TestObject> ptr;
    EXPECT_FALSE(static_cast<bool>(ptr));
    EXPECT_EQ(ptr.get(), nullptr);
}

// Test explicit nullptr construction
TEST_F(UniquePtrTest_28, NullptrConstruction_28) {
    Catch::Detail::unique_ptr<TestObject> ptr(nullptr);
    EXPECT_FALSE(static_cast<bool>(ptr));
    EXPECT_EQ(ptr.get(), nullptr);
}

// Test construction with a raw pointer
TEST_F(UniquePtrTest_28, ConstructWithRawPointer_28) {
    auto* raw = new TestObject(42);
    Catch::Detail::unique_ptr<TestObject> ptr(raw);
    EXPECT_TRUE(static_cast<bool>(ptr));
    EXPECT_EQ(ptr.get(), raw);
    EXPECT_EQ(ptr->value, 42);
}

// Test dereference operator
TEST_F(UniquePtrTest_28, DereferenceOperator_28) {
    Catch::Detail::unique_ptr<TestObject> ptr(new TestObject(99));
    EXPECT_EQ((*ptr).value, 99);
}

// Test arrow operator
TEST_F(UniquePtrTest_28, ArrowOperator_28) {
    Catch::Detail::unique_ptr<TestObject> ptr(new TestObject(77));
    EXPECT_EQ(ptr->value, 77);
}

// Test get() returns the stored pointer
TEST_F(UniquePtrTest_28, GetReturnsStoredPointer_28) {
    auto* raw = new TestObject(10);
    Catch::Detail::unique_ptr<TestObject> ptr(raw);
    EXPECT_EQ(ptr.get(), raw);
}

// Test release() returns the pointer and sets internal to null
TEST_F(UniquePtrTest_28, ReleaseReturnsPointerAndNullifies_28) {
    auto* raw = new TestObject(55);
    Catch::Detail::unique_ptr<TestObject> ptr(raw);
    T* released = ptr.release();
    EXPECT_EQ(released, raw);
    EXPECT_EQ(ptr.get(), nullptr);
    EXPECT_FALSE(static_cast<bool>(ptr));
    delete released; // manual cleanup since release() gives up ownership
}

// Test reset with nullptr
TEST_F(UniquePtrTest_28, ResetWithNullptr_28) {
    Catch::Detail::unique_ptr<LifetimeTracker> ptr(new LifetimeTracker(1));
    EXPECT_EQ(LifetimeTracker::alive_count, 1);
    ptr.reset(nullptr);
    EXPECT_EQ(LifetimeTracker::alive_count, 0);
    EXPECT_EQ(ptr.get(), nullptr);
    EXPECT_FALSE(static_cast<bool>(ptr));
}

// Test reset with new pointer
TEST_F(UniquePtrTest_28, ResetWithNewPointer_28) {
    auto* first = new LifetimeTracker(1);
    auto* second = new LifetimeTracker(2);
    EXPECT_EQ(LifetimeTracker::alive_count, 2);

    Catch::Detail::unique_ptr<LifetimeTracker> ptr(first);
    ptr.reset(second);
    EXPECT_EQ(LifetimeTracker::alive_count, 1);
    EXPECT_EQ(ptr.get(), second);
    EXPECT_EQ(ptr->id, 2);
}

// Test reset with no argument (defaults to nullptr)
TEST_F(UniquePtrTest_28, ResetDefaultNullptr_28) {
    Catch::Detail::unique_ptr<LifetimeTracker> ptr(new LifetimeTracker(1));
    EXPECT_EQ(LifetimeTracker::alive_count, 1);
    ptr.reset();
    EXPECT_EQ(LifetimeTracker::alive_count, 0);
    EXPECT_EQ(ptr.get(), nullptr);
}

// Test destructor deletes the managed object
TEST_F(UniquePtrTest_28, DestructorDeletesObject_28) {
    {
        Catch::Detail::unique_ptr<LifetimeTracker> ptr(new LifetimeTracker(1));
        EXPECT_EQ(LifetimeTracker::alive_count, 1);
    }
    EXPECT_EQ(LifetimeTracker::alive_count, 0);
}

// Test move construction
TEST_F(UniquePtrTest_28, MoveConstruction_28) {
    auto* raw = new TestObject(33);
    Catch::Detail::unique_ptr<TestObject> ptr1(raw);
    Catch::Detail::unique_ptr<TestObject> ptr2(std::move(ptr1));

    EXPECT_EQ(ptr2.get(), raw);
    EXPECT_EQ(ptr2->value, 33);
    // After move, the source should be null
    EXPECT_EQ(ptr1.get(), nullptr);
    EXPECT_FALSE(static_cast<bool>(ptr1));
}

// Test move assignment
TEST_F(UniquePtrTest_28, MoveAssignment_28) {
    auto* raw1 = new LifetimeTracker(1);
    auto* raw2 = new LifetimeTracker(2);
    EXPECT_EQ(LifetimeTracker::alive_count, 2);

    Catch::Detail::unique_ptr<LifetimeTracker> ptr1(raw1);
    Catch::Detail::unique_ptr<LifetimeTracker> ptr2(raw2);

    ptr1 = std::move(ptr2);
    // raw1 should have been deleted
    EXPECT_EQ(LifetimeTracker::alive_count, 1);
    EXPECT_EQ(ptr1.get(), raw2);
    EXPECT_EQ(ptr1->id, 2);
    EXPECT_EQ(ptr2.get(), nullptr);
}

// Test move construction from derived type
TEST_F(UniquePtrTest_28, MoveConstructionFromDerived_28) {
    auto* derived = new DerivedObject(10, 20);
    Catch::Detail::unique_ptr<DerivedObject> derivedPtr(derived);
    Catch::Detail::unique_ptr<TestObject> basePtr(std::move(derivedPtr));

    EXPECT_EQ(basePtr.get(), derived);
    EXPECT_EQ(basePtr->value, 10);
    EXPECT_EQ(derivedPtr.get(), nullptr);
}

// Test move assignment from derived type
TEST_F(UniquePtrTest_28, MoveAssignmentFromDerived_28) {
    auto* derived = new DerivedObject(15, 25);
    Catch::Detail::unique_ptr<DerivedObject> derivedPtr(derived);
    Catch::Detail::unique_ptr<TestObject> basePtr(new TestObject(0));

    basePtr = std::move(derivedPtr);
    EXPECT_EQ(basePtr.get(), derived);
    EXPECT_EQ(basePtr->value, 15);
    EXPECT_EQ(derivedPtr.get(), nullptr);
}

// Test explicit bool conversion when holding an object
TEST_F(UniquePtrTest_28, BoolConversionTrue_28) {
    Catch::Detail::unique_ptr<TestObject> ptr(new TestObject(1));
    EXPECT_TRUE(static_cast<bool>(ptr));
}

// Test explicit bool conversion when null
TEST_F(UniquePtrTest_28, BoolConversionFalse_28) {
    Catch::Detail::unique_ptr<TestObject> ptr;
    EXPECT_FALSE(static_cast<bool>(ptr));
}

// Test copy construction is deleted (compile-time check via type trait)
TEST_F(UniquePtrTest_28, CopyConstructionIsDeleted_28) {
    EXPECT_FALSE(std::is_copy_constructible<Catch::Detail::unique_ptr<TestObject>>::value);
}

// Test copy assignment is deleted
TEST_F(UniquePtrTest_28, CopyAssignmentIsDeleted_28) {
    EXPECT_FALSE(std::is_copy_assignable<Catch::Detail::unique_ptr<TestObject>>::value);
}

// Test release on a null pointer returns nullptr
TEST_F(UniquePtrTest_28, ReleaseOnNullReturnsNull_28) {
    Catch::Detail::unique_ptr<TestObject> ptr;
    auto* released = ptr.release();
    EXPECT_EQ(released, nullptr);
}

// Test reset on null pointer (no-op scenario, should not crash)
TEST_F(UniquePtrTest_28, ResetOnNullPointer_28) {
    Catch::Detail::unique_ptr<TestObject> ptr;
    ptr.reset(nullptr);
    EXPECT_EQ(ptr.get(), nullptr);
}

// Test multiple resets
TEST_F(UniquePtrTest_28, MultipleResets_28) {
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
}

// Test that release followed by manual delete works correctly
TEST_F(UniquePtrTest_28, ReleaseAndManualDelete_28) {
    Catch::Detail::unique_ptr<LifetimeTracker> ptr(new LifetimeTracker(1));
    EXPECT_EQ(LifetimeTracker::alive_count, 1);

    auto* raw = ptr.release();
    EXPECT_EQ(LifetimeTracker::alive_count, 1); // still alive
    EXPECT_EQ(ptr.get(), nullptr);

    delete raw;
    EXPECT_EQ(LifetimeTracker::alive_count, 0);
}

// Test move assignment to self-like scenario (move from empty to empty)
TEST_F(UniquePtrTest_28, MoveEmptyToEmpty_28) {
    Catch::Detail::unique_ptr<TestObject> ptr1;
    Catch::Detail::unique_ptr<TestObject> ptr2;
    ptr1 = std::move(ptr2);
    EXPECT_EQ(ptr1.get(), nullptr);
    EXPECT_EQ(ptr2.get(), nullptr);
}

// Test with primitive-like type (int)
TEST_F(UniquePtrTest_28, WorksWithIntType_28) {
    Catch::Detail::unique_ptr<int> ptr(new int(42));
    EXPECT_TRUE(static_cast<bool>(ptr));
    EXPECT_EQ(*ptr, 42);
    EXPECT_NE(ptr.get(), nullptr);

    int* raw = ptr.release();
    EXPECT_EQ(*raw, 42);
    EXPECT_EQ(ptr.get(), nullptr);
    delete raw;
}

// Test with std::string
TEST_F(UniquePtrTest_28, WorksWithString_28) {
    Catch::Detail::unique_ptr<std::string> ptr(new std::string("hello"));
    EXPECT_EQ(*ptr, "hello");
    EXPECT_EQ(ptr->size(), 5u);

    ptr.reset(new std::string("world"));
    EXPECT_EQ(*ptr, "world");
}
