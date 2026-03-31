#include <gtest/gtest.h>
#include <memory>
#include <optional>
#include <vector>
#include <string_view>

#include "CryptoSignBackend.h"

class CryptoSignFactoryTest_1965 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test: getAvailable returns a non-empty vector if any backend is compiled in
TEST_F(CryptoSignFactoryTest_1965, GetAvailableReturnsVector_1965) {
    auto available = CryptoSign::Factory::getAvailable();
    // We can't know exactly which backends are compiled in, but the vector should be valid
    // Each element should be a known Backend::Type
    for (auto backend : available) {
        EXPECT_TRUE(backend == CryptoSign::Backend::Type::NSS3 || backend == CryptoSign::Backend::Type::GPGME);
    }
}

// Test: create with NSS3 type
TEST_F(CryptoSignFactoryTest_1965, CreateNSS3Backend_1965) {
    auto backend = CryptoSign::Factory::create(CryptoSign::Backend::Type::NSS3);
    auto available = CryptoSign::Factory::getAvailable();
    bool nssAvailable = std::find(available.begin(), available.end(), CryptoSign::Backend::Type::NSS3) != available.end();
    
    if (nssAvailable) {
        EXPECT_NE(backend, nullptr);
    } else {
        EXPECT_EQ(backend, nullptr);
    }
}

// Test: create with GPGME type
TEST_F(CryptoSignFactoryTest_1965, CreateGPGMEBackend_1965) {
    auto backend = CryptoSign::Factory::create(CryptoSign::Backend::Type::GPGME);
    auto available = CryptoSign::Factory::getAvailable();
    bool gpgmeAvailable = std::find(available.begin(), available.end(), CryptoSign::Backend::Type::GPGME) != available.end();
    
    if (gpgmeAvailable) {
        EXPECT_NE(backend, nullptr);
    } else {
        EXPECT_EQ(backend, nullptr);
    }
}

// Test: create with an invalid enum value (cast from int beyond known range)
TEST_F(CryptoSignFactoryTest_1965, CreateWithInvalidTypeReturnsNull_1965) {
    auto backend = CryptoSign::Factory::create(static_cast<CryptoSign::Backend::Type>(999));
    EXPECT_EQ(backend, nullptr);
}

// Test: typeFromString with known string "NSS3" or "NSS"
TEST_F(CryptoSignFactoryTest_1965, TypeFromStringNSS_1965) {
    auto result = CryptoSign::Factory::typeFromString(std::string_view("NSS"));
    if (result.has_value()) {
        EXPECT_EQ(result.value(), CryptoSign::Backend::Type::NSS3);
    }
    // Also try "NSS3"
    auto result2 = CryptoSign::Factory::typeFromString(std::string_view("NSS3"));
    if (result2.has_value()) {
        EXPECT_EQ(result2.value(), CryptoSign::Backend::Type::NSS3);
    }
}

// Test: typeFromString with known string "GPGME" or "GPG"
TEST_F(CryptoSignFactoryTest_1965, TypeFromStringGPGME_1965) {
    auto result = CryptoSign::Factory::typeFromString(std::string_view("GPGME"));
    if (result.has_value()) {
        EXPECT_EQ(result.value(), CryptoSign::Backend::Type::GPGME);
    }
}

// Test: typeFromString with unknown string returns nullopt
TEST_F(CryptoSignFactoryTest_1965, TypeFromStringUnknownReturnsNullopt_1965) {
    auto result = CryptoSign::Factory::typeFromString(std::string_view("UNKNOWN_BACKEND"));
    EXPECT_FALSE(result.has_value());
}

// Test: typeFromString with empty string returns nullopt
TEST_F(CryptoSignFactoryTest_1965, TypeFromStringEmptyReturnsNullopt_1965) {
    auto result = CryptoSign::Factory::typeFromString(std::string_view(""));
    EXPECT_FALSE(result.has_value());
}

// Test: setPreferredBackend and getActive interaction
TEST_F(CryptoSignFactoryTest_1965, SetPreferredBackendAndGetActive_1965) {
    auto available = CryptoSign::Factory::getAvailable();
    if (!available.empty()) {
        CryptoSign::Factory::setPreferredBackend(available[0]);
        auto active = CryptoSign::Factory::getActive();
        EXPECT_TRUE(active.has_value());
        EXPECT_EQ(active.value(), available[0]);
    }
}

