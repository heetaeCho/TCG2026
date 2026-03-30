// File: test_print0x0006_1385.cpp
// TEST_ID: 1385

#include <gtest/gtest.h>

#include <exiv2/value.hpp>
#include <sstream>
#include <iomanip>
#include <string>

namespace Exiv2 {
class ExifData;  // forward decl is enough for signature
namespace Internal {
std::ostream& print0x0006(std::ostream& os, const Value& value, const ExifData*);
}  // namespace Internal
}  // namespace Exiv2

namespace {

class Print0x0006Test_1385 : public ::testing::Test {
 protected:
  static std::unique_ptr<Exiv2::Value> MakeURationalValue(const std::string& text) {
    auto v = Exiv2::Value::create(Exiv2::unsignedRational);
    // Parsing behavior is provided by Exiv2; we treat it as a black box.
    v->read(text);
    return v;
  }

  static std::string StreamValueToString(const Exiv2::Value& v) {
    std::ostringstream oss;
    oss << v;
    return oss.str();
  }
};

TEST_F(Print0x0006Test_1385, DenominatorZero_OutputsValueInParentheses_NoMetersSuffix_1385) {
  auto v = MakeURationalValue("1/0");

  std::ostringstream os;
  Exiv2::Internal::print0x0006(os, *v, nullptr);

  const std::string value_str = StreamValueToString(*v);
  EXPECT_EQ(os.str(), "(" + value_str + ")");
  EXPECT_EQ(os.str().find(" m"), std::string::npos);
}

TEST_F(Print0x0006Test_1385, DenominatorGreaterThanOne_UsesOneDecimalAndMetersSuffix_1385) {
  auto v = MakeURationalValue("3/2");  // 1.5

  std::ostringstream os;
  Exiv2::Internal::print0x0006(os, *v, nullptr);

  // Observable formatting: fixed + 1 decimal + " m"
  EXPECT_EQ(os.str(), "1.5 m");
}

TEST_F(Print0x0006Test_1385, DenominatorOne_UsesZeroDecimalsAndMetersSuffix_1385) {
  auto v = MakeURationalValue("3/1");  // 3

  std::ostringstream os;
  Exiv2::Internal::print0x0006(os, *v, nullptr);

  // Observable formatting: fixed + 0 decimals + " m"
  EXPECT_EQ(os.str(), "3 m");
}

TEST_F(Print0x0006Test_1385, PreservesStreamFormattingState_AfterPrinting_1385) {
  auto v = MakeURationalValue("3/2");

  std::ostringstream os;

  // Set a non-default formatting state on the stream.
  os.setf(std::ios::scientific, std::ios::floatfield);
  os.setf(std::ios::showpos);
  os << std::setprecision(7);
  os.fill('*');

  const std::ios::fmtflags before_flags = os.flags();
  const std::streamsize before_precision = os.precision();
  const char before_fill = os.fill();

  Exiv2::Internal::print0x0006(os, *v, nullptr);

  // Verify the function restored formatting-related stream state.
  EXPECT_EQ(os.flags(), before_flags);
  EXPECT_EQ(os.precision(), before_precision);
  EXPECT_EQ(os.fill(), before_fill);
}

}  // namespace