// TEST_ID 554
// File: test_fileio_transfer_554.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <exiv2/basicio.hpp>
#include <exiv2/error.hpp>

#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

namespace fs = std::filesystem;

using ::testing::_;
using ::testing::Return;

namespace {

using Exiv2::BasicIo;
using Exiv2::byte;
using Exiv2::Error;
using Exiv2::ErrorCode;
using Exiv2::FileIo;

static std::string UniqueName(const std::string& prefix) {
  // Good enough uniqueness for unit tests.
  const auto ticks = static_cast<unsigned long long>(std::time(nullptr));
  return prefix + "_" + std::to_string(ticks) + "_" + std::to_string(std::rand());
}

static void WriteFileBytes(const fs::path& p, const std::vector<byte>& data) {
  std::ofstream os(p, std::ios::binary | std::ios::trunc);
  ASSERT_TRUE(os.good());
  if (!data.empty()) {
    os.write(reinterpret_cast<const char*>(data.data()), static_cast<std::streamsize>(data.size()));
  }
  ASSERT_TRUE(os.good());
}

static std::vector<byte> ReadFileBytes(const fs::path& p) {
  std::ifstream is(p, std::ios::binary);
  std::vector<byte> out;
  if (!is.good()) return out;
  is.seekg(0, std::ios::end);
  const std::streamsize n = is.tellg();
  is.seekg(0, std::ios::beg);
  if (n > 0) {
    out.resize(static_cast<size_t>(n));
    is.read(reinterpret_cast<char*>(out.data()), n);
  }
  return out;
}

// A simple external collaborator for FileIo::transfer(BasicIo& src).
// Implements only what transfer/write(src) is expected to use (open/close/read/path/error).
class MemorySourceIo final : public BasicIo {
 public:
  explicit MemorySourceIo(std::string fakePath, std::vector<byte> data)
      : fakePath_(std::move(fakePath)), data_(std::move(data)) {}

  int open() override {
    isOpen_ = true;
    eof_ = false;
    err_ = 0;
    pos_ = 0;
    return openRc_;
  }

  int close() override {
    isOpen_ = false;
    return closeRc_;
  }

  size_t read(byte* buf, size_t rcount) override {
    if (!isOpen_) {
      err_ = 1;
      return 0;
    }
    const size_t remain = (pos_ <= data_.size()) ? (data_.size() - pos_) : 0;
    const size_t n = (rcount < remain) ? rcount : remain;
    if (n > 0) {
      std::memcpy(buf, data_.data() + pos_, n);
      pos_ += n;
    }
    if (n == 0) {
      eof_ = true;
    }
    return n;
  }

  Exiv2::DataBuf read(size_t /*rcount*/) override {
    // Not used by these tests. Provide a safe default.
    return Exiv2::DataBuf();
  }

  const std::string& path() override { return fakePath_; }

  const int error() override { return err_; }

  const bool eof() override { return eof_; }

  const bool isopen() override { return isOpen_; }

  // Controls for error-path tests
  void setOpenReturnCode(int rc) { openRc_ = rc; }
  void setCloseReturnCode(int rc) { closeRc_ = rc; }
  void setError(int e) { err_ = e; }

 private:
  std::string fakePath_;
  std::vector<byte> data_;
  size_t pos_{0};
  bool isOpen_{false};
  bool eof_{false};
  int err_{0};
  int openRc_{0};
  int closeRc_{0};
};

// Minimal mock only for testing observable exception path when src.open() fails.
class MockBasicIo final : public BasicIo {
 public:
  MOCK_METHOD(int, open, (), (override));
  MOCK_METHOD(int, close, (), (override));
  MOCK_METHOD(size_t, read, (byte* buf, size_t rcount), (override));
  MOCK_METHOD(Exiv2::DataBuf, read, (size_t rcount), (override));
  MOCK_METHOD(const std::string&, path, (), (override));
  MOCK_METHOD(const int, error, (), (override));
  MOCK_METHOD(const bool, eof, (), (override));
  MOCK_METHOD(const bool, isopen, (), (override));
};

class FileIoTransferTest_554 : public ::testing::Test {
 protected:
  void SetUp() override {
    baseDir_ = fs::temp_directory_path() / UniqueName("exiv2_fileio_transfer_554");
    fs::create_directories(baseDir_);
  }

  void TearDown() override {
    std::error_code ec;
    fs::remove_all(baseDir_, ec);
  }

  fs::path baseDir_;
};

}  // namespace

// Normal operation: transfer from non-FileIo BasicIo writes data into destination file.
TEST_F(FileIoTransferTest_554, TransfersFromNonFileIoIntoDestinationFile_554) {
  const fs::path dstPath = baseDir_ / "dst.bin";
  FileIo dst(dstPath.string());

  const std::vector<byte> payload = {0x00, 0x11, 0x22, 0x7f, 0x80, 0xff};
  MemorySourceIo src("mem://payload", payload);

  EXPECT_NO_THROW(dst.transfer(src));

  ASSERT_TRUE(fs::exists(dstPath));
  EXPECT_EQ(ReadFileBytes(dstPath), payload);
}

