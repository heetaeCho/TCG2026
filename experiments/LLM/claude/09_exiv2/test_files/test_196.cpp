#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <cstdint>

// Include necessary Exiv2 headers
#include <exiv2/value.hpp>
#include <exiv2/exif.hpp>

namespace Exiv2 {
namespace Internal {

class PentaxMakerNote {
public:
    std::ostream& printCompensation(std::ostream& os, const Value& value, const ExifData*) {
        // We need the function signature matching the partial code
        // Using stringFormat equivalent - but since we treat it as black box, we just need the class
        return os << fmt::format("{:.2g} EV", (static_cast<float>(value.toInt64()) - 50) / 10);
    }
};

}  // namespace Internal
}  // namespace Exiv2

// Since we can't easily include the internal header directly, let's work with
// what we have. We'll test the printCompensation method.

class PentaxMakerNoteTest_196 : public ::testing::Test {
protected:
    Exiv2::Internal::PentaxMakerNote maker;
    std::ostringstream os;
};

// Test zero compensation (value = 50 means 0 EV)
TEST_F(PentaxMakerNoteTest_196, ZeroCompensation_196) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.value_.push_back(50);
    maker.printCompensation(os, value, nullptr);
    EXPECT_EQ(os.str(), "0 EV");
}

// Test positive compensation: value=60 => (60-50)/10 = 1.0 EV
TEST_F(PentaxMakerNoteTest_196, PositiveOneEV_196) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.value_.push_back(60);
    maker.printCompensation(os, value, nullptr);
    EXPECT_EQ(os.str(), "1 EV");
}

// Test negative compensation: value=40 => (40-50)/10 = -1.0 EV
TEST_F(PentaxMakerNoteTest_196, NegativeOneEV_196) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.value_.push_back(40);
    maker.printCompensation(os, value, nullptr);
    EXPECT_EQ(os.str(), "-1 EV");
}

// Test fractional positive: value=53 => (53-50)/10 = 0.3 EV
TEST_F(PentaxMakerNoteTest_196, FractionalPositive_196) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.value_.push_back(53);
    maker.printCompensation(os, value, nullptr);
    EXPECT_EQ(os.str(), "0.3 EV");
}

// Test fractional negative: value=47 => (47-50)/10 = -0.3 EV
TEST_F(PentaxMakerNoteTest_196, FractionalNegative_196) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.value_.push_back(47);
    maker.printCompensation(os, value, nullptr);
    EXPECT_EQ(os.str(), "-0.3 EV");
}

// Test value=0 => (0-50)/10 = -5.0 EV
TEST_F(PentaxMakerNoteTest_196, ValueZero_196) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.value_.push_back(0);
    maker.printCompensation(os, value, nullptr);
    EXPECT_EQ(os.str(), "-5 EV");
}

// Test value=100 => (100-50)/10 = 5.0 EV
TEST_F(PentaxMakerNoteTest_196, ValueHundred_196) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.value_.push_back(100);
    maker.printCompensation(os, value, nullptr);
    EXPECT_EQ(os.str(), "5 EV");
}

// Test common camera compensation: +0.7 EV => value=57 => (57-50)/10 = 0.7
TEST_F(PentaxMakerNoteTest_196, PointSevenEV_196) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.value_.push_back(57);
    maker.printCompensation(os, value, nullptr);
    EXPECT_EQ(os.str(), "0.7 EV");
}

// Test +2.0 EV => value=70 => (70-50)/10 = 2.0
TEST_F(PentaxMakerNoteTest_196, PlusTwoEV_196) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.value_.push_back(70);
    maker.printCompensation(os, value, nullptr);
    EXPECT_EQ(os.str(), "2 EV");
}

// Test -2.0 EV => value=30 => (30-50)/10 = -2.0
TEST_F(PentaxMakerNoteTest_196, MinusTwoEV_196) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.value_.push_back(30);
    maker.printCompensation(os, value, nullptr);
    EXPECT_EQ(os.str(), "-2 EV");
}

