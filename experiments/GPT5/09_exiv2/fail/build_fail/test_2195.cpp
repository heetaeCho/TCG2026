// TEST_ID 2195
// File: test_sonymnheader_2195.cpp

#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "makernote_int.hpp"
#include "exiv2/types.hpp"

namespace {

using Exiv2::ByteOrder;
using Exiv2::bigEndian;
using Exiv2::invalidByteOrder;
using Exiv2::littleEndian;

using Exiv2::Internal::SonyMnHeader;

class SonyMnHeaderTest_2195 : public ::testing::Test {};

TEST_F(SonyMnHeaderTest_2195, DefaultConstructionDoesNotThrow_2195) {
  EXPECT_NO_THROW({
    SonyMnHeader hdr;
    (void)hdr;
  });
}

TEST_F(SonyMnHeaderTest_2195, SizeOfSignatureIsDeterministic_2195) {
  const size_t s1 = SonyMnHeader::sizeOfSignature();
  const size_t s2 = SonyMnHeader::sizeOfSignature();
  EXPECT_EQ(s1, s2);
}

TEST_F(SonyMnHeaderTest_2195, AccessorsCallableAfterConstruction_2195) {
  SonyMnHeader hdr;

  // These should be callable; we only assert basic invariants observable via the interface.
  EXPECT_NO_THROW({ (void)hdr.size(); });
  EXPECT_NO_THROW({ (void)hdr.ifdOffset(); });
  EXPECT_NO_THROW({ (void)hdr.byteOrder(); });

  // Returned enum value should be one of the declared ByteOrder enumerators.
  const ByteOrder bo = hdr.byteOrder();
  EXPECT_TRUE(bo == invalidByteOrder || bo == littleEndian || bo == bigEndian);
}

TEST_F(SonyMnHeaderTest_2195, AccessorsAreStableAcrossRepeatedCalls_2195) {
  SonyMnHeader hdr;

  const size_t sz1 = hdr.size();
  const size_t sz2 = hdr.size();
  EXPECT_EQ(sz1, sz2);

  const size_t off1 = hdr.ifdOffset();
  const size_t off2 = hdr.ifdOffset();
  EXPECT_EQ(off1, off2);

  const ByteOrder bo1 = hdr.byteOrder();
  const ByteOrder bo2 = hdr.byteOrder();
  EXPECT_EQ(bo1, bo2);
}

TEST_F(SonyMnHeaderTest_2195, ReadWithNullAndZeroSizeDoesNotThrow_2195) {
  SonyMnHeader hdr;

  EXPECT_NO_THROW({
    const bool ok = hdr.read(nullptr, 0u, invalidByteOrder);
    (void)ok;  // Return value is implementation-defined; we only require it is callable.
  });
}

TEST_F(SonyMnHeaderTest_2195, ReadWithBufferSizeOfSignatureDoesNotThrow_InvalidByteOrder_2195) {
  SonyMnHeader hdr;

  const size_t sigSize = SonyMnHeader::sizeOfSignature();
  std::vector<unsigned char> buf(sigSize, 0u);

  EXPECT_NO_THROW({
    const bool ok = hdr.read(reinterpret_cast<const Exiv2::byte*>(buf.data()), buf.size(), invalidByteOrder);
    (void)ok;
  });
}

TEST_F(SonyMnHeaderTest_2195, ReadWithBufferSizeOfSignatureDoesNotThrow_LittleEndian_2195) {
  SonyMnHeader hdr;

  const size_t sigSize = SonyMnHeader::sizeOfSignature();
  std::vector<unsigned char> buf(sigSize, 0u);

  EXPECT_NO_THROW({
    const bool ok = hdr.read(reinterpret_cast<const Exiv2::byte*>(buf.data()), buf.size(), littleEndian);
    (void)ok;
  });
}

TEST_F(SonyMnHeaderTest_2195, ReadWithBufferSizeOfSignatureDoesNotThrow_BigEndian_2195) {
  SonyMnHeader hdr;

  const size_t sigSize = SonyMnHeader::sizeOfSignature();
  std::vector<unsigned char> buf(sigSize, 0u);

  EXPECT_NO_THROW({
    const bool ok = hdr.read(reinterpret_cast<const Exiv2::byte*>(buf.data()), buf.size(), bigEndian);
    (void)ok;
  });
}

TEST_F(SonyMnHeaderTest_2195, ReadBoundarySizesDoNotThrow_2195) {
  SonyMnHeader hdr;

  const size_t sigSize = SonyMnHeader::sizeOfSignature();

  // Boundary: size smaller than signature size (if sigSize > 0).
  if (sigSize > 0) {
    std::vector<unsigned char> smaller(sigSize - 1u, 0u);
    EXPECT_NO_THROW({
      const bool ok = hdr.read(reinterpret_cast<const Exiv2::byte*>(smaller.data()), smaller.size(), invalidByteOrder);
      (void)ok;
    });
  }

  // Boundary: size exactly signature size (already covered) and size larger than signature size.
  std::vector<unsigned char> larger(sigSize + 1u, 0u);
  EXPECT_NO_THROW({
    const bool ok = hdr.read(reinterpret_cast<const Exiv2::byte*>(larger.data()), larger.size(), invalidByteOrder);
    (void)ok;
  });
}

}  // namespace