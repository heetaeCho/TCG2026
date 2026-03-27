// TEST_ID: 1579
// File: test_rw2image_readmetadata_1579.cpp

#include <gtest/gtest.h>

#include <memory>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

#include "exiv2/basicio.hpp"
#include "exiv2/error.hpp"
#include "exiv2/rw2image.hpp"

namespace {

// --- Small detection helpers to (optionally) assert Exiv2::ErrorCode if API exists.
template <typename T, typename = void>
struct has_code_method : std::false_type {};
template <typename T>
struct has_code_method<T, std::void_t<decltype(std::declval<const T&>().code())>> : std::true_type {};

template <typename T, typename = void>
struct has_error_code_method : std::false_type {};
template <typename T>
struct has_error_code_method<T, std::void_t<decltype(std::declval<const T&>().errorCode())>> : std::true_type {};

template <typename Err>
void ExpectErrorCodeIfAvailable(const Err& e, Exiv2::ErrorCode expected) {
  if constexpr (has_code_method<Err>::value) {
    EXPECT_EQ(e.code(), expected);
  } else if constexpr (has_error_code_method<Err>::value) {
    EXPECT_EQ(e.errorCode(), expected);
  } else {
    // ErrorCode accessor not available in this build; we still validated the exception type.
    (void)e;
    (void)expected;
    SUCCEED();
  }
}

// A controllable BasicIo test double.
// This is NOT mocking internal behavior of Rw2Image; it's a fake external dependency.
class FakeBasicIo final : public Exiv2::BasicIo {
 public:
  explicit FakeBasicIo(std::string path = "fake.rw2") : path_(std::move(path)) {}

  // Controls
  int open_rc = 0;
  int close_rc = 0;
  int error_rc = 0;
  bool eof_flag = false;
  bool is_open_flag = false;

  // Observability
  int open_calls = 0;
  int close_calls = 0;

  // Backing data for mmap/size
  std::vector<Exiv2::byte> data;

  int open() override {
    ++open_calls;
    if (open_rc == 0) is_open_flag = true;
    return open_rc;
  }

  int close() override {
    ++close_calls;
    is_open_flag = false;
    return close_rc;
  }

  Exiv2::byte* mmap(bool /*isWriteable*/) override {
    // Returning nullptr is allowed if size()==0; callers should cope (implementation-defined).
    return data.empty() ? nullptr : data.data();
  }

  int munmap() override { return 0; }

  const size_t size() override { return data.size(); }

  const bool isopen() override { return is_open_flag; }

  const int error() override { return error_rc; }

  const bool eof() override { return eof_flag; }

  const std::string& path() override { return path_; }

  // Unused methods can keep base behavior; only override what the CUT uses.
 private:
  std::string path_;
};

class Rw2ImageReadMetadataTest_1579 : public ::testing::Test {
 protected:
  static std::unique_ptr<Exiv2::Rw2Image> MakeImage(std::unique_ptr<Exiv2::BasicIo> io) {
    return std::make_unique<Exiv2::Rw2Image>(std::move(io));
  }
};

}  // namespace

TEST_F(Rw2ImageReadMetadataTest_1579, OpenFailureThrowsErrorAndDoesNotClose_1579) {
  auto fake = std::make_unique<FakeBasicIo>("cannot_open.rw2");
  FakeBasicIo* fake_ptr = fake.get();
  fake->open_rc = 1;  // Non-zero => open failure

  auto img = MakeImage(std::move(fake));

  try {
    img->readMetadata();
    FAIL() << "Expected Exiv2::Error to be thrown";
  } catch (const Exiv2::Error& e) {
    // Observable: exception type and (if available) code.
    ExpectErrorCodeIfAvailable(e, Exiv2::ErrorCode::kerDataSourceOpenFailed);
  }

  EXPECT_EQ(fake_ptr->open_calls, 1);
  // In the provided implementation, IoCloser is created only after open succeeds.
  EXPECT_EQ(fake_ptr->close_calls, 0);
}

TEST_F(Rw2ImageReadMetadataTest_1579, NonRw2WithoutIoErrorThrowsNotAnImageAndCloses_1579) {
  auto fake = std::make_unique<FakeBasicIo>("not_rw2.bin");
  FakeBasicIo* fake_ptr = fake.get();
  fake->open_rc = 0;
  fake->error_rc = 0;
  fake->eof_flag = false;

  // Provide some bytes that should not match RW2 signature/type.
  fake->data = {0x00, 0x11, 0x22, 0x33, 0x44};

  auto img = MakeImage(std::move(fake));

  try {
    img->readMetadata();
    FAIL() << "Expected Exiv2::Error to be thrown";
  } catch (const Exiv2::Error& e) {
    ExpectErrorCodeIfAvailable(e, Exiv2::ErrorCode::kerNotAnImage);
  }

  EXPECT_EQ(fake_ptr->open_calls, 1);
  // IoCloser should close even when the function throws after opening.
  EXPECT_EQ(fake_ptr->close_calls, 1);
}

TEST_F(Rw2ImageReadMetadataTest_1579, NonRw2WithIoErrorThrowsFailedToReadImageDataAndCloses_1579) {
  auto fake = std::make_unique<FakeBasicIo>("not_rw2_error.bin");
  FakeBasicIo* fake_ptr = fake.get();
  fake->open_rc = 0;

  // Force the path where non-RW2 + io_->error() triggers kerFailedToReadImageData.
  fake->error_rc = 7;
  fake->eof_flag = false;
  fake->data = {0xDE, 0xAD, 0xBE, 0xEF};

  auto img = MakeImage(std::move(fake));

  try {
    img->readMetadata();
    FAIL() << "Expected Exiv2::Error to be thrown";
  } catch (const Exiv2::Error& e) {
    ExpectErrorCodeIfAvailable(e, Exiv2::ErrorCode::kerFailedToReadImageData);
  }

  EXPECT_EQ(fake_ptr->open_calls, 1);
  EXPECT_EQ(fake_ptr->close_calls, 1);
}

TEST_F(Rw2ImageReadMetadataTest_1579, NonRw2WithEofThrowsFailedToReadImageDataAndCloses_1579) {
  auto fake = std::make_unique<FakeBasicIo>("not_rw2_eof.bin");
  FakeBasicIo* fake_ptr = fake.get();
  fake->open_rc = 0;

  // Force the path where non-RW2 + io_->eof() triggers kerFailedToReadImageData.
  fake->error_rc = 0;
  fake->eof_flag = true;
  fake->data = {0xAA, 0xBB, 0xCC};

  auto img = MakeImage(std::move(fake));

  try {
    img->readMetadata();
    FAIL() << "Expected Exiv2::Error to be thrown";
  } catch (const Exiv2::Error& e) {
    ExpectErrorCodeIfAvailable(e, Exiv2::ErrorCode::kerFailedToReadImageData);
  }

  EXPECT_EQ(fake_ptr->open_calls, 1);
  EXPECT_EQ(fake_ptr->close_calls, 1);
}