// Test: getActive returns a value when backends are available
TEST_F(CryptoSignFactoryTest_1965, GetActiveReturnsValueWhenAvailable_1965) {
    auto available = CryptoSign::Factory::getAvailable();
    auto active = CryptoSign::Factory::getActive();
    if (!available.empty()) {
        EXPECT_TRUE(active.has_value());
        // Active backend should be one of the available ones
        EXPECT_NE(std::find(available.begin(), available.end(), active.value()), available.end());
    }
}

// Test: createActive returns non-null when there is an active backend
TEST_F(CryptoSignFactoryTest_1965, CreateActiveReturnsNonNullWhenActive_1965) {
    auto active = CryptoSign::Factory::getActive();
    auto backend = CryptoSign::Factory::createActive();
    if (active.has_value()) {
        EXPECT_NE(backend, nullptr);
    } else {
        EXPECT_EQ(backend, nullptr);
    }
}

// Test: setPreferredBackend with NSS3 and verify getActive
TEST_F(CryptoSignFactoryTest_1965, SetPreferredNSS3_1965) {
    auto available = CryptoSign::Factory::getAvailable();
    bool nssAvailable = std::find(available.begin(), available.end(), CryptoSign::Backend::Type::NSS3) != available.end();
    
    if (nssAvailable) {
        CryptoSign::Factory::setPreferredBackend(CryptoSign::Backend::Type::NSS3);
        auto active = CryptoSign::Factory::getActive();
        EXPECT_TRUE(active.has_value());
        EXPECT_EQ(active.value(), CryptoSign::Backend::Type::NSS3);
    }
}

// Test: setPreferredBackend with GPGME and verify getActive
TEST_F(CryptoSignFactoryTest_1965, SetPreferredGPGME_1965) {
    auto available = CryptoSign::Factory::getAvailable();
    bool gpgmeAvailable = std::find(available.begin(), available.end(), CryptoSign::Backend::Type::GPGME) != available.end();
    
    if (gpgmeAvailable) {
        CryptoSign::Factory::setPreferredBackend(CryptoSign::Backend::Type::GPGME);
        auto active = CryptoSign::Factory::getActive();
        EXPECT_TRUE(active.has_value());
        EXPECT_EQ(active.value(), CryptoSign::Backend::Type::GPGME);
    }
}

// Test: createActive after setting preferred backend produces a valid object
TEST_F(CryptoSignFactoryTest_1965, CreateActiveAfterSetPreferred_1965) {
    auto available = CryptoSign::Factory::getAvailable();
    if (!available.empty()) {
        CryptoSign::Factory::setPreferredBackend(available[0]);
        auto backend = CryptoSign::Factory::createActive();
        EXPECT_NE(backend, nullptr);
    }
}

// Test: create each available backend and verify non-null
TEST_F(CryptoSignFactoryTest_1965, CreateEachAvailableBackend_1965) {
    auto available = CryptoSign::Factory::getAvailable();
    for (auto type : available) {
        auto backend = CryptoSign::Factory::create(type);
        EXPECT_NE(backend, nullptr) << "Backend type " << static_cast<int>(type) << " is available but create returned null";
    }
}

// Test: Backend::Type enum values are as expected
TEST_F(CryptoSignFactoryTest_1965, BackendTypeEnumValues_1965) {
    EXPECT_EQ(static_cast<int>(CryptoSign::Backend::Type::NSS3), 0);
    EXPECT_EQ(static_cast<int>(CryptoSign::Backend::Type::GPGME), 1);
}

// Test: Multiple calls to create return distinct objects
TEST_F(CryptoSignFactoryTest_1965, CreateReturnsFreshInstances_1965) {
    auto available = CryptoSign::Factory::getAvailable();
    if (!available.empty()) {
        auto b1 = CryptoSign::Factory::create(available[0]);
        auto b2 = CryptoSign::Factory::create(available[0]);
        EXPECT_NE(b1, nullptr);
        EXPECT_NE(b2, nullptr);
        EXPECT_NE(b1.get(), b2.get());
    }
}

// Test: Switching preferred backend between available types
TEST_F(CryptoSignFactoryTest_1965, SwitchPreferredBackend_1965) {
    auto available = CryptoSign::Factory::getAvailable();
    if (available.size() >= 2) {
        CryptoSign::Factory::setPreferredBackend(available[0]);
        auto active1 = CryptoSign::Factory::getActive();
        ASSERT_TRUE(active1.has_value());
        EXPECT_EQ(active1.value(), available[0]);

        CryptoSign::Factory::setPreferredBackend(available[1]);
        auto active2 = CryptoSign::Factory::getActive();
        ASSERT_TRUE(active2.has_value());
        EXPECT_EQ(active2.value(), available[1]);
    }
}
