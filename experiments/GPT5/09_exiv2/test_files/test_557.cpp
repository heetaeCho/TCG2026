// File: test_fileio_tell_557.cpp
#include <gtest/gtest.h>

#include <exiv2/basicio.hpp>

#include <cstdio>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

#if !defined(_WIN32)
#include <unistd.h>
#endif

namespace {

std::filesystem::path MakeUniqueTempPath(const std::string& prefix) {
  const auto dir = std::filesystem::temp_directory_path();
  // Good-enough uniqueness for unit tests.
  const auto name =
      prefix + "_" + std::to_string(::getpid()) + "_" + std::to_string(::time(nullptr)) + ".bin";
  return dir / name;
}

void WriteFileBytes(const std::filesystem::path& p, const std::vector<unsigned char>& bytes) {
  std::ofstream os(p, std::ios::binary | std::ios::trunc);
  ASSERT_TRUE(os.is_open());
  if (!bytes.empty()) {
    os.write(reinterpret_cast<const char*>(bytes.data()), static_cast<std::streamsize>(bytes.size()));
  }
  ASSERT_TRUE(os.good());
}

}  // namespace

class FileIoTellTest_557 : public ::testing::Test {};

TEST_F(FileIoTellTest_557, TellIsZeroRightAfterOpen_557) {
  const auto path = MakeUniqueTempPath("exiv2_fileio_tell_open0_557");
  // Ensure the file exists.
  WriteFileBytes(path, {});

  Exiv2::FileIo io(path.string());
  ASSERT_EQ(0, io.open("rb")) << "open(\"rb\") should succeed for an existing empty file";

  EXPECT_EQ(0u, io.tell());

  EXPECT_EQ(0, io.close());
  std::error_code ec;
  std::filesystem::remove(path, ec);
}

TEST_F(FileIoTellTest_557, TellAdvancesAfterWrite_557) {
  const auto path = MakeUniqueTempPath("exiv2_fileio_tell_write_557");

  Exiv2::FileIo io(path.string());
  ASSERT_EQ(0, io.open("wb+")) << "open(\"wb+\") should create/truncate and allow tell()";

  EXPECT_EQ(0u, io.tell());

  const Exiv2::byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
  const size_t written = io.write(data, sizeof(data));
  EXPECT_EQ(sizeof(data), written);

  // Observable behavior: tell() reflects current stream position.
  EXPECT_EQ(sizeof(data), io.tell());

  EXPECT_EQ(0, io.close());
  std::error_code ec;
  std::filesystem::remove(path, ec);
}

TEST_F(FileIoTellTest_557, TellUnchangedWhenWritingZeroBytes_557) {
  const auto path = MakeUniqueTempPath("exiv2_fileio_tell_write0_557");

  Exiv2::FileIo io(path.string());
  ASSERT_EQ(0, io.open("wb+"));

  const Exiv2::byte one = 0xAA;
  ASSERT_EQ(1u, io.write(&one, 1u));
  const size_t before = io.tell();

  // Boundary condition: write with count == 0 should not advance position.
  // (We pass a non-null pointer but a zero count.)
  EXPECT_EQ(0u, io.write(&one, 0u));
  EXPECT_EQ(before, io.tell());

  EXPECT_EQ(0, io.close());
  std::error_code ec;
  std::filesystem::remove(path, ec);
}

TEST_F(FileIoTellTest_557, TellAdvancesAfterRead_557) {
  const auto path = MakeUniqueTempPath("exiv2_fileio_tell_read_557");
  WriteFileBytes(path, {0x10, 0x20, 0x30, 0x40, 0x50});

  Exiv2::FileIo io(path.string());
  ASSERT_EQ(0, io.open("rb"));

  EXPECT_EQ(0u, io.tell());

  Exiv2::byte buf[2] = {};
  const size_t r = io.read(buf, sizeof(buf));
  EXPECT_EQ(sizeof(buf), r);

  EXPECT_EQ(sizeof(buf), io.tell());

  EXPECT_EQ(0, io.close());
  std::error_code ec;
  std::filesystem::remove(path, ec);
}

#if !defined(_WIN32) && defined(__linux__)
TEST_F(FileIoTellTest_557, TellThrowsWhenUnderlyingStreamIsNotSeekable_557) {
  // On Linux, ftello() on a pipe typically fails with ESPIPE and returns -1,
  // which should trigger the observable error handling in tell().
  int fds[2] = {-1, -1};
  ASSERT_EQ(0, ::pipe(fds));

  // Build a path that refers to the pipe read-end via /proc.
  const std::string procPath = std::string("/proc/self/fd/") + std::to_string(fds[0]);

  Exiv2::FileIo io(procPath);
  ASSERT_EQ(0, io.open("rb")) << "Opening /proc/self/fd/<pipefd> should succeed on Linux";

  EXPECT_ANY_THROW({ (void)io.tell(); });

  (void)io.close();
  ::close(fds[0]);
  ::close(fds[1]);
}
#endif