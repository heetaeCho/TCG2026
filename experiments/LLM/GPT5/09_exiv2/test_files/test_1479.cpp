// ***************************************************************** -*- C++ -*-
// Unit tests for Exiv2::Internal::PentaxDngMnHeader
// File: test_pentaxdngmnheader_1479.cpp
// *****************************************************************

#include <gtest/gtest.h>

#include "makernote_int.hpp"
#include "basicio.hpp"   // MemIo
#include "types.hpp"     // DataBuf, ByteOrder

#include <cstddef>
#include <cstdint>
#include <limits>
#include <type_traits>

namespace {

using Exiv2::ByteOrder;
using Exiv2::DataBuf;
using Exiv2::MemIo;
using Exiv2::Internal::IoWrapper;
using Exiv2::Internal::MnHeader;
using Exiv2::Internal::PentaxDngMnHeader;

class PentaxDngMnHeaderTest_1479 : public ::testing::Test {
 protected:
  PentaxDngMnHeader hdr_;
};

TEST_F(PentaxDngMnHeaderTest_1479, DefaultConstructed_SizeIsStable_1479) {
  const size_t s1 = hdr_.size();
  const size_t s2 = hdr_.size();
  const size_t s3 = hdr_.size();
  EXPECT_EQ(s1, s2);
  EXPECT_EQ(s2, s3);
}

TEST_F(PentaxDngMnHeaderTest_1479, PolymorphicSizeMatchesConcreteSize_1479) {
  MnHeader& base = hdr_;
  const size_t concrete = hdr_.size();
  const size_t poly = base.size();
  EXPECT_EQ(concrete, poly);
}

TEST_F(PentaxDngMnHeaderTest_1479, SizeOfSignature_IsDeterministic_1479) {
  const size_t a = PentaxDngMnHeader::sizeOfSignature();
  const size_t b = PentaxDngMnHeader::sizeOfSignature();
  EXPECT_EQ(a, b);
}

TEST_F(PentaxDngMnHeaderTest_1479, IfdOffset_IsDeterministic_1479) {
  const size_t a = hdr_.ifdOffset();
  const size_t b = hdr_.ifdOffset();
  EXPECT_EQ(a, b);
}

TEST_F(PentaxDngMnHeaderTest_1479, BaseOffset_BoundariesAreCallableAndDeterministic_1479) {
  const size_t inputs[] = {
      0u,
      1u,
      hdr_.size(),
      std::numeric_limits<size_t>::max() / 2u,
      std::numeric_limits<size_t>::max(),
  };

  for (const size_t mnOffset : inputs) {
    size_t out1 = 0, out2 = 0;
    EXPECT_NO_THROW(out1 = hdr_.baseOffset(mnOffset));
    EXPECT_NO_THROW(out2 = hdr_.baseOffset(mnOffset));
    EXPECT_EQ(out1, out2);
  }
}

TEST_F(PentaxDngMnHeaderTest_1479, Read_WithEmptyBuffer_DoesNotThrowAndSizeStaysStable_1479) {
  const size_t before = hdr_.size();

  bool r1 = false;
  EXPECT_NO_THROW(r1 = hdr_.read(nullptr, 0u, ByteOrder::littleEndian));
  (void)r1;

  const size_t after = hdr_.size();
  EXPECT_EQ(before, after);
}

TEST_F(PentaxDngMnHeaderTest_1479, Read_WithZeroedBuffer_BothByteOrdersCallable_1479) {
  const size_t before = hdr_.size();

  DataBuf buf(before);
  // Ensure deterministic contents.
  for (size_t i = 0; i < buf.size(); ++i) {
    buf.write_uint8(i, 0u);
  }

  bool rLittle = false;
  bool rBig = false;

  EXPECT_NO_THROW(rLittle = hdr_.read(buf.c_data(0), buf.size(), ByteOrder::littleEndian));
  EXPECT_NO_THROW(rBig = hdr_.read(buf.c_data(0), buf.size(), ByteOrder::bigEndian));
  (void)rLittle;
  (void)rBig;

  // Size() should remain stable across operations (observed via public API).
  EXPECT_EQ(before, hdr_.size());
}

TEST_F(PentaxDngMnHeaderTest_1479, Write_ToMemIo_DoesNotThrowAndReturnsDeterministicSize_1479) {
  MemIo mem;
  IoWrapper io(mem);

  size_t out1 = 0;
  size_t out2 = 0;

  EXPECT_NO_THROW(out1 = hdr_.write(io, ByteOrder::littleEndian));
  EXPECT_NO_THROW(out2 = hdr_.write(io, ByteOrder::littleEndian));

  EXPECT_EQ(out1, out2);
}

TEST_F(PentaxDngMnHeaderTest_1479, Write_InBothByteOrders_IsCallable_1479) {
  MemIo mem1;
  IoWrapper io1(mem1);

  MemIo mem2;
  IoWrapper io2(mem2);

  size_t outLittle = 0;
  size_t outBig = 0;

  EXPECT_NO_THROW(outLittle = hdr_.write(io1, ByteOrder::littleEndian));
  EXPECT_NO_THROW(outBig = hdr_.write(io2, ByteOrder::bigEndian));

  // We don't assume equality across byte orders; we only require the calls succeed and are observable.
  (void)outLittle;
  (void)outBig;
}

}  // namespace