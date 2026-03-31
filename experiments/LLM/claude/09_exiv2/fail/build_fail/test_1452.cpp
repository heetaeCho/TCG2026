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

// Since we need to test the write method which takes an IoWrapper,
// we need to work with the actual types from the library.

class OMSystemMnHeaderTest_1452 : public ::testing::Test {
 protected:
  void SetUp() override {
  }

  void TearDown() override {
  }
};

// Test that write() writes data and returns the size of the signature
TEST_F(OMSystemMnHeaderTest_1452, WriteReturnsSizeOfSignature_1452) {
  OMSystemMnHeader header;
  
  // Create a memory-based IO to capture written data
  Exiv2::Blob blob;
  Exiv2::MemIo memIo;
  
  // We need an IoWrapper - it wraps a BasicIo
  // IoWrapper requires a BasicIo reference and optionally other params
  IoWrapper ioWrapper(memIo, nullptr, 0, nullptr);
  
  size_t result = header.write(ioWrapper, Exiv2::bigEndian);
  
  // The write method should return sizeOfSignature() which should be > 0
  EXPECT_GT(result, 0u);
}

// Test that write() returns consistent size regardless of byte order (big endian)
TEST_F(OMSystemMnHeaderTest_1452, WriteWithBigEndianReturnsSignatureSize_1452) {
  OMSystemMnHeader header;
  Exiv2::MemIo memIo;
  IoWrapper ioWrapper(memIo, nullptr, 0, nullptr);
  
  size_t result = header.write(ioWrapper, Exiv2::bigEndian);
  EXPECT_GT(result, 0u);
}

// Test that write() returns consistent size regardless of byte order (little endian)
TEST_F(OMSystemMnHeaderTest_1452, WriteWithLittleEndianReturnsSignatureSize_1452) {
  OMSystemMnHeader header;
  Exiv2::MemIo memIo;
  IoWrapper ioWrapper(memIo, nullptr, 0, nullptr);
  
  size_t result = header.write(ioWrapper, Exiv2::littleEndian);
  EXPECT_GT(result, 0u);
}

// Test that write returns the same size for both byte orders
TEST_F(OMSystemMnHeaderTest_1452, WriteReturnsSameSizeForBothByteOrders_1452) {
  OMSystemMnHeader header;
  
  Exiv2::MemIo memIoBig;
  IoWrapper ioWrapperBig(memIoBig, nullptr, 0, nullptr);
  size_t resultBig = header.write(ioWrapperBig, Exiv2::bigEndian);
  
  Exiv2::MemIo memIoLittle;
  IoWrapper ioWrapperLittle(memIoLittle, nullptr, 0, nullptr);
  size_t resultLittle = header.write(ioWrapperLittle, Exiv2::littleEndian);
  
  EXPECT_EQ(resultBig, resultLittle);
}

// Test that calling write multiple times produces the same result
TEST_F(OMSystemMnHeaderTest_1452, WriteIsIdempotent_1452) {
  OMSystemMnHeader header;
  
  Exiv2::MemIo memIo1;
  IoWrapper ioWrapper1(memIo1, nullptr, 0, nullptr);
  size_t result1 = header.write(ioWrapper1, Exiv2::bigEndian);
  
  Exiv2::MemIo memIo2;
  IoWrapper ioWrapper2(memIo2, nullptr, 0, nullptr);
  size_t result2 = header.write(ioWrapper2, Exiv2::bigEndian);
  
  EXPECT_EQ(result1, result2);
}

// Test that data is actually written to the IO
TEST_F(OMSystemMnHeaderTest_1452, WriteActuallyWritesData_1452) {
  OMSystemMnHeader header;
  Exiv2::MemIo memIo;
  IoWrapper ioWrapper(memIo, nullptr, 0, nullptr);
  
  size_t written = header.write(ioWrapper, Exiv2::bigEndian);
  
  // The MemIo should now contain the written data
  EXPECT_EQ(static_cast<size_t>(memIo.size()), written);
}

// Test that two separate writes produce identical data
TEST_F(OMSystemMnHeaderTest_1452, WriteProducesConsistentData_1452) {
  OMSystemMnHeader header;
  
  Exiv2::MemIo memIo1;
  IoWrapper ioWrapper1(memIo1, nullptr, 0, nullptr);
  header.write(ioWrapper1, Exiv2::bigEndian);
  
  Exiv2::MemIo memIo2;
  IoWrapper ioWrapper2(memIo2, nullptr, 0, nullptr);
  header.write(ioWrapper2, Exiv2::bigEndian);
  
  ASSERT_EQ(memIo1.size(), memIo2.size());
  
  // Read data from both and compare
  memIo1.seek(0, BasicIo::beg);
  memIo2.seek(0, BasicIo::beg);
  
  std::vector<byte> data1(memIo1.size());
  std::vector<byte> data2(memIo2.size());
  
  memIo1.read(data1.data(), data1.size());
  memIo2.read(data2.data(), data2.size());
  
  EXPECT_EQ(data1, data2);
}
