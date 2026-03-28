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
static int g_destruction_count = 0;

struct TrackableObject {
    TrackableObject() { }
    ~TrackableObject() { g_destruction_count++; }
};

class UniquePtrTest_23 : public ::testing::Test {
protected:
    void SetUp() override {
        g_destruction_count = 0;
    }
};

// Test default construction (nullptr)
TEST_F(UniquePtrTest_23, DefaultConstructionIsNull_23) {
    Catch::Detail::unique_ptr<TestObject> ptr;
    EXPECT_FALSE(static_cast<bool>(ptr));
    EXPECT_EQ(ptr.get(), nullptr);
}

// Test construction with nullptr
TEST_F(UniquePtrTest_23, NullptrConstruction_23) {
    Catch::Detail::unique_ptr<TestObject> ptr(nullptr);
    EXPECT_FALSE(static_cast<bool>(ptr));
    EXPECT_EQ(ptr.get(), nullptr);
}

// Test construction with a raw pointer
TEST_F(UniquePtrTest_23, ExplicitPointerConstruction_23) {
    TestObject* raw = new TestObject(42);
    Catch::Detail::unique_ptr<TestObject> ptr(raw);
    EXPECT_TRUE(static_cast<bool>(ptr));
    EXPECT_EQ(ptr.get(), raw);
    EXPECT_EQ(ptr->value, 42);
}

// Test dereference operator
TEST_F(UniquePtrTest_23, DereferenceOperator_23) {
    Catch::Detail::unique_ptr<TestObject> ptr(new TestObject(99));
    EXPECT_EQ((*ptr).value, 99);
}

// Test arrow operator
TEST_F(UniquePtrTest_23, ArrowOperator_23) {
    Catch::Detail::unique_ptr<TestObject> ptr(new TestObject(77));
    EXPECT_EQ(ptr->value, 77);
}

// Test get() returns the stored pointer
TEST_F(UniquePtrTest_23, GetReturnsStoredPointer_23) {
    TestObject* raw = new TestObject(10);
    Catch::Detail::unique_ptr<TestObject> ptr(raw);
    EXPECT_EQ(ptr.get(), raw);
}

// Test release() returns pointer and sets internal to null
TEST_F(UniquePtrTest_23, ReleaseReturnsPointerAndNullifiesInternal_23) {
    TestObject* raw = new TestObject(55);
    Catch::Detail::unique_ptr<TestObject> ptr(raw);
    TestObject* released = ptr.release();
    EXPECT_EQ(released, raw);
    EXPECT_EQ(ptr.get(), nullptr);
    EXPECT_FALSE(static_cast<bool>(ptr));
    delete released; // manual cleanup since release transfers ownership
}

// Test reset() with a new pointer
TEST_F(UniquePtrTest_23, ResetWithNewPointer_23) {
    Catch::Detail::unique_ptr<TrackableObject> ptr(new TrackableObject());
    EXPECT_EQ(g_destruction_count, 0);
    ptr.reset(new TrackableObject());
    EXPECT_EQ(g_destruction_count, 1); // old object destroyed
    EXPECT_TRUE(static_cast<bool>(ptr));
}

// Test reset() with nullptr
TEST_F(UniquePtrTest_23, ResetWithNullptr_23) {
    Catch::Detail::unique_ptr<TrackableObject> ptr(new TrackableObject());
    EXPECT_EQ(g_destruction_count, 0);
    ptr.reset(nullptr);
    EXPECT_EQ(g_destruction_count, 1);
    EXPECT_FALSE(static_cast<bool>(ptr));
    EXPECT_EQ(ptr.get(), nullptr);
}

// Test reset() with default argument
TEST_F(UniquePtrTest_23, ResetDefaultArgument_23) {
    Catch::Detail::unique_ptr<TrackableObject> ptr(new TrackableObject());
    ptr.reset();
    EXPECT_EQ(g_destruction_count, 1);
    EXPECT_EQ(ptr.get(), nullptr);
}

// Test destructor deletes the managed object
TEST_F(UniquePtrTest_23, DestructorDeletesObject_23) {
    {
        Catch::Detail::unique_ptr<TrackableObject> ptr(new TrackableObject());
        EXPECT_EQ(g_destruction_count, 0);
    }
    EXPECT_EQ(g_destruction_count, 1);
}

// Test destructor of null unique_ptr does not crash
TEST_F(UniquePtrTest_23, DestructorOnNullDoesNotCrash_23) {
    {
        Catch::Detail::unique_ptr<TestObject> ptr;
    }
    // If we reach here, no crash occurred
    SUCCEED();
}

// Test move constructor
TEST_F(UniquePtrTest_23, MoveConstruction_23) {
    TestObject* raw = new TestObject(33);
    Catch::Detail::unique_ptr<TestObject> ptr1(raw);
    Catch::Detail::unique_ptr<TestObject> ptr2(std::move(ptr1));
    EXPECT_EQ(ptr2.get(), raw);
    EXPECT_EQ(ptr2->value, 33);
    // After move, the source should be null
    EXPECT_EQ(ptr1.get(), nullptr);
    EXPECT_FALSE(static_cast<bool>(ptr1));
}

