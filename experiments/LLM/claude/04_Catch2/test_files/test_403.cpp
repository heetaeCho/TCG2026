#include "catch2/internal/catch_optional.hpp"
#include <gtest/gtest.h>
#include <string>
#include <utility>

// Test fixture for Optional tests
class OptionalTest_403 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== Construction Tests ====================

TEST_F(OptionalTest_403, DefaultConstructedIsNone_403) {
    Catch::Optional<int> opt;
    EXPECT_TRUE(opt.none());
    EXPECT_FALSE(opt.some());
    EXPECT_FALSE(static_cast<bool>(opt));
    EXPECT_TRUE(!opt);
}

TEST_F(OptionalTest_403, ConstructWithValue_403) {
    Catch::Optional<int> opt(42);
    EXPECT_TRUE(opt.some());
    EXPECT_FALSE(opt.none());
    EXPECT_TRUE(static_cast<bool>(opt));
    EXPECT_FALSE(!opt);
    EXPECT_EQ(*opt, 42);
}

TEST_F(OptionalTest_403, ConstructWithConstReference_403) {
    const int value = 100;
    Catch::Optional<int> opt(value);
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, 100);
}

TEST_F(OptionalTest_403, ConstructWithMoveValue_403) {
    std::string str = "hello world";
    Catch::Optional<std::string> opt(std::move(str));
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, "hello world");
}

TEST_F(OptionalTest_403, CopyConstructFromNone_403) {
    Catch::Optional<int> original;
    Catch::Optional<int> copy(original);
    EXPECT_TRUE(copy.none());
    EXPECT_FALSE(copy.some());
}

TEST_F(OptionalTest_403, CopyConstructFromSome_403) {
    Catch::Optional<int> original(77);
    Catch::Optional<int> copy(original);
    EXPECT_TRUE(copy.some());
    EXPECT_EQ(*copy, 77);
    // Original should still be valid
    EXPECT_TRUE(original.some());
    EXPECT_EQ(*original, 77);
}

TEST_F(OptionalTest_403, MoveConstructFromNone_403) {
    Catch::Optional<int> original;
    Catch::Optional<int> moved(std::move(original));
    EXPECT_TRUE(moved.none());
}

TEST_F(OptionalTest_403, MoveConstructFromSome_403) {
    Catch::Optional<std::string> original(std::string("test"));
    Catch::Optional<std::string> moved(std::move(original));
    EXPECT_TRUE(moved.some());
    EXPECT_EQ(*moved, "test");
}

// ==================== Assignment Tests ====================

TEST_F(OptionalTest_403, AssignValueToNone_403) {
    Catch::Optional<int> opt;
    opt = 55;
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, 55);
}

TEST_F(OptionalTest_403, AssignValueToSome_403) {
    Catch::Optional<int> opt(10);
    opt = 20;
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, 20);
}

TEST_F(OptionalTest_403, AssignConstRefValue_403) {
    Catch::Optional<int> opt;
    const int val = 99;
    opt = val;
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, 99);
}

TEST_F(OptionalTest_403, MoveAssignValue_403) {
    Catch::Optional<std::string> opt;
    std::string str = "moved";
    opt = std::move(str);
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, "moved");
}

TEST_F(OptionalTest_403, CopyAssignFromNoneToNone_403) {
    Catch::Optional<int> a;
    Catch::Optional<int> b;
    b = a;
    EXPECT_TRUE(b.none());
}

TEST_F(OptionalTest_403, CopyAssignFromSomeToNone_403) {
    Catch::Optional<int> a(42);
    Catch::Optional<int> b;
    b = a;
    EXPECT_TRUE(b.some());
    EXPECT_EQ(*b, 42);
}

TEST_F(OptionalTest_403, CopyAssignFromNoneToSome_403) {
    Catch::Optional<int> a;
    Catch::Optional<int> b(42);
    b = a;
    EXPECT_TRUE(b.none());
}

TEST_F(OptionalTest_403, CopyAssignFromSomeToSome_403) {
    Catch::Optional<int> a(10);
    Catch::Optional<int> b(20);
    b = a;
    EXPECT_TRUE(b.some());
    EXPECT_EQ(*b, 10);
}

TEST_F(OptionalTest_403, MoveAssignFromNoneToNone_403) {
    Catch::Optional<int> a;
    Catch::Optional<int> b;
    b = std::move(a);
    EXPECT_TRUE(b.none());
}

