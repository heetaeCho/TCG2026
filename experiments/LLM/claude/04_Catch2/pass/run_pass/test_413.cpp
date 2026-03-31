#include "catch2/internal/catch_optional.hpp"
#include <gtest/gtest.h>
#include <string>
#include <utility>

using Catch::Optional;

// ============================================================
// Default construction tests
// ============================================================

TEST(OptionalTest_413, DefaultConstructedIsNone_413) {
    Optional<int> opt;
    EXPECT_TRUE(opt.none());
    EXPECT_FALSE(opt.some());
    EXPECT_FALSE(static_cast<bool>(opt));
    EXPECT_TRUE(!opt);
}

// ============================================================
// Value construction tests
// ============================================================

TEST(OptionalTest_413, ConstructWithLvalueHasValue_413) {
    int val = 42;
    Optional<int> opt(val);
    EXPECT_TRUE(opt.some());
    EXPECT_FALSE(opt.none());
    EXPECT_TRUE(static_cast<bool>(opt));
    EXPECT_FALSE(!opt);
    EXPECT_EQ(*opt, 42);
}

TEST(OptionalTest_413, ConstructWithRvalueHasValue_413) {
    Optional<int> opt(99);
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, 99);
}

TEST(OptionalTest_413, ConstructWithStringLvalue_413) {
    std::string s = "hello";
    Optional<std::string> opt(s);
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, "hello");
    // Original string should be unchanged (copy)
    EXPECT_EQ(s, "hello");
}

TEST(OptionalTest_413, ConstructWithStringRvalue_413) {
    std::string s = "world";
    Optional<std::string> opt(std::move(s));
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, "world");
}

// ============================================================
// Copy construction tests
// ============================================================

TEST(OptionalTest_413, CopyConstructFromEngagedOptional_413) {
    Optional<int> opt1(123);
    Optional<int> opt2(opt1);
    EXPECT_TRUE(opt2.some());
    EXPECT_EQ(*opt2, 123);
    // Original should still be valid
    EXPECT_TRUE(opt1.some());
    EXPECT_EQ(*opt1, 123);
}

TEST(OptionalTest_413, CopyConstructFromDisengagedOptional_413) {
    Optional<int> opt1;
    Optional<int> opt2(opt1);
    EXPECT_TRUE(opt2.none());
}

// ============================================================
// Move construction tests
// ============================================================

TEST(OptionalTest_413, MoveConstructFromEngagedOptional_413) {
    Optional<int> opt1(456);
    Optional<int> opt2(std::move(opt1));
    EXPECT_TRUE(opt2.some());
    EXPECT_EQ(*opt2, 456);
}

TEST(OptionalTest_413, MoveConstructFromDisengagedOptional_413) {
    Optional<int> opt1;
    Optional<int> opt2(std::move(opt1));
    EXPECT_TRUE(opt2.none());
}

// ============================================================
// Copy assignment tests
// ============================================================

TEST(OptionalTest_413, CopyAssignValueToDisengaged_413) {
    Optional<int> opt;
    int val = 10;
    opt = val;
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, 10);
}

TEST(OptionalTest_413, CopyAssignValueToEngaged_413) {
    Optional<int> opt(5);
    int val = 20;
    opt = val;
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, 20);
}

TEST(OptionalTest_413, CopyAssignOptionalToDisengaged_413) {
    Optional<int> opt1;
    Optional<int> opt2(30);
    opt1 = opt2;
    EXPECT_TRUE(opt1.some());
    EXPECT_EQ(*opt1, 30);
}

TEST(OptionalTest_413, CopyAssignOptionalToEngaged_413) {
    Optional<int> opt1(5);
    Optional<int> opt2(40);
    opt1 = opt2;
    EXPECT_TRUE(opt1.some());
    EXPECT_EQ(*opt1, 40);
}

TEST(OptionalTest_413, CopyAssignDisengagedOptionalToEngaged_413) {
    Optional<int> opt1(50);
    Optional<int> opt2;
    opt1 = opt2;
    EXPECT_TRUE(opt1.none());
}

