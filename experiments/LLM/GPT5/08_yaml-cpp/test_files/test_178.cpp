// TEST_ID: 178
// File: test_stream_readbuffer_178.cpp

#include <gtest/gtest.h>
#include <cstdint>
#include <type_traits>

// NOTE:
// The function under test is defined as an inline function inside a .cpp file in the provided snippet.
// To ensure the definition is visible to this test translation unit (and avoid link issues),
// we include the implementation file directly.
#include "TestProjects/yaml-cpp/src/stream.cpp"

namespace {

class ReadBufferTest_178 : public ::testing::Test {};

TEST_F(ReadBufferTest_178, NullptrReturnsNullptr_178) {
  unsigned char* in = nullptr;
  char* out = YAML::ReadBuffer(in);
  EXPECT_EQ(out, nullptr);
}

TEST_F(ReadBufferTest_178, NonNullptrPreservesAddress_178) {
  alignas(16) unsigned char buf[8] = {0};

  unsigned char* in = &buf[0];
  char* out = YAML::ReadBuffer(in);

  // Observable behavior: returned pointer should refer to the same address.
  EXPECT_EQ(reinterpret_cast<void*>(out), reinterpret_cast<void*>(in));
}

TEST_F(ReadBufferTest_178, ReturnedPointerCanBeUsedToModifyUnderlyingBytes_178) {
  unsigned char buf[4] = {0x00, 0x01, 0x7F, 0xFF};

  char* out = YAML::ReadBuffer(buf);
  ASSERT_NE(out, nullptr);

  // Modify via returned char* and verify the underlying unsigned char buffer observes the change.
  out[1] = static_cast<char>(0x22);
  EXPECT_EQ(buf[1], static_cast<unsigned char>(0x22));
}

TEST_F(ReadBufferTest_178, ReturnedTypeIsCharPointer_178) {
  // Compile-time check of the signature's observable contract.
  static_assert(std::is_same_v<decltype(YAML::ReadBuffer(static_cast<unsigned char*>(nullptr))), char*>);
  SUCCEED();
}

}  // namespace