#include <gtest/gtest.h>
#include "./TestProjects/Catch2/src/catch2/internal/catch_unique_ptr.hpp"

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

// Track destruction for certain tests
struct DestructionTracker {
    bool* destroyed;
    explicit DestructionTracker(bool* flag) : destroyed(flag) {}
    ~DestructionTracker() { *destroyed = true; }
};

using namespace Catch::Detail;

// ===================== Constructor Tests =====================

TEST(UniquePtrTest_29, DefaultConstructorIsNull_29) {
    unique_ptr<TestObject> ptr;
    EXPECT_FALSE(static_cast<bool>(ptr));
    EXPECT_EQ(ptr.get(), nullptr);
}

TEST(UniquePtrTest_29, NullptrConstructorIsNull_29) {
    unique_ptr<TestObject> ptr(nullptr);
    EXPECT_FALSE(static_cast<bool>(ptr));
    EXPECT_EQ(ptr.get(), nullptr);
}

TEST(UniquePtrTest_29, ExplicitPointerConstructor_29) {
    TestObject* raw = new TestObject(42);
    unique_ptr<TestObject> ptr(raw);
    EXPECT_TRUE(static_cast<bool>(ptr));
    EXPECT_EQ(ptr.get(), raw);
    EXPECT_EQ(ptr->value, 42);
}

// ===================== Move Constructor Tests =====================

TEST(UniquePtrTest_29, MoveConstructorTransfersOwnership_29) {
    unique_ptr<TestObject> ptr1(new TestObject(10));
    TestObject* raw = ptr1.get();
    unique_ptr<TestObject> ptr2(std::move(ptr1));
    
    EXPECT_EQ(ptr2.get(), raw);
    EXPECT_EQ(ptr2->value, 10);
    // After move, ptr1 should be null
    EXPECT_EQ(ptr1.get(), nullptr);
    EXPECT_FALSE(static_cast<bool>(ptr1));
}

TEST(UniquePtrTest_29, MoveConstructorFromDerived_29) {
    unique_ptr<DerivedObject> derived(new DerivedObject(5, 15));
    DerivedObject* raw = derived.get();
    unique_ptr<TestObject> base(std::move(derived));
    
    EXPECT_EQ(base.get(), raw);
    EXPECT_EQ(base->value, 5);
    EXPECT_EQ(derived.get(), nullptr);
}

// ===================== Move Assignment Tests =====================

TEST(UniquePtrTest_29, MoveAssignmentTransfersOwnership_29) {
    unique_ptr<TestObject> ptr1(new TestObject(20));
    unique_ptr<TestObject> ptr2(new TestObject(30));
    TestObject* raw1 = ptr1.get();
    
    ptr2 = std::move(ptr1);
    
    EXPECT_EQ(ptr2.get(), raw1);
    EXPECT_EQ(ptr2->value, 20);
    EXPECT_EQ(ptr1.get(), nullptr);
}

TEST(UniquePtrTest_29, MoveAssignmentFromDerived_29) {
    unique_ptr<DerivedObject> derived(new DerivedObject(7, 14));
    unique_ptr<TestObject> base(new TestObject(99));
    DerivedObject* raw = derived.get();
    
    base = std::move(derived);
    
    EXPECT_EQ(base.get(), raw);
    EXPECT_EQ(base->value, 7);
    EXPECT_EQ(derived.get(), nullptr);
}

// ===================== Destructor Tests =====================

TEST(UniquePtrTest_29, DestructorDeletesOwnedObject_29) {
    bool destroyed = false;
    {
        unique_ptr<DestructionTracker> ptr(new DestructionTracker(&destroyed));
        EXPECT_FALSE(destroyed);
    }
    EXPECT_TRUE(destroyed);
}

TEST(UniquePtrTest_29, DestructorOnNullptrIsNoOp_29) {
    // Should not crash
    {
        unique_ptr<TestObject> ptr;
    }
    // If we get here, no crash occurred
    SUCCEED();
}

// ===================== operator* Tests =====================

