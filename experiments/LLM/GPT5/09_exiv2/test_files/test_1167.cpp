// =================================================================================================
// TestProjects/exiv2/src/tiffimage_int_test_1167.cpp
// Unit tests for Exiv2::Internal::TiffParserWorker::decode
// =================================================================================================

#include <gtest/gtest.h>

#include <cstdint>
#include <limits>
#include <vector>

#include "tiffimage_int.hpp"

#include <exiv2/exif.hpp>
#include <exiv2/iptc.hpp>
#include <exiv2/xmp_exiv2.hpp>
#include <exiv2/types.hpp>

namespace {

using Exiv2::ByteOrder;
using Exiv2::ExifData;
using Exiv2::IptcData;
using Exiv2::XmpData;

using Exiv2::Internal::TiffHeaderBase;
using Exiv2::Internal::TiffParserWorker;

// A minimal header implementation that allows observing the byte order returned by decode()
// without depending on TiffHeader's concrete behavior.
class TrackingHeader final : public TiffHeaderBase {
 public:
  explicit TrackingHeader(ByteOrder initialBo)
      : TiffHeaderBase(/*tag*/ 0, /*size*/ 0, initialBo, /*offset*/ 0), bo_(initialBo) {}

  ByteOrder byteOrder() const override { return bo_; }
  void setByteOrder(ByteOrder byteOrder) override {
    bo_ = byteOrder;
    ++setByteOrderCalls_;
  }

  uint32_t offset() const override { return offset_; }
  void setOffset(uint32_t offset) override { offset_ = offset; }

  uint32_t size() const override { return size_; }
  uint16_t tag() const override { return 0; }

  int setByteOrderCalls() const { return setByteOrderCalls_; }

 private:
  ByteOrder bo_;
  uint32_t offset_{0};
  uint32_t size_{0};
  int setByteOrderCalls_{0};
};

class TiffParserWorkerTest_1167 : public ::testing::Test {
 protected:
  ExifData exif_;
  IptcData iptc_;
  XmpData xmp_;
};

TEST_F(TiffParserWorkerTest_1167, DecodeReturnsSameByteOrderAsHeaderAfterCall_1167) {
  // Use a provided header so the test doesn't depend on any default TiffHeader behavior.
  TrackingHeader header(Exiv2::littleEndian);

  const Exiv2::byte* pData = nullptr;
  const size_t size = 0;

  ByteOrder result{};
  ASSERT_NO_THROW({
    result = TiffParserWorker::decode(exif_, iptc_, xmp_, pData, size,
                                     /*root*/ 0U,
                                     /*findDecoderFct*/ nullptr,
                                     /*pHeader*/ &header);
  });

  // Observable behavior from the interface: decode returns a ByteOrder.
  // We only assert it matches the header's byteOrder() after decode returns.
  EXPECT_EQ(result, header.byteOrder());
}

TEST_F(TiffParserWorkerTest_1167, DecodeWithNullHeaderDoesNotThrowOnEmptyInput_1167) {
  // pHeader == nullptr should be handled by the implementation.
  const Exiv2::byte* pData = nullptr;
  const size_t size = 0;

  ByteOrder result{};
  EXPECT_NO_THROW({
    result = TiffParserWorker::decode(exif_, iptc_, xmp_, pData, size,
                                     /*root*/ 0U,
                                     /*findDecoderFct*/ nullptr,
                                     /*pHeader*/ nullptr);
  });

  // We don't assume a specific default byte order; just ensure we got a value back.
  // (ByteOrder is an enum; any returned value is acceptable for this black-box test.)
  (void)result;
}

TEST_F(TiffParserWorkerTest_1167, DecodeAcceptsBoundaryRootValuesWithoutThrow_1167) {
  TrackingHeader header(Exiv2::bigEndian);

  const Exiv2::byte* pData = nullptr;
  const size_t size = 0;

  ByteOrder r0{};
  EXPECT_NO_THROW({
    r0 = TiffParserWorker::decode(exif_, iptc_, xmp_, pData, size,
                                 /*root*/ 0U,
                                 /*findDecoderFct*/ nullptr,
                                 /*pHeader*/ &header);
  });
  EXPECT_EQ(r0, header.byteOrder());

  ByteOrder rMax{};
  EXPECT_NO_THROW({
    rMax = TiffParserWorker::decode(exif_, iptc_, xmp_, pData, size,
                                   /*root*/ (std::numeric_limits<uint32_t>::max)(),
                                   /*findDecoderFct*/ nullptr,
                                   /*pHeader*/ &header);
  });
  EXPECT_EQ(rMax, header.byteOrder());
}

TEST_F(TiffParserWorkerTest_1167, DecodeWithNonNullPointerButZeroSizeDoesNotThrow_1167) {
  TrackingHeader header(Exiv2::littleEndian);

  // Provide a non-null pointer with size == 0 to exercise boundary behavior.
  std::vector<Exiv2::byte> dummy(1, 0);
  const Exiv2::byte* pData = dummy.data();
  const size_t size = 0;

  ByteOrder result{};
  EXPECT_NO_THROW({
    result = TiffParserWorker::decode(exif_, iptc_, xmp_, pData, size,
                                     /*root*/ 0U,
                                     /*findDecoderFct*/ nullptr,
                                     /*pHeader*/ &header);
  });

  EXPECT_EQ(result, header.byteOrder());
}

}  // namespace