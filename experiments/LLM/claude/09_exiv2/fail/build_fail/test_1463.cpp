#include <gtest/gtest.h>
#include <cstring>
#include <vector>

// We need to include the necessary headers from exiv2
#include "makernote_int.hpp"
#include "types.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class Nikon2MnHeaderTest_1463 : public ::testing::Test {
 protected:
  Nikon2MnHeader header_;
  
  // The known Nikon2 signature is "Nikon\0" (6 bytes)
  // Based on the code: memcmp(pData, signature_, 6)
  static constexpr byte validSignature_[6] = {'N', 'i', 'k', 'o', 'n', '\0'};
};

constexpr byte Nikon2MnHeaderTest_1463::validSignature_[6];

// Test: read returns false when pData is nullptr
TEST_F(Nikon2MnHeaderTest_1463, ReadNullPointerReturnsFalse_1463) {
  bool result = header_.read(nullptr, 100, littleEndian);
  EXPECT_FALSE(result);
}

// Test: read returns false when size is 0
TEST_F(Nikon2MnHeaderTest_1463, ReadZeroSizeReturnsFalse_1463) {
  byte data[6] = {'N', 'i', 'k', 'o', 'n', '\0'};
  bool result = header_.read(data, 0, littleEndian);
  EXPECT_FALSE(result);
}

// Test: read returns false when size is less than signature size (less than 6)
TEST_F(Nikon2MnHeaderTest_1463, ReadSizeTooSmallReturnsFalse_1463) {
  byte data[5] = {'N', 'i', 'k', 'o', 'n'};
  bool result = header_.read(data, 5, littleEndian);
  EXPECT_FALSE(result);
}

// Test: read returns false when size is 1
TEST_F(Nikon2MnHeaderTest_1463, ReadSizeOneReturnsFalse_1463) {
  byte data[1] = {'N'};
  bool result = header_.read(data, 1, littleEndian);
  EXPECT_FALSE(result);
}

// Test: read returns false when signature doesn't match
TEST_F(Nikon2MnHeaderTest_1463, ReadInvalidSignatureReturnsFalse_1463) {
  byte data[6] = {'C', 'a', 'n', 'o', 'n', '\0'};
  bool result = header_.read(data, 6, littleEndian);
  EXPECT_FALSE(result);
}

// Test: read returns false when signature is partially correct
TEST_F(Nikon2MnHeaderTest_1463, ReadPartiallyCorrectSignatureReturnsFalse_1463) {
  byte data[6] = {'N', 'i', 'k', 'o', 'n', 'X'};  // last byte differs
  bool result = header_.read(data, 6, littleEndian);
  EXPECT_FALSE(result);
}

// Test: read returns true with valid signature and exact minimum size
TEST_F(Nikon2MnHeaderTest_1463, ReadValidSignatureExactSizeReturnsTrue_1463) {
  byte data[6] = {'N', 'i', 'k', 'o', 'n', '\0'};
  bool result = header_.read(data, 6, littleEndian);
  EXPECT_TRUE(result);
}

// Test: read returns true with valid signature and larger buffer
TEST_F(Nikon2MnHeaderTest_1463, ReadValidSignatureLargerBufferReturnsTrue_1463) {
  byte data[100];
  std::memset(data, 0, sizeof(data));
  std::memcpy(data, validSignature_, 6);
  bool result = header_.read(data, 100, littleEndian);
  EXPECT_TRUE(result);
}

// Test: read works with bigEndian byte order
TEST_F(Nikon2MnHeaderTest_1463, ReadValidSignatureBigEndianReturnsTrue_1463) {
  byte data[6] = {'N', 'i', 'k', 'o', 'n', '\0'};
  bool result = header_.read(data, 6, bigEndian);
  EXPECT_TRUE(result);
}

// Test: read with all zeros in data returns false
TEST_F(Nikon2MnHeaderTest_1463, ReadAllZerosReturnsFalse_1463) {
  byte data[6] = {0, 0, 0, 0, 0, 0};
  bool result = header_.read(data, 6, littleEndian);
  EXPECT_FALSE(result);
}

// Test: read with all 0xFF in data returns false
TEST_F(Nikon2MnHeaderTest_1463, ReadAllFFReturnsFalse_1463) {
  byte data[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
  bool result = header_.read(data, 6, littleEndian);
  EXPECT_FALSE(result);
}

// Test: After successful read, start() returns sizeOfSignature()
TEST_F(Nikon2MnHeaderTest_1463, StartReturnsSizeOfSignatureAfterRead_1463) {
  byte data[6] = {'N', 'i', 'k', 'o', 'n', '\0'};
  ASSERT_TRUE(header_.read(data, 6, littleEndian));
  EXPECT_EQ(header_.start(), header_.sizeOfSignature());
}

// Test: sizeOfSignature returns expected value (6)
TEST_F(Nikon2MnHeaderTest_1463, SizeOfSignatureReturnsExpectedValue_1463) {
  EXPECT_EQ(header_.sizeOfSignature(), 6u);
}

// Test: read can be called multiple times - successful after failure
TEST_F(Nikon2MnHeaderTest_1463, ReadMultipleTimesRecoverable_1463) {
  byte badData[6] = {'X', 'X', 'X', 'X', 'X', 'X'};
  EXPECT_FALSE(header_.read(badData, 6, littleEndian));
  
  byte goodData[6] = {'N', 'i', 'k', 'o', 'n', '\0'};
  EXPECT_TRUE(header_.read(goodData, 6, littleEndian));
}

// Test: read can be called successfully twice
TEST_F(Nikon2MnHeaderTest_1463, ReadCanBeCalledTwiceSuccessfully_1463) {
  byte data[6] = {'N', 'i', 'k', 'o', 'n', '\0'};
  EXPECT_TRUE(header_.read(data, 6, littleEndian));
  EXPECT_TRUE(header_.read(data, 6, littleEndian));
}

// Test: read with lowercase 'nikon' returns false 
TEST_F(Nikon2MnHeaderTest_1463, ReadLowercaseNikonReturnsFalse_1463) {
  byte data[6] = {'n', 'i', 'k', 'o', 'n', '\0'};
  bool result = header_.read(data, 6, littleEndian);
  EXPECT_FALSE(result);
}

// Test: Boundary - size exactly at signature size minus 1
TEST_F(Nikon2MnHeaderTest_1463, ReadSizeExactlyOneBelow_1463) {
  byte data[6] = {'N', 'i', 'k', 'o', 'n', '\0'};
  // sizeOfSignature() - 1 = 5
  bool result = header_.read(data, header_.sizeOfSignature() - 1, littleEndian);
  EXPECT_FALSE(result);
}

// Test: Boundary - size exactly at signature size
TEST_F(Nikon2MnHeaderTest_1463, ReadSizeExactlyAtSignature_1463) {
  byte data[6] = {'N', 'i', 'k', 'o', 'n', '\0'};
  bool result = header_.read(data, header_.sizeOfSignature(), littleEndian);
  EXPECT_TRUE(result);
}

// Test: Boundary - size exactly at signature size + 1
TEST_F(Nikon2MnHeaderTest_1463, ReadSizeOneAboveSignature_1463) {
  byte data[7] = {'N', 'i', 'k', 'o', 'n', '\0', 0x42};
  bool result = header_.read(data, header_.sizeOfSignature() + 1, littleEndian);
  EXPECT_TRUE(result);
}
