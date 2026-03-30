#include <gtest/gtest.h>

#include <yaml-cpp/binary.h>



namespace YAML {



class BinaryTest_10 : public ::testing::Test {

protected:

    Binary emptyBinary;

    Binary smallBinary;

    Binary largeBinary;



    static const unsigned char smallData[3];

    static const unsigned char largeData[5];



    BinaryTest_10()

        : smallBinary(smallData, 3),

          largeBinary(largeData, 5) {}

};



const unsigned char BinaryTest_10::smallData[3] = {0x01, 0x02, 0x03};

const unsigned char BinaryTest_10::largeData[5] = {0x10, 0x11, 0x12, 0x13, 0x14};



TEST_F(BinaryTest_10, DefaultConstructorCreatesEmptyBinary_10) {

    EXPECT_EQ(emptyBinary.size(), 0);

    EXPECT_EQ(emptyBinary.data(), nullptr);

}



TEST_F(BinaryTest_10, ParameterizedConstructorSetsDataAndSize_10) {

    EXPECT_EQ(smallBinary.size(), 3);

    EXPECT_NE(smallBinary.data(), nullptr);

    for (size_t i = 0; i < smallBinary.size(); ++i) {

        EXPECT_EQ(*(smallBinary.data() + i), smallData[i]);

    }

}



TEST_F(BinaryTest_10, CopyConstructorCreatesIdenticalObject_10) {

    Binary copy(smallBinary);

    EXPECT_EQ(copy.size(), smallBinary.size());

    for (size_t i = 0; i < copy.size(); ++i) {

        EXPECT_EQ(*(copy.data() + i), *(smallBinary.data() + i));

    }

}



TEST_F(BinaryTest_10, MoveConstructorTransfersOwnership_10) {

    Binary original(largeBinary);

    Binary moved(std::move(original));

    EXPECT_EQ(moved.size(), largeBinary.size());

    for (size_t i = 0; i < moved.size(); ++i) {

        EXPECT_EQ(*(moved.data() + i), *(largeBinary.data() + i));

    }

    EXPECT_EQ(original.size(), 0);

}



TEST_F(BinaryTest_10, CopyAssignmentOperatorCreatesIdenticalObject_10) {

    Binary copy;

    copy = smallBinary;

    EXPECT_EQ(copy.size(), smallBinary.size());

    for (size_t i = 0; i < copy.size(); ++i) {

        EXPECT_EQ(*(copy.data() + i), *(smallBinary.data() + i));

    }

}



TEST_F(BinaryTest_10, MoveAssignmentOperatorTransfersOwnership_10) {

    Binary original(largeBinary);

    Binary moved;

    moved = std::move(original);

    EXPECT_EQ(moved.size(), largeBinary.size());

    for (size_t i = 0; i < moved.size(); ++i) {

        EXPECT_EQ(*(moved.data() + i), *(largeBinary.data() + i));

    }

    EXPECT_EQ(original.size(), 0);

}



TEST_F(BinaryTest_10, EqualOperatorReturnsTrueForIdenticalBinaries_10) {

    Binary copy(smallBinary);

    EXPECT_TRUE(copy == smallBinary);

}



TEST_F(BinaryTest_10, EqualOperatorReturnsFalseForDifferentSizeBinaries_10) {

    EXPECT_FALSE(emptyBinary == smallBinary);

}



TEST_F(BinaryTest_10, EqualOperatorReturnsFalseForDifferentDataBinaries_10) {

    Binary different(smallData + 1, 2); // Different data

    EXPECT_FALSE(different == smallBinary);

}



TEST_F(BinaryTest_10, NotEqualOperatorReturnsTrueForDifferentBinaries_10) {

    Binary different(smallData + 1, 2); // Different data

    EXPECT_TRUE(different != smallBinary);

}



TEST_F(BinaryTest_10, NotEqualOperatorReturnsFalseForIdenticalBinaries_10) {

    Binary copy(smallBinary);

    EXPECT_FALSE(copy != smallBinary);

}

} // namespace YAML
