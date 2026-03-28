#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "CryptoSignBackend.h" // Include necessary header files

namespace Poppler {

class MockCryptoSignFactory : public CryptoSign::Factory {
public:
    MOCK_METHOD(void, setPreferredBackend, (CryptoSign::Backend::Type backend), (override));
    MOCK_METHOD(std::optional<CryptoSign::Backend::Type>, getActive, (), (override));
    MOCK_METHOD(std::vector<CryptoSign::Backend::Type>, getAvailable, (), (override));
    MOCK_METHOD(std::unique_ptr<CryptoSign::Backend>, createActive, (), (override));
    MOCK_METHOD(std::unique_ptr<CryptoSign::Backend>, create, (CryptoSign::Backend::Type backend), (override));
};

class SetActiveCryptoSignBackendTest_1375 : public ::testing::Test {
protected:
    MockCryptoSignFactory mockFactory;
};

TEST_F(SetActiveCryptoSignBackendTest_1375, SetActiveCryptoSignBackend_Success_1375) {
    // Setup: Assume available backends contain the desired one, and the conversion is successful
    CryptoSign::Backend::Type desiredBackend = CryptoSign::Backend::Type::SomeBackend;

    EXPECT_CALL(mockFactory, getAvailable())
        .WillOnce(testing::Return(std::vector<CryptoSign::Backend::Type>{desiredBackend}));

    EXPECT_CALL(mockFactory, create(desiredBackend))
        .WillOnce(testing::Return(std::make_unique<CryptoSign::Backend>()));

    EXPECT_CALL(mockFactory, setPreferredBackend(desiredBackend))
        .Times(1);

    bool result = setActiveCryptoSignBackend(desiredBackend);
    
    EXPECT_TRUE(result);  // Should return true when successful
}

TEST_F(SetActiveCryptoSignBackendTest_1375, SetActiveCryptoSignBackend_BackendNotAvailable_1375) {
    // Setup: Assume desired backend is not available
    CryptoSign::Backend::Type unavailableBackend = CryptoSign::Backend::Type::SomeBackend;

    EXPECT_CALL(mockFactory, getAvailable())
        .WillOnce(testing::Return(std::vector<CryptoSign::Backend::Type>{}));

    bool result = setActiveCryptoSignBackend(unavailableBackend);

    EXPECT_FALSE(result);  // Should return false when backend is not available
}

TEST_F(SetActiveCryptoSignBackendTest_1375, SetActiveCryptoSignBackend_ConversionFails_1375) {
    // Setup: Assume conversion to the backend fails
    CryptoSign::Backend::Type desiredBackend = CryptoSign::Backend::Type::SomeBackend;

    EXPECT_CALL(mockFactory, getAvailable())
        .WillOnce(testing::Return(std::vector<CryptoSign::Backend::Type>{desiredBackend}));

    EXPECT_CALL(mockFactory, create(desiredBackend))
        .WillOnce(testing::Return(nullptr));  // Simulate conversion failure

    bool result = setActiveCryptoSignBackend(desiredBackend);

    EXPECT_FALSE(result);  // Should return false when conversion fails
}

TEST_F(SetActiveCryptoSignBackendTest_1375, SetActiveCryptoSignBackend_SuccessAfterConversion_1375) {
    // Setup: Assume successful conversion and setting of backend
    CryptoSign::Backend::Type desiredBackend = CryptoSign::Backend::Type::SomeBackend;

    EXPECT_CALL(mockFactory, getAvailable())
        .WillOnce(testing::Return(std::vector<CryptoSign::Backend::Type>{desiredBackend}));

    EXPECT_CALL(mockFactory, create(desiredBackend))
        .WillOnce(testing::Return(std::make_unique<CryptoSign::Backend>()));

    EXPECT_CALL(mockFactory, setPreferredBackend(desiredBackend))
        .Times(1);

    bool result = setActiveCryptoSignBackend(desiredBackend);
    
    EXPECT_TRUE(result);  // Should return true when successful
}

} // namespace Poppler