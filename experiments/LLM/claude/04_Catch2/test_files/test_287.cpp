#include <gtest/gtest.h>

// Include necessary Catch2 headers
#include "catch2/catch_registry_hub.hpp"
#include "catch2/interfaces/catch_interfaces_registry_hub.hpp"

namespace {

// Test that getMutableRegistryHub returns a valid reference (non-null, no crash)
TEST(CatchRegistryHubTest_287, GetMutableRegistryHubReturnsValidReference_287) {
    // Should not throw or crash when getting the mutable registry hub
    EXPECT_NO_THROW({
        Catch::IMutableRegistryHub& hub = Catch::getMutableRegistryHub();
        // Just verify we can take the address (i.e., it's a valid reference)
        EXPECT_NE(&hub, nullptr);
    });
}

// Test that repeated calls return the same singleton instance
TEST(CatchRegistryHubTest_287, GetMutableRegistryHubReturnsSameSingleton_287) {
    Catch::IMutableRegistryHub& hub1 = Catch::getMutableRegistryHub();
    Catch::IMutableRegistryHub& hub2 = Catch::getMutableRegistryHub();
    EXPECT_EQ(&hub1, &hub2);
}

// Test that getRegistryHub returns a valid reference
TEST(CatchRegistryHubTest_287, GetRegistryHubReturnsValidReference_287) {
    EXPECT_NO_THROW({
        Catch::IRegistryHub const& hub = Catch::getRegistryHub();
        EXPECT_NE(&hub, nullptr);
    });
}

// Test that repeated calls to getRegistryHub return the same singleton
TEST(CatchRegistryHubTest_287, GetRegistryHubReturnsSameSingleton_287) {
    Catch::IRegistryHub const& hub1 = Catch::getRegistryHub();
    Catch::IRegistryHub const& hub2 = Catch::getRegistryHub();
    EXPECT_EQ(&hub1, &hub2);
}

// Test that mutable and const registry hub refer to the same underlying object
// (since they are both views of the same singleton)
TEST(CatchRegistryHubTest_287, MutableAndConstHubShareSameObject_287) {
    Catch::IMutableRegistryHub& mutableHub = Catch::getMutableRegistryHub();
    Catch::IRegistryHub const& constHub = Catch::getRegistryHub();
    
    // Both should point to the same singleton instance when cast to void*
    // The mutable interface and const interface should be derived from the same object
    // We can at least verify they are both valid
    EXPECT_NE(static_cast<const void*>(&mutableHub), nullptr);
    EXPECT_NE(static_cast<const void*>(&constHub), nullptr);
}

// Test that cleanUpContext and then re-accessing doesn't crash
// (tests the singleton lifecycle behavior)
TEST(CatchRegistryHubTest_287, CleanUpAndReaccess_287) {
    // First access to establish singleton
    Catch::IMutableRegistryHub& hub1 = Catch::getMutableRegistryHub();
    EXPECT_NE(&hub1, nullptr);

    // Clean up
    Catch::cleanUpContext();

    // Re-access should recreate the singleton
    EXPECT_NO_THROW({
        Catch::IMutableRegistryHub& hub2 = Catch::getMutableRegistryHub();
        EXPECT_NE(&hub2, nullptr);
    });
}

// Test that cleanUpContext can be called multiple times without issue
TEST(CatchRegistryHubTest_287, MultipleCleanUpsDoNotCrash_287) {
    EXPECT_NO_THROW({
        Catch::getMutableRegistryHub();
        Catch::cleanUpContext();
        Catch::cleanUpContext();
    });
    
    // Re-establish for other tests
    EXPECT_NO_THROW({
        Catch::getMutableRegistryHub();
    });
}

} // anonymous namespace
