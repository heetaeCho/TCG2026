#include <gtest/gtest.h>

#include <gmock/gmock.h>



extern "C" {

    static int getCharFromString(void *data);

}



class CharCodeToUnicodeTest_1879 : public ::testing::Test {

protected:

    unsigned char testData[4];

    void* dataPtr;



    void SetUp() override {

        dataPtr = &testData;

    }

};



TEST_F(CharCodeToUnicodeTest_1879, NormalOperationSingleChar_1879) {

    testData[0] = 'A';

    testData[1] = '\0';



    EXPECT_EQ(getCharFromString(dataPtr), 'A');

    EXPECT_EQ(getCharFromString(dataPtr), EOF);

}



TEST_F(CharCodeToUnicodeTest_1879, NormalOperationMultipleChars_1879) {

    testData[0] = 'H';

    testData[1] = 'e';

    testData[2] = 'l';

    testData[3] = '\0';



    EXPECT_EQ(getCharFromString(dataPtr), 'H');

    EXPECT_EQ(getCharFromString(dataPtr), 'e');

    EXPECT_EQ(getCharFromString(dataPtr), 'l');

    EXPECT_EQ(getCharFromString(dataPtr), EOF);

}



TEST_F(CharCodeToUnicodeTest_1879, BoundaryConditionEmptyString_1879) {

    testData[0] = '\0';



    EXPECT_EQ(getCharFromString(dataPtr), EOF);

}



TEST_F(CharCodeToUnicodeTest_1879, BoundaryConditionSingleNullByte_1879) {

    testData[0] = 0x00;

    testData[1] = '\0';



    EXPECT_EQ(getCharFromString(dataPtr), 0x00);

    EXPECT_EQ(getCharFromString(dataPtr), EOF);

}



TEST_F(CharCodeToUnicodeTest_1879, ExceptionalCaseNullDataPointer_1879) {

    dataPtr = nullptr;



    EXPECT_EQ(getCharFromString(dataPtr), EOF);

}