// ============================================================
// Move assignment tests
// ============================================================

TEST(OptionalTest_413, MoveAssignValueToDisengaged_413) {
    Optional<int> opt;
    opt = 60;
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, 60);
}

TEST(OptionalTest_413, MoveAssignValueToEngaged_413) {
    Optional<int> opt(5);
    opt = 70;
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, 70);
}

TEST(OptionalTest_413, MoveAssignOptionalToDisengaged_413) {
    Optional<int> opt1;
    Optional<int> opt2(80);
    opt1 = std::move(opt2);
    EXPECT_TRUE(opt1.some());
    EXPECT_EQ(*opt1, 80);
}

TEST(OptionalTest_413, MoveAssignOptionalToEngaged_413) {
    Optional<int> opt1(5);
    Optional<int> opt2(90);
    opt1 = std::move(opt2);
    EXPECT_TRUE(opt1.some());
    EXPECT_EQ(*opt1, 90);
}

TEST(OptionalTest_413, MoveAssignDisengagedOptionalToEngaged_413) {
    Optional<int> opt1(100);
    Optional<int> opt2;
    opt1 = std::move(opt2);
    EXPECT_TRUE(opt1.none());
}

// ============================================================
// Reset tests
// ============================================================

TEST(OptionalTest_413, ResetEngagedOptionalMakesNone_413) {
    Optional<int> opt(42);
    EXPECT_TRUE(opt.some());
    opt.reset();
    EXPECT_TRUE(opt.none());
    EXPECT_FALSE(opt.some());
    EXPECT_FALSE(static_cast<bool>(opt));
}

TEST(OptionalTest_413, ResetDisengagedOptionalStaysNone_413) {
    Optional<int> opt;
    opt.reset();
    EXPECT_TRUE(opt.none());
}

// ============================================================
// Dereference operator tests
// ============================================================

TEST(OptionalTest_413, DereferenceReturnsCorrectValue_413) {
    Optional<int> opt(55);
    EXPECT_EQ(*opt, 55);
}

TEST(OptionalTest_413, DereferenceAllowsModification_413) {
    Optional<int> opt(10);
    *opt = 20;
    EXPECT_EQ(*opt, 20);
}

// ============================================================
// Arrow operator tests
// ============================================================

TEST(OptionalTest_413, ArrowOperatorAccessesMember_413) {
    Optional<std::string> opt(std::string("test"));
    EXPECT_EQ(opt->size(), 4u);
    EXPECT_EQ(opt->at(0), 't');
}

// ============================================================
// valueOr tests
// ============================================================

TEST(OptionalTest_413, ValueOrReturnsValueWhenEngaged_413) {
    Optional<int> opt(42);
    EXPECT_EQ(opt.valueOr(99), 42);
}

TEST(OptionalTest_413, ValueOrReturnsDefaultWhenDisengaged_413) {
    Optional<int> opt;
    EXPECT_EQ(opt.valueOr(99), 99);
}

TEST(OptionalTest_413, ValueOrWithStringEngaged_413) {
    Optional<std::string> opt(std::string("actual"));
    EXPECT_EQ(opt.valueOr("default"), "actual");
}

TEST(OptionalTest_413, ValueOrWithStringDisengaged_413) {
    Optional<std::string> opt;
    EXPECT_EQ(opt.valueOr("default"), "default");
}

// ============================================================
// some() and none() consistency tests
// ============================================================

TEST(OptionalTest_413, SomeAndNoneAreMutuallyExclusive_413) {
    Optional<int> engaged(1);
    EXPECT_TRUE(engaged.some());
    EXPECT_FALSE(engaged.none());
    EXPECT_NE(engaged.some(), engaged.none());

    Optional<int> disengaged;
    EXPECT_FALSE(disengaged.some());
    EXPECT_TRUE(disengaged.none());
    EXPECT_NE(disengaged.some(), disengaged.none());
}

// ============================================================
// Boolean conversion and negation operator tests
// ============================================================

