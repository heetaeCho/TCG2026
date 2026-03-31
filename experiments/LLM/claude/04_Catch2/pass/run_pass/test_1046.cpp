#include <gtest/gtest.h>
#include "./TestProjects/Catch2/src/catch2/internal/catch_unique_ptr.hpp"
#include <type_traits>

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

// Track destruction
static int g_destructor_count = 0;

struct TrackableObject {
    TrackableObject() { }
    ~TrackableObject() { g_destructor_count++; }
};

class UniquePtrTest_1046 : public ::testing::Test {
protected:
    void SetUp() override {
        g_destructor_count = 0;
    }
};

// Test default construction with nullptr
TEST_F(UniquePtrTest_1046, DefaultConstructionIsNull_1046) {
    Catch::Detail::unique_ptr<TestObject> ptr;
    EXPECT_FALSE(static_cast<bool>(ptr));
    EXPECT_EQ(ptr.get(), nullptr);
}

// Test explicit nullptr construction
TEST_F(UniquePtrTest_1046, NullptrConstruction_1046) {
    Catch::Detail::unique_ptr<TestObject> ptr(nullptr);
    EXPECT_FALSE(static_cast<bool>(ptr));
    EXPECT_EQ(ptr.get(), nullptr);
}

// Test construction with a raw pointer
TEST_F(UniquePtrTest_1046, RawPointerConstruction_1046) {
    TestObject* raw = new TestObject(42);
    Catch::Detail::unique_ptr<TestObject> ptr(raw);
    EXPECT_TRUE(static_cast<bool>(ptr));
    EXPECT_EQ(ptr.get(), raw);
    EXPECT_EQ(ptr->value, 42);
}

// Test dereference operator
TEST_F(UniquePtrTest_1046, DereferenceOperator_1046) {
    Catch::Detail::unique_ptr<TestObject> ptr(new TestObject(99));
    EXPECT_EQ((*ptr).value, 99);
}

// Test arrow operator
TEST_F(UniquePtrTest_1046, ArrowOperator_1046) {
    Catch::Detail::unique_ptr<TestObject> ptr(new TestObject(77));
    EXPECT_EQ(ptr->value, 77);
}

// Test get() returns the managed pointer
TEST_F(UniquePtrTest_1046, GetReturnsPointer_1046) {
    TestObject* raw = new TestObject(10);
    Catch::Detail::unique_ptr<TestObject> ptr(raw);
    EXPECT_EQ(ptr.get(), raw);
}

// Test explicit bool conversion - true case
TEST_F(UniquePtrTest_1046, BoolConversionTrue_1046) {
    Catch::Detail::unique_ptr<TestObject> ptr(new TestObject(1));
    EXPECT_TRUE(static_cast<bool>(ptr));
}

// Test explicit bool conversion - false case
TEST_F(UniquePtrTest_1046, BoolConversionFalse_1046) {
    Catch::Detail::unique_ptr<TestObject> ptr;
    EXPECT_FALSE(static_cast<bool>(ptr));
}

// Test move construction
TEST_F(UniquePtrTest_1046, MoveConstruction_1046) {
    TestObject* raw = new TestObject(55);
    Catch::Detail::unique_ptr<TestObject> ptr1(raw);
    Catch::Detail::unique_ptr<TestObject> ptr2(std::move(ptr1));
    
    EXPECT_EQ(ptr2.get(), raw);
    EXPECT_EQ(ptr2->value, 55);
    EXPECT_EQ(ptr1.get(), nullptr);
    EXPECT_FALSE(static_cast<bool>(ptr1));
}

// Test move assignment
TEST_F(UniquePtrTest_1046, MoveAssignment_1046) {
    TestObject* raw = new TestObject(33);
    Catch::Detail::unique_ptr<TestObject> ptr1(raw);
    Catch::Detail::unique_ptr<TestObject> ptr2;
    
    ptr2 = std::move(ptr1);
    
    EXPECT_EQ(ptr2.get(), raw);
    EXPECT_EQ(ptr2->value, 33);
    EXPECT_EQ(ptr1.get(), nullptr);
    EXPECT_FALSE(static_cast<bool>(ptr1));
}

// Test release()
TEST_F(UniquePtrTest_1046, Release_1046) {
    TestObject* raw = new TestObject(88);
    Catch::Detail::unique_ptr<TestObject> ptr(raw);
    
    TestObject* released = ptr.release();
    
    EXPECT_EQ(released, raw);
    EXPECT_EQ(ptr.get(), nullptr);
    EXPECT_FALSE(static_cast<bool>(ptr));
    
    delete released; // Clean up manually since release() transfers ownership
}

// Test reset() with nullptr (default)
TEST_F(UniquePtrTest_1046, ResetToNull_1046) {
    Catch::Detail::unique_ptr<TrackableObject> ptr(new TrackableObject());
    EXPECT_EQ(g_destructor_count, 0);
    
    ptr.reset();
    
    EXPECT_EQ(g_destructor_count, 1);
    EXPECT_EQ(ptr.get(), nullptr);
    EXPECT_FALSE(static_cast<bool>(ptr));
}

// Test reset() with a new pointer
TEST_F(UniquePtrTest_1046, ResetToNewPointer_1046) {
    Catch::Detail::unique_ptr<TrackableObject> ptr(new TrackableObject());
    EXPECT_EQ(g_destructor_count, 0);
    
    TrackableObject* newObj = new TrackableObject();
    ptr.reset(newObj);
    
    EXPECT_EQ(g_destructor_count, 1); // Old object destroyed
    EXPECT_EQ(ptr.get(), newObj);
    EXPECT_TRUE(static_cast<bool>(ptr));
}

