#include <gtest/gtest.h>
#include <sstream>
#include "exiv2/tags.hpp"

namespace Exiv2 {

// Assuming that IfdId is an enum or some type that can be cast to an integer
enum class IfdId {
    Image = 0,
    Exif = 1,
    Iptc = 2,
    Xmp = 3
};

}  // namespace Exiv2

// Test fixture for testing the Exiv2::operator<< function
class Exiv2OperatorTest_123 : public ::testing::Test {
protected:
    std::ostringstream os;
};

// Test case for normal operation of operator<<
TEST_F(Exiv2OperatorTest_123, OutputStreamsCorrectValue_123) {
    Exiv2::IfdId id = Exiv2::IfdId::Exif;
    os.str("");  // Clear the string stream
    os << id;

    // Check if the correct integer value is streamed
    EXPECT_EQ(os.str(), "1");  // Exiv2::IfdId::Exif should be cast to 1
}

// Test case for boundary values of IfdId enum
TEST_F(Exiv2OperatorTest_123, OutputBoundaryValues_123) {
    Exiv2::IfdId id1 = Exiv2::IfdId::Image;
    Exiv2::IfdId id2 = Exiv2::IfdId::Xmp;

    os.str("");  // Clear the string stream
    os << id1;
    EXPECT_EQ(os.str(), "0");  // Exiv2::IfdId::Image should be cast to 0

    os.str("");  // Clear the string stream
    os << id2;
    EXPECT_EQ(os.str(), "3");  // Exiv2::IfdId::Xmp should be cast to 3
}

// Test case for invalid IfdId value (if it can be assigned and output)
TEST_F(Exiv2OperatorTest_123, OutputInvalidIfdId_123) {
    // Assuming there's a scenario where an invalid IfdId could exist (e.g., not in enum)
    // If invalid IfdId values are allowed (e.g., negative values), this might fail
    // or might be handled with a special output mechanism.
    Exiv2::IfdId id = static_cast<Exiv2::IfdId>(-1);  // Invalid IfdId value
    os.str("");  // Clear the string stream
    os << id;

    // If invalid ids are allowed to be cast and output, this might output "-1"
    EXPECT_EQ(os.str(), "-1");
}