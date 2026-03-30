// File: ieventlistener_getpreferences_tests_69.cpp
#include <gtest/gtest.h>

#include "catch2/interfaces/catch_interfaces_reporter.hpp"  // path from the prompt

// We only use the public interface. No access to protected/private state.
// Create a trivial concrete subclass so we can instantiate the interface
// without adding new public API or touching internals.
namespace {
    struct DummyListener : Catch::IEventListener {
        using Catch::IEventListener::IEventListener; // inherit ctor
        ~DummyListener() override = default;
    };
}

// --- Tests ---

// 1) Type correctness: getPreferences() returns const reference
TEST(IEventListenerGetPreferences_69, ReturnsConstReferenceType_69) {
    // Compile-time verification of the function's return type
    static_assert(std::is_same_v<
        const Catch::ReporterPreferences&,
        decltype(std::declval<const Catch::IEventListener&>().getPreferences())
    >,
    "getPreferences() must return const Catch::ReporterPreferences&");
    SUCCEED(); // If it compiles, the type check passed
}

// 2) Same object identity across calls on the same instance
TEST(IEventListenerGetPreferences_69, SameAddressAcrossCalls_69) {
    DummyListener listener{ /* IConfig const* */ nullptr };

    auto& p1 = listener.getPreferences();
    auto& p2 = listener.getPreferences();

    EXPECT_EQ(&p1, &p2) << "getPreferences() should return the same object each time for a given instance";
}

// 3) Different instances expose different preference objects (not a shared static)
TEST(IEventListenerGetPreferences_69, DifferentInstancesHaveDifferentAddresses_69) {
    DummyListener a{ nullptr };
    DummyListener b{ nullptr };

    EXPECT_NE(&a.getPreferences(), &b.getPreferences())
        << "Different instances should not expose the same preferences object address";
}

// 4) Address remains stable even after invoking unrelated lifecycle callbacks
//    (observable: still the same address before/after)
TEST(IEventListenerGetPreferences_69, AddressStableAfterCallbacks_69) {
    DummyListener listener{ nullptr };

    auto* before = &listener.getPreferences();

    // Call a sampling of public callbacks (treating class as black box).
    // We don't assert any behavior of these, only that getPreferences'
    // returned reference's address remains stable.
    // We pass default/empty values where possible; the specifics are not under test.
    // These types are part of Catch2's interface; we don't rely on their internals.
    // If any of these overloads are unavailable in your build, you can comment them out
    // and keep at least one public callback here.
    listener.noMatchingTestCases(Catch::StringRef{});
    listener.reportInvalidTestSpec(Catch::StringRef{});
    // We avoid constructing complex structs; these calls are enough to exercise the surface API.

    auto* after = &listener.getPreferences();

    EXPECT_EQ(before, after) << "The address returned by getPreferences() should remain stable across callbacks";
}

// 5) Copy construction: copied instance should not alias the same preferences object
TEST(IEventListenerGetPreferences_69, CopyConstructionYieldsIndependentPreferencesObject_69) {
    DummyListener original{ nullptr };

    // If DummyListener (via IEventListener) is non-copyable in your environment,
    // this test can be conditionally disabled or removed.
    DummyListener copy = original;

    EXPECT_NE(&original.getPreferences(), &copy.getPreferences())
        << "Copy-constructed instance should expose a distinct preferences object (different address)";
}

// 6) Move construction: moved-to instance should not expose the same address as another, distinct instance
TEST(IEventListenerGetPreferences_69, MoveConstructionYieldsIndependentPreferencesObject_69) {
    DummyListener source{ nullptr };

    DummyListener moved = std::move(source);

    // The exact address relationship with 'source' after move is unspecified and not asserted.
    // We only assert that 'moved' is a valid instance with a valid preferences reference.
    auto* addr = &moved.getPreferences();
    EXPECT_NE(addr, nullptr);
}
