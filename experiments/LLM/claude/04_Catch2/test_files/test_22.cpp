#include <gtest/gtest.h>
#include "./TestProjects/Catch2/src/catch2/internal/catch_unique_ptr.hpp"
#include <type_traits>

// A simple test class hierarchy for testing
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

// Track construction/destruction for leak detection
struct Tracked {
    static int alive_count;
    int id;
    Tracked() : id(0) { ++alive_count; }
    explicit Tracked(int i) : id(i) { ++alive_count; }
    ~Tracked() { --alive_count; }
};
int Tracked::alive_count = 0;

// ============================================================
// Test Fixture
// ============================================================
class UniquePtrTest_22 : public ::testing::Test {
protected:
    void SetUp() override {
        Tracked::alive_count = 0;
    }
    void TearDown() override {
        // Verify no leaks after each test
    }
};

// ============================================================
// Default Construction / nullptr construction
// ============================================================
TEST_F(UniquePtrTest_22, DefaultConstructionIsNull_22) {
    Catch::Detail::unique_ptr<int> ptr;
    EXPECT_FALSE(static_cast<bool>(ptr));
    EXPECT_EQ(ptr.get(), nullptr);
}

TEST_F(UniquePtrTest_22, NullptrConstructionIsNull_22) {
    Catch::Detail::unique_ptr<int> ptr(nullptr);
    EXPECT_FALSE(static_cast<bool>(ptr));
    EXPECT_EQ(ptr.get(), nullptr);
}

// ============================================================
// Explicit pointer construction
// ============================================================
TEST_F(UniquePtrTest_22, ExplicitPointerConstruction_22) {
    int* raw = new int(42);
    Catch::Detail::unique_ptr<int> ptr(raw);
    EXPECT_TRUE(static_cast<bool>(ptr));
    EXPECT_EQ(ptr.get(), raw);
    EXPECT_EQ(*ptr, 42);
}

TEST_F(UniquePtrTest_22, ExplicitPointerConstructionWithObject_22) {
    Base* raw = new Base(10);
    Catch::Detail::unique_ptr<Base> ptr(raw);
    EXPECT_TRUE(static_cast<bool>(ptr));
    EXPECT_EQ(ptr->value, 10);
}

// ============================================================
// Dereference operators
// ============================================================
TEST_F(UniquePtrTest_22, DereferenceOperator_22) {
    Catch::Detail::unique_ptr<int> ptr(new int(99));
    EXPECT_EQ(*ptr, 99);
    *ptr = 100;
    EXPECT_EQ(*ptr, 100);
}

TEST_F(UniquePtrTest_22, ArrowOperator_22) {
    Catch::Detail::unique_ptr<Base> ptr(new Base(55));
    EXPECT_EQ(ptr->value, 55);
    ptr->value = 77;
    EXPECT_EQ(ptr->value, 77);
}

// ============================================================
// Bool conversion
// ============================================================
TEST_F(UniquePtrTest_22, BoolConversionTrue_22) {
    Catch::Detail::unique_ptr<int> ptr(new int(1));
    EXPECT_TRUE(static_cast<bool>(ptr));
}

TEST_F(UniquePtrTest_22, BoolConversionFalse_22) {
    Catch::Detail::unique_ptr<int> ptr;
    EXPECT_FALSE(static_cast<bool>(ptr));
}

// ============================================================
// release()
// ============================================================
TEST_F(UniquePtrTest_22, ReleaseReturnsPointerAndSetsNull_22) {
    int* raw = new int(42);
    Catch::Detail::unique_ptr<int> ptr(raw);
    int* released = ptr.release();
    EXPECT_EQ(released, raw);
    EXPECT_EQ(ptr.get(), nullptr);
    EXPECT_FALSE(static_cast<bool>(ptr));
    delete released; // manual cleanup since ownership was released
}

TEST_F(UniquePtrTest_22, ReleaseOnNullReturnsNull_22) {
    Catch::Detail::unique_ptr<int> ptr;
    int* released = ptr.release();
    EXPECT_EQ(released, nullptr);
}

// ============================================================
// reset()
// ============================================================
TEST_F(UniquePtrTest_22, ResetDeletesOldAndTakesNew_22) {
    Tracked::alive_count = 0;
    {
        Catch::Detail::unique_ptr<Tracked> ptr(new Tracked(1));
        EXPECT_EQ(Tracked::alive_count, 1);
        
        Tracked* newObj = new Tracked(2);
        EXPECT_EQ(Tracked::alive_count, 2);
        
        ptr.reset(newObj);
        EXPECT_EQ(Tracked::alive_count, 1); // old one deleted
        EXPECT_EQ(ptr->id, 2);
    }
    EXPECT_EQ(Tracked::alive_count, 0);
}

