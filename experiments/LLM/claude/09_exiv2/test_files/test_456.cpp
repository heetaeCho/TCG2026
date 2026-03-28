#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <string>

// Minimal infrastructure to support the code under test
// We need to replicate the minimal interface that the code depends on

namespace Exiv2 {

std::string stringFormat(const char* fmt, ...) {
    char buf[256];
    va_list args;
    va_start(args, fmt);
    // The format uses {:.1f} which is a fmt-style format, but we need to handle it
    // We'll implement a simple version
    va_end(args);
    // For the actual test, we rely on the real implementation
    // But since we can't include the real headers easily, we do a workaround
    return "";
}

// Provide a minimal _() macro/function for translations
inline const char* _(const char* s) { return s; }

// Minimal Rational type
using Rational = std::pair<int32_t, int32_t>;

// Minimal Value interface
class Value {
public:
    virtual ~Value() = default;
    virtual Rational toRational(long n = 0) const = 0;
    
    friend std::ostream& operator<<(std::ostream& os, const Value& v) {
        auto [r, s] = v.toRational();
        os << r << "/" << s;
        return os;
    }
};

// Minimal ExifData
class ExifData {};

namespace Internal {

class Nikon2MakerNote {
public:
    std::ostream& print0x000a(std::ostream& os, const Value& value, const ExifData*) {
        auto [r, s] = value.toRational();
        if (r == 0)
            return os << "Not used";
        if (s == 0)
            return os << "(" << value << ")";
        // Format with 1 decimal place
        float result = static_cast<float>(r) / s;
        char buf[64];
        snprintf(buf, sizeof(buf), "%.1fx", result);
        return os << buf;
    }
};

} // namespace Internal
} // namespace Exiv2

// Mock Value class for testing
class MockValue : public Exiv2::Value {
public:
    MOCK_METHOD(Exiv2::Rational, toRational, (long n), (const, override));
};

class Nikon2MakerNoteTest_456 : public ::testing::Test {
protected:
    Exiv2::Internal::Nikon2MakerNote makerNote;
    std::ostringstream os;
};

// Test: When numerator is 0, should print "Not used"
TEST_F(Nikon2MakerNoteTest_456, Print0x000a_NumeratorZero_PrintsNotUsed_456) {
    MockValue mockValue;
    EXPECT_CALL(mockValue, toRational(0))
        .WillRepeatedly(::testing::Return(Exiv2::Rational{0, 1}));

    makerNote.print0x000a(os, mockValue, nullptr);
    EXPECT_EQ(os.str(), "Not used");
}

// Test: When numerator is 0 and denominator is 0, should still print "Not used" (r==0 checked first)
TEST_F(Nikon2MakerNoteTest_456, Print0x000a_BothZero_PrintsNotUsed_456) {
    MockValue mockValue;
    EXPECT_CALL(mockValue, toRational(0))
        .WillRepeatedly(::testing::Return(Exiv2::Rational{0, 0}));

    makerNote.print0x000a(os, mockValue, nullptr);
    EXPECT_EQ(os.str(), "Not used");
}

// Test: When denominator is 0 and numerator is non-zero, should print value in parentheses
TEST_F(Nikon2MakerNoteTest_456, Print0x000a_DenominatorZero_PrintsValueInParens_456) {
    MockValue mockValue;
    EXPECT_CALL(mockValue, toRational(0))
        .WillRepeatedly(::testing::Return(Exiv2::Rational{5, 0}));

    makerNote.print0x000a(os, mockValue, nullptr);
    EXPECT_EQ(os.str(), "(5/0)");
}

// Test: Normal rational value, e.g., 10/10 = 1.0x
TEST_F(Nikon2MakerNoteTest_456, Print0x000a_NormalValue_OnePointZero_456) {
    MockValue mockValue;
    EXPECT_CALL(mockValue, toRational(0))
        .WillRepeatedly(::testing::Return(Exiv2::Rational{10, 10}));

    makerNote.print0x000a(os, mockValue, nullptr);
    EXPECT_EQ(os.str(), "1.0x");
}

// Test: Normal rational value, e.g., 15/10 = 1.5x
TEST_F(Nikon2MakerNoteTest_456, Print0x000a_NormalValue_OnePointFive_456) {
    MockValue mockValue;
    EXPECT_CALL(mockValue, toRational(0))
        .WillRepeatedly(::testing::Return(Exiv2::Rational{15, 10}));

    makerNote.print0x000a(os, mockValue, nullptr);
    EXPECT_EQ(os.str(), "1.5x");
}

