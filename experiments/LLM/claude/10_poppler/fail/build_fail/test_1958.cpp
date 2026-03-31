#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "CryptoSignBackend.h"
#include <optional>
#include <vector>
#include <memory>
#include <string>

class CryptoSignFactoryTest_1958 : public ::testing::Test {
protected:
    void SetUp() override {
        // Reset state if possible - get available backends for reference
        availableBackends = CryptoSign::Factory::getAvailable();
    }

    std::vector<CryptoSign::Backend::Type> availableBackends;
};

TEST_F(CryptoSignFactoryTest_1958, GetAvailableReturnsVector_1958) {
    auto available = CryptoSign::Factory::getAvailable();
    // Should return a vector (may be empty if no backends compiled in)
    // Just verify it doesn't crash and returns consistently
    auto available2 = CryptoSign::Factory::getAvailable();
    EXPECT_EQ(available.size(), available2.size());
}

TEST_F(CryptoSignFactoryTest_1958, GetActiveReturnsOptional_1958) {
    auto active = CryptoSign::Factory::getActive();
    if (availableBackends.empty()) {
        // If no backends available, active should be nullopt
        EXPECT_FALSE(active.has_value());
    } else {
        // If backends are available, there should be an active one
        EXPECT_TRUE(active.has_value());
    }
}

TEST_F(CryptoSignFactoryTest_1958, SetPreferredBackendWithAvailableBackend_1958) {
    if (availableBackends.empty()) {
        GTEST_SKIP() << "No backends available for testing";
    }
    auto backendType = availableBackends[0];
    CryptoSign::Factory::setPreferredBackend(backendType);
    auto active = CryptoSign::Factory::getActive();
    ASSERT_TRUE(active.has_value());
    EXPECT_EQ(active.value(), backendType);
}

TEST_F(CryptoSignFactoryTest_1958, CreateActiveReturnsBackendWhenAvailable_1958) {
    if (availableBackends.empty()) {
        GTEST_SKIP() << "No backends available for testing";
    }
    CryptoSign::Factory::setPreferredBackend(availableBackends[0]);
    auto backend = CryptoSign::Factory::createActive();
    EXPECT_NE(backend, nullptr);
}

TEST_F(CryptoSignFactoryTest_1958, CreateWithValidType_1958) {
    if (availableBackends.empty()) {
        GTEST_SKIP() << "No backends available for testing";
    }
    auto backend = CryptoSign::Factory::create(availableBackends[0]);
    EXPECT_NE(backend, nullptr);
}

TEST_F(CryptoSignFactoryTest_1958, TypeFromStringInvalidReturnsNullopt_1958) {
    auto result = CryptoSign::Factory::typeFromString(std::string_view("invalid_backend_name_xyz"));
    EXPECT_FALSE(result.has_value());
}

TEST_F(CryptoSignFactoryTest_1958, TypeFromStringEmptyReturnsNullopt_1958) {
    auto result = CryptoSign::Factory::typeFromString(std::string_view(""));
    EXPECT_FALSE(result.has_value());
}

TEST_F(CryptoSignFactoryTest_1958, TypeFromStringNSS_1958) {
    auto result = CryptoSign::Factory::typeFromString(std::string_view("NSS"));
    // May or may not have value depending on compiled backends
    if (result.has_value()) {
        EXPECT_EQ(result.value(), CryptoSign::Backend::Type::NSS);
    }
}

TEST_F(CryptoSignFactoryTest_1958, TypeFromStringGPG_1958) {
    auto result = CryptoSign::Factory::typeFromString(std::string_view("GPG"));
    if (result.has_value()) {
        EXPECT_EQ(result.value(), CryptoSign::Backend::Type::GPGME);
    }
}

TEST_F(CryptoSignFactoryTest_1958, SetPreferredBackendChangesActive_1958) {
    if (availableBackends.size() < 2) {
        GTEST_SKIP() << "Need at least 2 backends to test switching";
    }
    CryptoSign::Factory::setPreferredBackend(availableBackends[0]);
    auto active1 = CryptoSign::Factory::getActive();
    ASSERT_TRUE(active1.has_value());
    EXPECT_EQ(active1.value(), availableBackends[0]);

    CryptoSign::Factory::setPreferredBackend(availableBackends[1]);
    auto active2 = CryptoSign::Factory::getActive();
    ASSERT_TRUE(active2.has_value());
    EXPECT_EQ(active2.value(), availableBackends[1]);
}

TEST_F(CryptoSignFactoryTest_1958, CreateActiveWhenNoBackendsAvailable_1958) {
    if (!availableBackends.empty()) {
        GTEST_SKIP() << "Backends are available, cannot test empty case";
    }
    auto backend = CryptoSign::Factory::createActive();
    EXPECT_EQ(backend, nullptr);
}

TEST_F(CryptoSignFactoryTest_1958, GetAvailableConsistentResults_1958) {
    auto first = CryptoSign::Factory::getAvailable();
    auto second = CryptoSign::Factory::getAvailable();
    EXPECT_EQ(first, second);
}

TEST_F(CryptoSignFactoryTest_1958, ActiveBackendIsInAvailableList_1958) {
    auto active = CryptoSign::Factory::getActive();
    if (active.has_value()) {
        auto available = CryptoSign::Factory::getAvailable();
        EXPECT_THAT(available, ::testing::Contains(active.value()));
    }
}
