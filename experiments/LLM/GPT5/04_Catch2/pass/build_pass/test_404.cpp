// File: tests/optional_assign_const_ref_404_tests.cpp
#include <gtest/gtest.h>
#include "Catch2/src/catch2/internal/catch_optional.hpp"

namespace {

struct Widget {
    int v{0};
    static int copies;
    static int moves;

    Widget() = default;
    explicit Widget(int x) : v(x) {}

    // Copy & move tracking (observable from the test only)
    Widget(const Widget& other) : v(other.v) { ++copies; }
    Widget(Widget&& other) noexcept : v(other.v) { ++moves; }

    int get() const { return v; }

    // Reset counters between tests
    static void ResetCounters() { copies = 0; moves = 0; }
};
int Widget::copies = 0;
int Widget::moves  = 0;

} // namespace

using Catch::Optional;

class OptionalAssignConstRefTest_404 : public ::testing::Test {
protected:
    void SetUp() override { Widget::ResetCounters(); }
};

// [Normal] Assigning a value to an empty Optional engages it.
TEST_F(OptionalAssignConstRefTest_404, AssignToEmpty_MakesSome_404) {
    Optional<Widget> opt;                // default-constructed: empty
    EXPECT_TRUE(opt.none());
    EXPECT_FALSE(opt.some());
    EXPECT_FALSE(static_cast<bool>(opt));

    const Widget w{42};
    opt = w;                             // operator=(T const&)

    EXPECT_TRUE(opt.some());
    EXPECT_FALSE(opt.none());
    EXPECT_TRUE(static_cast<bool>(opt));
    EXPECT_EQ((*opt).v, 42);             // observable through operator*
    EXPECT_EQ(opt->get(), 42);           // observable through operator->
}

// [Normal] Assigning a new value replaces the observed value.
TEST_F(OptionalAssignConstRefTest_404, AssignToEngaged_ReplacesValue_404) {
    Optional<Widget> opt{Widget{10}};    // engaged
    ASSERT_TRUE(opt.some());
    EXPECT_EQ(opt->get(), 10);

    const Widget w{77};
    opt = w;                             // replace

    EXPECT_TRUE(opt.some());
    EXPECT_EQ((*opt).v, 77);
    EXPECT_EQ(opt->get(), 77);
}

// [Boundary] Assign with same-value object still results in that value and stays engaged.
TEST_F(OptionalAssignConstRefTest_404, AssignSameValue_Object_RemainsEngaged_404) {
    Optional<Widget> opt{Widget{5}};
    const Widget same{5};

    opt = same;

    EXPECT_TRUE(opt.some());
    EXPECT_EQ(opt->get(), 5);
    // valueOr should return contained value, not the default
    EXPECT_EQ(opt.valueOr(Widget{999}).v, 5);
}

// [Interaction] valueOr returns the assigned value when engaged (ignores default).
TEST_F(OptionalAssignConstRefTest_404, ValueOr_IgnoresDefaultWhenAssigned_404) {
    Optional<Widget> opt;
    const Widget w{123};
    opt = w;

    Widget def{999};
    Widget result = opt.valueOr(def);
    EXPECT_EQ(result.v, 123);
}

// [Observable semantics] operator= with const& performs a copy (not a move) of T.
TEST_F(OptionalAssignConstRefTest_404, Assign_UsesCopyNotMove_404) {
    Optional<Widget> opt;                // start empty
    const Widget w{314};

    opt = w;                             // copy from const&
    // We only assert observable effects from T's public behavior:
    // a copy must have occurred; move should not be required for const&.
    EXPECT_GE(Widget::copies, 1);
    EXPECT_EQ(Widget::moves, 0);

    // Sanity check: engaged with the right value.
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(opt->v, 314);
}

// [Chaining] operator= returns a reference, enabling chaining (observable via final state).
TEST_F(OptionalAssignConstRefTest_404, Assign_ReturnsLvalueRef_EnablesChaining_404) {
    Optional<Widget> a, b;
    const Widget w1{1};
    const Widget w2{2};

    (a = w1) = w2;   // chaining assignment should be valid if operator= returns Optional&

    EXPECT_TRUE(a.some());
    EXPECT_EQ(a->v, 2);

    // Ensure independent optional 'b' is still empty (no cross-effects)
    EXPECT_TRUE(b.none());
}

