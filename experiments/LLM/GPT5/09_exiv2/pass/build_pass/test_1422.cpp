// File: test_tags_int_printExifVersion_1422.cpp

#include <gtest/gtest.h>

#include <exiv2/exif.hpp>
#include <exiv2/types.hpp>
#include <exiv2/value.hpp>

// Under test (internal)
#include "tags_int.hpp"

#include <cstdint>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

namespace {

using Exiv2::ByteOrder;
using Exiv2::ExifData;
using Exiv2::TypeId;
using Exiv2::Value;

class PrintExifVersionTest_1422 : public ::testing::Test {
 protected:
  static std::string StreamValue(const Value& v) {
    std::ostringstream oss;
    oss << v;
    return oss.str();
  }

  static Value::UniquePtr MakeValue(TypeId type) {
    // Exiv2::Value::create is part of the public API.
    return Value::create(type);
  }

  static void ReadBytes(Value& v, const std::vector<Exiv2::byte>& bytes) {
    // For undefined/raw byte-like values, byte order should be irrelevant;
    // use invalidByteOrder to avoid assuming endianness.
    v.read(bytes.data(), static_cast<long>(bytes.size()), Exiv2::invalidByteOrder);
  }
};

TEST_F(PrintExifVersionTest_1422, NonUndefinedType_WrapsValueInParentheses_1422) {
  auto v = MakeValue(Exiv2::asciiString);
  ASSERT_NE(v.get(), nullptr);

  // Any readable value content is fine; we only compare against operator<< output.
  v->read("hello");

  const std::string valueStr = StreamValue(*v);

  std::ostringstream oss;
  std::ostream& ret = Exiv2::Internal::printExifVersion(oss, *v, nullptr);

  EXPECT_EQ(&ret, &oss);
  EXPECT_EQ(oss.str(), "(" + valueStr + ")");
}

TEST_F(PrintExifVersionTest_1422, UndefinedButSizeNotFour_WrapsValueInParentheses_1422) {
  auto v = MakeValue(Exiv2::undefined);
  ASSERT_NE(v.get(), nullptr);

  ReadBytes(*v, std::vector<Exiv2::byte>{0x01, 0x02, 0x03});  // size != 4
  const std::string valueStr = StreamValue(*v);

  std::ostringstream oss;
  std::ostream& ret = Exiv2::Internal::printExifVersion(oss, *v, nullptr);

  EXPECT_EQ(&ret, &oss);
  EXPECT_EQ(oss.str(), "(" + valueStr + ")");
}

TEST_F(PrintExifVersionTest_1422, UndefinedSizeFour_DoesNotUseParenthesizedFallback_1422) {
  auto v = MakeValue(Exiv2::undefined);
  ASSERT_NE(v.get(), nullptr);

  // Common ExifVersion is "0230" (stored as 4 bytes). We do NOT assert exact formatting
  // of printVersion; we only verify that the fallback "(<value>)" is not used.
  ReadBytes(*v, std::vector<Exiv2::byte>{'0', '2', '3', '0'});

  const std::string fallback = "(" + StreamValue(*v) + ")";

  std::ostringstream oss;
  std::ostream& ret = Exiv2::Internal::printExifVersion(oss, *v, nullptr);

  EXPECT_EQ(&ret, &oss);
  EXPECT_NE(oss.str(), fallback);
  EXPECT_FALSE(oss.str().empty());
}

TEST_F(PrintExifVersionTest_1422, ExifDataPointerDoesNotAffectOutput_1422) {
  auto v = MakeValue(Exiv2::undefined);
  ASSERT_NE(v.get(), nullptr);

  ReadBytes(*v, std::vector<Exiv2::byte>{'0', '2', '3', '0'});

  ExifData exif;

  std::ostringstream ossNull;
  Exiv2::Internal::printExifVersion(ossNull, *v, nullptr);

  std::ostringstream ossNonNull;
  Exiv2::Internal::printExifVersion(ossNonNull, *v, &exif);

  EXPECT_EQ(ossNonNull.str(), ossNull.str());
}

TEST_F(PrintExifVersionTest_1422, Boundary_ExactlyFourNonPrintableBytes_StillNotFallbackAndReturnsStream_1422) {
  auto v = MakeValue(Exiv2::undefined);
  ASSERT_NE(v.get(), nullptr);

  // Exercise boundary with bytes that may not be printable when interpreted as chars.
  ReadBytes(*v, std::vector<Exiv2::byte>{0x00, 0x7F, 0x80, 0xFF});

  const std::string fallback = "(" + StreamValue(*v) + ")";

  std::ostringstream oss;
  std::ostream& ret = Exiv2::Internal::printExifVersion(oss, *v, nullptr);

  EXPECT_EQ(&ret, &oss);
  EXPECT_NE(oss.str(), fallback);
  EXPECT_FALSE(oss.str().empty());
}

}  // namespace