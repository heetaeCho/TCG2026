#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/value.hpp>
#include <exiv2/exif.hpp>

// We need access to the internal function
namespace Exiv2 {
namespace Internal {
std::ostream& print0x9101(std::ostream& os, const Value& value, const ExifData*);
}
}

using namespace Exiv2;
using namespace Exiv2::Internal;

class Print0x9101Test_1399 : public ::testing::Test {
protected:
    std::ostringstream os;
};

// Test with standard YCbCr components (1, 2, 3)
TEST_F(Print0x9101Test_1399, StandardYCbCr_1399) {
    UndefinedValue value;
    byte data[] = {1, 2, 3, 0};
    value.read(data, 4, invalidByteOrder);
    print0x9101(os, value, nullptr);
    EXPECT_EQ("YCbCr", os.str());
}

// Test with RGB components (4, 5, 6)
TEST_F(Print0x9101Test_1399, StandardRGB_1399) {
    UndefinedValue value;
    byte data[] = {4, 5, 6, 0};
    value.read(data, 4, invalidByteOrder);
    print0x9101(os, value, nullptr);
    EXPECT_EQ("RGB", os.str());
}

// Test with all zeros - should produce empty string
TEST_F(Print0x9101Test_1399, AllZeros_1399) {
    UndefinedValue value;
    byte data[] = {0, 0, 0, 0};
    value.read(data, 4, invalidByteOrder);
    print0x9101(os, value, nullptr);
    EXPECT_EQ("", os.str());
}

// Test with single Y component
TEST_F(Print0x9101Test_1399, SingleY_1399) {
    UndefinedValue value;
    byte data[] = {1};
    value.read(data, 1, invalidByteOrder);
    print0x9101(os, value, nullptr);
    EXPECT_EQ("Y", os.str());
}

// Test with single Cb component
TEST_F(Print0x9101Test_1399, SingleCb_1399) {
    UndefinedValue value;
    byte data[] = {2};
    value.read(data, 1, invalidByteOrder);
    print0x9101(os, value, nullptr);
    EXPECT_EQ("Cb", os.str());
}

// Test with single Cr component
TEST_F(Print0x9101Test_1399, SingleCr_1399) {
    UndefinedValue value;
    byte data[] = {3};
    value.read(data, 1, invalidByteOrder);
    print0x9101(os, value, nullptr);
    EXPECT_EQ("Cr", os.str());
}

// Test with single R component
TEST_F(Print0x9101Test_1399, SingleR_1399) {
    UndefinedValue value;
    byte data[] = {4};
    value.read(data, 1, invalidByteOrder);
    print0x9101(os, value, nullptr);
    EXPECT_EQ("R", os.str());
}

// Test with single G component
TEST_F(Print0x9101Test_1399, SingleG_1399) {
    UndefinedValue value;
    byte data[] = {5};
    value.read(data, 1, invalidByteOrder);
    print0x9101(os, value, nullptr);
    EXPECT_EQ("G", os.str());
}

// Test with single B component
TEST_F(Print0x9101Test_1399, SingleB_1399) {
    UndefinedValue value;
    byte data[] = {6};
    value.read(data, 1, invalidByteOrder);
    print0x9101(os, value, nullptr);
    EXPECT_EQ("B", os.str());
}

// Test with unknown/default value
TEST_F(Print0x9101Test_1399, UnknownValue_1399) {
    UndefinedValue value;
    byte data[] = {7};
    value.read(data, 1, invalidByteOrder);
    print0x9101(os, value, nullptr);
    EXPECT_EQ("(7)", os.str());
}

// Test with another unknown value
TEST_F(Print0x9101Test_1399, UnknownValue255_1399) {
    UndefinedValue value;
    byte data[] = {255};
    value.read(data, 1, invalidByteOrder);
    print0x9101(os, value, nullptr);
    EXPECT_EQ("(255)", os.str());
}

// Test with mixed known and unknown values
TEST_F(Print0x9101Test_1399, MixedKnownAndUnknown_1399) {
    UndefinedValue value;
    byte data[] = {1, 7, 2};
    value.read(data, 3, invalidByteOrder);
    print0x9101(os, value, nullptr);
    EXPECT_EQ("Y(7)Cb", os.str());
}

// Test with zero in the middle
TEST_F(Print0x9101Test_1399, ZeroInMiddle_1399) {
    UndefinedValue value;
    byte data[] = {1, 0, 2};
    value.read(data, 3, invalidByteOrder);
    print0x9101(os, value, nullptr);
    EXPECT_EQ("YCb", os.str());
}

// Test with empty value (no elements)
TEST_F(Print0x9101Test_1399, EmptyValue_1399) {
    UndefinedValue value;
    print0x9101(os, value, nullptr);
    EXPECT_EQ("", os.str());
}

// Test full sequence: Y, Cb, Cr, R, G, B
TEST_F(Print0x9101Test_1399, AllComponents_1399) {
    UndefinedValue value;
    byte data[] = {1, 2, 3, 4, 5, 6};
    value.read(data, 6, invalidByteOrder);
    print0x9101(os, value, nullptr);
    EXPECT_EQ("YCbCrRGB", os.str());
}

// Test that the function returns the ostream reference
TEST_F(Print0x9101Test_1399, ReturnsOstream_1399) {
    UndefinedValue value;
    byte data[] = {1};
    value.read(data, 1, invalidByteOrder);
    std::ostream& result = print0x9101(os, value, nullptr);
    EXPECT_EQ(&os, &result);
}

// Test with multiple unknown values
TEST_F(Print0x9101Test_1399, MultipleUnknownValues_1399) {
    UndefinedValue value;
    byte data[] = {8, 10, 15};
    value.read(data, 3, invalidByteOrder);
    print0x9101(os, value, nullptr);
    EXPECT_EQ("(8)(10)(15)", os.str());
}

// Test with value 0 only (single zero)
TEST_F(Print0x9101Test_1399, SingleZero_1399) {
    UndefinedValue value;
    byte data[] = {0};
    value.read(data, 1, invalidByteOrder);
    print0x9101(os, value, nullptr);
    EXPECT_EQ("", os.str());
}

// Test typical EXIF ComponentsConfiguration: YCbCr with trailing zero (4,5,6,0 typical for Exif)
TEST_F(Print0x9101Test_1399, TypicalExifYCbCrConfig_1399) {
    UndefinedValue value;
    byte data[] = {1, 2, 3, 0};
    value.read(data, 4, invalidByteOrder);
    print0x9101(os, value, nullptr);
    EXPECT_EQ("YCbCr", os.str());
}

// Test with value just at boundary (value = 6, the last known)
TEST_F(Print0x9101Test_1399, BoundaryValueSix_1399) {
    UndefinedValue value;
    byte data[] = {6};
    value.read(data, 1, invalidByteOrder);
    print0x9101(os, value, nullptr);
    EXPECT_EQ("B", os.str());
}

// Test with value just past boundary (value = 7, first unknown)
TEST_F(Print0x9101Test_1399, BoundaryValueSeven_1399) {
    UndefinedValue value;
    byte data[] = {7};
    value.read(data, 1, invalidByteOrder);
    print0x9101(os, value, nullptr);
    EXPECT_EQ("(7)", os.str());
}
