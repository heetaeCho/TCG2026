#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include "nikonmn_int.hpp" // Assuming the class definition is in this header file
#include "exiv2/exif.hpp"  // Assuming ExifData is defined in this header file
#include "exiv2/value.hpp" // Assuming Value class is in this header file

namespace Exiv2 {
namespace Internal {

class Nikon3MakerNoteTest : public ::testing::Test {
protected:
    // Helper function to create a mock Value object with a specified count and typeId
    std::shared_ptr<Value> createMockValue(size_t count, TypeId typeId) {
        auto value = std::make_shared<Value>(typeId);
        EXPECT_CALL(*value, count()).WillOnce(testing::Return(count));
        EXPECT_CALL(*value, typeId()).WillOnce(testing::Return(typeId));
        return value;
    }

    // Helper function to create a mock ExifData object
    std::shared_ptr<ExifData> createMockExifData() {
        return std::make_shared<ExifData>();
    }
};

// TEST_ID: 485
TEST_F(Nikon3MakerNoteTest, PrintExternalFlashData1Fl6_Fired_485) {
    // Setup mock Value object with valid count and typeId
    auto value = createMockValue(1, TypeId::unsignedByte);
    EXPECT_CALL(*value, toUint32(0)).WillOnce(testing::Return(0x01));  // Fired (first bit set)

    // Create mock ExifData object (if needed for external interactions)
    auto metadata = createMockExifData();

    std::ostringstream os;
    Nikon3MakerNote::printExternalFlashData1Fl6(os, *value, metadata);
    
    // Check that the output contains the "Fired" keyword
    EXPECT_THAT(os.str(), testing::HasSubstr("Fired"));
}

// TEST_ID: 486
TEST_F(Nikon3MakerNoteTest, PrintExternalFlashData1Fl6_DidNotFire_486) {
    // Setup mock Value object with valid count and typeId
    auto value = createMockValue(1, TypeId::unsignedByte);
    EXPECT_CALL(*value, toUint32(0)).WillOnce(testing::Return(0x00));  // Did not fire (first bit unset)

    // Create mock ExifData object (if needed for external interactions)
    auto metadata = createMockExifData();

    std::ostringstream os;
    Nikon3MakerNote::printExternalFlashData1Fl6(os, *value, metadata);
    
    // Check that the output contains the "Did not fire" keyword
    EXPECT_THAT(os.str(), testing::HasSubstr("Did not fire"));
}

// TEST_ID: 487
TEST_F(Nikon3MakerNoteTest, PrintExternalFlashData1Fl6_EmptyTagMask_487) {
    // Setup mock Value object with valid count and typeId
    auto value = createMockValue(1, TypeId::unsignedByte);
    EXPECT_CALL(*value, toUint32(0)).WillOnce(testing::Return(0x01));  // Fired (first bit set)

    // Mock the external flash adaptors bitmask to return an empty string
    std::ostringstream ossTemp;
    EXPECT_CALL(*value, toUint32(0)).WillOnce(testing::Return(0x01));
    EXV_PRINT_TAG_BITMASK(nikonFlashAdaptors)(ossTemp, *value, nullptr);

    std::ostringstream os;
    Nikon3MakerNote::printExternalFlashData1Fl6(os, *value, nullptr);
    
    // Check that the output contains the "Fired" keyword and no additional data
    EXPECT_THAT(os.str(), testing::HasSubstr("Fired"));
    EXPECT_THAT(os.str(), testing::Not(HasSubstr("Bounce Flash adaptor")));
}

// TEST_ID: 488
TEST_F(Nikon3MakerNoteTest, PrintExternalFlashData1Fl6_Error_InvalidCount_488) {
    // Setup mock Value object with invalid count
    auto value = createMockValue(0, TypeId::unsignedByte);  // Invalid count (not 1)

    // Create mock ExifData object (if needed for external interactions)
    auto metadata = createMockExifData();

    std::ostringstream os;
    Nikon3MakerNote::printExternalFlashData1Fl6(os, *value, metadata);
    
    // Check that the output does not contain "Fired" or "Did not fire" as the input is invalid
    EXPECT_THAT(os.str(), testing::Not(HasSubstr("Fired")));
    EXPECT_THAT(os.str(), testing::Not(HasSubstr("Did not fire")));
}

// TEST_ID: 489
TEST_F(Nikon3MakerNoteTest, PrintExternalFlashData1Fl6_Error_InvalidType_489) {
    // Setup mock Value object with invalid typeId
    auto value = createMockValue(1, TypeId::string);  // Invalid typeId (not unsignedByte)

    // Create mock ExifData object (if needed for external interactions)
    auto metadata = createMockExifData();

    std::ostringstream os;
    Nikon3MakerNote::printExternalFlashData1Fl6(os, *value, metadata);
    
    // Check that the output does not contain any flash-related output
    EXPECT_THAT(os.str(), testing::Not(HasSubstr("Fired")));
    EXPECT_THAT(os.str(), testing::Not(HasSubstr("Did not fire")));
}

}  // namespace Internal
}  // namespace Exiv2