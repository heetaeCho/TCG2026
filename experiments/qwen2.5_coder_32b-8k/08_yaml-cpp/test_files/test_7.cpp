#include <gtest/gtest.h>

#include <yaml-cpp/binary.h>



class BinaryTest_7 : public ::testing::Test {

protected:

    YAML::Binary emptyBinary;

    YAML::Binary ownedBinary;

    std::vector<unsigned char> data = {0x01, 0x02, 0x03};

    YAML::Binary unownedBinary{data.data(), data.size()};

    

    BinaryTest_7() : ownedBinary(data.data(), data.size()) {}

};



TEST_F(BinaryTest_7, DefaultConstructorCreatesEmptyBinary_7) {

    EXPECT_EQ(emptyBinary.size(), 0);

}



TEST_F(BinaryTest_7, OwnedBinaryReportsCorrectSize_7) {

    EXPECT_EQ(ownedBinary.size(), data.size());

}



TEST_F(BinaryTest_7, UnownedBinaryReportsCorrectSize_7) {

    EXPECT_EQ(unownedBinary.size(), data.size());

}



TEST_F(BinaryTest_7, OwnedBinaryDataMatchesConstructedData_7) {

    const unsigned char* ownedData = ownedBinary.data();

    for (std::size_t i = 0; i < data.size(); ++i) {

        EXPECT_EQ(ownedData[i], data[i]);

    }

}



TEST_F(BinaryTest_7, UnownedBinaryDataMatchesConstructedData_7) {

    const unsigned char* unownedData = unownedBinary.data();

    for (std::size_t i = 0; i < data.size(); ++i) {

        EXPECT_EQ(unownedData[i], data[i]);

    }

}



TEST_F(BinaryTest_7, EqualityOperatorReturnsTrueForEqualBinaries_7) {

    YAML::Binary anotherOwnedBinary{data.data(), data.size()};

    EXPECT_TRUE(ownedBinary == anotherOwnedBinary);

}



TEST_F(BinaryTest_7, InequalityOperatorReturnsFalseForEqualBinaries_7) {

    YAML::Binary anotherOwnedBinary{data.data(), data.size()};

    EXPECT_FALSE(ownedBinary != anotherOwnedBinary);

}



TEST_F(BinaryTest_7, EqualityOperatorReturnsFalseForDifferentBinaries_7) {

    std::vector<unsigned char> differentData = {0x04, 0x05};

    YAML::Binary differentBinary{differentData.data(), differentData.size()};

    EXPECT_FALSE(ownedBinary == differentBinary);

}



TEST_F(BinaryTest_7, InequalityOperatorReturnsTrueForDifferentBinaries_7) {

    std::vector<unsigned char> differentData = {0x04, 0x05};

    YAML::Binary differentBinary{differentData.data(), differentData.size()};

    EXPECT_TRUE(ownedBinary != differentBinary);

}



TEST_F(BinaryTest_7, OwnedBinaryIsOwned_7) {

    EXPECT_TRUE(ownedBinary.owned());

}



TEST_F(BinaryTest_7, UnownedBinaryIsNotOwned_7) {

    EXPECT_FALSE(unownedBinary.owned());

}
