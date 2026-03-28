#include <gtest/gtest.h>

#include "UnicodeConversions.cpp"



TEST_F(UnicodeConversionsTest_2063, PutASCIICodePoint_2063) {

    UTF32Unit cpIn = 0x41; // ASCII 'A'

    UTF8Unit utf8Out[1];

    size_t utf8Len = sizeof(utf8Out);

    size_t utf8Written;



    CodePoint_to_UTF8(cpIn, utf8Out, utf8Len, &utf8Written);



    EXPECT_EQ(utf8Written, 1);

    EXPECT_EQ(utf8Out[0], cpIn);

}



TEST_F(UnicodeConversionsTest_2063, PutMultiByteCodePoint_2063) {

    UTF32Unit cpIn = 0x044F; // Cyrillic 'я'

    UTF8Unit utf8Out[4]; // Maximum size needed for a single code point

    size_t utf8Len = sizeof(utf8Out);

    size_t utf8Written;



    CodePoint_to_UTF8(cpIn, utf8Out, utf8Len, &utf8Written);



    EXPECT_EQ(utf8Written, 2); // 'я' is represented by two UTF-8 bytes: 0xD1 0x9F

    EXPECT_EQ(utf8Out[0], 0xD1);

    EXPECT_EQ(utf8Out[1], 0x9F);

}



TEST_F(UnicodeConversionsTest_2063, PutMaxCodePoint_2063) {

    UTF32Unit cpIn = 0x10FFFF; // Maximum valid Unicode code point

    UTF8Unit utf8Out[4]; // Maximum size needed for a single code point

    size_t utf8Len = sizeof(utf8Out);

    size_t utf8Written;



    CodePoint_to_UTF8(cpIn, utf8Out, utf8Len, &utf8Written);



    EXPECT_EQ(utf8Written, 4); // Maximum UTF-8 byte sequence length is 4

    EXPECT_EQ(utf8Out[0], 0xF4);

    EXPECT_EQ(utf8Out[1], 0x8F);

    EXPECT_EQ(utf8Out[2], 0xBF);

    EXPECT_EQ(utf8Out[3], 0xBF);

}



TEST_F(UnicodeConversionsTest_2063, InsufficientBufferSpace_2063) {

    UTF32Unit cpIn = 0x044F; // Cyrillic 'я'

    UTF8Unit utf8Out[1]; // Buffer too small for multi-byte code point

    size_t utf8Len = sizeof(utf8Out);

    size_t utf8Written;



    CodePoint_to_UTF8(cpIn, utf8Out, utf8Len, &utf8Written);



    EXPECT_EQ(utf8Written, 0); // No bytes written due to insufficient buffer space

}



TEST_F(UnicodeConversionsTest_2063, NullOutputBuffer_2063) {

    UTF32Unit cpIn = 0x41; // ASCII 'A'

    UTF8Unit* utf8Out = nullptr;

    size_t utf8Len = 1;

    size_t utf8Written;



    EXPECT_DEATH({

        CodePoint_to_UTF8(cpIn, utf8Out, utf8Len, &utf8Written);

    }, "Assertion.*failed");

}



TEST_F(UnicodeConversionsTest_2063, NullBytesWrittenPointer_2063) {

    UTF32Unit cpIn = 0x41; // ASCII 'A'

    UTF8Unit utf8Out[1];

    size_t utf8Len = sizeof(utf8Out);

    size_t* utf8Written = nullptr;



    EXPECT_DEATH({

        CodePoint_to_UTF8(cpIn, utf8Out, utf8Len, utf8Written);

    }, "Assertion.*failed");

}
