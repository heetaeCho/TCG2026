// Optional_move_assign_407_tests.cpp
#include <gtest/gtest.h>
#include "catch2/internal/catch_optional.hpp"  // path as provided

// A simple movable/copyable value type to observe semantics without peeking inside Optional.
struct Movable {
    int value;
    static int move_ctor_count;
    static int copy_ctor_count;

    explicit Movable(int v = 0) : value(v) {}

    Movable(Movable&& other) noexcept : value(other.value) {
        ++move_ctor_count;
        // Mark source as moved-from (observable only through the value type, not Optional internals)
        other.value = -999;
    }
    Movable(const Movable& other) : value(other.value) {
        ++copy_ctor_count;
    }

    Movable& operator=(Movable&&) = delete;
    Movable& operator=(const Movable&) = delete;

    static void ResetCounters() {
        move_ctor_count = 0;
        copy_ctor_count = 0;
    }
};
int Movable::move_ctor_count = 0;
int Movable::copy_ctor_count = 0;

class OptionalMoveAssignTest_407 : public ::testing::Test {
protected:
    void SetUp() override {
        Movable::ResetCounters();
    }
};

// --- Tests ---

// Normal operation: move-assign from engaged -> empty destination
TEST_F(OptionalMoveAssignTest_407, MoveAssign_EngagedToEmpty_407) {
    Catch::Optional<Movable> src(Movable{7});
    Catch::Optional<Movable> dst; // empty

    // Capture observable source value before move (no assumptions about post-move state)
    int before = (*src).value;

    auto& ret = (dst = std::move(src));
    EXPECT_EQ(&ret, &dst) << "operator= should return *this by reference";

    EXPECT_TRUE(static_cast<bool>(dst));
    EXPECT_EQ((*dst).value, before);

    EXPECT_EQ(Movable::move_ctor_count, 1);
    EXPECT_EQ(Movable::copy_ctor_count, 0);
}

// Normal operation: move-assign from engaged -> engaged destination (replaces value)
TEST_F(OptionalMoveAssignTest_407, MoveAssign_EngagedToEngaged_407) {
    Catch::Optional<Movable> src(Movable{42});
    Catch::Optional<Movable> dst(Movable{1}); // already engaged

    int before = (*src).value;

    dst = std::move(src);

    EXPECT_TRUE(static_cast<bool>(dst));
    EXPECT_EQ((*dst).value, before);

    // Should construct via move (not copy)
    EXPECT_EQ(Movable::move_ctor_count, 1);
    EXPECT_EQ(Movable::copy_ctor_count, 0);
}

// Boundary: move-assign from empty -> engaged destination (destination becomes empty)
TEST_F(OptionalMoveAssignTest_407, MoveAssign_EmptyToEngaged_407) {
    Catch::Optional<Movable> src;                // empty
    Catch::Optional<Movable> dst(Movable{5});    // engaged

    dst = std::move(src);

    EXPECT_FALSE(static_cast<bool>(dst)) << "Assigning from empty should make destination empty";
    EXPECT_EQ(Movable::move_ctor_count, 0);
    EXPECT_EQ(Movable::copy_ctor_count, 0);
}

// Boundary: self move-assignment (should be a no-op; value preserved)
TEST_F(OptionalMoveAssignTest_407, MoveAssign_Self_407) {
    Catch::Optional<Movable> opt(Movable{33});

    // Self move-assign
    auto& ret = (opt = std::move(opt));

    EXPECT_EQ(&ret, &opt);
    EXPECT_TRUE(static_cast<bool>(opt));
    EXPECT_EQ((*opt).value, 33) << "Self move-assign should leave value unchanged";

    // No move/copy should have been invoked
    EXPECT_EQ(Movable::move_ctor_count, 0);
    EXPECT_EQ(Movable::copy_ctor_count, 0);
}

// Exceptional/edge behavior via observable effects: chaining and stability
TEST_F(OptionalMoveAssignTest_407, MoveAssign_ChainingAndStability_407) {
    Catch::Optional<Movable> a(Movable{1});
    Catch::Optional<Movable> b(Movable{2});
    Catch::Optional<Movable> c;

    // Chain: (c = std::move(b)) = std::move(a) — validate left-associativity & return ref
    ((c = std::move(b)) = std::move(a));

    EXPECT_TRUE(static_cast<bool>(c));
    EXPECT_EQ((*c).value, 1); // last assignment comes from 'a'

    // Two move constructions should have occurred in total across both assignments
    EXPECT_EQ(Movable::move_ctor_count, 2);
    EXPECT_EQ(Movable::copy_ctor_count, 0);
}
