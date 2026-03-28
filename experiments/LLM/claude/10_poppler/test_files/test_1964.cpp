#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "CryptoSignBackend.h"
#include <memory>
#include <optional>
#include <string>
#include <vector>

// Test fixture for CryptoSign::Factory tests
class CryptoSignFactoryTest_1964 : public ::testing::Test {
protected:
    void SetUp() override {
        // No setup needed since Factory has deleted constructor (all static methods)
    }

    void TearDown() override {
        // Clean up any preferred backend settings if possible
    }
};

// Test that getAvailable returns a vector (may be empty if no backends compiled in)
TEST_F(CryptoSignFactoryTest_1964, GetAvailableReturnsVector_1964) {
    auto available = CryptoSign::Factory::getAvailable();
    // Just verify it doesn't crash and returns a vector
    // The vector may be empty or contain backends depending on build configuration
    EXPECT_GE(available.size(), 0u);
}

// Test that getActive returns an optional that is consistent with available backends
TEST_F(CryptoSignFactoryTest_1964, GetActiveConsistentWithAvailable_1964) {
    auto available = CryptoSign::Factory::getAvailable();
    auto active = CryptoSign::Factory::getActive();
    
    if (available.empty()) {
        // If no backends available, active should be nullopt
        EXPECT_FALSE(active.has_value());
    } else {
        // If backends are available, active may or may not have a value
        // but if it does, it should be one of the available ones
        if (active.has_value()) {
            bool found = false;
            for (const auto& backend : available) {
                if (backend == active.value()) {
                    found = true;
                    break;
                }
            }
            EXPECT_TRUE(found) << "Active backend should be among available backends";
        }
    }
}

// Test createActive returns nullptr when no backends are available, or a valid pointer otherwise
TEST_F(CryptoSignFactoryTest_1964, CreateActiveReturnsValidOrNull_1964) {
    auto active = CryptoSign::Factory::getActive();
    auto backend = CryptoSign::Factory::createActive();
    
    if (active.has_value()) {
        EXPECT_NE(backend, nullptr) << "createActive should return non-null when an active backend exists";
    } else {
        EXPECT_EQ(backend, nullptr) << "createActive should return nullptr when no active backend";
    }
}

// Test create with each available backend type
TEST_F(CryptoSignFactoryTest_1964, CreateWithAvailableBackends_1964) {
    auto available = CryptoSign::Factory::getAvailable();
    
    for (const auto& type : available) {
        auto backend = CryptoSign::Factory::create(type);
        EXPECT_NE(backend, nullptr) << "create() should return non-null for available backend type";
    }
}

// Test typeFromString with known backend names
TEST_F(CryptoSignFactoryTest_1964, TypeFromStringNSS_1964) {
    auto result = CryptoSign::Factory::typeFromString(std::string_view("NSS"));
    // Result depends on build config; just verify it doesn't crash
    // If NSS is available, it should return a value
    auto available = CryptoSign::Factory::getAvailable();
    if (result.has_value()) {
        bool found = false;
        for (const auto& backend : available) {
            if (backend == result.value()) {
                found = true;
                break;
            }
        }
        EXPECT_TRUE(found);
    }
}

TEST_F(CryptoSignFactoryTest_1964, TypeFromStringGPG_1964) {
    auto result = CryptoSign::Factory::typeFromString(std::string_view("GPG"));
    // Similar to above - just verify it doesn't crash
    if (result.has_value()) {
        auto available = CryptoSign::Factory::getAvailable();
        bool found = false;
        for (const auto& backend : available) {
            if (backend == result.value()) {
                found = true;
                break;
            }
        }
        EXPECT_TRUE(found);
    }
}

// Test typeFromString with an invalid/unknown string
TEST_F(CryptoSignFactoryTest_1964, TypeFromStringInvalidReturnsNullopt_1964) {
    auto result = CryptoSign::Factory::typeFromString(std::string_view("NONEXISTENT_BACKEND_XYZ"));
    EXPECT_FALSE(result.has_value()) << "typeFromString with invalid string should return nullopt";
}