TEST_F(OptionalTest_403, MoveAssignFromSomeToNone_403) {
    Catch::Optional<std::string> a(std::string("hello"));
    Catch::Optional<std::string> b;
    b = std::move(a);
    EXPECT_TRUE(b.some());
    EXPECT_EQ(*b, "hello");
}

TEST_F(OptionalTest_403, MoveAssignFromNoneToSome_403) {
    Catch::Optional<int> a;
    Catch::Optional<int> b(42);
    b = std::move(a);
    EXPECT_TRUE(b.none());
}

TEST_F(OptionalTest_403, MoveAssignFromSomeToSome_403) {
    Catch::Optional<std::string> a(std::string("new"));
    Catch::Optional<std::string> b(std::string("old"));
    b = std::move(a);
    EXPECT_TRUE(b.some());
    EXPECT_EQ(*b, "new");
}

// ==================== Reset Tests ====================

TEST_F(OptionalTest_403, ResetSomeBecomesNone_403) {
    Catch::Optional<int> opt(42);
    EXPECT_TRUE(opt.some());
    opt.reset();
    EXPECT_TRUE(opt.none());
    EXPECT_FALSE(opt.some());
    EXPECT_FALSE(static_cast<bool>(opt));
}

TEST_F(OptionalTest_403, ResetNoneStaysNone_403) {
    Catch::Optional<int> opt;
    opt.reset();
    EXPECT_TRUE(opt.none());
}

// ==================== Dereference Tests ====================

TEST_F(OptionalTest_403, DereferenceReturnsValue_403) {
    Catch::Optional<int> opt(123);
    EXPECT_EQ(*opt, 123);
}

TEST_F(OptionalTest_403, DereferenceModifiesValue_403) {
    Catch::Optional<int> opt(10);
    *opt = 20;
    EXPECT_EQ(*opt, 20);
}

TEST_F(OptionalTest_403, ArrowOperatorAccessesMember_403) {
    Catch::Optional<std::string> opt(std::string("hello"));
    EXPECT_EQ(opt->size(), 5u);
    EXPECT_EQ(opt->c_str()[0], 'h');
}

TEST_F(OptionalTest_403, ArrowOperatorModifiesMember_403) {
    Catch::Optional<std::string> opt(std::string("hello"));
    opt->append(" world");
    EXPECT_EQ(*opt, "hello world");
}

// ==================== valueOr Tests ====================

TEST_F(OptionalTest_403, ValueOrReturnsValueWhenSome_403) {
    Catch::Optional<int> opt(42);
    EXPECT_EQ(opt.valueOr(0), 42);
}

TEST_F(OptionalTest_403, ValueOrReturnsDefaultWhenNone_403) {
    Catch::Optional<int> opt;
    EXPECT_EQ(opt.valueOr(99), 99);
}

TEST_F(OptionalTest_403, ValueOrWithStringWhenSome_403) {
    Catch::Optional<std::string> opt(std::string("present"));
    EXPECT_EQ(opt.valueOr("default"), "present");
}

TEST_F(OptionalTest_403, ValueOrWithStringWhenNone_403) {
    Catch::Optional<std::string> opt;
    EXPECT_EQ(opt.valueOr("default"), "default");
}

// ==================== some/none/bool/operator! Tests ====================

TEST_F(OptionalTest_403, SomeReturnsTrueWhenValuePresent_403) {
    Catch::Optional<int> opt(1);
    EXPECT_TRUE(opt.some());
}

TEST_F(OptionalTest_403, SomeReturnsFalseWhenEmpty_403) {
    Catch::Optional<int> opt;
    EXPECT_FALSE(opt.some());
}

TEST_F(OptionalTest_403, NoneReturnsTrueWhenEmpty_403) {
    Catch::Optional<int> opt;
    EXPECT_TRUE(opt.none());
}

TEST_F(OptionalTest_403, NoneReturnsFalseWhenValuePresent_403) {
    Catch::Optional<int> opt(1);
    EXPECT_FALSE(opt.none());
}

TEST_F(OptionalTest_403, BoolConversionTrueWhenSome_403) {
    Catch::Optional<int> opt(1);
    EXPECT_TRUE(static_cast<bool>(opt));
}

TEST_F(OptionalTest_403, BoolConversionFalseWhenNone_403) {
    Catch::Optional<int> opt;
    EXPECT_FALSE(static_cast<bool>(opt));
}

TEST_F(OptionalTest_403, NotOperatorFalseWhenSome_403) {
    Catch::Optional<int> opt(1);
    EXPECT_FALSE(!opt);
}

