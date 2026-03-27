// File: singleton_tests_280.cpp
#include <gtest/gtest.h>
#include <type_traits>
#include <climits>

// Include the header under test
// Adjust the include path as needed for your project layout.
#include "catch2/internal/catch_singletons.hpp"

// ---------- Minimal types to serve as InterfaceT / MutableInterfaceT ----------
// We define a tiny observable interface that exposes read/write operations.
// This lets us observe behavior purely via the public API (no internal access).

struct Counter {
    int v = 0;
    int value() const { return v; }     // observable read
    void set(int x) { v = x; }          // observable write
};

// Distinct tag types to demonstrate separate instances for distinct template instantiations.
struct TagA {};
struct TagB {};

// Concrete singleton aliases for tests.
// First template arg is the "implementation tag" type (we don't rely on its internals).
// InterfaceT and MutableInterfaceT are both Counter here.
using SingletonA = Catch::Singleton<TagA, Counter, Counter>;
using SingletonB = Catch::Singleton<TagB, Counter, Counter>;

// ----------------------------- Tests -----------------------------

TEST(SingletonTest_280, GetReturnsConstReference_TypeContract_280) {
    // Verify at compile-time that get() returns a const reference to InterfaceT.
    using GetType = decltype(SingletonA::get());
    static_assert(std::is_reference<GetType>::value, "get() must return a reference");
    static_assert(std::is_const<typename std::remove_reference<GetType>::type>::value,
                  "get() must return a const reference");
    SUCCEED(); // If it compiles, the type contract is satisfied.
}

TEST(SingletonTest_280, GetMutableReturnsMutableReference_TypeContract_280) {
    // Verify at compile-time that getMutable() returns a non-const reference to MutableInterfaceT.
    using GetMutType = decltype(SingletonA::getMutable());
    static_assert(std::is_reference<GetMutType>::value, "getMutable() must return a reference");
    static_assert(!std::is_const<typename std::remove_reference<GetMutType>::type>::value,
                  "getMutable() must return a mutable reference");
    SUCCEED(); // If it compiles, the type contract is satisfied.
}

TEST(SingletonTest_280, SameInstanceAcrossCalls_280) {
    auto const& a1 = SingletonA::get();
    auto const& a2 = SingletonA::get();
    auto& m1 = SingletonA::getMutable();
    auto& m2 = SingletonA::getMutable();

    // Address identity: all references should point to the same underlying object.
    EXPECT_EQ(&a1, &a2);
    EXPECT_EQ(&m1, &m2);

    // const and mutable views should refer to the same instance
    EXPECT_EQ(&a1, &m1);
}

TEST(SingletonTest_280, MutationViaGetMutableIsObservableViaGet_280) {
    // Arrange
    auto& mut = SingletonA::getMutable();
    mut.set(42);

    // Act / Assert (observe via const API)
    auto const& view = SingletonA::get();
    EXPECT_EQ(view.value(), 42);
}

TEST(SingletonTest_280, MultipleMutationsPersist_280) {
    SingletonA::getMutable().set(7);
    EXPECT_EQ(SingletonA::get().value(), 7);

    SingletonA::getMutable().set(13);
    EXPECT_EQ(SingletonA::get().value(), 13);
}

TEST(SingletonTest_280, BoundaryValues_IntMinMax_280) {
    SingletonA::getMutable().set(INT_MAX);
    EXPECT_EQ(SingletonA::get().value(), INT_MAX);

    SingletonA::getMutable().set(INT_MIN);
    EXPECT_EQ(SingletonA::get().value(), INT_MIN);
}

TEST(SingletonTest_280, DistinctInstancesForDifferentTemplateTags_280) {
    // Set different values in A and B singletons, then verify they don't interfere.
    SingletonA::getMutable().set(111);
    SingletonB::getMutable().set(222);

    auto const& a = SingletonA::get();
    auto const& b = SingletonB::get();

    // Values remain isolated per template instantiation.
    EXPECT_EQ(a.value(), 111);
    EXPECT_EQ(b.value(), 222);

    // And the underlying instances must be different objects.
    EXPECT_NE(&a, &b);
}

TEST(SingletonTest_280, ConstViewProhibitsMutation_280) {
    // This test ensures we can read via const view but cannot mutate through it.
    // (We can't "test" compilation failure, but we can confirm reading works.)
    SingletonA::getMutable().set(5);
    auto const& a = SingletonA::get();
    EXPECT_EQ(a.value(), 5);

    // NOTE: Attempting something like a.set(10) would fail to compile, which is desired.
}

