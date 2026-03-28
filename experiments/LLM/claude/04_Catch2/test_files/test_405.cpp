#include "catch2/internal/catch_optional.hpp"
#include <gtest/gtest.h>
#include <string>
#include <utility>

using Catch::Optional;

// ============================================================
// Test Fixture
// ============================================================
class OptionalTest_405 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ============================================================
// Default Construction
// ============================================================
TEST_F(OptionalTest_405, DefaultConstructedIsNone_405) {
    Optional<int> opt;
    EXPECT_TRUE(opt.none());
    EXPECT_FALSE(opt.some());
    EXPECT_FALSE(static_cast<bool>(opt));
    EXPECT_TRUE(!opt);
}

// ============================================================
// Construction with value (lvalue)
// ============================================================
TEST_F(OptionalTest_405, ConstructWithLvalueHasValue_405) {
    int val = 42;
    Optional<int> opt(val);
    EXPECT_TRUE(opt.some());
    EXPECT_FALSE(opt.none());
    EXPECT_TRUE(static_cast<bool>(opt));
    EXPECT_FALSE(!opt);
    EXPECT_EQ(*opt, 42);
}

// ============================================================
// Construction with value (rvalue)
// ============================================================
TEST_F(OptionalTest_405, ConstructWithRvalueHasValue_405) {
    Optional<std::string> opt(std::string("hello"));
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, "hello");
}

// ============================================================
// Copy Construction from engaged Optional
// ============================================================
TEST_F(OptionalTest_405, CopyConstructFromEngaged_405) {
    Optional<int> opt1(10);
    Optional<int> opt2(opt1);
    EXPECT_TRUE(opt2.some());
    EXPECT_EQ(*opt2, 10);
    // Original should still be intact
    EXPECT_TRUE(opt1.some());
    EXPECT_EQ(*opt1, 10);
}

// ============================================================
// Copy Construction from disengaged Optional
// ============================================================
TEST_F(OptionalTest_405, CopyConstructFromDisengaged_405) {
    Optional<int> opt1;
    Optional<int> opt2(opt1);
    EXPECT_TRUE(opt2.none());
}

// ============================================================
// Move Construction from engaged Optional
// ============================================================
TEST_F(OptionalTest_405, MoveConstructFromEngaged_405) {
    Optional<std::string> opt1(std::string("world"));
    Optional<std::string> opt2(std::move(opt1));
    EXPECT_TRUE(opt2.some());
    EXPECT_EQ(*opt2, "world");
}

// ============================================================
// Move Construction from disengaged Optional
// ============================================================
TEST_F(OptionalTest_405, MoveConstructFromDisengaged_405) {
    Optional<int> opt1;
    Optional<int> opt2(std::move(opt1));
    EXPECT_TRUE(opt2.none());
}

// ============================================================
// Assignment from lvalue T
// ============================================================
TEST_F(OptionalTest_405, AssignLvalueT_405) {
    Optional<int> opt;
    int val = 99;
    opt = val;
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, 99);
}

// ============================================================
// Assignment from rvalue T
// ============================================================
TEST_F(OptionalTest_405, AssignRvalueT_405) {
    Optional<std::string> opt;
    opt = std::string("test");
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, "test");
}

// ============================================================
// Reassignment from rvalue T (already engaged)
// ============================================================
TEST_F(OptionalTest_405, ReassignRvalueT_405) {
    Optional<int> opt(5);
    opt = 10;
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, 10);
}

// ============================================================
// Copy Assignment from engaged Optional
// ============================================================
TEST_F(OptionalTest_405, CopyAssignFromEngaged_405) {
    Optional<int> opt1(7);
    Optional<int> opt2;
    opt2 = opt1;
    EXPECT_TRUE(opt2.some());
    EXPECT_EQ(*opt2, 7);
}

// ============================================================
// Copy Assignment from disengaged Optional
// ============================================================
TEST_F(OptionalTest_405, CopyAssignFromDisengaged_405) {
    Optional<int> opt1;
    Optional<int> opt2(42);
    opt2 = opt1;
    EXPECT_TRUE(opt2.none());
}

