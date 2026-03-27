#include <gtest/gtest.h>

#include "tinyxml2.h"



namespace tinyxml2 {

    class XMLUtilTest_163 : public ::testing::Test {

    protected:

        char buffer[5]; // Enough to hold UTF-8 sequences up to 4 bytes

        int length;

    };



    TEST_F(XMLUtilTest_163, ConvertUTF32ToUTF8_Below80_163) {

        unsigned long input = 0x7F;

        XMLUtil::ConvertUTF32ToUTF8(input, buffer, &length);

        EXPECT_EQ(length, 1);

        EXPECT_EQ(buffer[0], static_cast<char>(input));

    }



    TEST_F(XMLUtilTest_163, ConvertUTF32ToUTF8_Below800_163) {

        unsigned long input = 0x7FF;

        XMLUtil::ConvertUTF32ToUTF8(input, buffer, &length);

        EXPECT_EQ(length, 2);

        EXPECT_EQ(buffer[0], static_cast<char>(0xC0 | (input >> 6)));

        EXPECT_EQ(buffer[1], static_cast<char>(0x80 | (input & 0x3F)));

    }



    TEST_F(XMLUtilTest_163, ConvertUTF32ToUTF8_Below10000_163) {

        unsigned long input = 0xFFFF;

        XMLUtil::ConvertUTF32ToUTF8(input, buffer, &length);

        EXPECT_EQ(length, 3);

        EXPECT_EQ(buffer[0], static_cast<char>(0xE0 | (input >> 12)));

        EXPECT_EQ(buffer[1], static_cast<char>(0x80 | ((input >> 6) & 0x3F)));

        EXPECT_EQ(buffer[2], static_cast<char>(0x80 | (input & 0x3F)));

    }



    TEST_F(XMLUtilTest_163, ConvertUTF32ToUTF8_Below200000_163) {

        unsigned long input = 0x1FFFF;

        XMLUtil::ConvertUTF32ToUTF8(input, buffer, &length);

        EXPECT_EQ(length, 4);

        EXPECT_EQ(buffer[0], static_cast<char>(0xF0 | (input >> 18)));

        EXPECT_EQ(buffer[1], static_cast<char>(0x80 | ((input >> 12) & 0x3F)));

        EXPECT_EQ(buffer[2], static_cast<char>(0x80 | ((input >> 6) & 0x3F)));

        EXPECT_EQ(buffer[3], static_cast<char>(0x80 | (input & 0x3F)));

    }



    TEST_F(XMLUtilTest_163, ConvertUTF32ToUTF8_OutOfRange_163) {

        unsigned long input = 0x200000;

        XMLUtil::ConvertUTF32ToUTF8(input, buffer, &length);

        EXPECT_EQ(length, 0); // Expected behavior as per implementation

    }



    TEST_F(XMLUtilTest_163, ConvertUTF32ToUTF8_Zero_163) {

        unsigned long input = 0x0;

        XMLUtil::ConvertUTF32ToUTF8(input, buffer, &length);

        EXPECT_EQ(length, 1);

        EXPECT_EQ(buffer[0], static_cast<char>(input));

    }



} // namespace tinyxml2
