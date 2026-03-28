// File: ./TestProjects/exiv2/test/nikonmn_int_test_502.cpp
// Unit tests for Exiv2::Internal::Nikon3MakerNote::printFlashZoomHeadPosition
//
// Constraints honored:
// - Treat implementation as a black box
// - Test only observable behavior via public interface (ostream output)
// - No private state access
// - Include normal, boundary, and error/exceptional (observable) cases
//
// TEST_ID: 502

#include <gtest/gtest.h>

#include <cstdint>
#include <sstream>
#include <string>
#include <vector>

// Include the real header that declares Nikon3MakerNote.
// Depending on your Exiv2 tree, this may differ.
// Keep it as the project-typical internal header.
#include "nikonmn_int.hpp"

// Exiv2 public types
#include "exif.hpp"
#include "value.hpp"
#include "types.hpp"

namespace {

using Exiv2::ExifData;
using Exiv2::Value;
using Exiv2::TypeId;
using Exiv2::Internal::Nikon3MakerNote;

class Nikon3MakerNoteTest_502 : public ::testing::Test {
 protected:
  Nikon3MakerNote sut_;
  ExifData exif_;  // Not used by this method, but passed to match signature.
};

static std::string CallPrintFlashZoomHeadPosition(Nikon3MakerNote& sut, const Value& v, const ExifData* exif) {
  std::ostringstream oss;
  sut.printFlashZoomHeadPosition(oss, v, exif);
  return oss.str();
}

}  // namespace

TEST_F(Nikon3MakerNoteTest_502, PrintsMmForUnsignedByteSingleCount_502) {
  // Normal case: unsignedByte, count == 1, convertible to uint32 -> "<n> mm"
  Exiv2::DataValue dv;  // DataValue lets us set type + raw bytes.
  dv.read("24", Exiv2::unsignedByte);  // one byte, value 24

  const std::string out = CallPrintFlashZoomHeadPosition(sut_, dv, &exif_);
  EXPECT_EQ(out, "24 mm");
}

TEST_F(Nikon3MakerNoteTest_502, AcceptsNullExifDataPointer_502) {
  // Boundary: exif pointer can be null; output should still be well-formed.
  Exiv2::DataValue dv;
  dv.read("50", Exiv2::unsignedByte);

  const std::string out = CallPrintFlashZoomHeadPosition(sut_, dv, nullptr);
  EXPECT_EQ(out, "50 mm");
}

TEST_F(Nikon3MakerNoteTest_502, PrintsParenthesizedValueWhenCountIsNotOne_502) {
  // Error/exceptional (observable): count != 1 triggers "(" << value << ")"
  Exiv2::DataValue dv;
  // Two bytes => count == 2 for unsignedByte
  dv.read("1 2", Exiv2::unsignedByte);

  const std::string out = CallPrintFlashZoomHeadPosition(sut_, dv, &exif_);

  // We can't assume Value's exact string formatting, but we can verify the wrapper.
  ASSERT_GE(out.size(), 2u);
  EXPECT_EQ(out.front(), '(');
  EXPECT_EQ(out.back(), ')');
}

TEST_F(Nikon3MakerNoteTest_502, PrintsParenthesizedValueWhenTypeIsNotUnsignedByte_502) {
  // Error/exceptional (observable): typeId != unsignedByte triggers "(" << value << ")"
  Exiv2::DataValue dv;
  dv.read("24", Exiv2::unsignedShort);  // different type

  const std::string out = CallPrintFlashZoomHeadPosition(sut_, dv, &exif_);

  ASSERT_GE(out.size(), 2u);
  EXPECT_EQ(out.front(), '(');
  EXPECT_EQ(out.back(), ')');
}

TEST_F(Nikon3MakerNoteTest_502, FormatsZeroAs0Mm_502) {
  // Boundary: value == 0 should still be formatted as "0 mm" if convertible.
  Exiv2::DataValue dv;
  dv.read("0", Exiv2::unsignedByte);

  const std::string out = CallPrintFlashZoomHeadPosition(sut_, dv, &exif_);
  EXPECT_EQ(out, "0 mm");
}

TEST_F(Nikon3MakerNoteTest_502, OutputIsWrittenToProvidedStream_502) {
  // Verification of interaction with external collaborator: the ostream receives output.
  // Observable via stream contents; no mocking needed.
  Exiv2::DataValue dv;
  dv.read("35", Exiv2::unsignedByte);

  std::ostringstream oss;
  sut_.printFlashZoomHeadPosition(oss, dv, &exif_);
  EXPECT_EQ(oss.str(), "35 mm");
}