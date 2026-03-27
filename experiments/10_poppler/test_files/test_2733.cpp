#include <gtest/gtest.h>

#include <cstring>



// Assuming strrstr is defined in a header file that we include

extern const char *strrstr(const char *s, const char *ss);



TEST(strrstrTest_2733, NormalOperation_2733) {

    const char *haystack = "hello world, hello universe";

    const char *needle = "hello";

    EXPECT_STREQ(strrstr(haystack, needle), "hello universe");

}



TEST(strrstrTest_2733, NeedleNotFound_2733) {

    const char *haystack = "hello world";

    const char *needle = "bye";

    EXPECT_EQ(strrstr(haystack, needle), nullptr);

}



TEST(strrstrTest_2733, EmptyHaystack_2733) {

    const char *haystack = "";

    const char *needle = "hello";

    EXPECT_EQ(strrstr(haystack, needle), nullptr);

}



TEST(strrstrTest_2733, EmptyNeedle_2733) {

    const char *haystack = "hello world";

    const char *needle = "";

    EXPECT_STREQ(strrstr(haystack, needle), haystack);

}



TEST(strrstrTest_2733, BothEmpty_2733) {

    const char *haystack = "";

    const char *needle = "";

    EXPECT_STREQ(strrstr(haystack, needle), haystack);

}



TEST(strrstrTest_2733, NeedleAtStart_2733) {

    const char *haystack = "hello world";

    const char *needle = "h";

    EXPECT_STREQ(strrstr(haystack, needle), "hello world");

}



TEST(strrstrTest_2733, NeedleAtEnd_2733) {

    const char *haystack = "hello world";

    const char *needle = "d";

    EXPECT_STREQ(strrstr(haystack, needle), "world");

}



TEST(strrstrTest_2733, OverlappingNeedles_2733) {

    const char *haystack = "abababa";

    const char *needle = "aba";

    EXPECT_STREQ(strrstr(haystack, needle), "ababa");

}
