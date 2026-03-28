// File: test_tags_int_printInt64_test_1377.cpp
// Unit tests for Exiv2::Internal::printInt64 (./TestProjects/exiv2/src/tags_int.cpp)

#include <gtest/gtest.h>

#include <exiv2/exif.hpp>
#include <exiv2/types.hpp>
#include <exiv2/value.hpp>

#include <cstdint>
#include <limits>
#include <sstream>
#include <string>

namespace {

// Minimal controllable Value test double for exercising printInt64’s fallback branch.
// (We only implement the parts required by the Exiv2::Value abstract interface.)
class FakeValueForPrintInt64 final : public Exiv2::Value {
 public:
  FakeValueForPrintInt64(Exiv2::Rational r, std::string printed)
      : r_(r), printed_(std::move(printed)) {}

  // Exiv2::Value interface
  Exiv2::Value* clone() const override { return new FakeValueForPrintInt64(*this); }

  Exiv2::TypeId typeId() const override { return Exiv2::invalidTypeId; }

  size_t count() const override { return 1; }

  size_t size() const override { return 0; }

  size_t sizeDataArea() const override { return 0; }

  int read(const Exiv2::byte*, size_t, Exiv2::ByteOrder) override { return 0; }

  int read(const std::string&) override { return 0; }

  size_t copy(Exiv2::byte*, Exiv2::ByteOrder) const override { return 0; }

  std::ostream& write(std::ostream& os) const override { return os << printed_; }

  Exiv2::Rational toRational(size_t /*n*/ = 0) const override { return r_; }

 private:
  Exiv2::Rational r_;
  std::string printed_;
};

}  // namespace

TEST(PrintInt64Test_1377, PositiveDenominatorPrintsQuotient_1377) {
  // Use a real Exiv2 Value for the normal path.
  Exiv2::Value::UniquePtr v = Exiv2::Value::create(Exiv2::signedRational);
  ASSERT_TRUE(v.get() != nullptr);

  // 10/2 -> 5
  ASSERT_EQ(0, v->read("10/2"));

  std::ostringstream os;
  std::ostream& ret = Exiv2::Internal::printInt64(os, *v, nullptr);

  EXPECT_EQ(&ret, &os);
  EXPECT_EQ("5", os.str());
}

TEST(PrintInt64Test_1377, DenominatorOnePrintsNumerator_1377) {
  Exiv2::Value::UniquePtr v = Exiv2::Value::create(Exiv2::signedRational);
  ASSERT_TRUE(v.get() != nullptr);

  // Boundary-ish: denom = 1
  ASSERT_EQ(0, v->read("123/1"));

  std::ostringstream os;
  Exiv2::Internal::printInt64(os, *v, nullptr);

  EXPECT_EQ("123", os.str());
}

TEST(PrintInt64Test_1377, NegativeNumeratorUsesIntegerDivision_1377) {
  Exiv2::Value::UniquePtr v = Exiv2::Value::create(Exiv2::signedRational);
  ASSERT_TRUE(v.get() != nullptr);

  // -3/2 -> -1 with C++ integer division (truncate toward zero)
  ASSERT_EQ(0, v->read("-3/2"));

  std::ostringstream os;
  Exiv2::Internal::printInt64(os, *v, nullptr);

  EXPECT_EQ("-1", os.str());
}

TEST(PrintInt64Test_1377, LargeNumeratorCastsToInt64BeforeDivision_1377) {
  Exiv2::Value::UniquePtr v = Exiv2::Value::create(Exiv2::signedRational);
  ASSERT_TRUE(v.get() != nullptr);

  // Use INT32_MAX/1, which should print the full value.
  const auto max32 = std::numeric_limits<int32_t>::max();
  ASSERT_EQ(0, v->read(std::to_string(max32) + "/1"));

  std::ostringstream os;
  Exiv2::Internal::printInt64(os, *v, nullptr);

  EXPECT_EQ(std::to_string(max32), os.str());
}

TEST(PrintInt64Test_1377, NonPositiveDenominatorFallsBackToParenthesizedValue_1377) {
  // Force the "fallback" branch deterministically without relying on parsing edge cases.
  FakeValueForPrintInt64 fake(/*r=*/Exiv2::Rational{42, 0}, /*printed=*/"FAKE_VALUE");

  std::ostringstream os;
  std::ostream& ret = Exiv2::Internal::printInt64(os, fake, nullptr);

  EXPECT_EQ(&ret, &os);
  EXPECT_EQ("(FAKE_VALUE)", os.str());
}

TEST(PrintInt64Test_1377, NegativeDenominatorAlsoFallsBackToParenthesizedValue_1377) {
  FakeValueForPrintInt64 fake(/*r=*/Exiv2::Rational{42, -7}, /*printed=*/"NEG_DEN");

  // Pass a non-null ExifData* as well (even though the function may ignore it),
  // just to ensure observable behavior is stable.
  Exiv2::ExifData exif;

  std::ostringstream os;
  Exiv2::Internal::printInt64(os, fake, &exif);

  EXPECT_EQ("(NEG_DEN)", os.str());
}