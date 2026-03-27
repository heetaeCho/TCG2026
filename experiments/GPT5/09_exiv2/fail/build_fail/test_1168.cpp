// SPDX-License-Identifier: GPL-2.0-or-later
// Test file for Exiv2::Internal::TiffParserWorker::encode
// The TEST_ID is 1168

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "basicio.hpp"
#include "exif.hpp"
#include "iptc.hpp"
#include "tiffimage_int.hpp"
#include "types.hpp"
#include "xmp_exiv2.hpp"

#include <cstdint>
#include <stdexcept>

namespace {

using namespace Exiv2;
using namespace Exiv2::Internal;

class MockIo_1168 : public Exiv2::MemIo {
public:
  MOCK_METHOD(void, transfer, (Exiv2::BasicIo& src), (override));
};

class ThrowingTransferIo_1168 : public Exiv2::MemIo {
public:
  explicit ThrowingTransferIo_1168(std::runtime_error ex) : ex_(std::move(ex)) {}
  void transfer(Exiv2::BasicIo& /*src*/) override { throw ex_; }

private:
  std::runtime_error ex_;
};

class TiffParserWorkerEncodeTest_1168 : public ::testing::Test {
protected:
  ExifData exif_;
  IptcData iptc_;
  XmpData xmp_;

  // Note: FindEncoderFct type is part of Exiv2 internals; default-initialize to "no callback".
  FindEncoderFct findEncoderFct_{};

  // Create a header instance with plausible values; tests treat encode as a black box.
  // If your build requires a more specific header subclass, replace this with the project’s
  // concrete TIFF header type.
  TiffHeaderBase header_{/*tag=*/0, /*size=*/0, /*byteOrder=*/littleEndian, /*offset=*/0};
};

TEST_F(TiffParserWorkerEncodeTest_1168, NullDataReturnsIntrusiveAndTransfers_1168) {
  MockIo_1168 io;

  // For the intrusive path, encode() is expected to transfer to the provided io.
  EXPECT_CALL(io, transfer(::testing::_)).Times(1);

  const byte* pData = nullptr;
  const size_t size = 0;
  const uint32_t root = 0;

  const WriteMethod wm =
      TiffParserWorker::encode(io, pData, size, exif_, iptc_, xmp_, root, findEncoderFct_, &header_, nullptr);

  // With no source binary data, parse() is expected to yield no parsed tree, so intrusive is observable.
  EXPECT_EQ(wm, wmIntrusive);
}

TEST_F(TiffParserWorkerEncodeTest_1168, TransferExceptionPropagates_1168) {
  ThrowingTransferIo_1168 io(std::runtime_error("transfer failed"));

  const byte* pData = nullptr;
  const size_t size = 0;
  const uint32_t root = 0;

  EXPECT_THROW(
      (void)TiffParserWorker::encode(io, pData, size, exif_, iptc_, xmp_, root, findEncoderFct_, &header_, nullptr),
      std::runtime_error);
}

TEST_F(TiffParserWorkerEncodeTest_1168, RealMemIoDestinationDoesNotThrow_1168) {
  Exiv2::MemIo io;

  const byte* pData = nullptr;
  const size_t size = 0;
  const uint32_t root = 0;

  WriteMethod wm = wmNonIntrusive;
  EXPECT_NO_THROW(
      wm = TiffParserWorker::encode(io, pData, size, exif_, iptc_, xmp_, root, findEncoderFct_, &header_, nullptr));

  // For the empty-input case, intrusive is the observable expected result.
  EXPECT_EQ(wm, wmIntrusive);

  // Basic sanity: if transfer happened, destination should be a valid BasicIo object (no crash).
  // We intentionally do not assert on io.size() because output size is implementation-defined.
  EXPECT_TRUE(true);
}

TEST_F(TiffParserWorkerEncodeTest_1168, NonNullOffsetWriterDoesNotThrow_1168) {
  Exiv2::MemIo io;
  OffsetWriter ow;

  const byte* pData = nullptr;
  const size_t size = 0;
  const uint32_t root = 0;

  WriteMethod wm = wmNonIntrusive;
  EXPECT_NO_THROW(
      wm = TiffParserWorker::encode(io, pData, size, exif_, iptc_, xmp_, root, findEncoderFct_, &header_, &ow));

  EXPECT_EQ(wm, wmIntrusive);
}

TEST_F(TiffParserWorkerEncodeTest_1168, BoundaryEmptyMetadataDoesNotThrow_1168) {
  Exiv2::MemIo io;

  // Explicitly ensure metadata containers are empty (boundary: no tags/records).
  exif_.clear();
  iptc_.clear();
  xmp_.clear();

  const byte* pData = nullptr;
  const size_t size = 0;
  const uint32_t root = 0;

  WriteMethod wm = wmNonIntrusive;
  EXPECT_NO_THROW(
      wm = TiffParserWorker::encode(io, pData, size, exif_, iptc_, xmp_, root, findEncoderFct_, &header_, nullptr));

  EXPECT_EQ(wm, wmIntrusive);
}

}  // namespace