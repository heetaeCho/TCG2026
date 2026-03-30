#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "pngchunk_int.hpp"
#include "types.hpp"

namespace Exiv2 {
namespace Internal {

class PngChunkTest : public testing::Test {
protected:
    PngChunk pngChunk;
};

TEST_F(PngChunkTest, decodeIHDRChunk_ValidData_1235) {
    // Arrange
    DataBuf data(8);
    uint32_t expectedWidth = 256;
    uint32_t expectedHeight = 128;
    uint32_t outWidth = 0;
    uint32_t outHeight = 0;

    // Fill the data buffer with valid IHDR chunk data
    data.write_uint32(0, expectedWidth, bigEndian);
    data.write_uint32(4, expectedHeight, bigEndian);

    // Act
    pngChunk.decodeIHDRChunk(data, &outWidth, &outHeight);

    // Assert
    EXPECT_EQ(outWidth, expectedWidth);
    EXPECT_EQ(outHeight, expectedHeight);
}

TEST_F(PngChunkTest, decodeIHDRChunk_EmptyData_1236) {
    // Arrange
    DataBuf data(0);
    uint32_t outWidth = 0;
    uint32_t outHeight = 0;

    // Act & Assert
    EXPECT_DEATH(pngChunk.decodeIHDRChunk(data, &outWidth, &outHeight), ".*");
}

TEST_F(PngChunkTest, decodeIHDRChunk_InvalidData_1237) {
    // Arrange
    DataBuf data(8);
    uint32_t outWidth = 0;
    uint32_t outHeight = 0;

    // Fill the data buffer with invalid IHDR chunk data (for instance, width as 0)
    data.write_uint32(0, 0, bigEndian);
    data.write_uint32(4, 128, bigEndian);

    // Act
    pngChunk.decodeIHDRChunk(data, &outWidth, &outHeight);

    // Assert
    EXPECT_EQ(outWidth, 0);  // Width should be 0 due to invalid IHDR data
    EXPECT_EQ(outHeight, 128);  // Height should still be set
}

}  // namespace Internal
}  // namespace Exiv2