// ============================================================
// Move Assignment from engaged Optional
// ============================================================
TEST_F(OptionalTest_405, MoveAssignFromEngaged_405) {
    Optional<std::string> opt1(std::string("abc"));
    Optional<std::string> opt2;
    opt2 = std::move(opt1);
    EXPECT_TRUE(opt2.some());
    EXPECT_EQ(*opt2, "abc");
}

// ============================================================
// Move Assignment from disengaged Optional
// ============================================================
TEST_F(OptionalTest_405, MoveAssignFromDisengaged_405) {
    Optional<int> opt1;
    Optional<int> opt2(100);
    opt2 = std::move(opt1);
    EXPECT_TRUE(opt2.none());
}

// ============================================================
// Reset engaged Optional
// ============================================================
TEST_F(OptionalTest_405, ResetEngaged_405) {
    Optional<int> opt(123);
    EXPECT_TRUE(opt.some());
    opt.reset();
    EXPECT_TRUE(opt.none());
    EXPECT_FALSE(static_cast<bool>(opt));
}

// ============================================================
// Reset disengaged Optional (should be safe)
// ============================================================
TEST_F(OptionalTest_405, ResetDisengaged_405) {
    Optional<int> opt;
    EXPECT_TRUE(opt.none());
    opt.reset();
    EXPECT_TRUE(opt.none());
}

// ============================================================
// Dereference operator
// ============================================================
TEST_F(OptionalTest_405, DereferenceOperator_405) {
    Optional<int> opt(55);
    EXPECT_EQ(*opt, 55);
    *opt = 66;
    EXPECT_EQ(*opt, 66);
}

// ============================================================
// Arrow operator
// ============================================================
TEST_F(OptionalTest_405, ArrowOperator_405) {
    Optional<std::string> opt(std::string("arrow"));
    EXPECT_EQ(opt->size(), 5u);
    EXPECT_EQ(opt->at(0), 'a');
}

// ============================================================
// valueOr with engaged Optional
// ============================================================
TEST_F(OptionalTest_405, ValueOrEngaged_405) {
    Optional<int> opt(42);
    EXPECT_EQ(opt.valueOr(0), 42);
}

// ============================================================
// valueOr with disengaged Optional
// ============================================================
TEST_F(OptionalTest_405, ValueOrDisengaged_405) {
    Optional<int> opt;
    EXPECT_EQ(opt.valueOr(99), 99);
}

// ============================================================
// some() and none() are consistent
// ============================================================
TEST_F(OptionalTest_405, SomeAndNoneConsistent_405) {
    Optional<int> opt;
    EXPECT_NE(opt.some(), opt.none());

    opt = 1;
    EXPECT_NE(opt.some(), opt.none());
    EXPECT_TRUE(opt.some());
    EXPECT_FALSE(opt.none());
}

// ============================================================
// Bool conversion and negation operator consistency
// ============================================================
TEST_F(OptionalTest_405, BoolAndNegationConsistency_405) {
    Optional<int> opt;
    EXPECT_EQ(static_cast<bool>(opt), !(!opt));

    opt = 5;
    EXPECT_EQ(static_cast<bool>(opt), !(!opt));
    EXPECT_TRUE(static_cast<bool>(opt));
    EXPECT_FALSE(!opt);
}

// ============================================================
// Assign value, reset, assign again
// ============================================================
TEST_F(OptionalTest_405, AssignResetReassign_405) {
    Optional<int> opt;
    opt = 1;
    EXPECT_EQ(*opt, 1);
    opt.reset();
    EXPECT_TRUE(opt.none());
    opt = 2;
    EXPECT_EQ(*opt, 2);
    EXPECT_TRUE(opt.some());
}

// ============================================================
// Multiple reassignments
// ============================================================
TEST_F(OptionalTest_405, MultipleReassignments_405) {
    Optional<int> opt(1);
    for (int i = 0; i < 100; ++i) {
        opt = i;
        EXPECT_EQ(*opt, i);
    }
}

// ============================================================
// Works with complex types
// ============================================================
TEST_F(OptionalTest_405, WorksWithComplexType_405) {
    struct Complex {
        int a;
        std::string b;
        bool operator==(const Complex& o) const { return a == o.a && b == o.b; }
    };

    Complex c{42, "hello"};
    Optional<Complex> opt(c);
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(opt->a, 42);
    EXPECT_EQ(opt->b, "hello");

    opt.reset();
    EXPECT_TRUE(opt.none());
}

