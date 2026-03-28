#include "catch2/internal/catch_unique_ptr.hpp"
#include <gtest/gtest.h>
#include <type_traits>

// A simple test class to use with unique_ptr
struct TestObject {
    int value;
    static int instance_count;
    
    TestObject() : value(0) { ++instance_count; }
    explicit TestObject(int v) : value(v) { ++instance_count; }
    virtual ~TestObject() { --instance_count; }
};

int TestObject::instance_count = 0;

struct DerivedTestObject : public TestObject {
    int extra;
    DerivedTestObject() : TestObject(), extra(0) {}
    explicit DerivedTestObject(int v, int e = 0) : TestObject(v), extra(e) {}
    ~DerivedTestObject() override = default;
};

class UniquePtrTest_27 : public ::testing::Test {
protected:
    void SetUp() override {
        TestObject::instance_count = 0;
    }
    void TearDown() override {
        // Verify no leaks in each test
    }
};

// Test default construction (nullptr)
TEST_F(UniquePtrTest_27, DefaultConstructionIsNull_27) {
    Catch::Detail::unique_ptr<TestObject> ptr;
    EXPECT_FALSE(static_cast<bool>(ptr));
    EXPECT_EQ(ptr.get(), nullptr);
}

// Test construction with nullptr_t
TEST_F(UniquePtrTest_27, NullptrConstruction_27) {
    Catch::Detail::unique_ptr<TestObject> ptr(nullptr);
    EXPECT_FALSE(static_cast<bool>(ptr));
    EXPECT_EQ(ptr.get(), nullptr);
}

// Test construction with raw pointer
TEST_F(UniquePtrTest_27, ExplicitPointerConstruction_27) {
    TestObject* raw = new TestObject(42);
    Catch::Detail::unique_ptr<TestObject> ptr(raw);
    EXPECT_TRUE(static_cast<bool>(ptr));
    EXPECT_EQ(ptr.get(), raw);
    EXPECT_EQ(ptr->value, 42);
    EXPECT_EQ(TestObject::instance_count, 1);
}

// Test destructor deletes object
TEST_F(UniquePtrTest_27, DestructorDeletesObject_27) {
    {
        Catch::Detail::unique_ptr<TestObject> ptr(new TestObject(10));
        EXPECT_EQ(TestObject::instance_count, 1);
    }
    EXPECT_EQ(TestObject::instance_count, 0);
}

// Test dereference operator
TEST_F(UniquePtrTest_27, DereferenceOperator_27) {
    Catch::Detail::unique_ptr<TestObject> ptr(new TestObject(99));
    TestObject& ref = *ptr;
    EXPECT_EQ(ref.value, 99);
}

// Test arrow operator
TEST_F(UniquePtrTest_27, ArrowOperator_27) {
    Catch::Detail::unique_ptr<TestObject> ptr(new TestObject(55));
    EXPECT_EQ(ptr->value, 55);
}

// Test get() returns raw pointer
TEST_F(UniquePtrTest_27, GetReturnsRawPointer_27) {
    TestObject* raw = new TestObject(7);
    Catch::Detail::unique_ptr<TestObject> ptr(raw);
    EXPECT_EQ(ptr.get(), raw);
}

// Test reset with no argument (sets to nullptr and deletes)
TEST_F(UniquePtrTest_27, ResetToNull_27) {
    Catch::Detail::unique_ptr<TestObject> ptr(new TestObject(1));
    EXPECT_EQ(TestObject::instance_count, 1);
    ptr.reset();
    EXPECT_EQ(TestObject::instance_count, 0);
    EXPECT_FALSE(static_cast<bool>(ptr));
    EXPECT_EQ(ptr.get(), nullptr);
}

// Test reset with new pointer
TEST_F(UniquePtrTest_27, ResetWithNewPointer_27) {
    Catch::Detail::unique_ptr<TestObject> ptr(new TestObject(1));
    EXPECT_EQ(TestObject::instance_count, 1);
    TestObject* newObj = new TestObject(2);
    EXPECT_EQ(TestObject::instance_count, 2);
    ptr.reset(newObj);
    EXPECT_EQ(TestObject::instance_count, 1);
    EXPECT_EQ(ptr.get(), newObj);
    EXPECT_EQ(ptr->value, 2);
}

