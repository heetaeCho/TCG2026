#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/value.hpp>
#include <exiv2/exif.hpp>

using namespace Exiv2;

namespace Exiv2 {
namespace Internal {
std::ostream& print0x0007(std::ostream& os, const Value& value, const ExifData*);
}
}

class Print0x0007Test_1386 : public ::testing::Test {
protected:
    std::ostringstream os;
};

// Test normal GPS time with 3 rational values representing HH:MM:SS
TEST_F(Print0x0007Test_1386, NormalTime_ThreeRationals_1386) {
    URationalValue value;
    value.value_.push_back({10, 1});  // 10 hours
    value.value_.push_back({30, 1});  // 30 minutes
    value.value_.push_back({45, 1});  // 45 seconds
    
    Exiv2::Internal::print0x0007(os, value, nullptr);
    EXPECT_EQ(os.str(), "10:30:45");
}

// Test midnight time 00:00:00
TEST_F(Print0x0007Test_1386, MidnightTime_1386) {
    URationalValue value;
    value.value_.push_back({0, 1});
    value.value_.push_back({0, 1});
    value.value_.push_back({0, 1});
    
    Exiv2::Internal::print0x0007(os, value, nullptr);
    EXPECT_EQ(os.str(), "00:00:00");
}

// Test time with single digit hours and minutes (padding check)
TEST_F(Print0x0007Test_1386, SingleDigitHoursMinutes_1386) {
    URationalValue value;
    value.value_.push_back({1, 1});   // 1 hour
    value.value_.push_back({2, 1});   // 2 minutes
    value.value_.push_back({3, 1});   // 3 seconds
    
    Exiv2::Internal::print0x0007(os, value, nullptr);
    EXPECT_EQ(os.str(), "01:02:03");
}

// Test time 23:59:59
TEST_F(Print0x0007Test_1386, MaxTime_1386) {
    URationalValue value;
    value.value_.push_back({23, 1});
    value.value_.push_back({59, 1});
    value.value_.push_back({59, 1});
    
    Exiv2::Internal::print0x0007(os, value, nullptr);
    EXPECT_EQ(os.str(), "23:59:59");
}

// Test when value count is not 3 — should just print the value directly
TEST_F(Print0x0007Test_1386, NonThreeCount_PrintsValueDirectly_1386) {
    URationalValue value;
    value.value_.push_back({10, 1});
    value.value_.push_back({30, 1});
    // Only 2 values
    
    Exiv2::Internal::print0x0007(os, value, nullptr);
    std::string result = os.str();
    // Should output the value directly (not formatted as time)
    EXPECT_FALSE(result.empty());
}

// Test when one rational has denominator 0 — should return raw value in parens
TEST_F(Print0x0007Test_1386, ZeroDenominator_ReturnsRawInParens_1386) {
    URationalValue value;
    value.value_.push_back({10, 1});
    value.value_.push_back({30, 0});  // denominator is 0
    value.value_.push_back({45, 1});
    
    Exiv2::Internal::print0x0007(os, value, nullptr);
    std::string result = os.str();
    EXPECT_EQ(result.front(), '(');
    EXPECT_EQ(result.back(), ')');
}

// Test when first rational has denominator 0
TEST_F(Print0x0007Test_1386, FirstDenominatorZero_ReturnsRawInParens_1386) {
    URationalValue value;
    value.value_.push_back({10, 0});
    value.value_.push_back({30, 1});
    value.value_.push_back({45, 1});
    
    Exiv2::Internal::print0x0007(os, value, nullptr);
    std::string result = os.str();
    EXPECT_EQ(result.front(), '(');
    EXPECT_EQ(result.back(), ')');
}

// Test when third rational has denominator 0
TEST_F(Print0x0007Test_1386, ThirdDenominatorZero_ReturnsRawInParens_1386) {
    URationalValue value;
    value.value_.push_back({10, 1});
    value.value_.push_back({30, 1});
    value.value_.push_back({45, 0});
    
    Exiv2::Internal::print0x0007(os, value, nullptr);
    std::string result = os.str();
    EXPECT_EQ(result.front(), '(');
    EXPECT_EQ(result.back(), ')');
}

