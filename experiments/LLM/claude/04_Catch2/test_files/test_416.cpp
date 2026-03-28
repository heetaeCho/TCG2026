#include "catch2/internal/catch_optional.hpp"

#include <gtest/gtest.h>
#include <string>
#include <utility>

using Catch::Optional;

// ============================================================
// Default construction
// ============================================================

TEST(OptionalTest_416, DefaultConstructedIsNone_416) {
    Optional<int> opt;
    EXPECT_TRUE(opt.none());
    EXPECT_FALSE(opt.some());
}

TEST(OptionalTest_416, DefaultConstructedBoolConversionIsFalse_416) {
    Optional<int> opt;
    EXPECT_FALSE(static_cast<bool>(opt));
    EXPECT_TRUE(!opt);
}

// ============================================================
// Construction with a value
// ============================================================

TEST(OptionalTest_416, ConstructWithLvalueIsSome_416) {
    int val = 42;
    Optional<int> opt(val);
    EXPECT_TRUE(opt.some());
    EXPECT_FALSE(opt.none());
    EXPECT_EQ(*opt, 42);
}

TEST(OptionalTest_416, ConstructWithRvalueIsSome_416) {
    Optional<int> opt(99);
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, 99);
}

TEST(OptionalTest_416, ConstructWithStringValue_416) {
    std::string s = "hello";
    Optional<std::string> opt(s);
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, "hello");
}

TEST(OptionalTest_416, ConstructWithMoveStringValue_416) {
    std::string s = "world";
    Optional<std::string> opt(std::move(s));
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, "world");
}

// ============================================================
// Copy construction
// ============================================================

TEST(OptionalTest_416, CopyConstructFromNone_416) {
    Optional<int> a;
    Optional<int> b(a);
    EXPECT_TRUE(b.none());
}

TEST(OptionalTest_416, CopyConstructFromSome_416) {
    Optional<int> a(7);
    Optional<int> b(a);
    EXPECT_TRUE(b.some());
    EXPECT_EQ(*b, 7);
    // original unchanged
    EXPECT_EQ(*a, 7);
}

// ============================================================
// Move construction
// ============================================================

TEST(OptionalTest_416, MoveConstructFromNone_416) {
    Optional<int> a;
    Optional<int> b(std::move(a));
    EXPECT_TRUE(b.none());
}

TEST(OptionalTest_416, MoveConstructFromSome_416) {
    Optional<std::string> a(std::string("moved"));
    Optional<std::string> b(std::move(a));
    EXPECT_TRUE(b.some());
    EXPECT_EQ(*b, "moved");
}

// ============================================================
// Assignment operators
// ============================================================

TEST(OptionalTest_416, AssignValueToNone_416) {
    Optional<int> opt;
    opt = 10;
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, 10);
}

TEST(OptionalTest_416, AssignValueToSomeOverwrites_416) {
    Optional<int> opt(5);
    opt = 20;
    EXPECT_EQ(*opt, 20);
}

TEST(OptionalTest_416, AssignRvalueValue_416) {
    Optional<std::string> opt;
    std::string s = "rvalue";
    opt = std::move(s);
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, "rvalue");
}

TEST(OptionalTest_416, CopyAssignFromSome_416) {
    Optional<int> a(3);
    Optional<int> b;
    b = a;
    EXPECT_TRUE(b.some());
    EXPECT_EQ(*b, 3);
}

TEST(OptionalTest_416, CopyAssignFromNone_416) {
    Optional<int> a;
    Optional<int> b(10);
    b = a;
    EXPECT_TRUE(b.none());
}

TEST(OptionalTest_416, MoveAssignFromSome_416) {
    Optional<std::string> a(std::string("abc"));
    Optional<std::string> b;
    b = std::move(a);
    EXPECT_TRUE(b.some());
    EXPECT_EQ(*b, "abc");
}

TEST(OptionalTest_416, MoveAssignFromNone_416) {
    Optional<int> a;
    Optional<int> b(42);
    b = std::move(a);
    EXPECT_TRUE(b.none());
}

TEST(OptionalTest_416, SelfCopyAssignSome_416) {
    Optional<int> a(123);
    const auto& ref = a;
    a = ref;
    EXPECT_TRUE(a.some());
    EXPECT_EQ(*a, 123);
}

TEST(OptionalTest_416, SelfCopyAssignNone_416) {
    Optional<int> a;
    const auto& ref = a;
    a = ref;
    EXPECT_TRUE(a.none());
}

// ============================================================
// reset()
// ============================================================

TEST(OptionalTest_416, ResetSomeBecomesNone_416) {
    Optional<int> opt(100);
    opt.reset();
    EXPECT_TRUE(opt.none());
    EXPECT_FALSE(opt.some());
}

TEST(OptionalTest_416, ResetNoneStaysNone_416) {
    Optional<int> opt;
    opt.reset();
    EXPECT_TRUE(opt.none());
}

// ============================================================
// Dereference and arrow operators
// ============================================================

TEST(OptionalTest_416, DereferenceReturnsValue_416) {
    Optional<int> opt(55);
    EXPECT_EQ(*opt, 55);
}

TEST(OptionalTest_416, DereferenceModifiesValue_416) {
    Optional<int> opt(1);
    *opt = 2;
    EXPECT_EQ(*opt, 2);
}

TEST(OptionalTest_416, ArrowOperator_416) {
    Optional<std::string> opt(std::string("arrow"));
    EXPECT_EQ(opt->size(), 5u);
}

// ============================================================
// valueOr()
// ============================================================

