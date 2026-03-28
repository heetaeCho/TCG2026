#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "UnicodeConversions.cpp"



// Test fixture for UTF16Swp_to_UTF8 function

class UTF16Swp_to_UTF8Test_2082 : public ::testing::Test {

protected:

    static const size_t kBufferSize = 1024;

    UTF16Unit utf16In[kBufferSize];

    UTF8Unit utf8Out[kBufferSize];

    size_t utf16Read;

    size_t utf8Written;



    void SetUp() override {

        memset(utf16In, 0, sizeof(utf16In));

        memset(utf8Out, 0, sizeof(utf8Out));

        utf16Read = 0;

        utf8Written = 0;

    }

};



// Test normal operation with ASCII characters

TEST_F(UTF16Swp_to_UTF8Test_2082, NormalOperationASCII_2082) {

    // Setup: Input "Hello" in UTF-16 (with swapped byte order)

    utf16In[0] = 0x4800;  // 'H'

    utf16In[1] = 0x6500;  // 'e'

    utf16In[2] = 0x6C00;  // 'l'

    utf16In[3] = 0x6C00;  // 'l'

    utf16In[4] = 0x6F00;  // 'o'



    // Exercise

    UTF16Swp_to_UTF8(utf16In, 5, utf8Out, kBufferSize, &utf16Read, &utf8Written);



    // Verify

    EXPECT_EQ(utf16Read, 5);

    EXPECT_EQ(utf8Written, 5);

    EXPECT_STREQ(reinterpret_cast<const char*>(utf8Out), "Hello");

}



// Test normal operation with Unicode characters

TEST_F(UTF16Swp_to_UTF8Test_2082, NormalOperationUnicode_2082) {

    // Setup: Input "😊" in UTF-16 (with swapped byte order)

    utf16In[0] = 0xD83D;  // High surrogate

    utf16In[1] = 0xDE0A;  // Low surrogate



    // Exercise

    UTF16Swp_to_UTF8(utf16In, 2, utf8Out, kBufferSize, &utf16Read, &utf8Written);



    // Verify

    EXPECT_EQ(utf16Read, 2);

    EXPECT_EQ(utf8Written, 4); // "😊" is 4 bytes in UTF-8

    EXPECT_STREQ(reinterpret_cast<const char*>(utf8Out), "\xF0\x9F\x98\x8A");

}



// Test boundary condition: empty input

TEST_F(UTF16Swp_to_UTF8Test_2082, EmptyInput_2082) {

    // Exercise

    UTF16Swp_to_UTF8(utf16In, 0, utf8Out, kBufferSize, &utf16Read, &utf8Written);



    // Verify

    EXPECT_EQ(utf16Read, 0);

    EXPECT_EQ(utf8Written, 0);

}



// Test boundary condition: full buffer case with exact fit

TEST_F(UTF16Swp_to_UTF8Test_2082, FullBufferExactFit_2082) {

    // Setup: Input "Hello" in UTF-16 (with swapped byte order)

    utf16In[0] = 0x4800;  // 'H'

    utf16In[1] = 0x6500;  // 'e'

    utf16In[2] = 0x6C00;  // 'l'

    utf16In[3] = 0x6C00;  // 'l'

    utf16In[4] = 0x6F00;  // 'o'



    // Exercise

    UTF16Swp_to_UTF8(utf16In, 5, utf8Out, 5, &utf16Read, &utf8Written);



    // Verify

    EXPECT_EQ(utf16Read, 5);

    EXPECT_EQ(utf8Written, 5);

    EXPECT_STREQ(reinterpret_cast<const char*>(utf8Out), "Hello");

}



// Test boundary condition: full buffer case with not enough space for last character

TEST_F(UTF16Swp_to_UTF8Test_2082, FullBufferNotEnoughSpace_2082) {

    // Setup: Input "😊" in UTF-16 (with swapped byte order)

    utf16In[0] = 0xD83D;  // High surrogate

    utf16In[1] = 0xDE0A;  // Low surrogate



    // Exercise

    UTF16Swp_to_UTF8(utf16In, 2, utf8Out, 3, &utf16Read, &utf8Written);



    // Verify

    EXPECT_EQ(utf16Read, 0);

    EXPECT_EQ(utf8Written, 0);

}



// Test exceptional case: invalid surrogate pair

TEST_F(UTF16Swp_to_UTF8Test_2082, InvalidSurrogatePair_2082) {

    // Setup: Input "H😊" but with only high surrogate in UTF-16 (with swapped byte order)

    utf16In[0] = 0x4800;  // 'H'

    utf16In[1] = 0xD83D;  // High surrogate



    // Exercise

    UTF16Swp_to_UTF8(utf16In, 2, utf8Out, kBufferSize, &utf16Read, &utf8Written);



    // Verify

    EXPECT_EQ(utf16Read, 1);

    EXPECT_EQ(utf8Written, 1);

    EXPECT_STREQ(reinterpret_cast<const char*>(utf8Out), "H");

}



// Test exceptional case: truncated surrogate pair at end of buffer

TEST_F(UTF16Swp_to_UTF8Test_2082, TruncatedSurrogatePair_2082) {

    // Setup: Input "😊" in UTF-16 (with swapped byte order), but input ends mid-surrogate

    utf16In[0] = 0xD83D;  // High surrogate



    // Exercise

    UTF16Swp_to_UTF8(utf16In, 1, utf8Out, kBufferSize, &utf16Read, &utf8Written);



    // Verify

    EXPECT_EQ(utf16Read, 0);

    EXPECT_EQ(utf8Written, 0);

}