// Test move assignment
TEST_F(UniquePtrTest_23, MoveAssignment_23) {
    Catch::Detail::unique_ptr<TrackableObject> ptr1(new TrackableObject());
    Catch::Detail::unique_ptr<TrackableObject> ptr2(new TrackableObject());
    EXPECT_EQ(g_destruction_count, 0);
    
    ptr1 = std::move(ptr2);
    // The old object in ptr1 should have been destroyed
    EXPECT_EQ(g_destruction_count, 1);
    EXPECT_TRUE(static_cast<bool>(ptr1));
    EXPECT_FALSE(static_cast<bool>(ptr2));
}

// Test move construction from derived type
TEST_F(UniquePtrTest_23, MoveConstructionFromDerived_23) {
    DerivedObject* raw = new DerivedObject(10, 20);
    Catch::Detail::unique_ptr<DerivedObject> derived_ptr(raw);
    Catch::Detail::unique_ptr<TestObject> base_ptr(std::move(derived_ptr));
    
    EXPECT_EQ(base_ptr.get(), raw);
    EXPECT_EQ(base_ptr->value, 10);
    EXPECT_EQ(derived_ptr.get(), nullptr);
}

// Test move assignment from derived type
TEST_F(UniquePtrTest_23, MoveAssignmentFromDerived_23) {
    Catch::Detail::unique_ptr<TestObject> base_ptr(new TestObject(5));
    Catch::Detail::unique_ptr<DerivedObject> derived_ptr(new DerivedObject(15, 25));
    
    DerivedObject* raw_derived = derived_ptr.get();
    base_ptr = std::move(derived_ptr);
    
    EXPECT_EQ(base_ptr.get(), raw_derived);
    EXPECT_EQ(base_ptr->value, 15);
    EXPECT_EQ(derived_ptr.get(), nullptr);
}

// Test explicit bool conversion - true case
TEST_F(UniquePtrTest_23, BoolConversionTrue_23) {
    Catch::Detail::unique_ptr<TestObject> ptr(new TestObject(1));
    EXPECT_TRUE(static_cast<bool>(ptr));
}

// Test explicit bool conversion - false case
TEST_F(UniquePtrTest_23, BoolConversionFalse_23) {
    Catch::Detail::unique_ptr<TestObject> ptr;
    EXPECT_FALSE(static_cast<bool>(ptr));
}

// Test copy constructor is deleted (compile-time check via type traits)
TEST_F(UniquePtrTest_23, CopyConstructorIsDeleted_23) {
    EXPECT_FALSE(std::is_copy_constructible<Catch::Detail::unique_ptr<TestObject>>::value);
}

// Test copy assignment is deleted
TEST_F(UniquePtrTest_23, CopyAssignmentIsDeleted_23) {
    EXPECT_FALSE(std::is_copy_assignable<Catch::Detail::unique_ptr<TestObject>>::value);
}

// Test multiple resets
TEST_F(UniquePtrTest_23, MultipleResets_23) {
    Catch::Detail::unique_ptr<TrackableObject> ptr(new TrackableObject());
    ptr.reset(new TrackableObject());
    EXPECT_EQ(g_destruction_count, 1);
    ptr.reset(new TrackableObject());
    EXPECT_EQ(g_destruction_count, 2);
    ptr.reset();
    EXPECT_EQ(g_destruction_count, 3);
    EXPECT_EQ(ptr.get(), nullptr);
}

// Test release on null ptr
TEST_F(UniquePtrTest_23, ReleaseOnNull_23) {
    Catch::Detail::unique_ptr<TestObject> ptr;
    TestObject* released = ptr.release();
    EXPECT_EQ(released, nullptr);
    EXPECT_EQ(ptr.get(), nullptr);
}

// Test move assignment to self-like scenario (move from empty to empty)
TEST_F(UniquePtrTest_23, MoveEmptyToEmpty_23) {
    Catch::Detail::unique_ptr<TestObject> ptr1;
    Catch::Detail::unique_ptr<TestObject> ptr2;
    ptr1 = std::move(ptr2);
    EXPECT_EQ(ptr1.get(), nullptr);
    EXPECT_EQ(ptr2.get(), nullptr);
}

// Test that moving from a valid ptr and then the source is usable as null
TEST_F(UniquePtrTest_23, SourceAfterMoveIsReusable_23) {
    Catch::Detail::unique_ptr<TestObject> ptr1(new TestObject(100));
    Catch::Detail::unique_ptr<TestObject> ptr2(std::move(ptr1));
    
    // ptr1 is now null, but should be reusable
    ptr1.reset(new TestObject(200));
    EXPECT_TRUE(static_cast<bool>(ptr1));
    EXPECT_EQ(ptr1->value, 200);
}

// Test modifying the object through the pointer
TEST_F(UniquePtrTest_23, ModifyThroughPointer_23) {
    Catch::Detail::unique_ptr<TestObject> ptr(new TestObject(1));
    ptr->value = 42;
    EXPECT_EQ(ptr->value, 42);
    EXPECT_EQ((*ptr).value, 42);
    EXPECT_EQ(ptr.get()->value, 42);
}
