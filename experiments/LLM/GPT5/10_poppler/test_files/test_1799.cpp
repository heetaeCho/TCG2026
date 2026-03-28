#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Mocking external dependencies if needed
// (No external dependencies were identified in the provided code)

extern "C" {
    typedef struct SECItem {
        void* data;
    } SECItem;

    typedef struct NSSCMSMessage {} NSSCMSMessage;

    // The function being tested
    NSSCMSMessage* CMS_MessageCreate(SECItem* cms_item);
}

class NSSCryptoSignBackendTest_1799 : public ::testing::Test {
protected:
    // Optional: Setup/teardown if needed
    void SetUp() override {
        // Any setup if needed
    }

    void TearDown() override {
        // Any cleanup if needed
    }
};

// Test normal operation
TEST_F(NSSCryptoSignBackendTest_1799, CMS_MessageCreate_ReturnsMessage_WhenDataIsNotNull_1799) {
    // Arrange
    SECItem cms_item;
    void* mock_data = reinterpret_cast<void*>(0x1234); // Mock data pointer
    cms_item.data = mock_data;

    // Act
    NSSCMSMessage* result = CMS_MessageCreate(&cms_item);

    // Assert
    EXPECT_NE(result, nullptr); // If data is not null, the result should not be nullptr
}

// Test boundary condition: data is null
TEST_F(NSSCryptoSignBackendTest_1799, CMS_MessageCreate_ReturnsNull_WhenDataIsNull_1799) {
    // Arrange
    SECItem cms_item;
    cms_item.data = nullptr;

    // Act
    NSSCMSMessage* result = CMS_MessageCreate(&cms_item);

    // Assert
    EXPECT_EQ(result, nullptr); // If data is null, the result should be nullptr
}

// Test exceptional/error case (although no clear exceptional case is provided, if the interface allows for null data, this can be considered an error)
TEST_F(NSSCryptoSignBackendTest_1799, CMS_MessageCreate_HandlesNullDataGracefully_1799) {
    // Arrange
    SECItem cms_item;
    cms_item.data = nullptr;

    // Act
    NSSCMSMessage* result = CMS_MessageCreate(&cms_item);

    // Assert
    EXPECT_EQ(result, nullptr); // Ensure that the system returns nullptr when the data is null
}