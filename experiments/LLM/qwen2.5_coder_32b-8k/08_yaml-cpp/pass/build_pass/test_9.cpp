#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "yaml-cpp/binary.h"



using namespace YAML;



class BinaryTest_9 : public ::testing::Test {

protected:

    Binary emptyBinary;

    std::vector<unsigned char> data = {1, 2, 3, 4, 5};

    Binary ownedBinary = Binary(data.data(), data.size());

};



TEST_F(BinaryTest_9, SwapWithEmptyVector_9) {

    std::vector<unsigned char> rhs;

    emptyBinary.swap(rhs);

    EXPECT_TRUE(emptyBinary.owned());

    EXPECT_EQ(emptyBinary.size(), 0);

    EXPECT_TRUE(rhs.empty());

}



TEST_F(BinaryTest_9, SwapWithNonEmptyVectorOwnedData_9) {

    std::vector<unsigned char> rhs = {10, 20, 30};

    ownedBinary.swap(rhs);

    EXPECT_TRUE(ownedBinary.owned());

    EXPECT_EQ(ownedBinary.size(), rhs.size());

    EXPECT_EQ(std::vector<unsigned char>(ownedBinary.data(), ownedBinary.data() + ownedBinary.size()), rhs);

    EXPECT_EQ(rhs.size(), data.size());

    EXPECT_EQ(rhs, data);

}



TEST_F(BinaryTest_9, SwapWithNonEmptyVectorUnownedData_9) {

    Binary unownedBinary(data.data(), data.size());

    std::vector<unsigned char> rhs = {10, 20, 30};

    unownedBinary.swap(rhs);

    EXPECT_TRUE(unownedBinary.owned());

    EXPECT_EQ(unownedBinary.size(), rhs.size());

    EXPECT_EQ(std::vector<unsigned char>(unownedBinary.data(), unownedBinary.data() + unownedBinary.size()), rhs);

    EXPECT_EQ(rhs.size(), data.size());

    EXPECT_EQ(rhs, data);

}



TEST_F(BinaryTest_9, SwapWithSameVectorOwnedData_9) {

    std::vector<unsigned char> rhs = {1, 2, 3, 4, 5};

    ownedBinary.swap(rhs);

    EXPECT_TRUE(ownedBinary.owned());

    EXPECT_EQ(ownedBinary.size(), rhs.size());

    EXPECT_EQ(std::vector<unsigned char>(ownedBinary.data(), ownedBinary.data() + ownedBinary.size()), rhs);

    EXPECT_TRUE(rhs.empty());

}



TEST_F(BinaryTest_9, SwapWithSameVectorUnownedData_9) {

    Binary unownedBinary(data.data(), data.size());

    std::vector<unsigned char> rhs = {1, 2, 3, 4, 5};

    unownedBinary.swap(rhs);

    EXPECT_TRUE(unownedBinary.owned());

    EXPECT_EQ(unownedBinary.size(), rhs.size());

    EXPECT_EQ(std::vector<unsigned char>(unownedBinary.data(), unownedBinary.data() + unownedBinary.size()), rhs);

    EXPECT_TRUE(rhs.empty());

}
