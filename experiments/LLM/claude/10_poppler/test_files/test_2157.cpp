#include <glib.h>
#include <gtest/gtest.h>
#include <cstring>

// Declaration of the function under test
extern "C" {
char *poppler_named_dest_from_bytestring(const guint8 *data, gsize length);
}

class PopplerNamedDestFromBytestringTest_2157 : public ::testing::Test {
protected:
    void TearDown() override {}
};

// Test normal ASCII string without special characters
TEST_F(PopplerNamedDestFromBytestringTest_2157, NormalAsciiString_2157)
{
    const guint8 data[] = {'h', 'e', 'l', 'l', 'o'};
    gsize length = sizeof(data);
    char *result = poppler_named_dest_from_bytestring(data, length);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "hello");
    g_free(result);
}

// Test string containing null bytes - should be escaped as \0
TEST_F(PopplerNamedDestFromBytestringTest_2157, NullByteEscaping_2157)
{
    const guint8 data[] = {'a', '\0', 'b'};
    gsize length = 3;
    char *result = poppler_named_dest_from_bytestring(data, length);
    ASSERT_NE(result, nullptr);
    // Expected: "a\\0b" (the literal characters a, \, 0, b)
    EXPECT_EQ(result[0], 'a');
    EXPECT_EQ(result[1], '\\');
    EXPECT_EQ(result[2], '0');
    EXPECT_EQ(result[3], 'b');
    EXPECT_EQ(result[4], '\0');
    g_free(result);
}

// Test string containing backslash - should be escaped as double backslash
TEST_F(PopplerNamedDestFromBytestringTest_2157, BackslashEscaping_2157)
{
    const guint8 data[] = {'a', '\\', 'b'};
    gsize length = 3;
    char *result = poppler_named_dest_from_bytestring(data, length);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result[0], 'a');
    EXPECT_EQ(result[1], '\\');
    EXPECT_EQ(result[2], '\\');
    EXPECT_EQ(result[3], 'b');
    EXPECT_EQ(result[4], '\0');
    g_free(result);
}

// Test single byte input
TEST_F(PopplerNamedDestFromBytestringTest_2157, SingleByte_2157)
{
    const guint8 data[] = {'x'};
    gsize length = 1;
    char *result = poppler_named_dest_from_bytestring(data, length);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "x");
    g_free(result);
}

// Test single null byte
TEST_F(PopplerNamedDestFromBytestringTest_2157, SingleNullByte_2157)
{
    const guint8 data[] = {'\0'};
    gsize length = 1;
    char *result = poppler_named_dest_from_bytestring(data, length);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result[0], '\\');
    EXPECT_EQ(result[1], '0');
    EXPECT_EQ(result[2], '\0');
    g_free(result);
}

// Test single backslash byte
TEST_F(PopplerNamedDestFromBytestringTest_2157, SingleBackslashByte_2157)
{
    const guint8 data[] = {'\\'};
    gsize length = 1;
    char *result = poppler_named_dest_from_bytestring(data, length);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result[0], '\\');
    EXPECT_EQ(result[1], '\\');
    EXPECT_EQ(result[2], '\0');
    g_free(result);
}

// Test with length 0 and non-null data pointer
TEST_F(PopplerNamedDestFromBytestringTest_2157, ZeroLengthWithNonNullData_2157)
{
    const guint8 data[] = {'a'};
    gsize length = 0;
    // g_return_val_if_fail(length != 0 || data != nullptr, nullptr)
    // length == 0 and data != nullptr => condition is true (0 || true = true), so it proceeds
    char *result = poppler_named_dest_from_bytestring(data, length);
    ASSERT_NE(result, nullptr);
    // With length 0, the loop doesn't execute, result should be empty string
    EXPECT_STREQ(result, "");
    g_free(result);
}

// Test multiple consecutive null bytes
TEST_F(PopplerNamedDestFromBytestringTest_2157, MultipleNullBytes_2157)
{
    const guint8 data[] = {'\0', '\0', '\0'};
    gsize length = 3;
    char *result = poppler_named_dest_from_bytestring(data, length);
    ASSERT_NE(result, nullptr);
    // Each \0 becomes \0 (two chars), so result is "\\0\\0\\0"
    EXPECT_EQ(strlen(result), 6u);
    EXPECT_EQ(result[0], '\\');
    EXPECT_EQ(result[1], '0');
    EXPECT_EQ(result[2], '\\');
    EXPECT_EQ(result[3], '0');
    EXPECT_EQ(result[4], '\\');
    EXPECT_EQ(result[5], '0');
    EXPECT_EQ(result[6], '\0');
    g_free(result);
}

