#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "makernote_int.cpp"



using namespace Exiv2::Internal;



class SonyMnHeaderTest_1501 : public ::testing::Test {

protected:

    SonyMnHeader header;

};



TEST_F(SonyMnHeaderTest_1501, ReadValidData_1501) {

    const byte data[] = { 'S', 'o', 'n', 'y' };

    EXPECT_TRUE(header.read(data, sizeof(data), littleEndian));

}



TEST_F(SonyMnHeaderTest_1501, ReadNullPointer_1501) {

    EXPECT_FALSE(header.read(nullptr, 4, littleEndian));

}



TEST_F(SonyMnHeaderTest_1501, ReadInsufficientSize_1501) {

    const byte data[] = { 'S', 'o' };

    EXPECT_FALSE(header.read(data, sizeof(data), littleEndian));

}



TEST_F(SonyMnHeaderTest_1501, ReadIncorrectSignature_1501) {

    const byte data[] = { 'X', 'i', 'x', '2' };

    EXPECT_FALSE(header.read(data, sizeof(data), littleEndian));

}



TEST_F(SonyMnHeaderTest_1501, ReadCorrectSizeAndSignature_1501) {

    const byte data[] = { 'S', 'o', 'n', 'y' };

    EXPECT_TRUE(header.read(data, sizeof(data), littleEndian));

}



// Assuming signature size is 4 bytes as per the example data

TEST_F(SonyMnHeaderTest_1501, ReadExactSignatureSize_1501) {

    const byte data[] = { 'S', 'o', 'n', 'y' };

    EXPECT_TRUE(header.read(data, 4, littleEndian));

}



TEST_F(SonyMnHeaderTest_1501, ReadLargerThanSignatureSize_1501) {

    const byte data[] = { 'S', 'o', 'n', 'y', 'e', 'x', 't' };

    EXPECT_TRUE(header.read(data, sizeof(data), littleEndian));

}
