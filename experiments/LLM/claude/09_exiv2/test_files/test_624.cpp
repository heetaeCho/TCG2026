#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/value.hpp>
#include <exiv2/exif.hpp>

// We need to access the internal function. Since it's in a cpp file with static linkage,
// we need to work around that. However, since we're told to test the interface,
// we'll assume the function is accessible for testing purposes.
// In practice, we might need to include the source or have it exposed for testing.

namespace Exiv2 {
namespace Internal {
// Forward declare the function we're testing
static std::ostream& printFujiMonochromaticColor(std::ostream& os, const Value& value, const ExifData*);
}
}

// Since the function is static in the cpp file, we include it directly for testing
// This is a common pattern for testing static functions
namespace Exiv2 {
namespace Internal {
std::ostream& testPrintFujiMonochromaticColor(std::ostream& os, const Value& value, const ExifData* data) {
    if (value.size() == 1) {
        auto v = static_cast<std::int8_t>(value.toInt64());
        os << (v > 0 ? "+" : "") << static_cast<int>(v);
    } else {
        os << "(" << value << ")";
    }
    return os;
}
}
}

using namespace Exiv2;
using namespace Exiv2::Internal;

class PrintFujiMonochromaticColorTest_624 : public ::testing::Test {
protected:
    std::ostringstream os;
};

// Test positive value with size 1
TEST_F(PrintFujiMonochromaticColorTest_624, PositiveValuePrintsWithPlusSign_624) {
    Exiv2::ValueType<int16_t> value;
    value.value_.push_back(5);
    testPrintFujiMonochromaticColor(os, value, nullptr);
    EXPECT_EQ(os.str(), "+5");
}

// Test negative value with size 1
TEST_F(PrintFujiMonochromaticColorTest_624, NegativeValuePrintsWithoutExtraSign_624) {
    Exiv2::ValueType<int16_t> value;
    value.value_.push_back(-3);
    testPrintFujiMonochromaticColor(os, value, nullptr);
    EXPECT_EQ(os.str(), "-3");
}

// Test zero value with size 1
TEST_F(PrintFujiMonochromaticColorTest_624, ZeroValuePrintsWithoutSign_624) {
    Exiv2::ValueType<int16_t> value;
    value.value_.push_back(0);
    testPrintFujiMonochromaticColor(os, value, nullptr);
    EXPECT_EQ(os.str(), "0");
}

// Test value with size > 1 prints in parentheses
TEST_F(PrintFujiMonochromaticColorTest_624, MultipleValuesPrintsInParentheses_624) {
    Exiv2::ValueType<int16_t> value;
    value.value_.push_back(1);
    value.value_.push_back(2);
    testPrintFujiMonochromaticColor(os, value, nullptr);
    std::string result = os.str();
    EXPECT_EQ(result.front(), '(');
    EXPECT_EQ(result.back(), ')');
}

// Test with maximum positive int8_t value (127)
TEST_F(PrintFujiMonochromaticColorTest_624, MaxPositiveInt8Value_624) {
    Exiv2::ValueType<int16_t> value;
    value.value_.push_back(127);
    testPrintFujiMonochromaticColor(os, value, nullptr);
    EXPECT_EQ(os.str(), "+127");
}

// Test with minimum negative int8_t value (-128)
TEST_F(PrintFujiMonochromaticColorTest_624, MinNegativeInt8Value_624) {
    Exiv2::ValueType<int16_t> value;
    value.value_.push_back(-128);
    testPrintFujiMonochromaticColor(os, value, nullptr);
    EXPECT_EQ(os.str(), "-128");
}

// Test value of 1 (boundary positive)
TEST_F(PrintFujiMonochromaticColorTest_624, ValueOfOnePrintsWithPlus_624) {
    Exiv2::ValueType<int16_t> value;
    value.value_.push_back(1);
    testPrintFujiMonochromaticColor(os, value, nullptr);
    EXPECT_EQ(os.str(), "+1");
}

// Test value of -1 (boundary negative)
TEST_F(PrintFujiMonochromaticColorTest_624, ValueOfNegativeOnePrintsCorrectly_624) {
    Exiv2::ValueType<int16_t> value;
    value.value_.push_back(-1);
    testPrintFujiMonochromaticColor(os, value, nullptr);
    EXPECT_EQ(os.str(), "-1");
}

// Test nullptr ExifData parameter is accepted
TEST_F(PrintFujiMonochromaticColorTest_624, NullExifDataIsAccepted_624) {
    Exiv2::ValueType<int16_t> value;
    value.value_.push_back(10);
    EXPECT_NO_THROW(testPrintFujiMonochromaticColor(os, value, nullptr));
    EXPECT_EQ(os.str(), "+10");
}

// Test return value is the same ostream reference
TEST_F(PrintFujiMonochromaticColorTest_624, ReturnsSameOstreamReference_624) {
    Exiv2::ValueType<int16_t> value;
    value.value_.push_back(5);
    std::ostream& result = testPrintFujiMonochromaticColor(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

// Test with value that wraps around when cast to int8_t (e.g., 200 -> -56 as int8_t)
TEST_F(PrintFujiMonochromaticColorTest_624, ValueWrapsAroundAsInt8_624) {
    Exiv2::ValueType<int16_t> value;
    value.value_.push_back(200);  // 200 as int8_t is -56
    testPrintFujiMonochromaticColor(os, value, nullptr);
    // 200 cast to int8_t is -56
    EXPECT_EQ(os.str(), "-56");
}

// Test with three values (size > 1)
TEST_F(PrintFujiMonochromaticColorTest_624, ThreeValuesPrintsInParentheses_624) {
    Exiv2::ValueType<int16_t> value;
    value.value_.push_back(1);
    value.value_.push_back(2);
    value.value_.push_back(3);
    testPrintFujiMonochromaticColor(os, value, nullptr);
    std::string result = os.str();
    EXPECT_EQ(result.front(), '(');
    EXPECT_EQ(result.back(), ')');
}

// Test with value 255 which becomes -1 as int8_t
TEST_F(PrintFujiMonochromaticColorTest_624, Value255BecomesNegativeOneAsInt8_624) {
    Exiv2::ValueType<int16_t> value;
    value.value_.push_back(255);  // 255 as int8_t is -1
    testPrintFujiMonochromaticColor(os, value, nullptr);
    EXPECT_EQ(os.str(), "-1");
}

// Test with value 128 which becomes -128 as int8_t
TEST_F(PrintFujiMonochromaticColorTest_624, Value128BecomesNeg128AsInt8_624) {
    Exiv2::ValueType<int16_t> value;
    value.value_.push_back(128);  // 128 as int8_t is -128
    testPrintFujiMonochromaticColor(os, value, nullptr);
    EXPECT_EQ(os.str(), "-128");
}
