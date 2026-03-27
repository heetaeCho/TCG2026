#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <string>
#include "nikonmn_int.cpp"  // Assuming the implementation file is included for the sake of testing

namespace Exiv2 {
    namespace Internal {

        // Mock Value class for testing
        class MockValue {
        public:
            MOCK_METHOD(int, count, (), (const));
            MOCK_METHOD(int, typeId, (), (const));
            MOCK_METHOD(int64_t, toInt64, (), (const));
            MOCK_METHOD(std::ostream&, operator<<, (std::ostream& os), (const));
        };

        // Mock ExifData class for testing
        class MockExifData {};

    }
}

// Unit Test Class for Nikon3MakerNote::printRepeatingFlashRate
class Nikon3MakerNoteTest : public ::testing::Test {
protected:
    Exiv2::Internal::Nikon3MakerNote makerNote;
};

// TEST_ID: 483
TEST_F(Nikon3MakerNoteTest, PrintRepeatingFlashRate_ValidValue_483) {
    std::ostringstream os;
    Exiv2::Internal::MockValue value;
    Exiv2::Internal::MockExifData exifData;

    // Setup mock behavior
    EXPECT_CALL(value, count()).WillOnce(testing::Return(1));
    EXPECT_CALL(value, typeId()).WillOnce(testing::Return(Exiv2::Internal::unsignedByte));
    EXPECT_CALL(value, toInt64()).WillOnce(testing::Return(100));

    // Call the function
    makerNote.printRepeatingFlashRate(os, value, &exifData);

    // Check output
    EXPECT_EQ(os.str(), "100 Hz");
}

// TEST_ID: 484
TEST_F(Nikon3MakerNoteTest, PrintRepeatingFlashRate_ValueCountNotOne_484) {
    std::ostringstream os;
    Exiv2::Internal::MockValue value;
    Exiv2::Internal::MockExifData exifData;

    // Setup mock behavior
    EXPECT_CALL(value, count()).WillOnce(testing::Return(2));  // Invalid count
    EXPECT_CALL(value, typeId()).WillOnce(testing::Return(Exiv2::Internal::unsignedByte));
    
    // Call the function
    makerNote.printRepeatingFlashRate(os, value, &exifData);

    // Check output
    EXPECT_EQ(os.str(), "(2)");  // Should print the value as is
}

// TEST_ID: 485
TEST_F(Nikon3MakerNoteTest, PrintRepeatingFlashRate_InvalidType_485) {
    std::ostringstream os;
    Exiv2::Internal::MockValue value;
    Exiv2::Internal::MockExifData exifData;

    // Setup mock behavior
    EXPECT_CALL(value, count()).WillOnce(testing::Return(1));
    EXPECT_CALL(value, typeId()).WillOnce(testing::Return(999));  // Invalid type

    // Call the function
    makerNote.printRepeatingFlashRate(os, value, &exifData);

    // Check output
    EXPECT_EQ(os.str(), "(999)");  // Should print the value as is
}

// TEST_ID: 486
TEST_F(Nikon3MakerNoteTest, PrintRepeatingFlashRate_ZeroOr255_486) {
    std::ostringstream os;
    Exiv2::Internal::MockValue value;
    Exiv2::Internal::MockExifData exifData;

    // Test for 0
    EXPECT_CALL(value, count()).WillOnce(testing::Return(1));
    EXPECT_CALL(value, typeId()).WillOnce(testing::Return(Exiv2::Internal::unsignedByte));
    EXPECT_CALL(value, toInt64()).WillOnce(testing::Return(0));
    makerNote.printRepeatingFlashRate(os, value, &exifData);
    EXPECT_EQ(os.str(), "n/a");

    // Test for 255
    os.str("");  // Clear the stringstream
    EXPECT_CALL(value, toInt64()).WillOnce(testing::Return(255));
    makerNote.printRepeatingFlashRate(os, value, &exifData);
    EXPECT_EQ(os.str(), "n/a");
}

// TEST_ID: 487
TEST_F(Nikon3MakerNoteTest, PrintRepeatingFlashRate_NegativeValue_487) {
    std::ostringstream os;
    Exiv2::Internal::MockValue value;
    Exiv2::Internal::MockExifData exifData;

    // Test for negative value
    EXPECT_CALL(value, count()).WillOnce(testing::Return(1));
    EXPECT_CALL(value, typeId()).WillOnce(testing::Return(Exiv2::Internal::unsignedByte));
    EXPECT_CALL(value, toInt64()).WillOnce(testing::Return(-10));
    makerNote.printRepeatingFlashRate(os, value, &exifData);
    
    // Check output
    EXPECT_EQ(os.str(), "(-10)");
}