// File: catch_unique_ptr_operator_arrow_tests_25.cpp

#include <gtest/gtest.h>
#include <type_traits>
#include <utility>   // std::declval
#include "catch2/internal/catch_unique_ptr.hpp"

using Catch::Detail::unique_ptr;

namespace {

// Simple helper types for observable behavior via member access
struct Widget {
    int x = 0;
    void set(int v) { x = v; }
    int value() const { return x; }
};

struct Base {
    virtual ~Base() = default;
    virtual int kind() const { return 1; }
};

struct Derived : Base {
    int kind() const override { return 2; }
};

} // namespace

class CatchUniquePtrOperatorArrowTest_25 : public ::testing::Test {};

// Normal operation: member access through operator-> must work
TEST_F(CatchUniquePtrOperatorArrowTest_25, OperatorArrow_AllowsMemberAccess_25) {
    unique_ptr<Widget> p(new Widget{});
    p->set(42);
    EXPECT_EQ(p->value(), 42);
}

// Compile-time contract: operator-> is noexcept
TEST_F(CatchUniquePtrOperatorArrowTest_25, OperatorArrow_IsNoexcept_25) {
    constexpr bool is_noexcept =
        noexcept(std::declval<unique_ptr<Widget>&>().operator->());
    static_assert(is_noexcept, "operator-> must be noexcept");
    EXPECT_TRUE(is_noexcept);
}

// Boundary/State change: works after reset to a valid pointer
TEST_F(CatchUniquePtrOperatorArrowTest_25, OperatorArrow_WorksAfterReset_25) {
    unique_ptr<Widget> p;                // default-constructed (null)
    p.reset(new Widget{});
    p->set(7);
    EXPECT_EQ(p->value(), 7);
}

// Inheritance: storing Derived in unique_ptr<Base> still allows virtual dispatch
TEST_F(CatchUniquePtrOperatorArrowTest_25, OperatorArrow_SupportsBasePointerAccess_25) {
    unique_ptr<Base> p(new Derived{});
    EXPECT_EQ(p->kind(), 2);             // virtual dispatch proves correct pointer return
}

// Consistency: operator-> returns the same address as get()
TEST_F(CatchUniquePtrOperatorArrowTest_25, OperatorArrow_EqualsGet_25) {
    unique_ptr<Widget> p(new Widget{});
    EXPECT_EQ(p.operator->(), p.get());
}

// Debug-only boundary case: calling operator-> on null should fail (assert/termination).
// Guarded by !NDEBUG so release builds (where assert may be compiled out) don't rely on UB.
#if !defined(NDEBUG)
TEST_F(CatchUniquePtrOperatorArrowTest_25, OperatorArrow_NullPointer_TriggersDeathInDebug_25) {
    unique_ptr<Widget> p; // null
    // We call operator->() directly; in debug this should hit the internal assert.
    EXPECT_DEATH_IF_SUPPORTED((void)p.operator->(), ""); // empty regex: any death reason
}
#endif
