#include <gtest/gtest.h>
#include <string>
#include <utility>

#include "catch2/internal/catch_optional.hpp"

// ============================================================
// Test fixture
// ============================================================
class OptionalTest_410 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ============================================================
// Default construction
// ============================================================
TEST_F(OptionalTest_410, DefaultConstructedIsNone_410) {
    Catch::Optional<int> opt;
    EXPECT_TRUE(opt.none());
    EXPECT_FALSE(opt.some());
    EXPECT_FALSE(static_cast<bool>(opt));
    EXPECT_TRUE(!opt);
}

// ============================================================
// Construction from lvalue
// ============================================================
TEST_F(OptionalTest_410, ConstructFromLValue_410) {
    int val = 42;
    Catch::Optional<int> opt(val);
    EXPECT_TRUE(opt.some());
    EXPECT_FALSE(opt.none());
    EXPECT_TRUE(static_cast<bool>(opt));
    EXPECT_FALSE(!opt);
    EXPECT_EQ(*opt, 42);
}

// ============================================================
// Construction from rvalue
// ============================================================
TEST_F(OptionalTest_410, ConstructFromRValue_410) {
    Catch::Optional<std::string> opt(std::string("hello"));
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, "hello");
}

// ============================================================
// Copy construction from engaged Optional
// ============================================================
TEST_F(OptionalTest_410, CopyConstructFromEngaged_410) {
    Catch::Optional<int> orig(7);
    Catch::Optional<int> copy(orig);
    EXPECT_TRUE(copy.some());
    EXPECT_EQ(*copy, 7);
    // Original should be unaffected
    EXPECT_TRUE(orig.some());
    EXPECT_EQ(*orig, 7);
}

// ============================================================
// Copy construction from disengaged Optional
// ============================================================
TEST_F(OptionalTest_410, CopyConstructFromDisengaged_410) {
    Catch::Optional<int> orig;
    Catch::Optional<int> copy(orig);
    EXPECT_TRUE(copy.none());
}

// ============================================================
// Move construction from engaged Optional
// ============================================================
TEST_F(OptionalTest_410, MoveConstructFromEngaged_410) {
    Catch::Optional<std::string> orig(std::string("world"));
    Catch::Optional<std::string> moved(std::move(orig));
    EXPECT_TRUE(moved.some());
    EXPECT_EQ(*moved, "world");
}

// ============================================================
// Move construction from disengaged Optional
// ============================================================
TEST_F(OptionalTest_410, MoveConstructFromDisengaged_410) {
    Catch::Optional<int> orig;
    Catch::Optional<int> moved(std::move(orig));
    EXPECT_TRUE(moved.none());
}

// ============================================================
// Copy assignment – value to empty
// ============================================================
TEST_F(OptionalTest_410, CopyAssignValueToEmpty_410) {
    Catch::Optional<int> opt;
    int v = 99;
    opt = v;
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, 99);
}

// ============================================================
// Copy assignment – value to engaged
// ============================================================
TEST_F(OptionalTest_410, CopyAssignValueToEngaged_410) {
    Catch::Optional<int> opt(10);
    int v = 20;
    opt = v;
    EXPECT_EQ(*opt, 20);
}

// ============================================================
// Move assignment from value
// ============================================================
TEST_F(OptionalTest_410, MoveAssignValue_410) {
    Catch::Optional<std::string> opt;
    opt = std::string("test");
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, "test");
}

// ============================================================
// Copy assignment from another Optional (engaged to empty)
// ============================================================
TEST_F(OptionalTest_410, CopyAssignOptionalEngagedToEmpty_410) {
    Catch::Optional<int> a(5);
    Catch::Optional<int> b;
    b = a;
    EXPECT_TRUE(b.some());
    EXPECT_EQ(*b, 5);
}

// ============================================================
// Copy assignment from another Optional (empty to engaged)
// ============================================================
TEST_F(OptionalTest_410, CopyAssignOptionalEmptyToEngaged_410) {
    Catch::Optional<int> a;
    Catch::Optional<int> b(5);
    b = a;
    EXPECT_TRUE(b.none());
}

// ============================================================
// Move assignment from another Optional
// ============================================================
TEST_F(OptionalTest_410, MoveAssignOptional_410) {
    Catch::Optional<std::string> a(std::string("abc"));
    Catch::Optional<std::string> b;
    b = std::move(a);
    EXPECT_TRUE(b.some());
    EXPECT_EQ(*b, "abc");
}

// ============================================================
// reset() on engaged Optional
// ============================================================
TEST_F(OptionalTest_410, ResetEngaged_410) {
    Catch::Optional<int> opt(42);
    EXPECT_TRUE(opt.some());
    opt.reset();
    EXPECT_TRUE(opt.none());
    EXPECT_FALSE(static_cast<bool>(opt));
}

// ============================================================
// reset() on disengaged Optional is safe
// ============================================================
TEST_F(OptionalTest_410, ResetDisengaged_410) {
    Catch::Optional<int> opt;
    opt.reset();
    EXPECT_TRUE(opt.none());
}

// ============================================================
// operator* returns mutable reference
// ============================================================
TEST_F(OptionalTest_410, DereferenceReturnsMutableRef_410) {
    Catch::Optional<int> opt(1);
    *opt = 100;
    EXPECT_EQ(*opt, 100);
}

// ============================================================
// operator-> provides member access
// ============================================================
TEST_F(OptionalTest_410, ArrowOperatorAccessesMembers_410) {
    Catch::Optional<std::string> opt(std::string("arrow"));
    EXPECT_EQ(opt->size(), 5u);
    opt->append("!");
    EXPECT_EQ(*opt, "arrow!");
}

