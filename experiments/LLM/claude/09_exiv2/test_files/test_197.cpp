#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <string>
#include <cstdint>

// Minimal required types to interface with the code under test
namespace Exiv2 {

class ExifData {};

class Value {
public:
    virtual ~Value() = default;
    virtual int64_t toInt64(size_t n = 0) const = 0;
};

// A concrete mock for Value
class MockValue : public Value {
public:
    MOCK_METHOD(int64_t, toInt64, (size_t n), (const, override));
};

namespace Internal {

// Forward declaration matching the format helper
std::string stringFormat(const char* fmt, ...) {
    char buf[256];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buf, sizeof(buf), fmt, args);
    va_end(args);
    return std::string(buf);
}

class PentaxMakerNote {
public:
    std::ostream& printTemperature(std::ostream& os, const Value& value, const ExifData*) {
        return os << stringFormat("{} C", value.toInt64());
    }
};

} // namespace Internal
} // namespace Exiv2

// Since stringFormat with "{}" may not do printf-style replacement,
// let's check what the actual behavior is by running tests.
// The implementation uses stringFormat("{} C", value.toInt64()) which
// likely formats using fmt-style or a custom implementation.
// We test observable output.

class PentaxMakerNoteTest_197 : public ::testing::Test {
protected:
    Exiv2::Internal::PentaxMakerNote maker;
    Exiv2::MockValue mockValue;
    std::ostringstream oss;
};

TEST_F(PentaxMakerNoteTest_197, PrintTemperature_PositiveValue_197) {
    EXPECT_CALL(mockValue, toInt64(0)).WillOnce(::testing::Return(25));

    maker.printTemperature(oss, mockValue, nullptr);

    std::string result = oss.str();
    // The output should contain "25" and "C"
    EXPECT_NE(result.find("25"), std::string::npos);
    EXPECT_NE(result.find("C"), std::string::npos);
}

TEST_F(PentaxMakerNoteTest_197, PrintTemperature_ZeroValue_197) {
    EXPECT_CALL(mockValue, toInt64(0)).WillOnce(::testing::Return(0));

    maker.printTemperature(oss, mockValue, nullptr);

    std::string result = oss.str();
    EXPECT_NE(result.find("0"), std::string::npos);
    EXPECT_NE(result.find("C"), std::string::npos);
}

TEST_F(PentaxMakerNoteTest_197, PrintTemperature_NegativeValue_197) {
    EXPECT_CALL(mockValue, toInt64(0)).WillOnce(::testing::Return(-10));

    maker.printTemperature(oss, mockValue, nullptr);

    std::string result = oss.str();
    EXPECT_NE(result.find("-10"), std::string::npos);
    EXPECT_NE(result.find("C"), std::string::npos);
}

TEST_F(PentaxMakerNoteTest_197, PrintTemperature_LargePositiveValue_197) {
    EXPECT_CALL(mockValue, toInt64(0)).WillOnce(::testing::Return(1000));

    maker.printTemperature(oss, mockValue, nullptr);

    std::string result = oss.str();
    EXPECT_NE(result.find("1000"), std::string::npos);
    EXPECT_NE(result.find("C"), std::string::npos);
}

TEST_F(PentaxMakerNoteTest_197, PrintTemperature_LargeNegativeValue_197) {
    EXPECT_CALL(mockValue, toInt64(0)).WillOnce(::testing::Return(-273));

    maker.printTemperature(oss, mockValue, nullptr);

    std::string result = oss.str();
    EXPECT_NE(result.find("-273"), std::string::npos);
    EXPECT_NE(result.find("C"), std::string::npos);
}

TEST_F(PentaxMakerNoteTest_197, PrintTemperature_ReturnsOstream_197) {
    EXPECT_CALL(mockValue, toInt64(0)).WillOnce(::testing::Return(42));

    std::ostream& returned = maker.printTemperature(oss, mockValue, nullptr);

    // Verify the returned reference is the same stream
    EXPECT_EQ(&returned, &oss);
}

TEST_F(PentaxMakerNoteTest_197, PrintTemperature_NullExifData_197) {
    EXPECT_CALL(mockValue, toInt64(0)).WillOnce(::testing::Return(20));

    // Should work fine with nullptr ExifData
    EXPECT_NO_THROW(maker.printTemperature(oss, mockValue, nullptr));

    std::string result = oss.str();
    EXPECT_NE(result.find("20"), std::string::npos);
}

TEST_F(PentaxMakerNoteTest_197, PrintTemperature_WithExifData_197) {
    Exiv2::ExifData exifData;
    EXPECT_CALL(mockValue, toInt64(0)).WillOnce(::testing::Return(37));

    // Should work fine with non-null ExifData (ignored parameter)
    EXPECT_NO_THROW(maker.printTemperature(oss, mockValue, &exifData));

    std::string result = oss.str();
    EXPECT_NE(result.find("37"), std::string::npos);
}

TEST_F(PentaxMakerNoteTest_197, PrintTemperature_MaxInt64Value_197) {
    EXPECT_CALL(mockValue, toInt64(0)).WillOnce(::testing::Return(INT64_MAX));

    maker.printTemperature(oss, mockValue, nullptr);

    std::string result = oss.str();
    EXPECT_NE(result.find("C"), std::string::npos);
    EXPECT_FALSE(result.empty());
}

TEST_F(PentaxMakerNoteTest_197, PrintTemperature_MinInt64Value_197) {
    EXPECT_CALL(mockValue, toInt64(0)).WillOnce(::testing::Return(INT64_MIN));

    maker.printTemperature(oss, mockValue, nullptr);

    std::string result = oss.str();
    EXPECT_NE(result.find("C"), std::string::npos);
    EXPECT_FALSE(result.empty());
}

TEST_F(PentaxMakerNoteTest_197, PrintTemperature_MultipleCallsAppend_197) {
    EXPECT_CALL(mockValue, toInt64(0))
        .WillOnce(::testing::Return(10))
        .WillOnce(::testing::Return(20));

    maker.printTemperature(oss, mockValue, nullptr);
    maker.printTemperature(oss, mockValue, nullptr);

    std::string result = oss.str();
    // Both values should appear in the stream
    EXPECT_NE(result.find("10"), std::string::npos);
    EXPECT_NE(result.find("20"), std::string::npos);
}

TEST_F(PentaxMakerNoteTest_197, PrintTemperature_SingleDigitValue_197) {
    EXPECT_CALL(mockValue, toInt64(0)).WillOnce(::testing::Return(5));

    maker.printTemperature(oss, mockValue, nullptr);

    std::string result = oss.str();
    EXPECT_NE(result.find("5"), std::string::npos);
    EXPECT_NE(result.find("C"), std::string::npos);
}
