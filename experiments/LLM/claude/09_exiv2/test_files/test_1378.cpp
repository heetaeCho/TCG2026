#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/value.hpp>
#include <exiv2/exif.hpp>

// We need access to the Internal namespace function
namespace Exiv2 {
namespace Internal {
std::ostream& printFloat(std::ostream& os, const Value& value, const ExifData*);
}
}

using namespace Exiv2;
using namespace Exiv2::Internal;

class PrintFloatTest_1378 : public ::testing::Test {
protected:
    std::ostringstream os;
};

// Test normal rational value with non-zero denominator
TEST_F(PrintFloatTest_1378, NormalRationalValue_1378) {
    RationalValue value;
    value.value_.push_back(Rational(1, 2));
    printFloat(os, value, nullptr);
    // 1/2 = 0.5
    EXPECT_EQ(os.str(), "0.5");
}

// Test rational value with zero denominator - should print in parentheses format
TEST_F(PrintFloatTest_1378, ZeroDenominatorPrintsInParentheses_1378) {
    RationalValue value;
    value.value_.push_back(Rational(5, 0));
    printFloat(os, value, nullptr);
    std::string result = os.str();
    EXPECT_EQ(result.front(), '(');
    EXPECT_EQ(result.back(), ')');
}

// Test rational value 1/1 = 1.0
TEST_F(PrintFloatTest_1378, RationalOneOverOne_1378) {
    RationalValue value;
    value.value_.push_back(Rational(1, 1));
    printFloat(os, value, nullptr);
    EXPECT_EQ(os.str(), "1");
}

// Test rational value 0/1 = 0
TEST_F(PrintFloatTest_1378, RationalZeroOverOne_1378) {
    RationalValue value;
    value.value_.push_back(Rational(0, 1));
    printFloat(os, value, nullptr);
    EXPECT_EQ(os.str(), "0");
}

// Test rational value 0/0 - zero denominator so parenthesized
TEST_F(PrintFloatTest_1378, RationalZeroOverZero_1378) {
    RationalValue value;
    value.value_.push_back(Rational(0, 0));
    printFloat(os, value, nullptr);
    std::string result = os.str();
    EXPECT_EQ(result.front(), '(');
    EXPECT_EQ(result.back(), ')');
}

// Test negative rational value
TEST_F(PrintFloatTest_1378, NegativeRationalValue_1378) {
    RationalValue value;
    value.value_.push_back(Rational(-3, 4));
    printFloat(os, value, nullptr);
    EXPECT_EQ(os.str(), "-0.75");
}

// Test large rational value
TEST_F(PrintFloatTest_1378, LargeRationalValue_1378) {
    RationalValue value;
    value.value_.push_back(Rational(1000000, 1));
    printFloat(os, value, nullptr);
    EXPECT_EQ(os.str(), "1e+06");
}

// Test rational value with large denominator
TEST_F(PrintFloatTest_1378, SmallFractionRationalValue_1378) {
    RationalValue value;
    value.value_.push_back(Rational(1, 1000));
    printFloat(os, value, nullptr);
    EXPECT_EQ(os.str(), "0.001");
}

// Test that the function returns the same ostream reference
TEST_F(PrintFloatTest_1378, ReturnsSameOstream_1378) {
    RationalValue value;
    value.value_.push_back(Rational(1, 2));
    std::ostream& result = printFloat(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

// Test with nullptr ExifData (should work fine)
TEST_F(PrintFloatTest_1378, NullExifDataDoesNotCrash_1378) {
    RationalValue value;
    value.value_.push_back(Rational(7, 3));
    EXPECT_NO_THROW(printFloat(os, value, nullptr));
}

// Test negative denominator
TEST_F(PrintFloatTest_1378, NegativeDenominator_1378) {
    RationalValue value;
    value.value_.push_back(Rational(1, -2));
    printFloat(os, value, nullptr);
    EXPECT_EQ(os.str(), "-0.5");
}

// Test with an actual ExifData object (not null)
TEST_F(PrintFloatTest_1378, WithExifDataObject_1378) {
    RationalValue value;
    value.value_.push_back(Rational(3, 10));
    ExifData exifData;
    printFloat(os, value, &exifData);
    EXPECT_EQ(os.str(), "0.3");
}

// Test rational value where denominator is 0 and numerator is negative
TEST_F(PrintFloatTest_1378, NegativeNumeratorZeroDenominator_1378) {
    RationalValue value;
    value.value_.push_back(Rational(-5, 0));
    printFloat(os, value, nullptr);
    std::string result = os.str();
    EXPECT_EQ(result.front(), '(');
    EXPECT_EQ(result.back(), ')');
}

// Test with URationalValue (unsigned rational)
TEST_F(PrintFloatTest_1378, URationalValue_1378) {
    URationalValue value;
    value.value_.push_back(URational(3, 4));
    printFloat(os, value, nullptr);
    EXPECT_EQ(os.str(), "0.75");
}

// Test with URational zero denominator
TEST_F(PrintFloatTest_1378, URationalZeroDenominator_1378) {
    URationalValue value;
    value.value_.push_back(URational(10, 0));
    printFloat(os, value, nullptr);
    std::string result = os.str();
    EXPECT_EQ(result.front(), '(');
    EXPECT_EQ(result.back(), ')');
}
