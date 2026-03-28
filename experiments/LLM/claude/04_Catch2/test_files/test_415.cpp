#include "catch2/internal/catch_optional.hpp"
#include <gtest/gtest.h>
#include <string>
#include <utility>

// Test fixture for Optional tests
class OptionalTest_415 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== Default Construction ====================

TEST_F(OptionalTest_415, DefaultConstructedIsNone_415) {
    Catch::Optional<int> opt;
    EXPECT_TRUE(opt.none());
    EXPECT_FALSE(opt.some());
}

TEST_F(OptionalTest_415, DefaultConstructedBoolConversionIsFalse_415) {
    Catch::Optional<int> opt;
    EXPECT_FALSE(static_cast<bool>(opt));
}

TEST_F(OptionalTest_415, DefaultConstructedNotOperatorIsTrue_415) {
    Catch::Optional<int> opt;
    EXPECT_TRUE(!opt);
}

// ==================== Value Construction ====================

TEST_F(OptionalTest_415, ConstructWithValueIsSome_415) {
    Catch::Optional<int> opt(42);
    EXPECT_TRUE(opt.some());
    EXPECT_FALSE(opt.none());
}

TEST_F(OptionalTest_415, ConstructWithValueBoolConversionIsTrue_415) {
    Catch::Optional<int> opt(42);
    EXPECT_TRUE(static_cast<bool>(opt));
}

TEST_F(OptionalTest_415, ConstructWithValueNotOperatorIsFalse_415) {
    Catch::Optional<int> opt(42);
    EXPECT_FALSE(!opt);
}

TEST_F(OptionalTest_415, ConstructWithValueDereferenceReturnsValue_415) {
    Catch::Optional<int> opt(42);
    EXPECT_EQ(*opt, 42);
}

TEST_F(OptionalTest_415, ConstructWithStringValue_415) {
    Catch::Optional<std::string> opt(std::string("hello"));
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, "hello");
}

// ==================== Move Construction ====================

TEST_F(OptionalTest_415, MoveConstructFromValue_415) {
    std::string val = "move me";
    Catch::Optional<std::string> opt(std::move(val));
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, "move me");
}

// ==================== Copy Construction ====================

TEST_F(OptionalTest_415, CopyConstructFromSomeOptional_415) {
    Catch::Optional<int> original(99);
    Catch::Optional<int> copy(original);
    EXPECT_TRUE(copy.some());
    EXPECT_EQ(*copy, 99);
    // Original should still be valid
    EXPECT_TRUE(original.some());
    EXPECT_EQ(*original, 99);
}

TEST_F(OptionalTest_415, CopyConstructFromNoneOptional_415) {
    Catch::Optional<int> original;
    Catch::Optional<int> copy(original);
    EXPECT_TRUE(copy.none());
    EXPECT_FALSE(copy.some());
}

// ==================== Move Construction from Optional ====================

TEST_F(OptionalTest_415, MoveConstructFromSomeOptional_415) {
    Catch::Optional<std::string> original(std::string("test"));
    Catch::Optional<std::string> moved(std::move(original));
    EXPECT_TRUE(moved.some());
    EXPECT_EQ(*moved, "test");
}

TEST_F(OptionalTest_415, MoveConstructFromNoneOptional_415) {
    Catch::Optional<std::string> original;
    Catch::Optional<std::string> moved(std::move(original));
    EXPECT_TRUE(moved.none());
}

// ==================== Copy Assignment ====================

TEST_F(OptionalTest_415, CopyAssignValueToNone_415) {
    Catch::Optional<int> opt;
    int val = 77;
    opt = val;
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, 77);
}

TEST_F(OptionalTest_415, CopyAssignValueToSome_415) {
    Catch::Optional<int> opt(10);
    int val = 20;
    opt = val;
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, 20);
}

TEST_F(OptionalTest_415, CopyAssignOptionalSomeToNone_415) {
    Catch::Optional<int> opt;
    Catch::Optional<int> other(55);
    opt = other;
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, 55);
}

TEST_F(OptionalTest_415, CopyAssignOptionalNoneToSome_415) {
    Catch::Optional<int> opt(33);
    Catch::Optional<int> other;
    opt = other;
    EXPECT_TRUE(opt.none());
}

TEST_F(OptionalTest_415, CopyAssignOptionalSomeToSome_415) {
    Catch::Optional<int> opt(11);
    Catch::Optional<int> other(22);
    opt = other;
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, 22);
}

