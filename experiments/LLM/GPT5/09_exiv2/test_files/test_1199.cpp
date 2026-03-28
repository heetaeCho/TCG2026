// ***************************************************************** -*- C++ -*-
// Unit tests for Exiv2::BmffImage::parseCr3Preview
// TEST_ID: 1199
// *****************************************************************

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <limits>
#include <memory>
#include <ostream>
#include <sstream>

#include "exiv2/basicio.hpp"
#include "exiv2/bmffimage.hpp"
#include "exiv2/types.hpp"

using ::testing::NiceMock;
using ::testing::Return;
using ::testing::HasSubstr;

namespace {

class MockBasicIo : public Exiv2::BasicIo {
 public:
  MOCK_METHOD(size_t, tell, (), (override));
};

class ParseCr3PreviewTest_1199 : public ::testing::Test {
 protected:
  std::unique_ptr<Exiv2::BmffImage> makeImageWithTell(size_t tell_value) {
    auto io = std::make_unique<NiceMock<MockBasicIo>>();
    auto* io_raw = io.get();
    ON_CALL(*io_raw, tell()).WillByDefault(Return(tell_value));

    // max_box_depth is irrelevant for parseCr3Preview; pick a small, valid value.
    return std::make_unique<Exiv2::BmffImage>(std::move(io), /*create*/ false, /*max_box_depth*/ 1);
  }

  // Use byte patterns that are invariant to endianness to avoid depending on internal byte order.
  Exiv2::DataBuf makeEndianInvariantBuf(size_t size,
                                       size_t w_off,
                                       size_t h_off,
                                       size_t s_off) {
    Exiv2::DataBuf buf(size);

    // 16-bit values: 0x0101 and 0xA5A5 (same when byte-swapped).
    // 32-bit value: 0x01010101 (same when byte-swapped).
    buf.write_uint16(w_off, static_cast<uint16_t>(0x0101), Exiv2::littleEndian);
    buf.write_uint16(h_off, static_cast<uint16_t>(0xA5A5), Exiv2::littleEndian);
    buf.write_uint32(s_off, static_cast<uint32_t>(0x01010101), Exiv2::littleEndian);

    return buf;
  }
};

TEST_F(ParseCr3PreviewTest_1199, AddsNativePreviewAndSetsFields_Version0MimeTypeJpeg_1199) {
  const size_t kHere = 123;
  const size_t kRel = 77;

  auto img = makeImageWithTell(kHere);

  const size_t w_off = 2;
  const size_t h_off = 6;
  const size_t s_off = 10;
  Exiv2::DataBuf data = makeEndianInvariantBuf(/*size*/ 32, w_off, h_off, s_off);

  std::ostringstream out;
  const bool bTrace = false;
  const uint8_t version = 0;

  const auto before = img->nativePreviews().size();
  img->parseCr3Preview(data, out, bTrace, version, w_off, h_off, s_off, kRel);
  const auto after = img->nativePreviews().size();

  ASSERT_EQ(after, before + 1);

  const auto& np = img->nativePreviews().back();
  EXPECT_EQ(np.position_, kHere + kRel);
  EXPECT_EQ(np.width_, 0x0101u);
  EXPECT_EQ(np.height_, 0xA5A5u);
  EXPECT_EQ(np.size_, 0x01010101u);
  EXPECT_TRUE(np.filter_.empty());
  EXPECT_EQ(np.mimeType_, "image/jpeg");
}

TEST_F(ParseCr3PreviewTest_1199, AddsNativePreview_VersionNonZeroMimeTypeOctetStream_1199) {
  const size_t kHere = 0;
  const size_t kRel = 0;

  auto img = makeImageWithTell(kHere);

  const size_t w_off = 0;
  const size_t h_off = 2;
  const size_t s_off = 4;
  Exiv2::DataBuf data = makeEndianInvariantBuf(/*size*/ 16, w_off, h_off, s_off);

  std::ostringstream out;
  const bool bTrace = false;
  const uint8_t version = 1;

  img->parseCr3Preview(data, out, bTrace, version, w_off, h_off, s_off, kRel);

  const auto& np = img->nativePreviews().back();
  EXPECT_EQ(np.position_, kHere + kRel);
  EXPECT_EQ(np.mimeType_, "application/octet-stream");
}

TEST_F(ParseCr3PreviewTest_1199, TraceEnabled_WritesHumanReadableSummaryToStream_1199) {
  const size_t kHere = 10;
  const size_t kRel = 5;

  auto img = makeImageWithTell(kHere);

  const size_t w_off = 1;
  const size_t h_off = 3;
  const size_t s_off = 5;
  Exiv2::DataBuf data = makeEndianInvariantBuf(/*size*/ 32, w_off, h_off, s_off);

  std::ostringstream out;
  const bool bTrace = true;

  img->parseCr3Preview(data, out, bTrace, /*version*/ 0, w_off, h_off, s_off, kRel);

  const std::string s = out.str();
  EXPECT_THAT(s, HasSubstr("width,height,size"));
  // Also ensure the numbers were emitted (using endianness-invariant values).
  EXPECT_THAT(s, HasSubstr("257"));        // 0x0101
  EXPECT_THAT(s, HasSubstr("42405"));      // 0xA5A5
  EXPECT_THAT(s, HasSubstr("16843009"));   // 0x01010101
}

TEST_F(ParseCr3PreviewTest_1199, Boundary_RelativePositionZero_PositionEqualsTell_1199) {
  const size_t kHere = 999;
  auto img = makeImageWithTell(kHere);

  const size_t w_off = 0;
  const size_t h_off = 2;
  const size_t s_off = 4;
  Exiv2::DataBuf data = makeEndianInvariantBuf(/*size*/ 16, w_off, h_off, s_off);

  std::ostringstream out;
  img->parseCr3Preview(data, out, /*bTrace*/ false, /*version*/ 0, w_off, h_off, s_off,
                       /*relative_position*/ 0);

  const auto& np = img->nativePreviews().back();
  EXPECT_EQ(np.position_, kHere);
}

TEST_F(ParseCr3PreviewTest_1199, Error_ArithmeticOverflowOnPositionComputation_Throws_1199) {
  // here == max, relative_position == 1 => should violate the checked condition.
  auto img = makeImageWithTell(std::numeric_limits<size_t>::max());

  const size_t w_off = 0;
  const size_t h_off = 2;
  const size_t s_off = 4;
  Exiv2::DataBuf data = makeEndianInvariantBuf(/*size*/ 16, w_off, h_off, s_off);

  std::ostringstream out;
  EXPECT_ANY_THROW(img->parseCr3Preview(data, out, /*bTrace*/ false, /*version*/ 0,
                                       w_off, h_off, s_off, /*relative_position*/ 1));
}

TEST_F(ParseCr3PreviewTest_1199, Error_DataBufOffsetsOutOfRange_Throws_1199) {
  auto img = makeImageWithTell(0);

  // Too small for requested offsets.
  Exiv2::DataBuf data(1);

  std::ostringstream out;
  EXPECT_ANY_THROW(img->parseCr3Preview(data, out, /*bTrace*/ false, /*version*/ 0,
                                       /*width_offset*/ 0,
                                       /*height_offset*/ 100,
                                       /*size_offset*/ 200,
                                       /*relative_position*/ 0));
}

}  // namespace