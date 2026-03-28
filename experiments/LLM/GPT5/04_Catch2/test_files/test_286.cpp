// File: catch_registry_hub_tests_286.cpp

#include <gtest/gtest.h>
#include <type_traits>
#include <thread>
#include <vector>
#include <array>

// Prefer using the public/internal declaration if available in your tree.
// If your project exposes a different header, adjust this include accordingly.
#include <catch2/internal/catch_registry_hub.hpp>

// If your include path differs, these forward declarations match the interface:
// namespace Catch {
//     struct IRegistryHub;
//     IRegistryHub const& getRegistryHub();
// }

using namespace ::testing;

namespace {

// ------------------------
// Test Suite: RegistryHub
// ------------------------

TEST(RegistryHubTest_286, ReturnsSameInstance_286) {
    // Normal operation: repeated calls should return the same singleton instance.
    auto& first  = Catch::getRegistryHub();
    auto& second = Catch::getRegistryHub();
    EXPECT_EQ(&first, &second);
}

TEST(RegistryHubTest_286, ReturnsConstReferenceType_286) {
    // Interface-level property: return type should be 'IRegistryHub const&'.
    using Ret = decltype(Catch::getRegistryHub());
    constexpr bool is_ref   = std::is_reference<Ret>::value;
    constexpr bool is_const = std::is_const<typename std::remove_reference<Ret>::type>::value;

    EXPECT_TRUE(is_ref);
    EXPECT_TRUE(is_const);
}

TEST(RegistryHubTest_286, AddressIsStableAcrossManyCalls_286) {
    // Boundary-ish check: ensure the address is stable across many calls.
    auto* baseline = &Catch::getRegistryHub();
    for (int i = 0; i < 1000; ++i) {
        EXPECT_EQ(&Catch::getRegistryHub(), baseline);
    }
}

TEST(RegistryHubTest_286, ConcurrentAccessReturnsSameInstance_286) {
    // Concurrency/robustness: concurrent access should observe the same instance.
    // (We do not assert anything about synchronization internals—only that the
    // observed address is identical across threads.)
    constexpr int kThreads = 8;
    std::array<const void*, kThreads> addrs{};
    std::vector<std::thread> threads;
    threads.reserve(kThreads);

    for (int i = 0; i < kThreads; ++i) {
        threads.emplace_back([i, &addrs]() {
            // Take the address of the const reference returned.
            addrs[i] = static_cast<const void*>(&Catch::getRegistryHub());
        });
    }
    for (auto& t : threads) t.join();

    for (int i = 1; i < kThreads; ++i) {
        EXPECT_EQ(addrs[i], addrs[0]) << "Different instance observed in thread " << i;
    }
}

TEST(RegistryHubTest_286, ReferenceIsNotNull_286) {
    // Sanity check: the reference we get should have a valid address.
    auto* ptr = &Catch::getRegistryHub();
    EXPECT_NE(ptr, nullptr);
}

} // namespace
