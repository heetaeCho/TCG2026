#include "catch2/internal/catch_optional.hpp"
#include <gtest/gtest.h>
#include <string>
#include <utility>

// Test fixture for Optional tests
class OptionalTest_407 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== Construction Tests ====================

TEST_F(OptionalTest_407, DefaultConstructor_CreatesEmptyOptional_407) {
    Catch::Optional<int> opt;
    EXPECT_TRUE(opt.none());
    EXPECT_FALSE(opt.some());
    EXPECT_FALSE(static_cast<bool>(opt));
    EXPECT_TRUE(!opt);
}

TEST_F(OptionalTest_407, ConstLValueConstructor_CreatesNonEmptyOptional_407) {
    const int value = 42;
    Catch::Optional<int> opt(value);
    EXPECT_TRUE(opt.some());
    EXPECT_FALSE(opt.none());
    EXPECT_TRUE(static_cast<bool>(opt));
    EXPECT_FALSE(!opt);
    EXPECT_EQ(*opt, 42);
}

TEST_F(OptionalTest_407, RValueConstructor_CreatesNonEmptyOptional_407) {
    Catch::Optional<int> opt(42);
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, 42);
}

TEST_F(OptionalTest_407, RValueConstructor_WithString_407) {
    std::string s = "hello";
    Catch::Optional<std::string> opt(std::move(s));
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, "hello");
}

TEST_F(OptionalTest_407, CopyConstructor_FromNonEmpty_407) {
    Catch::Optional<int> original(42);
    Catch::Optional<int> copy(original);
    EXPECT_TRUE(copy.some());
    EXPECT_EQ(*copy, 42);
    // Original should remain unchanged
    EXPECT_TRUE(original.some());
    EXPECT_EQ(*original, 42);
}

TEST_F(OptionalTest_407, CopyConstructor_FromEmpty_407) {
    Catch::Optional<int> original;
    Catch::Optional<int> copy(original);
    EXPECT_TRUE(copy.none());
}

TEST_F(OptionalTest_407, MoveConstructor_FromNonEmpty_407) {
    Catch::Optional<std::string> original("hello");
    Catch::Optional<std::string> moved(std::move(original));
    EXPECT_TRUE(moved.some());
    EXPECT_EQ(*moved, "hello");
}

TEST_F(OptionalTest_407, MoveConstructor_FromEmpty_407) {
    Catch::Optional<int> original;
    Catch::Optional<int> moved(std::move(original));
    EXPECT_TRUE(moved.none());
}

// ==================== Assignment Tests ====================

TEST_F(OptionalTest_407, CopyAssignment_FromValue_407) {
    Catch::Optional<int> opt;
    const int value = 99;
    opt = value;
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, 99);
}

TEST_F(OptionalTest_407, MoveAssignment_FromValue_407) {
    Catch::Optional<std::string> opt;
    std::string s = "world";
    opt = std::move(s);
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, "world");
}

TEST_F(OptionalTest_407, CopyAssignment_FromNonEmptyOptional_407) {
    Catch::Optional<int> opt1(10);
    Catch::Optional<int> opt2(20);
    opt1 = opt2;
    EXPECT_TRUE(opt1.some());
    EXPECT_EQ(*opt1, 20);
    EXPECT_TRUE(opt2.some());
    EXPECT_EQ(*opt2, 20);
}

TEST_F(OptionalTest_407, CopyAssignment_FromEmptyOptional_407) {
    Catch::Optional<int> opt1(10);
    Catch::Optional<int> opt2;
    opt1 = opt2;
    EXPECT_TRUE(opt1.none());
}

TEST_F(OptionalTest_407, MoveAssignment_FromNonEmptyOptional_407) {
    Catch::Optional<std::string> opt1("first");
    Catch::Optional<std::string> opt2("second");
    opt1 = std::move(opt2);
    EXPECT_TRUE(opt1.some());
    EXPECT_EQ(*opt1, "second");
}

TEST_F(OptionalTest_407, MoveAssignment_FromEmptyOptional_407) {
    Catch::Optional<int> opt1(42);
    Catch::Optional<int> opt2;
    opt1 = std::move(opt2);
    EXPECT_TRUE(opt1.none());
}

