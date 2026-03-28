#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "exiv2/pgfimage.hpp"
#include "exiv2/basicio.hpp"
#include "exiv2/error.hpp"

// Mock class for BasicIo to simulate the external behavior of I/O operations.
class MockBasicIo : public Exiv2::BasicIo {
public:
    MOCK_METHOD(int, open, (), (override));
    MOCK_METHOD(int, close, (), (override));
    MOCK_METHOD(size_t, write, (const byte* data, size_t wcount), (override));
    MOCK_METHOD(int, putb, (byte data), (override));
    MOCK_METHOD(Exiv2::DataBuf, read, (size_t rcount), (override));
    MOCK_METHOD(int, getb, (), (override));
    MOCK_METHOD(void, transfer, (Exiv2::BasicIo& src), (override));
    MOCK_METHOD(int, seek, (int64_t offset, Exiv2::Position pos), (override));
    MOCK_METHOD(size_t, tell, (), (const override));
    MOCK_METHOD(size_t, size, (), (const override));
    MOCK_METHOD(bool, isopen, (), (const override));
    MOCK_METHOD(int, error, (), (const override));
    MOCK_METHOD(bool, eof, (), (const override));
    MOCK_METHOD(const std::string&, path, (), (const override));
};

// Test fixture class
class PgfImageTest : public ::testing::Test {
protected:
    std::unique_ptr<MockBasicIo> mockIo;
    std::unique_ptr<Exiv2::PgfImage> pgfImage;

    void SetUp() override {
        mockIo = std::make_unique<MockBasicIo>();
        pgfImage = std::make_unique<Exiv2::PgfImage>(std::move(mockIo), true);
    }
};

// TEST_ID 1712: Normal operation of writeMetadata method
TEST_F(PgfImageTest, WriteMetadata_Success_1712) {
    // Setup mock behaviors for the I/O operations
    EXPECT_CALL(*mockIo, open()).WillOnce(::testing::Return(0));  // Simulate successful open
    EXPECT_CALL(*mockIo, close()).WillOnce(::testing::Return(0));  // Simulate successful close
    EXPECT_CALL(*mockIo, transfer(::testing::_)).Times(1);        // Verify transfer call

    // Execute the function under test
    EXPECT_NO_THROW(pgfImage->writeMetadata());
}

// TEST_ID 1713: Error case when open() fails in writeMetadata
TEST_F(PgfImageTest, WriteMetadata_OpenFailed_1713) {
    // Setup mock to simulate open failure
    EXPECT_CALL(*mockIo, open()).WillOnce(::testing::Return(1));  // Simulate failed open

    // Verify that the expected error is thrown
    EXPECT_THROW(pgfImage->writeMetadata(), Exiv2::Error);
}

// TEST_ID 1714: Boundary condition when writeMetadata is called with minimal valid data
TEST_F(PgfImageTest, WriteMetadata_MinimalData_1714) {
    // Setup mock to simulate successful open and close
    EXPECT_CALL(*mockIo, open()).WillOnce(::testing::Return(0));  // Simulate successful open
    EXPECT_CALL(*mockIo, close()).WillOnce(::testing::Return(0)); // Simulate successful close
    EXPECT_CALL(*mockIo, transfer(::testing::_)).Times(1);        // Verify transfer call

    // Execute the function under test (minimal data, no actual data manipulation)
    EXPECT_NO_THROW(pgfImage->writeMetadata());
}

// TEST_ID 1715: Boundary condition when io_ is already closed
TEST_F(PgfImageTest, WriteMetadata_AlreadyClosed_1715) {
    // Setup mock to simulate closed I/O
    EXPECT_CALL(*mockIo, open()).WillOnce(::testing::Return(0));  // Simulate successful open
    EXPECT_CALL(*mockIo, close()).WillOnce(::testing::Return(0)); // Simulate successful close
    EXPECT_CALL(*mockIo, transfer(::testing::_)).Times(1);        // Verify transfer call

    pgfImage->writeMetadata();  // First successful call

    // Now simulate a closed I/O by calling writeMetadata again
    EXPECT_CALL(*mockIo, open()).WillOnce(::testing::Return(1));  // Simulate failed open
    EXPECT_THROW(pgfImage->writeMetadata(), Exiv2::Error);        // Expecting error due to already closed I/O
}

// TEST_ID 1716: Verifying external interaction (write, transfer) with mocked Io
TEST_F(PgfImageTest, WriteMetadata_ExternalInteraction_1716) {
    // Setup mock to simulate successful open and close
    EXPECT_CALL(*mockIo, open()).WillOnce(::testing::Return(0));  // Simulate successful open
    EXPECT_CALL(*mockIo, close()).WillOnce(::testing::Return(0)); // Simulate successful close
    EXPECT_CALL(*mockIo, transfer(::testing::_)).Times(1);        // Verify transfer call
    EXPECT_CALL(*mockIo, write(::testing::_, ::testing::_)).Times(1);  // Simulate a write operation

    // Execute the function under test
    EXPECT_NO_THROW(pgfImage->writeMetadata());
}