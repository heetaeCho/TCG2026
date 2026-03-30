#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include "casiomn_int.cpp"  // Include the relevant header for CasioMakerNote if available

namespace Exiv2 {
namespace Internal {

// Mocking the Value class if needed for the test
class MockValue {
public:
    MOCK_METHOD(int64_t, toInt64, (), (const));  // Assuming this function returns the integer representation
};

}  // namespace Internal
}  // namespace Exiv2

// Unit test for print0x0006 function
TEST_F(CasioMakerNoteTest_1820, Print0x0006Normal_1820) {
    std::ostringstream os;
    Exiv2::Internal::CasioMakerNote casioMakerNote;

    // Set up the mock value
    Exiv2::Internal::MockValue value;
    EXPECT_CALL(value, toInt64()).WillOnce(testing::Return(5000));

    // Assuming ExifData is not used or is mocked
    ExifData* exifData = nullptr;

    // Call the function and check the output
    casioMakerNote.print0x0006(os, value, exifData);

    // Expect the output to be formatted correctly
    EXPECT_EQ(os.str(), "5.00 m");
}

TEST_F(CasioMakerNoteTest_1821, Print0x0006BoundaryZero_1821) {
    std::ostringstream os;
    Exiv2::Internal::CasioMakerNote casioMakerNote;

    // Set up the mock value for boundary case
    Exiv2::Internal::MockValue value;
    EXPECT_CALL(value, toInt64()).WillOnce(testing::Return(0));

    ExifData* exifData = nullptr;

    // Call the function and check the output
    casioMakerNote.print0x0006(os, value, exifData);

    // Expect the output to be formatted as "0.00 m"
    EXPECT_EQ(os.str(), "0.00 m");
}

TEST_F(CasioMakerNoteTest_1822, Print0x0006BoundaryNegative_1822) {
    std::ostringstream os;
    Exiv2::Internal::CasioMakerNote casioMakerNote;

    // Set up the mock value for a negative number
    Exiv2::Internal::MockValue value;
    EXPECT_CALL(value, toInt64()).WillOnce(testing::Return(-1000));

    ExifData* exifData = nullptr;

    // Call the function and check the output
    casioMakerNote.print0x0006(os, value, exifData);

    // Expect the output to be formatted correctly with negative number
    EXPECT_EQ(os.str(), "-1.00 m");
}

TEST_F(CasioMakerNoteTest_1823, Print0x0006InvalidValue_1823) {
    std::ostringstream os;
    Exiv2::Internal::CasioMakerNote casioMakerNote;

    // Set up the mock value for invalid case (negative of large number)
    Exiv2::Internal::MockValue value;
    EXPECT_CALL(value, toInt64()).WillOnce(testing::Return(-500000));

    ExifData* exifData = nullptr;

    // Call the function and check the output
    casioMakerNote.print0x0006(os, value, exifData);

    // The formatted output should reflect the negative large number
    EXPECT_EQ(os.str(), "-500.00 m");
}