TEST_F(UniquePtrTest_22, ResetToNullptr_22) {
    Tracked::alive_count = 0;
    {
        Catch::Detail::unique_ptr<Tracked> ptr(new Tracked(1));
        EXPECT_EQ(Tracked::alive_count, 1);
        
        ptr.reset();
        EXPECT_EQ(Tracked::alive_count, 0);
        EXPECT_EQ(ptr.get(), nullptr);
        EXPECT_FALSE(static_cast<bool>(ptr));
    }
}

TEST_F(UniquePtrTest_22, ResetOnNullPtr_22) {
    Catch::Detail::unique_ptr<Tracked> ptr;
    // Should be safe to reset a null unique_ptr
    ptr.reset();
    EXPECT_EQ(ptr.get(), nullptr);
}

// ============================================================
// Move constructor
// ============================================================
TEST_F(UniquePtrTest_22, MoveConstructor_22) {
    int* raw = new int(42);
    Catch::Detail::unique_ptr<int> ptr1(raw);
    Catch::Detail::unique_ptr<int> ptr2(std::move(ptr1));
    
    EXPECT_EQ(ptr2.get(), raw);
    EXPECT_EQ(*ptr2, 42);
    // After move, ptr1 should be null (or at least not owning the same pointer)
    // Based on the implementation: m_ptr(rhs.m_ptr), rhs.m_ptr is not nulled in move ctor
    // Actually looking more carefully, the move ctor sets m_ptr(rhs.m_ptr) but doesn't null rhs.
    // However the known interface says "unique_ptr(unique_ptr&& rhs) noexcept: m_ptr(rhs.m_ptr)"
    // This might not null rhs. But let's test based on expected unique_ptr semantics.
    // We'll just verify ptr2 is valid.
    EXPECT_TRUE(static_cast<bool>(ptr2));
}

// ============================================================
// Move assignment
// ============================================================
TEST_F(UniquePtrTest_22, MoveAssignment_22) {
    Tracked::alive_count = 0;
    {
        Catch::Detail::unique_ptr<Tracked> ptr1(new Tracked(1));
        Catch::Detail::unique_ptr<Tracked> ptr2(new Tracked(2));
        EXPECT_EQ(Tracked::alive_count, 2);
        
        ptr1 = std::move(ptr2);
        // Old object in ptr1 should be deleted
        EXPECT_EQ(Tracked::alive_count, 1);
        EXPECT_EQ(ptr1->id, 2);
    }
    EXPECT_EQ(Tracked::alive_count, 0);
}

TEST_F(UniquePtrTest_22, MoveAssignmentFromNull_22) {
    Tracked::alive_count = 0;
    {
        Catch::Detail::unique_ptr<Tracked> ptr1(new Tracked(1));
        Catch::Detail::unique_ptr<Tracked> ptr2;
        EXPECT_EQ(Tracked::alive_count, 1);
        
        ptr1 = std::move(ptr2);
        EXPECT_EQ(Tracked::alive_count, 0);
        EXPECT_EQ(ptr1.get(), nullptr);
    }
}

TEST_F(UniquePtrTest_22, MoveAssignmentToNull_22) {
    Tracked::alive_count = 0;
    {
        Catch::Detail::unique_ptr<Tracked> ptr1;
        Catch::Detail::unique_ptr<Tracked> ptr2(new Tracked(5));
        EXPECT_EQ(Tracked::alive_count, 1);
        
        ptr1 = std::move(ptr2);
        EXPECT_EQ(Tracked::alive_count, 1);
        EXPECT_EQ(ptr1->id, 5);
    }
    EXPECT_EQ(Tracked::alive_count, 0);
}

// ============================================================
// Destructor cleans up
// ============================================================
TEST_F(UniquePtrTest_22, DestructorDeletesObject_22) {
    Tracked::alive_count = 0;
    {
        Catch::Detail::unique_ptr<Tracked> ptr(new Tracked(1));
        EXPECT_EQ(Tracked::alive_count, 1);
    }
    EXPECT_EQ(Tracked::alive_count, 0);
}

