#include <gtest/gtest.h>

#include <cctype>

#include <cstring>



// Mocking or any external dependencies are not needed here as the function is standalone.



namespace re2 {



static const char* TerminateNumber(char* buf, const char* str, size_t n);

const int kMaxNumberLength = 32;



} // namespace re2



using namespace re2;



class TerminateNumberTest_202 : public ::testing::Test {

protected:

    static constexpr size_t kBufferSize = 64;

    char buffer_[kBufferSize];



    const char* CallTerminateNumber(const char* str, size_t n) {

        return TerminateNumber(buffer_, str, n);

    }

};



// Normal operation tests

TEST_F(TerminateNumberTest_202, ValidHexadecimalInput_202) {

    const char* result = CallTerminateNumber("1a3f", 4);

    EXPECT_STREQ(result, "1a3f");

}



TEST_F(TerminateNumberTest_202, ValidDecimalInput_202) {

    const char* result = CallTerminateNumber("12345", 5);

    EXPECT_STREQ(result, "12345");

}



// Boundary conditions tests

TEST_F(TerminateNumberTest_202, EmptyString_202) {

    const char* result = CallTerminateNumber("", 0);

    EXPECT_STREQ(result, "");

}



TEST_F(TerminateNumberTest_202, SingleDigit_202) {

    const char* result = CallTerminateNumber("9", 1);

    EXPECT_STREQ(result, "9");

}



TEST_F(TerminateNumberTest_202, MaxValidLength_202) {

    std::string max_length_str(kMaxNumberLength, 'a');

    const char* result = CallTerminateNumber(max_length_str.c_str(), kMaxNumberLength);

    EXPECT_STREQ(result, max_length_str.c_str());

}



TEST_F(TerminateNumberTest_202, JustAboveMaxValidLength_202) {

    std::string too_long_str(kMaxNumberLength + 1, 'a');

    const char* result = CallTerminateNumber(too_long_str.c_str(), kMaxNumberLength + 1);

    EXPECT_STREQ(result, "");

}



// Exceptional or error cases tests

TEST_F(TerminateNumberTest_202, NonNumericInput_202) {

    const char* result = CallTerminateNumber("abc", 3);

    EXPECT_STREQ(result, "a");

}



TEST_F(TerminateNumberTest_202, MixedContentWithLeadingSpace_202) {

    const char* result = CallTerminateNumber(" 1234", 5);

    EXPECT_STREQ(result, "");

}



TEST_F(TerminateNumberTest_202, MixedContentWithTrailingNonNumeric_202) {

    const char* result = CallTerminateNumber("123abc", 6);

    EXPECT_STREQ(result, "123");

}
