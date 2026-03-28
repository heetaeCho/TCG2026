#include "catch2/internal/catch_optional.hpp"
#include <gtest/gtest.h>
#include <string>
#include <utility>

using Catch::Optional;

// ========== Default Construction Tests ==========

TEST(OptionalTest_404, DefaultConstructedIsNone_404) {
    Optional<int> opt;
    EXPECT_TRUE(opt.none());
    EXPECT_FALSE(opt.some());
}

TEST(OptionalTest_404, DefaultConstructedBoolConversionIsFalse_404) {
    Optional<int> opt;
    EXPECT_FALSE(static_cast<bool>(opt));
}

TEST(OptionalTest_404, DefaultConstructedNotOperatorIsTrue_404) {
    Optional<int> opt;
    EXPECT_TRUE(!opt);
}

// ========== Value Construction Tests ==========

TEST(OptionalTest_404, ConstructWithLvalueHasValue_404) {
    int val = 42;
    Optional<int> opt(val);
    EXPECT_TRUE(opt.some());
    EXPECT_FALSE(opt.none());
    EXPECT_EQ(*opt, 42);
}

TEST(OptionalTest_404, ConstructWithRvalueHasValue_404) {
    Optional<std::string> opt(std::string("hello"));
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, "hello");
}

TEST(OptionalTest_404, ConstructedWithValueBoolConversionIsTrue_404) {
    Optional<int> opt(10);
    EXPECT_TRUE(static_cast<bool>(opt));
}

TEST(OptionalTest_404, ConstructedWithValueNotOperatorIsFalse_404) {
    Optional<int> opt(10);
    EXPECT_FALSE(!opt);
}

// ========== Copy Construction Tests ==========

TEST(OptionalTest_404, CopyConstructFromEngagedOptional_404) {
    Optional<int> original(99);
    Optional<int> copy(original);
    EXPECT_TRUE(copy.some());
    EXPECT_EQ(*copy, 99);
    // Original should remain valid
    EXPECT_TRUE(original.some());
    EXPECT_EQ(*original, 99);
}

TEST(OptionalTest_404, CopyConstructFromDisengagedOptional_404) {
    Optional<int> original;
    Optional<int> copy(original);
    EXPECT_TRUE(copy.none());
    EXPECT_FALSE(copy.some());
}

// ========== Move Construction Tests ==========

TEST(OptionalTest_404, MoveConstructFromEngagedOptional_404) {
    Optional<std::string> original(std::string("world"));
    Optional<std::string> moved(std::move(original));
    EXPECT_TRUE(moved.some());
    EXPECT_EQ(*moved, "world");
}

TEST(OptionalTest_404, MoveConstructFromDisengagedOptional_404) {
    Optional<int> original;
    Optional<int> moved(std::move(original));
    EXPECT_TRUE(moved.none());
}

// ========== Copy Assignment Tests ==========

TEST(OptionalTest_404, CopyAssignValueToDisengaged_404) {
    Optional<int> opt;
    int val = 55;
    opt = val;
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, 55);
}

TEST(OptionalTest_404, CopyAssignValueToEngaged_404) {
    Optional<int> opt(10);
    int val = 20;
    opt = val;
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, 20);
}

TEST(OptionalTest_404, CopyAssignOptionalToDisengaged_404) {
    Optional<int> opt;
    Optional<int> other(77);
    opt = other;
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, 77);
}

TEST(OptionalTest_404, CopyAssignDisengagedOptionalToEngaged_404) {
    Optional<int> opt(100);
    Optional<int> other;
    opt = other;
    EXPECT_TRUE(opt.none());
}

TEST(OptionalTest_404, CopyAssignEngagedOptionalToEngaged_404) {
    Optional<int> opt(10);
    Optional<int> other(20);
    opt = other;
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, 20);
}

// ========== Move Assignment Tests ==========

TEST(OptionalTest_404, MoveAssignValueToDisengaged_404) {
    Optional<std::string> opt;
    opt = std::string("moved");
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, "moved");
}

TEST(OptionalTest_404, MoveAssignValueToEngaged_404) {
    Optional<std::string> opt(std::string("old"));
    opt = std::string("new");
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, "new");
}

TEST(OptionalTest_404, MoveAssignOptionalToDisengaged_404) {
    Optional<std::string> opt;
    Optional<std::string> other(std::string("data"));
    opt = std::move(other);
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, "data");
}

TEST(OptionalTest_404, MoveAssignDisengagedOptionalToEngaged_404) {
    Optional<int> opt(42);
    Optional<int> other;
    opt = std::move(other);
    EXPECT_TRUE(opt.none());
}

TEST(OptionalTest_404, MoveAssignEngagedOptionalToEngaged_404) {
    Optional<int> opt(1);
    Optional<int> other(2);
    opt = std::move(other);
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, 2);
}

// ========== Reset Tests ==========

TEST(OptionalTest_404, ResetEngagedMakesNone_404) {
    Optional<int> opt(42);
    EXPECT_TRUE(opt.some());
    opt.reset();
    EXPECT_TRUE(opt.none());
    EXPECT_FALSE(opt.some());
    EXPECT_FALSE(static_cast<bool>(opt));
}

TEST(OptionalTest_404, ResetDisengagedRemainsNone_404) {
    Optional<int> opt;
    opt.reset();
    EXPECT_TRUE(opt.none());
}

// ========== Dereference and Arrow Operator Tests ==========

TEST(OptionalTest_404, DereferenceReturnsValue_404) {
    Optional<int> opt(123);
    EXPECT_EQ(*opt, 123);
}

TEST(OptionalTest_404, DereferenceAllowsModification_404) {
    Optional<int> opt(10);
    *opt = 20;
    EXPECT_EQ(*opt, 20);
}

