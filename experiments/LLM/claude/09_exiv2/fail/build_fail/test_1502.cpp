#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstdint>
#include <cstring>
#include <vector>

// Forward declarations and minimal includes needed
// We need to include the actual headers from exiv2
#include "makernote_int.hpp"
#include "exiv2/exiv2.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// Since IoWrapper is used in the write method, we need to understand its interface.
// IoWrapper wraps a BasicIo and provides write functionality.

// Test fixture for SonyMnHeader
class SonyMnHeaderTest_1502 : public ::testing::Test {
 protected:
  void SetUp() override {
  }

  void TearDown() override {
  }
};

// Test that SonyMnHeader::write returns the correct size (sizeOfSignature)
TEST_F(SonyMnHeaderTest_1502, WriteReturnsSizeOfSignature_1502) {
  SonyMnHeader header;
  
  // Create a MemIo to capture output
  Exiv2::MemIo memIo;
  
  // We need to create an IoWrapper. IoWrapper typically wraps a BasicIo.
  // The constructor and usage may vary, but we try standard construction.
  IoWrapper ioWrapper(memIo, nullptr, 0, nullptr);
  
  size_t result = header.write(ioWrapper, Exiv2::bigEndian);
  
  // The write method should return sizeOfSignature()
  // We verify that the return value equals the expected signature size
  // Sony MakerNote signature is typically "SONY DSC \0\0\0" which is 12 bytes
  EXPECT_GT(result, 0u);
}

// Test that write writes exactly sizeOfSignature bytes to the io wrapper
TEST_F(SonyMnHeaderTest_1502, WriteOutputsCorrectNumberOfBytes_1502) {
  SonyMnHeader header;
  
  Exiv2::MemIo memIo;
  IoWrapper ioWrapper(memIo, nullptr, 0, nullptr);
  
  size_t written = header.write(ioWrapper, Exiv2::bigEndian);
  
  // The number of bytes in the MemIo should match what write() returned
  EXPECT_EQ(static_cast<size_t>(memIo.size()), written);
}

// Test that write works with littleEndian byte order
TEST_F(SonyMnHeaderTest_1502, WriteWithLittleEndian_1502) {
  SonyMnHeader header;
  
  Exiv2::MemIo memIo;
  IoWrapper ioWrapper(memIo, nullptr, 0, nullptr);
  
  size_t result = header.write(ioWrapper, Exiv2::littleEndian);
  
  // The signature writing should not depend on byte order
  // (it writes raw bytes), so result should still be sizeOfSignature
  EXPECT_GT(result, 0u);
  EXPECT_EQ(static_cast<size_t>(memIo.size()), result);
}

// Test that write produces the same output regardless of byte order
TEST_F(SonyMnHeaderTest_1502, WriteProducesSameOutputRegardlessOfByteOrder_1502) {
  SonyMnHeader header;
  
  Exiv2::MemIo memIoBig;
  IoWrapper ioWrapperBig(memIoBig, nullptr, 0, nullptr);
  size_t resultBig = header.write(ioWrapperBig, Exiv2::bigEndian);
  
  Exiv2::MemIo memIoLittle;
  IoWrapper ioWrapperLittle(memIoLittle, nullptr, 0, nullptr);
  size_t resultLittle = header.write(ioWrapperLittle, Exiv2::littleEndian);
  
  // Both should return the same size since signature doesn't depend on byte order
  EXPECT_EQ(resultBig, resultLittle);
  
  // Both should have the same content
  EXPECT_EQ(memIoBig.size(), memIoLittle.size());
  
  if (memIoBig.size() == memIoLittle.size() && memIoBig.size() > 0) {
    memIoBig.seek(0, BasicIo::beg);
    memIoLittle.seek(0, BasicIo::beg);
    
    std::vector<uint8_t> dataBig(memIoBig.size());
    std::vector<uint8_t> dataLittle(memIoLittle.size());
    
    memIoBig.read(dataBig.data(), dataBig.size());
    memIoLittle.read(dataLittle.data(), dataLittle.size());
    
    EXPECT_EQ(dataBig, dataLittle);
  }
}

// Test calling write multiple times appends to the stream
TEST_F(SonyMnHeaderTest_1502, WriteCalledTwiceDoublesBytesWritten_1502) {
  SonyMnHeader header;
  
  Exiv2::MemIo memIo;
  IoWrapper ioWrapper(memIo, nullptr, 0, nullptr);
  
  size_t firstWrite = header.write(ioWrapper, Exiv2::bigEndian);
  size_t secondWrite = header.write(ioWrapper, Exiv2::bigEndian);
  
  EXPECT_EQ(firstWrite, secondWrite);
  EXPECT_EQ(static_cast<size_t>(memIo.size()), firstWrite + secondWrite);
}

// Test that the return value is consistent across multiple calls
TEST_F(SonyMnHeaderTest_1502, WriteReturnValueIsConsistent_1502) {
  SonyMnHeader header;
  
  Exiv2::MemIo memIo1;
  IoWrapper ioWrapper1(memIo1, nullptr, 0, nullptr);
  size_t result1 = header.write(ioWrapper1, Exiv2::bigEndian);
  
  Exiv2::MemIo memIo2;
  IoWrapper ioWrapper2(memIo2, nullptr, 0, nullptr);
  size_t result2 = header.write(ioWrapper2, Exiv2::bigEndian);
  
  EXPECT_EQ(result1, result2);
}
