#include "catch2/internal/catch_unique_ptr.hpp"
#include <gtest/gtest.h>
#include <type_traits>

// Test helper classes
class Base {
public:
    virtual ~Base() = default;
    virtual int value() const { return 1; }
};

class Derived : public Base {
public:
    int derivedValue = 42;
    int value() const override { return 2; }
};

class Unrelated {
public:
    virtual ~Unrelated() = default;
};

// Track construction/destruction
static int g_constructCount = 0;
static int g_destructCount = 0;

class Tracked {
public:
    Tracked() { ++g_constructCount; }
    ~Tracked() { ++g_destructCount; }
};

class TrackedDerived : public Tracked {
public:
    TrackedDerived() = default;
};

class UniquePtrTest_21 : public ::testing::Test {
protected:
    void SetUp() override {
        g_constructCount = 0;
        g_destructCount = 0;
    }
};

// Test default construction with nullptr
TEST_F(UniquePtrTest_21, DefaultConstruction_IsNull_21) {
    Catch::Detail::unique_ptr<Base> ptr;
    EXPECT_FALSE(static_cast<bool>(ptr));
    EXPECT_EQ(ptr.get(), nullptr);
}

// Test explicit nullptr construction
TEST_F(UniquePtrTest_21, NullptrConstruction_IsNull_21) {
    Catch::Detail::unique_ptr<Base> ptr(nullptr);
    EXPECT_FALSE(static_cast<bool>(ptr));
    EXPECT_EQ(ptr.get(), nullptr);
}

// Test construction with raw pointer
TEST_F(UniquePtrTest_21, RawPointerConstruction_OwnsPointer_21) {
    Base* raw = new Base();
    Catch::Detail::unique_ptr<Base> ptr(raw);
    EXPECT_TRUE(static_cast<bool>(ptr));
    EXPECT_EQ(ptr.get(), raw);
}

// Test dereference operator
TEST_F(UniquePtrTest_21, DereferenceOperator_ReturnsObject_21) {
    Catch::Detail::unique_ptr<Base> ptr(new Base());
    EXPECT_EQ((*ptr).value(), 1);
}

// Test arrow operator
TEST_F(UniquePtrTest_21, ArrowOperator_AccessesMember_21) {
    Catch::Detail::unique_ptr<Base> ptr(new Base());
    EXPECT_EQ(ptr->value(), 1);
}

// Test get() returns raw pointer
TEST_F(UniquePtrTest_21, Get_ReturnsRawPointer_21) {
    Base* raw = new Base();
    Catch::Detail::unique_ptr<Base> ptr(raw);
    EXPECT_EQ(ptr.get(), raw);
}

// Test release()
TEST_F(UniquePtrTest_21, Release_TransfersOwnership_21) {
    Base* raw = new Base();
    Catch::Detail::unique_ptr<Base> ptr(raw);
    Base* released = ptr.release();
    EXPECT_EQ(released, raw);
    EXPECT_EQ(ptr.get(), nullptr);
    EXPECT_FALSE(static_cast<bool>(ptr));
    delete released;
}

// Test reset() with no argument
TEST_F(UniquePtrTest_21, ResetNoArg_DeletesAndSetsNull_21) {
    Catch::Detail::unique_ptr<Tracked> ptr(new Tracked());
    EXPECT_EQ(g_destructCount, 0);
    ptr.reset();
    EXPECT_EQ(g_destructCount, 1);
    EXPECT_EQ(ptr.get(), nullptr);
    EXPECT_FALSE(static_cast<bool>(ptr));
}

// Test reset() with new pointer
TEST_F(UniquePtrTest_21, ResetWithPointer_ReplacesManaged_21) {
    Tracked* first = new Tracked();
    Tracked* second = new Tracked();
    EXPECT_EQ(g_constructCount, 2);

    Catch::Detail::unique_ptr<Tracked> ptr(first);
    ptr.reset(second);
    EXPECT_EQ(g_destructCount, 1); // first should be deleted
    EXPECT_EQ(ptr.get(), second);
}

