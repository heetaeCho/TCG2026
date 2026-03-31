#include <gtest/gtest.h>
#include <cstring>

// We need to include the namespace and function declaration
namespace YAML {
inline char* ReadBuffer(unsigned char* pBuffer) {
  return reinterpret_cast<char*>(pBuffer);
}
}

// Test fixture for ReadBuffer
class ReadBufferTest_178 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Normal operation: ReadBuffer returns a valid char pointer from unsigned char buffer
TEST_F(ReadBufferTest_178, ReturnsCharPointerFromUnsignedCharBuffer_178) {
  unsigned char buffer[] = {72, 101, 108, 108, 111};  // "Hello" in ASCII
  char* result = YAML::ReadBuffer(buffer);
  ASSERT_NE(result, nullptr);
  EXPECT_EQ(result[0], 'H');
  EXPECT_EQ(result[1], 'e');
  EXPECT_EQ(result[2], 'l');
  EXPECT_EQ(result[3], 'l');
  EXPECT_EQ(result[4], 'o');
}

// Normal operation: Verify the returned pointer points to the same memory address
TEST_F(ReadBufferTest_178, ReturnedPointerPointsToSameMemory_178) {
  unsigned char buffer[10] = {0};
  char* result = YAML::ReadBuffer(buffer);
  EXPECT_EQ(reinterpret_cast<void*>(result), reinterpret_cast<void*>(buffer));
}

// Normal operation: ReadBuffer with a string-like buffer
TEST_F(ReadBufferTest_178, WorksWithStringContent_178) {
  unsigned char buffer[] = "YAML content";
  char* result = YAML::ReadBuffer(buffer);
  EXPECT_STREQ(result, "YAML content");
}

// Boundary condition: ReadBuffer with a single byte buffer
TEST_F(ReadBufferTest_178, SingleByteBuffer_178) {
  unsigned char buffer[1] = {65};  // 'A'
  char* result = YAML::ReadBuffer(buffer);
  ASSERT_NE(result, nullptr);
  EXPECT_EQ(result[0], 'A');
}

// Boundary condition: ReadBuffer with null-terminated buffer
TEST_F(ReadBufferTest_178, NullTerminatedBuffer_178) {
  unsigned char buffer[] = {0};
  char* result = YAML::ReadBuffer(buffer);
  ASSERT_NE(result, nullptr);
  EXPECT_EQ(result[0], '\0');
}

// Boundary condition: ReadBuffer with nullptr
TEST_F(ReadBufferTest_178, NullPointerReturnsNull_178) {
  char* result = YAML::ReadBuffer(nullptr);
  EXPECT_EQ(result, nullptr);
}

// Normal operation: Modifying through returned pointer modifies original buffer
TEST_F(ReadBufferTest_178, ModificationThroughReturnedPointerAffectsOriginal_178) {
  unsigned char buffer[5] = {1, 2, 3, 4, 5};
  char* result = YAML::ReadBuffer(buffer);
  result[0] = 'X';
  EXPECT_EQ(buffer[0], static_cast<unsigned char>('X'));
}

// Normal operation: Buffer with high-value bytes (values > 127)
TEST_F(ReadBufferTest_178, HighValueBytes_178) {
  unsigned char buffer[3] = {128, 200, 255};
  char* result = YAML::ReadBuffer(buffer);
  ASSERT_NE(result, nullptr);
  // The pointer should still be valid and point to the same memory
  EXPECT_EQ(static_cast<unsigned char>(result[0]), 128);
  EXPECT_EQ(static_cast<unsigned char>(result[1]), 200);
  EXPECT_EQ(static_cast<unsigned char>(result[2]), 255);
}

// Normal operation: Large buffer
TEST_F(ReadBufferTest_178, LargeBuffer_178) {
  const size_t bufferSize = 4096;
  unsigned char buffer[bufferSize];
  for (size_t i = 0; i < bufferSize; ++i) {
    buffer[i] = static_cast<unsigned char>(i % 256);
  }
  char* result = YAML::ReadBuffer(buffer);
  ASSERT_NE(result, nullptr);
  for (size_t i = 0; i < bufferSize; ++i) {
    EXPECT_EQ(static_cast<unsigned char>(result[i]),
              static_cast<unsigned char>(i % 256))
        << "Mismatch at index " << i;
  }
}

// Normal operation: Buffer with all zeros
TEST_F(ReadBufferTest_178, AllZeroBuffer_178) {
  unsigned char buffer[10] = {0};
  char* result = YAML::ReadBuffer(buffer);
  ASSERT_NE(result, nullptr);
  for (int i = 0; i < 10; ++i) {
    EXPECT_EQ(result[i], '\0');
  }
}

// Verify that ReadBuffer is a pure reinterpret_cast (no copy)
TEST_F(ReadBufferTest_178, NoCopySemantics_178) {
  unsigned char buffer[4] = {10, 20, 30, 40};
  char* result = YAML::ReadBuffer(buffer);
  
  // Modify original buffer after getting the pointer
  buffer[2] = 99;
  
  // The change should be visible through the returned pointer
  EXPECT_EQ(static_cast<unsigned char>(result[2]), 99);
}
