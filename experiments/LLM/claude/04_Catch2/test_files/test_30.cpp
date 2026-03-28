#include "catch2/internal/catch_unique_ptr.hpp"
#include <gtest/gtest.h>
#include <type_traits>

// Test helper classes
struct Base {
    int value;
    virtual ~Base() = default;
    Base() : value(0) {}
    explicit Base(int v) : value(v) {}
};

struct Derived : public Base {
    int extra;
    Derived() : Base(), extra(0) {}
    explicit Derived(int v) : Base(v), extra(v * 2) {}
};

// Track destruction for leak/double-free detection
struct DestructionTracker {
    static int destruction_count;
    int id;
    explicit DestructionTracker(int i = 0) : id(i) {}
    ~DestructionTracker() { ++destruction_count; }
};
int DestructionTracker::destruction_count = 0;

class UniquePtrTest_30 : public ::testing::Test {
protected:
    void SetUp() override {
        DestructionTracker::destruction_count = 0;
    }
};

// === Construction Tests ===

TEST_F(UniquePtrTest_30, DefaultConstructor_IsNull_30) {
    Catch::Detail::unique_ptr<int> ptr;
    EXPECT_FALSE(static_cast<bool>(ptr));
    EXPECT_EQ(ptr.get(), nullptr);
}

TEST_F(UniquePtrTest_30, NullptrConstructor_IsNull_30) {
    Catch::Detail::unique_ptr<int> ptr(nullptr);
    EXPECT_FALSE(static_cast<bool>(ptr));
    EXPECT_EQ(ptr.get(), nullptr);
}

TEST_F(UniquePtrTest_30, ExplicitPointerConstructor_OwnsPointer_30) {
    int* raw = new int(42);
    Catch::Detail::unique_ptr<int> ptr(raw);
    EXPECT_TRUE(static_cast<bool>(ptr));
    EXPECT_EQ(ptr.get(), raw);
    EXPECT_EQ(*ptr, 42);
}

// === Move Construction ===

TEST_F(UniquePtrTest_30, MoveConstructor_TransfersOwnership_30) {
    Catch::Detail::unique_ptr<int> original(new int(99));
    int* raw = original.get();
    Catch::Detail::unique_ptr<int> moved(std::move(original));
    
    EXPECT_EQ(moved.get(), raw);
    EXPECT_EQ(*moved, 99);
    // Original should no longer own the pointer
    EXPECT_EQ(original.get(), nullptr);
    EXPECT_FALSE(static_cast<bool>(original));
}

TEST_F(UniquePtrTest_30, MoveConstructorFromDerived_TransfersOwnership_30) {
    Catch::Detail::unique_ptr<Derived> derived(new Derived(5));
    Derived* raw = derived.get();
    Catch::Detail::unique_ptr<Base> base(std::move(derived));
    
    EXPECT_EQ(base.get(), raw);
    EXPECT_EQ(base->value, 5);
    EXPECT_EQ(derived.get(), nullptr);
}

// === Move Assignment ===

TEST_F(UniquePtrTest_30, MoveAssignment_TransfersOwnership_30) {
    Catch::Detail::unique_ptr<int> a(new int(1));
    Catch::Detail::unique_ptr<int> b(new int(2));
    int* raw_b = b.get();
    
    a = std::move(b);
    EXPECT_EQ(a.get(), raw_b);
    EXPECT_EQ(*a, 2);
    EXPECT_EQ(b.get(), nullptr);
}

TEST_F(UniquePtrTest_30, MoveAssignment_DeletesPreviousObject_30) {
    DestructionTracker::destruction_count = 0;
    {
        Catch::Detail::unique_ptr<DestructionTracker> a(new DestructionTracker(1));
        Catch::Detail::unique_ptr<DestructionTracker> b(new DestructionTracker(2));
        
        a = std::move(b);  // Should destroy the original object in 'a'
        EXPECT_EQ(DestructionTracker::destruction_count, 1);
    }
    // Both should be destroyed now (one from move assignment, one from destructor)
    EXPECT_EQ(DestructionTracker::destruction_count, 2);
}

TEST_F(UniquePtrTest_30, MoveAssignmentFromDerived_30) {
    Catch::Detail::unique_ptr<Derived> derived(new Derived(7));
    Catch::Detail::unique_ptr<Base> base(new Base(3));
    
    base = std::move(derived);
    EXPECT_EQ(base->value, 7);
    EXPECT_EQ(derived.get(), nullptr);
}

// === Destructor ===

TEST_F(UniquePtrTest_30, Destructor_DeletesOwnedObject_30) {
    DestructionTracker::destruction_count = 0;
    {
        Catch::Detail::unique_ptr<DestructionTracker> ptr(new DestructionTracker(1));
    }
    EXPECT_EQ(DestructionTracker::destruction_count, 1);
}

