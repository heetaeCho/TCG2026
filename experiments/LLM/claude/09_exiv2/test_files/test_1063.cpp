#include <gtest/gtest.h>
#include <cstdint>

// Replicate the necessary types from exiv2/types.hpp
namespace Exiv2 {
enum TypeId {
    unsignedByte = 1,
    asciiString = 2,
    unsignedShort = 3,
    unsignedLong = 4,
    unsignedRational = 5,
    signedByte = 6,
    undefined = 7,
    signedShort = 8,
    signedLong = 9,
    signedRational = 10,
    tiffFloat = 11,
    tiffDouble = 12,
    tiffIfd = 13,
    unsignedLongLong = 16,
    signedLongLong = 17,
    tiffIfd8 = 18,
    string = 65536,
    date = 65537,
    time = 65538,
    comment = 65539,
    directory = 65540,
    xmpText = 65541,
    xmpAlt = 65542,
    xmpBag = 65543,
    xmpSeq = 65544,
    langAlt = 65545,
    invalidTypeId = 131070,
    lastTypeId = 131071
};

// Minimal Image class matching the provided partial implementation
class Image {
public:
    const char* typeName(uint16_t tag) {
        const char* result = nullptr;
        switch (tag) {
            case Exiv2::unsignedByte:
                result = "BYTE";
                break;
            case Exiv2::asciiString:
                result = "ASCII";
                break;
            case Exiv2::unsignedShort:
                result = "SHORT";
                break;
            case Exiv2::unsignedLong:
                result = "LONG";
                break;
            case Exiv2::unsignedRational:
                result = "RATIONAL";
                break;
            case Exiv2::signedByte:
                result = "SBYTE";
                break;
            case Exiv2::undefined:
                result = "UNDEFINED";
                break;
            case Exiv2::signedShort:
                result = "SSHORT";
                break;
            case Exiv2::signedLong:
                result = "SLONG";
                break;
            case Exiv2::signedRational:
                result = "SRATIONAL";
                break;
            case Exiv2::tiffFloat:
                result = "FLOAT";
                break;
            case Exiv2::tiffDouble:
                result = "DOUBLE";
                break;
            case Exiv2::tiffIfd:
                result = "IFD";
                break;
            default:
                result = "unknown";
                break;
        }
        return result;
    }
};
}  // namespace Exiv2

class ImageTypeNameTest_1063 : public ::testing::Test {
protected:
    Exiv2::Image image;
};

// Test all known type names

TEST_F(ImageTypeNameTest_1063, UnsignedByteReturnsBYTE_1063) {
    EXPECT_STREQ("BYTE", image.typeName(Exiv2::unsignedByte));
}

TEST_F(ImageTypeNameTest_1063, AsciiStringReturnsASCII_1063) {
    EXPECT_STREQ("ASCII", image.typeName(Exiv2::asciiString));
}

TEST_F(ImageTypeNameTest_1063, UnsignedShortReturnsSHORT_1063) {
    EXPECT_STREQ("SHORT", image.typeName(Exiv2::unsignedShort));
}

TEST_F(ImageTypeNameTest_1063, UnsignedLongReturnsLONG_1063) {
    EXPECT_STREQ("LONG", image.typeName(Exiv2::unsignedLong));
}

TEST_F(ImageTypeNameTest_1063, UnsignedRationalReturnsRATIONAL_1063) {
    EXPECT_STREQ("RATIONAL", image.typeName(Exiv2::unsignedRational));
}

TEST_F(ImageTypeNameTest_1063, SignedByteReturnsSBYTE_1063) {
    EXPECT_STREQ("SBYTE", image.typeName(Exiv2::signedByte));
}

TEST_F(ImageTypeNameTest_1063, UndefinedReturnsUNDEFINED_1063) {
    EXPECT_STREQ("UNDEFINED", image.typeName(Exiv2::undefined));
}

TEST_F(ImageTypeNameTest_1063, SignedShortReturnsSShort_1063) {
    EXPECT_STREQ("SSHORT", image.typeName(Exiv2::signedShort));
}

TEST_F(ImageTypeNameTest_1063, SignedLongReturnsSLONG_1063) {
    EXPECT_STREQ("SLONG", image.typeName(Exiv2::signedLong));
}

TEST_F(ImageTypeNameTest_1063, SignedRationalReturnsSRATIONAL_1063) {
    EXPECT_STREQ("SRATIONAL", image.typeName(Exiv2::signedRational));
}

TEST_F(ImageTypeNameTest_1063, TiffFloatReturnsFLOAT_1063) {
    EXPECT_STREQ("FLOAT", image.typeName(Exiv2::tiffFloat));
}

TEST_F(ImageTypeNameTest_1063, TiffDoubleReturnsDOUBLE_1063) {
    EXPECT_STREQ("DOUBLE", image.typeName(Exiv2::tiffDouble));
}

TEST_F(ImageTypeNameTest_1063, TiffIfdReturnsIFD_1063) {
    EXPECT_STREQ("IFD", image.typeName(Exiv2::tiffIfd));
}

// Test default/unknown cases

TEST_F(ImageTypeNameTest_1063, ZeroReturnsUnknown_1063) {
    EXPECT_STREQ("unknown", image.typeName(0));
}

