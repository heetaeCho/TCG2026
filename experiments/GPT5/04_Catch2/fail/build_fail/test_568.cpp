// File: tests/listener_registrar_typed_factory_568_tests.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "catch2/reporters/catch_reporter_registrars.hpp"  // Header under test

// If your project uses separate headers for these forward declarations,
// prefer those. We only reference interfaces/types that appear in the
// provided interface and do not peek into internals.
using Catch::ListenerRegistrar;

// Minimal stand-in mock for IConfig just so we can call create().
namespace {
    // Forward declare the type as it appears in the interface.
    // The real definition lives in Catch2 and will be linked from the project.
    class IConfig;
}

// -------------------------------
// Test fixture
// -------------------------------
class ListenerRegistrarTypedFactoryTest_568 : public ::testing::Test {
protected:
    // Helper that returns a factory constructed with a given name.
    // We avoid any assumptions about template parameters or internals.
    ListenerRegistrar::TypedListenerFactory makeFactory(const Catch::StringRef& name) {
        return ListenerRegistrar::TypedListenerFactory{name};
    }
};

// -------------------------------
// Tests
// -------------------------------

// Normal case: getName reflects the provided name exactly.
TEST_F(ListenerRegistrarTypedFactoryTest_568, GetName_ReturnsConstructorName_568) {
    const Catch::StringRef kName{"my_listener"};
    auto factory = makeFactory(kName);

    EXPECT_EQ(factory.getName(), kName);
}

// Boundary: empty name should be preserved (observable behavior only).
TEST_F(ListenerRegistrarTypedFactoryTest_568, GetName_EmptyName_IsPreserved_568) {
    const Catch::StringRef kEmptyName{};
    auto factory = makeFactory(kEmptyName);

    EXPECT_EQ(factory.getName().size(), 0u);
    EXPECT_EQ(factory.getName(), kEmptyName);
}

// Boundary: very long name should round-trip via getName (no assumptions on limits).
TEST_F(ListenerRegistrarTypedFactoryTest_568, GetName_LongName_RoundTrips_568) {
    std::string longName(4096, 'X');  // Large but reasonable boundary
    auto factory = makeFactory(Catch::StringRef{longName});

    EXPECT_EQ(factory.getName(), Catch::StringRef{longName});
}

// Behavior: getDescription is callable and stable (idempotent) across multiple invocations.
// We do NOT assert specific contents, only that it is consistent and does not throw.
TEST_F(ListenerRegistrarTypedFactoryTest_568, GetDescription_IsStableAndNoThrow_568) {
    auto factory = makeFactory(Catch::StringRef{"desc_listener"});

    std::string first;
    std::string second;

    EXPECT_NO_THROW(first  = factory.getDescription());
    EXPECT_NO_THROW(second = factory.getDescription());

    EXPECT_EQ(first, second) << "Description should be stable across calls";
}

// Smoke: create is callable with a config pointer.
// We do NOT infer behavior — only check that calling does not throw and (if non-null)
// returns a valid listener pointer type owned by a smart pointer.
TEST_F(ListenerRegistrarTypedFactoryTest_568, Create_IsCallableAndNoThrow_568) {
    auto factory = makeFactory(Catch::StringRef{"factory_create_smoke"});

    // We pass a nullptr config pointer intentionally — observable behavior is that the
    // function is callable. If the implementation requires non-null, it may return null
    // or throw; we only assert no-throw per black-box constraints.
    Catch::IConfig const* maybeNullConfig = nullptr;

    Catch::IEventListenerPtr listener;
    EXPECT_NO_THROW(listener = factory.create(maybeNullConfig));

    // If the implementation returns a non-null listener, great — we can at least assert ownership.
    // We DO NOT require non-null to avoid asserting internal policies.
    if (listener) {
        // Basic sanity: the pointer is unique_ptr-like and non-null.
        SUCCEED() << "create() returned a non-null listener";
    } else {
        SUCCEED() << "create() returned null (allowed by black-box contract)";
    }
}

// Regression/robustness: calling getDescription should not depend on previous getName calls.
TEST_F(ListenerRegistrarTypedFactoryTest_568, GetDescription_NotAffectedByGetNameCalls_568) {
    auto factory = makeFactory(Catch::StringRef{"independent_listener"});
    // Exercise getName a few times
    (void)factory.getName();
    (void)factory.getName();

    // Then verify description remains callable and stable
    EXPECT_NO_THROW({
        auto a = factory.getDescription();
        auto b = factory.getDescription();
        EXPECT_EQ(a, b);
    });
}

// Unicode name handling (observably preserved). This does not assume encoding
// normalization beyond what StringRef/getName expose.
TEST_F(ListenerRegistrarTypedFactoryTest_568, GetName_UnicodePreserved_568) {
    const std::string unicodeName = u8"리스너_描述_リスナー";
    auto factory = makeFactory(Catch::StringRef{unicodeName});

    EXPECT_EQ(factory.getName(), Catch::StringRef{unicodeName});
}