TEST_F(UniquePtrTest_30, Destructor_NullDoesNotCrash_30) {
    DestructionTracker::destruction_count = 0;
    {
        Catch::Detail::unique_ptr<DestructionTracker> ptr;
    }
    EXPECT_EQ(DestructionTracker::destruction_count, 0);
}

// === Dereference Operators ===

TEST_F(UniquePtrTest_30, DereferenceOperator_ReturnsValue_30) {
    Catch::Detail::unique_ptr<int> ptr(new int(123));
    EXPECT_EQ(*ptr, 123);
}

TEST_F(UniquePtrTest_30, ArrowOperator_AccessesMember_30) {
    Catch::Detail::unique_ptr<Base> ptr(new Base(456));
    EXPECT_EQ(ptr->value, 456);
}

TEST_F(UniquePtrTest_30, DereferenceOperator_CanModifyValue_30) {
    Catch::Detail::unique_ptr<int> ptr(new int(10));
    *ptr = 20;
    EXPECT_EQ(*ptr, 20);
}

TEST_F(UniquePtrTest_30, ArrowOperator_CanModifyMember_30) {
    Catch::Detail::unique_ptr<Base> ptr(new Base(10));
    ptr->value = 20;
    EXPECT_EQ(ptr->value, 20);
}

// === get() ===

TEST_F(UniquePtrTest_30, Get_ReturnsRawPointer_30) {
    int* raw = new int(77);
    Catch::Detail::unique_ptr<int> ptr(raw);
    EXPECT_EQ(ptr.get(), raw);
}

TEST_F(UniquePtrTest_30, Get_ReturnsNullForDefault_30) {
    Catch::Detail::unique_ptr<int> ptr;
    EXPECT_EQ(ptr.get(), nullptr);
}

// === reset() ===

TEST_F(UniquePtrTest_30, Reset_WithNewPointer_30) {
    Catch::Detail::unique_ptr<int> ptr(new int(1));
    int* new_raw = new int(2);
    ptr.reset(new_raw);
    EXPECT_EQ(ptr.get(), new_raw);
    EXPECT_EQ(*ptr, 2);
}

TEST_F(UniquePtrTest_30, Reset_DeletesOldObject_30) {
    DestructionTracker::destruction_count = 0;
    Catch::Detail::unique_ptr<DestructionTracker> ptr(new DestructionTracker(1));
    ptr.reset(new DestructionTracker(2));
    EXPECT_EQ(DestructionTracker::destruction_count, 1);  // Old one destroyed
    EXPECT_EQ(ptr->id, 2);
}

TEST_F(UniquePtrTest_30, Reset_ToNull_30) {
    DestructionTracker::destruction_count = 0;
    Catch::Detail::unique_ptr<DestructionTracker> ptr(new DestructionTracker(1));
    ptr.reset();
    EXPECT_EQ(DestructionTracker::destruction_count, 1);
    EXPECT_EQ(ptr.get(), nullptr);
    EXPECT_FALSE(static_cast<bool>(ptr));
}

TEST_F(UniquePtrTest_30, Reset_NullToNull_30) {
    Catch::Detail::unique_ptr<int> ptr;
    ptr.reset();
    EXPECT_EQ(ptr.get(), nullptr);
}

TEST_F(UniquePtrTest_30, Reset_WithNullptrExplicit_30) {
    DestructionTracker::destruction_count = 0;
    Catch::Detail::unique_ptr<DestructionTracker> ptr(new DestructionTracker(1));
    ptr.reset(nullptr);
    EXPECT_EQ(DestructionTracker::destruction_count, 1);
    EXPECT_EQ(ptr.get(), nullptr);
}

// === release() ===

TEST_F(UniquePtrTest_30, Release_ReturnsPointerAndReleasesOwnership_30) {
    int* raw = new int(55);
    Catch::Detail::unique_ptr<int> ptr(raw);
    int* released = ptr.release();
    
    EXPECT_EQ(released, raw);
    EXPECT_EQ(ptr.get(), nullptr);
    EXPECT_FALSE(static_cast<bool>(ptr));
    
    delete released;  // Manual cleanup since ownership was released
}

TEST_F(UniquePtrTest_30, Release_DoesNotDeleteObject_30) {
    DestructionTracker::destruction_count = 0;
    DestructionTracker* released;
    {
        Catch::Detail::unique_ptr<DestructionTracker> ptr(new DestructionTracker(1));
        released = ptr.release();
    }
    EXPECT_EQ(DestructionTracker::destruction_count, 0);  // Not destroyed
    delete released;
    EXPECT_EQ(DestructionTracker::destruction_count, 1);
}

TEST_F(UniquePtrTest_30, Release_NullReturnsNull_30) {
    Catch::Detail::unique_ptr<int> ptr;
    int* released = ptr.release();
    EXPECT_EQ(released, nullptr);
}

// === operator bool ===