TEST_F(OptionalTest_415, CopyAssignOptionalNoneToNone_415) {
    Catch::Optional<int> opt;
    Catch::Optional<int> other;
    opt = other;
    EXPECT_TRUE(opt.none());
}

// ==================== Move Assignment ====================

TEST_F(OptionalTest_415, MoveAssignValueToNone_415) {
    Catch::Optional<std::string> opt;
    opt = std::string("moved");
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, "moved");
}

TEST_F(OptionalTest_415, MoveAssignValueToSome_415) {
    Catch::Optional<std::string> opt(std::string("old"));
    opt = std::string("new");
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, "new");
}

TEST_F(OptionalTest_415, MoveAssignOptionalSomeToNone_415) {
    Catch::Optional<std::string> opt;
    Catch::Optional<std::string> other(std::string("data"));
    opt = std::move(other);
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, "data");
}

TEST_F(OptionalTest_415, MoveAssignOptionalNoneToSome_415) {
    Catch::Optional<std::string> opt(std::string("value"));
    Catch::Optional<std::string> other;
    opt = std::move(other);
    EXPECT_TRUE(opt.none());
}

// ==================== Reset ====================

TEST_F(OptionalTest_415, ResetSomeMakesNone_415) {
    Catch::Optional<int> opt(42);
    EXPECT_TRUE(opt.some());
    opt.reset();
    EXPECT_TRUE(opt.none());
    EXPECT_FALSE(opt.some());
    EXPECT_FALSE(static_cast<bool>(opt));
}

TEST_F(OptionalTest_415, ResetNoneStaysNone_415) {
    Catch::Optional<int> opt;
    opt.reset();
    EXPECT_TRUE(opt.none());
}

// ==================== Dereference and Arrow Operators ====================

TEST_F(OptionalTest_415, DereferenceReturnsReference_415) {
    Catch::Optional<int> opt(10);
    *opt = 20;
    EXPECT_EQ(*opt, 20);
}

TEST_F(OptionalTest_415, ArrowOperatorAccessesMember_415) {
    Catch::Optional<std::string> opt(std::string("hello"));
    EXPECT_EQ(opt->size(), 5u);
}

TEST_F(OptionalTest_415, ArrowOperatorModifiesMember_415) {
    Catch::Optional<std::string> opt(std::string("hello"));
    opt->append(" world");
    EXPECT_EQ(*opt, "hello world");
}

// ==================== valueOr ====================

TEST_F(OptionalTest_415, ValueOrReturnsValueWhenSome_415) {
    Catch::Optional<int> opt(42);
    EXPECT_EQ(opt.valueOr(0), 42);
}

TEST_F(OptionalTest_415, ValueOrReturnsDefaultWhenNone_415) {
    Catch::Optional<int> opt;
    EXPECT_EQ(opt.valueOr(99), 99);
}

TEST_F(OptionalTest_415, ValueOrWithStringWhenSome_415) {
    Catch::Optional<std::string> opt(std::string("actual"));
    EXPECT_EQ(opt.valueOr("default"), "actual");
}

TEST_F(OptionalTest_415, ValueOrWithStringWhenNone_415) {
    Catch::Optional<std::string> opt;
    EXPECT_EQ(opt.valueOr("default"), "default");
}

// ==================== some() and none() ====================

TEST_F(OptionalTest_415, SomeAndNoneAreMutuallyExclusive_415) {
    Catch::Optional<int> none_opt;
    EXPECT_NE(none_opt.some(), none_opt.none());

    Catch::Optional<int> some_opt(1);
    EXPECT_NE(some_opt.some(), some_opt.none());
}

// ==================== Boundary/Edge Cases ====================

TEST_F(OptionalTest_415, OptionalWithZeroValue_415) {
    Catch::Optional<int> opt(0);
    EXPECT_TRUE(opt.some());
    EXPECT_FALSE(opt.none());
    EXPECT_EQ(*opt, 0);
}

TEST_F(OptionalTest_415, OptionalWithEmptyString_415) {
    Catch::Optional<std::string> opt(std::string(""));
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, "");
}

TEST_F(OptionalTest_415, OptionalWithNegativeValue_415) {
    Catch::Optional<int> opt(-1);
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, -1);
}

TEST_F(OptionalTest_415, OptionalWithBoolFalse_415) {
    Catch::Optional<bool> opt(false);
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, false);
}

