#include <gtest/gtest.h>
#include <string>
#include <utility>

#include "catch2/internal/catch_optional.hpp"

// ============================================================
// Tests for Catch::Optional<T>
// ============================================================

// ------- Construction Tests -------

TEST(OptionalTest_408, DefaultConstructedIsNone_408) {
    Catch::Optional<int> opt;
    EXPECT_TRUE(opt.none());
    EXPECT_FALSE(opt.some());
    EXPECT_FALSE(static_cast<bool>(opt));
    EXPECT_TRUE(!opt);
}

TEST(OptionalTest_408, ConstructFromLvalueHasValue_408) {
    int val = 42;
    Catch::Optional<int> opt(val);
    EXPECT_TRUE(opt.some());
    EXPECT_FALSE(opt.none());
    EXPECT_TRUE(static_cast<bool>(opt));
    EXPECT_FALSE(!opt);
    EXPECT_EQ(*opt, 42);
}

TEST(OptionalTest_408, ConstructFromRvalueHasValue_408) {
    Catch::Optional<int> opt(99);
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, 99);
}

TEST(OptionalTest_408, CopyConstructFromEngagedOptional_408) {
    Catch::Optional<int> original(7);
    Catch::Optional<int> copy(original);
    EXPECT_TRUE(copy.some());
    EXPECT_EQ(*copy, 7);
    // Original should be unaffected
    EXPECT_TRUE(original.some());
    EXPECT_EQ(*original, 7);
}

TEST(OptionalTest_408, CopyConstructFromDisengagedOptional_408) {
    Catch::Optional<int> original;
    Catch::Optional<int> copy(original);
    EXPECT_TRUE(copy.none());
}

TEST(OptionalTest_408, MoveConstructFromEngagedOptional_408) {
    Catch::Optional<std::string> original(std::string("hello"));
    Catch::Optional<std::string> moved(std::move(original));
    EXPECT_TRUE(moved.some());
    EXPECT_EQ(*moved, "hello");
}

TEST(OptionalTest_408, MoveConstructFromDisengagedOptional_408) {
    Catch::Optional<int> original;
    Catch::Optional<int> moved(std::move(original));
    EXPECT_TRUE(moved.none());
}

// ------- Assignment Tests -------

TEST(OptionalTest_408, AssignLvalueToDisengaged_408) {
    Catch::Optional<int> opt;
    int val = 10;
    opt = val;
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, 10);
}

TEST(OptionalTest_408, AssignRvalueToDisengaged_408) {
    Catch::Optional<int> opt;
    opt = 20;
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, 20);
}

TEST(OptionalTest_408, AssignLvalueToEngaged_408) {
    Catch::Optional<int> opt(5);
    int val = 15;
    opt = val;
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, 15);
}

TEST(OptionalTest_408, AssignRvalueToEngaged_408) {
    Catch::Optional<int> opt(5);
    opt = 25;
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, 25);
}

TEST(OptionalTest_408, CopyAssignEngagedToDisengaged_408) {
    Catch::Optional<int> src(100);
    Catch::Optional<int> dst;
    dst = src;
    EXPECT_TRUE(dst.some());
    EXPECT_EQ(*dst, 100);
    EXPECT_TRUE(src.some());
    EXPECT_EQ(*src, 100);
}

TEST(OptionalTest_408, CopyAssignDisengagedToEngaged_408) {
    Catch::Optional<int> src;
    Catch::Optional<int> dst(50);
    dst = src;
    EXPECT_TRUE(dst.none());
}

TEST(OptionalTest_408, CopyAssignEngagedToEngaged_408) {
    Catch::Optional<int> src(200);
    Catch::Optional<int> dst(300);
    dst = src;
    EXPECT_TRUE(dst.some());
    EXPECT_EQ(*dst, 200);
}

TEST(OptionalTest_408, CopyAssignDisengagedToDisengaged_408) {
    Catch::Optional<int> src;
    Catch::Optional<int> dst;
    dst = src;
    EXPECT_TRUE(dst.none());
}

TEST(OptionalTest_408, MoveAssignEngagedToDisengaged_408) {
    Catch::Optional<std::string> src(std::string("world"));
    Catch::Optional<std::string> dst;
    dst = std::move(src);
    EXPECT_TRUE(dst.some());
    EXPECT_EQ(*dst, "world");
}

TEST(OptionalTest_408, MoveAssignDisengagedToEngaged_408) {
    Catch::Optional<int> src;
    Catch::Optional<int> dst(77);
    dst = std::move(src);
    EXPECT_TRUE(dst.none());
}

// ------- reset() Tests -------

TEST(OptionalTest_408, ResetEngagedBecomeNone_408) {
    Catch::Optional<int> opt(42);
    EXPECT_TRUE(opt.some());
    opt.reset();
    EXPECT_TRUE(opt.none());
    EXPECT_FALSE(opt.some());
    EXPECT_FALSE(static_cast<bool>(opt));
}

TEST(OptionalTest_408, ResetDisengagedStaysNone_408) {
    Catch::Optional<int> opt;
    EXPECT_TRUE(opt.none());
    opt.reset();
    EXPECT_TRUE(opt.none());
}