TEST_F(OptionalTest_403, NotOperatorTrueWhenNone_403) {
    Catch::Optional<int> opt;
    EXPECT_TRUE(!opt);
}

// ==================== Edge Cases ====================

TEST_F(OptionalTest_403, ZeroValueIsSome_403) {
    Catch::Optional<int> opt(0);
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, 0);
}

TEST_F(OptionalTest_403, NegativeValueIsSome_403) {
    Catch::Optional<int> opt(-1);
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, -1);
}

TEST_F(OptionalTest_403, EmptyStringIsSome_403) {
    Catch::Optional<std::string> opt(std::string(""));
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, "");
}

TEST_F(OptionalTest_403, ReassignAfterReset_403) {
    Catch::Optional<int> opt(42);
    opt.reset();
    EXPECT_TRUE(opt.none());
    opt = 100;
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, 100);
}

TEST_F(OptionalTest_403, MultipleResetsAreSafe_403) {
    Catch::Optional<int> opt(42);
    opt.reset();
    opt.reset();
    opt.reset();
    EXPECT_TRUE(opt.none());
}

TEST_F(OptionalTest_403, SelfCopyAssignment_403) {
    Catch::Optional<int> opt(42);
    const auto& ref = opt;
    opt = ref;
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, 42);
}

TEST_F(OptionalTest_403, SelfMoveAssignment_403) {
    Catch::Optional<int> opt(42);
    opt = std::move(opt);
    // After self-move, the optional should still be in a valid state
    // We just check it doesn't crash; behavior may vary
}

TEST_F(OptionalTest_403, ChainedAssignment_403) {
    Catch::Optional<int> a, b, c;
    a = 1;
    b = a;
    c = b;
    EXPECT_EQ(*a, 1);
    EXPECT_EQ(*b, 1);
    EXPECT_EQ(*c, 1);
}

// ==================== Destructor / Resource Management ====================

// Test with a type that tracks construction/destruction
struct TrackableObject_403 {
    static int alive_count;
    TrackableObject_403() { ++alive_count; }
    TrackableObject_403(const TrackableObject_403&) { ++alive_count; }
    TrackableObject_403(TrackableObject_403&&) { ++alive_count; }
    ~TrackableObject_403() { --alive_count; }
    TrackableObject_403& operator=(const TrackableObject_403&) = default;
    TrackableObject_403& operator=(TrackableObject_403&&) = default;
};
int TrackableObject_403::alive_count = 0;

TEST_F(OptionalTest_403, DestructorDestroysContainedObject_403) {
    TrackableObject_403::alive_count = 0;
    {
        Catch::Optional<TrackableObject_403> opt(TrackableObject_403{});
    }
    EXPECT_EQ(TrackableObject_403::alive_count, 0);
}

TEST_F(OptionalTest_403, ResetDestroysContainedObject_403) {
    TrackableObject_403::alive_count = 0;
    {
        Catch::Optional<TrackableObject_403> opt(TrackableObject_403{});
        // At this point there should be at least 1 alive inside opt
        int countBefore = TrackableObject_403::alive_count;
        opt.reset();
        EXPECT_LT(TrackableObject_403::alive_count, countBefore);
    }
    EXPECT_EQ(TrackableObject_403::alive_count, 0);
}

TEST_F(OptionalTest_403, AssignmentOverwriteDestroysOldObject_403) {
    TrackableObject_403::alive_count = 0;
    {
        Catch::Optional<TrackableObject_403> opt(TrackableObject_403{});
        int countAfterFirst = TrackableObject_403::alive_count;
        opt = TrackableObject_403{};
        // The old object should be destroyed and a new one stored
        // Count should remain the same (one destroyed, one created)
        EXPECT_EQ(TrackableObject_403::alive_count, countAfterFirst);
    }
    EXPECT_EQ(TrackableObject_403::alive_count, 0);
}

TEST_F(OptionalTest_403, ValueOrOnConstOptional_403) {
    const Catch::Optional<int> opt(42);
    EXPECT_EQ(opt.valueOr(0), 42);
    
    const Catch::Optional<int> empty;
    EXPECT_EQ(empty.valueOr(0), 0);
}

TEST_F(OptionalTest_403, ConstructWithLargeValue_403) {
    struct LargeStruct {
        int data[100];
    };
    LargeStruct ls;
    for (int i = 0; i < 100; ++i) ls.data[i] = i;
    
    Catch::Optional<LargeStruct> opt(ls);
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(opt->data[0], 0);
    EXPECT_EQ(opt->data[99], 99);
}
