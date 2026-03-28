#include <glib.h>
#include <gtest/gtest.h>
#include <cstring>

// Declaration of the function under test
extern "C" {
guint8 *poppler_named_dest_to_bytestring(const char *name, gsize *length);
}

class PopplerNamedDestToBytestringTest_2158 : public ::testing::Test {
protected:
    void TearDown() override {}
};

// Test normal string without any escape sequences
TEST_F(PopplerNamedDestToBytestringTest_2158, NormalStringNoEscapes_2158)
{
    gsize length = 0;
    guint8 *result = poppler_named_dest_to_bytestring("hello", &length);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(length, 5u);
    EXPECT_EQ(memcmp(result, "hello", 5), 0);
    g_free(result);
}

// Test empty string
TEST_F(PopplerNamedDestToBytestringTest_2158, EmptyString_2158)
{
    gsize length = 0;
    guint8 *result = poppler_named_dest_to_bytestring("", &length);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(length, 0u);
    g_free(result);
}

// Test string with escaped null character (\0)
TEST_F(PopplerNamedDestToBytestringTest_2158, EscapedNullCharacter_2158)
{
    gsize length = 0;
    guint8 *result = poppler_named_dest_to_bytestring("abc\\0def", &length);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(length, 7u);
    EXPECT_EQ(result[0], 'a');
    EXPECT_EQ(result[1], 'b');
    EXPECT_EQ(result[2], 'c');
    EXPECT_EQ(result[3], '\0');
    EXPECT_EQ(result[4], 'd');
    EXPECT_EQ(result[5], 'e');
    EXPECT_EQ(result[6], 'f');
    g_free(result);
}

// Test string with escaped backslash (\\)
TEST_F(PopplerNamedDestToBytestringTest_2158, EscapedBackslash_2158)
{
    gsize length = 0;
    guint8 *result = poppler_named_dest_to_bytestring("abc\\\\def", &length);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(length, 7u);
    EXPECT_EQ(result[0], 'a');
    EXPECT_EQ(result[1], 'b');
    EXPECT_EQ(result[2], 'c');
    EXPECT_EQ(result[3], '\\');
    EXPECT_EQ(result[4], 'd');
    EXPECT_EQ(result[5], 'e');
    EXPECT_EQ(result[6], 'f');
    g_free(result);
}

// Test invalid escape sequence (e.g., \a which is not \0 or \\)
TEST_F(PopplerNamedDestToBytestringTest_2158, InvalidEscapeSequence_2158)
{
    gsize length = 99;
    guint8 *result = poppler_named_dest_to_bytestring("abc\\adef", &length);
    EXPECT_EQ(result, nullptr);
    EXPECT_EQ(length, 0u);
}

// Test multiple escape sequences in a row
TEST_F(PopplerNamedDestToBytestringTest_2158, MultipleEscapeSequences_2158)
{
    gsize length = 0;
    guint8 *result = poppler_named_dest_to_bytestring("\\0\\\\\\0", &length);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(length, 3u);
    EXPECT_EQ(result[0], '\0');
    EXPECT_EQ(result[1], '\\');
    EXPECT_EQ(result[2], '\0');
    g_free(result);
}

// Test string that is only a single escaped null
TEST_F(PopplerNamedDestToBytestringTest_2158, SingleEscapedNull_2158)
{
    gsize length = 0;
    guint8 *result = poppler_named_dest_to_bytestring("\\0", &length);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(length, 1u);
    EXPECT_EQ(result[0], '\0');
    g_free(result);
}

// Test string that is only a single escaped backslash
TEST_F(PopplerNamedDestToBytestringTest_2158, SingleEscapedBackslash_2158)
{
    gsize length = 0;
    guint8 *result = poppler_named_dest_to_bytestring("\\\\", &length);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(length, 1u);
    EXPECT_EQ(result[0], '\\');
    g_free(result);
}

// Test invalid escape at the very start
TEST_F(PopplerNamedDestToBytestringTest_2158, InvalidEscapeAtStart_2158)
{
    gsize length = 99;
    guint8 *result = poppler_named_dest_to_bytestring("\\xabc", &length);
    EXPECT_EQ(result, nullptr);
    EXPECT_EQ(length, 0u);
}

