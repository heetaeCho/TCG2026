#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "exiv2/pgfimage.hpp"
#include "exiv2/error.hpp"
#include "exiv2/basicio.hpp"

namespace Exiv2 {

class MockBasicIo : public BasicIo {
public:
    MOCK_METHOD(int, open, (), (override));
    MOCK_METHOD(int, close, (), (override));
    MOCK_METHOD(size_t, read, (byte * buf, size_t rcount), (override));
    MOCK_METHOD(size_t, write, (const byte * data, size_t wcount), (override));
    MOCK_METHOD(int, seek, (int64_t offset, Position pos), (override));
    MOCK_METHOD(bool, isopen, (), (const, override));
    MOCK_METHOD(const std::string&, path, (), (const, override));
    MOCK_METHOD(int, error, (), (const, override));
    MOCK_METHOD(bool, eof, (), (const, override));
    MOCK_METHOD(size_t, size, (), (const, override));
};

class PgfImageTest : public ::testing::Test {
protected:
    std::unique_ptr<MockBasicIo> mockIo;
    std::unique_ptr<PgfImage> pgfImage;

    void SetUp() override {
        mockIo = std::make_unique<MockBasicIo>();
        pgfImage = std::make_unique<PgfImage>(std::move(mockIo), true);
    }
};

TEST_F(PgfImageTest, ReadMetadata_Success) {
    // Arrange
    EXPECT_CALL(*mockIo, open()).WillOnce(testing::Return(0));  // Simulate successful open
    EXPECT_CALL(*mockIo, eof()).WillOnce(testing::Return(false));
    EXPECT_CALL(*mockIo, error()).WillOnce(testing::Return(0));

    // Act & Assert
    EXPECT_NO_THROW(pgfImage->readMetadata());
}

TEST_F(PgfImageTest, ReadMetadata_OpenFailure) {
    // Arrange
    EXPECT_CALL(*mockIo, open()).WillOnce(testing::Return(1));  // Simulate open failure

    // Act & Assert
    EXPECT_THROW(pgfImage->readMetadata(), Error);  // Expect ErrorCode::kerDataSourceOpenFailed
}

TEST_F(PgfImageTest, ReadMetadata_InvalidImageType) {
    // Arrange
    EXPECT_CALL(*mockIo, open()).WillOnce(testing::Return(0));  // Simulate successful open
    EXPECT_CALL(*mockIo, eof()).WillOnce(testing::Return(true));
    EXPECT_CALL(*mockIo, error()).WillOnce(testing::Return(0));

    // Act & Assert
    EXPECT_THROW(pgfImage->readMetadata(), Error);  // Expect ErrorCode::kerFailedToReadImageData
}

TEST_F(PgfImageTest, ReadMetadata_CorruptedData) {
    // Arrange
    EXPECT_CALL(*mockIo, open()).WillOnce(testing::Return(0));  // Simulate successful open
    EXPECT_CALL(*mockIo, error()).WillOnce(testing::Return(0));

    // Simulate corrupted header size
    EXPECT_CALL(*mockIo, eof()).WillOnce(testing::Return(false));

    // Act & Assert
    EXPECT_THROW(pgfImage->readMetadata(), Error);  // Expect ErrorCode::kerCorruptedMetadata
}

TEST_F(PgfImageTest, ReadMetadata_InsufficientData) {
    // Arrange
    EXPECT_CALL(*mockIo, open()).WillOnce(testing::Return(0));  // Simulate successful open
    EXPECT_CALL(*mockIo, error()).WillOnce(testing::Return(0));
    EXPECT_CALL(*mockIo, eof()).WillOnce(testing::Return(false));

    // Simulate insufficient data for image
    EXPECT_CALL(*mockIo, size()).WillOnce(testing::Return(100));
    EXPECT_CALL(*mockIo, tell()).WillOnce(testing::Return(90));

    // Act & Assert
    EXPECT_THROW(pgfImage->readMetadata(), Error);  // Expect ErrorCode::kerInputDataReadFailed
}

}  // namespace Exiv2