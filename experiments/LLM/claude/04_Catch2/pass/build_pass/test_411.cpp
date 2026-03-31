#include "catch2/internal/catch_optional.hpp"
#include <gtest/gtest.h>
#include <string>
#include <utility>

using Catch::Optional;

// ============================================================
// Default Construction Tests
// ============================================================

TEST(OptionalTest_411, DefaultConstructedIsNone_411) {
    Optional<int> opt;
    EXPECT_TRUE(opt.none());
    EXPECT_FALSE(opt.some());
    EXPECT_FALSE(static_cast<bool>(opt));
    EXPECT_TRUE(!opt);
}

// ============================================================
// Value Construction Tests
// ============================================================

TEST(OptionalTest_411, ConstructWithLvalueHasValue_411) {
    int val = 42;
    Optional<int> opt(val);
    EXPECT_TRUE(opt.some());
    EXPECT_FALSE(opt.none());
    EXPECT_TRUE(static_cast<bool>(opt));
    EXPECT_FALSE(!opt);
    EXPECT_EQ(*opt, 42);
}

TEST(OptionalTest_411, ConstructWithRvalueHasValue_411) {
    Optional<int> opt(99);
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, 99);
}

TEST(OptionalTest_411, ConstructWithString_411) {
    std::string s = "hello";
    Optional<std::string> opt(s);
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, "hello");
}

TEST(OptionalTest_411, ConstructWithMoveString_411) {
    std::string s = "world";
    Optional<std::string> opt(std::move(s));
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, "world");
}

// ============================================================
// Copy Construction Tests
// ============================================================

TEST(OptionalTest_411, CopyConstructFromNone_411) {
    Optional<int> original;
    Optional<int> copy(original);
    EXPECT_TRUE(copy.none());
}

TEST(OptionalTest_411, CopyConstructFromSome_411) {
    Optional<int> original(123);
    Optional<int> copy(original);
    EXPECT_TRUE(copy.some());
    EXPECT_EQ(*copy, 123);
    // Original should still be valid
    EXPECT_TRUE(original.some());
    EXPECT_EQ(*original, 123);
}

// ============================================================
// Move Construction Tests
// ============================================================

TEST(OptionalTest_411, MoveConstructFromNone_411) {
    Optional<int> original;
    Optional<int> moved(std::move(original));
    EXPECT_TRUE(moved.none());
}

TEST(OptionalTest_411, MoveConstructFromSome_411) {
    Optional<std::string> original(std::string("moveable"));
    Optional<std::string> moved(std::move(original));
    EXPECT_TRUE(moved.some());
    EXPECT_EQ(*moved, "moveable");
}

// ============================================================
// Copy Assignment Tests
// ============================================================

TEST(OptionalTest_411, CopyAssignValueToEmpty_411) {
    Optional<int> opt;
    int val = 77;
    opt = val;
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, 77);
}

TEST(OptionalTest_411, CopyAssignValueToExisting_411) {
    Optional<int> opt(10);
    int val = 20;
    opt = val;
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, 20);
}

TEST(OptionalTest_411, CopyAssignOptionalWithValueToEmpty_411) {
    Optional<int> opt;
    Optional<int> other(55);
    opt = other;
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, 55);
}

TEST(OptionalTest_411, CopyAssignEmptyOptionalToExisting_411) {
    Optional<int> opt(100);
    Optional<int> other;
    opt = other;
    EXPECT_TRUE(opt.none());
}

TEST(OptionalTest_411, CopyAssignOptionalToOptional_411) {
    Optional<int> opt(1);
    Optional<int> other(2);
    opt = other;
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, 2);
}

// ============================================================
// Move Assignment Tests
// ============================================================

TEST(OptionalTest_411, MoveAssignValueToEmpty_411) {
    Optional<int> opt;
    opt = 42;
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, 42);
}