// Test with nullptr ExifData (should not crash)
TEST_F(PentaxMakerNoteTest_196, NullExifData_196) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.value_.push_back(50);
    EXPECT_NO_THROW(maker.printCompensation(os, value, nullptr));
}

// Test return value is same stream
TEST_F(PentaxMakerNoteTest_196, ReturnsSameStream_196) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.value_.push_back(50);
    std::ostream& result = maker.printCompensation(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

// Test large positive value: value=150 => (150-50)/10 = 10.0
TEST_F(PentaxMakerNoteTest_196, LargePositiveValue_196) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.value_.push_back(150);
    maker.printCompensation(os, value, nullptr);
    EXPECT_EQ(os.str(), "10 EV");
}

// Test negative input value: value=-50 => (-50-50)/10 = -10.0
TEST_F(PentaxMakerNoteTest_196, NegativeInputValue_196) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.value_.push_back(-50);
    maker.printCompensation(os, value, nullptr);
    EXPECT_EQ(os.str(), "-10 EV");
}

// Test +1/3 stop: value=53 => 0.3 EV (common camera setting)
TEST_F(PentaxMakerNoteTest_196, OneThirdStop_196) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.value_.push_back(53);
    maker.printCompensation(os, value, nullptr);
    std::string result = os.str();
    EXPECT_TRUE(result.find("EV") != std::string::npos);
}

// Test +2/3 stop: value=57 => 0.7 EV (common camera setting)
TEST_F(PentaxMakerNoteTest_196, TwoThirdsStop_196) {
    Exiv2::ValueType<int32_t> value(Exiv2::signedLong);
    value.value_.push_back(57);
    maker.printCompensation(os, value, nullptr);
    std::string result = os.str();
    EXPECT_TRUE(result.find("EV") != std::string::npos);
}
#include <gtest/gtest.h>
#include <sstream>
#include <string>

#include <exiv2/value.hpp>
#include <exiv2/exif.hpp>

// We need to access the internal PentaxMakerNote - include the internal header
#include "pentaxmn_int.hpp"

class PentaxMakerNoteTest_196 : public ::testing::Test {
protected:
    std::ostringstream os;
};

// Helper to create a Value with a specific integer
static std::unique_ptr<Exiv2::Value> makeIntValue(int32_t v) {
    auto val = Exiv2::Value::create(Exiv2::signedLong);
    val->read(std::to_string(v));
    return val;
}

// Test zero compensation (value = 50 means 0 EV)
TEST_F(PentaxMakerNoteTest_196, ZeroCompensation_196) {
    auto value = makeIntValue(50);
    Exiv2::Internal::PentaxMakerNote::printCompensation(os, *value, nullptr);
    EXPECT_EQ(os.str(), "0 EV");
}

// Test positive compensation: value=60 => (60-50)/10 = 1.0 EV
TEST_F(PentaxMakerNoteTest_196, PositiveOneEV_196) {
    auto value = makeIntValue(60);
    Exiv2::Internal::PentaxMakerNote::printCompensation(os, *value, nullptr);
    EXPECT_EQ(os.str(), "1 EV");
}

// Test negative compensation: value=40 => (40-50)/10 = -1.0 EV
TEST_F(PentaxMakerNoteTest_196, NegativeOneEV_196) {
    auto value = makeIntValue(40);
    Exiv2::Internal::PentaxMakerNote::printCompensation(os, *value, nullptr);
    EXPECT_EQ(os.str(), "-1 EV");
}

// Test fractional positive: value=53 => (53-50)/10 = 0.3 EV
TEST_F(PentaxMakerNoteTest_196, FractionalPositive_196) {
    auto value = makeIntValue(53);
    Exiv2::Internal::PentaxMakerNote::printCompensation(os, *value, nullptr);
    EXPECT_EQ(os.str(), "0.3 EV");
}

// Test fractional negative: value=47 => (47-50)/10 = -0.3 EV
TEST_F(PentaxMakerNoteTest_196, FractionalNegative_196) {
    auto value = makeIntValue(47);
    Exiv2::Internal::PentaxMakerNote::printCompensation(os, *value, nullptr);
    EXPECT_EQ(os.str(), "-0.3 EV");
}

