#include "catch2/internal/catch_optional.hpp"
#include <gtest/gtest.h>
#include <string>
#include <utility>

// Test fixture
class OptionalTest_414 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== Default Construction ====================

TEST_F(OptionalTest_414, DefaultConstructedIsEmpty_414) {
    Catch::Optional<int> opt;
    EXPECT_TRUE(!opt);
    EXPECT_FALSE(static_cast<bool>(opt));
    EXPECT_TRUE(opt.none());
    EXPECT_FALSE(opt.some());
}

// ==================== Value Construction ====================

TEST_F(OptionalTest_414, ConstructWithLvalueHasValue_414) {
    int val = 42;
    Catch::Optional<int> opt(val);
    EXPECT_FALSE(!opt);
    EXPECT_TRUE(static_cast<bool>(opt));
    EXPECT_TRUE(opt.some());
    EXPECT_FALSE(opt.none());
    EXPECT_EQ(*opt, 42);
}

TEST_F(OptionalTest_414, ConstructWithRvalueHasValue_414) {
    Catch::Optional<int> opt(42);
    EXPECT_TRUE(static_cast<bool>(opt));
    EXPECT_EQ(*opt, 42);
}

TEST_F(OptionalTest_414, ConstructWithStringValue_414) {
    std::string s = "hello";
    Catch::Optional<std::string> opt(s);
    EXPECT_TRUE(static_cast<bool>(opt));
    EXPECT_EQ(*opt, "hello");
}

TEST_F(OptionalTest_414, ConstructWithStringRvalue_414) {
    Catch::Optional<std::string> opt(std::string("world"));
    EXPECT_TRUE(static_cast<bool>(opt));
    EXPECT_EQ(*opt, "world");
}

// ==================== Copy Construction ====================

TEST_F(OptionalTest_414, CopyConstructFromNonEmpty_414) {
    Catch::Optional<int> original(99);
    Catch::Optional<int> copy(original);
    EXPECT_TRUE(static_cast<bool>(copy));
    EXPECT_EQ(*copy, 99);
    // Original should still be valid
    EXPECT_TRUE(static_cast<bool>(original));
    EXPECT_EQ(*original, 99);
}

TEST_F(OptionalTest_414, CopyConstructFromEmpty_414) {
    Catch::Optional<int> original;
    Catch::Optional<int> copy(original);
    EXPECT_FALSE(static_cast<bool>(copy));
    EXPECT_TRUE(copy.none());
}

// ==================== Move Construction ====================

TEST_F(OptionalTest_414, MoveConstructFromNonEmpty_414) {
    Catch::Optional<std::string> original(std::string("moved"));
    Catch::Optional<std::string> moved(std::move(original));
    EXPECT_TRUE(static_cast<bool>(moved));
    EXPECT_EQ(*moved, "moved");
}

TEST_F(OptionalTest_414, MoveConstructFromEmpty_414) {
    Catch::Optional<int> original;
    Catch::Optional<int> moved(std::move(original));
    EXPECT_FALSE(static_cast<bool>(moved));
}

// ==================== Copy Assignment ====================

TEST_F(OptionalTest_414, CopyAssignValueToEmpty_414) {
    Catch::Optional<int> opt;
    int val = 10;
    opt = val;
    EXPECT_TRUE(static_cast<bool>(opt));
    EXPECT_EQ(*opt, 10);
}

TEST_F(OptionalTest_414, CopyAssignValueToNonEmpty_414) {
    Catch::Optional<int> opt(5);
    int val = 20;
    opt = val;
    EXPECT_TRUE(static_cast<bool>(opt));
    EXPECT_EQ(*opt, 20);
}

TEST_F(OptionalTest_414, CopyAssignOptionalToEmpty_414) {
    Catch::Optional<int> opt;
    Catch::Optional<int> other(30);
    opt = other;
    EXPECT_TRUE(static_cast<bool>(opt));
    EXPECT_EQ(*opt, 30);
}

TEST_F(OptionalTest_414, CopyAssignEmptyOptionalToNonEmpty_414) {
    Catch::Optional<int> opt(100);
    Catch::Optional<int> empty;
    opt = empty;
    EXPECT_FALSE(static_cast<bool>(opt));
}

TEST_F(OptionalTest_414, CopyAssignOptionalToNonEmpty_414) {
    Catch::Optional<int> opt(5);
    Catch::Optional<int> other(50);
    opt = other;
    EXPECT_TRUE(static_cast<bool>(opt));
    EXPECT_EQ(*opt, 50);
}

// ==================== Move Assignment ====================

TEST_F(OptionalTest_414, MoveAssignValueToEmpty_414) {
    Catch::Optional<std::string> opt;
    opt = std::string("assigned");
    EXPECT_TRUE(static_cast<bool>(opt));
    EXPECT_EQ(*opt, "assigned");
}

