#include <gtest/gtest.h>

#include "UnicodeConversions.cpp"



class UTF16Nat_to_UTF32NatTest_2074 : public ::testing::Test {

protected:

    void SetUp() override {

        utf16In = new UTF16Unit[10];

        utf32Out = new UTF32Unit[10];

        utf16Read = new size_t;

        utf32Written = new size_t;

    }



    void TearDown() override {

        delete[] utf16In;

        delete[] utf32Out;

        delete utf16Read;

        delete utf32Written;

    }



    UTF16Unit* utf16In;

    UTF32Unit* utf32Out;

    size_t* utf16Read;

    size_t* utf32Written;

};



TEST_F(UTF16Nat_to_UTF32NatTest_2074, NormalOperation_2074) {

    utf16In[0] = 0x0041; // 'A'

    utf16In[1] = 0x0042; // 'B'

    utf16In[2] = 0x0043; // 'C'



    UTF16Nat_to_UTF32Nat(utf16In, 3, utf32Out, 3, utf16Read, utf32Written);



    EXPECT_EQ(*utf16Read, 3);

    EXPECT_EQ(*utf32Written, 3);

    EXPECT_EQ(utf32Out[0], 0x0041);

    EXPECT_EQ(utf32Out[1], 0x0042);

    EXPECT_EQ(utf32Out[2], 0x0043);

}



TEST_F(UTF16Nat_to_UTF32NatTest_2074, BoundaryCondition_Utf16ShorterThanUtf32_2074) {

    utf16In[0] = 0x0041; // 'A'

    utf16In[1] = 0x0042; // 'B'



    UTF16Nat_to_UTF32Nat(utf16In, 2, utf32Out, 5, utf16Read, utf32Written);



    EXPECT_EQ(*utf16Read, 2);

    EXPECT_EQ(*utf32Written, 2);

    EXPECT_EQ(utf32Out[0], 0x0041);

    EXPECT_EQ(utf32Out[1], 0x0042);

}



TEST_F(UTF16Nat_to_UTF32NatTest_2074, BoundaryCondition_Utf32ShorterThanUtf16_2074) {

    utf16In[0] = 0x0041; // 'A'

    utf16In[1] = 0x0042; // 'B'



    UTF16Nat_to_UTF32Nat(utf16In, 5, utf32Out, 2, utf16Read, utf32Written);



    EXPECT_EQ(*utf16Read, 2);

    EXPECT_EQ(*utf32Written, 2);

    EXPECT_EQ(utf32Out[0], 0x0041);

    EXPECT_EQ(utf32Out[1], 0x0042);

}



TEST_F(UTF16Nat_to_UTF32NatTest_2074, SurrogatePairConversion_2074) {

    utf16In[0] = 0xD800; // High surrogate

    utf16In[1] = 0xDC00; // Low surrogate



    UTF16Nat_to_UTF32Nat(utf16In, 2, utf32Out, 1, utf16Read, utf32Written);



    EXPECT_EQ(*utf16Read, 2);

    EXPECT_EQ(*utf32Written, 1);

}



TEST_F(UTF16Nat_to_UTF32NatTest_2074, IncompleteSurrogatePairAtEnd_2074) {

    utf16In[0] = 0xD800; // High surrogate



    UTF16Nat_to_UTF32Nat(utf16In, 1, utf32Out, 1, utf16Read, utf32Written);



    EXPECT_EQ(*utf16Read, 0);

    EXPECT_EQ(*utf32Written, 0);

}



TEST_F(UTF16Nat_to_UTF32NatTest_2074, MixedContentConversion_2074) {

    utf16In[0] = 0x0041; // 'A'

    utf16In[1] = 0xD800; // High surrogate

    utf16In[2] = 0xDC00; // Low surrogate

    utf16In[3] = 0x0042; // 'B'



    UTF16Nat_to_UTF32Nat(utf16In, 4, utf32Out, 4, utf16Read, utf32Written);



    EXPECT_EQ(*utf16Read, 4);

    EXPECT_EQ(*utf32Written, 4);

    EXPECT_EQ(utf32Out[0], 0x0041);

    EXPECT_EQ(utf32Out[1], 0x10000); // Expected UTF-32 code point

    EXPECT_EQ(utf32Out[2], 0x0042);

}



TEST_F(UTF16Nat_to_UTF32NatTest_2074, InvalidHighSurrogateOnly_2074) {

    utf16In[0] = 0xD800; // High surrogate



    UTF16Nat_to_UTF32Nat(utf16In, 1, utf32Out, 1, utf16Read, utf32Written);



    EXPECT_EQ(*utf16Read, 0);

    EXPECT_EQ(*utf32Written, 0);

}



TEST_F(UTF16Nat_to_UTF32NatTest_2074, InvalidLowSurrogateOnly_2074) {

    utf16In[0] = 0xDC00; // Low surrogate



    UTF16Nat_to_UTF32Nat(utf16In, 1, utf32Out, 1, utf16Read, utf32Written);



    EXPECT_EQ(*utf16Read, 1);

    EXPECT_EQ(*utf32Written, 1);

    EXPECT_EQ(utf32Out[0], 0xDC00); // Invalid surrogate pair treated as single UTF-32 code point

}