// Test multiple consecutive backslashes
TEST_F(PopplerNamedDestFromBytestringTest_2157, MultipleBackslashes_2157)
{
    const guint8 data[] = {'\\', '\\'};
    gsize length = 2;
    char *result = poppler_named_dest_from_bytestring(data, length);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(strlen(result), 4u);
    EXPECT_EQ(result[0], '\\');
    EXPECT_EQ(result[1], '\\');
    EXPECT_EQ(result[2], '\\');
    EXPECT_EQ(result[3], '\\');
    g_free(result);
}

// Test mixed content with all special and normal characters
TEST_F(PopplerNamedDestFromBytestringTest_2157, MixedContent_2157)
{
    const guint8 data[] = {'A', '\0', '\\', 'B', '\0', '\\', 'C'};
    gsize length = 7;
    char *result = poppler_named_dest_from_bytestring(data, length);
    ASSERT_NE(result, nullptr);
    // Expected: A \0 \\ B \0 \\ C => "A\\0\\\\B\\0\\\\C"
    const char *expected = "A\\0\\\\B\\0\\\\C";
    EXPECT_STREQ(result, expected);
    g_free(result);
}

// Test with binary data (non-printable bytes that aren't null or backslash)
TEST_F(PopplerNamedDestFromBytestringTest_2157, BinaryData_2157)
{
    const guint8 data[] = {0x01, 0x02, 0xFF, 0xFE};
    gsize length = 4;
    char *result = poppler_named_dest_from_bytestring(data, length);
    ASSERT_NE(result, nullptr);
    // Non-special bytes should pass through unchanged
    EXPECT_EQ((guint8)result[0], 0x01);
    EXPECT_EQ((guint8)result[1], 0x02);
    EXPECT_EQ((guint8)result[2], 0xFF);
    EXPECT_EQ((guint8)result[3], 0xFE);
    EXPECT_EQ(result[4], '\0');
    g_free(result);
}

// Test output length for all-special input
TEST_F(PopplerNamedDestFromBytestringTest_2157, OutputLengthAllSpecial_2157)
{
    // All bytes are special (null and backslash alternating)
    const guint8 data[] = {'\0', '\\', '\0', '\\'};
    gsize length = 4;
    char *result = poppler_named_dest_from_bytestring(data, length);
    ASSERT_NE(result, nullptr);
    // Each special byte produces 2 output chars, so length should be 8
    EXPECT_EQ(strlen(result), 8u);
    g_free(result);
}

// Test with a larger input
TEST_F(PopplerNamedDestFromBytestringTest_2157, LargerInput_2157)
{
    // Create a larger buffer with known content
    const gsize length = 256;
    guint8 data[256];
    for (gsize i = 0; i < length; i++) {
        data[i] = (guint8)i;
    }
    char *result = poppler_named_dest_from_bytestring(data, length);
    ASSERT_NE(result, nullptr);
    // Only bytes 0x00 and 0x5C ('\\') should be escaped
    // That's 2 special bytes, each producing 2 output chars instead of 1
    // So total length = 256 - 2 + 2*2 = 258
    // But we need to be careful: strlen won't work because there might be embedded... wait, 
    // there are NO embedded nulls in the output since \0 is escaped to \0 (backslash, zero-char)
    // Actually the output for byte 0x00 is '\\' followed by '0' (the ASCII digit zero, 0x30), not a null byte
    // So strlen should work fine
    gsize expected_len = 256 + 2; // 2 extra chars for 2 special bytes
    EXPECT_EQ(strlen(result), expected_len);
    g_free(result);
}

// Test that the result is properly zero-terminated for empty-like input
TEST_F(PopplerNamedDestFromBytestringTest_2157, ProperZeroTermination_2157)
{
    const guint8 data[] = {'t', 'e', 's', 't'};
    gsize length = 4;
    char *result = poppler_named_dest_from_bytestring(data, length);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(strlen(result), 4u);
    EXPECT_EQ(result[4], '\0');
    g_free(result);
}
