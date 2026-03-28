#include <gtest/gtest.h>
#include <string>
#include <utility>

// Include the header under test
#include "catch2/internal/catch_optional.hpp"

// Test fixture
class OptionalTest_409 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== Construction Tests ====================

TEST_F(OptionalTest_409, DefaultConstructor_IsNone_409) {
    Catch::Optional<int> opt;
    EXPECT_TRUE(opt.none());
    EXPECT_FALSE(opt.some());
    EXPECT_FALSE(static_cast<bool>(opt));
    EXPECT_TRUE(!opt);
}

TEST_F(OptionalTest_409, ConstructWithLValueInt_IsSome_409) {
    int val = 42;
    Catch::Optional<int> opt(val);
    EXPECT_TRUE(opt.some());
    EXPECT_FALSE(opt.none());
    EXPECT_TRUE(static_cast<bool>(opt));
    EXPECT_FALSE(!opt);
    EXPECT_EQ(*opt, 42);
}

TEST_F(OptionalTest_409, ConstructWithRValueInt_IsSome_409) {
    Catch::Optional<int> opt(42);
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, 42);
}

TEST_F(OptionalTest_409, ConstructWithString_409) {
    std::string s = "hello";
    Catch::Optional<std::string> opt(s);
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, "hello");
}

TEST_F(OptionalTest_409, ConstructWithRValueString_409) {
    Catch::Optional<std::string> opt(std::string("world"));
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, "world");
}

// ==================== Copy Construction Tests ====================

TEST_F(OptionalTest_409, CopyConstructFromSome_409) {
    Catch::Optional<int> opt1(100);
    Catch::Optional<int> opt2(opt1);
    EXPECT_TRUE(opt2.some());
    EXPECT_EQ(*opt2, 100);
    // Original should be unaffected
    EXPECT_TRUE(opt1.some());
    EXPECT_EQ(*opt1, 100);
}

TEST_F(OptionalTest_409, CopyConstructFromNone_409) {
    Catch::Optional<int> opt1;
    Catch::Optional<int> opt2(opt1);
    EXPECT_TRUE(opt2.none());
}

// ==================== Move Construction Tests ====================

TEST_F(OptionalTest_409, MoveConstructFromSome_409) {
    Catch::Optional<std::string> opt1(std::string("moveme"));
    Catch::Optional<std::string> opt2(std::move(opt1));
    EXPECT_TRUE(opt2.some());
    EXPECT_EQ(*opt2, "moveme");
}

TEST_F(OptionalTest_409, MoveConstructFromNone_409) {
    Catch::Optional<int> opt1;
    Catch::Optional<int> opt2(std::move(opt1));
    EXPECT_TRUE(opt2.none());
}

// ==================== Copy Assignment Tests ====================

TEST_F(OptionalTest_409, CopyAssignValueToNone_409) {
    Catch::Optional<int> opt;
    int val = 55;
    opt = val;
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, 55);
}

TEST_F(OptionalTest_409, CopyAssignValueToSome_409) {
    Catch::Optional<int> opt(10);
    int val = 20;
    opt = val;
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, 20);
}

TEST_F(OptionalTest_409, MoveAssignValue_409) {
    Catch::Optional<std::string> opt;
    opt = std::string("assigned");
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, "assigned");
}

TEST_F(OptionalTest_409, CopyAssignOptionalSomeToNone_409) {
    Catch::Optional<int> opt1(77);
    Catch::Optional<int> opt2;
    opt2 = opt1;
    EXPECT_TRUE(opt2.some());
    EXPECT_EQ(*opt2, 77);
}

TEST_F(OptionalTest_409, CopyAssignOptionalNoneToSome_409) {
    Catch::Optional<int> opt1;
    Catch::Optional<int> opt2(99);
    opt2 = opt1;
    EXPECT_TRUE(opt2.none());
}

TEST_F(OptionalTest_409, CopyAssignOptionalSomeToSome_409) {
    Catch::Optional<int> opt1(11);
    Catch::Optional<int> opt2(22);
    opt2 = opt1;
    EXPECT_TRUE(opt2.some());
    EXPECT_EQ(*opt2, 11);
}

TEST_F(OptionalTest_409, CopyAssignOptionalNoneToNone_409) {
    Catch::Optional<int> opt1;
    Catch::Optional<int> opt2;
    opt2 = opt1;
    EXPECT_TRUE(opt2.none());
}

// ==================== Move Assignment Tests ====================

TEST_F(OptionalTest_409, MoveAssignOptionalSomeToNone_409) {
    Catch::Optional<std::string> opt1(std::string("move_assign"));
    Catch::Optional<std::string> opt2;
    opt2 = std::move(opt1);
    EXPECT_TRUE(opt2.some());
    EXPECT_EQ(*opt2, "move_assign");
}

TEST_F(OptionalTest_409, MoveAssignOptionalNoneToSome_409) {
    Catch::Optional<int> opt1;
    Catch::Optional<int> opt2(5);
    opt2 = std::move(opt1);
    EXPECT_TRUE(opt2.none());
}

// ==================== Reset Tests ====================

TEST_F(OptionalTest_409, ResetFromSome_409) {
    Catch::Optional<int> opt(42);
    EXPECT_TRUE(opt.some());
    opt.reset();
    EXPECT_TRUE(opt.none());
    EXPECT_FALSE(opt.some());
    EXPECT_FALSE(static_cast<bool>(opt));
}

TEST_F(OptionalTest_409, ResetFromNone_409) {
    Catch::Optional<int> opt;
    opt.reset();
    EXPECT_TRUE(opt.none());
}

// ==================== Dereference and Arrow Operator Tests ====================

