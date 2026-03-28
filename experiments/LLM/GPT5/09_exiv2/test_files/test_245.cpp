#include <gtest/gtest.h>
#include "tiffcomposite_int.hpp"

namespace Exiv2 {
namespace Internal {

// Test class for TiffDirectory
class TiffDirectoryTest : public ::testing::Test {
protected:
    // Helper function to create a TiffDirectory instance
    TiffDirectory createTiffDirectory(uint16_t tag, IfdId group, bool hasNext) {
        return TiffDirectory(tag, group, hasNext);
    }
};

// TEST_ID: 245
TEST_F(TiffDirectoryTest, HasNextReturnsTrueWhenHasNextIsTrue_245) {
    TiffDirectory tiffDir(1, 1, true);
    EXPECT_TRUE(tiffDir.hasNext());
}

// TEST_ID: 246
TEST_F(TiffDirectoryTest, HasNextReturnsFalseWhenHasNextIsFalse_246) {
    TiffDirectory tiffDir(1, 1, false);
    EXPECT_FALSE(tiffDir.hasNext());
}

// TEST_ID: 247
TEST_F(TiffDirectoryTest, CopyConstructorCopiesHasNext_247) {
    TiffDirectory original(1, 1, true);
    TiffDirectory copy = original;
    EXPECT_TRUE(copy.hasNext());
}

// TEST_ID: 248
TEST_F(TiffDirectoryTest, CopyConstructorCopiesHasNextFalse_248) {
    TiffDirectory original(1, 1, false);
    TiffDirectory copy = original;
    EXPECT_FALSE(copy.hasNext());
}

// TEST_ID: 249
TEST_F(TiffDirectoryTest, CreatingTiffDirectoryWithHasNextTrue_249) {
    TiffDirectory tiffDir(100, 200, true);
    EXPECT_TRUE(tiffDir.hasNext());
}

// TEST_ID: 250
TEST_F(TiffDirectoryTest, CreatingTiffDirectoryWithHasNextFalse_250) {
    TiffDirectory tiffDir(100, 200, false);
    EXPECT_FALSE(tiffDir.hasNext());
}

// TEST_ID: 251
TEST_F(TiffDirectoryTest, BoundaryTestMaxTag_251) {
    // Assuming tag can be uint16_t, testing maximum value
    TiffDirectory tiffDir(std::numeric_limits<uint16_t>::max(), 1, true);
    EXPECT_TRUE(tiffDir.hasNext());
}

// TEST_ID: 252
TEST_F(TiffDirectoryTest, BoundaryTestMinTag_252) {
    // Test with minimum tag (0)
    TiffDirectory tiffDir(0, 1, false);
    EXPECT_FALSE(tiffDir.hasNext());
}

// TEST_ID: 253
TEST_F(TiffDirectoryTest, ExceptionalCaseWhenHasNextIsNotSet_253) {
    try {
        // Using default constructor (if exists) where hasNext_ may be undefined
        TiffDirectory tiffDir(1, 1, false);
        // Depending on the behavior, we may want to check for some default or error condition
        ASSERT_FALSE(tiffDir.hasNext());
    } catch (const std::exception& e) {
        FAIL() << "Exception thrown during construction: " << e.what();
    }
}

}  // namespace Internal
}  // namespace Exiv2