#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <optional>
#include <vector>
#include <string_view>
#include "./TestProjects/poppler/poppler/CryptoSignBackend.h" // Assuming header files are available for inclusion

namespace CryptoSign {
namespace Backend {
    class Type {
    public:
        enum class TypeEnum { NSS3 = 0, GPGME = 1 };
    };
}

class MockBackend : public CryptoSign::Backend {
public:
    MOCK_METHOD(void, someFunction, (), (override));
};

// Test the Factory::create method
TEST_F(CryptoSignFactoryTest_1965, CreateNSS3Backend_1965) {
    // Arrange
    // Assuming that ENABLE_NSS3 is defined for the test case, we'll mock the behavior accordingly

    // Act
    auto backend = CryptoSign::Factory::create(CryptoSign::Backend::Type::NSS3);

    // Assert
    EXPECT_NE(backend, nullptr); // Expect that the backend is created
}

TEST_F(CryptoSignFactoryTest_1966, CreateGPGMEBackend_1966) {
    // Arrange
    // Assuming that ENABLE_GPGME is defined for the test case, we'll mock the behavior accordingly

    // Act
    auto backend = CryptoSign::Factory::create(CryptoSign::Backend::Type::GPGME);

    // Assert
    EXPECT_NE(backend, nullptr); // Expect that the backend is created
}

TEST_F(CryptoSignFactoryTest_1967, CreateInvalidBackend_1967) {
    // Arrange
    // Providing a backend type that does not exist

    // Act
    auto backend = CryptoSign::Factory::create(static_cast<CryptoSign::Backend::Type::TypeEnum>(999));

    // Assert
    EXPECT_EQ(backend, nullptr); // Expect that the backend is nullptr
}

TEST_F(CryptoSignFactoryTest_1968, CreateBackendWhenDisabled_1968) {
    // Arrange
    // Assuming that ENABLE_NSS3 or ENABLE_GPGME is not defined for the test case

    // Act
    auto backend = CryptoSign::Factory::create(CryptoSign::Backend::Type::NSS3);

    // Assert
    EXPECT_EQ(backend, nullptr); // Expect that the backend is nullptr
}

TEST_F(CryptoSignFactoryTest_1969, GetAvailableBackends_1969) {
    // Arrange
    // Assuming that both NSS3 and GPGME are available
    std::vector<CryptoSign::Backend::Type::TypeEnum> expected_backends = {
        CryptoSign::Backend::Type::NSS3,
        CryptoSign::Backend::Type::GPGME
    };

    // Act
    auto available_backends = CryptoSign::Factory::getAvailable();

    // Assert
    EXPECT_EQ(available_backends, expected_backends); // Expect the available backends to match the expected list
}

TEST_F(CryptoSignFactoryTest_1970, SetPreferredBackend_1970) {
    // Arrange
    CryptoSign::Factory::setPreferredBackend(CryptoSign::Backend::Type::GPGME);

    // Act
    auto active_backend = CryptoSign::Factory::getActive();

    // Assert
    EXPECT_EQ(active_backend, CryptoSign::Backend::Type::GPGME); // Expect the active backend to match the preferred backend
}

TEST_F(CryptoSignFactoryTest_1971, TypeFromString_Valid_1971) {
    // Arrange
    std::string_view backend_str = "NSS3";

    // Act
    auto backend_type = CryptoSign::Factory::typeFromString(backend_str);

    // Assert
    EXPECT_EQ(backend_type, CryptoSign::Backend::Type::NSS3); // Expect that "NSS3" maps to the correct enum value
}

TEST_F(CryptoSignFactoryTest_1972, TypeFromString_Invalid_1972) {
    // Arrange
    std::string_view invalid_backend_str = "Invalid";

    // Act
    auto backend_type = CryptoSign::Factory::typeFromString(invalid_backend_str);

    // Assert
    EXPECT_EQ(backend_type, std::nullopt); // Expect that an invalid string returns std::nullopt
}

TEST_F(CryptoSignFactoryTest_1973, CreateActiveBackend_1973) {
    // Arrange
    CryptoSign::Factory::setPreferredBackend(CryptoSign::Backend::Type::NSS3);

    // Act
    auto active_backend = CryptoSign::Factory::createActive();

    // Assert
    EXPECT_NE(active_backend, nullptr); // Expect that the active backend is created
}