TEST_F(OptionalTest_409, DereferenceOperator_409) {
    Catch::Optional<int> opt(123);
    EXPECT_EQ(*opt, 123);
    // Modify through dereference
    *opt = 456;
    EXPECT_EQ(*opt, 456);
}

TEST_F(OptionalTest_409, ArrowOperator_409) {
    Catch::Optional<std::string> opt(std::string("arrow"));
    EXPECT_EQ(opt->size(), 5u);
    EXPECT_EQ(opt->at(0), 'a');
}

// ==================== valueOr Tests ====================

TEST_F(OptionalTest_409, ValueOrWhenSome_409) {
    Catch::Optional<int> opt(42);
    EXPECT_EQ(opt.valueOr(0), 42);
}

TEST_F(OptionalTest_409, ValueOrWhenNone_409) {
    Catch::Optional<int> opt;
    EXPECT_EQ(opt.valueOr(99), 99);
}

TEST_F(OptionalTest_409, ValueOrWithString_409) {
    Catch::Optional<std::string> opt;
    EXPECT_EQ(opt.valueOr("default"), "default");
}

TEST_F(OptionalTest_409, ValueOrWithStringWhenSome_409) {
    Catch::Optional<std::string> opt(std::string("present"));
    EXPECT_EQ(opt.valueOr("default"), "present");
}

// ==================== Boolean Conversion Tests ====================

TEST_F(OptionalTest_409, ExplicitBoolConversionTrue_409) {
    Catch::Optional<int> opt(1);
    EXPECT_TRUE(static_cast<bool>(opt));
}

TEST_F(OptionalTest_409, ExplicitBoolConversionFalse_409) {
    Catch::Optional<int> opt;
    EXPECT_FALSE(static_cast<bool>(opt));
}

TEST_F(OptionalTest_409, NotOperatorTrue_409) {
    Catch::Optional<int> opt;
    EXPECT_TRUE(!opt);
}

TEST_F(OptionalTest_409, NotOperatorFalse_409) {
    Catch::Optional<int> opt(0);
    EXPECT_FALSE(!opt);
}

// ==================== some() and none() Tests ====================

TEST_F(OptionalTest_409, SomeAndNoneConsistency_409) {
    Catch::Optional<int> opt;
    EXPECT_NE(opt.some(), opt.none());
    
    opt = 5;
    EXPECT_NE(opt.some(), opt.none());
    EXPECT_TRUE(opt.some());
    EXPECT_FALSE(opt.none());
}

// ==================== Edge Cases ====================

TEST_F(OptionalTest_409, OptionalWithZeroValue_409) {
    Catch::Optional<int> opt(0);
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, 0);
    EXPECT_TRUE(static_cast<bool>(opt));
}

TEST_F(OptionalTest_409, OptionalWithNegativeValue_409) {
    Catch::Optional<int> opt(-1);
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, -1);
}

TEST_F(OptionalTest_409, OptionalWithEmptyString_409) {
    Catch::Optional<std::string> opt(std::string(""));
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, "");
}

TEST_F(OptionalTest_409, OptionalWithBoolFalse_409) {
    Catch::Optional<bool> opt(false);
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, false);
    EXPECT_TRUE(static_cast<bool>(opt));  // Optional has value, even if value is false
}

TEST_F(OptionalTest_409, ReassignMultipleTimes_409) {
    Catch::Optional<int> opt;
    opt = 1;
    EXPECT_EQ(*opt, 1);
    opt = 2;
    EXPECT_EQ(*opt, 2);
    opt.reset();
    EXPECT_TRUE(opt.none());
    opt = 3;
    EXPECT_EQ(*opt, 3);
}

TEST_F(OptionalTest_409, SelfCopyAssignment_409) {
    Catch::Optional<int> opt(42);
    opt = opt;  // self-assignment
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, 42);
}

TEST_F(OptionalTest_409, ChainedAssignment_409) {
    Catch::Optional<int> opt1, opt2, opt3;
    int val = 10;
    opt1 = val;
    opt2 = opt1;
    opt3 = opt2;
    EXPECT_EQ(*opt3, 10);
}

// ==================== Struct Type Tests ====================

struct TestStruct {
    int x;
    double y;
    bool operator==(const TestStruct& other) const {
        return x == other.x && y == other.y;
    }
};

TEST_F(OptionalTest_409, OptionalWithStruct_409) {
    TestStruct ts{10, 3.14};
    Catch::Optional<TestStruct> opt(ts);
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(opt->x, 10);
    EXPECT_DOUBLE_EQ(opt->y, 3.14);
}

TEST_F(OptionalTest_409, OptionalWithStructValueOr_409) {
    Catch::Optional<TestStruct> opt;
    TestStruct defaultVal{0, 0.0};
    auto result = opt.valueOr(defaultVal);
    EXPECT_EQ(result.x, 0);
    EXPECT_DOUBLE_EQ(result.y, 0.0);
}

// ==================== Const Optional Tests ====================

TEST_F(OptionalTest_409, ConstOptionalValueOr_409) {
    const Catch::Optional<int> opt(42);
    EXPECT_EQ(opt.valueOr(0), 42);
}

TEST_F(OptionalTest_409, ConstOptionalNoneValueOr_409) {
    const Catch::Optional<int> opt;
    EXPECT_EQ(opt.valueOr(99), 99);
}

TEST_F(OptionalTest_409, ConstOptionalSome_409) {
    const Catch::Optional<int> opt(42);
    EXPECT_TRUE(opt.some());
    EXPECT_FALSE(opt.none());
    EXPECT_TRUE(static_cast<bool>(opt));
}