TEST(OptionalTest_404, ArrowOperatorAccessesMember_404) {
    Optional<std::string> opt(std::string("test"));
    EXPECT_EQ(opt->size(), 4u);
}

TEST(OptionalTest_404, ArrowOperatorAllowsModification_404) {
    Optional<std::string> opt(std::string("abc"));
    opt->append("def");
    EXPECT_EQ(*opt, "abcdef");
}

// ========== valueOr Tests ==========

TEST(OptionalTest_404, ValueOrReturnsValueWhenEngaged_404) {
    Optional<int> opt(42);
    EXPECT_EQ(opt.valueOr(0), 42);
}

TEST(OptionalTest_404, ValueOrReturnsDefaultWhenDisengaged_404) {
    Optional<int> opt;
    EXPECT_EQ(opt.valueOr(99), 99);
}

TEST(OptionalTest_404, ValueOrReturnsDefaultAfterReset_404) {
    Optional<int> opt(10);
    opt.reset();
    EXPECT_EQ(opt.valueOr(77), 77);
}

TEST(OptionalTest_404, ValueOrWithStringEngaged_404) {
    Optional<std::string> opt(std::string("hello"));
    EXPECT_EQ(opt.valueOr("default"), "hello");
}

TEST(OptionalTest_404, ValueOrWithStringDisengaged_404) {
    Optional<std::string> opt;
    EXPECT_EQ(opt.valueOr("default"), "default");
}

// ========== some() and none() Tests ==========

TEST(OptionalTest_404, SomeAndNoneAreMutuallyExclusive_404) {
    Optional<int> engaged(5);
    EXPECT_TRUE(engaged.some());
    EXPECT_FALSE(engaged.none());

    Optional<int> disengaged;
    EXPECT_FALSE(disengaged.some());
    EXPECT_TRUE(disengaged.none());
}

// ========== Chained Assignment Tests ==========

TEST(OptionalTest_404, ChainedAssignmentReturnsReference_404) {
    Optional<int> opt;
    int val = 5;
    Optional<int>& ref = (opt = val);
    EXPECT_EQ(&ref, &opt);
    EXPECT_EQ(*opt, 5);
}

TEST(OptionalTest_404, ChainedMoveAssignmentReturnsReference_404) {
    Optional<int> opt;
    Optional<int>& ref = (opt = 10);
    EXPECT_EQ(&ref, &opt);
    EXPECT_EQ(*opt, 10);
}

// ========== Complex Type Tests ==========

struct Counter {
    static int instances;
    int value;
    Counter(int v) : value(v) { ++instances; }
    Counter(const Counter& o) : value(o.value) { ++instances; }
    Counter(Counter&& o) : value(o.value) { o.value = 0; ++instances; }
    ~Counter() { --instances; }
};
int Counter::instances = 0;

TEST(OptionalTest_404, DestructorCallsContainedTypeDestructor_404) {
    Counter::instances = 0;
    {
        Optional<Counter> opt(Counter(1));
        EXPECT_GT(Counter::instances, 0);
    }
    EXPECT_EQ(Counter::instances, 0);
}

TEST(OptionalTest_404, ResetCallsContainedTypeDestructor_404) {
    Counter::instances = 0;
    Optional<Counter> opt(Counter(1));
    int before = Counter::instances;
    opt.reset();
    EXPECT_LT(Counter::instances, before);
    EXPECT_TRUE(opt.none());
}

TEST(OptionalTest_404, ReassignmentDestroysOldValue_404) {
    Counter::instances = 0;
    Optional<Counter> opt(Counter(1));
    int count_after_first = Counter::instances;
    opt = Counter(2);
    // After reassignment, old value destroyed, new one created
    // Count should be same or equal
    EXPECT_EQ(Counter::instances, count_after_first);
    EXPECT_EQ((*opt).value, 2);
}

// ========== Boundary / Edge Cases ==========

TEST(OptionalTest_404, AssignZeroValue_404) {
    Optional<int> opt(0);
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, 0);
}

TEST(OptionalTest_404, AssignEmptyString_404) {
    Optional<std::string> opt(std::string(""));
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, "");
}

TEST(OptionalTest_404, AssignFalseBoolean_404) {
    Optional<bool> opt(false);
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, false);
}

TEST(OptionalTest_404, ValueOrWithZeroDefault_404) {
    Optional<int> opt;
    EXPECT_EQ(opt.valueOr(0), 0);
}

TEST(OptionalTest_404, MultipleResetsAreSafe_404) {
    Optional<int> opt(42);
    opt.reset();
    opt.reset();
    opt.reset();
    EXPECT_TRUE(opt.none());
}

TEST(OptionalTest_404, ReassignAfterReset_404) {
    Optional<int> opt(10);
    opt.reset();
    EXPECT_TRUE(opt.none());
    opt = 20;
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, 20);
}

TEST(OptionalTest_404, SelfCopyAssignmentOptional_404) {
    Optional<int> opt(42);
    opt = opt;
    // Should still be valid after self-assignment
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, 42);
}

TEST(OptionalTest_404, ConstOptionalValueOr_404) {
    const Optional<int> opt(42);
    EXPECT_EQ(opt.valueOr(0), 42);
}

TEST(OptionalTest_404, ConstOptionalNone_404) {
    const Optional<int> opt;
    EXPECT_TRUE(opt.none());
    EXPECT_FALSE(opt.some());
    EXPECT_EQ(opt.valueOr(99), 99);
}

TEST(OptionalTest_404, ConstOptionalBoolConversion_404) {
    const Optional<int> engaged(5);
    const Optional<int> disengaged;
    EXPECT_TRUE(static_cast<bool>(engaged));
    EXPECT_FALSE(static_cast<bool>(disengaged));
}
