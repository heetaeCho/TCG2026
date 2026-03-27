#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "exiv2/jpgimage.hpp"
#include "exiv2/basicio.hpp"

using namespace Exiv2;

class BasicIoMock : public BasicIo {
public:
    MOCK_METHOD(size_t, write, (const byte* data, size_t wcount), (override));
    MOCK_METHOD(size_t, read, (byte* buf, size_t rcount), (override));
    MOCK_METHOD(int, open, (), (override));
    MOCK_METHOD(int, close, (), (override));
    MOCK_METHOD(int, getb, (), (override));
    MOCK_METHOD(void, seekOrThrow, (int64_t offset, Position pos, ErrorCode err), (override));
    MOCK_METHOD(const size_t, tell, (), (override));
    MOCK_METHOD(const size_t, size, (), (override));
    MOCK_METHOD(const bool, isopen, (), (override));
    MOCK_METHOD(const int, error, (), (override));
    MOCK_METHOD(const bool, eof, (), (override));
    MOCK_METHOD(const std::string&, path, (), (override));
    MOCK_METHOD(void, populateFakeData, (), (override));
};

class ExvImageTest : public ::testing::Test {
protected:
    std::unique_ptr<BasicIoMock> mockIo;
    ExvImageTest() : mockIo(std::make_unique<BasicIoMock>()) {}
};

TEST_F(ExvImageTest, isThisType_ReturnsTrue_WhenValidType) {
    // Arrange
    EXPECT_CALL(*mockIo, read(testing::_, testing::_)).WillOnce(testing::Return(1));
    ExvImage exvImage(std::move(mockIo), true);

    // Act
    bool result = exvImage.isThisType(*mockIo, true);

    // Assert
    EXPECT_TRUE(result);
    // TEST_ID: 1227
}

TEST_F(ExvImageTest, isThisType_ReturnsFalse_WhenInvalidType) {
    // Arrange
    EXPECT_CALL(*mockIo, read(testing::_, testing::_)).WillOnce(testing::Return(0));
    ExvImage exvImage(std::move(mockIo), true);

    // Act
    bool result = exvImage.isThisType(*mockIo, false);

    // Assert
    EXPECT_FALSE(result);
    // TEST_ID: 1228
}

TEST_F(ExvImageTest, mimeType_ReturnsCorrectMimeType) {
    // Arrange
    ExvImage exvImage(std::move(mockIo), true);

    // Act
    std::string mimeType = exvImage.mimeType();

    // Assert
    EXPECT_EQ(mimeType, "image/exv");
    // TEST_ID: 1229
}

TEST_F(ExvImageTest, writeHeader_Succeeds_WhenValidData) {
    // Arrange
    EXPECT_CALL(*mockIo, write(testing::_, testing::_)).WillOnce(testing::Return(10));
    ExvImage exvImage(std::move(mockIo), true);

    // Act
    int result = exvImage.writeHeader(*mockIo);

    // Assert
    EXPECT_EQ(result, 10);
    // TEST_ID: 1230
}

TEST_F(ExvImageTest, writeHeader_Fails_WhenInvalidData) {
    // Arrange
    EXPECT_CALL(*mockIo, write(testing::_, testing::_)).WillOnce(testing::Return(0));
    ExvImage exvImage(std::move(mockIo), true);

    // Act
    int result = exvImage.writeHeader(*mockIo);

    // Assert
    EXPECT_EQ(result, 0);
    // TEST_ID: 1231
}