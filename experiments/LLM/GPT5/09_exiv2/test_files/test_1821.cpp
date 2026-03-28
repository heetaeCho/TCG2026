#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "exiv2.hpp"  // Assuming relevant headers for Value, ExifData

namespace Exiv2 {
namespace Internal {

class CasioMakerNoteTest : public ::testing::Test {
protected:
    CasioMakerNote casioMakerNote;
};

TEST_F(CasioMakerNoteTest, Print0x0015ValidData_1821) {
    std::ostringstream oss;
    std::vector<char> data = {'3', '1', '0', '1', '0', '5', '2', '1', '1', '5', '4', '3'};  // Example data
    Value value(data);
    ExifData exifData;  // Assuming a default ExifData object

    // Expected output for the given input, formatted as "2021:05:15 21:54:00"
    std::string expected_output = "2021:05:15 21:54:00";

    // Perform the test
    casioMakerNote.print0x0015(oss, value, &exifData);

    // Verify the output
    EXPECT_EQ(oss.str(), expected_output);
}

TEST_F(CasioMakerNoteTest, Print0x0015BoundaryCondition_LessThan10Chars_1822) {
    std::ostringstream oss;
    std::vector<char> data = {'3', '1', '0', '1', '0', '5', '2', '1', '1'};  // 9 characters, less than required
    Value value(data);
    ExifData exifData;  // Assuming a default ExifData object

    // In this case, the output should simply be the value because it doesn't meet the boundary condition of 10 characters.
    std::string expected_output = "310105211";

    // Perform the test
    casioMakerNote.print0x0015(oss, value, &exifData);

    // Verify the output
    EXPECT_EQ(oss.str(), expected_output);
}

TEST_F(CasioMakerNoteTest, Print0x0015BoundaryCondition_Exactly10Chars_1823) {
    std::ostringstream oss;
    std::vector<char> data = {'3', '1', '0', '1', '0', '5', '2', '1', '1', '5'};  // Exactly 10 characters
    Value value(data);
    ExifData exifData;  // Assuming a default ExifData object

    // Expected output when the length of numbers is exactly 10.
    std::string expected_output = "2021:05:15 21:50";

    // Perform the test
    casioMakerNote.print0x0015(oss, value, &exifData);

    // Verify the output
    EXPECT_EQ(oss.str(), expected_output);
}

TEST_F(CasioMakerNoteTest, Print0x0015BoundaryCondition_Exactly12Chars_1824) {
    std::ostringstream oss;
    std::vector<char> data = {'3', '1', '0', '1', '0', '5', '2', '1', '1', '5', '4', '3'};  // Exactly 12 characters
    Value value(data);
    ExifData exifData;  // Assuming a default ExifData object

    // Expected output when the length of numbers is exactly 12.
    std::string expected_output = "2021:05:15 21:54:00";

    // Perform the test
    casioMakerNote.print0x0015(oss, value, &exifData);

    // Verify the output
    EXPECT_EQ(oss.str(), expected_output);
}

TEST_F(CasioMakerNoteTest, Print0x0015ErrorCase_NullValue_1825) {
    std::ostringstream oss;
    Value value(nullptr);  // Invalid value
    ExifData exifData;  // Assuming a default ExifData object

    // The output should be the value itself since there is no valid data
    std::string expected_output = "0";

    // Perform the test
    casioMakerNote.print0x0015(oss, value, &exifData);

    // Verify the output
    EXPECT_EQ(oss.str(), expected_output);
}

}  // namespace Internal
}  // namespace Exiv2