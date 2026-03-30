#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include "nikonmn_int.cpp"  // Assuming the partial implementation is available in this file

namespace Exiv2 { namespace Internal {

// Mocking the external Value and ExifData classes if necessary
class MockValue {
public:
    MOCK_METHOD(int, count, (), (const));
    MOCK_METHOD(int64_t, toInt64, (int), (const));
    MOCK_METHOD(const char*, toString, (), (const));
};

class MockExifData {};

} }

using testing::_;
using testing::Return;
using testing::NiceMock;

// Test fixture for testing the print0x0002 function
class Nikon3MakerNoteTest : public testing::Test {
protected:
    Exiv2::Internal::Nikon3MakerNote makerNote;
};

// Normal operation test: Single value print (when count() is 1)
TEST_F(Nikon3MakerNoteTest, PrintSingleValue_460) {
    // Prepare mock value
    NiceMock<Exiv2::Internal::MockValue> value;
    const char* expectedValue = "singleValue";
    
    // Set expectations for count() and toString()
    EXPECT_CALL(value, count()).WillOnce(Return(1));
    EXPECT_CALL(value, toString()).WillOnce(Return(expectedValue));

    std::ostringstream os;
    os << makerNote.print0x0002(os, value, nullptr);
    EXPECT_EQ(os.str(), "(singleValue)");
}

// Boundary condition test: Multiple value print (when count() > 1)
TEST_F(Nikon3MakerNoteTest, PrintMultipleValues_461) {
    // Prepare mock value
    NiceMock<Exiv2::Internal::MockValue> value;
    int64_t expectedInt64 = 123456789;

    // Set expectations for count() and toInt64()
    EXPECT_CALL(value, count()).WillOnce(Return(2));
    EXPECT_CALL(value, toInt64(1)).WillOnce(Return(expectedInt64));

    std::ostringstream os;
    os << makerNote.print0x0002(os, value, nullptr);
    EXPECT_EQ(os.str(), "123456789");
}

// Exceptional case test: Edge case where count() is 0 (assuming count() could be 0)
TEST_F(Nikon3MakerNoteTest, PrintZeroCount_462) {
    // Prepare mock value
    NiceMock<Exiv2::Internal::MockValue> value;

    // Set expectations for count()
    EXPECT_CALL(value, count()).WillOnce(Return(0));

    std::ostringstream os;
    // Since the implementation doesn't handle count() == 0, assume no output is expected
    os << makerNote.print0x0002(os, value, nullptr);
    EXPECT_EQ(os.str(), "");
}

// Exceptional case test: Invalid value in toInt64 (e.g., negative)
TEST_F(Nikon3MakerNoteTest, PrintNegativeValue_463) {
    // Prepare mock value
    NiceMock<Exiv2::Internal::MockValue> value;
    int64_t negativeValue = -123456789;

    // Set expectations for count() and toInt64()
    EXPECT_CALL(value, count()).WillOnce(Return(2));
    EXPECT_CALL(value, toInt64(1)).WillOnce(Return(negativeValue));

    std::ostringstream os;
    os << makerNote.print0x0002(os, value, nullptr);
    EXPECT_EQ(os.str(), "-123456789");
}

// Test for verifying external interactions (Mocking ExifData)
TEST_F(Nikon3MakerNoteTest, VerifyExternalInteraction_464) {
    // Prepare mock value and mock ExifData
    NiceMock<Exiv2::Internal::MockValue> value;
    NiceMock<Exiv2::Internal::MockExifData> exifData;

    // Set expectations for count()
    EXPECT_CALL(value, count()).WillOnce(Return(1));

    std::ostringstream os;
    os << makerNote.print0x0002(os, value, &exifData);
    // Since there are no interactions with exifData in the implementation, this is just a placeholder
    EXPECT_EQ(os.str(), "(singleValue)");
}

}  // namespace Exiv2