TEST(UniquePtrTest_29, DereferenceOperator_29) {
    unique_ptr<TestObject> ptr(new TestObject(77));
    TestObject& ref = *ptr;
    EXPECT_EQ(ref.value, 77);
}

TEST(UniquePtrTest_29, DereferenceOperatorModify_29) {
    unique_ptr<TestObject> ptr(new TestObject(10));
    (*ptr).value = 55;
    EXPECT_EQ(ptr->value, 55);
}

// ===================== operator-> Tests =====================

TEST(UniquePtrTest_29, ArrowOperator_29) {
    unique_ptr<TestObject> ptr(new TestObject(88));
    EXPECT_EQ(ptr->value, 88);
}

TEST(UniquePtrTest_29, ArrowOperatorModify_29) {
    unique_ptr<TestObject> ptr(new TestObject(1));
    ptr->value = 100;
    EXPECT_EQ(ptr->value, 100);
}

// ===================== get() Tests =====================

TEST(UniquePtrTest_29, GetReturnsRawPointer_29) {
    TestObject* raw = new TestObject(33);
    unique_ptr<TestObject> ptr(raw);
    EXPECT_EQ(ptr.get(), raw);
}

TEST(UniquePtrTest_29, GetReturnsNullForDefault_29) {
    unique_ptr<TestObject> ptr;
    EXPECT_EQ(ptr.get(), nullptr);
}

// ===================== reset() Tests =====================

TEST(UniquePtrTest_29, ResetToNull_29) {
    bool destroyed = false;
    unique_ptr<DestructionTracker> ptr(new DestructionTracker(&destroyed));
    EXPECT_FALSE(destroyed);
    
    ptr.reset();
    
    EXPECT_TRUE(destroyed);
    EXPECT_EQ(ptr.get(), nullptr);
    EXPECT_FALSE(static_cast<bool>(ptr));
}

TEST(UniquePtrTest_29, ResetToNewPointer_29) {
    bool destroyed1 = false;
    bool destroyed2 = false;
    
    unique_ptr<DestructionTracker> ptr(new DestructionTracker(&destroyed1));
    DestructionTracker* newObj = new DestructionTracker(&destroyed2);
    
    ptr.reset(newObj);
    
    EXPECT_TRUE(destroyed1);
    EXPECT_FALSE(destroyed2);
    EXPECT_EQ(ptr.get(), newObj);
}

TEST(UniquePtrTest_29, ResetNullPtrToNull_29) {
    unique_ptr<TestObject> ptr;
    ptr.reset(); // Should not crash
    EXPECT_EQ(ptr.get(), nullptr);
}

TEST(UniquePtrTest_29, ResetWithNullptrArgument_29) {
    bool destroyed = false;
    unique_ptr<DestructionTracker> ptr(new DestructionTracker(&destroyed));
    
    ptr.reset(nullptr);
    
    EXPECT_TRUE(destroyed);
    EXPECT_EQ(ptr.get(), nullptr);
}

// ===================== release() Tests =====================

TEST(UniquePtrTest_29, ReleaseReturnsPointerAndSetsNull_29) {
    TestObject* raw = new TestObject(50);
    unique_ptr<TestObject> ptr(raw);
    
    TestObject* released = ptr.release();
    
    EXPECT_EQ(released, raw);
    EXPECT_EQ(ptr.get(), nullptr);
    EXPECT_FALSE(static_cast<bool>(ptr));
    
    // We need to manually delete since ownership was released
    delete released;
}

TEST(UniquePtrTest_29, ReleaseDoesNotDestroy_29) {
    bool destroyed = false;
    unique_ptr<DestructionTracker> ptr(new DestructionTracker(&destroyed));
    
    DestructionTracker* released = ptr.release();
    
    EXPECT_FALSE(destroyed);
    EXPECT_EQ(ptr.get(), nullptr);
    
    delete released;
    EXPECT_TRUE(destroyed);
}

