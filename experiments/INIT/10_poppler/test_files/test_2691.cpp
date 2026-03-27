// writeStream_test_2691.cc
#include <gtest/gtest.h>

#include <cairo/cairo.h>

#include <cstdio>
#include <cstring>

#if defined(__unix__) || defined(__APPLE__)
#include <unistd.h>   // close, unlink
#endif

// pdftocairo.cc typically defines a main(). Avoid colliding with gtest's main.
#define main pdftocairo_main_2691
#include "TestProjects/poppler/utils/pdftocairo.cc"
#undef main

namespace {

#if defined(__unix__) || defined(__APPLE__)
std::string MakeTempFilePath_2691() {
  // mkstemp requires the template to end with "XXXXXX" and modifies it in-place.
  char tmpl[] = "/tmp/writeStream_2691_XXXXXX";
  const int fd = mkstemp(tmpl);
  if (fd >= 0) {
    close(fd);
  }
  return std::string(tmpl);
}
#endif

}  // namespace

class WriteStreamTest_2691 : public ::testing::Test {};

TEST_F(WriteStreamTest_2691, ReturnsSuccessAndWritesBytes_2691) {
  FILE* f = std::tmpfile();
  ASSERT_NE(f, nullptr);

  const unsigned char payload[] = {'p', 'o', 'p', 'p', 'l', 'e', 'r'};
  const cairo_status_t st = writeStream(static_cast<void*>(f), payload,
                                        static_cast<unsigned int>(sizeof(payload)));
  EXPECT_EQ(st, CAIRO_STATUS_SUCCESS);

  std::rewind(f);
  unsigned char out[sizeof(payload)] = {};
  const size_t nread = std::fread(out, 1, sizeof(out), f);
  EXPECT_EQ(nread, sizeof(out));
  EXPECT_EQ(std::memcmp(out, payload, sizeof(payload)), 0);

  std::fclose(f);
}

#if defined(__unix__) || defined(__APPLE__)
TEST_F(WriteStreamTest_2691, ReturnsWriteErrorWhenFileIsReadOnly_2691) {
  const std::string path = MakeTempFilePath_2691();
  ASSERT_FALSE(path.empty());

  // Open read-only.
  FILE* f = std::fopen(path.c_str(), "rb");
  ASSERT_NE(f, nullptr);

  const unsigned char payload[] = {0x01, 0x02, 0x03, 0x04};
  const cairo_status_t st = writeStream(static_cast<void*>(f), payload,
                                        static_cast<unsigned int>(sizeof(payload)));
  EXPECT_EQ(st, CAIRO_STATUS_WRITE_ERROR);

  std::fclose(f);
  (void)unlink(path.c_str());
}
#endif

TEST_F(WriteStreamTest_2691, ZeroLengthWriteReturnsWriteError_2691) {
  FILE* f = std::tmpfile();
  ASSERT_NE(f, nullptr);

  const unsigned char dummy[] = {0xAB};  // Non-null pointer; length is zero.
  const cairo_status_t st = writeStream(static_cast<void*>(f), dummy, 0u);
  EXPECT_EQ(st, CAIRO_STATUS_WRITE_ERROR);

  std::fclose(f);
}