TEST(OptionalTest_411, MoveAssignOptionalToEmpty_411) {
    Optional<std::string> opt;
    Optional<std::string> other(std::string("test"));
    opt = std::move(other);
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, "test");
}

TEST(OptionalTest_411, MoveAssignEmptyOptionalToExisting_411) {
    Optional<int> opt(100);
    Optional<int> other;
    opt = std::move(other);
    EXPECT_TRUE(opt.none());
}

// ============================================================
// reset() Tests
// ============================================================

TEST(OptionalTest_411, ResetMakesOptionalNone_411) {
    Optional<int> opt(42);
    EXPECT_TRUE(opt.some());
    opt.reset();
    EXPECT_TRUE(opt.none());
    EXPECT_FALSE(opt.some());
    EXPECT_FALSE(static_cast<bool>(opt));
}

TEST(OptionalTest_411, ResetOnAlreadyEmptyOptional_411) {
    Optional<int> opt;
    opt.reset();
    EXPECT_TRUE(opt.none());
}

// ============================================================
// operator*() Tests
// ============================================================

TEST(OptionalTest_411, DereferenceReturnsValue_411) {
    Optional<int> opt(7);
    EXPECT_EQ(*opt, 7);
}

TEST(OptionalTest_411, DereferenceAllowsModification_411) {
    Optional<int> opt(10);
    *opt = 20;
    EXPECT_EQ(*opt, 20);
}

// ============================================================
// operator->() Tests
// ============================================================

TEST(OptionalTest_411, ArrowOperatorAccessesMember_411) {
    Optional<std::string> opt(std::string("arrow"));
    EXPECT_EQ(opt->size(), 5u);
    EXPECT_EQ(opt->at(0), 'a');
}

// ============================================================
// valueOr() Tests
// ============================================================

TEST(OptionalTest_411, ValueOrReturnsValueWhenSome_411) {
    Optional<int> opt(42);
    EXPECT_EQ(opt.valueOr(0), 42);
}

TEST(OptionalTest_411, ValueOrReturnsDefaultWhenNone_411) {
    Optional<int> opt;
    EXPECT_EQ(opt.valueOr(99), 99);
}

TEST(OptionalTest_411, ValueOrWithStringWhenSome_411) {
    Optional<std::string> opt(std::string("present"));
    EXPECT_EQ(opt.valueOr("default"), "present");
}

TEST(OptionalTest_411, ValueOrWithStringWhenNone_411) {
    Optional<std::string> opt;
    EXPECT_EQ(opt.valueOr("default"), "default");
}

TEST(OptionalTest_411, ValueOrAfterReset_411) {
    Optional<int> opt(10);
    opt.reset();
    EXPECT_EQ(opt.valueOr(-1), -1);
}

// ============================================================
// some() / none() Tests
// ============================================================

TEST(OptionalTest_411, SomeAndNoneAreMutuallyExclusive_411) {
    Optional<int> opt;
    EXPECT_NE(opt.some(), opt.none());
    
    opt = 5;
    EXPECT_NE(opt.some(), opt.none());
}

TEST(OptionalTest_411, SomeIsTrueWhenValuePresent_411) {
    Optional<int> opt(1);
    EXPECT_TRUE(opt.some());
}

TEST(OptionalTest_411, NoneIsTrueWhenNoValue_411) {
    Optional<int> opt;
    EXPECT_TRUE(opt.none());
}

// ============================================================
// operator bool() / operator!() Tests
// ============================================================

TEST(OptionalTest_411, BoolConversionTrueWhenSome_411) {
    Optional<int> opt(1);
    EXPECT_TRUE(static_cast<bool>(opt));
}

TEST(OptionalTest_411, BoolConversionFalseWhenNone_411) {
    Optional<int> opt;
    EXPECT_FALSE(static_cast<bool>(opt));
}

TEST(OptionalTest_411, NotOperatorFalseWhenSome_411) {
    Optional<int> opt(1);
    EXPECT_FALSE(!opt);
}

