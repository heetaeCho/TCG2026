#include <gtest/gtest.h>

#include <absl/strings/string_view.h>



// Assuming the function TerminateNumber is exposed in a header file re2_internal.h for testing purposes.

namespace re2 {

namespace re2_internal {



const char* TerminateNumber(char* buf, size_t nbuf, const char* str, size_t* np, bool accept_spaces);



}  // namespace re2_internal

}  // namespace re2



using namespace re2::re2_internal;



TEST(TerminateNumberTest_272, NormalOperation_PositiveNumber_272) {

    char buf[10];

    size_t n = 3;

    const char* str = "123";

    EXPECT_EQ(TerminateNumber(buf, sizeof(buf), str, &n, false), buf);

    EXPECT_STREQ(buf, "123");

    EXPECT_EQ(n, 3);

}



TEST(TerminateNumberTest_272, NormalOperation_NegativeNumber_272) {

    char buf[10];

    size_t n = 4;

    const char* str = "-123";

    EXPECT_EQ(TerminateNumber(buf, sizeof(buf), str, &n, false), buf);

    EXPECT_STREQ(buf, "-123");

    EXPECT_EQ(n, 4);

}



TEST(TerminateNumberTest_272, NormalOperation_LeadingSpacesAccepted_272) {

    char buf[10];

    size_t n = 5;

    const char* str = "  123";

    EXPECT_EQ(TerminateNumber(buf, sizeof(buf), str, &n, true), buf);

    EXPECT_STREQ(buf, "123");

    EXPECT_EQ(n, 3);

}



TEST(TerminateNumberTest_272, NormalOperation_LeadingSpacesNotAccepted_272) {

    char buf[10];

    size_t n = 5;

    const char* str = "  123";

    EXPECT_STREQ(TerminateNumber(buf, sizeof(buf), str, &n, false), "");

    EXPECT_EQ(n, 5);

}



TEST(TerminateNumberTest_272, BoundaryCondition_ZeroLengthString_272) {

    char buf[10];

    size_t n = 0;

    const char* str = "";

    EXPECT_STREQ(TerminateNumber(buf, sizeof(buf), str, &n, false), "");

    EXPECT_EQ(n, 0);

}



TEST(TerminateNumberTest_272, BoundaryCondition_MaxBufferLength_272) {

    char buf[10];

    size_t n = 9;

    const char* str = "123456789";

    EXPECT_EQ(TerminateNumber(buf, sizeof(buf), str, &n, false), buf);

    EXPECT_STREQ(buf, "123456789");

    EXPECT_EQ(n, 9);

}



TEST(TerminateNumberTest_272, BoundaryCondition_ExceedBufferLength_272) {

    char buf[10];

    size_t n = 10;

    const char* str = "1234567890";

    EXPECT_STREQ(TerminateNumber(buf, sizeof(buf), str, &n, false), "");

    EXPECT_EQ(n, 10);

}



TEST(TerminateNumberTest_272, EdgeCase_MultipleLeadingZeros_272) {

    char buf[10];

    size_t n = 6;

    const char* str = "000123";

    EXPECT_EQ(TerminateNumber(buf, sizeof(buf), str, &n, false), buf);

    EXPECT_STREQ(buf, "123");

    EXPECT_EQ(n, 3);

}



TEST(TerminateNumberTest_272, EdgeCase_NegativeMultipleLeadingZeros_272) {

    char buf[10];

    size_t n = 7;

    const char* str = "-000123";

    EXPECT_EQ(TerminateNumber(buf, sizeof(buf), str, &n, false), buf);

    EXPECT_STREQ(buf, "-123");

    EXPECT_EQ(n, 4);

}



TEST(TerminateNumberTest_272, EdgeCase_AllZeros_272) {

    char buf[10];

    size_t n = 6;

    const char* str = "000000";

    EXPECT_EQ(TerminateNumber(buf, sizeof(buf), str, &n, false), buf);

    EXPECT_STREQ(buf, "");

    EXPECT_EQ(n, 0);

}



TEST(TerminateNumberTest_272, EdgeCase_NegativeAllZeros_272) {

    char buf[10];

    size_t n = 7;

    const char* str = "-000000";

    EXPECT_STREQ(TerminateNumber(buf, sizeof(buf), str, &n, false), "");

    EXPECT_EQ(n, 7);

}
