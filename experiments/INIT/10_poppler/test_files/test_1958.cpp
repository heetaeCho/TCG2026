#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <optional>
#include <vector>
#include <string_view>
#include <memory>

// Mock Backend class
namespace CryptoSign {
    class Backend {
    public:
        enum class Type {
            UNKNOWN,
            BACKEND_A,
            BACKEND_B
        };
    };
}

// Mocked Factory class for testing
namespace CryptoSign {

    class Factory {
    public:
        static void setPreferredBackend(CryptoSign::Backend::Type backend) {
            preferredBackend = backend;
        }

        static std::optional<Backend::Type> getActive() {
            return preferredBackend;
        }

        static std::vector<Backend::Type> getAvailable() {
            return {Backend::Type::BACKEND_A, Backend::Type::BACKEND_B};
        }

        static std::unique_ptr<Backend> createActive() {
            return create(preferredBackend);
        }

        static std::unique_ptr<Backend> create(Backend::Type backend) {
            return std::make_unique<Backend>();
        }

        static std::optional<Backend::Type> typeFromString(std::string_view string) {
            if (string == "BACKEND_A") {
                return Backend::Type::BACKEND_A;
            }
            if (string == "BACKEND_B") {
                return Backend::Type::BACKEND_B;
            }
            return std::nullopt;
        }

        static std::optional<Backend::Type> typeFromString(int val) {
            if (val == 1) {
                return Backend::Type::BACKEND_A;
            }
            if (val == 2) {
                return Backend::Type::BACKEND_B;
            }
            return std::nullopt;
        }

    private:
        static Backend::Type preferredBackend;
    };

    // Static member initialization
    CryptoSign::Backend::Type Factory::preferredBackend = Backend::Type::UNKNOWN;
}

// Test suite for CryptoSign::Factory
class CryptoSignFactoryTest : public ::testing::Test {};

// TEST_ID 1958
TEST_F(CryptoSignFactoryTest, SetPreferredBackend_ValidType_1958) {
    // Test for normal operation where the backend is set correctly
    CryptoSign::Factory::setPreferredBackend(CryptoSign::Backend::Type::BACKEND_A);

    auto activeBackend = CryptoSign::Factory::getActive();
    EXPECT_TRUE(activeBackend.has_value());
    EXPECT_EQ(activeBackend.value(), CryptoSign::Backend::Type::BACKEND_A);
}

// TEST_ID 1959
TEST_F(CryptoSignFactoryTest, SetPreferredBackend_InvalidType_1959) {
    // Test for setting an invalid backend and checking that no active backend is set
    CryptoSign::Factory::setPreferredBackend(CryptoSign::Backend::Type::UNKNOWN);

    auto activeBackend = CryptoSign::Factory::getActive();
    EXPECT_TRUE(!activeBackend.has_value());
}

// TEST_ID 1960
TEST_F(CryptoSignFactoryTest, GetAvailableBackends_1958) {
    // Test for getting available backends
    auto availableBackends = CryptoSign::Factory::getAvailable();
    EXPECT_EQ(availableBackends.size(), 2);
    EXPECT_EQ(availableBackends[0], CryptoSign::Backend::Type::BACKEND_A);
    EXPECT_EQ(availableBackends[1], CryptoSign::Backend::Type::BACKEND_B);
}

// TEST_ID 1961
TEST_F(CryptoSignFactoryTest, CreateActiveBackend_1958) {
    // Test for creating an active backend based on the preferred backend
    CryptoSign::Factory::setPreferredBackend(CryptoSign::Backend::Type::BACKEND_B);
    auto backend = CryptoSign::Factory::createActive();
    EXPECT_NE(backend, nullptr);
}

// TEST_ID 1962
TEST_F(CryptoSignFactoryTest, CreateBackendFromType_Valid_1958) {
    // Test for creating a backend of a specific type
    auto backend = CryptoSign::Factory::create(CryptoSign::Backend::Type::BACKEND_A);
    EXPECT_NE(backend, nullptr);
}

// TEST_ID 1963
TEST_F(CryptoSignFactoryTest, TypeFromString_Valid_1958) {
    // Test for converting string to backend type
    auto type = CryptoSign::Factory::typeFromString("BACKEND_A");
    EXPECT_TRUE(type.has_value());
    EXPECT_EQ(type.value(), CryptoSign::Backend::Type::BACKEND_A);
}

// TEST_ID 1964
TEST_F(CryptoSignFactoryTest, TypeFromString_Invalid_1958) {
    // Test for invalid string conversion to backend type
    auto type = CryptoSign::Factory::typeFromString("INVALID_BACKEND");
    EXPECT_FALSE(type.has_value());
}

// TEST_ID 1965
TEST_F(CryptoSignFactoryTest, TypeFromInt_Valid_1958) {
    // Test for converting integer to backend type
    auto type = CryptoSign::Factory::typeFromString(1);
    EXPECT_TRUE(type.has_value());
    EXPECT_EQ(type.value(), CryptoSign::Backend::Type::BACKEND_A);
}

// TEST_ID 1966
TEST_F(CryptoSignFactoryTest, TypeFromInt_Invalid_1958) {
    // Test for invalid integer conversion to backend type
    auto type = CryptoSign::Factory::typeFromString(99);
    EXPECT_FALSE(type.has_value());
}