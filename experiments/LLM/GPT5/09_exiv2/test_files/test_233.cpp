#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "tiffcomposite_int.hpp"

namespace Exiv2 {
namespace Internal {

// Test for the setOffset method
TEST_F(TiffEntryBaseTest_233, SetOffset_NormalOperation_233) {
    TiffEntryBase entry(1, IfdId::Exif, TiffType::BYTE);
    
    // Set the offset to 100
    entry.setOffset(100);
    
    // Check if the offset is correctly set
    EXPECT_EQ(entry.offset(), 100);
}

TEST_F(TiffEntryBaseTest_233, SetOffset_BoundaryCondition_233) {
    TiffEntryBase entry(1, IfdId::Exif, TiffType::BYTE);
    
    // Set the offset to 0 (boundary case)
    entry.setOffset(0);
    
    // Check if the offset is correctly set to 0
    EXPECT_EQ(entry.offset(), 0);
}

TEST_F(TiffEntryBaseTest_233, SetOffset_LargeOffset_233) {
    TiffEntryBase entry(1, IfdId::Exif, TiffType::BYTE);
    
    // Set a very large offset
    size_t largeOffset = std::numeric_limits<size_t>::max();
    entry.setOffset(largeOffset);
    
    // Check if the offset is correctly set to the large value
    EXPECT_EQ(entry.offset(), largeOffset);
}

}  // namespace Internal
}  // namespace Exiv2