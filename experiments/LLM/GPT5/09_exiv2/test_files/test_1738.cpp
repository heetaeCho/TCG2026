#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include "exiv2/tiffimage.hpp"
#include "exiv2/error.hpp"

using namespace Exiv2;
using ::testing::_;
using ::testing::MockFunction;

class MockBasicIo : public BasicIo {
public:
    MOCK_METHOD(int, open, (), (override));
    MOCK_METHOD(int, close, (), (override));
    MOCK_METHOD(size_t, write, (const byte* data, size_t wcount), (override));
    MOCK_METHOD(int, seek, (int64_t offset, Position pos), (override));
    MOCK_METHOD(int, error, (), (const, override));
    MOCK_METHOD(bool, eof, (), (const, override));
    MOCK_METHOD(const std::string&, path, (), (const, override));
    MOCK_METHOD(void, populateFakeData, (), (override));
};

class TiffImageTest_1738 : public ::testing::Test {
protected:
    void SetUp() override {
        io_ = std::make_unique<MockBasicIo>();
        tiffImage_ = std::make_unique<TiffImage>(std::move(io_), true);
    }

    std::unique_ptr<MockBasicIo> io_;
    std::unique_ptr<TiffImage> tiffImage_;
};

TEST_F(TiffImageTest_1738, PrintStructure_ThrowsErrorWhenDataSourceOpenFails) {
    // Arrange
    EXPECT_CALL(*io_, open()).WillOnce(testing::Return(1)); // Simulate failure on open

    std::ostringstream out;
    // Act & Assert
    EXPECT_THROW(tiffImage_->printStructure(out, PrintStructureOption::None, 0), Error);
}

TEST_F(TiffImageTest_1738, PrintStructure_ThrowsErrorWhenImageIsNotTiff) {
    // Arrange
    EXPECT_CALL(*io_, open()).WillOnce(testing::Return(0)); // Simulate success on open
    EXPECT_CALL(*io_, error()).WillOnce(testing::Return(true)); // Simulate error
    EXPECT_CALL(*io_, eof()).WillOnce(testing::Return(false)); // Simulate not EOF

    std::ostringstream out;
    // Act & Assert
    EXPECT_THROW(tiffImage_->printStructure(out, PrintStructureOption::None, 0), Error);
}

TEST_F(TiffImageTest_1738, PrintStructure_ThrowsErrorWhenNotAJpeg) {
    // Arrange
    EXPECT_CALL(*io_, open()).WillOnce(testing::Return(0)); // Simulate success on open
    EXPECT_CALL(*io_, error()).WillOnce(testing::Return(false)); // Simulate no error
    EXPECT_CALL(*io_, eof()).WillOnce(testing::Return(false)); // Simulate not EOF

    std::ostringstream out;
    // Act & Assert
    EXPECT_THROW(tiffImage_->printStructure(out, PrintStructureOption::None, 0), Error);
}

TEST_F(TiffImageTest_1738, PrintStructure_SuccessfulExecution) {
    // Arrange
    EXPECT_CALL(*io_, open()).WillOnce(testing::Return(0)); // Simulate success on open
    EXPECT_CALL(*io_, error()).WillOnce(testing::Return(false)); // Simulate no error
    EXPECT_CALL(*io_, eof()).WillOnce(testing::Return(false)); // Simulate not EOF

    std::ostringstream out;
    // Act & Assert
    EXPECT_NO_THROW(tiffImage_->printStructure(out, PrintStructureOption::None, 0));
}