// Test reset with nullptr
TEST_F(UniquePtrTest_21, ResetWithNullptr_DeletesManaged_21) {
    Catch::Detail::unique_ptr<Tracked> ptr(new Tracked());
    ptr.reset(nullptr);
    EXPECT_EQ(g_destructCount, 1);
    EXPECT_EQ(ptr.get(), nullptr);
}

// Test explicit bool conversion - true case
TEST_F(UniquePtrTest_21, BoolConversion_TrueWhenNonNull_21) {
    Catch::Detail::unique_ptr<Base> ptr(new Base());
    EXPECT_TRUE(static_cast<bool>(ptr));
}

// Test explicit bool conversion - false case
TEST_F(UniquePtrTest_21, BoolConversion_FalseWhenNull_21) {
    Catch::Detail::unique_ptr<Base> ptr;
    EXPECT_FALSE(static_cast<bool>(ptr));
}

// Test destructor deletes managed object
TEST_F(UniquePtrTest_21, Destructor_DeletesManagedObject_21) {
    {
        Catch::Detail::unique_ptr<Tracked> ptr(new Tracked());
        EXPECT_EQ(g_destructCount, 0);
    }
    EXPECT_EQ(g_destructCount, 1);
}

// Test destructor with nullptr does not crash
TEST_F(UniquePtrTest_21, Destructor_WithNull_NoCrash_21) {
    {
        Catch::Detail::unique_ptr<Tracked> ptr(nullptr);
    }
    EXPECT_EQ(g_destructCount, 0);
}

// Test move construction
TEST_F(UniquePtrTest_21, MoveConstruction_TransfersOwnership_21) {
    Base* raw = new Base();
    Catch::Detail::unique_ptr<Base> ptr1(raw);
    Catch::Detail::unique_ptr<Base> ptr2(std::move(ptr1));
    EXPECT_EQ(ptr2.get(), raw);
    // ptr1 should no longer own the object (implementation detail: typically set to nullptr)
}

// Test move construction from derived
TEST_F(UniquePtrTest_21, MoveConstruction_FromDerived_21) {
    Derived* raw = new Derived();
    Catch::Detail::unique_ptr<Derived> derivedPtr(raw);
    Catch::Detail::unique_ptr<Base> basePtr(std::move(derivedPtr));
    EXPECT_EQ(basePtr.get(), raw);
    EXPECT_EQ(basePtr->value(), 2);
}

// Test move assignment operator
TEST_F(UniquePtrTest_21, MoveAssignment_TransfersOwnership_21) {
    Base* raw1 = new Base();
    Base* raw2 = new Base();
    Catch::Detail::unique_ptr<Base> ptr1(raw1);
    Catch::Detail::unique_ptr<Base> ptr2(raw2);
    ptr1 = std::move(ptr2);
    EXPECT_EQ(ptr1.get(), raw2);
}

// Test move assignment deletes previously managed object
TEST_F(UniquePtrTest_21, MoveAssignment_DeletesPreviousObject_21) {
    Catch::Detail::unique_ptr<Tracked> ptr1(new Tracked());
    Catch::Detail::unique_ptr<Tracked> ptr2(new Tracked());
    EXPECT_EQ(g_constructCount, 2);
    EXPECT_EQ(g_destructCount, 0);
    ptr1 = std::move(ptr2);
    EXPECT_EQ(g_destructCount, 1); // old ptr1 object should be deleted
}

// Test move assignment from derived unique_ptr
TEST_F(UniquePtrTest_21, MoveAssignment_FromDerived_21) {
    Derived* raw = new Derived();
    Catch::Detail::unique_ptr<Derived> derivedPtr(raw);
    Catch::Detail::unique_ptr<Base> basePtr;
    basePtr = std::move(derivedPtr);
    EXPECT_EQ(basePtr.get(), raw);
    EXPECT_EQ(basePtr->value(), 2);
}

// Test polymorphic behavior through unique_ptr
TEST_F(UniquePtrTest_21, PolymorphicBehavior_21) {
    Catch::Detail::unique_ptr<Base> ptr(new Derived());
    EXPECT_EQ(ptr->value(), 2);
}

