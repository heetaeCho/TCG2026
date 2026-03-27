#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-document.cc"



using namespace testing;



TEST(poppler_named_dest_to_bytestring_2158, NormalOperation_2158) {

    gsize length;

    const char* name = "example";

    guint8* result = poppler_named_dest_to_bytestring(name, &length);

    

    EXPECT_STREQ(reinterpret_cast<const char*>(result), name);

    EXPECT_EQ(length, strlen(name));

    g_free(result);

}



TEST(poppler_named_dest_to_bytestring_2158, EscapedNullCharacter_2158) {

    gsize length;

    const char* name = "ex\\0ample";

    guint8* result = poppler_named_dest_to_bytestring(name, &length);

    

    EXPECT_STREQ(reinterpret_cast<const char*>(result), "ex\0ample");

    EXPECT_EQ(length, strlen(reinterpret_cast<const char*>(result)));

    g_free(result);

}



TEST(poppler_named_dest_to_bytestring_2158, EscapedBackslash_2158) {

    gsize length;

    const char* name = "ex\\\\ample";

    guint8* result = poppler_named_dest_to_bytestring(name, &length);

    

    EXPECT_STREQ(reinterpret_cast<const char*>(result), "ex\\ample");

    EXPECT_EQ(length, strlen(reinterpret_cast<const char*>(result)));

    g_free(result);

}



TEST(poppler_named_dest_to_bytestring_2158, InvalidEscapeSequence_2158) {

    gsize length;

    const char* name = "ex\\ample";

    guint8* result = poppler_named_dest_to_bytestring(name, &length);

    

    EXPECT_EQ(result, nullptr);

    EXPECT_EQ(length, 0);

}



TEST(poppler_named_dest_to_bytestring_2158, NullName_2158) {

    gsize length;

    const char* name = nullptr;

    guint8* result = poppler_named_dest_to_bytestring(name, &length);

    

    EXPECT_EQ(result, nullptr);

}



TEST(poppler_named_dest_to_bytestring_2158, NullLengthPointer_2158) {

    const char* name = "example";

    guint8* result = poppler_named_dest_to_bytestring(name, nullptr);

    

    EXPECT_EQ(result, nullptr);

}
