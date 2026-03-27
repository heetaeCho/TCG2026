// File: tests/config_testSpec_720.cpp

#include <gtest/gtest.h>
#include <type_traits>

// Include only the public header that declares the interface under test.
#include "catch2/catch_config.hpp"

using namespace Catch;

class ConfigTest_720 : public ::testing::Test {};

// [Normal operation] The function returns a reference and does not throw.
TEST_F(ConfigTest_720, ReturnsReference_NoThrow_720) {
    Config cfg; // use public default ctor as exposed by the header
    EXPECT_NO_THROW({
        auto& ref = cfg.testSpec();
        (void)ref; // silence unused warning
    });
}

// [Normal operation] Multiple calls return the same referenced object (stable address within the same instance).
TEST_F(ConfigTest_720, SameAddressAcrossCalls_720) {
    Config cfg;
    const auto* first = &cfg.testSpec();
    const auto* second = &cfg.testSpec();
    EXPECT_EQ(first, second);
}

// [Boundary/const-correctness] Calling via const view returns the same object.
TEST_F(ConfigTest_720, SameAddressThroughConstView_720) {
    Config cfg;
    const auto* from_nonconst = &cfg.testSpec();

    const Config& cview = cfg;
    const auto* from_const = &cview.testSpec();

    EXPECT_EQ(from_nonconst, from_const);
}

// [Boundary] Different Config instances should not alias the same referenced object.
TEST_F(ConfigTest_720, DifferentInstancesHaveDifferentTestSpecObjects_720) {
    Config a;
    Config b;

    const auto* pa = &a.testSpec();
    const auto* pb = &b.testSpec();

    // Expect different storage for different objects' test specs.
    EXPECT_NE(pa, pb);
}

// [Boundary] Copying the Config does not change the original’s referenced object.
TEST_F(ConfigTest_720, OriginalReferenceStableAfterCopy_720) {
    Config original;

    const auto* before_copy = &original.testSpec();

    // Make a copy using the public copy constructor (implicitly available if not deleted).
    Config copied = original;

    const auto* after_copy = &original.testSpec();

    EXPECT_EQ(before_copy, after_copy) << "Address of original's testSpec should remain stable after copying the Config";
    // (We intentionally do not assert anything about `copied`'s internals; we only check original stability.)
}

// [Interface shape] The returned type is a const reference (compile-time check only).
TEST_F(ConfigTest_720, ReturnsConstReference_TypeTraits_720) {
    Config cfg;
    using Ret = decltype(cfg.testSpec());
    // Must be a reference
    static_assert(std::is_reference<Ret>::value, "testSpec() should return a reference");
    // Must be const-qualified
    static_assert(std::is_const<std::remove_reference_t<Ret>>::value, "testSpec() should return a const-qualified reference");
}
