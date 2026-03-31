#include "catch2/internal/catch_unique_ptr.hpp"
#include <gtest/gtest.h>
#include <string>
#include <type_traits>

// A simple test class to use with unique_ptr
struct TestObject {
    int value;
    TestObject() : value(0) {}
    explicit TestObject(int v) : value(v) {}
    int getValue() const { return value; }
    void setValue(int v) { value = v; }
};

struct Base {
    virtual ~Base() = default;
    virtual int id() const { return 0; }
};

struct Derived : public Base {
    int id() const override { return 1; }
};

// Track destructor calls
struct DestructorTracker {
    static int destructorCount;
    ~DestructorTracker() { ++destructorCount; }
};
int DestructorTracker::destructorCount = 0;

class UniquePtrTest_25 : public ::testing::Test {
protected:
    void SetUp() override {
        DestructorTracker::destructorCount = 0;
    }
};

// Default construction with nullptr
TEST_F(UniquePtrTest_25, DefaultConstructionIsNull_25) {
    Catch::Detail::unique_ptr<TestObject> ptr;
    EXPECT_FALSE(static_cast<bool>(ptr));
    EXPECT_EQ(ptr.get(), nullptr);
}

// Construction with nullptr literal
TEST_F(UniquePtrTest_25, NullptrConstructionIsNull_25) {
    Catch::Detail::unique_ptr<TestObject> ptr(nullptr);
    EXPECT_FALSE(static_cast<bool>(ptr));
    EXPECT_EQ(ptr.get(), nullptr);
}

// Construction with raw pointer
TEST_F(UniquePtrTest_25, ConstructionWithRawPointer_25) {
    TestObject* raw = new TestObject(42);
    Catch::Detail::unique_ptr<TestObject> ptr(raw);
    EXPECT_TRUE(static_cast<bool>(ptr));
    EXPECT_EQ(ptr.get(), raw);
    EXPECT_EQ(ptr->getValue(), 42);
}

// Dereference operator
TEST_F(UniquePtrTest_25, DereferenceOperator_25) {
    Catch::Detail::unique_ptr<TestObject> ptr(new TestObject(99));
    EXPECT_EQ((*ptr).value, 99);
}

// Arrow operator
TEST_F(UniquePtrTest_25, ArrowOperator_25) {
    Catch::Detail::unique_ptr<TestObject> ptr(new TestObject(55));
    EXPECT_EQ(ptr->getValue(), 55);
    ptr->setValue(77);
    EXPECT_EQ(ptr->getValue(), 77);
}

// Get returns raw pointer
TEST_F(UniquePtrTest_25, GetReturnsRawPointer_25) {
    TestObject* raw = new TestObject(10);
    Catch::Detail::unique_ptr<TestObject> ptr(raw);
    EXPECT_EQ(ptr.get(), raw);
}

// Release gives up ownership
TEST_F(UniquePtrTest_25, ReleaseGivesUpOwnership_25) {
    TestObject* raw = new TestObject(20);
    Catch::Detail::unique_ptr<TestObject> ptr(raw);
    TestObject* released = ptr.release();
    EXPECT_EQ(released, raw);
    EXPECT_EQ(ptr.get(), nullptr);
    EXPECT_FALSE(static_cast<bool>(ptr));
    delete released;
}

// Reset with nullptr
TEST_F(UniquePtrTest_25, ResetToNull_25) {
    Catch::Detail::unique_ptr<DestructorTracker> ptr(new DestructorTracker());
    EXPECT_EQ(DestructorTracker::destructorCount, 0);
    ptr.reset();
    EXPECT_EQ(DestructorTracker::destructorCount, 1);
    EXPECT_EQ(ptr.get(), nullptr);
    EXPECT_FALSE(static_cast<bool>(ptr));
}

// Reset with new pointer
TEST_F(UniquePtrTest_25, ResetWithNewPointer_25) {
    TestObject* first = new TestObject(1);
    TestObject* second = new TestObject(2);
    Catch::Detail::unique_ptr<TestObject> ptr(first);
    ptr.reset(second);
    EXPECT_EQ(ptr.get(), second);
    EXPECT_EQ(ptr->getValue(), 2);
}

// Reset destroys old object
TEST_F(UniquePtrTest_25, ResetDestroysOldObject_25) {
    Catch::Detail::unique_ptr<DestructorTracker> ptr(new DestructorTracker());
    ptr.reset(new DestructorTracker());
    EXPECT_EQ(DestructorTracker::destructorCount, 1);
}

// Move construction
TEST_F(UniquePtrTest_25, MoveConstruction_25) {
    TestObject* raw = new TestObject(30);
    Catch::Detail::unique_ptr<TestObject> original(raw);
    Catch::Detail::unique_ptr<TestObject> moved(std::move(original));
    EXPECT_EQ(moved.get(), raw);
    EXPECT_EQ(moved->getValue(), 30);
    EXPECT_EQ(original.get(), nullptr);
    EXPECT_FALSE(static_cast<bool>(original));
}

// Move assignment
TEST_F(UniquePtrTest_25, MoveAssignment_25) {
    TestObject* raw1 = new TestObject(1);
    TestObject* raw2 = new TestObject(2);
    Catch::Detail::unique_ptr<TestObject> ptr1(raw1);
    Catch::Detail::unique_ptr<TestObject> ptr2(raw2);
    ptr1 = std::move(ptr2);
    EXPECT_EQ(ptr1.get(), raw2);
    EXPECT_EQ(ptr1->getValue(), 2);
    EXPECT_EQ(ptr2.get(), nullptr);
}

