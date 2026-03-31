#include "catch2/internal/catch_optional.hpp"
#include <gtest/gtest.h>
#include <string>
#include <utility>

using Catch::Optional;

// ============================================================
// Default construction tests
// ============================================================

TEST(OptionalTest_412, DefaultConstructedIsNone_412) {
    Optional<int> opt;
    EXPECT_TRUE(opt.none());
    EXPECT_FALSE(opt.some());
    EXPECT_FALSE(static_cast<bool>(opt));
    EXPECT_TRUE(!opt);
}

// ============================================================
// Construction with value
// ============================================================

TEST(OptionalTest_412, ConstructWithLvalueIsSome_412) {
    int val = 42;
    Optional<int> opt(val);
    EXPECT_TRUE(opt.some());
    EXPECT_FALSE(opt.none());
    EXPECT_TRUE(static_cast<bool>(opt));
    EXPECT_FALSE(!opt);
    EXPECT_EQ(*opt, 42);
}

TEST(OptionalTest_412, ConstructWithRvalueIsSome_412) {
    Optional<int> opt(99);
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, 99);
}

TEST(OptionalTest_412, ConstructWithString_412) {
    std::string s = "hello";
    Optional<std::string> opt(s);
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, "hello");
}

TEST(OptionalTest_412, ConstructWithRvalueString_412) {
    Optional<std::string> opt(std::string("world"));
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, "world");
}

// ============================================================
// Copy construction
// ============================================================

TEST(OptionalTest_412, CopyConstructFromSome_412) {
    Optional<int> opt1(10);
    Optional<int> opt2(opt1);
    EXPECT_TRUE(opt2.some());
    EXPECT_EQ(*opt2, 10);
    // Original should be unaffected
    EXPECT_TRUE(opt1.some());
    EXPECT_EQ(*opt1, 10);
}

TEST(OptionalTest_412, CopyConstructFromNone_412) {
    Optional<int> opt1;
    Optional<int> opt2(opt1);
    EXPECT_TRUE(opt2.none());
}

// ============================================================
// Move construction
// ============================================================

TEST(OptionalTest_412, MoveConstructFromSome_412) {
    Optional<std::string> opt1(std::string("moveme"));
    Optional<std::string> opt2(std::move(opt1));
    EXPECT_TRUE(opt2.some());
    EXPECT_EQ(*opt2, "moveme");
}

TEST(OptionalTest_412, MoveConstructFromNone_412) {
    Optional<int> opt1;
    Optional<int> opt2(std::move(opt1));
    EXPECT_TRUE(opt2.none());
}

// ============================================================
// Copy assignment
// ============================================================

TEST(OptionalTest_412, CopyAssignValueToNone_412) {
    Optional<int> opt;
    int val = 55;
    opt = val;
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, 55);
}

TEST(OptionalTest_412, CopyAssignValueToSome_412) {
    Optional<int> opt(10);
    int val = 20;
    opt = val;
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, 20);
}

TEST(OptionalTest_412, CopyAssignOptionalSomeToNone_412) {
    Optional<int> opt1;
    Optional<int> opt2(77);
    opt1 = opt2;
    EXPECT_TRUE(opt1.some());
    EXPECT_EQ(*opt1, 77);
}

TEST(OptionalTest_412, CopyAssignOptionalNoneToSome_412) {
    Optional<int> opt1(42);
    Optional<int> opt2;
    opt1 = opt2;
    EXPECT_TRUE(opt1.none());
}

TEST(OptionalTest_412, CopyAssignOptionalSomeToSome_412) {
    Optional<int> opt1(1);
    Optional<int> opt2(2);
    opt1 = opt2;
    EXPECT_TRUE(opt1.some());
    EXPECT_EQ(*opt1, 2);
}

TEST(OptionalTest_412, CopyAssignOptionalNoneToNone_412) {
    Optional<int> opt1;
    Optional<int> opt2;
    opt1 = opt2;
    EXPECT_TRUE(opt1.none());
}

// ============================================================
// Move assignment
// ============================================================

TEST(OptionalTest_412, MoveAssignRvalueToNone_412) {
    Optional<int> opt;
    opt = 123;
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, 123);
}

TEST(OptionalTest_412, MoveAssignRvalueToSome_412) {
    Optional<int> opt(10);
    opt = 20;
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, 20);
}

TEST(OptionalTest_412, MoveAssignOptionalSomeToNone_412) {
    Optional<std::string> opt1;
    Optional<std::string> opt2(std::string("moved"));
    opt1 = std::move(opt2);
    EXPECT_TRUE(opt1.some());
    EXPECT_EQ(*opt1, "moved");
}

TEST(OptionalTest_412, MoveAssignOptionalNoneToSome_412) {
    Optional<int> opt1(42);
    Optional<int> opt2;
    opt1 = std::move(opt2);
    EXPECT_TRUE(opt1.none());
}

// ============================================================
// reset
// ============================================================

TEST(OptionalTest_412, ResetFromSome_412) {
    Optional<int> opt(42);
    EXPECT_TRUE(opt.some());
    opt.reset();
    EXPECT_TRUE(opt.none());
    EXPECT_FALSE(opt.some());
    EXPECT_FALSE(static_cast<bool>(opt));
}

TEST(OptionalTest_412, ResetFromNone_412) {
    Optional<int> opt;
    opt.reset();
    EXPECT_TRUE(opt.none());
}

// ============================================================
// Dereference operator*
// ============================================================

TEST(OptionalTest_412, DereferenceReturnsValue_412) {
    Optional<int> opt(7);
    EXPECT_EQ(*opt, 7);
}