TEST(OptionalTest_408, ResetCallsDestructor_408) {
    // Use a type whose destructor has observable side effects
    static int destructorCount = 0;
    struct Tracked {
        ~Tracked() { ++destructorCount; }
    };
    destructorCount = 0;
    {
        Catch::Optional<Tracked> opt(Tracked{});
        int countBefore = destructorCount;
        opt.reset();
        // Destructor should have been called once more
        EXPECT_GT(destructorCount, countBefore);
        EXPECT_TRUE(opt.none());
    }
}

// ------- Dereference Tests -------

TEST(OptionalTest_408, DereferenceReturnsCorrectValue_408) {
    Catch::Optional<int> opt(123);
    EXPECT_EQ(*opt, 123);
}

TEST(OptionalTest_408, DereferenceAllowsMutation_408) {
    Catch::Optional<int> opt(10);
    *opt = 20;
    EXPECT_EQ(*opt, 20);
}

TEST(OptionalTest_408, ArrowOperatorAccessesMember_408) {
    Catch::Optional<std::string> opt(std::string("test"));
    EXPECT_EQ(opt->size(), 4u);
}

TEST(OptionalTest_408, ArrowOperatorAllowsMutation_408) {
    Catch::Optional<std::string> opt(std::string("abc"));
    opt->append("def");
    EXPECT_EQ(*opt, "abcdef");
}

// ------- valueOr() Tests -------

TEST(OptionalTest_408, ValueOrReturnsValueWhenEngaged_408) {
    Catch::Optional<int> opt(42);
    EXPECT_EQ(opt.valueOr(0), 42);
}

TEST(OptionalTest_408, ValueOrReturnsDefaultWhenDisengaged_408) {
    Catch::Optional<int> opt;
    EXPECT_EQ(opt.valueOr(99), 99);
}

TEST(OptionalTest_408, ValueOrWithStringEngaged_408) {
    Catch::Optional<std::string> opt(std::string("present"));
    EXPECT_EQ(opt.valueOr("absent"), "present");
}

TEST(OptionalTest_408, ValueOrWithStringDisengaged_408) {
    Catch::Optional<std::string> opt;
    EXPECT_EQ(opt.valueOr("absent"), "absent");
}

// ------- some() / none() / operator bool / operator! Tests -------

TEST(OptionalTest_408, SomeAndNoneAreOpposites_408) {
    Catch::Optional<int> engaged(1);
    EXPECT_TRUE(engaged.some());
    EXPECT_FALSE(engaged.none());

    Catch::Optional<int> disengaged;
    EXPECT_FALSE(disengaged.some());
    EXPECT_TRUE(disengaged.none());
}

TEST(OptionalTest_408, BoolConversionMatchesSome_408) {
    Catch::Optional<int> engaged(1);
    EXPECT_TRUE(static_cast<bool>(engaged));
    EXPECT_FALSE(!engaged);

    Catch::Optional<int> disengaged;
    EXPECT_FALSE(static_cast<bool>(disengaged));
    EXPECT_TRUE(!disengaged);
}

// ------- Re-engagement after reset -------

TEST(OptionalTest_408, CanReengageAfterReset_408) {
    Catch::Optional<int> opt(1);
    opt.reset();
    EXPECT_TRUE(opt.none());
    opt = 2;
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, 2);
}

// ------- Self-assignment -------

TEST(OptionalTest_408, SelfCopyAssignEngaged_408) {
    Catch::Optional<int> opt(42);
    const auto& ref = opt;
    opt = ref;
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(*opt, 42);
}

TEST(OptionalTest_408, SelfMoveAssignEngaged_408) {
    Catch::Optional<int> opt(42);
    opt = std::move(opt);
    // After self-move, the object should still be in a valid state.
    // We just verify it doesn't crash; value may or may not be preserved.
    // But typically it should remain engaged.
    (void)opt.some();
}

// ------- Complex type tests -------

TEST(OptionalTest_408, WorksWithComplexType_408) {
    struct Point {
        int x, y;
        bool operator==(const Point& o) const { return x == o.x && y == o.y; }
    };
    
    Point p{3, 4};
    Catch::Optional<Point> opt(p);
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(opt->x, 3);
    EXPECT_EQ(opt->y, 4);
    
    opt.reset();
    EXPECT_TRUE(opt.none());
    
    opt = Point{5, 6};
    EXPECT_EQ(opt->x, 5);
    EXPECT_EQ(opt->y, 6);
}

TEST(OptionalTest_408, MultipleResetsAreSafe_408) {
    Catch::Optional<int> opt(10);
    opt.reset();
    opt.reset();
    opt.reset();
    EXPECT_TRUE(opt.none());
}

// ------- Const correctness -------

TEST(OptionalTest_408, ConstOptionalValueOr_408) {
    const Catch::Optional<int> opt(55);
    EXPECT_EQ(opt.valueOr(0), 55);
    EXPECT_TRUE(opt.some());
    EXPECT_FALSE(opt.none());
    EXPECT_TRUE(static_cast<bool>(opt));
    EXPECT_FALSE(!opt);
}

TEST(OptionalTest_408, ConstDisengagedOptional_408) {
    const Catch::Optional<int> opt;
    EXPECT_EQ(opt.valueOr(77), 77);
    EXPECT_FALSE(opt.some());
    EXPECT_TRUE(opt.none());
}