// Test reset on null pointer (should be safe)
TEST_F(UniquePtrTest_27, ResetOnNullPtr_27) {
    Catch::Detail::unique_ptr<TestObject> ptr;
    ptr.reset();
    EXPECT_FALSE(static_cast<bool>(ptr));
    EXPECT_EQ(ptr.get(), nullptr);
}

// Test release returns pointer and sets to null
TEST_F(UniquePtrTest_27, ReleaseReturnsPointerAndNullifiesOwnership_27) {
    TestObject* raw = new TestObject(33);
    Catch::Detail::unique_ptr<TestObject> ptr(raw);
    TestObject* released = ptr.release();
    EXPECT_EQ(released, raw);
    EXPECT_EQ(ptr.get(), nullptr);
    EXPECT_FALSE(static_cast<bool>(ptr));
    // Object should still be alive
    EXPECT_EQ(TestObject::instance_count, 1);
    delete released;
    EXPECT_EQ(TestObject::instance_count, 0);
}

// Test release on null pointer
TEST_F(UniquePtrTest_27, ReleaseOnNullReturnsNull_27) {
    Catch::Detail::unique_ptr<TestObject> ptr;
    TestObject* released = ptr.release();
    EXPECT_EQ(released, nullptr);
}

// Test bool conversion operator with valid pointer
TEST_F(UniquePtrTest_27, BoolConversionTrue_27) {
    Catch::Detail::unique_ptr<TestObject> ptr(new TestObject(1));
    EXPECT_TRUE(static_cast<bool>(ptr));
}

// Test bool conversion operator with null pointer
TEST_F(UniquePtrTest_27, BoolConversionFalse_27) {
    Catch::Detail::unique_ptr<TestObject> ptr;
    EXPECT_FALSE(static_cast<bool>(ptr));
}

// Test move constructor
TEST_F(UniquePtrTest_27, MoveConstructor_27) {
    TestObject* raw = new TestObject(77);
    Catch::Detail::unique_ptr<TestObject> ptr1(raw);
    Catch::Detail::unique_ptr<TestObject> ptr2(std::move(ptr1));
    
    EXPECT_EQ(ptr2.get(), raw);
    EXPECT_EQ(ptr2->value, 77);
    // ptr1 should be null after move
    EXPECT_EQ(ptr1.get(), nullptr);
    EXPECT_FALSE(static_cast<bool>(ptr1));
    EXPECT_EQ(TestObject::instance_count, 1);
}

// Test move assignment operator
TEST_F(UniquePtrTest_27, MoveAssignment_27) {
    Catch::Detail::unique_ptr<TestObject> ptr1(new TestObject(11));
    Catch::Detail::unique_ptr<TestObject> ptr2(new TestObject(22));
    EXPECT_EQ(TestObject::instance_count, 2);
    
    TestObject* raw1Before = ptr1.get();
    ptr2 = std::move(ptr1);
    
    // ptr2 should now own ptr1's old object, and ptr2's old object should be deleted
    EXPECT_EQ(ptr2.get(), raw1Before);
    EXPECT_EQ(ptr2->value, 11);
    EXPECT_EQ(ptr1.get(), nullptr);
    EXPECT_EQ(TestObject::instance_count, 1);
}

// Test move constructor from derived type
TEST_F(UniquePtrTest_27, MoveConstructFromDerived_27) {
    DerivedTestObject* raw = new DerivedTestObject(5, 10);
    Catch::Detail::unique_ptr<DerivedTestObject> derivedPtr(raw);
    Catch::Detail::unique_ptr<TestObject> basePtr(std::move(derivedPtr));
    
    EXPECT_EQ(basePtr.get(), raw);
    EXPECT_EQ(basePtr->value, 5);
    EXPECT_EQ(derivedPtr.get(), nullptr);
}