TEST(OptionalTest_412, DereferenceAllowsModification_412) {
    Optional<int> opt(7);
    *opt = 14;
    EXPECT_EQ(*opt, 14);
}

// ============================================================
// Arrow operator->
// ============================================================

TEST(OptionalTest_412, ArrowOperatorAccessesMember_412) {
    Optional<std::string> opt(std::string("test"));
    EXPECT_EQ(opt->size(), 4u);
}

TEST(OptionalTest_412, ArrowOperatorAllowsMutation_412) {
    Optional<std::string> opt(std::string("test"));
    opt->append("123");
    EXPECT_EQ(*opt, "test123");
}

// ============================================================
// valueOr
// ============================================================

TEST(OptionalTest_412, ValueOrReturnValueWhenSome_412) {
    Optional<int> opt(42);
    EXPECT_EQ(opt.valueOr(0), 42);
}

TEST(OptionalTest_412, ValueOrReturnsDefaultWhenNone_412) {
    Optional<int> opt;
    EXPECT_EQ(opt.valueOr(99), 99);
}

TEST(OptionalTest_412, ValueOrWithString_412) {
    Optional<std::string> opt;
    EXPECT_EQ(opt.valueOr("default"), "default");
}

TEST(OptionalTest_412, ValueOrWithStringWhenSome_412) {
    Optional<std::string> opt(std::string("actual"));
    EXPECT_EQ(opt.valueOr("default"), "actual");
}

// ============================================================
// some() / none() / operator bool / operator!
// ============================================================

TEST(OptionalTest_412, SomeAndNoneAreOpposites_412) {
    Optional<int> opt;
    EXPECT_EQ(opt.some(), !opt.none());

    Optional<int> opt2(1);
    EXPECT_EQ(opt2.some(), !opt2.none());
}

TEST(OptionalTest_412, BoolConversionMatchesSome_412) {
    Optional<int> opt;
    EXPECT_EQ(static_cast<bool>(opt), opt.some());

    Optional<int> opt2(1);
    EXPECT_EQ(static_cast<bool>(opt2), opt2.some());
}

TEST(OptionalTest_412, NotOperatorMatchesNone_412) {
    Optional<int> opt;
    EXPECT_EQ(!opt, opt.none());

    Optional<int> opt2(1);
    EXPECT_EQ(!opt2, opt2.none());
}

// ============================================================
// Self-assignment
// ============================================================

TEST(OptionalTest_412, SelfCopyAssignment_412) {
    Optional<int> opt(42);
    opt = opt;
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, 42);
}

TEST(OptionalTest_412, SelfMoveAssignment_412) {
    Optional<int> opt(42);
    opt = std::move(opt);
    // After self-move, we just check it doesn't crash.
    // Behavior may be implementation-defined but shouldn't segfault.
}

// ============================================================
// Chained assignments
// ============================================================

TEST(OptionalTest_412, ChainedAssignment_412) {
    Optional<int> opt1, opt2, opt3;
    int val = 10;
    opt1 = val;
    opt2 = opt1;
    opt3 = opt2;
    EXPECT_EQ(*opt3, 10);
}

// ============================================================
// Complex type
// ============================================================

struct Trackable {
    static int instances;
    int value;
    Trackable(int v) : value(v) { ++instances; }
    Trackable(const Trackable& o) : value(o.value) { ++instances; }
    Trackable(Trackable&& o) : value(o.value) { ++instances; o.value = -1; }
    ~Trackable() { --instances; }
};
int Trackable::instances = 0;

TEST(OptionalTest_412, DestructorCalledOnReset_412) {
    Trackable::instances = 0;
    {
        Optional<Trackable> opt(Trackable(5));
        EXPECT_EQ(Trackable::instances, 1);
        opt.reset();
        EXPECT_EQ(Trackable::instances, 0);
        EXPECT_TRUE(opt.none());
    }
    EXPECT_EQ(Trackable::instances, 0);
}

TEST(OptionalTest_412, DestructorCalledOnDestruction_412) {
    Trackable::instances = 0;
    {
        Optional<Trackable> opt(Trackable(5));
        EXPECT_EQ(Trackable::instances, 1);
    }
    EXPECT_EQ(Trackable::instances, 0);
}

TEST(OptionalTest_412, DestructorCalledOnReassignment_412) {
    Trackable::instances = 0;
    {
        Optional<Trackable> opt(Trackable(5));
        EXPECT_EQ(Trackable::instances, 1);
        opt = Trackable(10);
        EXPECT_EQ(Trackable::instances, 1);
        EXPECT_EQ(opt->value, 10);
    }
    EXPECT_EQ(Trackable::instances, 0);
}

// ============================================================
// Multiple resets
// ============================================================

TEST(OptionalTest_412, MultipleResetsAreSafe_412) {
    Optional<int> opt(42);
    opt.reset();
    opt.reset();
    opt.reset();
    EXPECT_TRUE(opt.none());
}

// ============================================================
// Reassign after reset
// ============================================================

TEST(OptionalTest_412, ReassignAfterReset_412) {
    Optional<int> opt(42);
    opt.reset();
    EXPECT_TRUE(opt.none());
    opt = 100;
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, 100);
}

// ============================================================
// valueOr does not modify state
// ============================================================

TEST(OptionalTest_412, ValueOrDoesNotModifyState_412) {
    Optional<int> opt;
    int result = opt.valueOr(5);
    EXPECT_EQ(result, 5);
    EXPECT_TRUE(opt.none());

    Optional<int> opt2(10);
    result = opt2.valueOr(5);
    EXPECT_EQ(result, 10);
    EXPECT_TRUE(opt2.some());
    EXPECT_EQ(*opt2, 10);
}
