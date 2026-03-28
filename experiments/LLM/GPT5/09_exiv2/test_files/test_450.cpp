#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include "nikonmn_int.hpp"  // Include the header for Nikon1MakerNote and Value class

namespace Exiv2 {
namespace Internal {

// Mocking the Value class for our tests
class MockValue {
public:
    MOCK_METHOD(int, count, (), (const));
    MOCK_METHOD(int64_t, toInt64, (int), (const));
    MOCK_METHOD(std::string, toString, (), (const));
};

// Test fixture for Nikon1MakerNote
class Nikon1MakerNoteTest : public testing::Test {
protected:
    Nikon1MakerNote makerNote;
    std::ostringstream os;
    MockValue value;
    const ExifData* exifData = nullptr;  // Assuming ExifData is not used in the provided method
};

TEST_F(Nikon1MakerNoteTest, Print0x0002SingleValue_450) {
    // Arrange
    EXPECT_CALL(value, count()).WillOnce(testing::Return(1));
    EXPECT_CALL(value, toString()).WillOnce(testing::Return("test"));

    // Act
    makerNote.print0x0002(os, value, exifData);

    // Assert
    EXPECT_EQ(os.str(), "(test)");
}

TEST_F(Nikon1MakerNoteTest, Print0x0002MultipleValues_451) {
    // Arrange
    EXPECT_CALL(value, count()).WillOnce(testing::Return(2));
    EXPECT_CALL(value, toInt64(1)).WillOnce(testing::Return(12345));

    // Act
    makerNote.print0x0002(os, value, exifData);

    // Assert
    EXPECT_EQ(os.str(), "12345");
}

TEST_F(Nikon1MakerNoteTest, Print0x0002ZeroCount_452) {
    // Arrange
    EXPECT_CALL(value, count()).WillOnce(testing::Return(0));

    // Act
    makerNote.print0x0002(os, value, exifData);

    // Assert
    // This assumes there is no valid output for count() == 0, so we expect an empty string.
    EXPECT_EQ(os.str(), "");
}

TEST_F(Nikon1MakerNoteTest, Print0x0002NegativeToInt64_453) {
    // Arrange
    EXPECT_CALL(value, count()).WillOnce(testing::Return(2));
    EXPECT_CALL(value, toInt64(1)).WillOnce(testing::Return(-987654));

    // Act
    makerNote.print0x0002(os, value, exifData);

    // Assert
    EXPECT_EQ(os.str(), "-987654");
}

}  // namespace Internal
}  // namespace Exiv2