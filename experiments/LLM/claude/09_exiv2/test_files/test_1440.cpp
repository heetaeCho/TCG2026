#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include necessary headers from exiv2
#include <exiv2/exiv2.hpp>

// Internal headers needed for the class under test
// We need to access Internal namespace components
#include "makernote_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;
using namespace testing;

// We need to create a mock or minimal IoWrapper for testing
// IoWrapper wraps a BasicIo and provides write functionality

class OlympusMnHeaderTest_1440 : public ::testing::Test {
 protected:
  void SetUp() override {
  }

  void TearDown() override {
  }
};

// Test that OlympusMnHeader can be default constructed
TEST_F(OlympusMnHeaderTest_1440, DefaultConstruction_1440) {
  EXPECT_NO_THROW({
    OlympusMnHeader header;
  });
}

// Test that sizeOfSignature returns a non-zero value
TEST_F(OlympusMnHeaderTest_1440, SizeOfSignatureNonZero_1440) {
  OlympusMnHeader header;
  EXPECT_GT(header.sizeOfSignature(), 0u);
}

// Test that write returns sizeOfSignature
TEST_F(OlympusMnHeaderTest_1440, WriteReturnsSizeOfSignature_1440) {
  OlympusMnHeader header;
  
  // Create a MemIo to capture written data
  auto memIo = std::make_unique<Exiv2::MemIo>();
  
  // We need an IoWrapper - it typically wraps a BasicIo
  // IoWrapper constructor takes (BasicIo&, ...) 
  IoWrapper ioWrapper(*memIo, nullptr, 0, nullptr);
  
  size_t result = header.write(ioWrapper, Exiv2::bigEndian);
  EXPECT_EQ(result, header.sizeOfSignature());
}

// Test that write with littleEndian also returns sizeOfSignature
TEST_F(OlympusMnHeaderTest_1440, WriteWithLittleEndianReturnsSizeOfSignature_1440) {
  OlympusMnHeader header;
  
  auto memIo = std::make_unique<Exiv2::MemIo>();
  IoWrapper ioWrapper(*memIo, nullptr, 0, nullptr);
  
  size_t result = header.write(ioWrapper, Exiv2::littleEndian);
  EXPECT_EQ(result, header.sizeOfSignature());
}

// Test that write actually writes data (the MemIo should have data after write)
TEST_F(OlympusMnHeaderTest_1440, WriteActuallyWritesData_1440) {
  OlympusMnHeader header;
  
  auto memIo = std::make_unique<Exiv2::MemIo>();
  IoWrapper ioWrapper(*memIo, nullptr, 0, nullptr);
  
  size_t written = header.write(ioWrapper, Exiv2::bigEndian);
  
  // The memory IO should have received exactly sizeOfSignature bytes
  EXPECT_EQ(written, header.sizeOfSignature());
  EXPECT_GE(memIo->size(), header.sizeOfSignature());
}

// Test that write is consistent - calling it multiple times returns same value
TEST_F(OlympusMnHeaderTest_1440, WriteConsistentReturnValue_1440) {
  OlympusMnHeader header;
  
  auto memIo1 = std::make_unique<Exiv2::MemIo>();
  IoWrapper ioWrapper1(*memIo1, nullptr, 0, nullptr);
  size_t result1 = header.write(ioWrapper1, Exiv2::bigEndian);
  
  auto memIo2 = std::make_unique<Exiv2::MemIo>();
  IoWrapper ioWrapper2(*memIo2, nullptr, 0, nullptr);
  size_t result2 = header.write(ioWrapper2, Exiv2::bigEndian);
  
  EXPECT_EQ(result1, result2);
}

// Test that the Olympus signature is "OLYMP" followed by additional bytes
// The Olympus makernote signature is known to start with "OLYMP"
TEST_F(OlympusMnHeaderTest_1440, SignatureContentCheck_1440) {
  OlympusMnHeader header;
  
  auto memIo = std::make_unique<Exiv2::MemIo>();
  IoWrapper ioWrapper(*memIo, nullptr, 0, nullptr);
  
  header.write(ioWrapper, Exiv2::bigEndian);
  
  // Read back what was written
  if (memIo->size() >= 5) {
    memIo->seek(0, Exiv2::BasicIo::beg);
    Exiv2::byte buf[10] = {};
    size_t toRead = std::min(static_cast<size_t>(memIo->size()), sizeof(buf));
    memIo->read(buf, toRead);
    
    // Olympus MakerNote signature starts with "OLYMP"
    EXPECT_EQ(buf[0], 'O');
    EXPECT_EQ(buf[1], 'L');
    EXPECT_EQ(buf[2], 'Y');
    EXPECT_EQ(buf[3], 'M');
    EXPECT_EQ(buf[4], 'P');
  }
}

// Test that ByteOrder parameter doesn't affect the return value
TEST_F(OlympusMnHeaderTest_1440, ByteOrderDoesNotAffectReturnValue_1440) {
  OlympusMnHeader header;
  
  auto memIo1 = std::make_unique<Exiv2::MemIo>();
  IoWrapper ioWrapper1(*memIo1, nullptr, 0, nullptr);
  size_t bigEndianResult = header.write(ioWrapper1, Exiv2::bigEndian);
  
  auto memIo2 = std::make_unique<Exiv2::MemIo>();
  IoWrapper ioWrapper2(*memIo2, nullptr, 0, nullptr);
  size_t littleEndianResult = header.write(ioWrapper2, Exiv2::littleEndian);
  
  EXPECT_EQ(bigEndianResult, littleEndianResult);
}