TEST_F(OptionalTest_414, MoveAssignOptionalToEmpty_414) {
    Catch::Optional<std::string> opt;
    Catch::Optional<std::string> other(std::string("from_other"));
    opt = std::move(other);
    EXPECT_TRUE(static_cast<bool>(opt));
    EXPECT_EQ(*opt, "from_other");
}

TEST_F(OptionalTest_414, MoveAssignEmptyOptionalToNonEmpty_414) {
    Catch::Optional<int> opt(42);
    Catch::Optional<int> empty;
    opt = std::move(empty);
    EXPECT_FALSE(static_cast<bool>(opt));
}

// ==================== Reset ====================

TEST_F(OptionalTest_414, ResetNonEmptyBecomesEmpty_414) {
    Catch::Optional<int> opt(42);
    EXPECT_TRUE(static_cast<bool>(opt));
    opt.reset();
    EXPECT_FALSE(static_cast<bool>(opt));
    EXPECT_TRUE(opt.none());
    EXPECT_FALSE(opt.some());
}

TEST_F(OptionalTest_414, ResetEmptyRemainsEmpty_414) {
    Catch::Optional<int> opt;
    opt.reset();
    EXPECT_FALSE(static_cast<bool>(opt));
}

// ==================== Dereference Operator ====================

TEST_F(OptionalTest_414, DereferenceReturnsCorrectValue_414) {
    Catch::Optional<int> opt(77);
    EXPECT_EQ(*opt, 77);
}

TEST_F(OptionalTest_414, DereferenceAllowsMutation_414) {
    Catch::Optional<int> opt(10);
    *opt = 20;
    EXPECT_EQ(*opt, 20);
}

// ==================== Arrow Operator ====================

TEST_F(OptionalTest_414, ArrowOperatorAccessesMember_414) {
    Catch::Optional<std::string> opt(std::string("test"));
    EXPECT_EQ(opt->size(), 4u);
    EXPECT_EQ(opt->at(0), 't');
}

// ==================== valueOr ====================

TEST_F(OptionalTest_414, ValueOrReturnsValueWhenPresent_414) {
    Catch::Optional<int> opt(42);
    EXPECT_EQ(opt.valueOr(0), 42);
}

TEST_F(OptionalTest_414, ValueOrReturnsDefaultWhenEmpty_414) {
    Catch::Optional<int> opt;
    EXPECT_EQ(opt.valueOr(99), 99);
}

TEST_F(OptionalTest_414, ValueOrWithStringWhenPresent_414) {
    Catch::Optional<std::string> opt(std::string("present"));
    EXPECT_EQ(opt.valueOr("default"), "present");
}

TEST_F(OptionalTest_414, ValueOrWithStringWhenEmpty_414) {
    Catch::Optional<std::string> opt;
    EXPECT_EQ(opt.valueOr("default"), "default");
}

// ==================== some() and none() ====================

TEST_F(OptionalTest_414, SomeReturnsTrueWhenHasValue_414) {
    Catch::Optional<int> opt(1);
    EXPECT_TRUE(opt.some());
}

TEST_F(OptionalTest_414, SomeReturnsFalseWhenEmpty_414) {
    Catch::Optional<int> opt;
    EXPECT_FALSE(opt.some());
}

TEST_F(OptionalTest_414, NoneReturnsTrueWhenEmpty_414) {
    Catch::Optional<int> opt;
    EXPECT_TRUE(opt.none());
}

TEST_F(OptionalTest_414, NoneReturnsFalseWhenHasValue_414) {
    Catch::Optional<int> opt(1);
    EXPECT_FALSE(opt.none());
}

// ==================== Boolean operators ====================

TEST_F(OptionalTest_414, NotOperatorTrueWhenEmpty_414) {
    Catch::Optional<int> opt;
    EXPECT_TRUE(!opt);
}

TEST_F(OptionalTest_414, NotOperatorFalseWhenHasValue_414) {
    Catch::Optional<int> opt(5);
    EXPECT_FALSE(!opt);
}

TEST_F(OptionalTest_414, ExplicitBoolTrueWhenHasValue_414) {
    Catch::Optional<int> opt(5);
    EXPECT_TRUE(static_cast<bool>(opt));
}

TEST_F(OptionalTest_414, ExplicitBoolFalseWhenEmpty_414) {
    Catch::Optional<int> opt;
    EXPECT_FALSE(static_cast<bool>(opt));
}

// ==================== Boundary / Special Cases ====================

TEST_F(OptionalTest_414, OptionalWithZeroValue_414) {
    Catch::Optional<int> opt(0);
    EXPECT_TRUE(static_cast<bool>(opt));
    EXPECT_EQ(*opt, 0);
    EXPECT_TRUE(opt.some());
}

TEST_F(OptionalTest_414, OptionalWithEmptyString_414) {
    Catch::Optional<std::string> opt(std::string(""));
    EXPECT_TRUE(static_cast<bool>(opt));
    EXPECT_EQ(*opt, "");
    EXPECT_TRUE(opt.some());
}