// ============================================================
// valueOr returns contained value when engaged
// ============================================================
TEST_F(OptionalTest_410, ValueOrReturnsValueWhenEngaged_410) {
    Catch::Optional<int> opt(7);
    EXPECT_EQ(opt.valueOr(0), 7);
}

// ============================================================
// valueOr returns default when disengaged
// ============================================================
TEST_F(OptionalTest_410, ValueOrReturnsDefaultWhenDisengaged_410) {
    Catch::Optional<int> opt;
    EXPECT_EQ(opt.valueOr(42), 42);
}

// ============================================================
// some() / none() consistency
// ============================================================
TEST_F(OptionalTest_410, SomeNoneAreOpposites_410) {
    Catch::Optional<int> empty;
    EXPECT_NE(empty.some(), empty.none());

    Catch::Optional<int> full(1);
    EXPECT_NE(full.some(), full.none());
}

// ============================================================
// operator bool and operator! are consistent
// ============================================================
TEST_F(OptionalTest_410, BoolAndNotAreConsistent_410) {
    Catch::Optional<int> empty;
    EXPECT_EQ(static_cast<bool>(empty), !(!empty));

    Catch::Optional<int> full(1);
    EXPECT_EQ(static_cast<bool>(full), !(!full));
}

// ============================================================
// Self copy-assignment
// ============================================================
TEST_F(OptionalTest_410, SelfCopyAssignment_410) {
    Catch::Optional<int> opt(55);
    const auto& ref = opt;
    opt = ref;
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, 55);
}

// ============================================================
// Self move-assignment
// ============================================================
TEST_F(OptionalTest_410, SelfMoveAssignment_410) {
    Catch::Optional<int> opt(77);
    opt = std::move(opt);
    // After self-move, we just check it doesn't crash.
    // Behavior may vary, but it should be in a valid state.
    // We don't assert specific value.
}

// ============================================================
// Chain of assignments
// ============================================================
TEST_F(OptionalTest_410, ChainedAssignment_410) {
    Catch::Optional<int> a, b, c;
    int v = 10;
    a = v;
    b = a;
    c = std::move(b);
    EXPECT_TRUE(c.some());
    EXPECT_EQ(*c, 10);
}

// ============================================================
// Works with non-trivial types (struct with counter)
// ============================================================
namespace {
    struct Counter {
        static int instances;
        int value;
        Counter(int v) : value(v) { ++instances; }
        Counter(const Counter& o) : value(o.value) { ++instances; }
        Counter(Counter&& o) : value(o.value) { ++instances; o.value = -1; }
        ~Counter() { --instances; }
        Counter& operator=(const Counter&) = default;
        Counter& operator=(Counter&&) = default;
    };
    int Counter::instances = 0;
}

TEST_F(OptionalTest_410, DestructorCalledOnReset_410) {
    Counter::instances = 0;
    {
        Catch::Optional<Counter> opt(Counter(1));
        EXPECT_GT(Counter::instances, 0);
        opt.reset();
        EXPECT_EQ(Counter::instances, 0);
    }
    EXPECT_EQ(Counter::instances, 0);
}

TEST_F(OptionalTest_410, DestructorCalledOnDestruction_410) {
    Counter::instances = 0;
    {
        Catch::Optional<Counter> opt(Counter(2));
    }
    EXPECT_EQ(Counter::instances, 0);
}

TEST_F(OptionalTest_410, ReassignmentDestroysOldValue_410) {
    Counter::instances = 0;
    {
        Catch::Optional<Counter> opt(Counter(1));
        int before = Counter::instances;
        opt = Counter(2);
        // The instance count should stay the same (old destroyed, new created)
        EXPECT_EQ(Counter::instances, before);
        EXPECT_EQ(opt->value, 2);
    }
    EXPECT_EQ(Counter::instances, 0);
}

// ============================================================
// valueOr with string type
// ============================================================
TEST_F(OptionalTest_410, ValueOrWithString_410) {
    Catch::Optional<std::string> opt;
    EXPECT_EQ(opt.valueOr("default"), "default");

    opt = std::string("present");
    EXPECT_EQ(opt.valueOr("default"), "present");
}

// ============================================================
// Multiple resets
// ============================================================
TEST_F(OptionalTest_410, MultipleResets_410) {
    Catch::Optional<int> opt(10);
    opt.reset();
    opt.reset();
    opt.reset();
    EXPECT_TRUE(opt.none());
}

// ============================================================
// Assign after reset
// ============================================================
TEST_F(OptionalTest_410, AssignAfterReset_410) {
    Catch::Optional<int> opt(10);
    opt.reset();
    EXPECT_TRUE(opt.none());
    opt = 20;
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, 20);
}

// ============================================================
// Copy assign Optional engaged to engaged
// ============================================================
TEST_F(OptionalTest_410, CopyAssignOptionalEngagedToEngaged_410) {
    Catch::Optional<int> a(100);
    Catch::Optional<int> b(200);
    b = a;
    EXPECT_EQ(*b, 100);
    EXPECT_EQ(*a, 100);
}

// ============================================================
// Move assign Optional engaged to engaged
// ============================================================
TEST_F(OptionalTest_410, MoveAssignOptionalEngagedToEngaged_410) {
    Catch::Optional<std::string> a(std::string("first"));
    Catch::Optional<std::string> b(std::string("second"));
    b = std::move(a);
    EXPECT_EQ(*b, "first");
}
