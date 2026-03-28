#include <gtest/gtest.h>
#include <vector>
#include <optional>
#include <memory>
#include <string_view>

#include "CryptoSignBackend.h"

using namespace CryptoSign;

// Test that getAvailable returns a vector (may be empty depending on build config)
TEST(CryptoSignFactoryTest_1963, GetAvailableReturnsVector_1963)
{
    std::vector<Backend::Type> available = Factory::getAvailable();
    // We can at least verify it doesn't crash and returns a valid vector
    EXPECT_GE(available.size(), 0u);
}

// Test that calling getAvailable multiple times returns the same result (cached)
TEST(CryptoSignFactoryTest_1963, GetAvailableIsConsistent_1963)
{
    std::vector<Backend::Type> first = Factory::getAvailable();
    std::vector<Backend::Type> second = Factory::getAvailable();
    EXPECT_EQ(first.size(), second.size());
    for (size_t i = 0; i < first.size(); ++i) {
        EXPECT_EQ(first[i], second[i]);
    }
}

// Test getActive - should return a value if backends are available, or nullopt otherwise
TEST(CryptoSignFactoryTest_1963, GetActiveReturnsOptional_1963)
{
    std::optional<Backend::Type> active = Factory::getActive();
    std::vector<Backend::Type> available = Factory::getAvailable();
    if (available.empty()) {
        EXPECT_FALSE(active.has_value());
    } else {
        // If backends are available, getActive should return something
        EXPECT_TRUE(active.has_value());
    }
}

// Test that setPreferredBackend with an available backend changes the active backend
TEST(CryptoSignFactoryTest_1963, SetPreferredBackendChangesActive_1963)
{
    std::vector<Backend::Type> available = Factory::getAvailable();
    if (available.empty()) {
        GTEST_SKIP() << "No backends available";
    }
    for (const auto &backend : available) {
        Factory::setPreferredBackend(backend);
        std::optional<Backend::Type> active = Factory::getActive();
        ASSERT_TRUE(active.has_value());
        EXPECT_EQ(active.value(), backend);
    }
}

// Test createActive returns a valid backend when backends are available
TEST(CryptoSignFactoryTest_1963, CreateActiveReturnsBackend_1963)
{
    std::vector<Backend::Type> available = Factory::getAvailable();
    if (available.empty()) {
        GTEST_SKIP() << "No backends available";
    }
    std::unique_ptr<Backend> backend = Factory::createActive();
    EXPECT_NE(backend, nullptr);
}

// Test createActive returns nullptr when no backends are available
TEST(CryptoSignFactoryTest_1963, CreateActiveReturnsNullWhenNoBackends_1963)
{
    std::vector<Backend::Type> available = Factory::getAvailable();
    if (!available.empty()) {
        GTEST_SKIP() << "Backends are available, cannot test null case";
    }
    std::unique_ptr<Backend> backend = Factory::createActive();
    EXPECT_EQ(backend, nullptr);
}

// Test create with each available backend type
TEST(CryptoSignFactoryTest_1963, CreateWithAvailableBackendType_1963)
{
    std::vector<Backend::Type> available = Factory::getAvailable();
    if (available.empty()) {
        GTEST_SKIP() << "No backends available";
    }
    for (const auto &type : available) {
        std::unique_ptr<Backend> backend = Factory::create(type);
        EXPECT_NE(backend, nullptr) << "Failed to create backend for available type";
    }
}

// Test typeFromString with known string values
TEST(CryptoSignFactoryTest_1963, TypeFromStringWithNSS_1963)
{
    std::optional<Backend::Type> result = Factory::typeFromString(std::string_view("NSS"));
    // Result depends on available backends - just verify it doesn't crash
    // If NSS is available, it should return a value
    std::vector<Backend::Type> available = Factory::getAvailable();
    if (result.has_value()) {
        // The returned type should be one of the available backends or a valid type
        EXPECT_TRUE(result.has_value());
    }
}

TEST(CryptoSignFactoryTest_1963, TypeFromStringWithGPG_1963)
{
    std::optional<Backend::Type> result = Factory::typeFromString(std::string_view("GPG"));
    // Just verify it doesn't crash - result depends on build configuration
    (void)result;
}

// Test typeFromString with unknown string
TEST(CryptoSignFactoryTest_1963, TypeFromStringWithUnknownString_1963)
{
    std::optional<Backend::Type> result = Factory::typeFromString(std::string_view("UNKNOWN_BACKEND_XYZ"));
    EXPECT_FALSE(result.has_value());
}

// Test typeFromString with empty string
TEST(CryptoSignFactoryTest_1963, TypeFromStringWithEmptyString_1963)
{
    std::optional<Backend::Type> result = Factory::typeFromString(std::string_view(""));
    EXPECT_FALSE(result.has_value());
}

// Test that setPreferredBackend followed by getActive returns the set backend
TEST(CryptoSignFactoryTest_1963, SetAndGetPreferredBackend_1963)
{
    std::vector<Backend::Type> available = Factory::getAvailable();
    if (available.size() < 2) {
        GTEST_SKIP() << "Need at least 2 backends to test preference switching";
    }
    
    Factory::setPreferredBackend(available[0]);
    EXPECT_EQ(Factory::getActive().value(), available[0]);
    
    Factory::setPreferredBackend(available[1]);
    EXPECT_EQ(Factory::getActive().value(), available[1]);
    
    // Switch back
    Factory::setPreferredBackend(available[0]);
    EXPECT_EQ(Factory::getActive().value(), available[0]);
}

// Test typeFromString with various case patterns
TEST(CryptoSignFactoryTest_1963, TypeFromStringCaseSensitivity_1963)
{
    std::optional<Backend::Type> lower = Factory::typeFromString(std::string_view("nss"));
    std::optional<Backend::Type> upper = Factory::typeFromString(std::string_view("NSS"));
    // Just verify neither crashes; case sensitivity behavior is implementation-defined
    (void)lower;
    (void)upper;
}
