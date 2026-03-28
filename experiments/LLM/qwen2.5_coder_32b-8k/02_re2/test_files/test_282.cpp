#include <gtest/gtest.h>

#include <gmock/gmock.h>



namespace re2 { namespace re2_internal {



// Mocking external collaborators if any were needed

// In this case, no mocks are required as there are no external dependencies to mock.



TEST(ParseTest_282, NormalOperation_ValidNumber_282) {

    unsigned long long dest;

    EXPECT_TRUE(Parse("12345", 5, &dest, 10));

    EXPECT_EQ(dest, 12345ULL);

}



TEST(ParseTest_282, NormalOperation_Zero_282) {

    unsigned long long dest;

    EXPECT_TRUE(Parse("0", 1, &dest, 10));

    EXPECT_EQ(dest, 0ULL);

}



TEST(ParseTest_282, NormalOperation_MaxValue_282) {

    unsigned long long dest;

    const char* max_value_str = "4294967295"; // 2^32 - 1

    EXPECT_TRUE(Parse(max_value_str, strlen(max_value_str), &dest, 10));

    EXPECT_EQ(dest, 4294967295ULL);

}



TEST(ParseTest_282, BoundaryCondition_EmptyString_282) {

    unsigned long long dest;

    EXPECT_FALSE(Parse("", 0, &dest, 10));

}



TEST(ParseTest_282, BoundaryCondition_MaxLengthNumber_282) {

    unsigned long long dest;

    char max_length_str[kMaxNumberLength + 1] = {};

    memset(max_length_str, '9', kMaxNumberLength);

    max_length_str[kMaxNumberLength] = '\0';

    EXPECT_TRUE(Parse(max_length_str, strlen(max_length_str), &dest, 10));

}



TEST(ParseTest_282, BoundaryCondition_OutOfMaxLengthNumber_282) {

    unsigned long long dest;

    char out_of_max_length_str[kMaxNumberLength + 2] = {};

    memset(out_of_max_length_str, '9', kMaxNumberLength + 1);

    out_of_max_length_str[kMaxNumberLength + 1] = '\0';

    EXPECT_FALSE(Parse(out_of_max_length_str, strlen(out_of_max_length_str), &dest, 10));

}



TEST(ParseTest_282, Exceptional_NegativeNumber_282) {

    unsigned long long dest;

    EXPECT_FALSE(Parse("-12345", 6, &dest, 10));

}



TEST(ParseTest_282, Exceptional_InvalidCharacters_282) {

    unsigned long long dest;

    EXPECT_FALSE(Parse("123abc", 6, &dest, 10));

}



TEST(ParseTest_282, Exceptional_NullDestination_282) {

    EXPECT_TRUE(Parse("12345", 5, nullptr, 10));

}



TEST(ParseTest_282, Exceptional_LargeRadix_282) {

    unsigned long long dest;

    EXPECT_FALSE(Parse("12345", 5, &dest, 37)); // Invalid radix

}



TEST(ParseTest_282, Exceptional_BaseOverflow_282) {

    unsigned long long dest;

    const char* overflow_str = "18446744073709551616"; // 2^64 which overflows ull

    EXPECT_FALSE(Parse(overflow_str, strlen(overflow_str), &dest, 10));

}



}} // namespace re2::re2_internal