// Test destructor destroys the managed object
TEST_F(UniquePtrTest_1046, DestructorDestroysObject_1046) {
    {
        Catch::Detail::unique_ptr<TrackableObject> ptr(new TrackableObject());
        EXPECT_EQ(g_destructor_count, 0);
    }
    EXPECT_EQ(g_destructor_count, 1);
}

// Test destructor on null pointer doesn't crash
TEST_F(UniquePtrTest_1046, DestructorOnNull_1046) {
    {
        Catch::Detail::unique_ptr<TrackableObject> ptr;
    }
    EXPECT_EQ(g_destructor_count, 0);
}

// Test move construction from derived type
TEST_F(UniquePtrTest_1046, MoveConstructionFromDerived_1046) {
    DerivedObject* raw = new DerivedObject(10, 20);
    Catch::Detail::unique_ptr<DerivedObject> derivedPtr(raw);
    Catch::Detail::unique_ptr<TestObject> basePtr(std::move(derivedPtr));
    
    EXPECT_EQ(basePtr.get(), raw);
    EXPECT_EQ(basePtr->value, 10);
    EXPECT_EQ(derivedPtr.get(), nullptr);
}

// Test move assignment from derived type
TEST_F(UniquePtrTest_1046, MoveAssignmentFromDerived_1046) {
    DerivedObject* raw = new DerivedObject(15, 25);
    Catch::Detail::unique_ptr<DerivedObject> derivedPtr(raw);
    Catch::Detail::unique_ptr<TestObject> basePtr;
    
    basePtr = std::move(derivedPtr);
    
    EXPECT_EQ(basePtr.get(), raw);
    EXPECT_EQ(basePtr->value, 15);
    EXPECT_EQ(derivedPtr.get(), nullptr);
}

// Test release on null pointer
TEST_F(UniquePtrTest_1046, ReleaseOnNull_1046) {
    Catch::Detail::unique_ptr<TestObject> ptr;
    TestObject* released = ptr.release();
    EXPECT_EQ(released, nullptr);
}

// Test reset on null pointer (no-op basically)
TEST_F(UniquePtrTest_1046, ResetOnNullPtr_1046) {
    Catch::Detail::unique_ptr<TestObject> ptr;
    ptr.reset(nullptr);
    EXPECT_EQ(ptr.get(), nullptr);
    EXPECT_FALSE(static_cast<bool>(ptr));
}

// Test move assignment replaces and destroys existing object
TEST_F(UniquePtrTest_1046, MoveAssignmentDestroysExisting_1046) {
    Catch::Detail::unique_ptr<TrackableObject> ptr1(new TrackableObject());
    Catch::Detail::unique_ptr<TrackableObject> ptr2(new TrackableObject());
    EXPECT_EQ(g_destructor_count, 0);
    
    ptr1 = std::move(ptr2);
    
    // The old object held by ptr1 should be destroyed
    EXPECT_EQ(g_destructor_count, 1);
    EXPECT_TRUE(static_cast<bool>(ptr1));
    EXPECT_FALSE(static_cast<bool>(ptr2));
}

// Test multiple resets
TEST_F(UniquePtrTest_1046, MultipleResets_1046) {
    Catch::Detail::unique_ptr<TrackableObject> ptr(new TrackableObject());
    EXPECT_EQ(g_destructor_count, 0);
    
    ptr.reset(new TrackableObject());
    EXPECT_EQ(g_destructor_count, 1);
    
    ptr.reset(new TrackableObject());
    EXPECT_EQ(g_destructor_count, 2);
    
    ptr.reset();
    EXPECT_EQ(g_destructor_count, 3);
    EXPECT_EQ(ptr.get(), nullptr);
}

// Test that copy construction is deleted (compile-time check expressed as a type trait)
TEST_F(UniquePtrTest_1046, NotCopyConstructible_1046) {
    EXPECT_FALSE(std::is_copy_constructible<Catch::Detail::unique_ptr<TestObject>>::value);
}

// Test that copy assignment is deleted
TEST_F(UniquePtrTest_1046, NotCopyAssignable_1046) {
    EXPECT_FALSE(std::is_copy_assignable<Catch::Detail::unique_ptr<TestObject>>::value);
}

// Test that move constructible
TEST_F(UniquePtrTest_1046, IsMoveConstructible_1046) {
    EXPECT_TRUE(std::is_move_constructible<Catch::Detail::unique_ptr<TestObject>>::value);
}

// Test that move assignable
TEST_F(UniquePtrTest_1046, IsMoveAssignable_1046) {
    EXPECT_TRUE(std::is_move_assignable<Catch::Detail::unique_ptr<TestObject>>::value);
}

// Test self-move-assignment (edge case)
TEST_F(UniquePtrTest_1046, SelfMoveAssignment_1046) {
    Catch::Detail::unique_ptr<TestObject> ptr(new TestObject(42));
    TestObject* raw = ptr.get();
    
    // Self-move is generally undefined, but let's ensure no crash at minimum
    // This is somewhat implementation-defined behavior
    ptr = std::move(ptr);
    // We don't assert specific behavior for self-move as it's UB-adjacent
}

// Test modifying object through dereferenced pointer
TEST_F(UniquePtrTest_1046, ModifyThroughDereference_1046) {
    Catch::Detail::unique_ptr<TestObject> ptr(new TestObject(0));
    (*ptr).value = 100;
    EXPECT_EQ(ptr->value, 100);
}

// Test modifying object through arrow operator
TEST_F(UniquePtrTest_1046, ModifyThroughArrow_1046) {
    Catch::Detail::unique_ptr<TestObject> ptr(new TestObject(0));
    ptr->value = 200;
    EXPECT_EQ((*ptr).value, 200);
}
