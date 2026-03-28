// ReporterRegistry_registerListener_tests_576.cpp
#include <gtest/gtest.h>

#include "catch2/internal/catch_reporter_registry.hpp"
#include "catch2/internal/catch_unique_ptr.hpp"

namespace {

using Catch::ReporterRegistry;
using Catch::Detail::unique_ptr;

// Forward-declare the type to construct null pointers without requiring its definition.
class EventListenerFactory;

class ReporterRegistryTest_576 : public ::testing::Test {
protected:
    ReporterRegistry registry_;
};

} // namespace

// Verifies that a default-constructed registry starts with no listeners.
TEST_F(ReporterRegistryTest_576, InitiallyEmptyListeners_576) {
    const auto& listeners = registry_.getListeners();
    EXPECT_TRUE(listeners.empty());
}

// Verifies that registering a (moved) unique_ptr adds one entry
// and the source unique_ptr becomes empty (move semantics are observable).
TEST_F(ReporterRegistryTest_576, RegisterListener_AddsEntryAndInvalidatesSource_576) {
    unique_ptr<EventListenerFactory> src; // nullptr unique_ptr is valid and observable

    // Move into the registry
    registry_.registerListener(std::move(src));

    // After move, the source should be empty/null
    EXPECT_FALSE(static_cast<bool>(src));

    // The registry should now report one listener entry, which holds a null pointer
    // (observable via operator bool()/get() on the element).
    const auto& listeners = registry_.getListeners();
    ASSERT_EQ(listeners.size(), 1u);
    EXPECT_FALSE(static_cast<bool>(listeners.back())); // null entry is preserved
    EXPECT_EQ(listeners.back().get(), nullptr);
}

// Verifies that multiple calls append entries (order/append behavior),
// and sizes match the number of registrations.
TEST_F(ReporterRegistryTest_576, RegisterListener_MultipleAddsIncreaseSize_576) {
    // Register two null listeners via moved unique_ptrs.
    unique_ptr<EventListenerFactory> a;
    unique_ptr<EventListenerFactory> b;

    registry_.registerListener(std::move(a));
    registry_.registerListener(std::move(b));

    const auto& listeners = registry_.getListeners();
    ASSERT_EQ(listeners.size(), 2u);

    // Both inserted entries should be present and (since we passed nullptr) null.
    EXPECT_FALSE(static_cast<bool>(listeners[0]));
    EXPECT_FALSE(static_cast<bool>(listeners[1]));
}
