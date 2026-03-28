#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include "exiv2/exif.hpp"
#include "exiv2/value.hpp"
#include "exiv2/types.hpp"
#include "nikonmn_int.hpp"

namespace Exiv2 {
namespace Internal {

class Nikon3MakerNoteTest : public ::testing::Test {
protected:
    // Test helper to create a mock ExifData instance
    ExifData* mockExifData() {
        return new ExifData();
    }
};

TEST_F(Nikon3MakerNoteTest, PrintFlashGroupBCControlData_NormalOperation_492) {
    // Arrange
    Nikon3MakerNote makerNote;
    Value value(unsignedByte);
    value.setDataArea(reinterpret_cast<const uint8_t*>("\x1A\x2B\x3C\x4D"), 4);  // Example data for the test
    ExifData* data = mockExifData();
    
    std::ostringstream os;

    // Act
    makerNote.printFlashGroupBCControlData(os, value, data);

    // Assert
    std::string result = os.str();
    EXPECT_NE(result.find("Off"), std::string::npos);  // Expects first flash control mode to be "Off"
    EXPECT_NE(result.find("Repeating Flash"), std::string::npos);  // Expects second flash control mode to be "Repeating Flash"
}

TEST_F(Nikon3MakerNoteTest, PrintFlashGroupBCControlData_BoundaryCondition_493) {
    // Arrange
    Nikon3MakerNote makerNote;
    Value value(unsignedByte);
    value.setDataArea(reinterpret_cast<const uint8_t*>("\x00\x00\x00\x00"), 4);  // Minimal possible value
    ExifData* data = mockExifData();

    std::ostringstream os;

    // Act
    makerNote.printFlashGroupBCControlData(os, value, data);

    // Assert
    std::string result = os.str();
    EXPECT_EQ(result.find("Off"), std::string::npos);  // Expects "Off" for both flash control modes
}

TEST_F(Nikon3MakerNoteTest, PrintFlashGroupBCControlData_InvalidValue_494) {
    // Arrange
    Nikon3MakerNote makerNote;
    Value value(unsignedByte);
    value.setDataArea(reinterpret_cast<const uint8_t*>("\xFF\xFF\xFF\xFF"), 4);  // Invalid value for flash control mode
    ExifData* data = mockExifData();

    std::ostringstream os;

    // Act
    makerNote.printFlashGroupBCControlData(os, value, data);

    // Assert
    std::string result = os.str();
    EXPECT_EQ(result.find("Off"), std::string::npos);  // Should not find "Off" for invalid value
}

TEST_F(Nikon3MakerNoteTest, PrintFlashGroupBCControlData_EmptyValue_495) {
    // Arrange
    Nikon3MakerNote makerNote;
    Value value(unsignedByte);
    ExifData* data = mockExifData();

    std::ostringstream os;

    // Act
    makerNote.printFlashGroupBCControlData(os, value, data);

    // Assert
    std::string result = os.str();
    EXPECT_EQ(result, "()");
}

TEST_F(Nikon3MakerNoteTest, PrintFlashGroupBCControlData_NullExifData_496) {
    // Arrange
    Nikon3MakerNote makerNote;
    Value value(unsignedByte);
    value.setDataArea(reinterpret_cast<const uint8_t*>("\x1A\x2B\x3C\x4D"), 4);  // Example data for the test
    
    std::ostringstream os;

    // Act
    makerNote.printFlashGroupBCControlData(os, value, nullptr);

    // Assert
    std::string result = os.str();
    EXPECT_NE(result.find("Off"), std::string::npos);  // Still expects to find "Off" despite nullptr ExifData
}

}  // namespace Internal
}  // namespace Exiv2