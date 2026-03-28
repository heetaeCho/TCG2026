#include "catch2/internal/catch_optional.hpp"
#include <gtest/gtest.h>
#include <string>
#include <utility>

using Catch::Optional;

// ============================================================
// Default construction
// ============================================================

TEST(OptionalTest_417, DefaultConstructedIsNone_417) {
    Optional<int> opt;
    EXPECT_TRUE(opt.none());
    EXPECT_FALSE(opt.some());
    EXPECT_FALSE(static_cast<bool>(opt));
    EXPECT_TRUE(!opt);
}

// ============================================================
// Construction from value (lvalue)
// ============================================================

TEST(OptionalTest_417, ConstructFromLvalue_417) {
    int val = 42;
    Optional<int> opt(val);
    EXPECT_TRUE(opt.some());
    EXPECT_FALSE(opt.none());
    EXPECT_TRUE(static_cast<bool>(opt));
    EXPECT_FALSE(!opt);
    EXPECT_EQ(*opt, 42);
}

// ============================================================
// Construction from value (rvalue)
// ============================================================

TEST(OptionalTest_417, ConstructFromRvalue_417) {
    Optional<std::string> opt(std::string("hello"));
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, "hello");
}

// ============================================================
// Copy construction from engaged optional
// ============================================================

TEST(OptionalTest_417, CopyConstructFromEngaged_417) {
    Optional<int> original(7);
    Optional<int> copy(original);
    EXPECT_TRUE(copy.some());
    EXPECT_EQ(*copy, 7);
    // original should still be valid
    EXPECT_TRUE(original.some());
    EXPECT_EQ(*original, 7);
}

// ============================================================
// Copy construction from disengaged optional
// ============================================================

TEST(OptionalTest_417, CopyConstructFromDisengaged_417) {
    Optional<int> original;
    Optional<int> copy(original);
    EXPECT_TRUE(copy.none());
}

// ============================================================
// Move construction from engaged optional
// ============================================================

TEST(OptionalTest_417, MoveConstructFromEngaged_417) {
    Optional<std::string> original(std::string("world"));
    Optional<std::string> moved(std::move(original));
    EXPECT_TRUE(moved.some());
    EXPECT_EQ(*moved, "world");
}

// ============================================================
// Move construction from disengaged optional
// ============================================================

TEST(OptionalTest_417, MoveConstructFromDisengaged_417) {
    Optional<int> original;
    Optional<int> moved(std::move(original));
    EXPECT_TRUE(moved.none());
}

// ============================================================
// Assignment from lvalue T
// ============================================================

TEST(OptionalTest_417, AssignLvalueT_417) {
    Optional<int> opt;
    int val = 99;
    opt = val;
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, 99);
}

TEST(OptionalTest_417, AssignLvalueTOverwrite_417) {
    Optional<int> opt(10);
    int val = 20;
    opt = val;
    EXPECT_EQ(*opt, 20);
}

// ============================================================
// Assignment from rvalue T
// ============================================================

TEST(OptionalTest_417, AssignRvalueT_417) {
    Optional<std::string> opt;
    opt = std::string("test");
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, "test");
}

// ============================================================
// Copy assignment from engaged optional
// ============================================================

TEST(OptionalTest_417, CopyAssignEngaged_417) {
    Optional<int> a(5);
    Optional<int> b;
    b = a;
    EXPECT_TRUE(b.some());
    EXPECT_EQ(*b, 5);
    EXPECT_TRUE(a.some());
    EXPECT_EQ(*a, 5);
}

// ============================================================
// Copy assignment from disengaged optional
// ============================================================

TEST(OptionalTest_417, CopyAssignDisengaged_417) {
    Optional<int> a;
    Optional<int> b(100);
    b = a;
    EXPECT_TRUE(b.none());
}

// ============================================================
// Move assignment from engaged optional
// ============================================================