TEST(OptionalTest_413, BoolConversionEngaged_413) {
    Optional<int> opt(0); // value is 0 but optional is engaged
    EXPECT_TRUE(static_cast<bool>(opt));
    EXPECT_FALSE(!opt);
    EXPECT_TRUE(opt.some());
}

TEST(OptionalTest_413, BoolConversionDisengaged_413) {
    Optional<int> opt;
    EXPECT_FALSE(static_cast<bool>(opt));
    EXPECT_TRUE(!opt);
}

// ============================================================
// Chain of operations tests
// ============================================================

TEST(OptionalTest_413, AssignResetAssignSequence_413) {
    Optional<int> opt;
    EXPECT_TRUE(opt.none());

    opt = 10;
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, 10);

    opt.reset();
    EXPECT_TRUE(opt.none());

    opt = 20;
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, 20);
}

TEST(OptionalTest_413, SelfCopyAssignment_413) {
    Optional<int> opt(42);
    opt = opt;
    // Should still be valid after self-assignment
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, 42);
}

TEST(OptionalTest_413, SelfMoveAssignment_413) {
    Optional<int> opt(42);
    opt = std::move(opt);
    // Behavior after self-move is implementation-defined but shouldn't crash
    // We just verify it doesn't crash; the value may or may not be valid
}

// ============================================================
// Type with non-trivial destructor
// ============================================================

struct Counter {
    static int instances;
    Counter() { ++instances; }
    Counter(const Counter&) { ++instances; }
    Counter(Counter&&) { ++instances; }
    ~Counter() { --instances; }
    Counter& operator=(const Counter&) = default;
    Counter& operator=(Counter&&) = default;
};
int Counter::instances = 0;

TEST(OptionalTest_413, DestructorCalledOnReset_413) {
    Counter::instances = 0;
    {
        Optional<Counter> opt(Counter{});
        EXPECT_GT(Counter::instances, 0);
        opt.reset();
        EXPECT_EQ(Counter::instances, 0);
    }
    EXPECT_EQ(Counter::instances, 0);
}

TEST(OptionalTest_413, DestructorCalledOnDestruction_413) {
    Counter::instances = 0;
    {
        Optional<Counter> opt(Counter{});
    }
    EXPECT_EQ(Counter::instances, 0);
}

TEST(OptionalTest_413, DestructorNotCalledForDisengaged_413) {
    Counter::instances = 0;
    {
        Optional<Counter> opt;
    }
    EXPECT_EQ(Counter::instances, 0);
}

// ============================================================
// Edge case: Optional with zero value
// ============================================================

TEST(OptionalTest_413, OptionalWithZeroValueIsEngaged_413) {
    Optional<int> opt(0);
    EXPECT_TRUE(opt.some());
    EXPECT_FALSE(opt.none());
    EXPECT_EQ(*opt, 0);
    EXPECT_EQ(opt.valueOr(42), 0);
}

// ============================================================
// Edge case: Optional with negative value
// ============================================================

TEST(OptionalTest_413, OptionalWithNegativeValue_413) {
    Optional<int> opt(-1);
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, -1);
}

// ============================================================
// Assignment returns reference
// ============================================================

TEST(OptionalTest_413, AssignmentReturnsSelf_413) {
    Optional<int> opt;
    Optional<int>& ref = (opt = 42);
    EXPECT_EQ(&ref, &opt);
    EXPECT_EQ(*opt, 42);
}

TEST(OptionalTest_413, OptionalAssignmentReturnsSelf_413) {
    Optional<int> opt;
    Optional<int> other(100);
    Optional<int>& ref = (opt = other);
    EXPECT_EQ(&ref, &opt);
    EXPECT_EQ(*opt, 100);
}

// ============================================================
// Multiple resets
// ============================================================

TEST(OptionalTest_413, MultipleResetsAreHarmless_413) {
    Optional<int> opt(42);
    opt.reset();
    opt.reset();
    opt.reset();
    EXPECT_TRUE(opt.none());
}
