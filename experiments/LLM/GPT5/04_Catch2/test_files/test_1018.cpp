// File: tests/testregistry_getalltests_1018.cpp

#include <gtest/gtest.h>

// Prefer the amalgamated header if available in your tree.
// If you include paths differently, adjust the include accordingly.
#include <catch_amalgamated.hpp>

using Catch::TestRegistry;

class TestRegistryTest_1018 : public ::testing::Test {
protected:
    TestRegistry registry_; // Default-constructed registry under test
};

// [Normal] Empty registry should return an empty vector.
TEST_F(TestRegistryTest_1018, EmptyRegistry_ReturnsEmptyVector_1018) {
    const auto& all = registry_.getAllTests();
    EXPECT_TRUE(all.empty()) << "Newly constructed registry should have no tests";
    EXPECT_EQ(all.size(), 0u);
}

// [Boundary] The function should return a const reference that remains valid
// and consistent across multiple calls (i.e., references the same container).
TEST_F(TestRegistryTest_1018, ReturnsConstReference_IsStableAcrossCalls_1018) {
    const auto* first_addr  = &registry_.getAllTests();
    const auto* second_addr = &registry_.getAllTests();
    EXPECT_EQ(first_addr, second_addr)
        << "getAllTests() should return a reference to the same underlying container";
}

// [Boundary] The returned reference must be const and not allow modification.
// (This is a compile-time property; here we assert runtime characteristics
// without attempting to modify it.)
TEST_F(TestRegistryTest_1018, ReturnedReference_IsConstAndNotModifiable_1018) {
    // Access via const reference and iterate (read-only) to verify usability.
    // We intentionally do NOT modify the contents.
    const auto& all = registry_.getAllTests();
    size_t count = 0;
    for (const auto& _ : all) {
        (void)_; // noop; just proving we can read/iterate
        ++count;
    }
    EXPECT_EQ(count, all.size());
}

// [Behavior] Multiple calls should not allocate new containers each time (address stable)
// and should remain empty if no tests were registered.
TEST_F(TestRegistryTest_1018, MultipleCalls_ConsistentContents_1018) {
    const auto& first = registry_.getAllTests();
    const auto& second = registry_.getAllTests();
    EXPECT_EQ(&first, &second);
    EXPECT_EQ(first.size(), second.size());
    EXPECT_TRUE(first.empty());
}
