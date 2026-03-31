#include <gtest/gtest.h>
#include <sstream>
#include <cmath>
#include <exiv2/exiv2.hpp>
#include "nikonmn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class Nikon3MakerNoteTest_507 : public ::testing::Test {
protected:
    std::ostringstream os;
};

// Helper to create an UnsignedShort value with a single entry
static Exiv2::UShortValue makeUShortValue(uint16_t v) {
    Exiv2::UShortValue val;
    val.value_.push_back(v);
    return val;
}

// Test: Normal aperture value produces expected F-stop string
TEST_F(Nikon3MakerNoteTest_507, NormalApertureValue_507) {
    // For a typical aperture value, verify it outputs something starting with "F"
    Exiv2::UShortValue val;
    val.value_.push_back(512);

    Nikon3MakerNote maker;
    maker.printApertureLd4(os, val, nullptr);

    std::string result = os.str();
    EXPECT_EQ(result.substr(0, 1), "F");
}

// Test: Value of 0 should return "n/a"
TEST_F(Nikon3MakerNoteTest_507, ZeroValueReturnsNA_507) {
    Exiv2::UShortValue val;
    val.value_.push_back(0);

    Nikon3MakerNote maker;
    maker.printApertureLd4(os, val, nullptr);

    std::string result = os.str();
    // "n/a" is the translated string; in default locale it should be "n/a"
    EXPECT_NE(result.find("n/a"), std::string::npos);
}

// Test: Wrong type (not unsignedShort) should return parenthesized value
TEST_F(Nikon3MakerNoteTest_507, WrongTypeReturnsParenthesized_507) {
    Exiv2::StringValue val;
    val.read("hello");

    Nikon3MakerNote maker;
    maker.printApertureLd4(os, val, nullptr);

    std::string result = os.str();
    EXPECT_EQ(result.front(), '(');
    EXPECT_EQ(result.back(), ')');
}

// Test: Multiple values (count != 1) should return parenthesized value
TEST_F(Nikon3MakerNoteTest_507, MultipleValuesReturnsParenthesized_507) {
    Exiv2::UShortValue val;
    val.value_.push_back(384);
    val.value_.push_back(512);

    Nikon3MakerNote maker;
    maker.printApertureLd4(os, val, nullptr);

    std::string result = os.str();
    EXPECT_EQ(result.front(), '(');
    EXPECT_EQ(result.back(), ')');
}

// Test: Value of 384 should produce F1.0 (2^((384/384)-1) = 2^0 = 1.0)
TEST_F(Nikon3MakerNoteTest_507, Value384ProducesF1_507) {
    Exiv2::UShortValue val;
    val.value_.push_back(384);

    Nikon3MakerNote maker;
    maker.printApertureLd4(os, val, nullptr);

    std::string result = os.str();
    EXPECT_EQ(result, "F1.0");
}

// Test: Value of 768 should produce F2.0 (2^((768/384)-1) = 2^1 = 2.0)
TEST_F(Nikon3MakerNoteTest_507, Value768ProducesF2_507) {
    Exiv2::UShortValue val;
    val.value_.push_back(768);

    Nikon3MakerNote maker;
    maker.printApertureLd4(os, val, nullptr);

    std::string result = os.str();
    EXPECT_EQ(result, "F2.0");
}

// Test: Value of 1152 should produce F4.0 (2^((1152/384)-1) = 2^2 = 4.0)
TEST_F(Nikon3MakerNoteTest_507, Value1152ProducesF4_507) {
    Exiv2::UShortValue val;
    val.value_.push_back(1152);

    Nikon3MakerNote maker;
    maker.printApertureLd4(os, val, nullptr);

    std::string result = os.str();
    EXPECT_EQ(result, "F4.0");
}

// Test: Value of 1536 should produce F8.0 (2^((1536/384)-1) = 2^3 = 8.0)
TEST_F(Nikon3MakerNoteTest_507, Value1536ProducesF8_507) {
    Exiv2::UShortValue val;
    val.value_.push_back(1536);

    Nikon3MakerNote maker;
    maker.printApertureLd4(os, val, nullptr);

    std::string result = os.str();
    EXPECT_EQ(result, "F8.0");
}

// Test: Small non-zero value (e.g., 1) should produce a valid F-number
TEST_F(Nikon3MakerNoteTest_507, SmallNonZeroValue_507) {
    Exiv2::UShortValue val;
    val.value_.push_back(1);

    Nikon3MakerNote maker;
    maker.printApertureLd4(os, val, nullptr);

    std::string result = os.str();
    // Should start with F since it's non-zero
    EXPECT_EQ(result.substr(0, 1), "F");
}

// Test: Maximum uint16 value should produce a valid F-number
TEST_F(Nikon3MakerNoteTest_507, MaxUint16Value_507) {
    Exiv2::UShortValue val;
    val.value_.push_back(65535);

    Nikon3MakerNote maker;
    maker.printApertureLd4(os, val, nullptr);

    std::string result = os.str();
    EXPECT_EQ(result.substr(0, 1), "F");
}

// Test: nullptr ExifData parameter should not cause issues
TEST_F(Nikon3MakerNoteTest_507, NullExifDataParam_507) {
    Exiv2::UShortValue val;
    val.value_.push_back(384);

    Nikon3MakerNote maker;
    // Should not crash with nullptr
    maker.printApertureLd4(os, val, nullptr);

    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// Test: Wrong type - using signed long instead of unsigned short
TEST_F(Nikon3MakerNoteTest_507, SignedLongTypeReturnsParenthesized_507) {
    Exiv2::LongValue val;
    val.value_.push_back(384);

    Nikon3MakerNote maker;
    maker.printApertureLd4(os, val, nullptr);

    std::string result = os.str();
    EXPECT_EQ(result.front(), '(');
    EXPECT_EQ(result.back(), ')');
}

// Test: Empty value (count == 0) should return parenthesized
TEST_F(Nikon3MakerNoteTest_507, EmptyValueReturnsParenthesized_507) {
    Exiv2::UShortValue val;
    // No values pushed - count is 0

    Nikon3MakerNote maker;
    maker.printApertureLd4(os, val, nullptr);

    std::string result = os.str();
    EXPECT_EQ(result.front(), '(');
    EXPECT_EQ(result.back(), ')');
}

// Test: Return value is the same ostream reference
TEST_F(Nikon3MakerNoteTest_507, ReturnsOstreamReference_507) {
    Exiv2::UShortValue val;
    val.value_.push_back(384);

    Nikon3MakerNote maker;
    std::ostream& returned = maker.printApertureLd4(os, val, nullptr);

    EXPECT_EQ(&returned, &os);
}