// ============================================================
// Self copy assignment (engaged)
// ============================================================
TEST_F(OptionalTest_405, SelfCopyAssignment_405) {
    Optional<int> opt(77);
    opt = opt;
    // Should still be valid after self-assignment
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, 77);
}

// ============================================================
// Self move assignment (engaged)
// ============================================================
TEST_F(OptionalTest_405, SelfMoveAssignment_405) {
    Optional<int> opt(88);
    opt = std::move(opt);
    // Behavior may vary, but should not crash; just check it's still usable
    // We don't assert value since self-move is implementation-defined
}

// ============================================================
// Chain assignment returns reference
// ============================================================
TEST_F(OptionalTest_405, ChainAssignment_405) {
    Optional<int> opt;
    auto& ref = (opt = 5);
    EXPECT_EQ(&ref, &opt);
    EXPECT_EQ(*opt, 5);
}

// ============================================================
// valueOr with string type
// ============================================================
TEST_F(OptionalTest_405, ValueOrString_405) {
    Optional<std::string> opt;
    EXPECT_EQ(opt.valueOr("default"), "default");

    opt = std::string("value");
    EXPECT_EQ(opt.valueOr("default"), "value");
}

// ============================================================
// Const Optional valueOr
// ============================================================
TEST_F(OptionalTest_405, ConstOptionalValueOr_405) {
    const Optional<int> opt1(10);
    EXPECT_EQ(opt1.valueOr(0), 10);

    const Optional<int> opt2;
    EXPECT_EQ(opt2.valueOr(0), 0);
}

// ============================================================
// Const Optional bool conversion
// ============================================================
TEST_F(OptionalTest_405, ConstOptionalBool_405) {
    const Optional<int> opt1(10);
    EXPECT_TRUE(static_cast<bool>(opt1));
    EXPECT_TRUE(opt1.some());
    EXPECT_FALSE(opt1.none());

    const Optional<int> opt2;
    EXPECT_FALSE(static_cast<bool>(opt2));
    EXPECT_FALSE(opt2.some());
    EXPECT_TRUE(opt2.none());
}

// ============================================================
// Optional with zero value (boundary: zero != none)
// ============================================================
TEST_F(OptionalTest_405, ZeroValueIsNotNone_405) {
    Optional<int> opt(0);
    EXPECT_TRUE(opt.some());
    EXPECT_FALSE(opt.none());
    EXPECT_EQ(*opt, 0);
}

// ============================================================
// Optional with false bool (boundary: false != none)
// ============================================================
TEST_F(OptionalTest_405, FalseValueIsNotNone_405) {
    Optional<bool> opt(false);
    EXPECT_TRUE(opt.some());
    EXPECT_FALSE(opt.none());
    EXPECT_EQ(*opt, false);
}

// ============================================================
// Optional with empty string (boundary: empty != none)
// ============================================================
TEST_F(OptionalTest_405, EmptyStringIsNotNone_405) {
    Optional<std::string> opt(std::string(""));
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, "");
}

// ============================================================
// Copy assign engaged to engaged
// ============================================================
TEST_F(OptionalTest_405, CopyAssignEngagedToEngaged_405) {
    Optional<int> opt1(10);
    Optional<int> opt2(20);
    opt2 = opt1;
    EXPECT_EQ(*opt2, 10);
    EXPECT_EQ(*opt1, 10);
}

// ============================================================
// Move assign engaged to engaged
// ============================================================
TEST_F(OptionalTest_405, MoveAssignEngagedToEngaged_405) {
    Optional<std::string> opt1(std::string("source"));
    Optional<std::string> opt2(std::string("target"));
    opt2 = std::move(opt1);
    EXPECT_EQ(*opt2, "source");
}

// ============================================================
// Lvalue assign to already engaged
// ============================================================
TEST_F(OptionalTest_405, LvalueAssignToEngaged_405) {
    Optional<int> opt(10);
    int val = 20;
    opt = val;
    EXPECT_EQ(*opt, 20);
}
