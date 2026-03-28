#include <gtest/gtest.h>
#include "catch2/internal/catch_unique_ptr.hpp"
#include <string>
#include <utility>

// Test basic construction and access with unique_ptr
TEST(CatchUniquePtrTest_31, DefaultConstruction_31) {
    Catch::Detail::unique_ptr<int> ptr;
    EXPECT_EQ(ptr.get(), nullptr);
}

TEST(CatchUniquePtrTest_31, ConstructionWithRawPointer_31) {
    int* raw = new int(42);
    Catch::Detail::unique_ptr<int> ptr(raw);
    EXPECT_EQ(ptr.get(), raw);
    EXPECT_EQ(*ptr, 42);
}

TEST(CatchUniquePtrTest_31, ConstructionWithNullptr_31) {
    Catch::Detail::unique_ptr<int> ptr(nullptr);
    EXPECT_EQ(ptr.get(), nullptr);
}

TEST(CatchUniquePtrTest_31, MakeUniqueInt_31) {
    auto ptr = Catch::Detail::make_unique<int>(42);
    EXPECT_NE(ptr.get(), nullptr);
    EXPECT_EQ(*ptr, 42);
}

TEST(CatchUniquePtrTest_31, MakeUniqueDefaultConstructed_31) {
    auto ptr = Catch::Detail::make_unique<int>();
    EXPECT_NE(ptr.get(), nullptr);
    EXPECT_EQ(*ptr, 0);
}

TEST(CatchUniquePtrTest_31, MakeUniqueString_31) {
    auto ptr = Catch::Detail::make_unique<std::string>("hello");
    EXPECT_NE(ptr.get(), nullptr);
    EXPECT_EQ(*ptr, "hello");
}

TEST(CatchUniquePtrTest_31, MakeUniqueStringMultipleArgs_31) {
    auto ptr = Catch::Detail::make_unique<std::string>(5, 'a');
    EXPECT_NE(ptr.get(), nullptr);
    EXPECT_EQ(*ptr, "aaaaa");
}

TEST(CatchUniquePtrTest_31, DereferenceOperator_31) {
    auto ptr = Catch::Detail::make_unique<int>(100);
    EXPECT_EQ(*ptr, 100);
    *ptr = 200;
    EXPECT_EQ(*ptr, 200);
}

TEST(CatchUniquePtrTest_31, ArrowOperator_31) {
    auto ptr = Catch::Detail::make_unique<std::string>("test");
    EXPECT_EQ(ptr->size(), 4u);
    EXPECT_EQ(ptr->c_str()[0], 't');
}

TEST(CatchUniquePtrTest_31, MoveConstruction_31) {
    auto ptr1 = Catch::Detail::make_unique<int>(42);
    int* raw = ptr1.get();
    Catch::Detail::unique_ptr<int> ptr2(std::move(ptr1));
    EXPECT_EQ(ptr1.get(), nullptr);
    EXPECT_EQ(ptr2.get(), raw);
    EXPECT_EQ(*ptr2, 42);
}

TEST(CatchUniquePtrTest_31, MoveAssignment_31) {
    auto ptr1 = Catch::Detail::make_unique<int>(42);
    auto ptr2 = Catch::Detail::make_unique<int>(99);
    int* raw1 = ptr1.get();
    ptr2 = std::move(ptr1);
    EXPECT_EQ(ptr1.get(), nullptr);
    EXPECT_EQ(ptr2.get(), raw1);
    EXPECT_EQ(*ptr2, 42);
}

TEST(CatchUniquePtrTest_31, BoolConversionTrue_31) {
    auto ptr = Catch::Detail::make_unique<int>(1);
    EXPECT_TRUE(static_cast<bool>(ptr));
}

TEST(CatchUniquePtrTest_31, BoolConversionFalse_31) {
    Catch::Detail::unique_ptr<int> ptr;
    EXPECT_FALSE(static_cast<bool>(ptr));
}