// Test invalid escape at the end
TEST_F(PopplerNamedDestToBytestringTest_2158, InvalidEscapeAtEnd_2158)
{
    gsize length = 99;
    guint8 *result = poppler_named_dest_to_bytestring("abc\\1", &length);
    EXPECT_EQ(result, nullptr);
    EXPECT_EQ(length, 0u);
}

// Test single character string
TEST_F(PopplerNamedDestToBytestringTest_2158, SingleCharacter_2158)
{
    gsize length = 0;
    guint8 *result = poppler_named_dest_to_bytestring("a", &length);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(length, 1u);
    EXPECT_EQ(result[0], 'a');
    g_free(result);
}

// Test string with escape sequences mixed with normal characters
TEST_F(PopplerNamedDestToBytestringTest_2158, MixedContent_2158)
{
    gsize length = 0;
    guint8 *result = poppler_named_dest_to_bytestring("a\\0b\\\\c", &length);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(length, 5u);
    EXPECT_EQ(result[0], 'a');
    EXPECT_EQ(result[1], '\0');
    EXPECT_EQ(result[2], 'b');
    EXPECT_EQ(result[3], '\\');
    EXPECT_EQ(result[4], 'c');
    g_free(result);
}

// Test that a trailing backslash (end of string after backslash) is invalid
// When we see '\\' at the end, p is incremented to point at '\0', which is not '0' or '\\'
// so it goes to invalid
TEST_F(PopplerNamedDestToBytestringTest_2158, TrailingBackslash_2158)
{
    gsize length = 99;
    guint8 *result = poppler_named_dest_to_bytestring("abc\\", &length);
    // The backslash is followed by '\0' (end of string), 
    // p is incremented past backslash, *p is '\0', which doesn't match '0' or '\\'
    // so it goes to invalid
    EXPECT_EQ(result, nullptr);
    EXPECT_EQ(length, 0u);
}

// Test various invalid escape characters
TEST_F(PopplerNamedDestToBytestringTest_2158, InvalidEscapeVariousChars_2158)
{
    gsize length;

    length = 99;
    guint8 *r1 = poppler_named_dest_to_bytestring("\\n", &length);
    EXPECT_EQ(r1, nullptr);
    EXPECT_EQ(length, 0u);

    length = 99;
    guint8 *r2 = poppler_named_dest_to_bytestring("\\t", &length);
    EXPECT_EQ(r2, nullptr);
    EXPECT_EQ(length, 0u);

    length = 99;
    guint8 *r3 = poppler_named_dest_to_bytestring("\\1", &length);
    EXPECT_EQ(r3, nullptr);
    EXPECT_EQ(length, 0u);

    length = 99;
    guint8 *r4 = poppler_named_dest_to_bytestring("\\ ", &length);
    EXPECT_EQ(r4, nullptr);
    EXPECT_EQ(length, 0u);
}

// Test a longer string with no escapes
TEST_F(PopplerNamedDestToBytestringTest_2158, LongerStringNoEscapes_2158)
{
    const char *input = "This is a test destination name";
    gsize length = 0;
    guint8 *result = poppler_named_dest_to_bytestring(input, &length);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(length, strlen(input));
    EXPECT_EQ(memcmp(result, input, length), 0);
    g_free(result);
}

// Test consecutive escaped nulls
TEST_F(PopplerNamedDestToBytestringTest_2158, ConsecutiveEscapedNulls_2158)
{
    gsize length = 0;
    guint8 *result = poppler_named_dest_to_bytestring("\\0\\0\\0", &length);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(length, 3u);
    EXPECT_EQ(result[0], '\0');
    EXPECT_EQ(result[1], '\0');
    EXPECT_EQ(result[2], '\0');
    g_free(result);
}

// Test consecutive escaped backslashes
TEST_F(PopplerNamedDestToBytestringTest_2158, ConsecutiveEscapedBackslashes_2158)
{
    gsize length = 0;
    // Input: "\\\\\\\\" which in C string is "\\\\" (four chars), representing two escape sequences
    guint8 *result = poppler_named_dest_to_bytestring("\\\\\\\\", &length);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(length, 2u);
    EXPECT_EQ(result[0], '\\');
    EXPECT_EQ(result[1], '\\');
    g_free(result);
}
