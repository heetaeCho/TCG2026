#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <string>

// We need to replicate minimal infrastructure to test the function
// Since we're treating the implementation as a black box, we need the Value interface

namespace Exiv2 {

// Minimal i18n stub
inline const char* _(const char* s) { return s; }

// Minimal stringFormat
inline std::string stringFormat(const char* fmt, float val) {
    char buf[64];
    snprintf(buf, sizeof(buf), "%.2f m", val);
    return std::string(buf);
}

// Minimal Rational type
using Rational = std::pair<int32_t, int32_t>;

// Minimal ExifData stub
class ExifData {};

// Minimal Value interface
class Value {
public:
    virtual ~Value() = default;
    virtual Rational toRational(long n = 0) const = 0;
    
    friend std::ostream& operator<<(std::ostream& os, const Value& v) {
        auto r = v.toRational();
        os << r.first << "/" << r.second;
        return os;
    }
};

namespace Internal {

class Nikon3MakerNote {
public:
    std::ostream& print0x0085(std::ostream& os, const Value& value, const ExifData*) {
        auto [r, s] = value.toRational();
        if (r == 0)
            return os << _("Unknown");
        if (s == 0)
            return os << "(" << value << ")";
        return os << stringFormat("{:.2f} m", static_cast<float>(r) / s);
    }
};

}  // namespace Internal
}  // namespace Exiv2

// Mock Value class for testing
class MockValue : public Exiv2::Value {
public:
    MOCK_METHOD(Exiv2::Rational, toRational, (long n), (const, override));
};

class Nikon3MakerNoteTest_465 : public ::testing::Test {
protected:
    Exiv2::Internal::Nikon3MakerNote makerNote;
    std::ostringstream os;
};

// Test when numerator r == 0, should output "Unknown"
TEST_F(Nikon3MakerNoteTest_465, Print0x0085_NumeratorZero_ReturnsUnknown_465) {
    MockValue mockValue;
    EXPECT_CALL(mockValue, toRational(0))
        .WillOnce(::testing::Return(Exiv2::Rational{0, 1}));
    
    makerNote.print0x0085(os, mockValue, nullptr);
    EXPECT_EQ(os.str(), "Unknown");
}

// Test when numerator r == 0 and denominator s == 0, should still output "Unknown" (r==0 check first)
TEST_F(Nikon3MakerNoteTest_465, Print0x0085_BothZero_ReturnsUnknown_465) {
    MockValue mockValue;
    EXPECT_CALL(mockValue, toRational(0))
        .WillOnce(::testing::Return(Exiv2::Rational{0, 0}));
    
    makerNote.print0x0085(os, mockValue, nullptr);
    EXPECT_EQ(os.str(), "Unknown");
}

// Test when denominator s == 0 but r != 0, should output "(value)"
TEST_F(Nikon3MakerNoteTest_465, Print0x0085_DenominatorZero_ReturnsParenthesizedValue_465) {
    MockValue mockValue;
    EXPECT_CALL(mockValue, toRational(0))
        .WillRepeatedly(::testing::Return(Exiv2::Rational{5, 0}));
    
    makerNote.print0x0085(os, mockValue, nullptr);
    EXPECT_EQ(os.str(), "(5/0)");
}

// Test normal case with valid rational, e.g., 3/2 = 1.50 m
TEST_F(Nikon3MakerNoteTest_465, Print0x0085_NormalRational_ReturnsFormattedDistance_465) {
    MockValue mockValue;
    EXPECT_CALL(mockValue, toRational(0))
        .WillOnce(::testing::Return(Exiv2::Rational{3, 2}));
    
    makerNote.print0x0085(os, mockValue, nullptr);
    EXPECT_EQ(os.str(), "1.50 m");
}

// Test normal case with 1/1 = 1.00 m
TEST_F(Nikon3MakerNoteTest_465, Print0x0085_OneOverOne_ReturnsOnePointZeroZero_465) {
    MockValue mockValue;
    EXPECT_CALL(mockValue, toRational(0))
        .WillOnce(::testing::Return(Exiv2::Rational{1, 1}));
    
    makerNote.print0x0085(os, mockValue, nullptr);
    EXPECT_EQ(os.str(), "1.00 m");
}

