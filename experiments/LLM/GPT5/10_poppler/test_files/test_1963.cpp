#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <optional>
#include <vector>
#include <string_view>

namespace CryptoSign {
    class Backend {
    public:
        enum class Type { TYPE_1, TYPE_2, TYPE_3 }; // Example types for Backend::Type
    };

    class Factory {
    public:
        static void setPreferredBackend(CryptoSign::Backend::Type backend) {
            // Simulated logic
        }

        static std::optional<CryptoSign::Backend::Type> getActive() {
            // Simulated logic
            return CryptoSign::Backend::Type::TYPE_1; // For example
        }

        static std::vector<CryptoSign::Backend::Type> getAvailable() {
            static std::vector<CryptoSign::Backend::Type> availableBackends = createAvailableBackends();
            return availableBackends;
        }

        static std::unique_ptr<CryptoSign::Backend> createActive() {
            // Simulated logic
            return std::make_unique<CryptoSign::Backend>();
        }

        static std::unique_ptr<CryptoSign::Backend> create(CryptoSign::Backend::Type backend) {
            // Simulated logic
            return std::make_unique<CryptoSign::Backend>();
        }

        static std::optional<CryptoSign::Backend::Type> typeFromString(std::string_view string) {
            // Simulated logic
            if (string == "TYPE_1") return CryptoSign::Backend::Type::TYPE_1;
            if (string == "TYPE_2") return CryptoSign::Backend::Type::TYPE_2;
            return std::nullopt;
        }

        static std::optional<CryptoSign::Backend::Type> typeFromString(int number) {
            // Simulated logic
            if (number == 1) return CryptoSign::Backend::Type::TYPE_1;
            if (number == 2) return CryptoSign::Backend::Type::TYPE_2;
            return std::nullopt;
        }

    private:
        static std::vector<CryptoSign::Backend::Type> createAvailableBackends() {
            return { CryptoSign::Backend::Type::TYPE_1, CryptoSign::Backend::Type::TYPE_2 };
        }
    };
}

using namespace CryptoSign;

TEST_F(FactoryTest_1963, GetAvailableBackends_1963) {
    std::vector<Backend::Type> availableBackends = Factory::getAvailable();

    ASSERT_EQ(availableBackends.size(), 2);
    EXPECT_EQ(availableBackends[0], Backend::Type::TYPE_1);
    EXPECT_EQ(availableBackends[1], Backend::Type::TYPE_2);
}

TEST_F(FactoryTest_1963, SetPreferredBackend_1963) {
    Factory::setPreferredBackend(Backend::Type::TYPE_1);

    std::optional<Backend::Type> activeBackend = Factory::getActive();
    ASSERT_TRUE(activeBackend.has_value());
    EXPECT_EQ(activeBackend.value(), Backend::Type::TYPE_1);
}

TEST_F(FactoryTest_1963, TypeFromStringValid_1963) {
    std::optional<Backend::Type> type = Factory::typeFromString("TYPE_1");

    ASSERT_TRUE(type.has_value());
    EXPECT_EQ(type.value(), Backend::Type::TYPE_1);
}

TEST_F(FactoryTest_1963, TypeFromStringInvalid_1963) {
    std::optional<Backend::Type> type = Factory::typeFromString("INVALID_TYPE");

    ASSERT_FALSE(type.has_value());
}

TEST_F(FactoryTest_1963, TypeFromIntValid_1963) {
    std::optional<Backend::Type> type = Factory::typeFromString(1);

    ASSERT_TRUE(type.has_value());
    EXPECT_EQ(type.value(), Backend::Type::TYPE_1);
}

TEST_F(FactoryTest_1963, TypeFromIntInvalid_1963) {
    std::optional<Backend::Type> type = Factory::typeFromString(99);

    ASSERT_FALSE(type.has_value());
}

TEST_F(FactoryTest_1963, CreateActiveBackend_1963) {
    auto backend = Factory::createActive();

    ASSERT_NE(backend, nullptr);
}

TEST_F(FactoryTest_1963, CreateBackendWithType_1963) {
    auto backend = Factory::create(Backend::Type::TYPE_2);

    ASSERT_NE(backend, nullptr);
}