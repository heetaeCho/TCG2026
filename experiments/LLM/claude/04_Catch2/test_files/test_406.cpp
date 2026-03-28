#include "catch2/internal/catch_optional.hpp"
#include <gtest/gtest.h>
#include <string>
#include <utility>

using Catch::Optional;

// Test default construction creates empty optional
TEST(OptionalTest_406, DefaultConstructionIsEmpty_406) {
    Optional<int> opt;
    EXPECT_TRUE(opt.none());
    EXPECT_FALSE(opt.some());
    EXPECT_FALSE(static_cast<bool>(opt));
    EXPECT_TRUE(!opt);
}

// Test construction with a value
TEST(OptionalTest_406, ConstructWithValue_406) {
    Optional<int> opt(42);
    EXPECT_TRUE(opt.some());
    EXPECT_FALSE(opt.none());
    EXPECT_TRUE(static_cast<bool>(opt));
    EXPECT_FALSE(!opt);
    EXPECT_EQ(*opt, 42);
}

// Test copy construction from non-empty optional
TEST(OptionalTest_406, CopyConstructionFromNonEmpty_406) {
    Optional<int> opt1(42);
    Optional<int> opt2(opt1);
    EXPECT_TRUE(opt2.some());
    EXPECT_EQ(*opt2, 42);
    EXPECT_EQ(*opt1, 42); // original should be unchanged
}

// Test copy construction from empty optional
TEST(OptionalTest_406, CopyConstructionFromEmpty_406) {
    Optional<int> opt1;
    Optional<int> opt2(opt1);
    EXPECT_TRUE(opt2.none());
}

// Test move construction from non-empty optional
TEST(OptionalTest_406, MoveConstructionFromNonEmpty_406) {
    Optional<std::string> opt1(std::string("hello"));
    Optional<std::string> opt2(std::move(opt1));
    EXPECT_TRUE(opt2.some());
    EXPECT_EQ(*opt2, "hello");
}

// Test move construction from empty optional
TEST(OptionalTest_406, MoveConstructionFromEmpty_406) {
    Optional<int> opt1;
    Optional<int> opt2(std::move(opt1));
    EXPECT_TRUE(opt2.none());
}

// Test copy assignment from non-empty to empty
TEST(OptionalTest_406, CopyAssignNonEmptyToEmpty_406) {
    Optional<int> opt1(42);
    Optional<int> opt2;
    opt2 = opt1;
    EXPECT_TRUE(opt2.some());
    EXPECT_EQ(*opt2, 42);
}

// Test copy assignment from empty to non-empty
TEST(OptionalTest_406, CopyAssignEmptyToNonEmpty_406) {
    Optional<int> opt1;
    Optional<int> opt2(42);
    opt2 = opt1;
    EXPECT_TRUE(opt2.none());
}

// Test copy assignment from non-empty to non-empty
TEST(OptionalTest_406, CopyAssignNonEmptyToNonEmpty_406) {
    Optional<int> opt1(100);
    Optional<int> opt2(42);
    opt2 = opt1;
    EXPECT_TRUE(opt2.some());
    EXPECT_EQ(*opt2, 100);
}

// Test copy assignment from empty to empty
TEST(OptionalTest_406, CopyAssignEmptyToEmpty_406) {
    Optional<int> opt1;
    Optional<int> opt2;
    opt2 = opt1;
    EXPECT_TRUE(opt2.none());
}

// Test self-assignment
TEST(OptionalTest_406, SelfAssignment_406) {
    Optional<int> opt(42);
    opt = opt;
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, 42);
}

// Test self-assignment on empty
TEST(OptionalTest_406, SelfAssignmentEmpty_406) {
    Optional<int> opt;
    opt = opt;
    EXPECT_TRUE(opt.none());
}

// Test move assignment from non-empty to empty
TEST(OptionalTest_406, MoveAssignNonEmptyToEmpty_406) {
    Optional<std::string> opt1(std::string("hello"));
    Optional<std::string> opt2;
    opt2 = std::move(opt1);
    EXPECT_TRUE(opt2.some());
    EXPECT_EQ(*opt2, "hello");
}

// Test move assignment from empty to non-empty
TEST(OptionalTest_406, MoveAssignEmptyToNonEmpty_406) {
    Optional<std::string> opt1;
    Optional<std::string> opt2(std::string("hello"));
    opt2 = std::move(opt1);
    EXPECT_TRUE(opt2.none());
}

// Test value assignment (const lvalue)
TEST(OptionalTest_406, ValueAssignmentLValue_406) {
    Optional<int> opt;
    int val = 42;
    opt = val;
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, 42);
}

// Test value assignment (rvalue)
TEST(OptionalTest_406, ValueAssignmentRValue_406) {
    Optional<std::string> opt;
    opt = std::string("hello");
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, "hello");
}

// Test value assignment overwrites existing value
TEST(OptionalTest_406, ValueAssignmentOverwrite_406) {
    Optional<int> opt(42);
    opt = 100;
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, 100);
}

