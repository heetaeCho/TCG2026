// SPDX-License-Identifier: GPL-2.0-or-later
// TEST_ID 706
//
// Unit tests for Exiv2::Internal::PanasonicMakerNote (panasonicmn_int.hpp)
//
// Constraints honored:
// - Treat implementation as black box
// - Only use public interface / observable behavior
// - No private state access
// - No internal logic re-implementation

#include <gtest/gtest.h>

#include <exiv2/exif.hpp>
#include <exiv2/value.hpp>

#include <sstream>
#include <type_traits>

#include "panasonicmn_int.hpp"

namespace {

using Exiv2::ExifData;
using Exiv2::Value;

using Exiv2::Internal::PanasonicMakerNote;

using PrintFn = std::ostream& (*)(std::ostream&, const Value&, const ExifData*);

template <typename T>
Value::UniquePtr MakeValueFromString(const std::string& txt) {
  Value::UniquePtr v = Value::create(T{});
  // If parsing fails for any reason, the value object remains valid; tests only
  // require that calls are safe and return the stream reference.
  v->read(txt);
  return v;
}

void ExpectPrintFnReturnsSameStream(PrintFn fn, const Value& value) {
  std::ostringstream os;
  std::ostream& ret = fn(os, value, nullptr);
  EXPECT_EQ(&ret, &os);
  EXPECT_TRUE(os.good());
}

}  // namespace

// Compile-time interface checks (do not assert implementation details).
namespace {
using TagListRawRet = decltype(PanasonicMakerNote::tagListRaw());
static_assert(std::is_pointer_v<TagListRawRet> || std::is_array_v<std::remove_reference_t<TagListRawRet>> ||
                  std::is_reference_v<TagListRawRet>,
              "tagListRaw() should return a pointer/array/reference-like tag list handle");
}  // namespace

class PanasonicMakerNoteTest_706 : public ::testing::Test {};

TEST_F(PanasonicMakerNoteTest_706, TagListRawIsCallable_706) {
  // Only checks that it can be called and yields a usable handle.
  auto list = PanasonicMakerNote::tagListRaw();
  (void)list;
  SUCCEED();
}

TEST_F(PanasonicMakerNoteTest_706, TagListRawIsStableAcrossCalls_706) {
  // Observable behavior: repeated calls should yield the same list handle
  // for a static tag table (common pattern). We only check identity.
  auto a = PanasonicMakerNote::tagListRaw();
  auto b = PanasonicMakerNote::tagListRaw();
  EXPECT_EQ(a, b);
}

TEST_F(PanasonicMakerNoteTest_706, TagListRawPointerIsNonNullWhenPointer_706) {
  // If it is a pointer type, it should not be null.
  // If it is not a pointer type, this test still compiles and trivially passes.
  if constexpr (std::is_pointer_v<decltype(PanasonicMakerNote::tagListRaw())>) {
    EXPECT_NE(PanasonicMakerNote::tagListRaw(), nullptr);
  } else {
    SUCCEED();
  }
}

TEST_F(PanasonicMakerNoteTest_706, Print0x000fReturnsStreamReference_706) {
  auto v = MakeValueFromString<Exiv2::unsignedShort>("0");
  ExpectPrintFnReturnsSameStream(&PanasonicMakerNote::print0x000f, *v);
}

TEST_F(PanasonicMakerNoteTest_706, Print0x0023ReturnsStreamReference_706) {
  auto v = MakeValueFromString<Exiv2::unsignedShort>("0");
  ExpectPrintFnReturnsSameStream(&PanasonicMakerNote::print0x0023, *v);
}

TEST_F(PanasonicMakerNoteTest_706, Print0x0029ReturnsStreamReference_706) {
  auto v = MakeValueFromString<Exiv2::unsignedShort>("0");
  ExpectPrintFnReturnsSameStream(&PanasonicMakerNote::print0x0029, *v);
}

TEST_F(PanasonicMakerNoteTest_706, Print0x0033ReturnsStreamReference_706) {
  auto v = MakeValueFromString<Exiv2::unsignedShort>("0");
  ExpectPrintFnReturnsSameStream(&PanasonicMakerNote::print0x0033, *v);
}

TEST_F(PanasonicMakerNoteTest_706, Print0x0036ReturnsStreamReference_706) {
  auto v = MakeValueFromString<Exiv2::unsignedShort>("0");
  ExpectPrintFnReturnsSameStream(&PanasonicMakerNote::print0x0036, *v);
}

TEST_F(PanasonicMakerNoteTest_706, Print0x003cReturnsStreamReference_706) {
  auto v = MakeValueFromString<Exiv2::unsignedShort>("0");
  ExpectPrintFnReturnsSameStream(&PanasonicMakerNote::print0x003c, *v);
}

TEST_F(PanasonicMakerNoteTest_706, PrintPanasonicTextReturnsStreamReference_706) {
  // Boundary-ish input: empty string read into a Value instance.
  auto v = MakeValueFromString<Exiv2::unsignedShort>("");  // intentionally empty
  ExpectPrintFnReturnsSameStream(&PanasonicMakerNote::printPanasonicText, *v);
}

TEST_F(PanasonicMakerNoteTest_706, PrintPressureReturnsStreamReference_706) {
  // Boundary-ish input: a single numeric component.
  auto v = MakeValueFromString<Exiv2::unsignedLong>("0");
  ExpectPrintFnReturnsSameStream(&PanasonicMakerNote::printPressure, *v);
}

TEST_F(PanasonicMakerNoteTest_706, PrintAccelerometerReturnsStreamReference_706) {
  // Provide multiple components (common for accelerometer-like fields),
  // but assert only that the function is safe and returns the stream.
  auto v = MakeValueFromString<Exiv2::signedShort>("0 0 0");
  ExpectPrintFnReturnsSameStream(&PanasonicMakerNote::printAccelerometer, *v);
}

TEST_F(PanasonicMakerNoteTest_706, PrintRollAngleReturnsStreamReference_706) {
  auto v = MakeValueFromString<Exiv2::signedShort>("0");
  ExpectPrintFnReturnsSameStream(&PanasonicMakerNote::printRollAngle, *v);
}

TEST_F(PanasonicMakerNoteTest_706, PrintPitchAngleReturnsStreamReference_706) {
  auto v = MakeValueFromString<Exiv2::signedShort>("0");
  ExpectPrintFnReturnsSameStream(&PanasonicMakerNote::printPitchAngle, *v);
}

TEST_F(PanasonicMakerNoteTest_706, PrintFunctionsHandleNullExifData_706) {
  // Exceptional/error-case (observable): passing null ExifData* should not
  // invalidate the stream reference contract.
  auto v = MakeValueFromString<Exiv2::unsignedShort>("1");

  std::ostringstream os;
  auto& ret = PanasonicMakerNote::print0x0023(os, *v, nullptr);
  EXPECT_EQ(&ret, &os);
  EXPECT_TRUE(os.good());
}