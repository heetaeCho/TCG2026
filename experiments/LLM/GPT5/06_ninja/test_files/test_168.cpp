// File: ./TestProjects/ninja/misc/manifest_fuzzer_test.cc

#include <gtest/gtest.h>

#include <cstdint>
#include <filesystem>
#include <fstream>
#include <system_error>
#include <vector>

// Forward declaration of the function under test.
// Implementation is provided by ./misc/manifest_fuzzer.cc.
int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size);

class ManifestFuzzerTest_168 : public ::testing::Test {
protected:
  const std::filesystem::path build_file_{"/tmp/build.ninja"};

  void SetUp() override {
    // Ensure a clean state before each test.
    std::error_code ec;
    std::filesystem::remove_all(build_file_, ec);
  }

  void TearDown() override {
    // Clean up any leftover file after each test.
    std::error_code ec;
    std::filesystem::remove_all(build_file_, ec);
  }

  bool FileExists() const {
    std::error_code ec;
    return std::filesystem::exists(build_file_, ec);
  }
};

// Normal operation: empty input should be handled gracefully.
// Verifies that the function returns 0 and the build file is removed.
TEST_F(ManifestFuzzerTest_168, EmptyInput_ReturnsZeroAndCleansUp_168) {
  uint8_t dummy = 0;  // Non-null pointer, even though size is 0.

  int result = LLVMFuzzerTestOneInput(&dummy, 0);

  EXPECT_EQ(0, result);
  EXPECT_FALSE(FileExists());
}

// Normal operation: simple textual ninja-like manifest.
// We don't assert anything about parsing itself, only return value and cleanup.
TEST_F(ManifestFuzzerTest_168, SimpleManifest_ReturnsZeroAndCleansUp_168) {
  const char kManifest[] =
      "rule r\n"
      "  command = echo hi\n"
      "build out: r in\n";
  const uint8_t* data =
      reinterpret_cast<const uint8_t*>(kManifest);
  size_t size = sizeof(kManifest) - 1;  // exclude terminating '\0'

  int result = LLVMFuzzerTestOneInput(data, size);

  EXPECT_EQ(0, result);
  EXPECT_FALSE(FileExists());
}

// Boundary / stress-ish case: larger binary-like input.
// Ensures the function handles arbitrary data and still cleans up.
TEST_F(ManifestFuzzerTest_168, BinaryData_ReturnsZeroAndCleansUp_168) {
  std::vector<uint8_t> data(1024);
  for (size_t i = 0; i < data.size(); ++i) {
    data[i] = static_cast<uint8_t>(i & 0xFF);
  }

  int result = LLVMFuzzerTestOneInput(data.data(), data.size());

  EXPECT_EQ(0, result);
  EXPECT_FALSE(FileExists());
}

// Exceptional / edge observable case:
// If a build file already exists, it should be removed by the fuzzer entry.
// We pre-create /tmp/build.ninja and verify it is gone after the call.
TEST_F(ManifestFuzzerTest_168, PreExistingFile_IsRemovedAfterCall_168) {
  // Pre-create /tmp/build.ninja with some content.
  {
    std::ofstream ofs(build_file_);
    ASSERT_TRUE(ofs.is_open());
    ofs << "pre-existing content\n";
  }

  ASSERT_TRUE(FileExists());

  const char kData[] = "dummy";
  const uint8_t* data =
      reinterpret_cast<const uint8_t*>(kData);
  size_t size = sizeof(kData) - 1;

  int result = LLVMFuzzerTestOneInput(data, size);

  EXPECT_EQ(0, result);
  EXPECT_FALSE(FileExists());
}

// Additional behavior check: multiple consecutive calls should each clean up
// after themselves and consistently return 0.
TEST_F(ManifestFuzzerTest_168, MultipleCalls_RemainIdempotentAndClean_168) {
  const char kData1[] = "first input";
  const char kData2[] = "second input with more stuff";

  const uint8_t* data1 =
      reinterpret_cast<const uint8_t*>(kData1);
  const uint8_t* data2 =
      reinterpret_cast<const uint8_t*>(kData2);

  int result1 = LLVMFuzzerTestOneInput(data1, sizeof(kData1) - 1);
  EXPECT_EQ(0, result1);
  EXPECT_FALSE(FileExists());

  int result2 = LLVMFuzzerTestOneInput(data2, sizeof(kData2) - 1);
  EXPECT_EQ(0, result2);
  EXPECT_FALSE(FileExists());
}