// Test move assignment from derived type
TEST_F(UniquePtrTest_27, MoveAssignFromDerived_27) {
    Catch::Detail::unique_ptr<TestObject> basePtr(new TestObject(100));
    Catch::Detail::unique_ptr<DerivedTestObject> derivedPtr(new DerivedTestObject(200, 300));
    EXPECT_EQ(TestObject::instance_count, 2);
    
    DerivedTestObject* derivedRaw = derivedPtr.get();
    basePtr = std::move(derivedPtr);
    
    EXPECT_EQ(basePtr.get(), derivedRaw);
    EXPECT_EQ(basePtr->value, 200);
    EXPECT_EQ(derivedPtr.get(), nullptr);
    EXPECT_EQ(TestObject::instance_count, 1);
}

// Test copy constructor is deleted (compile-time check via type trait)
TEST_F(UniquePtrTest_27, CopyConstructorIsDeleted_27) {
    EXPECT_FALSE(std::is_copy_constructible<Catch::Detail::unique_ptr<TestObject>>::value);
}

// Test copy assignment is deleted
TEST_F(UniquePtrTest_27, CopyAssignmentIsDeleted_27) {
    EXPECT_FALSE(std::is_copy_assignable<Catch::Detail::unique_ptr<TestObject>>::value);
}

// Test multiple resets
TEST_F(UniquePtrTest_27, MultipleResets_27) {
    Catch::Detail::unique_ptr<TestObject> ptr(new TestObject(1));
    EXPECT_EQ(TestObject::instance_count, 1);
    
    ptr.reset(new TestObject(2));
    EXPECT_EQ(TestObject::instance_count, 1);
    EXPECT_EQ(ptr->value, 2);
    
    ptr.reset(new TestObject(3));
    EXPECT_EQ(TestObject::instance_count, 1);
    EXPECT_EQ(ptr->value, 3);
    
    ptr.reset();
    EXPECT_EQ(TestObject::instance_count, 0);
}

// Test move from null unique_ptr
TEST_F(UniquePtrTest_27, MoveFromNull_27) {
    Catch::Detail::unique_ptr<TestObject> ptr1;
    Catch::Detail::unique_ptr<TestObject> ptr2(std::move(ptr1));
    EXPECT_EQ(ptr2.get(), nullptr);
    EXPECT_EQ(ptr1.get(), nullptr);
}

// Test move assign to null from null
TEST_F(UniquePtrTest_27, MoveAssignNullToNull_27) {
    Catch::Detail::unique_ptr<TestObject> ptr1;
    Catch::Detail::unique_ptr<TestObject> ptr2;
    ptr2 = std::move(ptr1);
    EXPECT_EQ(ptr2.get(), nullptr);
    EXPECT_EQ(ptr1.get(), nullptr);
}

// Test with primitive-like types (int)
TEST_F(UniquePtrTest_27, WorksWithIntType_27) {
    Catch::Detail::unique_ptr<int> ptr(new int(42));
    EXPECT_TRUE(static_cast<bool>(ptr));
    EXPECT_EQ(*ptr, 42);
    EXPECT_NE(ptr.get(), nullptr);
    
    int* released = ptr.release();
    EXPECT_EQ(*released, 42);
    EXPECT_EQ(ptr.get(), nullptr);
    delete released;
}

// Test reset with nullptr explicitly
TEST_F(UniquePtrTest_27, ResetWithExplicitNullptr_27) {
    Catch::Detail::unique_ptr<TestObject> ptr(new TestObject(5));
    EXPECT_EQ(TestObject::instance_count, 1);
    ptr.reset(nullptr);
    EXPECT_EQ(TestObject::instance_count, 0);
    EXPECT_EQ(ptr.get(), nullptr);
}

// Test that arrow operator returns correct pointer
TEST_F(UniquePtrTest_27, ArrowOperatorReturnsCorrectPointer_27) {
    TestObject* raw = new TestObject(123);
    Catch::Detail::unique_ptr<TestObject> ptr(raw);
    EXPECT_EQ(ptr.operator->(), raw);
}
