// File: tests/registry_hub_get_mutable_tests_287.cpp

#include <gtest/gtest.h>
#include <type_traits>

// Public interfaces/decls from Catch2
#include <catch2/interfaces/catch_interfaces_registry_hub.hpp>
#include <catch2/internal/catch_registry_hub.hpp>

using namespace Catch;

class RegistryHubTest_287 : public ::testing::Test {};

// [287] Verifies the function is callable, does not throw, and returns a non-null reference.
TEST_F(RegistryHubTest_287, NoThrowAndNotNull_287) {
    EXPECT_NO_THROW({
        IMutableRegistryHub& ref = getMutableRegistryHub();
        (void)ref; // silence unused warning; we only assert observables
    });

    IMutableRegistryHub* ptr = &getMutableRegistryHub();
    EXPECT_NE(ptr, nullptr);
}

// [287] Compile-time contract: return type must be IMutableRegistryHub&.
TEST_F(RegistryHubTest_287, ReturnTypeIsMutableInterface_287) {
    static_assert(std::is_same<decltype(getMutableRegistryHub()), IMutableRegistryHub&>::value,
                  "getMutableRegistryHub must return IMutableRegistryHub&");
    SUCCEED();
}

// [287] Repeated calls must return the same singleton instance (stable identity).
TEST_F(RegistryHubTest_287, ReturnsSameInstanceOnRepeatedCalls_287) {
    IMutableRegistryHub* first = &getMutableRegistryHub();
    for (int i = 0; i < 100; ++i) {
        IMutableRegistryHub* next = &getMutableRegistryHub();
        EXPECT_EQ(first, next) << "Call #" << i << " returned a different instance";
    }
}

// [287] The reference should remain the same when bound through const and non-const views.
TEST_F(RegistryHubTest_287, SameAddressThroughConstRef_287) {
    IMutableRegistryHub& mutRef = getMutableRegistryHub();
    const IMutableRegistryHub& constRef = getMutableRegistryHub();

    auto* mutPtr = &mutRef;
    auto* constPtr = const_cast<IMutableRegistryHub*>(&constRef);
    EXPECT_EQ(mutPtr, constPtr);
}
