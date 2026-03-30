#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/catch_tostring.hpp"



using namespace Catch;

using ::testing::_;

using ::testing::Return;



class StringMakerMock {

public:

    MOCK_METHOD1(convert, std::string(const char* str));

    MOCK_METHOD1(convert, std::string(char const* str));

    MOCK_METHOD1(convert, std::string(unsigned char const* str));

    MOCK_METHOD1(convert, std::string(bool b));

    MOCK_METHOD0(convert, std::string(std::nullptr_t));

    template <typename U>

    MOCK_METHOD1(convert, std::string(U* p));

    MOCK_METHOD1(convert, std::string(R C::* p));

};



TEST(StringMakerTest_87, ConvertCharPointer_87) {

    StringMakerMock mock;

    EXPECT_CALL(mock, convert("test")).WillOnce(Return("converted_test"));

    EXPECT_EQ(mock.convert("test"), "converted_test");

}



TEST(StringMakerTest_87, ConvertSignedCharPointer_87) {

    signed char const* str = "signed_test";

    EXPECT_EQ(StringMaker<signed char>::convert(str), "signed_test");

}



TEST(StringMakerTest_87, ConvertUnsignedCharPointer_87) {

    unsigned char const* str = "unsigned_test";

    EXPECT_EQ(StringMaker<unsigned char>::convert(str), "unsigned_test");

}



TEST(StringMakerTest_87, ConvertBoolTrue_87) {

    EXPECT_EQ(StringMaker<bool>::convert(true), "true");

}



TEST(StringMakerTest_87, ConvertBoolFalse_87) {

    EXPECT_EQ(StringMaker<bool>::convert(false), "false");

}



TEST(StringMakerTest_87, ConvertNullptr_87) {

    EXPECT_EQ(StringMaker<std::nullptr_t>::convert(nullptr), "nullptr");

}



TEST(StringMakerTest_87, ConvertPointerToChar_87) {

    char c = 'a';

    char* ptr = &c;

    EXPECT_EQ(StringMaker<char*>::convert(ptr), StringMaker<char*>::convert(ptr));

}



TEST(StringMakerTest_87, ConvertMemberPointer_87) {

    struct TestStruct { int member; };

    int TestStruct::*memberPtr = &TestStruct::member;

    EXPECT_EQ(StringMaker<int TestStruct::*>::convert(memberPtr), ::Catch::Detail::rawMemoryToString(memberPtr));

}



TEST(StringMakerTest_87, ConvertStdString_87) {

    std::string str = "std_string_test";

    EXPECT_EQ(StringMaker<std::string>::convert(str), str);

}



TEST(StringMakerTest_87, ConvertStringView_87) {

    std::string_view sv = "string_view_test";

    EXPECT_EQ(StringMaker<std::string_view>::convert(sv), std::string(sv));

}



TEST(StringMakerTest_87, ConvertWChar_tPointer_87) {

    wchar_t const* wstr = L"wide_test";

    EXPECT_EQ(StringMaker<wchar_t const*>::convert(wstr), StringMaker<wchar_t const*>::convert(wstr));

}



TEST(StringMakerTest_87, ConvertWString_87) {

    std::wstring wstr = L"wstd_string_test";

    EXPECT_EQ(StringMaker<std::wstring>::convert(wstr), ::Catch::Detail::toMbcs(std::string(wstr.begin(), wstr.end())));

}



TEST(StringMakerTest_87, ConvertByte_87) {

    std::byte b{42};

    EXPECT_EQ(StringMaker<std::byte>::convert(b), "std::byte{42}");

}



TEST(StringMakerTest_87, ConvertInt_87) {

    int value = 123;

    EXPECT_EQ(StringMaker<int>::convert(value), "123");

}



TEST(StringMakerTest_87, ConvertLong_87) {

    long value = 123456L;

    EXPECT_EQ(StringMaker<long>::convert(value), "123456");

}



TEST(StringMakerTest_87, ConvertLongLong_87) {

    long long value = 1234567890LL;

    EXPECT_EQ(StringMaker<long long>::convert(value), "1234567890");

}



TEST(StringMakerTest_87, ConvertUnsignedInt_87) {

    unsigned int value = 456U;

    EXPECT_EQ(StringMaker<unsigned int>::convert(value), "456");

}



TEST(StringMakerTest_87, ConvertUnsignedLong_87) {

    unsigned long value = 123456UL;

    EXPECT_EQ(StringMaker<unsigned long>::convert(value), "123456");

}



TEST(StringMakerTest_87, ConvertUnsignedLongLong_87) {

    unsigned long long value = 1234567890ULL;

    EXPECT_EQ(StringMaker<unsigned long long>::convert(value), "1234567890");

}



TEST(StringMakerTest_87, ConvertSignedChar_87) {

    signed char value = 'c';

    EXPECT_EQ(StringMaker<signed char>::convert(value), "'c'");

}



TEST(StringMakerTest_87, ConvertChar_87) {

    char value = 'd';

    EXPECT_EQ(StringMaker<char>::convert(value), "'d'");

}



TEST(StringMakerTest_87, ConvertUnsignedChar_87) {

    unsigned char value = 'e';

    EXPECT_EQ(StringMaker<unsigned char>::convert(value), "'e'");

}



TEST(StringMakerTest_87, ConvertFloat_87) {

    float value = 3.14f;

    EXPECT_EQ(StringMaker<float>::convert(value), "3.14");

}



TEST(StringMakerTest_87, ConvertDouble_87) {

    double value = 2.71828;

    EXPECT_EQ(StringMaker<double>::convert(value), "2.71828");

}



TEST(StringMakerTest_87, ConvertApprox_87) {

    Approx value(3.14);

    EXPECT_EQ(StringMaker<Catch::Approx>::convert(value), "Catch::Approx( 3.14 )");

}
