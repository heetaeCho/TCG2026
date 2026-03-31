#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <exiv2/value.hpp>
#include <exiv2/exif.hpp>

// We need access to the Internal namespace function
namespace Exiv2 {
namespace Internal {
std::ostream& printInt64(std::ostream& os, const Value& value, const ExifData*);
}
}

using namespace Exiv2;
using namespace Exiv2::Internal;

class PrintInt64Test_1377 : public ::testing::Test {
protected:
    std::ostringstream os;
};

// Test normal positive rational value where second > 0
TEST_F(PrintInt64Test_1377, PositiveRationalPrintsQuotient_1377) {
    RationalValue val;
    val.value_.push_back(Rational(10, 2));
    
    printInt64(os, val, nullptr);
    
    EXPECT_EQ(os.str(), "5");
}

// Test rational value with numerator 0 and positive denominator
TEST_F(PrintInt64Test_1377, ZeroNumeratorPrintsZero_1377) {
    RationalValue val;
    val.value_.push_back(Rational(0, 1));
    
    printInt64(os, val, nullptr);
    
    EXPECT_EQ(os.str(), "0");
}

// Test rational with denominator = 0 should print parenthesized form
TEST_F(PrintInt64Test_1377, ZeroDenominatorPrintsParenthesized_1377) {
    RationalValue val;
    val.value_.push_back(Rational(5, 0));
    
    printInt64(os, val, nullptr);
    
    std::string result = os.str();
    EXPECT_EQ(result.front(), '(');
    EXPECT_EQ(result.back(), ')');
}

// Test negative denominator (which is <= 0) should print parenthesized
TEST_F(PrintInt64Test_1377, NegativeDenominatorPrintsParenthesized_1377) {
    RationalValue val;
    val.value_.push_back(Rational(10, -2));
    
    printInt64(os, val, nullptr);
    
    std::string result = os.str();
    // Negative denominator means second <= 0, so it goes to the parenthesized branch
    EXPECT_EQ(result.front(), '(');
    EXPECT_EQ(result.back(), ')');
}

// Test rational with large positive values
TEST_F(PrintInt64Test_1377, LargePositiveValues_1377) {
    RationalValue val;
    val.value_.push_back(Rational(1000000, 1));
    
    printInt64(os, val, nullptr);
    
    EXPECT_EQ(os.str(), "1000000");
}

// Test rational with negative numerator and positive denominator
TEST_F(PrintInt64Test_1377, NegativeNumeratorPositiveDenominator_1377) {
    RationalValue val;
    val.value_.push_back(Rational(-10, 2));
    
    printInt64(os, val, nullptr);
    
    EXPECT_EQ(os.str(), "-5");
}

// Test integer division truncation behavior
TEST_F(PrintInt64Test_1377, IntegerDivisionTruncates_1377) {
    RationalValue val;
    val.value_.push_back(Rational(7, 2));
    
    printInt64(os, val, nullptr);
    
    // 7/2 = 3 with integer division (int64_t cast then divide)
    EXPECT_EQ(os.str(), "3");
}

// Test rational 1/1 prints 1
TEST_F(PrintInt64Test_1377, OneOverOnePrintsOne_1377) {
    RationalValue val;
    val.value_.push_back(Rational(1, 1));
    
    printInt64(os, val, nullptr);
    
    EXPECT_EQ(os.str(), "1");
}

// Test that nullptr ExifData is acceptable
TEST_F(PrintInt64Test_1377, NullExifDataAccepted_1377) {
    RationalValue val;
    val.value_.push_back(Rational(42, 1));
    
    printInt64(os, val, nullptr);
    
    EXPECT_EQ(os.str(), "42");
}

// Test denominator of 1 with various numerators
TEST_F(PrintInt64Test_1377, DenominatorOneReturnsNumerator_1377) {
    RationalValue val;
    val.value_.push_back(Rational(12345, 1));
    
    printInt64(os, val, nullptr);
    
    EXPECT_EQ(os.str(), "12345");
}

// Test return value is the same ostream reference
TEST_F(PrintInt64Test_1377, ReturnsSameOstream_1377) {
    RationalValue val;
    val.value_.push_back(Rational(10, 2));
    
    std::ostream& result = printInt64(os, val, nullptr);
    
    EXPECT_EQ(&result, &os);
}

// Test return value is the same ostream reference for parenthesized branch
TEST_F(PrintInt64Test_1377, ReturnsSameOstreamForParenthesized_1377) {
    RationalValue val;
    val.value_.push_back(Rational(10, 0));
    
    std::ostream& result = printInt64(os, val, nullptr);
    
    EXPECT_EQ(&result, &os);
}

// Test with small fractional that truncates to zero
TEST_F(PrintInt64Test_1377, SmallFractionTruncatesToZero_1377) {
    RationalValue val;
    val.value_.push_back(Rational(1, 100));
    
    printInt64(os, val, nullptr);
    
    EXPECT_EQ(os.str(), "0");
}

// Test with negative numerator and fraction that truncates toward zero
TEST_F(PrintInt64Test_1377, NegativeSmallFractionTruncatesToZero_1377) {
    RationalValue val;
    val.value_.push_back(Rational(-1, 100));
    
    printInt64(os, val, nullptr);
    
    EXPECT_EQ(os.str(), "0");
}