TEST_F(UniquePtrTest_30, BoolConversion_TrueWhenNonNull_30) {
    Catch::Detail::unique_ptr<int> ptr(new int(1));
    EXPECT_TRUE(static_cast<bool>(ptr));
}

TEST_F(UniquePtrTest_30, BoolConversion_FalseWhenNull_30) {
    Catch::Detail::unique_ptr<int> ptr;
    EXPECT_FALSE(static_cast<bool>(ptr));
}

TEST_F(UniquePtrTest_30, BoolConversion_FalseAfterRelease_30) {
    Catch::Detail::unique_ptr<int> ptr(new int(1));
    int* raw = ptr.release();
    EXPECT_FALSE(static_cast<bool>(ptr));
    delete raw;
}

TEST_F(UniquePtrTest_30, BoolConversion_FalseAfterReset_30) {
    Catch::Detail::unique_ptr<int> ptr(new int(1));
    ptr.reset();
    EXPECT_FALSE(static_cast<bool>(ptr));
}

TEST_F(UniquePtrTest_30, BoolConversion_FalseAfterMove_30) {
    Catch::Detail::unique_ptr<int> ptr(new int(1));
    Catch::Detail::unique_ptr<int> other(std::move(ptr));
    EXPECT_FALSE(static_cast<bool>(ptr));
    EXPECT_TRUE(static_cast<bool>(other));
}

// === swap ===

TEST_F(UniquePtrTest_30, Swap_ExchangesOwnership_30) {
    int* raw1 = new int(1);
    int* raw2 = new int(2);
    Catch::Detail::unique_ptr<int> a(raw1);
    Catch::Detail::unique_ptr<int> b(raw2);
    
    swap(a, b);
    
    EXPECT_EQ(a.get(), raw2);
    EXPECT_EQ(b.get(), raw1);
    EXPECT_EQ(*a, 2);
    EXPECT_EQ(*b, 1);
}

TEST_F(UniquePtrTest_30, Swap_WithNull_30) {
    int* raw = new int(42);
    Catch::Detail::unique_ptr<int> a(raw);
    Catch::Detail::unique_ptr<int> b;
    
    swap(a, b);
    
    EXPECT_EQ(a.get(), nullptr);
    EXPECT_EQ(b.get(), raw);
    EXPECT_FALSE(static_cast<bool>(a));
    EXPECT_TRUE(static_cast<bool>(b));
}

TEST_F(UniquePtrTest_30, Swap_BothNull_30) {
    Catch::Detail::unique_ptr<int> a;
    Catch::Detail::unique_ptr<int> b;
    
    swap(a, b);
    
    EXPECT_EQ(a.get(), nullptr);
    EXPECT_EQ(b.get(), nullptr);
}

// === Polymorphism ===

TEST_F(UniquePtrTest_30, Polymorphism_DerivedToBase_30) {
    Catch::Detail::unique_ptr<Base> ptr(new Derived(10));
    EXPECT_EQ(ptr->value, 10);
}

// === Copy is deleted (compile-time check — just verify no issues with move) ===

TEST_F(UniquePtrTest_30, CopyConstructorDeleted_Verification_30) {
    EXPECT_FALSE(std::is_copy_constructible<Catch::Detail::unique_ptr<int>>::value);
}

TEST_F(UniquePtrTest_30, CopyAssignmentDeleted_Verification_30) {
    EXPECT_FALSE(std::is_copy_assignable<Catch::Detail::unique_ptr<int>>::value);
}

TEST_F(UniquePtrTest_30, MoveConstructible_Verification_30) {
    EXPECT_TRUE(std::is_move_constructible<Catch::Detail::unique_ptr<int>>::value);
}

TEST_F(UniquePtrTest_30, MoveAssignable_Verification_30) {
    EXPECT_TRUE(std::is_move_assignable<Catch::Detail::unique_ptr<int>>::value);
}

// === Multiple operations sequence ===

TEST_F(UniquePtrTest_30, SequenceOfOperations_30) {
    DestructionTracker::destruction_count = 0;
    
    Catch::Detail::unique_ptr<DestructionTracker> ptr(new DestructionTracker(1));
    EXPECT_TRUE(static_cast<bool>(ptr));
    EXPECT_EQ(ptr->id, 1);
    
    ptr.reset(new DestructionTracker(2));
    EXPECT_EQ(DestructionTracker::destruction_count, 1);
    EXPECT_EQ(ptr->id, 2);
    
    DestructionTracker* raw = ptr.release();
    EXPECT_EQ(DestructionTracker::destruction_count, 1);  // No additional destruction
    EXPECT_FALSE(static_cast<bool>(ptr));
    
    ptr.reset(raw);  // Take ownership again
    EXPECT_TRUE(static_cast<bool>(ptr));
    EXPECT_EQ(ptr->id, 2);
    
    ptr.reset();
    EXPECT_EQ(DestructionTracker::destruction_count, 2);
    EXPECT_FALSE(static_cast<bool>(ptr));
}