TEST_F(OptionalTest_407, MoveAssignment_SelfAssignment_407) {
    Catch::Optional<int> opt(42);
    opt = std::move(opt);
    // After self-assignment, value should still be accessible or at least not crash
    // The implementation explicitly checks for self-assignment
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, 42);
}

TEST_F(OptionalTest_407, CopyAssignment_OverwriteExistingValue_407) {
    Catch::Optional<int> opt(10);
    const int newValue = 20;
    opt = newValue;
    EXPECT_EQ(*opt, 20);
}

TEST_F(OptionalTest_407, Assignment_EmptyToEmpty_407) {
    Catch::Optional<int> opt1;
    Catch::Optional<int> opt2;
    opt1 = opt2;
    EXPECT_TRUE(opt1.none());
}

// ==================== Reset Tests ====================

TEST_F(OptionalTest_407, Reset_NonEmptyBecomeEmpty_407) {
    Catch::Optional<int> opt(42);
    EXPECT_TRUE(opt.some());
    opt.reset();
    EXPECT_TRUE(opt.none());
    EXPECT_FALSE(static_cast<bool>(opt));
}

TEST_F(OptionalTest_407, Reset_AlreadyEmpty_407) {
    Catch::Optional<int> opt;
    opt.reset();
    EXPECT_TRUE(opt.none());
}

TEST_F(OptionalTest_407, Reset_ThenReassign_407) {
    Catch::Optional<int> opt(42);
    opt.reset();
    EXPECT_TRUE(opt.none());
    opt = 99;
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, 99);
}

// ==================== Dereference/Access Tests ====================

TEST_F(OptionalTest_407, Dereference_ReturnsValue_407) {
    Catch::Optional<int> opt(42);
    EXPECT_EQ(*opt, 42);
}

TEST_F(OptionalTest_407, Dereference_Mutable_407) {
    Catch::Optional<int> opt(42);
    *opt = 100;
    EXPECT_EQ(*opt, 100);
}

TEST_F(OptionalTest_407, ArrowOperator_AccessesMember_407) {
    Catch::Optional<std::string> opt("hello");
    EXPECT_EQ(opt->size(), 5u);
}

TEST_F(OptionalTest_407, ArrowOperator_MutableAccess_407) {
    Catch::Optional<std::string> opt("hello");
    opt->append(" world");
    EXPECT_EQ(*opt, "hello world");
}

// ==================== valueOr Tests ====================

TEST_F(OptionalTest_407, ValueOr_ReturnsValueWhenPresent_407) {
    Catch::Optional<int> opt(42);
    EXPECT_EQ(opt.valueOr(0), 42);
}

TEST_F(OptionalTest_407, ValueOr_ReturnsDefaultWhenEmpty_407) {
    Catch::Optional<int> opt;
    EXPECT_EQ(opt.valueOr(99), 99);
}

TEST_F(OptionalTest_407, ValueOr_WithString_Present_407) {
    Catch::Optional<std::string> opt("hello");
    EXPECT_EQ(opt.valueOr("default"), "hello");
}

TEST_F(OptionalTest_407, ValueOr_WithString_Empty_407) {
    Catch::Optional<std::string> opt;
    EXPECT_EQ(opt.valueOr("default"), "default");
}

// ==================== Boolean State Tests ====================

TEST_F(OptionalTest_407, Some_TrueWhenPresent_407) {
    Catch::Optional<int> opt(1);
    EXPECT_TRUE(opt.some());
}

TEST_F(OptionalTest_407, Some_FalseWhenEmpty_407) {
    Catch::Optional<int> opt;
    EXPECT_FALSE(opt.some());
}

TEST_F(OptionalTest_407, None_TrueWhenEmpty_407) {
    Catch::Optional<int> opt;
    EXPECT_TRUE(opt.none());
}

TEST_F(OptionalTest_407, None_FalseWhenPresent_407) {
    Catch::Optional<int> opt(1);
    EXPECT_FALSE(opt.none());
}

