#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "./TestProjects/poppler/poppler/FileSpec.h"

// Mocking the GooString class for testing purposes
class MockGooString : public GooString {
public:
    MOCK_CONST_METHOD0(c_str, const char*());
};

// Test fixture for EmbFile
class EmbFileTest_1127 : public ::testing::Test {
protected:
    EmbFileTest_1127() = default;
    ~EmbFileTest_1127() override = default;

    // Mocked GooString for modDate and createDate
    std::unique_ptr<MockGooString> modDateMock;
    std::unique_ptr<MockGooString> createDateMock;

    // Setting up test data
    void SetUp() override {
        modDateMock = std::make_unique<MockGooString>();
        createDateMock = std::make_unique<MockGooString>();
    }

    void TearDown() override {
        // Cleanup if needed
    }
};

// Test Case 1: Normal operation for modDate()
TEST_F(EmbFileTest_1127, ModDateReturnsCorrectValue_1127) {
    // Arrange
    EmbFile embFile(std::move(mockObject));
    EXPECT_CALL(*modDateMock, c_str()).WillOnce(testing::Return("2026-02-16"));

    // Act
    const GooString* result = embFile.modDate();

    // Assert
    EXPECT_EQ(result->c_str(), "2026-02-16");
}

// Test Case 2: Normal operation for createDate()
TEST_F(EmbFileTest_1127, CreateDateReturnsCorrectValue_1127) {
    // Arrange
    EmbFile embFile(std::move(mockObject));
    EXPECT_CALL(*createDateMock, c_str()).WillOnce(testing::Return("2026-02-01"));

    // Act
    const GooString* result = embFile.createDate();

    // Assert
    EXPECT_EQ(result->c_str(), "2026-02-01");
}

// Test Case 3: Exceptional case for modDate() (return null if uninitialized)
TEST_F(EmbFileTest_1127, ModDateReturnsNullWhenUninitialized_1127) {
    // Arrange
    EmbFile embFile(std::move(mockObject));
    EXPECT_CALL(*modDateMock, c_str()).WillOnce(testing::Return(nullptr));

    // Act
    const GooString* result = embFile.modDate();

    // Assert
    EXPECT_EQ(result, nullptr);
}

// Test Case 4: Verify that save function is called correctly (mock external interaction)
TEST_F(EmbFileTest_1127, SaveCalledCorrectly_1127) {
    // Arrange
    EmbFile embFile(std::move(mockObject));
    EXPECT_CALL(embFile, save(testing::_)).WillOnce(testing::Return(true));

    // Act
    bool result = embFile.save("test_path");

    // Assert
    EXPECT_TRUE(result);
}

// Test Case 5: Verify isOk() returns true (assuming success scenario)
TEST_F(EmbFileTest_1127, IsOkReturnsTrue_1127) {
    // Arrange
    EmbFile embFile(std::move(mockObject));
    
    // Act
    bool result = embFile.isOk();

    // Assert
    EXPECT_TRUE(result);
}