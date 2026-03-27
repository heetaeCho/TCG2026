#include <gtest/gtest.h>

#include "yaml-cpp/binary.h"



class BinaryTest_8 : public ::testing::Test {

protected:

    YAML::Binary defaultBinary;

    YAML::Binary ownedBinary;

    const unsigned char testData[3] = {0x01, 0x02, 0x03};

    YAML::Binary unownedBinary;



    BinaryTest_8() : ownedBinary(testData, 3), unownedBinary(testData, 3) {

        unownedBinary.swap(const_cast<std::vector<unsigned char>&>(unownedBinary.m_data));

        unownedBinary = YAML::Binary(testData, 3);

    }

};



TEST_F(BinaryTest_8, DefaultConstructorInitializesEmptyData_8) {

    EXPECT_EQ(defaultBinary.data(), nullptr);

    EXPECT_EQ(defaultBinary.size(), 0);

}



TEST_F(BinaryTest_8, OwnedConstructorSetsDataAndSizeCorrectly_8) {

    EXPECT_NE(ownedBinary.data(), nullptr);

    EXPECT_EQ(ownedBinary.size(), 3);

    for (std::size_t i = 0; i < ownedBinary.size(); ++i) {

        EXPECT_EQ(ownedBinary.data()[i], testData[i]);

    }

}



TEST_F(BinaryTest_8, UnownedConstructorSetsDataAndSizeCorrectly_8) {

    EXPECT_NE(unownedBinary.data(), nullptr);

    EXPECT_EQ(unownedBinary.size(), 3);

    for (std::size_t i = 0; i < unownedBinary.size(); ++i) {

        EXPECT_EQ(unownedBinary.data()[i], testData[i]);

    }

}



TEST_F(BinaryTest_8, OwnedDataReturnsTrueForOwnedBinary_8) {

    EXPECT_TRUE(ownedBinary.owned());

}



TEST_F(BinaryTest_8, UnownedDataReturnsFalseForUnownedBinary_8) {

    EXPECT_FALSE(unownedBinary.owned());

}



TEST_F(BinaryTest_8, EqualityOperatorComparesDataAndSize_8) {

    YAML::Binary sameOwnedBinary(testData, 3);

    YAML::Binary differentOwnedBinary(testData, 2);

    unsigned char differentData[3] = {0x01, 0x02, 0x04};

    YAML::Binary sameUnownedBinary(differentData, 3);



    EXPECT_EQ(ownedBinary, sameOwnedBinary);

    EXPECT_NE(ownedBinary, differentOwnedBinary);

    EXPECT_NE(ownedBinary, sameUnownedBinary);

}



TEST_F(BinaryTest_8, InequalityOperatorComparesDataAndSize_8) {

    YAML::Binary sameOwnedBinary(testData, 3);

    YAML::Binary differentOwnedBinary(testData, 2);

    unsigned char differentData[3] = {0x01, 0x02, 0x04};

    YAML::Binary sameUnownedBinary(differentData, 3);



    EXPECT_FALSE(ownedBinary != sameOwnedBinary);

    EXPECT_TRUE(ownedBinary != differentOwnedBinary);

    EXPECT_TRUE(ownedBinary != sameUnownedBinary);

}



TEST_F(BinaryTest_8, SwapExchangesDataWithVector_8) {

    std::vector<unsigned char> swapData = {0x10, 0x20, 0x30};

    ownedBinary.swap(swapData);



    EXPECT_EQ(ownedBinary.size(), 3);

    for (std::size_t i = 0; i < ownedBinary.size(); ++i) {

        EXPECT_EQ(ownedBinary.data()[i], swapData[i]);

    }

    EXPECT_TRUE(swapData.empty());

}