TEST(OptionalTest_411, NotOperatorTrueWhenNone_411) {
    Optional<int> opt;
    EXPECT_TRUE(!opt);
}

// ============================================================
// Chained Operations Tests
// ============================================================

TEST(OptionalTest_411, AssignResetAssign_411) {
    Optional<int> opt(10);
    EXPECT_EQ(*opt, 10);
    opt.reset();
    EXPECT_TRUE(opt.none());
    opt = 20;
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, 20);
}

TEST(OptionalTest_411, MultipleResets_411) {
    Optional<int> opt(5);
    opt.reset();
    opt.reset();
    EXPECT_TRUE(opt.none());
}

TEST(OptionalTest_411, ReassignMultipleTimes_411) {
    Optional<int> opt;
    for (int i = 0; i < 100; ++i) {
        opt = i;
        EXPECT_EQ(*opt, i);
    }
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, 99);
}

// ============================================================
// Complex Type Tests
// ============================================================

struct Counter {
    static int instances;
    int value;
    Counter(int v) : value(v) { ++instances; }
    Counter(const Counter& o) : value(o.value) { ++instances; }
    Counter(Counter&& o) : value(o.value) { o.value = 0; ++instances; }
    ~Counter() { --instances; }
    Counter& operator=(const Counter&) = default;
    Counter& operator=(Counter&&) = default;
};

int Counter::instances = 0;

TEST(OptionalTest_411, DestructorCalledOnReset_411) {
    Counter::instances = 0;
    {
        Optional<Counter> opt(Counter(42));
        EXPECT_GT(Counter::instances, 0);
        opt.reset();
        EXPECT_EQ(Counter::instances, 0);
    }
    EXPECT_EQ(Counter::instances, 0);
}

TEST(OptionalTest_411, DestructorCalledOnDestruction_411) {
    Counter::instances = 0;
    {
        Optional<Counter> opt(Counter(10));
    }
    EXPECT_EQ(Counter::instances, 0);
}

TEST(OptionalTest_411, DestructorCalledOnReassign_411) {
    Counter::instances = 0;
    {
        Optional<Counter> opt(Counter(1));
        int before = Counter::instances;
        opt = Counter(2);
        // Should still have same number of managed instances (old destroyed, new created)
        EXPECT_EQ(Counter::instances, before);
        EXPECT_EQ(opt->value, 2);
    }
    EXPECT_EQ(Counter::instances, 0);
}

// ============================================================
// Boundary / Edge Case Tests
// ============================================================

TEST(OptionalTest_411, OptionalOfBool_411) {
    Optional<bool> optTrue(true);
    Optional<bool> optFalse(false);
    Optional<bool> optNone;

    EXPECT_TRUE(optTrue.some());
    EXPECT_EQ(*optTrue, true);

    EXPECT_TRUE(optFalse.some());
    EXPECT_EQ(*optFalse, false);

    EXPECT_TRUE(optNone.none());
    EXPECT_EQ(optNone.valueOr(true), true);
}

TEST(OptionalTest_411, OptionalOfZero_411) {
    Optional<int> opt(0);
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, 0);
    EXPECT_EQ(opt.valueOr(42), 0);
}

TEST(OptionalTest_411, SelfCopyAssignment_411) {
    Optional<int> opt(42);
    const Optional<int>& ref = opt;
    opt = ref;
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, 42);
}

TEST(OptionalTest_411, ValueOrDoesNotModifyOptional_411) {
    Optional<int> opt;
    int result = opt.valueOr(100);
    EXPECT_EQ(result, 100);
    EXPECT_TRUE(opt.none()); // valueOr should not change state
}

TEST(OptionalTest_411, ConstOptionalValueOr_411) {
    const Optional<int> opt(50);
    EXPECT_EQ(opt.valueOr(0), 50);
}

TEST(OptionalTest_411, ConstEmptyOptionalValueOr_411) {
    const Optional<int> opt;
    EXPECT_EQ(opt.valueOr(0), 0);
}
