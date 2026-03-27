#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <string>

namespace Exiv2 { namespace Internal {

// Mock class for ExifData to be used in the tests.
class MockExifData : public ExifData {
    // You may define mock methods here if necessary
};

TEST_F(PrintFocalLengthTest_1722, PrintFocalLength35_Normal_Operation_1722) {
    // Normal case where length is valid and non-zero
    Value value(12345); // A valid focal length value
    std::ostringstream os;
    MockExifData exifData;
    printFocalLength35(os, value, &exifData);
    EXPECT_EQ(os.str(), "1234.5 mm"); // The focal length should be displayed in mm with one decimal place
}

TEST_F(PrintFocalLengthTest_1723, PrintFocalLength35_Zero_Length_1723) {
    // Special case where length is zero
    Value value(0); // A zero focal length value
    std::ostringstream os;
    MockExifData exifData;
    printFocalLength35(os, value, &exifData);
    EXPECT_EQ(os.str(), "Unknown"); // The function should return "Unknown" for a zero focal length
}

TEST_F(PrintFocalLengthTest_1724, PrintFocalLength35_Invalid_TypeId_1724) {
    // Exceptional case where the typeId is invalid
    Value value("invalid"); // Passing a string instead of a number
    std::ostringstream os;
    MockExifData exifData;
    printFocalLength35(os, value, &exifData);
    EXPECT_EQ(os.str(), "invalid"); // The function should just output the value as it is if typeId is invalid
}

TEST_F(PrintFocalLengthTest_1725, PrintFocalLength35_Invalid_Count_1725) {
    // Exceptional case where count is not equal to 1
    Value value(12345); // A valid value
    value.setCount(2); // Setting an invalid count
    std::ostringstream os;
    MockExifData exifData;
    printFocalLength35(os, value, &exifData);
    EXPECT_EQ(os.str(), "12345"); // The function should return the raw value if count is not 1
}

TEST_F(PrintFocalLengthTest_1726, PrintFocalLength35_Extreme_Length_1726) {
    // Boundary case for extreme focal length value
    Value value(1000000); // A very large focal length
    std::ostringstream os;
    MockExifData exifData;
    printFocalLength35(os, value, &exifData);
    EXPECT_EQ(os.str(), "100000.0 mm"); // The function should handle large values correctly
}

} } // namespace Exiv2::Internal