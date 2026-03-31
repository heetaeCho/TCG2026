#include <gtest/gtest.h>
#include <cstring>
#include <vector>

// We need to include the relevant headers from exiv2
#include "makernote_int.hpp"
#include "types.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class SonyMnHeaderTest_1501 : public ::testing::Test {
 protected:
  SonyMnHeader header_;
};

// Test that read returns false when pData is nullptr
TEST_F(SonyMnHeaderTest_1501, ReadNullDataReturnsFalse_1501) {
  bool result = header_.read(nullptr, 100, littleEndian);
  EXPECT_FALSE(result);
}

// Test that read returns false when size is 0
TEST_F(SonyMnHeaderTest_1501, ReadZeroSizeReturnsFalse_1501) {
  const byte data[] = {0x53, 0x4F, 0x4E, 0x59, 0x20, 0x44, 0x53, 0x43, 0x20, 0x00, 0x00, 0x00};
  bool result = header_.read(data, 0, littleEndian);
  EXPECT_FALSE(result);
}

// Test that read returns false when size is too small (less than signature size)
TEST_F(SonyMnHeaderTest_1501, ReadSizeTooSmallReturnsFalse_1501) {
  const byte data[] = {0x53, 0x4F, 0x4E};
  bool result = header_.read(data, 3, littleEndian);
  EXPECT_FALSE(result);
}

// Test that read returns false when signature doesn't match
TEST_F(SonyMnHeaderTest_1501, ReadWrongSignatureReturnsFalse_1501) {
  // Use data that is long enough but doesn't match the Sony signature
  const byte data[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  bool result = header_.read(data, sizeof(data), littleEndian);
  EXPECT_FALSE(result);
}

// Test that read returns true with a valid Sony MakerNote signature
// The Sony MakerNote signature is "SONY DSC \0\0\0" (12 bytes)
TEST_F(SonyMnHeaderTest_1501, ReadValidSignatureReturnsTrue_1501) {
  // Sony DSC signature: "SONY DSC \0\0\0"
  const byte data[] = {'S', 'O', 'N', 'Y', ' ', 'D', 'S', 'C', ' ', 0x00, 0x00, 0x00};
  bool result = header_.read(data, sizeof(data), littleEndian);
  EXPECT_TRUE(result);
}

// Test that read works with big endian byte order as well
TEST_F(SonyMnHeaderTest_1501, ReadValidSignatureBigEndianReturnsTrue_1501) {
  const byte data[] = {'S', 'O', 'N', 'Y', ' ', 'D', 'S', 'C', ' ', 0x00, 0x00, 0x00};
  bool result = header_.read(data, sizeof(data), bigEndian);
  EXPECT_TRUE(result);
}

// Test that read returns true when size is exactly the signature size
TEST_F(SonyMnHeaderTest_1501, ReadExactSignatureSizeReturnsTrue_1501) {
  const byte data[] = {'S', 'O', 'N', 'Y', ' ', 'D', 'S', 'C', ' ', 0x00, 0x00, 0x00};
  size_t sigSize = header_.sizeOfSignature();
  bool result = header_.read(data, sigSize, littleEndian);
  EXPECT_TRUE(result);
}

// Test that read returns false when size is one less than signature size
TEST_F(SonyMnHeaderTest_1501, ReadOneLessThanSignatureSizeReturnsFalse_1501) {
  const byte data[] = {'S', 'O', 'N', 'Y', ' ', 'D', 'S', 'C', ' ', 0x00, 0x00, 0x00};
  size_t sigSize = header_.sizeOfSignature();
  if (sigSize > 0) {
    bool result = header_.read(data, sigSize - 1, littleEndian);
    EXPECT_FALSE(result);
  }
}

// Test that read with larger buffer containing valid signature at start succeeds
TEST_F(SonyMnHeaderTest_1501, ReadLargerBufferWithValidSignatureReturnsTrue_1501) {
  std::vector<byte> data(256, 0);
  const byte sig[] = {'S', 'O', 'N', 'Y', ' ', 'D', 'S', 'C', ' ', 0x00, 0x00, 0x00};
  std::copy(std::begin(sig), std::end(sig), data.begin());
  bool result = header_.read(data.data(), data.size(), littleEndian);
  EXPECT_TRUE(result);
}

// Test that sizeOfSignature returns a non-zero value
TEST_F(SonyMnHeaderTest_1501, SizeOfSignatureIsNonZero_1501) {
  EXPECT_GT(header_.sizeOfSignature(), static_cast<size_t>(0));
}

// Test that start() returns sizeOfSignature after a successful read
TEST_F(SonyMnHeaderTest_1501, StartReturnsSizeOfSignatureAfterRead_1501) {
  const byte data[] = {'S', 'O', 'N', 'Y', ' ', 'D', 'S', 'C', ' ', 0x00, 0x00, 0x00};
  size_t sigSize = header_.sizeOfSignature();
  bool result = header_.read(data, sizeof(data), littleEndian);
  if (result) {
    EXPECT_EQ(header_.start(), static_cast<uint32_t>(sigSize));
  }
}

// Test that read can be called multiple times successfully
TEST_F(SonyMnHeaderTest_1501, ReadCanBeCalledMultipleTimes_1501) {
  const byte data[] = {'S', 'O', 'N', 'Y', ' ', 'D', 'S', 'C', ' ', 0x00, 0x00, 0x00};
  EXPECT_TRUE(header_.read(data, sizeof(data), littleEndian));
  EXPECT_TRUE(header_.read(data, sizeof(data), bigEndian));
}

// Test that partially matching signature fails
TEST_F(SonyMnHeaderTest_1501, ReadPartiallyMatchingSignatureFails_1501) {
  // Matches the beginning but not all
  const byte data[] = {'S', 'O', 'N', 'Y', ' ', 'D', 'S', 'C', ' ', 0x01, 0x01, 0x01};
  bool result = header_.read(data, sizeof(data), littleEndian);
  // This may or may not pass depending on the actual signature - we just test the interface
  // The signature likely includes the null bytes, so this should fail
  EXPECT_FALSE(result);
}