TEST_F(OptionalTest_415, OptionalWithBoolTrue_415) {
    Catch::Optional<bool> opt(true);
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, true);
}

// ==================== Self Assignment ====================

TEST_F(OptionalTest_415, SelfCopyAssignment_415) {
    Catch::Optional<int> opt(42);
    opt = opt;
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, 42);
}

TEST_F(OptionalTest_415, SelfMoveAssignment_415) {
    Catch::Optional<int> opt(42);
    opt = std::move(opt);
    // After self-move, we just check it doesn't crash
    // Behavior may be implementation-defined
}

// ==================== Repeated Operations ====================

TEST_F(OptionalTest_415, ResetAndReassign_415) {
    Catch::Optional<int> opt(1);
    EXPECT_EQ(*opt, 1);
    opt.reset();
    EXPECT_TRUE(opt.none());
    opt = 2;
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, 2);
    opt.reset();
    EXPECT_TRUE(opt.none());
    opt = 3;
    EXPECT_EQ(*opt, 3);
}

TEST_F(OptionalTest_415, MultipleAssignments_415) {
    Catch::Optional<int> opt;
    for (int i = 0; i < 100; ++i) {
        opt = i;
        EXPECT_EQ(*opt, i);
    }
}

// ==================== Complex Type ====================

struct TrackDestruction {
    int* counter;
    TrackDestruction(int* c) : counter(c) {}
    TrackDestruction(const TrackDestruction& o) : counter(o.counter) {}
    TrackDestruction(TrackDestruction&& o) : counter(o.counter) { o.counter = nullptr; }
    ~TrackDestruction() { if (counter) ++(*counter); }
    TrackDestruction& operator=(const TrackDestruction&) = default;
    TrackDestruction& operator=(TrackDestruction&&) = default;
};

TEST_F(OptionalTest_415, DestructorCalledOnReset_415) {
    int counter = 0;
    {
        Catch::Optional<TrackDestruction> opt(TrackDestruction(&counter));
        // Construction may have caused some destructions of temporaries
        int before = counter;
        opt.reset();
        EXPECT_GT(counter, before);
        EXPECT_TRUE(opt.none());
    }
}

TEST_F(OptionalTest_415, DestructorCalledOnDestruction_415) {
    int counter = 0;
    {
        Catch::Optional<TrackDestruction> opt(TrackDestruction(&counter));
        int before = counter;
        // opt goes out of scope
        // We'll check after the block
    }
    // At least one destruction should have happened (the contained value)
    EXPECT_GT(counter, 0);
}

// ==================== Const Optional ====================

TEST_F(OptionalTest_415, ConstOptionalValueOr_415) {
    const Catch::Optional<int> opt(42);
    EXPECT_EQ(opt.valueOr(0), 42);
    EXPECT_TRUE(opt.some());
    EXPECT_FALSE(opt.none());
}

TEST_F(OptionalTest_415, ConstOptionalNoneValueOr_415) {
    const Catch::Optional<int> opt;
    EXPECT_EQ(opt.valueOr(99), 99);
    EXPECT_TRUE(opt.none());
    EXPECT_FALSE(opt.some());
}

TEST_F(OptionalTest_415, ConstOptionalBoolConversion_415) {
    const Catch::Optional<int> some_opt(1);
    const Catch::Optional<int> none_opt;
    EXPECT_TRUE(static_cast<bool>(some_opt));
    EXPECT_FALSE(static_cast<bool>(none_opt));
}

// ==================== Chain of assignments ====================

TEST_F(OptionalTest_415, AssignmentReturnsReference_415) {
    Catch::Optional<int> opt;
    Catch::Optional<int>& ref = (opt = 42);
    EXPECT_EQ(&ref, &opt);
    EXPECT_EQ(*opt, 42);
}

TEST_F(OptionalTest_415, CopyAssignmentOptionalReturnsReference_415) {
    Catch::Optional<int> opt;
    Catch::Optional<int> other(10);
    Catch::Optional<int>& ref = (opt = other);
    EXPECT_EQ(&ref, &opt);
    EXPECT_EQ(*opt, 10);
}

TEST_F(OptionalTest_415, MoveAssignmentOptionalReturnsReference_415) {
    Catch::Optional<int> opt;
    Catch::Optional<int>& ref = (opt = Catch::Optional<int>(5));
    EXPECT_EQ(&ref, &opt);
    EXPECT_EQ(*opt, 5);
}
