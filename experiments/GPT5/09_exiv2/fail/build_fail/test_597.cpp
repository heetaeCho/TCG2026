// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_xpathio_writeDataToFile_597.cpp

#include <gtest/gtest.h>

#include <exiv2/basicio.hpp>

#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

namespace fs = std::filesystem;

namespace {

// Simple RAII cleanup helper for files created during a test.
class ScopedFileRemover {
 public:
  explicit ScopedFileRemover(std::string p) : path_(std::move(p)) {}
  ScopedFileRemover(const ScopedFileRemover&) = delete;
  ScopedFileRemover& operator=(const ScopedFileRemover&) = delete;
  ~ScopedFileRemover() {
    if (!path_.empty()) {
      std::error_code ec;
      fs::remove(fs::path(path_), ec);
    }
  }

  const std::string& path() const { return path_; }

 private:
  std::string path_;
};

static std::string ReadAllBytes(const std::string& path) {
  std::ifstream ifs(path, std::ios::binary);
  if (!ifs.is_open()) return {};
  std::string data;
  ifs.seekg(0, std::ios::end);
  std::streamoff sz = ifs.tellg();
  if (sz < 0) return {};
  data.resize(static_cast<size_t>(sz));
  ifs.seekg(0, std::ios::beg);
  if (!data.empty()) {
    ifs.read(&data[0], static_cast<std::streamsize>(data.size()));
  }
  return data;
}

// Detection helpers to avoid hard-coding Error API details.
template <typename T>
class HasCode {
  template <typename U>
  static auto test(int) -> decltype(std::declval<const U&>().code(), std::true_type{});
  template <typename>
  static std::false_type test(...);

 public:
  static constexpr bool value = decltype(test<T>(0))::value;
};

}  // namespace

class XPathIoWriteDataToFileTest_597 : public ::testing::Test {};

// Normal operation: data: URI with base64 payload creates a temp file containing decoded bytes.
TEST_F(XPathIoWriteDataToFileTest_597, DataUriBase64WritesDecodedContent_597) {
  // "Hello, Exiv2!" base64 => "SGVsbG8sIEV4aXYyIQ=="
  const std::string orgPath = "data:application/octet-stream;base64,SGVsbG8sIEV4aXYyIQ==";

  const std::string outPath = Exiv2::XPathIo::writeDataToFile(orgPath);
  ASSERT_FALSE(outPath.empty());

  ScopedFileRemover cleanup(outPath);

  EXPECT_TRUE(fs::exists(fs::path(outPath)));

  const std::string fileBytes = ReadAllBytes(outPath);
  EXPECT_EQ(fileBytes, "Hello, Exiv2!");
}

// Exceptional/error case: data: URI missing "base64," marker should throw.
TEST_F(XPathIoWriteDataToFileTest_597, DataUriMissingBase64MarkerThrows_597) {
  // Intentionally no "base64," substring.
  const std::string orgPath = "data:text/plain,SGVsbG8=";

  try {
    (void)Exiv2::XPathIo::writeDataToFile(orgPath);
    FAIL() << "Expected Exiv2::Error to be thrown";
  } catch (const Exiv2::Error& e) {
    // If Error exposes code(), verify it is kerErrorMessage; otherwise just accept the exception.
    if constexpr (HasCode<Exiv2::Error>::value) {
      EXPECT_EQ(e.code(), Exiv2::ErrorCode::kerErrorMessage);
    }
    // Message content is observable via what(); keep it permissive (substring).
    EXPECT_NE(std::string(e.what()).find("base64"), std::string::npos);
  }
}

// Boundary + exceptional case: empty base64 payload should fail to decode and throw.
TEST_F(XPathIoWriteDataToFileTest_597, DataUriEmptyBase64DataThrows_597) {
  const std::string orgPath = "data:application/octet-stream;base64,";

  try {
    (void)Exiv2::XPathIo::writeDataToFile(orgPath);
    FAIL() << "Expected Exiv2::Error to be thrown";
  } catch (const Exiv2::Error& e) {
    if constexpr (HasCode<Exiv2::Error>::value) {
      EXPECT_EQ(e.code(), Exiv2::ErrorCode::kerErrorMessage);
    }
    EXPECT_NE(std::string(e.what()).find("base 64"), std::string::npos);
  }
}