// Destructor cleans up
TEST_F(UniquePtrTest_25, DestructorCleansUp_25) {
    {
        Catch::Detail::unique_ptr<DestructorTracker> ptr(new DestructorTracker());
        EXPECT_EQ(DestructorTracker::destructorCount, 0);
    }
    EXPECT_EQ(DestructorTracker::destructorCount, 1);
}

// Boolean conversion - true when non-null
TEST_F(UniquePtrTest_25, BoolConversionTrue_25) {
    Catch::Detail::unique_ptr<TestObject> ptr(new TestObject());
    EXPECT_TRUE(static_cast<bool>(ptr));
}

// Boolean conversion - false when null
TEST_F(UniquePtrTest_25, BoolConversionFalse_25) {
    Catch::Detail::unique_ptr<TestObject> ptr;
    EXPECT_FALSE(static_cast<bool>(ptr));
}

// Polymorphic move construction (Derived to Base)
TEST_F(UniquePtrTest_25, PolymorphicMoveConstruction_25) {
    Catch::Detail::unique_ptr<Derived> derived(new Derived());
    Catch::Detail::unique_ptr<Base> base(std::move(derived));
    EXPECT_TRUE(static_cast<bool>(base));
    EXPECT_EQ(base->id(), 1);
    EXPECT_EQ(derived.get(), nullptr);
}

// Polymorphic move assignment (Derived to Base)
TEST_F(UniquePtrTest_25, PolymorphicMoveAssignment_25) {
    Catch::Detail::unique_ptr<Derived> derived(new Derived());
    Catch::Detail::unique_ptr<Base> base(new Base());
    base = std::move(derived);
    EXPECT_TRUE(static_cast<bool>(base));
    EXPECT_EQ(base->id(), 1);
    EXPECT_EQ(derived.get(), nullptr);
}

// Release on null pointer returns nullptr
TEST_F(UniquePtrTest_25, ReleaseOnNullReturnsNullptr_25) {
    Catch::Detail::unique_ptr<TestObject> ptr;
    TestObject* released = ptr.release();
    EXPECT_EQ(released, nullptr);
}

// Reset null pointer with nullptr (no crash)
TEST_F(UniquePtrTest_25, ResetNullWithNull_25) {
    Catch::Detail::unique_ptr<TestObject> ptr;
    ptr.reset(nullptr);
    EXPECT_FALSE(static_cast<bool>(ptr));
    EXPECT_EQ(ptr.get(), nullptr);
}

// Get on null pointer returns nullptr
TEST_F(UniquePtrTest_25, GetOnNullReturnsNullptr_25) {
    Catch::Detail::unique_ptr<TestObject> ptr;
    EXPECT_EQ(ptr.get(), nullptr);
}

// Move assignment cleans up previous resource
TEST_F(UniquePtrTest_25, MoveAssignmentCleansUpPrevious_25) {
    Catch::Detail::unique_ptr<DestructorTracker> ptr1(new DestructorTracker());
    Catch::Detail::unique_ptr<DestructorTracker> ptr2(new DestructorTracker());
    EXPECT_EQ(DestructorTracker::destructorCount, 0);
    ptr1 = std::move(ptr2);
    EXPECT_EQ(DestructorTracker::destructorCount, 1);
}

// Multiple resets
TEST_F(UniquePtrTest_25, MultipleResets_25) {
    Catch::Detail::unique_ptr<DestructorTracker> ptr(new DestructorTracker());
    ptr.reset(new DestructorTracker());
    EXPECT_EQ(DestructorTracker::destructorCount, 1);
    ptr.reset(new DestructorTracker());
    EXPECT_EQ(DestructorTracker::destructorCount, 2);
    ptr.reset();
    EXPECT_EQ(DestructorTracker::destructorCount, 3);
}

// Copy constructor is deleted (compile-time check via type trait)
TEST_F(UniquePtrTest_25, CopyConstructorIsDeleted_25) {
    EXPECT_FALSE(std::is_copy_constructible<Catch::Detail::unique_ptr<TestObject>>::value);
}

// Copy assignment is deleted
TEST_F(UniquePtrTest_25, CopyAssignmentIsDeleted_25) {
    EXPECT_FALSE(std::is_copy_assignable<Catch::Detail::unique_ptr<TestObject>>::value);
}

// Move constructible
TEST_F(UniquePtrTest_25, IsMoveConstructible_25) {
    EXPECT_TRUE(std::is_move_constructible<Catch::Detail::unique_ptr<TestObject>>::value);
}

// Move assignable
TEST_F(UniquePtrTest_25, IsMoveAssignable_25) {
    EXPECT_TRUE(std::is_move_assignable<Catch::Detail::unique_ptr<TestObject>>::value);
}

// Works with primitive types
TEST_F(UniquePtrTest_25, WorksWithInt_25) {
    Catch::Detail::unique_ptr<int> ptr(new int(42));
    EXPECT_TRUE(static_cast<bool>(ptr));
    EXPECT_EQ(*ptr, 42);
    EXPECT_EQ(*ptr.get(), 42);
}

// Boolean conversion after release
TEST_F(UniquePtrTest_25, BoolAfterRelease_25) {
    Catch::Detail::unique_ptr<TestObject> ptr(new TestObject(5));
    EXPECT_TRUE(static_cast<bool>(ptr));
    TestObject* raw = ptr.release();
    EXPECT_FALSE(static_cast<bool>(ptr));
    delete raw;
}

// Boolean conversion after move
TEST_F(UniquePtrTest_25, BoolAfterMove_25) {
    Catch::Detail::unique_ptr<TestObject> ptr1(new TestObject(5));
    Catch::Detail::unique_ptr<TestObject> ptr2(std::move(ptr1));
    EXPECT_FALSE(static_cast<bool>(ptr1));
    EXPECT_TRUE(static_cast<bool>(ptr2));
}
