// File: port/accelerated_crc32c_test_43.cc
#include "port/port_stdcxx.h"

#include <gtest/gtest.h>
#include <cstdint>
#include <cstring>

#if HAVE_CRC32C
// If the build enables CRC32C, include the header so we can compute the oracle
// value using the same external collaborator the function delegates to.
#include <crc32c/crc32c.h>
#endif

namespace {

using leveldb::port::AcceleratedCRC32C;

class PortAcceleratedCRC32CTest_43 : public ::testing::Test {};

// Normal operation with a typical buffer.
TEST_F(PortAcceleratedCRC32CTest_43, ComputesCrcForSmallBuffer_43) {
  const char* data = "abc";
  const uint32_t seed = 0;

#if HAVE_CRC32C
  uint32_t expected = ::crc32c::Extend(seed,
                                       reinterpret_cast<const uint8_t*>(data),
                                       3);
  EXPECT_EQ(expected, AcceleratedCRC32C(seed, data, 3));
#else
  // When CRC32C is not available, the function must ignore inputs and return 0.
  EXPECT_EQ(0u, AcceleratedCRC32C(seed, data, 3));
#endif
}

// Boundary: empty input (size 0). Buf may be nullptr safely when size==0.
TEST_F(PortAcceleratedCRC32CTest_43, EmptyInputReturnsConsistentResult_43) {
  const uint32_t seed = 12345;

#if HAVE_CRC32C
  uint32_t expected = ::crc32c::Extend(seed, nullptr, 0);
  EXPECT_EQ(expected, AcceleratedCRC32C(seed, nullptr, 0));
#else
  EXPECT_EQ(0u, AcceleratedCRC32C(seed, nullptr, 0));
#endif
}

// Boundary: non-zero seed with non-empty buffer.
TEST_F(PortAcceleratedCRC32CTest_43, RespectsSeedValue_43) {
  const char* data = "LevelDB";
  const size_t n = std::strlen(data);
  const uint32_t seed = 0xDEADBEEF;

#if HAVE_CRC32C
  uint32_t expected = ::crc32c::Extend(seed,
                                       reinterpret_cast<const uint8_t*>(data),
                                       n);
  EXPECT_EQ(expected, AcceleratedCRC32C(seed, data, n));
#else
  EXPECT_EQ(0u, AcceleratedCRC32C(seed, data, n));
#endif
}

// Observability: deterministic for same inputs.
TEST_F(PortAcceleratedCRC32CTest_43, DeterministicForSameInputs_43) {
  const char* data = "repeatable";
  const size_t n = std::strlen(data);
  const uint32_t seed = 42;

  uint32_t a = AcceleratedCRC32C(seed, data, n);
  uint32_t b = AcceleratedCRC32C(seed, data, n);
  EXPECT_EQ(a, b);
}

// Error/edge handling: large size with valid pointer (no crash, consistent).
TEST_F(PortAcceleratedCRC32CTest_43, LargeInputSlice_43) {
  // Use a modest buffer to avoid heavy runtime while still non-trivial.
  std::string payload(1 << 12, 'x');  // 4096 bytes of 'x'
  const uint32_t seed = 7;

#if HAVE_CRC32C
  uint32_t expected = ::crc32c::Extend(
      seed, reinterpret_cast<const uint8_t*>(payload.data()), payload.size());
  EXPECT_EQ(expected,
            AcceleratedCRC32C(seed, payload.data(), payload.size()));
#else
  EXPECT_EQ(0u, AcceleratedCRC32C(seed, payload.data(), payload.size()));
#endif
}

}  // namespace
