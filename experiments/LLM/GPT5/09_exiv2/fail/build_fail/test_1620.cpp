// File: test_sonymn_int_printSonyMisc3cSequenceNumber_1620.cpp

#include <gtest/gtest.h>

#include <exiv2/exif.hpp>
#include <exiv2/value.hpp>

#include <cstdint>
#include <limits>
#include <sstream>
#include <string>

namespace {

// Minimal forward declaration (avoid relying on any internal state).
// The real class is provided by the production codebase.
namespace Exiv2 {
namespace Internal {
class SonyMakerNote {
public:
  std::ostream& printSonyMisc3cSequenceNumber(std::ostream& os, const Exiv2::Value& value, const Exiv2::ExifData*);
};
}  // namespace Internal
}  // namespace Exiv2

static std::string CallPrint(const Exiv2::Value& v, const Exiv2::ExifData* ed = nullptr) {
  Exiv2::Internal::SonyMakerNote mn;
  std::ostringstream oss;
  mn.printSonyMisc3cSequenceNumber(oss, v, ed);
  return oss.str();
}

static std::string ParenthesizedValue(const Exiv2::Value& v) {
  std::ostringstream oss;
  oss << "(" << v << ")";
  return oss.str();
}

}  // namespace

TEST(SonyMakerNoteTest_1620, PrintsParenthesizedValueWhenTypeIsNotUnsignedLong_1620) {
  auto v = Exiv2::Value::create(Exiv2::asciiString);
  ASSERT_TRUE(v.get() != nullptr);
  ASSERT_EQ(0, v->read("abc"));  // one element, but not unsignedLong type

  const std::string out = CallPrint(*v);
  EXPECT_EQ(ParenthesizedValue(*v), out);
}

TEST(SonyMakerNoteTest_1620, PrintsParenthesizedValueWhenCountIsNotOneEvenIfUnsignedLong_1620) {
  auto v = Exiv2::Value::create(Exiv2::unsignedLong);
  ASSERT_TRUE(v.get() != nullptr);
  ASSERT_EQ(0, v->read("1 2"));  // count == 2

  const std::string out = CallPrint(*v);
  EXPECT_EQ(ParenthesizedValue(*v), out);
}

TEST(SonyMakerNoteTest_1620, PrintsIncrementedNumberWhenUnsignedLongAndCountIsOne_1620) {
  auto v = Exiv2::Value::create(Exiv2::unsignedLong);
  ASSERT_TRUE(v.get() != nullptr);
  ASSERT_EQ(0, v->read("0"));

  const std::string out = CallPrint(*v);
  EXPECT_EQ("1", out);
}

TEST(SonyMakerNoteTest_1620, AcceptsNullExifDataPointer_1620) {
  auto v = Exiv2::Value::create(Exiv2::unsignedLong);
  ASSERT_TRUE(v.get() != nullptr);
  ASSERT_EQ(0, v->read("41"));

  const std::string out = CallPrint(*v, nullptr);
  EXPECT_EQ("42", out);
}

TEST(SonyMakerNoteTest_1620, HandlesLargeUnsignedLongValues_1620) {
  // Use a value at the typical uint32 max boundary; output should still be representable in int64.
  const std::uint64_t maxU32 = 0xFFFFFFFFULL;

  auto v = Exiv2::Value::create(Exiv2::unsignedLong);
  ASSERT_TRUE(v.get() != nullptr);

  {
    std::ostringstream in;
    in << maxU32;
    ASSERT_EQ(0, v->read(in.str()));
  }

  const std::string out = CallPrint(*v);
  EXPECT_EQ("4294967296", out);  // 0xFFFFFFFF + 1
}