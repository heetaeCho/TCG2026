#include <gtest/gtest.h>

#include "exiv2/value.hpp"



using namespace Exiv2;



class XmpValueTest_830 : public ::testing::Test {

protected:

    XmpValue xmpValue;

};



TEST_F(XmpValueTest_830, DefaultXmpStructIsNone_830) {

    EXPECT_EQ(xmpValue.xmpStruct(), xsNone);

}



TEST_F(XmpValueTest_830, SetXmpStructAndGetCorrectly_830) {

    xmpValue.setXmpStruct(xsSeq);

    EXPECT_EQ(xmpValue.xmpStruct(), xsSeq);

}



TEST_F(XmpValueTest_830, DefaultXmpArrayTypeIsNone_830) {

    EXPECT_EQ(xmpValue.xmpArrayType(), xaNone);

}



TEST_F(XmpValueTest_830, SetXmpArrayTypeAndGetCorrectly_830) {

    xmpValue.setXmpArrayType(xaBag);

    EXPECT_EQ(xmpValue.xmpArrayType(), xaBag);

}



TEST_F(XmpValueTest_830, SizeInitiallyZero_830) {

    EXPECT_EQ(xmpValue.size(), 0u);

}



// Assuming copy and read methods have some observable side effects on size

// Here we test if the size changes after a hypothetical successful operation



TEST_F(XmpValueTest_830, CopyMethodDoesNotChangeSizeWithoutData_830) {

    byte buffer[1] = {0};

    EXPECT_EQ(xmpValue.copy(buffer, static_cast<ByteOrder>(1)), 0u);

}



TEST_F(XmpValueTest_830, ReadFromBufferSetsSizeCorrectly_830) {

    const byte buffer[] = "test";

    size_t len = sizeof(buffer) - 1; // Exclude null terminator

    EXPECT_EQ(xmpValue.read(buffer, len, static_cast<ByteOrder>(1)), 0);

    EXPECT_EQ(xmpValue.size(), len);

}



TEST_F(XmpValueTest_830, ReadFromStringSetsSizeCorrectly_830) {

    std::string testString = "test";

    EXPECT_EQ(xmpValue.read(testString), 0);

    EXPECT_EQ(xmpValue.size(), testString.length());

}