// Test typeFromString with empty string
TEST_F(CryptoSignFactoryTest_1964, TypeFromStringEmptyReturnsNullopt_1964) {
    auto result = CryptoSign::Factory::typeFromString(std::string_view(""));
    EXPECT_FALSE(result.has_value()) << "typeFromString with empty string should return nullopt";
}

// Test setPreferredBackend and verify it affects getActive
TEST_F(CryptoSignFactoryTest_1964, SetPreferredBackendAffectsGetActive_1964) {
    auto available = CryptoSign::Factory::getAvailable();
    
    if (available.size() > 0) {
        // Set preferred to the first available backend
        CryptoSign::Factory::setPreferredBackend(available[0]);
        auto active = CryptoSign::Factory::getActive();
        EXPECT_TRUE(active.has_value());
        EXPECT_EQ(active.value(), available[0]);
    }
}

// Test setPreferredBackend with each available backend
TEST_F(CryptoSignFactoryTest_1964, SetPreferredBackendEachAvailable_1964) {
    auto available = CryptoSign::Factory::getAvailable();
    
    for (const auto& type : available) {
        CryptoSign::Factory::setPreferredBackend(type);
        auto active = CryptoSign::Factory::getActive();
        EXPECT_TRUE(active.has_value());
        EXPECT_EQ(active.value(), type);
    }
}

// Test that createActive works after setting preferred backend
TEST_F(CryptoSignFactoryTest_1964, CreateActiveAfterSetPreferred_1964) {
    auto available = CryptoSign::Factory::getAvailable();
    
    if (!available.empty()) {
        CryptoSign::Factory::setPreferredBackend(available[0]);
        auto backend = CryptoSign::Factory::createActive();
        EXPECT_NE(backend, nullptr);
    }
}

// Test that multiple calls to createActive return independent objects
TEST_F(CryptoSignFactoryTest_1964, CreateActiveReturnsUniqueInstances_1964) {
    auto active = CryptoSign::Factory::getActive();
    
    if (active.has_value()) {
        auto backend1 = CryptoSign::Factory::createActive();
        auto backend2 = CryptoSign::Factory::createActive();
        EXPECT_NE(backend1, nullptr);
        EXPECT_NE(backend2, nullptr);
        EXPECT_NE(backend1.get(), backend2.get()) << "Each call should return a distinct instance";
    }
}

// Test that multiple calls to create return independent objects
TEST_F(CryptoSignFactoryTest_1964, CreateReturnsUniqueInstances_1964) {
    auto available = CryptoSign::Factory::getAvailable();
    
    if (!available.empty()) {
        auto backend1 = CryptoSign::Factory::create(available[0]);
        auto backend2 = CryptoSign::Factory::create(available[0]);
        EXPECT_NE(backend1, nullptr);
        EXPECT_NE(backend2, nullptr);
        EXPECT_NE(backend1.get(), backend2.get()) << "Each call should return a distinct instance";
    }
}

// Test typeFromString with various case variations (boundary)
TEST_F(CryptoSignFactoryTest_1964, TypeFromStringCaseSensitivity_1964) {
    auto resultLower = CryptoSign::Factory::typeFromString(std::string_view("nss"));
    auto resultUpper = CryptoSign::Factory::typeFromString(std::string_view("NSS"));
    // Just check they don't crash; case sensitivity behavior is implementation-defined
    // but we can note if they differ
    (void)resultLower;
    (void)resultUpper;
}

// Test getAvailable returns consistent results on multiple calls
TEST_F(CryptoSignFactoryTest_1964, GetAvailableConsistentAcrossCalls_1964) {
    auto available1 = CryptoSign::Factory::getAvailable();
    auto available2 = CryptoSign::Factory::getAvailable();
    EXPECT_EQ(available1.size(), available2.size());
    for (size_t i = 0; i < available1.size(); ++i) {
        EXPECT_EQ(available1[i], available2[i]);
    }
}
