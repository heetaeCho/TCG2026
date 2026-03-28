#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <cmath>
#include <string>

namespace Exiv2 { namespace Internal {

class Nikon3MakerNoteTest : public ::testing::Test {
protected:
    Nikon3MakerNote makerNote;
};

// Mock classes to simulate the external dependencies
class MockValue {
public:
    MOCK_METHOD(int, count, (), (const));
    MOCK_METHOD(int, typeId, (), (const));
    MOCK_METHOD(int64_t, toInt64, (), (const));
};

class MockExifData {};

TEST_F(Nikon3MakerNoteTest, printFocal_ValidSingleValue_ReturnsFormattedString_479) {
    // Arrange
    std::stringstream os;
    MockValue value;
    MockExifData exifData;

    EXPECT_CALL(value, count()).WillOnce(testing::Return(1));
    EXPECT_CALL(value, typeId()).WillOnce(testing::Return(0));  // unsignedByte
    EXPECT_CALL(value, toInt64()).WillOnce(testing::Return(4));

    // Act
    makerNote.printFocal(os, value, &exifData);

    // Assert
    EXPECT_EQ(os.str(), "{:.1f} mm");  // Expected output with val == 4
}

TEST_F(Nikon3MakerNoteTest, printFocal_ValidZeroValue_ReturnsNA_480) {
    // Arrange
    std::stringstream os;
    MockValue value;
    MockExifData exifData;

    EXPECT_CALL(value, count()).WillOnce(testing::Return(1));
    EXPECT_CALL(value, typeId()).WillOnce(testing::Return(0));  // unsignedByte
    EXPECT_CALL(value, toInt64()).WillOnce(testing::Return(0));

    // Act
    makerNote.printFocal(os, value, &exifData);

    // Assert
    EXPECT_EQ(os.str(), "n/a");
}

TEST_F(Nikon3MakerNoteTest, printFocal_InvalidCount_ReturnsRawValue_481) {
    // Arrange
    std::stringstream os;
    MockValue value;
    MockExifData exifData;

    EXPECT_CALL(value, count()).WillOnce(testing::Return(2));  // Invalid count
    EXPECT_CALL(value, typeId()).WillOnce(testing::Return(0));  // unsignedByte
    EXPECT_CALL(value, toInt64()).Times(0);  // Should not be called due to invalid count

    // Act
    makerNote.printFocal(os, value, &exifData);

    // Assert
    EXPECT_EQ(os.str(), "(0)");  // Raw value due to invalid count
}

TEST_F(Nikon3MakerNoteTest, printFocal_InvalidType_ReturnsRawValue_482) {
    // Arrange
    std::stringstream os;
    MockValue value;
    MockExifData exifData;

    EXPECT_CALL(value, count()).WillOnce(testing::Return(1));
    EXPECT_CALL(value, typeId()).WillOnce(testing::Return(1));  // Invalid type
    EXPECT_CALL(value, toInt64()).Times(0);  // Should not be called due to invalid type

    // Act
    makerNote.printFocal(os, value, &exifData);

    // Assert
    EXPECT_EQ(os.str(), "(0)");  // Raw value due to invalid type
}

TEST_F(Nikon3MakerNoteTest, printFocal_ValidFormattedFocalLength_483) {
    // Arrange
    std::stringstream os;
    MockValue value;
    MockExifData exifData;

    EXPECT_CALL(value, count()).WillOnce(testing::Return(1));
    EXPECT_CALL(value, typeId()).WillOnce(testing::Return(0));  // unsignedByte
    EXPECT_CALL(value, toInt64()).WillOnce(testing::Return(5));

    // Act
    makerNote.printFocal(os, value, &exifData);

    // Assert
    double expectedFocalLength = 5.0 * std::exp2(5 / 24.0);  // Calculation based on the formula
    EXPECT_EQ(os.str(), "{:.1f} mm" + std::to_string(expectedFocalLength));
}

} }  // namespace Exiv2::Internal