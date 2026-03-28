// File: test_image_is8bytetype_1054.cpp
// TEST_ID: 1054

#include <gtest/gtest.h>

#include <cstdint>

#include <exiv2/image.hpp>
#include <exiv2/types.hpp>

namespace {

using Exiv2::Image;
using Exiv2::TypeId;

TEST(ImageIs8ByteTypeTest_1054, ReturnsTrueForUnsignedRational_1054)
{
    const uint16_t type = static_cast<uint16_t>(TypeId::unsignedRational);
    EXPECT_TRUE(Image::is8ByteType(type));
}

TEST(ImageIs8ByteTypeTest_1054, ReturnsTrueForSignedRational_1054)
{
    const uint16_t type = static_cast<uint16_t>(TypeId::signedRational);
    EXPECT_TRUE(Image::is8ByteType(type));
}

TEST(ImageIs8ByteTypeTest_1054, ReturnsTrueForUnsignedLongLong_1054)
{
    const uint16_t type = static_cast<uint16_t>(TypeId::unsignedLongLong);
    EXPECT_TRUE(Image::is8ByteType(type));
}

TEST(ImageIs8ByteTypeTest_1054, ReturnsTrueForSignedLongLong_1054)
{
    const uint16_t type = static_cast<uint16_t>(TypeId::signedLongLong);
    EXPECT_TRUE(Image::is8ByteType(type));
}

TEST(ImageIs8ByteTypeTest_1054, ReturnsTrueForTiffIfd8_1054)
{
    const uint16_t type = static_cast<uint16_t>(TypeId::tiffIfd8);
    EXPECT_TRUE(Image::is8ByteType(type));
}

TEST(ImageIs8ByteTypeTest_1054, ReturnsTrueForTiffDouble_1054)
{
    const uint16_t type = static_cast<uint16_t>(TypeId::tiffDouble);
    EXPECT_TRUE(Image::is8ByteType(type));
}

TEST(ImageIs8ByteTypeTest_1054, ReturnsFalseForCommonNon8ByteTypes_1054)
{
    EXPECT_FALSE(Image::is8ByteType(static_cast<uint16_t>(TypeId::unsignedByte)));
    EXPECT_FALSE(Image::is8ByteType(static_cast<uint16_t>(TypeId::asciiString)));
    EXPECT_FALSE(Image::is8ByteType(static_cast<uint16_t>(TypeId::unsignedShort)));
    EXPECT_FALSE(Image::is8ByteType(static_cast<uint16_t>(TypeId::unsignedLong)));
    EXPECT_FALSE(Image::is8ByteType(static_cast<uint16_t>(TypeId::tiffFloat)));
    EXPECT_FALSE(Image::is8ByteType(static_cast<uint16_t>(TypeId::tiffIfd)));
}

TEST(ImageIs8ByteTypeTest_1054, ReturnsFalseForBoundaryValues_1054)
{
    EXPECT_FALSE(Image::is8ByteType(static_cast<uint16_t>(0)));
    EXPECT_FALSE(Image::is8ByteType(static_cast<uint16_t>(0xFFFF)));
}

TEST(ImageIs8ByteTypeTest_1054, ReturnsFalseForInvalidTypeIdTruncatedToUint16_1054)
{
    // invalidTypeId is larger than uint16_t; the production API takes uint16_t.
    // We verify behavior is well-defined for the truncated input value.
    const uint16_t truncated = static_cast<uint16_t>(TypeId::invalidTypeId);
    EXPECT_FALSE(Image::is8ByteType(truncated));
}

}  // namespace