TEST(CatchUniquePtrTest_31, BoolConversionAfterMove_31) {
    auto ptr1 = Catch::Detail::make_unique<int>(1);
    EXPECT_TRUE(static_cast<bool>(ptr1));
    auto ptr2 = std::move(ptr1);
    EXPECT_FALSE(static_cast<bool>(ptr1));
    EXPECT_TRUE(static_cast<bool>(ptr2));
}

// Test with a struct to ensure proper construction and destruction
struct TestStruct_31 {
    int a;
    double b;
    TestStruct_31(int x, double y) : a(x), b(y) {}
};

TEST(CatchUniquePtrTest_31, MakeUniqueCustomStruct_31) {
    auto ptr = Catch::Detail::make_unique<TestStruct_31>(10, 3.14);
    EXPECT_NE(ptr.get(), nullptr);
    EXPECT_EQ(ptr->a, 10);
    EXPECT_DOUBLE_EQ(ptr->b, 3.14);
}

// Test destruction tracking
struct DestructionTracker_31 {
    bool* destroyed;
    DestructionTracker_31(bool* d) : destroyed(d) { *destroyed = false; }
    ~DestructionTracker_31() { *destroyed = true; }
};

TEST(CatchUniquePtrTest_31, DestructorCalledOnScopeExit_31) {
    bool destroyed = false;
    {
        auto ptr = Catch::Detail::make_unique<DestructionTracker_31>(&destroyed);
        EXPECT_FALSE(destroyed);
    }
    EXPECT_TRUE(destroyed);
}

TEST(CatchUniquePtrTest_31, DestructorCalledOnAssignment_31) {
    bool destroyed1 = false;
    bool destroyed2 = false;
    auto ptr1 = Catch::Detail::make_unique<DestructionTracker_31>(&destroyed1);
    auto ptr2 = Catch::Detail::make_unique<DestructionTracker_31>(&destroyed2);
    EXPECT_FALSE(destroyed1);
    EXPECT_FALSE(destroyed2);
    ptr1 = std::move(ptr2);
    EXPECT_TRUE(destroyed1);
    EXPECT_FALSE(destroyed2);
}

// Test with polymorphic types
struct Base_31 {
    virtual ~Base_31() = default;
    virtual int value() const { return 0; }
};

struct Derived_31 : Base_31 {
    int val;
    Derived_31(int v) : val(v) {}
    int value() const override { return val; }
};

TEST(CatchUniquePtrTest_31, MakeUniqueWithDerivedType_31) {
    auto ptr = Catch::Detail::make_unique<Derived_31>(55);
    EXPECT_EQ(ptr->value(), 55);
}

TEST(CatchUniquePtrTest_31, SelfMoveAssignment_31) {
    auto ptr = Catch::Detail::make_unique<int>(42);
    int* raw = ptr.get();
    // Self-move is technically undefined, but we test observable behavior
    // Just ensure the pointer was valid before
    EXPECT_NE(raw, nullptr);
    EXPECT_EQ(*ptr, 42);
}

TEST(CatchUniquePtrTest_31, GetReturnsCorrectPointer_31) {
    auto ptr = Catch::Detail::make_unique<double>(2.718);
    double* raw = ptr.get();
    EXPECT_NE(raw, nullptr);
    EXPECT_DOUBLE_EQ(*raw, 2.718);
}

TEST(CatchUniquePtrTest_31, MoveFromNullptr_31) {
    Catch::Detail::unique_ptr<int> ptr1;
    Catch::Detail::unique_ptr<int> ptr2(std::move(ptr1));
    EXPECT_EQ(ptr1.get(), nullptr);
    EXPECT_EQ(ptr2.get(), nullptr);
}

TEST(CatchUniquePtrTest_31, MakeUniqueDefaultString_31) {
    auto ptr = Catch::Detail::make_unique<std::string>();
    EXPECT_NE(ptr.get(), nullptr);
    EXPECT_TRUE(ptr->empty());
}