// Test reset on non-empty optional
TEST(OptionalTest_406, ResetNonEmpty_406) {
    Optional<int> opt(42);
    opt.reset();
    EXPECT_TRUE(opt.none());
    EXPECT_FALSE(opt.some());
    EXPECT_FALSE(static_cast<bool>(opt));
}

// Test reset on empty optional
TEST(OptionalTest_406, ResetEmpty_406) {
    Optional<int> opt;
    opt.reset();
    EXPECT_TRUE(opt.none());
}

// Test dereference operator
TEST(OptionalTest_406, DereferenceOperator_406) {
    Optional<int> opt(42);
    EXPECT_EQ(*opt, 42);
    *opt = 100;
    EXPECT_EQ(*opt, 100);
}

// Test arrow operator
TEST(OptionalTest_406, ArrowOperator_406) {
    Optional<std::string> opt(std::string("hello"));
    EXPECT_EQ(opt->size(), 5u);
    EXPECT_EQ(opt->c_str(), std::string("hello"));
}

// Test valueOr returns value when present
TEST(OptionalTest_406, ValueOrReturnsValueWhenPresent_406) {
    Optional<int> opt(42);
    EXPECT_EQ(opt.valueOr(0), 42);
}

// Test valueOr returns default when empty
TEST(OptionalTest_406, ValueOrReturnsDefaultWhenEmpty_406) {
    Optional<int> opt;
    EXPECT_EQ(opt.valueOr(0), 0);
    EXPECT_EQ(opt.valueOr(-1), -1);
}

// Test some() and none() consistency
TEST(OptionalTest_406, SomeAndNoneConsistency_406) {
    Optional<int> opt;
    EXPECT_NE(opt.some(), opt.none());
    
    opt = 42;
    EXPECT_NE(opt.some(), opt.none());
    EXPECT_TRUE(opt.some());
    EXPECT_FALSE(opt.none());
}

// Test bool conversion and not operator consistency
TEST(OptionalTest_406, BoolAndNotConsistency_406) {
    Optional<int> opt;
    EXPECT_EQ(static_cast<bool>(opt), !(!opt));
    
    opt = 42;
    EXPECT_EQ(static_cast<bool>(opt), !(!opt));
}

// Test with complex type (string)
TEST(OptionalTest_406, WorksWithString_406) {
    Optional<std::string> opt(std::string("test string"));
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, "test string");
    
    opt.reset();
    EXPECT_TRUE(opt.none());
    EXPECT_EQ(opt.valueOr("default"), "default");
}

// Test construction with rvalue
TEST(OptionalTest_406, ConstructWithRValue_406) {
    std::string s = "hello";
    Optional<std::string> opt(std::move(s));
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, "hello");
}

// Test chained assignments
TEST(OptionalTest_406, ChainedAssignment_406) {
    Optional<int> opt1, opt2, opt3;
    opt1 = 42;
    opt2 = opt1;
    opt3 = opt2;
    EXPECT_EQ(*opt1, 42);
    EXPECT_EQ(*opt2, 42);
    EXPECT_EQ(*opt3, 42);
}

// Test reassignment multiple times
TEST(OptionalTest_406, MultipleReassignment_406) {
    Optional<int> opt;
    for (int i = 0; i < 100; ++i) {
        opt = i;
        EXPECT_EQ(*opt, i);
    }
    opt.reset();
    EXPECT_TRUE(opt.none());
}

// Test with struct type
struct TestStruct_406 {
    int x;
    double y;
    bool operator==(const TestStruct_406& other) const {
        return x == other.x && y == other.y;
    }
};

TEST(OptionalTest_406, WorksWithStruct_406) {
    TestStruct_406 ts{10, 3.14};
    Optional<TestStruct_406> opt(ts);
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(opt->x, 10);
    EXPECT_DOUBLE_EQ(opt->y, 3.14);
}

// Test valueOr with string default
TEST(OptionalTest_406, ValueOrWithStringDefault_406) {
    Optional<std::string> opt(std::string("actual"));
    EXPECT_EQ(opt.valueOr("default"), "actual");
    
    opt.reset();
    EXPECT_EQ(opt.valueOr("default"), "default");
}

// Test copy assignment returns reference to self
TEST(OptionalTest_406, CopyAssignmentReturnsSelf_406) {
    Optional<int> opt1(10);
    Optional<int> opt2;
    Optional<int>& ref = (opt2 = opt1);
    EXPECT_EQ(&ref, &opt2);
    EXPECT_EQ(*opt2, 10);
}

// Test value assignment to already populated optional with string
TEST(OptionalTest_406, ValueAssignmentOverwriteString_406) {
    Optional<std::string> opt(std::string("first"));
    opt = std::string("second");
    EXPECT_EQ(*opt, "second");
}

// Test reset followed by value assignment
TEST(OptionalTest_406, ResetThenAssign_406) {
    Optional<int> opt(42);
    opt.reset();
    EXPECT_TRUE(opt.none());
    opt = 100;
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, 100);
}