TEST(UniquePtrTest_29, ReleaseOnNullReturnsNull_29) {
    unique_ptr<TestObject> ptr;
    TestObject* released = ptr.release();
    EXPECT_EQ(released, nullptr);
}

// ===================== operator bool Tests =====================

TEST(UniquePtrTest_29, BoolOperatorTrueWhenNonNull_29) {
    unique_ptr<TestObject> ptr(new TestObject(1));
    EXPECT_TRUE(static_cast<bool>(ptr));
}

TEST(UniquePtrTest_29, BoolOperatorFalseWhenNull_29) {
    unique_ptr<TestObject> ptr;
    EXPECT_FALSE(static_cast<bool>(ptr));
}

TEST(UniquePtrTest_29, BoolOperatorFalseAfterRelease_29) {
    unique_ptr<TestObject> ptr(new TestObject(1));
    EXPECT_TRUE(static_cast<bool>(ptr));
    
    TestObject* released = ptr.release();
    EXPECT_FALSE(static_cast<bool>(ptr));
    delete released;
}

TEST(UniquePtrTest_29, BoolOperatorFalseAfterReset_29) {
    unique_ptr<TestObject> ptr(new TestObject(1));
    EXPECT_TRUE(static_cast<bool>(ptr));
    
    ptr.reset();
    EXPECT_FALSE(static_cast<bool>(ptr));
}

// ===================== Copy Prevention Tests =====================

// These are compile-time checks. If the code compiles, copy is disabled.
// We verify by static_assert or by the fact that copy construction/assignment are deleted.

TEST(UniquePtrTest_29, CopyConstructorIsDeleted_29) {
    EXPECT_FALSE(std::is_copy_constructible<unique_ptr<TestObject>>::value);
}

TEST(UniquePtrTest_29, CopyAssignmentIsDeleted_29) {
    EXPECT_FALSE(std::is_copy_assignable<unique_ptr<TestObject>>::value);
}

// ===================== Move Semantics Verification =====================

TEST(UniquePtrTest_29, IsMoveConstructible_29) {
    EXPECT_TRUE(std::is_move_constructible<unique_ptr<TestObject>>::value);
}

TEST(UniquePtrTest_29, IsMoveAssignable_29) {
    EXPECT_TRUE(std::is_move_assignable<unique_ptr<TestObject>>::value);
}

// ===================== Edge Cases =====================

TEST(UniquePtrTest_29, MoveAssignmentDestroysOldObject_29) {
    bool destroyed = false;
    unique_ptr<DestructionTracker> ptr1(new DestructionTracker(&destroyed));
    
    bool destroyed2 = false;
    unique_ptr<DestructionTracker> ptr2(new DestructionTracker(&destroyed2));
    
    ptr1 = std::move(ptr2);
    
    EXPECT_TRUE(destroyed); // Old object in ptr1 should be destroyed
    EXPECT_FALSE(destroyed2); // Object moved into ptr1 should still be alive
    EXPECT_EQ(ptr2.get(), nullptr);
}

TEST(UniquePtrTest_29, MultipleMoveOperations_29) {
    unique_ptr<TestObject> ptr1(new TestObject(100));
    TestObject* raw = ptr1.get();
    
    unique_ptr<TestObject> ptr2(std::move(ptr1));
    EXPECT_EQ(ptr2.get(), raw);
    EXPECT_EQ(ptr1.get(), nullptr);
    
    unique_ptr<TestObject> ptr3;
    ptr3 = std::move(ptr2);
    EXPECT_EQ(ptr3.get(), raw);
    EXPECT_EQ(ptr2.get(), nullptr);
    
    EXPECT_EQ(ptr3->value, 100);
}

TEST(UniquePtrTest_29, ResetMultipleTimes_29) {
    unique_ptr<TestObject> ptr(new TestObject(1));
    ptr.reset(new TestObject(2));
    EXPECT_EQ(ptr->value, 2);
    ptr.reset(new TestObject(3));
    EXPECT_EQ(ptr->value, 3);
    ptr.reset();
    EXPECT_EQ(ptr.get(), nullptr);
}