// Test fractional seconds (e.g., 10h 30m 45.5s)
TEST_F(Print0x0007Test_1386, FractionalSeconds_1386) {
    URationalValue value;
    value.value_.push_back({10, 1});
    value.value_.push_back({30, 1});
    value.value_.push_back({91, 2});  // 45.5 seconds
    
    Exiv2::Internal::print0x0007(os, value, nullptr);
    std::string result = os.str();
    // Should contain fractional seconds with precision 1
    EXPECT_NE(result.find('.'), std::string::npos);
    EXPECT_EQ(result.substr(0, 5), "10:30");
}

// Test with empty value (count = 0)
TEST_F(Print0x0007Test_1386, EmptyValue_1386) {
    URationalValue value;
    // No values added
    
    Exiv2::Internal::print0x0007(os, value, nullptr);
    // Should just print the value directly (not formatted)
    // Empty value should produce some output
}

// Test with single value
TEST_F(Print0x0007Test_1386, SingleValue_1386) {
    URationalValue value;
    value.value_.push_back({10, 1});
    
    Exiv2::Internal::print0x0007(os, value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// Test 12:00:00 (noon)
TEST_F(Print0x0007Test_1386, NoonTime_1386) {
    URationalValue value;
    value.value_.push_back({12, 1});
    value.value_.push_back({0, 1});
    value.value_.push_back({0, 1});
    
    Exiv2::Internal::print0x0007(os, value, nullptr);
    EXPECT_EQ(os.str(), "12:00:00");
}

// Test that the function returns the stream reference
TEST_F(Print0x0007Test_1386, ReturnsStreamReference_1386) {
    URationalValue value;
    value.value_.push_back({10, 1});
    value.value_.push_back({30, 1});
    value.value_.push_back({45, 1});
    
    std::ostream& result = Exiv2::Internal::print0x0007(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

// Test with nullptr ExifData (should not crash)
TEST_F(Print0x0007Test_1386, NullExifData_1386) {
    URationalValue value;
    value.value_.push_back({5, 1});
    value.value_.push_back({15, 1});
    value.value_.push_back({30, 1});
    
    EXPECT_NO_THROW(Exiv2::Internal::print0x0007(os, value, nullptr));
    EXPECT_EQ(os.str(), "05:15:30");
}

// Test all denominators zero
TEST_F(Print0x0007Test_1386, AllDenominatorsZero_1386) {
    URationalValue value;
    value.value_.push_back({0, 0});
    value.value_.push_back({0, 0});
    value.value_.push_back({0, 0});
    
    Exiv2::Internal::print0x0007(os, value, nullptr);
    std::string result = os.str();
    EXPECT_EQ(result.front(), '(');
    EXPECT_EQ(result.back(), ')');
}

// Test that stream flags are preserved after the call
TEST_F(Print0x0007Test_1386, StreamFlagsPreserved_1386) {
    URationalValue value;
    value.value_.push_back({10, 1});
    value.value_.push_back({30, 1});
    value.value_.push_back({45, 1});
    
    os << std::hex;
    std::ios::fmtflags before = os.flags();
    Exiv2::Internal::print0x0007(os, value, nullptr);
    std::ios::fmtflags after = os.flags();
    EXPECT_EQ(before, after);
}

// Test with rationals that simplify to whole numbers
TEST_F(Print0x0007Test_1386, RationalsSimplifyToWholeNumbers_1386) {
    URationalValue value;
    value.value_.push_back({20, 2});   // 10 hours
    value.value_.push_back({60, 2});   // 30 minutes
    value.value_.push_back({90, 2});   // 45 seconds
    
    Exiv2::Internal::print0x0007(os, value, nullptr);
    EXPECT_EQ(os.str(), "10:30:45");
}

// Test with 4 values (count != 3)
TEST_F(Print0x0007Test_1386, FourValues_1386) {
    URationalValue value;
    value.value_.push_back({10, 1});
    value.value_.push_back({30, 1});
    value.value_.push_back({45, 1});
    value.value_.push_back({0, 1});
    
    Exiv2::Internal::print0x0007(os, value, nullptr);
    // Should fall through to direct print since count != 3
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}
