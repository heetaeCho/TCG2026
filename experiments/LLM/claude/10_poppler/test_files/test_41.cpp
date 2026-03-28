#include <gtest/gtest.h>
#include <cstdio>
#include <cstring>

// Declaration of the function under test
char *getLine(char *buf, int size, FILE *f);

class GetLineTest_41 : public ::testing::Test {
protected:
    FILE *createTempFile(const char *content, size_t len) {
        FILE *f = tmpfile();
        if (f && content && len > 0) {
            fwrite(content, 1, len, f);
            rewind(f);
        }
        return f;
    }

    FILE *createTempFileStr(const char *content) {
        return createTempFile(content, strlen(content));
    }
};

// Test reading a simple line terminated by \n (LF)
TEST_F(GetLineTest_41, ReadsLineLF_41) {
    FILE *f = createTempFileStr("hello\nworld\n");
    ASSERT_NE(f, nullptr);

    char buf[256];
    char *result = getLine(buf, sizeof(buf), f);

    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(buf, "hello\n");

    fclose(f);
}

// Test reading a simple line terminated by \r\n (CRLF)
TEST_F(GetLineTest_41, ReadsLineCRLF_41) {
    FILE *f = createTempFileStr("hello\r\nworld\r\n");
    ASSERT_NE(f, nullptr);

    char buf[256];
    char *result = getLine(buf, sizeof(buf), f);

    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(buf, "hello\r\n");

    fclose(f);
}

// Test reading a line terminated by \r (CR only)
TEST_F(GetLineTest_41, ReadsLineCROnly_41) {
    FILE *f = createTempFileStr("hello\rworld\r");
    ASSERT_NE(f, nullptr);

    char buf[256];
    char *result = getLine(buf, sizeof(buf), f);

    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(buf, "hello\r");

    // Next call should read "world\r"
    result = getLine(buf, sizeof(buf), f);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(buf, "world\r");

    fclose(f);
}

// Test that EOF on empty file returns nullptr
TEST_F(GetLineTest_41, EmptyFileReturnsNull_41) {
    FILE *f = createTempFileStr("");
    ASSERT_NE(f, nullptr);

    char buf[256];
    char *result = getLine(buf, sizeof(buf), f);

    EXPECT_EQ(result, nullptr);

    fclose(f);
}

// Test reading line without any line terminator (EOF terminates)
TEST_F(GetLineTest_41, ReadsLineNoTerminator_41) {
    FILE *f = createTempFileStr("hello");
    ASSERT_NE(f, nullptr);

    char buf[256];
    char *result = getLine(buf, sizeof(buf), f);

    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(buf, "hello");

    // Next call should return nullptr (EOF)
    result = getLine(buf, sizeof(buf), f);
    EXPECT_EQ(result, nullptr);

    fclose(f);
}

// Test buffer size limit truncates content
TEST_F(GetLineTest_41, BufferSizeLimitsContent_41) {
    FILE *f = createTempFileStr("abcdefghij\n");
    ASSERT_NE(f, nullptr);

    char buf[6]; // Can hold 5 chars + null
    char *result = getLine(buf, sizeof(buf), f);

    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(buf, "abcde");
    EXPECT_EQ(strlen(buf), 5u);

    fclose(f);
}

// Test multiple consecutive reads
TEST_F(GetLineTest_41, MultipleReads_41) {
    FILE *f = createTempFileStr("line1\nline2\nline3\n");
    ASSERT_NE(f, nullptr);

    char buf[256];

    char *result = getLine(buf, sizeof(buf), f);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(buf, "line1\n");

    result = getLine(buf, sizeof(buf), f);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(buf, "line2\n");

    result = getLine(buf, sizeof(buf), f);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(buf, "line3\n");

    result = getLine(buf, sizeof(buf), f);
    EXPECT_EQ(result, nullptr);

    fclose(f);
}

// Test buffer of size 1 should always produce empty string and return nullptr
TEST_F(GetLineTest_41, BufferSize1_41) {
    FILE *f = createTempFileStr("hello\n");
    ASSERT_NE(f, nullptr);

    char buf[1];
    char *result = getLine(buf, sizeof(buf), f);

    // size - 1 = 0, so loop doesn't execute, i == 0 => nullptr
    EXPECT_EQ(result, nullptr);
    EXPECT_EQ(buf[0], '\0');

    fclose(f);
}

// Test buffer of size 2 reads exactly one character
TEST_F(GetLineTest_41, BufferSize2_41) {
    FILE *f = createTempFileStr("hello\n");
    ASSERT_NE(f, nullptr);

    char buf[2];
    char *result = getLine(buf, sizeof(buf), f);

    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(buf, "h");

    fclose(f);
}

// Test \r followed by non-\n character (the non-\n should be pushed back)
TEST_F(GetLineTest_41, CRFollowedByNonLF_41) {
    FILE *f = createTempFileStr("abc\rdef\n");
    ASSERT_NE(f, nullptr);

    char buf[256];
    char *result = getLine(buf, sizeof(buf), f);

    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(buf, "abc\r");

    // 'd' should not be consumed
    result = getLine(buf, sizeof(buf), f);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(buf, "def\n");

    fclose(f);
}

