// =================================================================================================
//  TEST_ID: 945
//  File:    test_canonmn_int_print0x000c_945.cpp
//  Purpose: Unit tests for Exiv2::Internal::CanonMakerNote::print0x000c (black-box)
// =================================================================================================

#include <gtest/gtest.h>

#include <exiv2/exif.hpp>
#include <exiv2/tags.hpp>
#include <exiv2/types.hpp>
#include <exiv2/value.hpp>

#include <cstdint>
#include <memory>
#include <ostream>
#include <sstream>
#include <string>

#include "canonmn_int.hpp"

namespace {

using Exiv2::ExifData;
using Exiv2::ExifKey;
using Exiv2::Internal::CanonMakerNote;
using Exiv2::Value;

class CanonMakerNotePrint0x000cTest_945 : public ::testing::Test {
protected:
  static std::unique_ptr<Value> MakeAsciiValue(const std::string& s) {
    auto v = Value::create(Exiv2::asciiString);
    EXPECT_NE(v.get(), nullptr);
    v->read(s);
    return v;
  }

  static std::string CallPrint0x000c(const Value& v, const ExifData* exif) {
    std::ostringstream os;
    CanonMakerNote::print0x000c(os, v, exif);
    return os.str();
  }

  static void SetModelId(ExifData& exif, uint32_t modelId) {
    exif["Exif.Canon.ModelID"] = modelId;
  }
};

// Normal operation: null metadata -> should stream the Value as-is.
TEST_F(CanonMakerNotePrint0x000cTest_945, NullExifDataOutputsValue_945) {
  auto v = MakeAsciiValue("123456");
  const std::string out = CallPrint0x000c(*v, nullptr);
  EXPECT_EQ(out, v->toString());
}

// Normal operation: metadata present but ModelID key missing -> should stream Value as-is.
TEST_F(CanonMakerNotePrint0x000cTest_945, MissingModelIdOutputsValue_945) {
  ExifData exif;  // empty
  auto v = MakeAsciiValue("123456");

  const std::string out = CallPrint0x000c(*v, &exif);
  EXPECT_EQ(out, v->toString());
}

// Normal operation: ModelID present but not the special value -> should stream Value as-is.
TEST_F(CanonMakerNotePrint0x000cTest_945, NonMatchingModelIdOutputsValue_945) {
  ExifData exif;
  SetModelId(exif, 0xDEADBEEF);  // non-matching
  auto v = MakeAsciiValue("123456");

  const std::string out = CallPrint0x000c(*v, &exif);
  EXPECT_EQ(out, v->toString());
}

// Normal operation: ModelID matches special value and value is numeric -> formatted output.
TEST_F(CanonMakerNotePrint0x000cTest_945, MatchingModelIdFormatsNumericValue_945) {
  ExifData exif;
  SetModelId(exif, 0x01140000);  // triggers special formatting
  auto v = MakeAsciiValue("123456");  // decimal 123456 == 0x0001E240

  // Expected: "{:04x}{:05}" with (l>>16)&0xFFFF and (l&0xFFFF)
  // high16 = 0x0001 -> "0001"
  // low16  = 57920  -> "57920"
  const std::string out = CallPrint0x000c(*v, &exif);
  EXPECT_EQ(out, "000157920");
}

// Boundary condition: low-part needs zero padding to 5 digits.
TEST_F(CanonMakerNotePrint0x000cTest_945, MatchingModelIdPadsLowPartToFiveDigits_945) {
  ExifData exif;
  SetModelId(exif, 0x01140000);
  auto v = MakeAsciiValue("1");  // 0x00000001 -> high16 "0000", low16 "00001"

  const std::string out = CallPrint0x000c(*v, &exif);
  EXPECT_EQ(out, "000000001");
}

// Boundary condition: low-part exactly 65535 (max 16-bit) still prints 5 digits without padding changes.
TEST_F(CanonMakerNotePrint0x000cTest_945, MatchingModelIdLowPartAtMax16Bit_945) {
  ExifData exif;
  SetModelId(exif, 0x01140000);
  auto v = MakeAsciiValue("65535");  // 0x0000FFFF -> high16 "0000", low16 "65535"

  const std::string out = CallPrint0x000c(*v, &exif);
  EXPECT_EQ(out, "000065535");
}

// Exceptional case: when formatting path is taken, non-numeric value can cause std::stoul to throw.
TEST_F(CanonMakerNotePrint0x000cTest_945, MatchingModelIdNonNumericValueThrows_945) {
  ExifData exif;
  SetModelId(exif, 0x01140000);
  auto v = MakeAsciiValue("not_a_number");

  std::ostringstream os;
  EXPECT_THROW({ CanonMakerNote::print0x000c(os, *v, &exif); }, std::exception);
}

}  // namespace