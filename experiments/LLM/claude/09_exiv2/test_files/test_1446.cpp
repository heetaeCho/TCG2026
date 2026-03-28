#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstdint>
#include <cstring>
#include <vector>

// We need to include the relevant headers from exiv2
#include "makernote_int.hpp"
#include "exiv2/exiv2.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// Since IoWrapper is used in the write method, we need to work with it.
// We'll create tests that exercise the Olympus2MnHeader::write method
// through the public interface.

class Olympus2MnHeaderTest_1446 : public ::testing::Test {
 protected:
  void SetUp() override {
  }

  void TearDown() override {
  }
};

// Test that Olympus2MnHeader can be constructed
TEST_F(Olympus2MnHeaderTest_1446, Construction_1446) {
  Olympus2MnHeader header;
  // If we get here without crashing, construction succeeded
  SUCCEED();
}

// Test that sizeOfSignature returns a positive value
TEST_F(Olympus2MnHeaderTest_1446, SizeOfSignatureIsPositive_1446) {
  Olympus2MnHeader header;
  EXPECT_GT(header.sizeOfSignature(), 0u);
}

// Test that write returns the size of the signature
TEST_F(Olympus2MnHeaderTest_1446, WriteReturnsSizeOfSignature_1446) {
  Olympus2MnHeader header;
  
  // Create an in-memory blob to write to
  Exiv2::Blob blob;
  MemIo memIo;
  // We need an IoWrapper to call write
  // IoWrapper wraps a BasicIo reference
  IoWrapper ioWrapper(memIo, nullptr, 0, nullptr);
  
  ByteOrder byteOrder = littleEndian;
  size_t result = header.write(ioWrapper, byteOrder);
  
  EXPECT_EQ(result, header.sizeOfSignature());
}

// Test that write produces output of expected size
TEST_F(Olympus2MnHeaderTest_1446, WriteProducesCorrectAmountOfData_1446) {
  Olympus2MnHeader header;
  
  MemIo memIo;
  IoWrapper ioWrapper(memIo, nullptr, 0, nullptr);
  
  ByteOrder byteOrder = bigEndian;
  size_t written = header.write(ioWrapper, byteOrder);
  
  EXPECT_EQ(memIo.size(), written);
}

// Test write with little endian byte order
TEST_F(Olympus2MnHeaderTest_1446, WriteWithLittleEndian_1446) {
  Olympus2MnHeader header;
  
  MemIo memIo;
  IoWrapper ioWrapper(memIo, nullptr, 0, nullptr);
  
  size_t result = header.write(ioWrapper, littleEndian);
  
  EXPECT_EQ(result, header.sizeOfSignature());
  EXPECT_EQ(memIo.size(), header.sizeOfSignature());
}

// Test write with big endian byte order
TEST_F(Olympus2MnHeaderTest_1446, WriteWithBigEndian_1446) {
  Olympus2MnHeader header;
  
  MemIo memIo;
  IoWrapper ioWrapper(memIo, nullptr, 0, nullptr);
  
  size_t result = header.write(ioWrapper, bigEndian);
  
  EXPECT_EQ(result, header.sizeOfSignature());
  EXPECT_EQ(memIo.size(), header.sizeOfSignature());
}

// Test that write is consistent - calling it produces the same result each time
TEST_F(Olympus2MnHeaderTest_1446, WriteIsConsistent_1446) {
  Olympus2MnHeader header;
  
  MemIo memIo1;
  IoWrapper ioWrapper1(memIo1, nullptr, 0, nullptr);
  size_t result1 = header.write(ioWrapper1, littleEndian);
  
  MemIo memIo2;
  IoWrapper ioWrapper2(memIo2, nullptr, 0, nullptr);
  size_t result2 = header.write(ioWrapper2, littleEndian);
  
  EXPECT_EQ(result1, result2);
  EXPECT_EQ(memIo1.size(), memIo2.size());
  
  // Read back and compare
  if (memIo1.size() == memIo2.size() && memIo1.size() > 0) {
    memIo1.seek(0, BasicIo::beg);
    memIo2.seek(0, BasicIo::beg);
    
    std::vector<byte> data1(memIo1.size());
    std::vector<byte> data2(memIo2.size());
    
    memIo1.read(data1.data(), data1.size());
    memIo2.read(data2.data(), data2.size());
    
    EXPECT_EQ(data1, data2);
  }
}

// Test that byte order does not affect the written signature
// (since the signature is written as-is, byte order parameter may be unused)
TEST_F(Olympus2MnHeaderTest_1446, ByteOrderDoesNotAffectSignature_1446) {
  Olympus2MnHeader header;
  
  MemIo memIoLE;
  IoWrapper ioWrapperLE(memIoLE, nullptr, 0, nullptr);
  header.write(ioWrapperLE, littleEndian);
  
  MemIo memIoBE;
  IoWrapper ioWrapperBE(memIoBE, nullptr, 0, nullptr);
  header.write(ioWrapperBE, bigEndian);
  
  EXPECT_EQ(memIoLE.size(), memIoBE.size());
  
  if (memIoLE.size() == memIoBE.size() && memIoLE.size() > 0) {
    memIoLE.seek(0, BasicIo::beg);
    memIoBE.seek(0, BasicIo::beg);
    
    std::vector<byte> dataLE(memIoLE.size());
    std::vector<byte> dataBE(memIoBE.size());
    
    memIoLE.read(dataLE.data(), dataLE.size());
    memIoBE.read(dataBE.data(), dataBE.size());
    
    EXPECT_EQ(dataLE, dataBE);
  }
}

// Test that the read method can recognize the written signature
TEST_F(Olympus2MnHeaderTest_1446, ReadRecognizesWrittenSignature_1446) {
  Olympus2MnHeader headerWrite;
  
  MemIo memIo;
  IoWrapper ioWrapper(memIo, nullptr, 0, nullptr);
  headerWrite.write(ioWrapper, littleEndian);
  
  // Now try to read it back
  Olympus2MnHeader headerRead;
  memIo.seek(0, BasicIo::beg);
  
  std::vector<byte> data(memIo.size());
  memIo.read(data.data(), data.size());
  
  bool readResult = headerRead.read(data.data(), static_cast<uint32_t>(data.size()));
  EXPECT_TRUE(readResult);
}

// Test that read fails with empty data
TEST_F(Olympus2MnHeaderTest_1446, ReadFailsWithEmptyData_1446) {
  Olympus2MnHeader header;
  
  bool result = header.read(nullptr, 0);
  EXPECT_FALSE(result);
}

// Test that read fails with insufficient data
TEST_F(Olympus2MnHeaderTest_1446, ReadFailsWithInsufficientData_1446) {
  Olympus2MnHeader header;
  
  // Provide a small buffer that's too short for the signature
  byte smallBuf[1] = {0};
  bool result = header.read(smallBuf, 1);
  EXPECT_FALSE(result);
}
