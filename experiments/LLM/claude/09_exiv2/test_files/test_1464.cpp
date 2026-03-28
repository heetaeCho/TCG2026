#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstdint>
#include <cstring>
#include <vector>

// We need to include the necessary Exiv2 headers
#include "makernote_int.hpp"
#include "exiv2/exiv2.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// Since IoWrapper and related types are part of Exiv2's internal infrastructure,
// we need to work with what's available through the public/internal headers.

class Nikon2MnHeaderTest_1464 : public ::testing::Test {
 protected:
  void SetUp() override {
  }

  void TearDown() override {
  }
};

// Test that Nikon2MnHeader can be default constructed
TEST_F(Nikon2MnHeaderTest_1464, DefaultConstruction_1464) {
  Nikon2MnHeader header;
  // If construction succeeds without throwing, the test passes
  SUCCEED();
}

// Test that sizeOfSignature returns a consistent positive value
TEST_F(Nikon2MnHeaderTest_1464, SizeOfSignatureIsPositive_1464) {
  Nikon2MnHeader header;
  EXPECT_GT(header.sizeOfSignature(), static_cast<size_t>(0));
}

// Test that sizeOfSignature returns the same value on repeated calls
TEST_F(Nikon2MnHeaderTest_1464, SizeOfSignatureIsConsistent_1464) {
  Nikon2MnHeader header;
  size_t size1 = header.sizeOfSignature();
  size_t size2 = header.sizeOfSignature();
  EXPECT_EQ(size1, size2);
}

// Test that write returns the size of the signature
TEST_F(Nikon2MnHeaderTest_1464, WriteReturnsSizeOfSignature_1464) {
  Nikon2MnHeader header;

  // Create a memory-backed BasicIo for writing
  Exiv2::MemIo memIo;
  // We need an IoWrapper - construct one using available means
  // IoWrapper typically wraps a BasicIo
  IoWrapper ioWrapper(memIo, nullptr, 0, nullptr);

  size_t written = header.write(ioWrapper, Exiv2::bigEndian);
  EXPECT_EQ(written, header.sizeOfSignature());
}

// Test write with little endian byte order
TEST_F(Nikon2MnHeaderTest_1464, WriteWithLittleEndian_1464) {
  Nikon2MnHeader header;

  Exiv2::MemIo memIo;
  IoWrapper ioWrapper(memIo, nullptr, 0, nullptr);

  size_t written = header.write(ioWrapper, Exiv2::littleEndian);
  EXPECT_EQ(written, header.sizeOfSignature());
}

// Test that write actually writes data to the stream
TEST_F(Nikon2MnHeaderTest_1464, WriteActuallyWritesData_1464) {
  Nikon2MnHeader header;

  Exiv2::MemIo memIo;
  IoWrapper ioWrapper(memIo, nullptr, 0, nullptr);

  header.write(ioWrapper, Exiv2::bigEndian);

  // The MemIo should now contain data equal to sizeOfSignature bytes
  EXPECT_GE(memIo.size(), header.sizeOfSignature());
}

// Test that two consecutive writes produce consistent results
TEST_F(Nikon2MnHeaderTest_1464, ConsecutiveWritesProduceSameSize_1464) {
  Nikon2MnHeader header;

  Exiv2::MemIo memIo1;
  IoWrapper ioWrapper1(memIo1, nullptr, 0, nullptr);
  size_t written1 = header.write(ioWrapper1, Exiv2::bigEndian);

  Exiv2::MemIo memIo2;
  IoWrapper ioWrapper2(memIo2, nullptr, 0, nullptr);
  size_t written2 = header.write(ioWrapper2, Exiv2::bigEndian);

  EXPECT_EQ(written1, written2);
}

// Test that write returns same value regardless of byte order (since signature is fixed)
TEST_F(Nikon2MnHeaderTest_1464, WriteReturnSameForDifferentByteOrders_1464) {
  Nikon2MnHeader header;

  Exiv2::MemIo memIoBE;
  IoWrapper ioWrapperBE(memIoBE, nullptr, 0, nullptr);
  size_t writtenBE = header.write(ioWrapperBE, Exiv2::bigEndian);

  Exiv2::MemIo memIoLE;
  IoWrapper ioWrapperLE(memIoLE, nullptr, 0, nullptr);
  size_t writtenLE = header.write(ioWrapperLE, Exiv2::littleEndian);

  EXPECT_EQ(writtenBE, writtenLE);
}

// Test the read method if available
TEST_F(Nikon2MnHeaderTest_1464, ReadValidSignature_1464) {
  Nikon2MnHeader header;
  // First write to get the signature bytes
  Exiv2::MemIo memIo;
  IoWrapper ioWrapper(memIo, nullptr, 0, nullptr);
  header.write(ioWrapper, Exiv2::bigEndian);

  // Now read it back
  memIo.seek(0, Exiv2::BasicIo::beg);
  std::vector<Exiv2::byte> buf(memIo.size());
  memIo.read(buf.data(), buf.size());

  Nikon2MnHeader header2;
  bool result = header2.read(buf.data(), static_cast<uint32_t>(buf.size()), Exiv2::bigEndian);
  EXPECT_TRUE(result);
}
