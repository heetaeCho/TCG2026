#include <gtest/gtest.h>

#include "XMP_Const.h"



// Assuming VerifySetOptions is declared in a header file that we include

extern XMP_OptionBits VerifySetOptions(XMP_OptionBits options, XMP_StringPtr propValue);



class VerifySetOptionsTest_1891 : public ::testing::Test {

protected:

    // You can add any setup or teardown code here if needed

};



TEST_F(VerifySetOptionsTest_1891, NormalOperation_NoFlags_1891) {

    EXPECT_EQ(VerifySetOptions(0, nullptr), 0);

}



TEST_F(VerifySetOptionsTest_1891, NormalOperation_SetArrayIsAltText_1891) {

    EXPECT_EQ(VerifySetOptions(kXMP_PropArrayIsAltText, nullptr), kXMP_PropArrayIsAltText | kXMP_PropArrayIsAlternate | kXMP_PropArrayIsOrdered | kXMP_PropValueIsArray);

}



TEST_F(VerifySetOptionsTest_1891, NormalOperation_SetArrayIsAlternate_1891) {

    EXPECT_EQ(VerifySetOptions(kXMP_PropArrayIsAlternate, nullptr), kXMP_PropArrayIsAlternate | kXMP_PropArrayIsOrdered | kXMP_PropValueIsArray);

}



TEST_F(VerifySetOptionsTest_1891, NormalOperation_SetArrayIsOrdered_1891) {

    EXPECT_EQ(VerifySetOptions(kXMP_PropArrayIsOrdered, nullptr), kXMP_PropArrayIsOrdered | kXMP_PropValueIsArray);

}



TEST_F(VerifySetOptionsTest_1891, BoundaryCondition_UnrecognizedFlags_1891) {

    EXPECT_THROW(VerifySetOptions(kXMP_AllSetOptionsMask + 1, nullptr), XMP_Error);

}



TEST_F(VerifySetOptionsTest_1891, Exceptional_IsStructAndIsArray_1891) {

    EXPECT_THROW(VerifySetOptions(kXMP_PropValueIsStruct | kXMP_PropValueIsArray, nullptr), XMP_Error);

}



TEST_F(VerifySetOptionsTest_1891, Exceptional_StructsWithValueOptions_1891) {

    EXPECT_THROW(VerifySetOptions(kXMP_PropValueIsStruct | kXMP_PropValueOptionsMask, nullptr), XMP_Error);

}



TEST_F(VerifySetOptionsTest_1891, Exceptional_ArraysWithValueOptions_1891) {

    EXPECT_THROW(VerifySetOptions(kXMP_PropValueIsArray | kXMP_PropValueOptionsMask, nullptr), XMP_Error);

}



TEST_F(VerifySetOptionsTest_1891, Exceptional_StructsWithStringValue_1891) {

    EXPECT_THROW(VerifySetOptions(kXMP_PropValueIsStruct, "Some String"), XMP_Error);

}



TEST_F(VerifySetOptionsTest_1891, Exceptional_ArraysWithStringValue_1891) {

    EXPECT_THROW(VerifySetOptions(kXMP_PropValueIsArray, "Some String"), XMP_Error);

}