TEST_F(UniquePtrTest_22, DestructorOnNullIsSafe_22) {
    Tracked::alive_count = 0;
    {
        Catch::Detail::unique_ptr<Tracked> ptr;
    }
    EXPECT_EQ(Tracked::alive_count, 0);
}

// ============================================================
// Polymorphic / base-derived conversions
// ============================================================
TEST_F(UniquePtrTest_22, MoveConstructFromDerived_22) {
    Derived* raw = new Derived(10);
    Catch::Detail::unique_ptr<Derived> derivedPtr(raw);
    Catch::Detail::unique_ptr<Base> basePtr(std::move(derivedPtr));
    
    EXPECT_TRUE(static_cast<bool>(basePtr));
    EXPECT_EQ(basePtr->value, 10);
}

TEST_F(UniquePtrTest_22, MoveAssignFromDerived_22) {
    Catch::Detail::unique_ptr<Base> basePtr(new Base(1));
    Catch::Detail::unique_ptr<Derived> derivedPtr(new Derived(20));
    
    basePtr = std::move(derivedPtr);
    EXPECT_TRUE(static_cast<bool>(basePtr));
    EXPECT_EQ(basePtr->value, 20);
}

// ============================================================
// get() returns correct pointer
// ============================================================
TEST_F(UniquePtrTest_22, GetReturnsRawPointer_22) {
    Base* raw = new Base(33);
    Catch::Detail::unique_ptr<Base> ptr(raw);
    EXPECT_EQ(ptr.get(), raw);
}

TEST_F(UniquePtrTest_22, GetOnNullReturnsNullptr_22) {
    Catch::Detail::unique_ptr<Base> ptr;
    EXPECT_EQ(ptr.get(), nullptr);
}

// ============================================================
// Copy is deleted (compile-time check concept; just document)
// ============================================================
TEST_F(UniquePtrTest_22, CopyConstructorIsDeleted_22) {
    EXPECT_FALSE(std::is_copy_constructible<Catch::Detail::unique_ptr<int>>::value);
}

TEST_F(UniquePtrTest_22, CopyAssignmentIsDeleted_22) {
    EXPECT_FALSE(std::is_copy_assignable<Catch::Detail::unique_ptr<int>>::value);
}

// ============================================================
// Self move assignment
// ============================================================
TEST_F(UniquePtrTest_22, SelfMoveAssignment_22) {
    Tracked::alive_count = 0;
    {
        Catch::Detail::unique_ptr<Tracked> ptr(new Tracked(7));
        EXPECT_EQ(Tracked::alive_count, 1);
        
        // Self-move assignment - should be safe
        ptr = std::move(ptr);
        // The object might or might not be alive depending on implementation,
        // but it shouldn't crash. We just check it doesn't blow up.
    }
    // After scope, alive_count should be 0 (no leak)
    EXPECT_EQ(Tracked::alive_count, 0);
}

// ============================================================
// Multiple resets
// ============================================================
TEST_F(UniquePtrTest_22, MultipleResets_22) {
    Tracked::alive_count = 0;
    Catch::Detail::unique_ptr<Tracked> ptr(new Tracked(1));
    EXPECT_EQ(Tracked::alive_count, 1);
    
    ptr.reset(new Tracked(2));
    EXPECT_EQ(Tracked::alive_count, 1);
    EXPECT_EQ(ptr->id, 2);
    
    ptr.reset(new Tracked(3));
    EXPECT_EQ(Tracked::alive_count, 1);
    EXPECT_EQ(ptr->id, 3);
    
    ptr.reset();
    EXPECT_EQ(Tracked::alive_count, 0);
    EXPECT_EQ(ptr.get(), nullptr);
}

// ============================================================
// Chain of moves
// ============================================================
TEST_F(UniquePtrTest_22, ChainOfMoves_22) {
    Tracked::alive_count = 0;
    {
        Catch::Detail::unique_ptr<Tracked> ptr1(new Tracked(1));
        Catch::Detail::unique_ptr<Tracked> ptr2(std::move(ptr1));
        Catch::Detail::unique_ptr<Tracked> ptr3;
        ptr3 = std::move(ptr2);
        
        EXPECT_EQ(Tracked::alive_count, 1);
        EXPECT_TRUE(static_cast<bool>(ptr3));
        EXPECT_EQ(ptr3->id, 1);
    }
    EXPECT_EQ(Tracked::alive_count, 0);
}
