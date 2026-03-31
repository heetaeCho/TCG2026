#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/value.hpp>
#include <exiv2/exif.hpp>

// We need access to the printDegrees function
namespace Exiv2 {
namespace Internal {
std::ostream& printDegrees(std::ostream& os, const Value& value, const ExifData*);
}
}

using namespace Exiv2;

class PrintDegreesTest_1379 : public ::testing::Test {
protected:
    std::ostringstream os;

    // Helper to create a URationalValue with 3 rationals
    std::unique_ptr<URationalValue> makeURationalValue(
        URational r1, URational r2, URational r3) {
        auto val = std::make_unique<URationalValue>();
        val->value_.push_back(r1);
        val->value_.push_back(r2);
        val->value_.push_back(r3);
        return val;
    }

    // Helper to create a RationalValue with 3 rationals (signed)
    std::unique_ptr<RationalValue> makeRationalValue(
        Rational r1, Rational r2, Rational r3) {
        auto val = std::make_unique<RationalValue>();
        val->value_.push_back(r1);
        val->value_.push_back(r2);
        val->value_.push_back(r3);
        return val;
    }
};

// Test normal case: 3 rationals representing degrees, minutes, seconds with integer values
TEST_F(PrintDegreesTest_1379, NormalIntegerDegMinSec_1379) {
    auto val = makeRationalValue({45, 1}, {30, 1}, {15, 1});
    Internal::printDegrees(os, *val, nullptr);
    EXPECT_EQ(os.str(), "45 deg 30' 15\"");
}

// Test normal case with fractional seconds
TEST_F(PrintDegreesTest_1379, NormalFractionalSeconds_1379) {
    auto val = makeRationalValue({45, 1}, {30, 1}, {1550, 100});
    Internal::printDegrees(os, *val, nullptr);
    EXPECT_EQ(os.str(), "45 deg 30' 15.50\"");
}

// Test case where value count is not 3 (e.g., 2 values)
TEST_F(PrintDegreesTest_1379, CountNotThree_TwoValues_1379) {
    auto val = std::make_unique<RationalValue>();
    val->value_.push_back({45, 1});
    val->value_.push_back({30, 1});
    Internal::printDegrees(os, *val, nullptr);
    std::string result = os.str();
    EXPECT_EQ(result[0], '(');
    EXPECT_EQ(result[result.size() - 1], ')');
}

// Test case where value count is not 3 (e.g., 4 values)
TEST_F(PrintDegreesTest_1379, CountNotThree_FourValues_1379) {
    auto val = std::make_unique<RationalValue>();
    val->value_.push_back({45, 1});
    val->value_.push_back({30, 1});
    val->value_.push_back({15, 1});
    val->value_.push_back({0, 1});
    Internal::printDegrees(os, *val, nullptr);
    std::string result = os.str();
    EXPECT_EQ(result[0], '(');
    EXPECT_EQ(result[result.size() - 1], ')');
}

// Test case where deg.second != 1 -> parenthesized output
TEST_F(PrintDegreesTest_1379, DegSecondNotOne_1379) {
    auto val = makeRationalValue({90, 2}, {30, 1}, {15, 1});
    Internal::printDegrees(os, *val, nullptr);
    std::string result = os.str();
    EXPECT_EQ(result[0], '(');
    EXPECT_EQ(result[result.size() - 1], ')');
}

// Test case where min.second <= 0 -> parenthesized output
TEST_F(PrintDegreesTest_1379, MinSecondZero_1379) {
    auto val = makeRationalValue({45, 1}, {30, 0}, {15, 1});
    Internal::printDegrees(os, *val, nullptr);
    std::string result = os.str();
    EXPECT_EQ(result[0], '(');
    EXPECT_EQ(result[result.size() - 1], ')');
}

// Test case where sec.second <= 0 -> parenthesized output
TEST_F(PrintDegreesTest_1379, SecSecondZero_1379) {
    auto val = makeRationalValue({45, 1}, {30, 1}, {15, 0});
    Internal::printDegrees(os, *val, nullptr);
    std::string result = os.str();
    EXPECT_EQ(result[0], '(');
    EXPECT_EQ(result[result.size() - 1], ')');
}

// Test case: minutes with fractional part, seconds are 0/1 -> seconds computed from remainder
TEST_F(PrintDegreesTest_1379, FractionalMinutesConvertedToSeconds_1379) {
    // min = 30.5 = 61/2, sec = 0/1
    // rem = 61 % 2 = 1, sec.first = 60 * 1 = 60, sec.second = 2 -> 30.00 seconds
    auto val = makeRationalValue({45, 1}, {61, 2}, {0, 1});
    Internal::printDegrees(os, *val, nullptr);
    EXPECT_EQ(os.str(), "45 deg 30' 30.00\"");
}

// Test case: minutes with fractional part but seconds are non-zero -> parenthesized
TEST_F(PrintDegreesTest_1379, FractionalMinutesNonZeroSeconds_1379) {
    // min = 61/2, sec = 10/1 (non-zero)
    auto val = makeRationalValue({45, 1}, {61, 2}, {10, 1});
    Internal::printDegrees(os, *val, nullptr);
    std::string result = os.str();
    EXPECT_EQ(result[0], '(');
    EXPECT_EQ(result[result.size() - 1], ')');
}

// Test zero degrees, zero minutes, zero seconds
TEST_F(PrintDegreesTest_1379, AllZero_1379) {
    auto val = makeRationalValue({0, 1}, {0, 1}, {0, 1});
    Internal::printDegrees(os, *val, nullptr);
    EXPECT_EQ(os.str(), "0 deg 0' 0\"");
}

