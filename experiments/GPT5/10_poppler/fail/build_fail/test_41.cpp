// Unit tests for getLine() in ./TestProjects/poppler/goo/gfile.cc
// The TEST_ID is 41
//
// Constraints respected:
// - Treat getLine as a black box: verify only observable behavior via return value and buffer contents.
// - No reliance on internal state.
// - No mocking needed (uses stdio FILE*).

#include <gtest/gtest.h>

#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

extern "C" {
char *getLine(char *buf, int size, FILE *f);
}

namespace {

class GetLineTest_41 : public ::testing::Test {
protected:
  FILE* MakeTmpFileWithContent(const std::string& content) {
    FILE* fp = std::tmpfile();
    if (!fp) return nullptr;
    if (!content.empty()) {
      const size_t written = std::fwrite(content.data(), 1, content.size(), fp);
      EXPECT_EQ(written, content.size());
    }
    std::rewind(fp);
    return fp;
  }

  static std::string BufToString(const char* buf) {
    return buf ? std::string(buf) : std::string();
  }
};

TEST_F(GetLineTest_41, ReturnsNullptrOnImmediateEof_41) {
  FILE* fp = MakeTmpFileWithContent("");
  ASSERT_NE(fp, nullptr);

  char buf[16];
  std::memset(buf, 0x7f, sizeof(buf));  // sentinel

  char* ret = getLine(buf, static_cast<int>(sizeof(buf)), fp);

  EXPECT_EQ(ret, nullptr);
  std::fclose(fp);
}

TEST_F(GetLineTest_41, ReadsLineEndingWithLfAndIncludesLf_41) {
  FILE* fp = MakeTmpFileWithContent("abc\nDEF\n");
  ASSERT_NE(fp, nullptr);

  char buf[64] = {0};

  char* ret = getLine(buf, static_cast<int>(sizeof(buf)), fp);
  ASSERT_EQ(ret, buf);
  EXPECT_EQ(BufToString(buf), "abc\n");

  // Next call should read next line
  std::memset(buf, 0, sizeof(buf));
  ret = getLine(buf, static_cast<int>(sizeof(buf)), fp);
  ASSERT_EQ(ret, buf);
  EXPECT_EQ(BufToString(buf), "DEF\n");

  std::fclose(fp);
}

TEST_F(GetLineTest_41, ReadsLineEndingWithCrLfAndIncludesBothChars_41) {
  FILE* fp = MakeTmpFileWithContent("abc\r\nDEF\r\n");
  ASSERT_NE(fp, nullptr);

  char buf[64] = {0};

  char* ret = getLine(buf, static_cast<int>(sizeof(buf)), fp);
  ASSERT_EQ(ret, buf);
  EXPECT_EQ(BufToString(buf), std::string("abc\r\n"));

  std::memset(buf, 0, sizeof(buf));
  ret = getLine(buf, static_cast<int>(sizeof(buf)), fp);
  ASSERT_EQ(ret, buf);
  EXPECT_EQ(BufToString(buf), std::string("DEF\r\n"));

  std::fclose(fp);
}

TEST_F(GetLineTest_41, ReadsLineEndingWithCrOnlyAndIncludesCr_41) {
  FILE* fp = MakeTmpFileWithContent("abc\rDEF");
  ASSERT_NE(fp, nullptr);

  char buf[64] = {0};

  char* ret = getLine(buf, static_cast<int>(sizeof(buf)), fp);
  ASSERT_EQ(ret, buf);
  EXPECT_EQ(BufToString(buf), std::string("abc\r"));

  // Next call should continue with remaining content ("DEF")
  std::memset(buf, 0, sizeof(buf));
  ret = getLine(buf, static_cast<int>(sizeof(buf)), fp);
  ASSERT_EQ(ret, buf);
  EXPECT_EQ(BufToString(buf), "DEF");

  std::fclose(fp);
}

TEST_F(GetLineTest_41, ReadsLastLineWithoutNewline_41) {
  FILE* fp = MakeTmpFileWithContent("no_newline");
  ASSERT_NE(fp, nullptr);

  char buf[64] = {0};
  char* ret = getLine(buf, static_cast<int>(sizeof(buf)), fp);

  ASSERT_EQ(ret, buf);
  EXPECT_EQ(BufToString(buf), "no_newline");

  // Now EOF
  std::memset(buf, 0, sizeof(buf));
  ret = getLine(buf, static_cast<int>(sizeof(buf)), fp);
  EXPECT_EQ(ret, nullptr);

  std::fclose(fp);
}

TEST_F(GetLineTest_41, BufferSizeOneAlwaysReturnsNullptrAndWritesNullTerminator_41) {
  FILE* fp = MakeTmpFileWithContent("abc\n");
  ASSERT_NE(fp, nullptr);

  char buf[1];
  buf[0] = 'X';

  char* ret = getLine(buf, 1, fp);

  EXPECT_EQ(ret, nullptr);
  EXPECT_EQ(buf[0], '\0');  // observable: null-terminated buffer

  std::fclose(fp);
}

TEST_F(GetLineTest_41, TruncatesWhenBufferTooSmallAndNullTerminates_41) {
  // Needs more than 4 chars before newline
  FILE* fp = MakeTmpFileWithContent("ABCDE\nTAIL\n");
  ASSERT_NE(fp, nullptr);

  char buf[5]; // can store at most 4 chars + '\0'
  std::memset(buf, 0, sizeof(buf));

  char* ret = getLine(buf, static_cast<int>(sizeof(buf)), fp);
  ASSERT_EQ(ret, buf);

  // Should contain exactly 4 chars, no newline due to truncation
  EXPECT_EQ(std::strlen(buf), 4u);
  EXPECT_EQ(BufToString(buf), "ABCD");

  // Next call should continue from where it left off (likely "E\n" or similar),
  // but we only assert it returns a non-null line and is null-terminated.
  std::memset(buf, 0, sizeof(buf));
  ret = getLine(buf, static_cast<int>(sizeof(buf)), fp);
  ASSERT_NE(ret, nullptr);
  EXPECT_EQ(ret, buf);
  EXPECT_EQ(buf[sizeof(buf) - 1], '\0');

  std::fclose(fp);
}

TEST_F(GetLineTest_41, CrLfAtBufferBoundaryStillNullTerminates_41) {
  // Create a situation where '\r' is read near the end of buffer.
  // size=3 => max payload is 2 chars. Input "A\r\nB"
  FILE* fp = MakeTmpFileWithContent("A\r\nB");
  ASSERT_NE(fp, nullptr);

  char buf[3];
  std::memset(buf, 0, sizeof(buf));

  char* ret = getLine(buf, static_cast<int>(sizeof(buf)), fp);
  ASSERT_EQ(ret, buf);

  // With payload=2, it can hold "A\r" but cannot necessarily include '\n'
  // We assert safe observable properties: starts with 'A', contains '\r', null-terminated.
  EXPECT_EQ(buf[0], 'A');
  EXPECT_NE(std::strchr(buf, '\r'), nullptr);
  EXPECT_EQ(buf[2], '\0');

  std::fclose(fp);
}

} // namespace