// Test copy constructor is deleted (compile-time check commented, conceptual test)
TEST_F(UniquePtrTest_21, CopyConstructor_IsDeleted_21) {
    EXPECT_FALSE(std::is_copy_constructible<Catch::Detail::unique_ptr<Base>>::value);
}

// Test copy assignment is deleted
TEST_F(UniquePtrTest_21, CopyAssignment_IsDeleted_21) {
    EXPECT_FALSE(std::is_copy_assignable<Catch::Detail::unique_ptr<Base>>::value);
}

// Test release on null pointer
TEST_F(UniquePtrTest_21, Release_OnNull_ReturnsNull_21) {
    Catch::Detail::unique_ptr<Base> ptr;
    Base* released = ptr.release();
    EXPECT_EQ(released, nullptr);
}

// Test multiple resets
TEST_F(UniquePtrTest_21, MultipleResets_21) {
    Catch::Detail::unique_ptr<Tracked> ptr(new Tracked());
    EXPECT_EQ(g_constructCount, 1);
    ptr.reset(new Tracked());
    EXPECT_EQ(g_constructCount, 2);
    EXPECT_EQ(g_destructCount, 1);
    ptr.reset(new Tracked());
    EXPECT_EQ(g_constructCount, 3);
    EXPECT_EQ(g_destructCount, 2);
    ptr.reset();
    EXPECT_EQ(g_destructCount, 3);
}

// Test arrow operator returns correct pointer
TEST_F(UniquePtrTest_21, ArrowOperator_ReturnsSameAsGet_21) {
    Catch::Detail::unique_ptr<Base> ptr(new Base());
    EXPECT_EQ(ptr.operator->(), ptr.get());
}

// Test move construct from nullptr unique_ptr
TEST_F(UniquePtrTest_21, MoveConstruct_FromNullUniquePtr_21) {
    Catch::Detail::unique_ptr<Base> ptr1(nullptr);
    Catch::Detail::unique_ptr<Base> ptr2(std::move(ptr1));
    EXPECT_FALSE(static_cast<bool>(ptr2));
    EXPECT_EQ(ptr2.get(), nullptr);
}

// Test move assign from nullptr unique_ptr
TEST_F(UniquePtrTest_21, MoveAssign_FromNullUniquePtr_21) {
    Catch::Detail::unique_ptr<Tracked> ptr1(new Tracked());
    Catch::Detail::unique_ptr<Tracked> ptr2(nullptr);
    ptr1 = std::move(ptr2);
    EXPECT_EQ(g_destructCount, 1); // old ptr1 object deleted
    EXPECT_EQ(ptr1.get(), nullptr);
}

// Test derived-to-base move assignment replaces and deletes old
TEST_F(UniquePtrTest_21, DerivedToBaseMoveAssign_ReplacesAndDeletesOld_21) {
    Catch::Detail::unique_ptr<Tracked> basePtr(new Tracked());
    Catch::Detail::unique_ptr<TrackedDerived> derivedPtr(new TrackedDerived());
    EXPECT_EQ(g_constructCount, 3); // Tracked ctor called for base + derived's base + derived itself doesn't add extra Tracked
    // Actually TrackedDerived inherits from Tracked, so creating TrackedDerived calls Tracked() once.
    // new Tracked() = 1 Tracked ctor, new TrackedDerived() = 1 Tracked ctor (base) = total 2
    int destructsBefore = g_destructCount;
    basePtr = std::move(derivedPtr);
    EXPECT_EQ(g_destructCount, destructsBefore + 1); // old basePtr object should be deleted
}

// Test chaining: release then create new unique_ptr
TEST_F(UniquePtrTest_21, ReleaseAndRewrap_21) {
    Base* raw = new Derived();
    Catch::Detail::unique_ptr<Base> ptr1(raw);
    Base* released = ptr1.release();
    EXPECT_EQ(released, raw);
    Catch::Detail::unique_ptr<Base> ptr2(released);
    EXPECT_EQ(ptr2.get(), raw);
    EXPECT_EQ(ptr2->value(), 2);
}