// Test with exactly 0 seconds but sec.second = 1 -> no decimal places
TEST_F(PrintDegreesTest_1379, ZeroSecondsIntegerPrecision_1379) {
    auto val = makeRationalValue({90, 1}, {0, 1}, {0, 1});
    Internal::printDegrees(os, *val, nullptr);
    EXPECT_EQ(os.str(), "90 deg 0' 0\"");
}

// Test with sec.second > 1 -> 2 decimal places
TEST_F(PrintDegreesTest_1379, SecondsPrecisionTwoDecimals_1379) {
    auto val = makeRationalValue({10, 1}, {20, 1}, {75, 10});
    Internal::printDegrees(os, *val, nullptr);
    EXPECT_EQ(os.str(), "10 deg 20' 7.50\"");
}

// Test with empty value (count == 0)
TEST_F(PrintDegreesTest_1379, EmptyValue_1379) {
    auto val = std::make_unique<RationalValue>();
    Internal::printDegrees(os, *val, nullptr);
    std::string result = os.str();
    EXPECT_EQ(result[0], '(');
    EXPECT_EQ(result[result.size() - 1], ')');
}

// Test that the function returns the same ostream reference
TEST_F(PrintDegreesTest_1379, ReturnsOstreamReference_1379) {
    auto val = makeRationalValue({45, 1}, {30, 1}, {15, 1});
    std::ostream& result = Internal::printDegrees(os, *val, nullptr);
    EXPECT_EQ(&result, &os);
}

// Test that the function restores format flags
TEST_F(PrintDegreesTest_1379, RestoresFormatFlags_1379) {
    auto val = makeRationalValue({45, 1}, {30, 1}, {1550, 100});
    std::ios::fmtflags before = os.flags();
    Internal::printDegrees(os, *val, nullptr);
    std::ios::fmtflags after = os.flags();
    EXPECT_EQ(before, after);
}

// Test with min.second negative -> parenthesized (min.second <= 0)
TEST_F(PrintDegreesTest_1379, MinSecondNegative_1379) {
    auto val = makeRationalValue({45, 1}, {30, -1}, {15, 1});
    Internal::printDegrees(os, *val, nullptr);
    std::string result = os.str();
    EXPECT_EQ(result[0], '(');
    EXPECT_EQ(result[result.size() - 1], ')');
}

// Test with sec.second negative -> parenthesized (sec.second <= 0)
TEST_F(PrintDegreesTest_1379, SecSecondNegative_1379) {
    auto val = makeRationalValue({45, 1}, {30, 1}, {15, -1});
    Internal::printDegrees(os, *val, nullptr);
    std::string result = os.str();
    EXPECT_EQ(result[0], '(');
    EXPECT_EQ(result[result.size() - 1], ')');
}

// Test large degree values
TEST_F(PrintDegreesTest_1379, LargeDegreeValue_1379) {
    auto val = makeRationalValue({359, 1}, {59, 1}, {59, 1});
    Internal::printDegrees(os, *val, nullptr);
    EXPECT_EQ(os.str(), "359 deg 59' 59\"");
}

// Test fractional minutes conversion where remainder * 60 would overflow
TEST_F(PrintDegreesTest_1379, FractionalMinutesOverflowCheck_1379) {
    // rem that when multiplied by 60 would overflow int32_t
    // max / 60 ~ 35791394, so rem = 35791395 would overflow
    // min = (35791395 * 2 + 1) / 2 => too large? Let's construct carefully.
    // min.first = large, min.second = 2, rem = min.first % 2
    // We need rem > max/60. Let's use min.first = 2*35791395 + 1 = 71582791, min.second = 2
    // rem = 71582791 % 2 = 1. That's not > max/60.
    // We need min.second > 1 and rem > max/60.
    // Use min.second = 3, min.first such that min.first % 3 > max/60
    // max/60 = 35791394. So rem = 35791395. min.first = 35791395 (which gives rem = 35791395 % 3 = 0). Not useful.
    // Let min.first = 35791395 * 3 + 35791395 = ... complicated.
    // Actually rem = min.first % min.second. We need rem > max/60.
    // Let min.second = 35791396, min.first = 35791396 + 35791395 = 71582791
    // rem = 71582791 % 35791396 = 35791395, which is > 35791394
    // sec must be {0, 1}
    auto val = makeRationalValue({10, 1}, {71582791, 35791396}, {0, 1});
    Internal::printDegrees(os, *val, nullptr);
    std::string result = os.str();
    // Should be parenthesized because rem > max/60
    EXPECT_EQ(result[0], '(');
    EXPECT_EQ(result[result.size() - 1], ')');
}

// Test count of 1
TEST_F(PrintDegreesTest_1379, CountOne_1379) {
    auto val = std::make_unique<RationalValue>();
    val->value_.push_back({45, 1});
    Internal::printDegrees(os, *val, nullptr);
    std::string result = os.str();
    EXPECT_EQ(result[0], '(');
    EXPECT_EQ(result[result.size() - 1], ')');
}

// Test with URational values (unsigned)
TEST_F(PrintDegreesTest_1379, URationalNormalCase_1379) {
    auto val = makeURationalValue({45, 1}, {30, 1}, {15, 1});
    Internal::printDegrees(os, *val, nullptr);
    EXPECT_EQ(os.str(), "45 deg 30' 15\"");
}

// Test minutes with no remainder (min.second > 1 but rem == 0) -> normal case
TEST_F(PrintDegreesTest_1379, MinSecondGreaterThanOneButNoRemainder_1379) {
    // min = 60/2 = 30, rem = 0
    auto val = makeRationalValue({45, 1}, {60, 2}, {15, 1});
    Internal::printDegrees(os, *val, nullptr);
    EXPECT_EQ(os.str(), "45 deg 30' 15\"");
}
