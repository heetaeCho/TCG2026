// =================================================================================================
// Test file for ./TestProjects/exiv2/src/tags_int.cpp (TEST_ID: 1378)
// =================================================================================================

#include <gtest/gtest.h>

#include <exiv2/exif.hpp>
#include <exiv2/value.hpp>

#include <memory>
#include <sstream>
#include <string>

namespace Exiv2 {
namespace Internal {
// Forward declaration (internal function implemented in tags_int.cpp)
std::ostream& printFloat(std::ostream& os, const Value& value, const ExifData*);
}  // namespace Internal
}  // namespace Exiv2

namespace {

class PrintFloatTest_1378 : public ::testing::Test {
 protected:
  static std::string CallPrintFloat(const Exiv2::Value& v, const Exiv2::ExifData* exif) {
    std::ostringstream os;
    Exiv2::Internal::printFloat(os, v, exif);
    return os.str();
  }

  static std::string StreamFloat(double f) {
    std::ostringstream os;
    os << f;
    return os.str();
  }

  static std::string ParenthesizedValue(const Exiv2::Value& v) {
    std::ostringstream os;
    os << "(" << v << ")";
    return os.str();
  }

  static std::unique_ptr<Exiv2::Value> MakeRationalValue(int32_t num, int32_t den) {
    auto v = Exiv2::Value::create(Exiv2::signedRational);
    // Use only the public interface. If this type doesn't accept the set operation in this build,
    // the test will fail at compile time (which is preferable to guessing internals).
    v->read(std::to_string(num) + "/" + std::to_string(den));
    return v;
  }

  static std::unique_ptr<Exiv2::Value> MakeFloatValue(double x) {
    auto v = Exiv2::Value::create(Exiv2::tiffFloat);
    v->read(std::to_string(x));
    return v;
  }
};

TEST_F(PrintFloatTest_1378, RationalDenomNonZero_PrintsToFloat_1378) {
  auto v = MakeRationalValue(1, 2);

  const std::string expected = StreamFloat(v->toFloat());
  const std::string actual = CallPrintFloat(*v, nullptr);

  EXPECT_EQ(actual, expected);
}

TEST_F(PrintFloatTest_1378, DenomZero_PrintsParenthesizedValue_1378) {
  // Use a non-rational typed value so that toRational() is expected to yield a denominator of 0,
  // exercising the "else" branch through observable output.
  auto v = MakeFloatValue(1.25);

  const std::string expected = ParenthesizedValue(*v);
  const std::string actual = CallPrintFloat(*v, nullptr);

  EXPECT_EQ(actual, expected);
}

TEST_F(PrintFloatTest_1378, ExifDataPointerDoesNotChangeOutput_1378) {
  auto v = MakeRationalValue(3, 4);

  Exiv2::ExifData exif;
  const std::string out_null = CallPrintFloat(*v, nullptr);
  const std::string out_nonnull = CallPrintFloat(*v, &exif);

  EXPECT_EQ(out_nonnull, out_null);
}

TEST_F(PrintFloatTest_1378, Boundary_ZeroRational_PrintsToFloat_1378) {
  auto v = MakeRationalValue(0, 1);

  const std::string expected = StreamFloat(v->toFloat());
  const std::string actual = CallPrintFloat(*v, nullptr);

  EXPECT_EQ(actual, expected);
}

TEST_F(PrintFloatTest_1378, Boundary_NegativeRational_PrintsToFloat_1378) {
  auto v = MakeRationalValue(-3, 2);

  const std::string expected = StreamFloat(v->toFloat());
  const std::string actual = CallPrintFloat(*v, nullptr);

  EXPECT_EQ(actual, expected);
}

TEST_F(PrintFloatTest_1378, EmptyValue_DoesNotThrow_AndMatchesObservedFormatting_1378) {
  // Create a rational Value but do not populate it. We do not assume how it behaves internally;
  // we only assert that printFloat is callable and that its output matches the interface-derived
  // expectation for the denom==0 branch (parenthesized streaming of the value) when that occurs.
  auto v = Exiv2::Value::create(Exiv2::signedRational);

  std::string actual;
  EXPECT_NO_THROW(actual = CallPrintFloat(*v, nullptr));

  // Expected output is based on the observable formatting rule: "(" << value << ")" when denom==0.
  // If this empty value is treated as denom!=0 in some implementation, this assertion will fail,
  // surfacing a real behavior difference.
  const std::string expected = ParenthesizedValue(*v);
  EXPECT_EQ(actual, expected);
}

}  // namespace