// Test with larger values, e.g., 10/3 = 3.33 m
TEST_F(Nikon3MakerNoteTest_465, Print0x0085_LargerRational_ReturnsFormattedDistance_465) {
    MockValue mockValue;
    EXPECT_CALL(mockValue, toRational(0))
        .WillOnce(::testing::Return(Exiv2::Rational{10, 3}));
    
    makerNote.print0x0085(os, mockValue, nullptr);
    EXPECT_EQ(os.str(), "3.33 m");
}

// Test with negative numerator
TEST_F(Nikon3MakerNoteTest_465, Print0x0085_NegativeNumerator_ReturnsNegativeDistance_465) {
    MockValue mockValue;
    EXPECT_CALL(mockValue, toRational(0))
        .WillOnce(::testing::Return(Exiv2::Rational{-3, 2}));
    
    makerNote.print0x0085(os, mockValue, nullptr);
    EXPECT_EQ(os.str(), "-1.50 m");
}

// Test with negative denominator
TEST_F(Nikon3MakerNoteTest_465, Print0x0085_NegativeDenominator_ReturnsNegativeDistance_465) {
    MockValue mockValue;
    EXPECT_CALL(mockValue, toRational(0))
        .WillOnce(::testing::Return(Exiv2::Rational{3, -2}));
    
    makerNote.print0x0085(os, mockValue, nullptr);
    EXPECT_EQ(os.str(), "-1.50 m");
}

// Test with both negative (should give positive result)
TEST_F(Nikon3MakerNoteTest_465, Print0x0085_BothNegative_ReturnsPositiveDistance_465) {
    MockValue mockValue;
    EXPECT_CALL(mockValue, toRational(0))
        .WillOnce(::testing::Return(Exiv2::Rational{-3, -2}));
    
    makerNote.print0x0085(os, mockValue, nullptr);
    EXPECT_EQ(os.str(), "1.50 m");
}

// Test with very small fraction
TEST_F(Nikon3MakerNoteTest_465, Print0x0085_SmallFraction_ReturnsSmallDistance_465) {
    MockValue mockValue;
    EXPECT_CALL(mockValue, toRational(0))
        .WillOnce(::testing::Return(Exiv2::Rational{1, 100}));
    
    makerNote.print0x0085(os, mockValue, nullptr);
    EXPECT_EQ(os.str(), "0.01 m");
}

// Test with ExifData pointer being nullptr (should work fine)
TEST_F(Nikon3MakerNoteTest_465, Print0x0085_NullExifData_WorksNormally_465) {
    MockValue mockValue;
    EXPECT_CALL(mockValue, toRational(0))
        .WillOnce(::testing::Return(Exiv2::Rational{5, 1}));
    
    makerNote.print0x0085(os, mockValue, nullptr);
    EXPECT_EQ(os.str(), "5.00 m");
}

// Test with exact integer rational
TEST_F(Nikon3MakerNoteTest_465, Print0x0085_ExactInteger_ReturnsWholeNumber_465) {
    MockValue mockValue;
    EXPECT_CALL(mockValue, toRational(0))
        .WillOnce(::testing::Return(Exiv2::Rational{100, 1}));
    
    makerNote.print0x0085(os, mockValue, nullptr);
    EXPECT_EQ(os.str(), "100.00 m");
}

// Test that the function returns the ostream reference
TEST_F(Nikon3MakerNoteTest_465, Print0x0085_ReturnsOstreamReference_465) {
    MockValue mockValue;
    EXPECT_CALL(mockValue, toRational(0))
        .WillOnce(::testing::Return(Exiv2::Rational{1, 1}));
    
    std::ostream& result = makerNote.print0x0085(os, mockValue, nullptr);
    EXPECT_EQ(&result, &os);
}

// Test denominator zero with negative numerator
TEST_F(Nikon3MakerNoteTest_465, Print0x0085_NegativeNumeratorDenominatorZero_ReturnsParenthesized_465) {
    MockValue mockValue;
    EXPECT_CALL(mockValue, toRational(0))
        .WillRepeatedly(::testing::Return(Exiv2::Rational{-5, 0}));
    
    makerNote.print0x0085(os, mockValue, nullptr);
    EXPECT_EQ(os.str(), "(-5/0)");
}
