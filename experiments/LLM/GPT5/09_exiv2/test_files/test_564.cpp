// TEST_ID: 564
// File: test_fileio_read_564.cpp

#include <gtest/gtest.h>

#include <exiv2/basicio.hpp>

#include <cstdio>
#include <cstring>
#include <fstream>
#include <string>
#include <vector>

namespace {

class TempFile_564 {
 public:
  explicit TempFile_564(const std::vector<Exiv2::byte>& content) {
    // Create a unique-ish temp filename (portable fallback).
    // We avoid relying on internal Exiv2 test helpers since they are not provided here.
    char nameBuf[L_tmpnam];
#if defined(_MSC_VER)
    tmpnam_s(nameBuf, sizeof(nameBuf));
    path_ = nameBuf;
#else
    std::tmpnam(nameBuf);  // NOLINT(concurrency-mt-unsafe)
    path_ = nameBuf;
#endif

    std::ofstream os(path_, std::ios::binary | std::ios::out | std::ios::trunc);
    ASSERT_TRUE(os.is_open()) << "Failed to create temp file: " << path_;
    os.write(reinterpret_cast<const char*>(content.data()),
             static_cast<std::streamsize>(content.size()));
    os.close();
  }

  ~TempFile_564() {
    if (!path_.empty()) {
      std::remove(path_.c_str());
    }
  }

  const std::string& path() const { return path_; }

 private:
  std::string path_;
};

class FileIoReadTest_564 : public ::testing::Test {
 protected:
  FileIoReadTest_564()
      : content_{static_cast<Exiv2::byte>('A'), static_cast<Exiv2::byte>('B'),
                 static_cast<Exiv2::byte>('C'), static_cast<Exiv2::byte>('D'),
                 static_cast<Exiv2::byte>('E')},
        tmp_(content_) {}

  std::vector<Exiv2::byte> content_;
  TempFile_564 tmp_;
};

}  // namespace

TEST_F(FileIoReadTest_564, ReadReturnsZeroWhenNotOpen_564) {
  Exiv2::FileIo io(tmp_.path());

  Exiv2::byte buf[8];
  std::memset(buf, 0x7F, sizeof(buf));

  const size_t n = io.read(buf, sizeof(buf));
  EXPECT_EQ(0u, n);
}

TEST_F(FileIoReadTest_564, ReadReturnsZeroAfterClose_564) {
  Exiv2::FileIo io(tmp_.path());
  ASSERT_EQ(0, io.open("rb"));
  ASSERT_EQ(0, io.close());

  Exiv2::byte buf[8];
  std::memset(buf, 0, sizeof(buf));

  const size_t n = io.read(buf, sizeof(buf));
  EXPECT_EQ(0u, n);
}

TEST_F(FileIoReadTest_564, ReadsExactBytesFromBeginning_564) {
  Exiv2::FileIo io(tmp_.path());
  ASSERT_EQ(0, io.open("rb"));

  Exiv2::byte buf[4];
  std::memset(buf, 0, sizeof(buf));

  const size_t n = io.read(buf, sizeof(buf));
  EXPECT_EQ(4u, n);
  EXPECT_EQ(static_cast<Exiv2::byte>('A'), buf[0]);
  EXPECT_EQ(static_cast<Exiv2::byte>('B'), buf[1]);
  EXPECT_EQ(static_cast<Exiv2::byte>('C'), buf[2]);
  EXPECT_EQ(static_cast<Exiv2::byte>('D'), buf[3]);
}

TEST_F(FileIoReadTest_564, ReadWithZeroCountReturnsZero_564) {
  Exiv2::FileIo io(tmp_.path());
  ASSERT_EQ(0, io.open("rb"));

  Exiv2::byte buf[4];
  std::memset(buf, 0x11, sizeof(buf));

  const size_t before = io.tell();
  const size_t n = io.read(buf, 0);
  const size_t after = io.tell();

  EXPECT_EQ(0u, n);
  // Observable behavior through public interface: position should not advance.
  EXPECT_EQ(before, after);
}

TEST_F(FileIoReadTest_564, ReadPastEndThenSubsequentReadReturnsZero_564) {
  Exiv2::FileIo io(tmp_.path());
  ASSERT_EQ(0, io.open("rb"));

  std::vector<Exiv2::byte> buf(content_.size() + 10, static_cast<Exiv2::byte>(0));

  const size_t n1 = io.read(buf.data(), buf.size());
  EXPECT_EQ(content_.size(), n1);

  // Validate the bytes that exist in the file.
  for (size_t i = 0; i < content_.size(); ++i) {
    EXPECT_EQ(content_[i], buf[i]);
  }

  // A subsequent read at/after end-of-file should yield 0 bytes.
  Exiv2::byte one = 0;
  const size_t n2 = io.read(&one, 1);
  EXPECT_EQ(0u, n2);

  // If EOF is exposed by the interface, it should now be observable.
  // (We keep this as a weak expectation since exact EOF signaling can vary.)
  EXPECT_TRUE(io.eof() || io.tell() >= content_.size());
}