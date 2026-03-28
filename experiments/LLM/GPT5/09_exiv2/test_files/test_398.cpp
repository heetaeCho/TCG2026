#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "tiffcomposite_int.hpp"

namespace Exiv2 {
namespace Internal {

class TiffDirectoryTest_398 : public ::testing::Test {
protected:
    // Setup and teardown code can be added here if needed.
    // For this case, no special setup is required.
};

TEST_F(TiffDirectoryTest_398, DoSizeData_ReturnsZero_398) {
    // Arrange
    TiffDirectory dir(123, IfdId::Exif, true);  // Using example tag and group
    // Act
    size_t result = dir.doSizeData();
    // Assert
    EXPECT_EQ(result, 0) << "Expected doSizeData to return 0 as per the implementation";
}

TEST_F(TiffDirectoryTest_398, DoSizeData_WhenDirectoryHasNoEntries_ReturnsZero_399) {
    // Arrange
    TiffDirectory dir(123, IfdId::Exif, false);  // No next directory
    // Act
    size_t result = dir.doSizeData();
    // Assert
    EXPECT_EQ(result, 0) << "Expected doSizeData to return 0 when directory has no entries";
}

TEST_F(TiffDirectoryTest_398, DoSizeData_WithNonDefaultConfiguration_ReturnsZero_400) {
    // Arrange
    TiffDirectory dir(123, IfdId::Exif, true);  // Next directory exists
    // Act
    size_t result = dir.doSizeData();
    // Assert
    EXPECT_EQ(result, 0) << "Expected doSizeData to return 0 under non-default configuration";
}

}  // namespace Internal
}  // namespace Exiv2