TEST_F(OptionalTest_414, OptionalWithNegativeValue_414) {
    Catch::Optional<int> opt(-1);
    EXPECT_TRUE(static_cast<bool>(opt));
    EXPECT_EQ(*opt, -1);
}

TEST_F(OptionalTest_414, OptionalWithFalseBoolean_414) {
    Catch::Optional<bool> opt(false);
    EXPECT_TRUE(static_cast<bool>(opt));
    EXPECT_EQ(*opt, false);
    EXPECT_TRUE(opt.some());
}

TEST_F(OptionalTest_414, OptionalWithTrueBoolean_414) {
    Catch::Optional<bool> opt(true);
    EXPECT_TRUE(static_cast<bool>(opt));
    EXPECT_EQ(*opt, true);
}

// ==================== Reassignment scenarios ====================

TEST_F(OptionalTest_414, ResetThenAssignAgain_414) {
    Catch::Optional<int> opt(42);
    opt.reset();
    EXPECT_FALSE(static_cast<bool>(opt));
    opt = 100;
    EXPECT_TRUE(static_cast<bool>(opt));
    EXPECT_EQ(*opt, 100);
}

TEST_F(OptionalTest_414, MultipleAssignments_414) {
    Catch::Optional<int> opt;
    opt = 1;
    EXPECT_EQ(*opt, 1);
    opt = 2;
    EXPECT_EQ(*opt, 2);
    opt = 3;
    EXPECT_EQ(*opt, 3);
}

TEST_F(OptionalTest_414, SelfCopyAssignment_414) {
    Catch::Optional<int> opt(42);
    const auto& ref = opt;
    opt = ref;
    EXPECT_TRUE(static_cast<bool>(opt));
    EXPECT_EQ(*opt, 42);
}

// ==================== Chaining assignment return value ====================

TEST_F(OptionalTest_414, AssignmentReturnsSelf_414) {
    Catch::Optional<int> opt;
    auto& returned = (opt = 42);
    EXPECT_EQ(&returned, &opt);
    EXPECT_EQ(*opt, 42);
}

TEST_F(OptionalTest_414, CopyAssignmentReturnsSelf_414) {
    Catch::Optional<int> opt;
    Catch::Optional<int> other(55);
    auto& returned = (opt = other);
    EXPECT_EQ(&returned, &opt);
    EXPECT_EQ(*opt, 55);
}

TEST_F(OptionalTest_414, MoveAssignmentReturnsSelf_414) {
    Catch::Optional<int> opt;
    Catch::Optional<int> other(66);
    auto& returned = (opt = std::move(other));
    EXPECT_EQ(&returned, &opt);
    EXPECT_EQ(*opt, 66);
}

// ==================== ValueOr does not modify the optional ====================

TEST_F(OptionalTest_414, ValueOrDoesNotModifyOptional_414) {
    Catch::Optional<int> opt(42);
    int result = opt.valueOr(0);
    EXPECT_EQ(result, 42);
    EXPECT_TRUE(static_cast<bool>(opt));
    EXPECT_EQ(*opt, 42);
}

TEST_F(OptionalTest_414, ValueOrOnEmptyDoesNotModify_414) {
    Catch::Optional<int> opt;
    int result = opt.valueOr(99);
    EXPECT_EQ(result, 99);
    EXPECT_FALSE(static_cast<bool>(opt));
}

// ==================== Complex type ====================

struct ComplexType {
    int x;
    std::string name;
    bool operator==(const ComplexType& other) const {
        return x == other.x && name == other.name;
    }
};

TEST_F(OptionalTest_414, OptionalWithComplexType_414) {
    ComplexType ct{42, "test"};
    Catch::Optional<ComplexType> opt(ct);
    EXPECT_TRUE(static_cast<bool>(opt));
    EXPECT_EQ(opt->x, 42);
    EXPECT_EQ(opt->name, "test");
}

TEST_F(OptionalTest_414, OptionalCopyComplexType_414) {
    ComplexType ct{10, "copy"};
    Catch::Optional<ComplexType> original(ct);
    Catch::Optional<ComplexType> copy(original);
    EXPECT_EQ(copy->x, 10);
    EXPECT_EQ(copy->name, "copy");
    EXPECT_EQ(original->x, 10);
}

TEST_F(OptionalTest_414, OptionalMoveComplexType_414) {
    ComplexType ct{20, "move_me"};
    Catch::Optional<ComplexType> original(std::move(ct));
    Catch::Optional<ComplexType> moved(std::move(original));
    EXPECT_TRUE(static_cast<bool>(moved));
    EXPECT_EQ(moved->x, 20);
}

TEST_F(OptionalTest_414, ResetComplexTypeOptional_414) {
    ComplexType ct{5, "reset"};
    Catch::Optional<ComplexType> opt(ct);
    opt.reset();
    EXPECT_FALSE(static_cast<bool>(opt));
    EXPECT_TRUE(opt.none());
}