// Test \r at end of file
TEST_F(GetLineTest_41, CRAtEndOfFile_41) {
    FILE *f = createTempFileStr("abc\r");
    ASSERT_NE(f, nullptr);

    char buf[256];
    char *result = getLine(buf, sizeof(buf), f);

    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(buf, "abc\r");

    // Should return nullptr on next call
    result = getLine(buf, sizeof(buf), f);
    EXPECT_EQ(result, nullptr);

    fclose(f);
}

// Test CRLF with buffer just big enough for \r but not \n
TEST_F(GetLineTest_41, CRLFBufferTooSmallForLF_41) {
    // "ab\r\n" - buffer size 4 means we can store 3 chars + null
    // We read 'a', 'b', '\r', then peek '\n' but i=3 and size-1=3, so can't fit
    FILE *f = createTempFileStr("ab\r\n");
    ASSERT_NE(f, nullptr);

    char buf[4];
    char *result = getLine(buf, sizeof(buf), f);

    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(buf, "ab\r");

    fclose(f);
}

// Test an empty line (just \n)
TEST_F(GetLineTest_41, EmptyLineLF_41) {
    FILE *f = createTempFileStr("\nhello\n");
    ASSERT_NE(f, nullptr);

    char buf[256];
    char *result = getLine(buf, sizeof(buf), f);

    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(buf, "\n");

    result = getLine(buf, sizeof(buf), f);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(buf, "hello\n");

    fclose(f);
}

// Test an empty line (just \r\n)
TEST_F(GetLineTest_41, EmptyLineCRLF_41) {
    FILE *f = createTempFileStr("\r\nhello\n");
    ASSERT_NE(f, nullptr);

    char buf[256];
    char *result = getLine(buf, sizeof(buf), f);

    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(buf, "\r\n");

    result = getLine(buf, sizeof(buf), f);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(buf, "hello\n");

    fclose(f);
}

// Test return value is the same as the buffer
TEST_F(GetLineTest_41, ReturnValueIsBufPointer_41) {
    FILE *f = createTempFileStr("test\n");
    ASSERT_NE(f, nullptr);

    char buf[256];
    char *result = getLine(buf, sizeof(buf), f);

    EXPECT_EQ(result, buf);

    fclose(f);
}

// Test with binary content including null bytes
TEST_F(GetLineTest_41, BinaryContentWithNullByte_41) {
    const char content[] = "ab\0cd\n";
    FILE *f = createTempFile(content, 6);
    ASSERT_NE(f, nullptr);

    char buf[256];
    memset(buf, 'X', sizeof(buf));
    char *result = getLine(buf, sizeof(buf), f);

    ASSERT_NE(result, nullptr);
    // The function reads byte by byte; null byte is just another char
    // It should read "ab\0cd\n"
    EXPECT_EQ(buf[0], 'a');
    EXPECT_EQ(buf[1], 'b');
    EXPECT_EQ(buf[2], '\0');

    fclose(f);
}

// Test reading a very long line
TEST_F(GetLineTest_41, LongLine_41) {
    std::string longLine(1000, 'A');
    longLine += '\n';
    FILE *f = createTempFileStr(longLine.c_str());
    ASSERT_NE(f, nullptr);

    char buf[2048];
    char *result = getLine(buf, sizeof(buf), f);

    ASSERT_NE(result, nullptr);
    EXPECT_EQ(strlen(buf), 1001u); // 1000 A's + \n

    fclose(f);
}

// Test multiple empty lines
TEST_F(GetLineTest_41, MultipleEmptyLines_41) {
    FILE *f = createTempFileStr("\n\n\n");
    ASSERT_NE(f, nullptr);

    char buf[256];

    for (int i = 0; i < 3; i++) {
        char *result = getLine(buf, sizeof(buf), f);
        ASSERT_NE(result, nullptr);
        EXPECT_STREQ(buf, "\n");
    }

    char *result = getLine(buf, sizeof(buf), f);
    EXPECT_EQ(result, nullptr);

    fclose(f);
}

// Test mixed line endings
TEST_F(GetLineTest_41, MixedLineEndings_41) {
    FILE *f = createTempFileStr("line1\nline2\rline3\r\nline4");
    ASSERT_NE(f, nullptr);

    char buf[256];

    char *result = getLine(buf, sizeof(buf), f);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(buf, "line1\n");

    result = getLine(buf, sizeof(buf), f);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(buf, "line2\r");

    result = getLine(buf, sizeof(buf), f);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(buf, "line3\r\n");

    result = getLine(buf, sizeof(buf), f);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(buf, "line4");

    result = getLine(buf, sizeof(buf), f);
    EXPECT_EQ(result, nullptr);

    fclose(f);
}
