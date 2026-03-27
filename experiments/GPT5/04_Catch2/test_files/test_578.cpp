// ReporterRegistry_getListeners_test_578.cpp
#include <gtest/gtest.h>

#include "catch2/internal/catch_reporter_registry.hpp"

// Minimal stand-in for external collaborator.
// We do NOT simulate any internal behavior of ReporterRegistry.
// This exists solely to provide a concrete type for the unique_ptr.
namespace Catch {
    struct EventListenerFactory {
        virtual ~EventListenerFactory() = default;
    };
}

using Catch::ReporterRegistry;
using Catch::Detail::unique_ptr;
using Catch::EventListenerFactory;

class ReporterRegistryTest_578 : public ::testing::Test {
protected:
    ReporterRegistry registry_;
};

// [Boundary] Fresh registry has no listeners
TEST_F(ReporterRegistryTest_578, GetListeners_EmptyOnConstruction_578) {
    const auto& listeners = registry_.getListeners();
    EXPECT_TRUE(listeners.empty());
}

// [Normal] After registering a listener, it is observable via getListeners()
TEST_F(ReporterRegistryTest_578, RegisterListener_ThenVisibleViaGetListeners_578) {
    // arrange
    unique_ptr<EventListenerFactory> f{ new EventListenerFactory() };

    // act
    registry_.registerListener(std::move(f));

    // assert
    const auto& listeners = registry_.getListeners();
    ASSERT_EQ(listeners.size(), 1u);
    // The stored unique_ptr should hold a non-null pointer (observable via get())
    // without making any assumptions about internal layout/order beyond size.
    EXPECT_NE(listeners[0].get(), nullptr);
}

// [Normal] Multiple registrations are reflected in size reported by getListeners()
TEST_F(ReporterRegistryTest_578, RegisterMultipleListeners_SizeAccumulates_578) {
    unique_ptr<EventListenerFactory> f1{ new EventListenerFactory() };
    unique_ptr<EventListenerFactory> f2{ new EventListenerFactory() };

    registry_.registerListener(std::move(f1));
    registry_.registerListener(std::move(f2));

    const auto& listeners = registry_.getListeners();
    EXPECT_EQ(listeners.size(), 2u);
    // Do not assert ordering/internal behavior; just that both entries are non-null.
    EXPECT_NE(listeners[0].get(), nullptr);
    EXPECT_NE(listeners[1].get(), nullptr);
}

// [Normal/Ownership] Passing a unique_ptr transfers ownership away from the caller (observable)
TEST_F(ReporterRegistryTest_578, RegisterListener_MovesOwnershipFromCaller_578) {
    unique_ptr<EventListenerFactory> f{ new EventListenerFactory() };
    ASSERT_TRUE(static_cast<bool>(f)); // precondition: caller owns it

    registry_.registerListener(std::move(f));

    // After move, the caller's unique_ptr should be empty (observable without peeking inside registry)
    EXPECT_FALSE(static_cast<bool>(f));

    // And registry exposes exactly one listener
    const auto& listeners = registry_.getListeners();
    ASSERT_EQ(listeners.size(), 1u);
    EXPECT_NE(listeners[0].get(), nullptr);
}

// [API contract] getListeners returns a reference to the same container each time
TEST_F(ReporterRegistryTest_578, GetListeners_ReturnsStableReference_578) {
    const auto& ref1 = registry_.getListeners();
    const auto& ref2 = registry_.getListeners();
    // Taking addresses of the referenced container objects should match
    EXPECT_EQ(&ref1, &ref2);
}