// Boundary condition: transferring an empty source produces an empty destination file (or truncates).
TEST_F(FileIoTransferTest_554, TransfersEmptySourceProducesEmptyFile_554) {
  const fs::path dstPath = baseDir_ / "dst_empty.bin";
  // Pre-fill destination to ensure transfer overwrites/truncates in the non-FileIo path.
  WriteFileBytes(dstPath, std::vector<byte>{0xAA, 0xBB, 0xCC});

  FileIo dst(dstPath.string());

  MemorySourceIo src("mem://empty", {});
  EXPECT_NO_THROW(dst.transfer(src));

  ASSERT_TRUE(fs::exists(dstPath));
  EXPECT_TRUE(ReadFileBytes(dstPath).empty());
}

// Verification of external interactions (observable): transfer opens and closes the source on success.
TEST_F(FileIoTransferTest_554, OpensAndClosesSourceOnSuccess_554) {
  const fs::path dstPath = baseDir_ / "dst_openclose.bin";
  FileIo dst(dstPath.string());

  MemorySourceIo src("mem://openclose", std::vector<byte>{0x10, 0x20});
  EXPECT_FALSE(src.isopen());

  EXPECT_NO_THROW(dst.transfer(src));

  EXPECT_FALSE(src.isopen());  // must be closed after transfer
  EXPECT_EQ(ReadFileBytes(dstPath), (std::vector<byte>{0x10, 0x20}));
}

// Exceptional/error case: if src.open() fails (nonzero), transfer throws.
TEST_F(FileIoTransferTest_554, ThrowsWhenSourceOpenFails_554) {
  const fs::path dstPath = baseDir_ / "dst_throws_srcopen.bin";
  FileIo dst(dstPath.string());

  MockBasicIo src;
  const std::string srcPath = "mock://src";

  EXPECT_CALL(src, path()).WillRepeatedly(Return(::testing::Ref(srcPath)));
  EXPECT_CALL(src, open()).WillOnce(Return(1));  // fail open

  // transfer should throw due to src.open() != 0
  EXPECT_THROW(dst.transfer(src), Error);
}

// Exceptional/error case: if destination cannot be opened for writing, transfer throws.
TEST_F(FileIoTransferTest_554, ThrowsWhenDestinationOpenFailsInNonFileIoPath_554) {
  // Use a path within a non-existent directory to make open("w+b") fail.
  const fs::path missingDir = baseDir_ / "does_not_exist";
  const fs::path dstPath = missingDir / "dst.bin";

  FileIo dst(dstPath.string());
  MemorySourceIo src("mem://payload", std::vector<byte>{0x01, 0x02, 0x03});

  EXPECT_THROW(dst.transfer(src), Error);

  // Destination should not exist if open failed.
  EXPECT_FALSE(fs::exists(dstPath));
}

// Normal operation (FileIo-to-FileIo path): transfer should replace destination with source file content
// and the source path should be removed.
TEST_F(FileIoTransferTest_554, TransfersFromFileIoReplacesDestinationAndRemovesSource_554) {
  const fs::path dstPath = baseDir_ / "dst_fileio.bin";
  const fs::path srcPath = baseDir_ / "src_fileio.bin";

  const std::vector<byte> dstOld = {0xDE, 0xAD, 0xBE, 0xEF};
  const std::vector<byte> srcData = {0x01, 0x02, 0x03, 0x04, 0x05};

  WriteFileBytes(dstPath, dstOld);
  WriteFileBytes(srcPath, srcData);

  FileIo dst(dstPath.string());
  FileIo src(srcPath.string());

  EXPECT_NO_THROW(dst.transfer(src));

  ASSERT_TRUE(fs::exists(dstPath));
  EXPECT_EQ(ReadFileBytes(dstPath), srcData);

  // In the FileIo path, the source path is removed.
  EXPECT_FALSE(fs::exists(srcPath));
}

// Boundary/behavior: if destination was already open, it should end up open after transfer.
TEST_F(FileIoTransferTest_554, KeepsDestinationOpenIfItWasOpenBeforeTransfer_554) {
  const fs::path dstPath = baseDir_ / "dst_open.bin";
  const fs::path srcPath = baseDir_ / "src_open.bin";

  WriteFileBytes(dstPath, std::vector<byte>{0x00});
  WriteFileBytes(srcPath, std::vector<byte>{0x99, 0x88});

  FileIo dst(dstPath.string());
  FileIo src(srcPath.string());

  // Open destination in some mode; transfer is expected to restore previous open state.
  ASSERT_EQ(dst.open("rb"), 0);
  ASSERT_TRUE(dst.isopen());

  EXPECT_NO_THROW(dst.transfer(src));

  EXPECT_TRUE(dst.isopen());  // should be reopened/restored
  EXPECT_EQ(ReadFileBytes(dstPath), (std::vector<byte>{0x99, 0x88}));

  // Clean up
  (void)dst.close();
}

// Exceptional/error case (FileIo-to-FileIo): if destination cannot be opened in "a+b",
// implementation removes the source path and throws.
TEST_F(FileIoTransferTest_554, WhenDestinationOpenFailsInFileIoPathRemovesSourceAndThrows_554) {
  const fs::path missingDir = baseDir_ / "no_such_dir";
  const fs::path dstPath = missingDir / "dst_fail.bin";  // open("a+b") should fail
  const fs::path srcPath = baseDir_ / "src_will_be_removed.bin";

  WriteFileBytes(srcPath, std::vector<byte>{0x41, 0x42, 0x43});

  FileIo dst(dstPath.string());
  FileIo src(srcPath.string());

  EXPECT_THROW(dst.transfer(src), Error);

  // Observable behavior from the interface: source file removed on this failure path.
  EXPECT_FALSE(fs::exists(srcPath));
}