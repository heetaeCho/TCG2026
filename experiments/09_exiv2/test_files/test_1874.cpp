#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Assuming XMP_Uns32 and XMP_Uns8 are defined somewhere in the codebase.

typedef unsigned int XMP_Uns32;

typedef unsigned char XMP_Uns8;



extern "C" {

    void CodePoint_from_UTF8(const XMP_Uns8 *u8Ptr, size_t maxBytes, XMP_Uns32 *cp, size_t *u8Len);

}



// Mocking the external function CodePoint_from_UTF8

class MockCodePointFromUTF8 {

public:

    MOCK_METHOD4(CodePoint_from_UTF8, void(const XMP_Uns8*, size_t, XMP_Uns32*, size_t*));

};



MockCodePointFromUTF8* mock = nullptr;



extern "C" {

    void CodePoint_from_UTF8(const XMP_Uns8 *u8Ptr, size_t maxBytes, XMP_Uns32 *cp, size_t *u8Len) {

        mock->CodePoint_from_UTF8(u8Ptr, maxBytes, cp, u8Len);

    }

}



// Assuming the function GetCodePoint is part of a class or namespace.

// For simplicity, we'll assume it's in the global namespace for this test.

XMP_Uns32 GetCodePoint(const XMP_Uns8 **utf8Str_io);



class UnicodeInlinesTest_1874 : public ::testing::Test {

protected:

    void SetUp() override {

        mock = new MockCodePointFromUTF8();

    }



    void TearDown() override {

        delete mock;

    }

};



TEST_F(UnicodeInlinesTest_1874, GetCodePoint_NormalOperation_1874) {

    const XMP_Uns8 utf8Str[] = {0xE2, 0x9C, 0x85}; // U+2705 (CHECK MARK)

    const XMP_Uns8 *utf8Ptr = utf8Str;

    EXPECT_CALL(*mock, CodePoint_from_UTF8(utf8Ptr, 4, testing::NotNull(), testing::NotNull()))

        .WillOnce(testing::DoAll(

            testing::SetArgReferee<2>(0x2705),

            testing::SetArgReferee<3>(3)

        ));



    XMP_Uns32 cp = GetCodePoint(&utf8Ptr);

    EXPECT_EQ(cp, 0x2705);

    EXPECT_EQ(utf8Ptr - utf8Str, 3);

}



TEST_F(UnicodeInlinesTest_1874, GetCodePoint_BoundaryCondition_SingleByte_1874) {

    const XMP_Uns8 utf8Str[] = {0x41}; // 'A'

    const XMP_Uns8 *utf8Ptr = utf8Str;

    EXPECT_CALL(*mock, CodePoint_from_UTF8(utf8Ptr, 4, testing::NotNull(), testing::NotNull()))

        .WillOnce(testing::DoAll(

            testing::SetArgReferee<2>(0x41),

            testing::SetArgReferee<3>(1)

        ));



    XMP_Uns32 cp = GetCodePoint(&utf8Ptr);

    EXPECT_EQ(cp, 0x41);

    EXPECT_EQ(utf8Ptr - utf8Str, 1);

}



TEST_F(UnicodeInlinesTest_1874, GetCodePoint_BoundaryCondition_MaxBytes_1874) {

    const XMP_Uns8 utf8Str[] = {0xF0, 0x9F, 0x92, 0xA9}; // U+1F4A9 (PILE OF POO)

    const XMP_Uns8 *utf8Ptr = utf8Str;

    EXPECT_CALL(*mock, CodePoint_from_UTF8(utf8Ptr, 4, testing::NotNull(), testing::NotNull()))

        .WillOnce(testing::DoAll(

            testing::SetArgReferee<2>(0x1F4A9),

            testing::SetArgReferee<3>(4)

        ));



    XMP_Uns32 cp = GetCodePoint(&utf8Ptr);

    EXPECT_EQ(cp, 0x1F4A9);

    EXPECT_EQ(utf8Ptr - utf8Str, 4);

}



TEST_F(UnicodeInlinesTest_1874, GetCodePoint_ExceptionalCase_InvalidUTF8_1874) {

    const XMP_Uns8 utf8Str[] = {0xFF}; // Invalid UTF-8

    const XMP_Uns8 *utf8Ptr = utf8Str;

    EXPECT_CALL(*mock, CodePoint_from_UTF8(utf8Ptr, 4, testing::NotNull(), testing::NotNull()))

        .WillOnce(testing::Throw(std::runtime_error("Invalid UTF-8")));



    EXPECT_THROW(GetCodePoint(&utf8Ptr), std::runtime_error);

}