TEST_F(OptionalTest_407, BoolConversion_TrueWhenPresent_407) {
    Catch::Optional<int> opt(1);
    EXPECT_TRUE(static_cast<bool>(opt));
}

TEST_F(OptionalTest_407, BoolConversion_FalseWhenEmpty_407) {
    Catch::Optional<int> opt;
    EXPECT_FALSE(static_cast<bool>(opt));
}

TEST_F(OptionalTest_407, NotOperator_FalseWhenPresent_407) {
    Catch::Optional<int> opt(1);
    EXPECT_FALSE(!opt);
}

TEST_F(OptionalTest_407, NotOperator_TrueWhenEmpty_407) {
    Catch::Optional<int> opt;
    EXPECT_TRUE(!opt);
}

// ==================== Complex Type Tests ====================

struct TrackingType {
    static int constructCount;
    static int destructCount;
    static void resetCounts() { constructCount = 0; destructCount = 0; }

    int value;
    TrackingType(int v) : value(v) { ++constructCount; }
    TrackingType(const TrackingType& o) : value(o.value) { ++constructCount; }
    TrackingType(TrackingType&& o) : value(o.value) { o.value = -1; ++constructCount; }
    ~TrackingType() { ++destructCount; }
    TrackingType& operator=(const TrackingType&) = default;
    TrackingType& operator=(TrackingType&&) = default;
};

int TrackingType::constructCount = 0;
int TrackingType::destructCount = 0;

TEST_F(OptionalTest_407, Destructor_CleansUpContainedObject_407) {
    TrackingType::resetCounts();
    {
        Catch::Optional<TrackingType> opt(TrackingType(42));
    }
    // The contained object should be destroyed when optional goes out of scope
    EXPECT_EQ(TrackingType::constructCount, TrackingType::destructCount);
}

TEST_F(OptionalTest_407, Reset_DestroysContainedObject_407) {
    TrackingType::resetCounts();
    Catch::Optional<TrackingType> opt(TrackingType(42));
    int countBeforeReset = TrackingType::destructCount;
    opt.reset();
    // At least one more destruction should have occurred
    EXPECT_GT(TrackingType::destructCount, countBeforeReset);
    EXPECT_TRUE(opt.none());
}

// ==================== Chained Operations Tests ====================

TEST_F(OptionalTest_407, ChainedAssignment_407) {
    Catch::Optional<int> opt;
    opt = 10;
    EXPECT_EQ(*opt, 10);
    opt = 20;
    EXPECT_EQ(*opt, 20);
    opt.reset();
    EXPECT_TRUE(opt.none());
    opt = 30;
    EXPECT_EQ(*opt, 30);
}

TEST_F(OptionalTest_407, ValueWithZero_IsStillPresent_407) {
    Catch::Optional<int> opt(0);
    EXPECT_TRUE(opt.some());
    EXPECT_FALSE(opt.none());
    EXPECT_EQ(*opt, 0);
}

TEST_F(OptionalTest_407, ValueWithEmptyString_IsStillPresent_407) {
    Catch::Optional<std::string> opt(std::string(""));
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, "");
}

TEST_F(OptionalTest_407, ValueWithFalse_IsStillPresent_407) {
    Catch::Optional<bool> opt(false);
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, false);
}

TEST_F(OptionalTest_407, MoveAssignment_ReturnsReference_407) {
    Catch::Optional<int> opt1(10);
    Catch::Optional<int> opt2(20);
    Catch::Optional<int>& ref = (opt1 = std::move(opt2));
    EXPECT_EQ(&ref, &opt1);
    EXPECT_EQ(*opt1, 20);
}

TEST_F(OptionalTest_407, CopyAssignment_ReturnsReference_407) {
    Catch::Optional<int> opt1(10);
    Catch::Optional<int> opt2(20);
    Catch::Optional<int>& ref = (opt1 = opt2);
    EXPECT_EQ(&ref, &opt1);
    EXPECT_EQ(*opt1, 20);
}

TEST_F(OptionalTest_407, MultipleResets_407) {
    Catch::Optional<int> opt(42);
    opt.reset();
    opt.reset();
    opt.reset();
    EXPECT_TRUE(opt.none());
}