TEST(OptionalTest_417, MoveAssignEngaged_417) {
    Optional<std::string> a(std::string("move_me"));
    Optional<std::string> b;
    b = std::move(a);
    EXPECT_TRUE(b.some());
    EXPECT_EQ(*b, "move_me");
}

// ============================================================
// Move assignment from disengaged optional
// ============================================================

TEST(OptionalTest_417, MoveAssignDisengaged_417) {
    Optional<int> a;
    Optional<int> b(50);
    b = std::move(a);
    EXPECT_TRUE(b.none());
}

// ============================================================
// Self-copy assignment
// ============================================================

TEST(OptionalTest_417, SelfCopyAssign_417) {
    Optional<int> opt(42);
    const auto& ref = opt;
    opt = ref;
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, 42);
}

// ============================================================
// reset()
// ============================================================

TEST(OptionalTest_417, ResetEngaged_417) {
    Optional<int> opt(10);
    opt.reset();
    EXPECT_TRUE(opt.none());
    EXPECT_FALSE(opt.some());
    EXPECT_FALSE(static_cast<bool>(opt));
}

TEST(OptionalTest_417, ResetDisengaged_417) {
    Optional<int> opt;
    opt.reset();
    EXPECT_TRUE(opt.none());
}

// ============================================================
// operator* (dereference)
// ============================================================

TEST(OptionalTest_417, DereferenceReturnsValue_417) {
    Optional<int> opt(123);
    EXPECT_EQ(*opt, 123);
}

TEST(OptionalTest_417, DereferenceCanModify_417) {
    Optional<int> opt(1);
    *opt = 2;
    EXPECT_EQ(*opt, 2);
}

// ============================================================
// operator-> (member access)
// ============================================================

TEST(OptionalTest_417, ArrowOperator_417) {
    Optional<std::string> opt(std::string("arrow"));
    EXPECT_EQ(opt->size(), 5u);
}

// ============================================================
// valueOr()
// ============================================================

TEST(OptionalTest_417, ValueOrWhenEngaged_417) {
    Optional<int> opt(42);
    EXPECT_EQ(opt.valueOr(0), 42);
}

TEST(OptionalTest_417, ValueOrWhenDisengaged_417) {
    Optional<int> opt;
    EXPECT_EQ(opt.valueOr(99), 99);
}

TEST(OptionalTest_417, ValueOrStringEngaged_417) {
    Optional<std::string> opt(std::string("present"));
    EXPECT_EQ(opt.valueOr("absent"), "present");
}

TEST(OptionalTest_417, ValueOrStringDisengaged_417) {
    Optional<std::string> opt;
    EXPECT_EQ(opt.valueOr("fallback"), "fallback");
}

// ============================================================
// some() and none()
// ============================================================

TEST(OptionalTest_417, SomeAndNoneConsistency_417) {
    Optional<int> opt;
    EXPECT_NE(opt.some(), opt.none());
    opt = 1;
    EXPECT_NE(opt.some(), opt.none());
}

// ============================================================
// operator bool and operator!
// ============================================================

TEST(OptionalTest_417, BoolAndNotConsistency_417) {
    Optional<int> opt;
    EXPECT_EQ(static_cast<bool>(opt), !(!opt));
    opt = 5;
    EXPECT_EQ(static_cast<bool>(opt), !(!opt));
}

// ============================================================
// Equality operator
// ============================================================

TEST(OptionalTest_417, EqualityBothDisengaged_417) {
    Optional<int> a;
    Optional<int> b;
    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a != b);
}

TEST(OptionalTest_417, EqualityBothEngagedSameValue_417) {
    Optional<int> a(10);
    Optional<int> b(10);
    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a != b);
}

TEST(OptionalTest_417, EqualityBothEngagedDifferentValues_417) {
    Optional<int> a(10);
    Optional<int> b(20);
    EXPECT_FALSE(a == b);
    EXPECT_TRUE(a != b);
}

TEST(OptionalTest_417, EqualityOneEngagedOneDisengaged_417) {
    Optional<int> a(10);
    Optional<int> b;
    EXPECT_FALSE(a == b);
    EXPECT_TRUE(a != b);
    EXPECT_FALSE(b == a);
    EXPECT_TRUE(b != a);
}

