// File: test_fileio_impl_switchmode_546.cpp

#include <gtest/gtest.h>

#include <cstdio>
#include <cstring>
#include <filesystem>
#include <string>

#ifndef _WIN32
#include <unistd.h>  // pipe, close
#endif

// Access FileIo::Impl if it is not publicly visible in the header.
#define private public
#define protected public
#include "basicio.hpp"
#undef private
#undef protected

namespace {

class FileIoImplSwitchModeTest_546 : public ::testing::Test {
 protected:
  static std::string MakeTempPath_546() {
    namespace fs = std::filesystem;
    auto dir = fs::temp_directory_path();
    auto name = std::string("exiv2_fileio_switchmode_546_") + std::to_string(::getpid()) + "_" +
                std::to_string(reinterpret_cast<std::uintptr_t>(&dir)) + ".bin";
    return (dir / name).string();
  }

  static void WriteBytes_546(const std::string& path, const std::string& bytes) {
    std::FILE* f = std::fopen(path.c_str(), "wb");
    ASSERT_NE(f, nullptr);
    ASSERT_EQ(std::fwrite(bytes.data(), 1U, bytes.size(), f), bytes.size());
    std::fclose(f);
  }

  static std::FILE* FOpenOrFail_546(const std::string& path, const char* mode) {
    std::FILE* f = std::fopen(path.c_str(), mode);
    EXPECT_NE(f, nullptr);
    return f;
  }
};

TEST_F(FileIoImplSwitchModeTest_546, SameModeReturnsZero_546) {
  const std::string path = MakeTempPath_546();
  WriteBytes_546(path, "0123456789");

  Exiv2::FileIo::Impl impl(path);
  impl.openMode_ = "rb";
  impl.fp_ = FOpenOrFail_546(path, impl.openMode_.c_str());
  ASSERT_NE(impl.fp_, nullptr);

  impl.opMode_ = Exiv2::FileIo::Impl::opRead;
  EXPECT_EQ(impl.switchMode(Exiv2::FileIo::Impl::opRead), 0);

  std::fclose(impl.fp_);
  std::error_code ec;
  std::filesystem::remove(path, ec);
}

TEST_F(FileIoImplSwitchModeTest_546, NoReopenFromSeekToReadReturnsZero_546) {
  const std::string path = MakeTempPath_546();
  WriteBytes_546(path, "abcdef");

  Exiv2::FileIo::Impl impl(path);
  impl.openMode_ = "rb";  // opRead should not require reopen per observable return behavior
  impl.fp_ = FOpenOrFail_546(path, impl.openMode_.c_str());
  ASSERT_NE(impl.fp_, nullptr);

  impl.opMode_ = Exiv2::FileIo::Impl::opSeek;
  EXPECT_EQ(impl.switchMode(Exiv2::FileIo::Impl::opRead), 0);

  // Still usable: tell should work.
  EXPECT_GE(std::ftell(impl.fp_), 0L);

  std::fclose(impl.fp_);
  std::error_code ec;
  std::filesystem::remove(path, ec);
}

TEST_F(FileIoImplSwitchModeTest_546, NoReopenFromWriteToReadReturnsZeroAndPreservesOffset_546) {
  const std::string path = MakeTempPath_546();
  WriteBytes_546(path, "0123456789abcdef");

  Exiv2::FileIo::Impl impl(path);
  impl.openMode_ = "rb";  // choose a mode that makes switching to opRead non-reopen in the implementation
  impl.fp_ = FOpenOrFail_546(path, impl.openMode_.c_str());
  ASSERT_NE(impl.fp_, nullptr);

  // Put the stream somewhere non-zero.
  ASSERT_EQ(std::fseek(impl.fp_, 5, SEEK_SET), 0);
  const long before = std::ftell(impl.fp_);
  ASSERT_EQ(before, 5);

  impl.opMode_ = Exiv2::FileIo::Impl::opWrite;  // old mode != opSeek -> path that does fseek(SEEK_CUR)
  EXPECT_EQ(impl.switchMode(Exiv2::FileIo::Impl::opRead), 0);

  const long after = std::ftell(impl.fp_);
  EXPECT_EQ(after, before);

  std::fclose(impl.fp_);
  std::error_code ec;
  std::filesystem::remove(path, ec);
}

TEST_F(FileIoImplSwitchModeTest_546, ReopenPathUpdatesModeAndPreservesOffset_546) {
  const std::string path = MakeTempPath_546();
  WriteBytes_546(path, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");

  Exiv2::FileIo::Impl impl(path);
  impl.openMode_ = "wb";  // a mode that should force reopen when switching to opRead
  impl.fp_ = FOpenOrFail_546(path, "r+b");  // ensure file exists and we can seek before switch
  ASSERT_NE(impl.fp_, nullptr);

  ASSERT_EQ(std::fseek(impl.fp_, 10, SEEK_SET), 0);
  const long before = std::ftell(impl.fp_);
  ASSERT_EQ(before, 10);

  impl.opMode_ = Exiv2::FileIo::Impl::opSeek;
  const int rc = impl.switchMode(Exiv2::FileIo::Impl::opRead);

  // Observable through interface: return code and public fields (as provided in prompt).
  EXPECT_EQ(rc, 0);
  EXPECT_EQ(impl.openMode_, std::string("r+b"));
  EXPECT_EQ(impl.opMode_, Exiv2::FileIo::Impl::opSeek);

  const long after = std::ftell(impl.fp_);
  EXPECT_EQ(after, before);

  std::fclose(impl.fp_);
  std::error_code ec;
  std::filesystem::remove(path, ec);
}

TEST_F(FileIoImplSwitchModeTest_546, ReopenFailureReturnsOneWhenPathMissing_546) {
  const std::string path = MakeTempPath_546();
  WriteBytes_546(path, "hello");

  Exiv2::FileIo::Impl impl(path);
  impl.openMode_ = "wb";              // force reopen when switching to opRead
  impl.fp_ = FOpenOrFail_546(path, "r+b");
  ASSERT_NE(impl.fp_, nullptr);

  // Remove the file so reopen via fopen(path_, ...) fails.
  std::error_code ec;
  std::filesystem::remove(path, ec);
  ASSERT_FALSE(std::filesystem::exists(path));

  impl.opMode_ = Exiv2::FileIo::Impl::opSeek;
  const int rc = impl.switchMode(Exiv2::FileIo::Impl::opRead);
  EXPECT_EQ(rc, 1);
}

#ifndef _WIN32
TEST_F(FileIoImplSwitchModeTest_546, FtelloFailureReturnsMinusOne_546) {
  int fds[2] = {-1, -1};
  ASSERT_EQ(::pipe(fds), 0);

  // Use the read end; seeking/telling on a pipe is not supported -> ftello should fail.
  std::FILE* fp = ::fdopen(fds[0], "rb");
  ASSERT_NE(fp, nullptr);
  ::close(fds[1]);  // close write end

  Exiv2::FileIo::Impl impl(std::string("does_not_matter_546"));
  impl.openMode_ = "wb";  // force reopen when switching to opRead (so ftello path is exercised)
  impl.fp_ = fp;
  impl.opMode_ = Exiv2::FileIo::Impl::opSeek;

  const int rc = impl.switchMode(Exiv2::FileIo::Impl::opRead);
  EXPECT_EQ(rc, -1);

  // switchMode may fclose() on success path, but on ftello failure it should not fclose() in the shown code.
  std::fclose(fp);
}
#endif

}  // namespace