// File: crc32c_can_accelerate_test.cc

#include <gtest/gtest.h>
#include <cstdint>
#include <string>

// ---- Test double for the external collaborator ----
// We provide a test-only definition of leveldb::port::AcceleratedCRC32C
// so that the function in util/crc32c.cc links against this double.
namespace testdouble {
enum class Mode { kReturnMatch, kReturnMismatch };
static Mode g_mode = Mode::kReturnMatch;

// Capture last call to verify external interaction.
static uint32_t last_crc = 0;
static std::string last_buf;
static size_t last_size = 0;

// The magic value expected by util/crc32c.cc.
static constexpr uint32_t kExpectedCRC = 0xdcbc59fa;
}  // namespace testdouble

namespace leveldb {
namespace port {
uint32_t AcceleratedCRC32C(uint32_t crc, const char* buf, size_t size) {
  using namespace testdouble;
  last_crc = crc;
  last_buf.assign(buf, size);
  last_size = size;
  return (g_mode == Mode::kReturnMatch) ? kExpectedCRC : 0u;
}
}  // namespace port
}  // namespace leveldb

// ---- Include the .cc under test so the internal 'static' symbol is visible ----
#include "util/crc32c.cc"

// ---- Tests ----

class Crc32cCanAccelerateTest_454 : public ::testing::Test {
protected:
  void SetUp() override {
    // Reset captured interaction state before each test.
    testdouble::g_mode = testdouble::Mode::kReturnMatch;
    testdouble::last_crc = 0xDEADBEEF;
    testdouble::last_buf.clear();
    testdouble::last_size = 9999;
  }
};

// Normal case: when the accelerated function returns the expected CRC, we should get true.
// Also validate the external interaction parameters (crc seed, buffer content and size).
TEST_F(Crc32cCanAccelerateTest_454, ReturnsTrueAndCallsAcceleratedWithExpectedArgs_454) {
  using leveldb::crc32c::CanAccelerateCRC32C;
  testdouble::g_mode = testdouble::Mode::kReturnMatch;

  const bool can = CanAccelerateCRC32C();
  EXPECT_TRUE(can);

  // Verify the call parameters to the external collaborator.
  EXPECT_EQ(0u, testdouble::last_crc) << "Initial CRC seed should be 0";

  // The implementation passes a literal "TestCRCBuffer" with length excluding the null terminator.
  const std::string expected_buf = "TestCRCBuffer";
  EXPECT_EQ(expected_buf, testdouble::last_buf);
  EXPECT_EQ(expected_buf.size(), testdouble::last_size);
}

// Error/negative path: when the accelerated function DOES NOT return the expected CRC, we should get false.
// Still verify the external interaction parameters are as expected.
TEST_F(Crc32cCanAccelerateTest_454, ReturnsFalseWhenAcceleratedResultDiffers_454) {
  using leveldb::crc32c::CanAccelerateCRC32C;
  testdouble::g_mode = testdouble::Mode::kReturnMismatch;

  const bool can = CanAccelerateCRC32C();
  EXPECT_FALSE(can);

  // External interaction verification remains the same.
  EXPECT_EQ(0u, testdouble::last_crc);

  const std::string expected_buf = "TestCRCBuffer";
  EXPECT_EQ(expected_buf, testdouble::last_buf);
  EXPECT_EQ(expected_buf.size(), testdouble::last_size);
}
