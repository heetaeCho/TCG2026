#include <gtest/gtest.h>

#include "yaml-cpp/binary.h"



using namespace YAML;



class BinaryTest_6 : public ::testing::Test {

protected:

    Binary ownedBinary;

    const unsigned char data[] = {0x1, 0x2, 0x3};

    Binary unownedBinary = Binary(data, sizeof(data));

};



TEST_F(BinaryTest_6, OwnedConstructor_Default_6) {

    EXPECT_TRUE(ownedBinary.owned());

}



TEST_F(BinaryTest_6, OwnedConstructor_UnownedData_6) {

    EXPECT_FALSE(unownedBinary.owned());

}



TEST_F(BinaryTest_6, Size_ReturnsCorrectSizeOwned_6) {

    std::vector<unsigned char> vec = {0x1, 0x2, 0x3};

    Binary binary(vec.data(), vec.size());

    EXPECT_EQ(binary.size(), vec.size());

}



TEST_F(BinaryTest_6, Size_ReturnsCorrectSizeUnowned_6) {

    EXPECT_EQ(unownedBinary.size(), sizeof(data));

}



TEST_F(BinaryTest_6, Data_ReturnsCorrectPointerOwned_6) {

    std::vector<unsigned char> vec = {0x1, 0x2, 0x3};

    Binary binary(vec.data(), vec.size());

    EXPECT_EQ(binary.data(), vec.data());

}



TEST_F(BinaryTest_6, Data_ReturnsCorrectPointerUnowned_6) {

    EXPECT_EQ(unownedBinary.data(), data);

}



TEST_F(BinaryTest_6, Equality_OwnedSameData_6) {

    std::vector<unsigned char> vec = {0x1, 0x2, 0x3};

    Binary binary1(vec.data(), vec.size());

    Binary binary2(vec.data(), vec.size());

    EXPECT_TRUE(binary1 == binary2);

}



TEST_F(BinaryTest_6, Equality_UnownedSameData_6) {

    Binary binary1(data, sizeof(data));

    Binary binary2(data, sizeof(data));

    EXPECT_TRUE(binary1 == binary2);

}



TEST_F(BinaryTest_6, Inequality_OwnedDifferentData_6) {

    std::vector<unsigned char> vec1 = {0x1, 0x2, 0x3};

    std::vector<unsigned char> vec2 = {0x4, 0x5, 0x6};

    Binary binary1(vec1.data(), vec1.size());

    Binary binary2(vec2.data(), vec2.size());

    EXPECT_TRUE(binary1 != binary2);

}



TEST_F(BinaryTest_6, Inequality_UnownedDifferentData_6) {

    const unsigned char data2[] = {0x4, 0x5, 0x6};

    Binary binary1(data, sizeof(data));

    Binary binary2(data2, sizeof(data2));

    EXPECT_TRUE(binary1 != binary2);

}



TEST_F(BinaryTest_6, Inequality_DifferentSize_6) {

    std::vector<unsigned char> vec = {0x1, 0x2, 0x3};

    Binary binary1(vec.data(), vec.size());

    Binary binary2(data, sizeof(data) - 1);

    EXPECT_TRUE(binary1 != binary2);

}



TEST_F(BinaryTest_6, Swap_ChangesData_6) {

    std::vector<unsigned char> vec = {0x1, 0x2, 0x3};

    ownedBinary.swap(vec);

    EXPECT_EQ(ownedBinary.data(), vec.data());

    EXPECT_EQ(ownedBinary.size(), vec.size());

}