// ============================================================
// Inequality (operator!=) is consistent with operator==
// ============================================================

TEST(OptionalTest_417, InequalityIsNegationOfEquality_417) {
    Optional<int> a(5);
    Optional<int> b(5);
    Optional<int> c(6);
    Optional<int> d;

    EXPECT_EQ((a != b), !(a == b));
    EXPECT_EQ((a != c), !(a == c));
    EXPECT_EQ((a != d), !(a == d));
    EXPECT_EQ((d != d), !(d == d));
}

// ============================================================
// Works with non-trivial types
// ============================================================

struct Counter {
    static int instances;
    Counter() { ++instances; }
    Counter(const Counter&) { ++instances; }
    Counter(Counter&&) { ++instances; }
    ~Counter() { --instances; }
    Counter& operator=(const Counter&) = default;
    Counter& operator=(Counter&&) = default;
    bool operator==(const Counter&) const { return true; }
};
int Counter::instances = 0;

TEST(OptionalTest_417, DestructorCalledOnReset_417) {
    int before = Counter::instances;
    {
        Optional<Counter> opt(Counter{});
        EXPECT_GT(Counter::instances, before);
        opt.reset();
        EXPECT_EQ(Counter::instances, before);
    }
    EXPECT_EQ(Counter::instances, before);
}

TEST(OptionalTest_417, DestructorCalledOnDestruction_417) {
    int before = Counter::instances;
    {
        Optional<Counter> opt(Counter{});
        EXPECT_GT(Counter::instances, before);
    }
    EXPECT_EQ(Counter::instances, before);
}

TEST(OptionalTest_417, ReassignCallsDestructor_417) {
    int before = Counter::instances;
    {
        Optional<Counter> opt(Counter{});
        int after_construct = Counter::instances;
        opt = Counter{};
        // After reassignment, the number of instances should remain the same
        // (old destroyed, new constructed)
        EXPECT_EQ(Counter::instances, after_construct);
    }
    EXPECT_EQ(Counter::instances, before);
}

// ============================================================
// Chain of operations
// ============================================================

TEST(OptionalTest_417, ChainSetResetSet_417) {
    Optional<int> opt;
    EXPECT_TRUE(opt.none());

    opt = 1;
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, 1);

    opt.reset();
    EXPECT_TRUE(opt.none());

    opt = 2;
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, 2);
}

// ============================================================
// Optional with bool type (edge case)
// ============================================================

TEST(OptionalTest_417, OptionalBoolFalse_417) {
    Optional<bool> opt(false);
    EXPECT_TRUE(opt.some());
    EXPECT_TRUE(static_cast<bool>(opt));
    EXPECT_EQ(*opt, false);
}

TEST(OptionalTest_417, OptionalBoolTrue_417) {
    Optional<bool> opt(true);
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, true);
}

// ============================================================
// Optional with zero value
// ============================================================

TEST(OptionalTest_417, OptionalIntZero_417) {
    Optional<int> opt(0);
    EXPECT_TRUE(opt.some());
    EXPECT_FALSE(opt.none());
    EXPECT_EQ(*opt, 0);
    EXPECT_EQ(opt.valueOr(42), 0);
}

// ============================================================
// Overwrite engaged optional with copy assignment from engaged
// ============================================================

TEST(OptionalTest_417, CopyAssignOverwrite_417) {
    Optional<int> a(10);
    Optional<int> b(20);
    a = b;
    EXPECT_EQ(*a, 20);
    EXPECT_EQ(*b, 20);
}

// ============================================================
// Overwrite engaged optional with move assignment from engaged
// ============================================================

TEST(OptionalTest_417, MoveAssignOverwrite_417) {
    Optional<std::string> a(std::string("first"));
    Optional<std::string> b(std::string("second"));
    a = std::move(b);
    EXPECT_EQ(*a, "second");
}
