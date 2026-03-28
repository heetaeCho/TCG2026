#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <glib.h>



extern "C" {

    char *poppler_named_dest_from_bytestring(const guint8 *data, gsize length);

}



TEST(poppler_named_dest_from_bytestring_2157, NormalOperation_2157) {

    const guint8 data[] = { 'H', 'e', 'l', 'l', 'o' };

    gsize length = sizeof(data) / sizeof(guint8);



    char *result = poppler_named_dest_from_bytestring(data, length);

    EXPECT_STREQ(result, "Hello");

    g_free(result);

}



TEST(poppler_named_dest_from_bytestring_2157, ContainsNullByte_2157) {

    const guint8 data[] = { 'H', '\0', 'l', 'l', 'o' };

    gsize length = sizeof(data) / sizeof(guint8);



    char *result = poppler_named_dest_from_bytestring(data, length);

    EXPECT_STREQ(result, "H\\0llo");

    g_free(result);

}



TEST(poppler_named_dest_from_bytestring_2157, ContainsBackslash_2157) {

    const guint8 data[] = { 'H', '\\', 'e', 'l', 'l', 'o' };

    gsize length = sizeof(data) / sizeof(guint8);



    char *result = poppler_named_dest_from_bytestring(data, length);

    EXPECT_STREQ(result, "H\\\\ello");

    g_free(result);

}



TEST(poppler_named_dest_from_bytestring_2157, EmptyString_2157) {

    const guint8 data[] = { };

    gsize length = sizeof(data) / sizeof(guint8);



    char *result = poppler_named_dest_from_bytestring(data, length);

    EXPECT_STREQ(result, "");

    g_free(result);

}



TEST(poppler_named_dest_from_bytestring_2157, SingleNullByte_2157) {

    const guint8 data[] = { '\0' };

    gsize length = sizeof(data) / sizeof(guint8);



    char *result = poppler_named_dest_from_bytestring(data, length);

    EXPECT_STREQ(result, "\\0");

    g_free(result);

}



TEST(poppler_named_dest_from_bytestring_2157, SingleBackslash_2157) {

    const guint8 data[] = { '\\' };

    gsize length = sizeof(data) / sizeof(guint8);



    char *result = poppler_named_dest_from_bytestring(data, length);

    EXPECT_STREQ(result, "\\\\");

    g_free(result);

}



TEST(poppler_named_dest_from_bytestring_2157, NullDataPointer_2157) {

    const guint8 *data = nullptr;

    gsize length = 0;



    char *result = poppler_named_dest_from_bytestring(data, length);

    EXPECT_EQ(result, nullptr);

}



TEST(poppler_named_dest_from_bytestring_2157, ZeroLengthWithNonNullData_2157) {

    const guint8 data[] = { 'H', 'e', 'l', 'l', 'o' };

    gsize length = 0;



    char *result = poppler_named_dest_from_bytestring(data, length);

    EXPECT_STREQ(result, "");

    g_free(result);

}
