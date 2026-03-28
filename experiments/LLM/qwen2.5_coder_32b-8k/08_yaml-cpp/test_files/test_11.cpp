#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "yaml-cpp/binary.h"



using namespace YAML;



class BinaryTest_11 : public ::testing::Test {

protected:

    const unsigned char data1[3] = {0x01, 0x02, 0x03};

    const unsigned char data2[3] = {0x04, 0x05, 0x06};



    Binary binaryDefault;

    Binary binaryWithData1;

    Binary binaryWithData2;



    BinaryTest_11() : binaryDefault(), binaryWithData1(data1, 3), binaryWithData2(data2, 3) {}

};



TEST_F(BinaryTest_11, DefaultConstructorInitializesEmptyData_11) {

    EXPECT_EQ(binaryDefault.size(), 0);

    EXPECT_TRUE(binaryDefault.data() == nullptr);

}



TEST_F(BinaryTest_11, DataConstructorSetsCorrectSizeAndData_11) {

    EXPECT_EQ(binaryWithData1.size(), 3);

    EXPECT_EQ(memcmp(binaryWithData1.data(), data1, 3), 0);

}



TEST_F(BinaryTest_11, CopyConstructorCopiesData_11) {

    Binary binaryCopy = binaryWithData1;

    EXPECT_EQ(binaryCopy.size(), binaryWithData1.size());

    EXPECT_EQ(memcmp(binaryCopy.data(), binaryWithData1.data(), binaryWithData1.size()), 0);

}



TEST_F(BinaryTest_11, MoveConstructorTransfersOwnership_11) {

    Binary binaryMove = std::move(binaryWithData1);

    EXPECT_EQ(binaryMove.size(), 3);

    EXPECT_EQ(memcmp(binaryMove.data(), data1, 3), 0);

    // Original should be empty or in a valid state

    EXPECT_TRUE(binaryWithData1.data() == nullptr || binaryWithData1.size() == 0);

}



TEST_F(BinaryTest_11, CopyAssignmentOperatorCopiesData_11) {

    Binary binaryCopy;

    binaryCopy = binaryWithData1;

    EXPECT_EQ(binaryCopy.size(), binaryWithData1.size());

    EXPECT_EQ(memcmp(binaryCopy.data(), binaryWithData1.data(), binaryWithData1.size()), 0);

}



TEST_F(BinaryTest_11, MoveAssignmentOperatorTransfersOwnership_11) {

    Binary binaryMove;

    binaryMove = std::move(binaryWithData1);

    EXPECT_EQ(binaryMove.size(), 3);

    EXPECT_EQ(memcmp(binaryMove.data(), data1, 3), 0);

    // Original should be empty or in a valid state

    EXPECT_TRUE(binaryWithData1.data() == nullptr || binaryWithData1.size() == 0);

}



TEST_F(BinaryTest_11, SwapExchangesDataBetweenBinaries_11) {

    std::vector<unsigned char> temp = {0x07, 0x08, 0x09};

    binaryDefault.swap(temp);

    EXPECT_EQ(binaryDefault.size(), 3);

    EXPECT_EQ(memcmp(binaryDefault.data(), temp.data(), 3), 0);

    EXPECT_TRUE(temp.empty());

}



TEST_F(BinaryTest_11, EqualOperatorReturnsTrueForSameData_11) {

    Binary binaryCopy(data1, 3);

    EXPECT_TRUE(binaryWithData1 == binaryCopy);

}



TEST_F(BinaryTest_11, EqualOperatorReturnsFalseForDifferentData_11) {

    EXPECT_FALSE(binaryWithData1 == binaryWithData2);

}



TEST_F(BinaryTest_11, NotEqualOperatorReturnsTrueForDifferentData_11) {

    EXPECT_TRUE(binaryWithData1 != binaryWithData2);

}



TEST_F(BinaryTest_11, NotEqualOperatorReturnsFalseForSameData_11) {

    Binary binaryCopy(data1, 3);

    EXPECT_FALSE(binaryWithData1 != binaryCopy);

}