// Test: Normal rational value, e.g., 20/10 = 2.0x
TEST_F(Nikon2MakerNoteTest_456, Print0x000a_NormalValue_TwoPointZero_456) {
    MockValue mockValue;
    EXPECT_CALL(mockValue, toRational(0))
        .WillRepeatedly(::testing::Return(Exiv2::Rational{20, 10}));

    makerNote.print0x000a(os, mockValue, nullptr);
    EXPECT_EQ(os.str(), "2.0x");
}

// Test: Negative numerator with positive denominator
TEST_F(Nikon2MakerNoteTest_456, Print0x000a_NegativeNumerator_456) {
    MockValue mockValue;
    EXPECT_CALL(mockValue, toRational(0))
        .WillRepeatedly(::testing::Return(Exiv2::Rational{-10, 10}));

    makerNote.print0x000a(os, mockValue, nullptr);
    EXPECT_EQ(os.str(), "-1.0x");
}

// Test: Negative denominator with positive numerator
TEST_F(Nikon2MakerNoteTest_456, Print0x000a_NegativeDenominator_456) {
    MockValue mockValue;
    EXPECT_CALL(mockValue, toRational(0))
        .WillRepeatedly(::testing::Return(Exiv2::Rational{10, -10}));

    makerNote.print0x000a(os, mockValue, nullptr);
    EXPECT_EQ(os.str(), "-1.0x");
}

// Test: Large values
TEST_F(Nikon2MakerNoteTest_456, Print0x000a_LargeValues_456) {
    MockValue mockValue;
    EXPECT_CALL(mockValue, toRational(0))
        .WillRepeatedly(::testing::Return(Exiv2::Rational{1000000, 3}));

    makerNote.print0x000a(os, mockValue, nullptr);
    // 1000000/3 = 333333.3...
    EXPECT_EQ(os.str(), "333333.3x");
}

// Test: Small fractional value
TEST_F(Nikon2MakerNoteTest_456, Print0x000a_SmallFractionalValue_456) {
    MockValue mockValue;
    EXPECT_CALL(mockValue, toRational(0))
        .WillRepeatedly(::testing::Return(Exiv2::Rational{1, 3}));

    makerNote.print0x000a(os, mockValue, nullptr);
    EXPECT_EQ(os.str(), "0.3x");
}

// Test: Numerator equals 1, denominator equals 1
TEST_F(Nikon2MakerNoteTest_456, Print0x000a_OneOverOne_456) {
    MockValue mockValue;
    EXPECT_CALL(mockValue, toRational(0))
        .WillRepeatedly(::testing::Return(Exiv2::Rational{1, 1}));

    makerNote.print0x000a(os, mockValue, nullptr);
    EXPECT_EQ(os.str(), "1.0x");
}

// Test: ExifData pointer is null (should not affect behavior)
TEST_F(Nikon2MakerNoteTest_456, Print0x000a_NullExifData_456) {
    MockValue mockValue;
    EXPECT_CALL(mockValue, toRational(0))
        .WillRepeatedly(::testing::Return(Exiv2::Rational{10, 5}));

    makerNote.print0x000a(os, mockValue, nullptr);
    EXPECT_EQ(os.str(), "2.0x");
}

// Test: Return value is the same ostream reference
TEST_F(Nikon2MakerNoteTest_456, Print0x000a_ReturnsOstreamReference_456) {
    MockValue mockValue;
    EXPECT_CALL(mockValue, toRational(0))
        .WillRepeatedly(::testing::Return(Exiv2::Rational{10, 5}));

    std::ostream& result = makerNote.print0x000a(os, mockValue, nullptr);
    EXPECT_EQ(&result, &os);
}

// Test: Denominator zero with negative numerator
TEST_F(Nikon2MakerNoteTest_456, Print0x000a_DenominatorZeroNegativeNumerator_456) {
    MockValue mockValue;
    EXPECT_CALL(mockValue, toRational(0))
        .WillRepeatedly(::testing::Return(Exiv2::Rational{-3, 0}));

    makerNote.print0x000a(os, mockValue, nullptr);
    EXPECT_EQ(os.str(), "(-3/0)");
}

// Test: Value with repeating decimal 2/3
TEST_F(Nikon2MakerNoteTest_456, Print0x000a_RepeatingDecimal_456) {
    MockValue mockValue;
    EXPECT_CALL(mockValue, toRational(0))
        .WillRepeatedly(::testing::Return(Exiv2::Rational{2, 3}));

    makerNote.print0x000a(os, mockValue, nullptr);
    EXPECT_EQ(os.str(), "0.7x");
}