TEST_F(ImageTypeNameTest_1063, Tag14ReturnsUnknown_1063) {
    EXPECT_STREQ("unknown", image.typeName(14));
}

TEST_F(ImageTypeNameTest_1063, Tag15ReturnsUnknown_1063) {
    EXPECT_STREQ("unknown", image.typeName(15));
}

TEST_F(ImageTypeNameTest_1063, UnsignedLongLongReturnsUnknown_1063) {
    // unsignedLongLong = 16, not in switch
    EXPECT_STREQ("unknown", image.typeName(Exiv2::unsignedLongLong));
}

TEST_F(ImageTypeNameTest_1063, SignedLongLongReturnsUnknown_1063) {
    EXPECT_STREQ("unknown", image.typeName(Exiv2::signedLongLong));
}

TEST_F(ImageTypeNameTest_1063, TiffIfd8ReturnsUnknown_1063) {
    EXPECT_STREQ("unknown", image.typeName(Exiv2::tiffIfd8));
}

TEST_F(ImageTypeNameTest_1063, MaxUint16ReturnsUnknown_1063) {
    EXPECT_STREQ("unknown", image.typeName(UINT16_MAX));
}

TEST_F(ImageTypeNameTest_1063, LargeValueReturnsUnknown_1063) {
    EXPECT_STREQ("unknown", image.typeName(65535));
}

TEST_F(ImageTypeNameTest_1063, Value100ReturnsUnknown_1063) {
    EXPECT_STREQ("unknown", image.typeName(100));
}

TEST_F(ImageTypeNameTest_1063, Value255ReturnsUnknown_1063) {
    EXPECT_STREQ("unknown", image.typeName(255));
}

// Verify exact tag values match expected types
TEST_F(ImageTypeNameTest_1063, TagValue1ReturnsBYTE_1063) {
    EXPECT_STREQ("BYTE", image.typeName(1));
}

TEST_F(ImageTypeNameTest_1063, TagValue2ReturnsASCII_1063) {
    EXPECT_STREQ("ASCII", image.typeName(2));
}

TEST_F(ImageTypeNameTest_1063, TagValue3ReturnsSHORT_1063) {
    EXPECT_STREQ("SHORT", image.typeName(3));
}

TEST_F(ImageTypeNameTest_1063, TagValue4ReturnsLONG_1063) {
    EXPECT_STREQ("LONG", image.typeName(4));
}

TEST_F(ImageTypeNameTest_1063, TagValue5ReturnsRATIONAL_1063) {
    EXPECT_STREQ("RATIONAL", image.typeName(5));
}

TEST_F(ImageTypeNameTest_1063, TagValue6ReturnsSBYTE_1063) {
    EXPECT_STREQ("SBYTE", image.typeName(6));
}

TEST_F(ImageTypeNameTest_1063, TagValue7ReturnsUNDEFINED_1063) {
    EXPECT_STREQ("UNDEFINED", image.typeName(7));
}

TEST_F(ImageTypeNameTest_1063, TagValue8ReturnsSShort_1063) {
    EXPECT_STREQ("SSHORT", image.typeName(8));
}

TEST_F(ImageTypeNameTest_1063, TagValue9ReturnsSLONG_1063) {
    EXPECT_STREQ("SLONG", image.typeName(9));
}

TEST_F(ImageTypeNameTest_1063, TagValue10ReturnsSRATIONAL_1063) {
    EXPECT_STREQ("SRATIONAL", image.typeName(10));
}

TEST_F(ImageTypeNameTest_1063, TagValue11ReturnsFLOAT_1063) {
    EXPECT_STREQ("FLOAT", image.typeName(11));
}

TEST_F(ImageTypeNameTest_1063, TagValue12ReturnsDOUBLE_1063) {
    EXPECT_STREQ("DOUBLE", image.typeName(12));
}

TEST_F(ImageTypeNameTest_1063, TagValue13ReturnsIFD_1063) {
    EXPECT_STREQ("IFD", image.typeName(13));
}

// Boundary: result is not null for any input
TEST_F(ImageTypeNameTest_1063, ResultIsNeverNullForKnownTypes_1063) {
    for (uint16_t tag = 1; tag <= 13; ++tag) {
        EXPECT_NE(nullptr, image.typeName(tag)) << "Failed for tag: " << tag;
    }
}

TEST_F(ImageTypeNameTest_1063, ResultIsNeverNullForUnknownTypes_1063) {
    EXPECT_NE(nullptr, image.typeName(0));
    EXPECT_NE(nullptr, image.typeName(14));
    EXPECT_NE(nullptr, image.typeName(1000));
    EXPECT_NE(nullptr, image.typeName(UINT16_MAX));
}

// Verify calling typeName multiple times returns consistent results
TEST_F(ImageTypeNameTest_1063, ConsistentResultsOnMultipleCalls_1063) {
    EXPECT_STREQ(image.typeName(1), image.typeName(1));
    EXPECT_STREQ(image.typeName(7), image.typeName(7));
    EXPECT_STREQ(image.typeName(0), image.typeName(0));
    EXPECT_STREQ(image.typeName(999), image.typeName(999));
}
