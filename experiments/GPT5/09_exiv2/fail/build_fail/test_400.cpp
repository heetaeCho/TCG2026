#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "tiffcomposite_int.hpp"

namespace Exiv2 { namespace Internal {

class TiffImageEntryTest : public ::testing::Test {
protected:
    TiffImageEntry tiffImageEntry;
};

// Test for normal operation when group() > IfdId::mnId
TEST_F(TiffImageEntryTest, doSizeData_NormalOperation_400) {
    // Mock group() to return a value greater than IfdId::mnId
    ON_CALL(tiffImageEntry, group()).WillByDefault(testing::Return(IfdId::mnId + 1));

    // Mock sizeImage to return a specific size
    size_t expectedSize = 100;
    ON_CALL(tiffImageEntry, sizeImage()).WillByDefault(testing::Return(expectedSize));

    // Call the doSizeData function
    size_t result = tiffImageEntry.doSizeData();

    // Verify the result
    EXPECT_EQ(result, expectedSize);
}

// Test for boundary condition when group() == IfdId::mnId
TEST_F(TiffImageEntryTest, doSizeData_BoundaryCondition_GroupEqualsMnId_401) {
    // Mock group() to return IfdId::mnId
    ON_CALL(tiffImageEntry, group()).WillByDefault(testing::Return(IfdId::mnId));

    // Expect doSizeData to return 0 as no size is calculated
    size_t result = tiffImageEntry.doSizeData();
    EXPECT_EQ(result, 0);
}

// Test for exceptional case when group() is less than IfdId::mnId
TEST_F(TiffImageEntryTest, doSizeData_ExceptionalCase_GroupLessThanMnId_402) {
    // Mock group() to return a value less than IfdId::mnId
    ON_CALL(tiffImageEntry, group()).WillByDefault(testing::Return(IfdId::ifd0Id));

    // Expect doSizeData to return 0 as no size is calculated
    size_t result = tiffImageEntry.doSizeData();
    EXPECT_EQ(result, 0);
}

} } // namespace Exiv2::Internal