TEST(OptionalTest_416, ValueOrReturnsValueWhenSome_416) {
    Optional<int> opt(42);
    EXPECT_EQ(opt.valueOr(0), 42);
}

TEST(OptionalTest_416, ValueOrReturnsDefaultWhenNone_416) {
    Optional<int> opt;
    EXPECT_EQ(opt.valueOr(99), 99);
}

TEST(OptionalTest_416, ValueOrWithString_416) {
    Optional<std::string> opt;
    EXPECT_EQ(opt.valueOr("default"), "default");

    Optional<std::string> opt2(std::string("actual"));
    EXPECT_EQ(opt2.valueOr("default"), "actual");
}

// ============================================================
// some() and none()
// ============================================================

TEST(OptionalTest_416, SomeAndNoneAreMutuallyExclusive_416) {
    Optional<int> empty;
    EXPECT_NE(empty.some(), empty.none());

    Optional<int> filled(1);
    EXPECT_NE(filled.some(), filled.none());
}

// ============================================================
// Bool conversion and operator!
// ============================================================

TEST(OptionalTest_416, BoolConversionSome_416) {
    Optional<int> opt(1);
    EXPECT_TRUE(static_cast<bool>(opt));
    EXPECT_FALSE(!opt);
}

TEST(OptionalTest_416, BoolConversionNone_416) {
    Optional<int> opt;
    EXPECT_FALSE(static_cast<bool>(opt));
    EXPECT_TRUE(!opt);
}

// ============================================================
// Equality operator (friend)
// ============================================================

TEST(OptionalTest_416, BothNoneAreEqual_416) {
    Optional<int> a;
    Optional<int> b;
    EXPECT_TRUE(a == b);
}

TEST(OptionalTest_416, NoneAndSomeAreNotEqual_416) {
    Optional<int> a;
    Optional<int> b(1);
    EXPECT_FALSE(a == b);
    EXPECT_FALSE(b == a);
}

TEST(OptionalTest_416, BothSomeSameValueAreEqual_416) {
    Optional<int> a(42);
    Optional<int> b(42);
    EXPECT_TRUE(a == b);
}

TEST(OptionalTest_416, BothSomeDifferentValuesAreNotEqual_416) {
    Optional<int> a(1);
    Optional<int> b(2);
    EXPECT_FALSE(a == b);
}

TEST(OptionalTest_416, EqualityWithStrings_416) {
    Optional<std::string> a(std::string("test"));
    Optional<std::string> b(std::string("test"));
    Optional<std::string> c(std::string("other"));
    Optional<std::string> d;

    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a == c);
    EXPECT_FALSE(a == d);
}

// ============================================================
// Lifecycle / complex type tests
// ============================================================

TEST(OptionalTest_416, WorksWithNonTrivialType_416) {
    struct Counted {
        static int instances;
        Counted() { ++instances; }
        Counted(const Counted&) { ++instances; }
        Counted(Counted&&) noexcept { ++instances; }
        ~Counted() { --instances; }
        Counted& operator=(const Counted&) = default;
        Counted& operator=(Counted&&) noexcept = default;
        bool operator==(const Counted&) const { return true; }
    };
    Counted::instances = 0;

    {
        Optional<Counted> opt(Counted{});
        EXPECT_TRUE(opt.some());
        EXPECT_GE(Counted::instances, 1);
    }
    EXPECT_EQ(Counted::instances, 0);
}

int Counted_instances_416 = 0; // forward for struct below — actually let's use in-test static

TEST(OptionalTest_416, ResetCallsDestructor_416) {
    struct Tracked {
        int* counter;
        Tracked(int* c) : counter(c) { ++(*counter); }
        Tracked(const Tracked& o) : counter(o.counter) { ++(*counter); }
        Tracked(Tracked&& o) noexcept : counter(o.counter) { ++(*counter); }
        ~Tracked() { --(*counter); }
        Tracked& operator=(const Tracked&) = default;
        Tracked& operator=(Tracked&&) noexcept = default;
        bool operator==(const Tracked& o) const { return counter == o.counter; }
    };

    int count = 0;
    {
        Optional<Tracked> opt(Tracked(&count));
        EXPECT_GE(count, 1);
        opt.reset();
        // After reset, the contained object should be destroyed.
        // count may be 0 (if temporaries were destroyed already)
        // But none() must be true
        EXPECT_TRUE(opt.none());
    }
    EXPECT_EQ(count, 0);
}

// ============================================================
// Reassignment chains
// ============================================================

TEST(OptionalTest_416, ChainedAssignments_416) {
    Optional<int> opt;
    opt = 1;
    EXPECT_EQ(*opt, 1);
    opt = 2;
    EXPECT_EQ(*opt, 2);
    opt.reset();
    EXPECT_TRUE(opt.none());
    opt = 3;
    EXPECT_EQ(*opt, 3);
}

TEST(OptionalTest_416, AssignOptionalOverExisting_416) {
    Optional<int> a(10);
    Optional<int> b(20);
    a = b;
    EXPECT_EQ(*a, 20);
    EXPECT_EQ(*b, 20);
}

// ============================================================
// Edge: zero / negative values
// ============================================================

TEST(OptionalTest_416, ZeroValueIsSome_416) {
    Optional<int> opt(0);
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, 0);
    EXPECT_TRUE(static_cast<bool>(opt));
}

TEST(OptionalTest_416, NegativeValueIsSome_416) {
    Optional<int> opt(-1);
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, -1);
}

TEST(OptionalTest_416, EmptyStringIsSome_416) {
    Optional<std::string> opt(std::string(""));
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, "");
}