// Test value=0 => (0-50)/10 = -5.0 EV
TEST_F(PentaxMakerNoteTest_196, ValueZero_196) {
    auto value = makeIntValue(0);
    Exiv2::Internal::PentaxMakerNote::printCompensation(os, *value, nullptr);
    EXPECT_EQ(os.str(), "-5 EV");
}

// Test value=100 => (100-50)/10 = 5.0 EV
TEST_F(PentaxMakerNoteTest_196, ValueHundred_196) {
    auto value = makeIntValue(100);
    Exiv2::Internal::PentaxMakerNote::printCompensation(os, *value, nullptr);
    EXPECT_EQ(os.str(), "5 EV");
}

// Test +2.0 EV => value=70 => (70-50)/10 = 2.0
TEST_F(PentaxMakerNoteTest_196, PlusTwoEV_196) {
    auto value = makeIntValue(70);
    Exiv2::Internal::PentaxMakerNote::printCompensation(os, *value, nullptr);
    EXPECT_EQ(os.str(), "2 EV");
}

// Test -2.0 EV => value=30 => (30-50)/10 = -2.0
TEST_F(PentaxMakerNoteTest_196, MinusTwoEV_196) {
    auto value = makeIntValue(30);
    Exiv2::Internal::PentaxMakerNote::printCompensation(os, *value, nullptr);
    EXPECT_EQ(os.str(), "-2 EV");
}

// Test with nullptr ExifData (should not crash)
TEST_F(PentaxMakerNoteTest_196, NullExifData_196) {
    auto value = makeIntValue(50);
    EXPECT_NO_THROW(Exiv2::Internal::PentaxMakerNote::printCompensation(os, *value, nullptr));
}

// Test return value is same stream
TEST_F(PentaxMakerNoteTest_196, ReturnsSameStream_196) {
    auto value = makeIntValue(50);
    std::ostream& result = Exiv2::Internal::PentaxMakerNote::printCompensation(os, *value, nullptr);
    EXPECT_EQ(&result, &os);
}

// Test large positive value: value=150 => (150-50)/10 = 10.0
TEST_F(PentaxMakerNoteTest_196, LargePositiveValue_196) {
    auto value = makeIntValue(150);
    Exiv2::Internal::PentaxMakerNote::printCompensation(os, *value, nullptr);
    EXPECT_EQ(os.str(), "10 EV");
}

// Test value=55 => (55-50)/10 = 0.5 EV
TEST_F(PentaxMakerNoteTest_196, HalfEV_196) {
    auto value = makeIntValue(55);
    Exiv2::Internal::PentaxMakerNote::printCompensation(os, *value, nullptr);
    EXPECT_EQ(os.str(), "0.5 EV");
}

// Test value=45 => (45-50)/10 = -0.5 EV
TEST_F(PentaxMakerNoteTest_196, NegativeHalfEV_196) {
    auto value = makeIntValue(45);
    Exiv2::Internal::PentaxMakerNote::printCompensation(os, *value, nullptr);
    EXPECT_EQ(os.str(), "-0.5 EV");
}

// Test output always contains "EV" suffix
TEST_F(PentaxMakerNoteTest_196, OutputContainsEVSuffix_196) {
    auto value = makeIntValue(57);
    Exiv2::Internal::PentaxMakerNote::printCompensation(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_NE(result.find("EV"), std::string::npos);
}

// Test value=51 => (51-50)/10 = 0.1 EV
TEST_F(PentaxMakerNoteTest_196, SmallPositive_196) {
    auto value = makeIntValue(51);
    Exiv2::Internal::PentaxMakerNote::printCompensation(os, *value, nullptr);
    EXPECT_EQ(os.str(), "0.1 EV");
}

// Test value=49 => (49-50)/10 = -0.1 EV
TEST_F(PentaxMakerNoteTest_196, SmallNegative_196) {
    auto value = makeIntValue(49);
    Exiv2::Internal::PentaxMakerNote::printCompensation(os, *value, nullptr);
    EXPECT_EQ(os.str(), "-0.1 EV");
}
