#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/tags_int.hpp"

#include <sstream>



using namespace Exiv2;

using namespace Exiv2::Internal;



// Mock class for Value to simulate its behavior

class MockValue : public Value {

public:

    MOCK_METHOD(size_t, count, (), (const));

    MOCK_METHOD(uint32_t, toUint32, (size_t), (const));

};



TEST_F(PrintTagBitlistAllLETest_185, NormalOperation_185) {

    const TagDetailsBitlistSorted array[] = {{0, "Bit0"}, {1, "Bit1"}, {2, "Bit2"}};

    MockValue mockValue;

    std::ostringstream os;



    EXPECT_CALL(mockValue, count()).WillOnce(testing::Return(3));

    EXPECT_CALL(mockValue, toUint32(0)).WillOnce(testing::Return(0b00000101)); // Bit0 and Bit2

    EXPECT_CALL(mockValue, toUint32(1)).WillOnce(testing::Return(0b00000010)); // Bit1

    EXPECT_CALL(mockValue, toUint32(2)).WillOnce(testing::Return(0b00000000)); // No bits



    printTagBitlistAllLE(os, mockValue, nullptr);



    EXPECT_EQ(os.str(), "Bit0, Bit2, Bit1");

}



TEST_F(PrintTagBitlistAllLETest_185, AllBitsZero_185) {

    const TagDetailsBitlistSorted array[] = {{0, "Bit0"}, {1, "Bit1"}, {2, "Bit2"}};

    MockValue mockValue;

    std::ostringstream os;



    EXPECT_CALL(mockValue, count()).WillOnce(testing::Return(3));

    EXPECT_CALL(mockValue, toUint32(0)).WillOnce(testing::Return(0b00000000)); // No bits

    EXPECT_CALL(mockValue, toUint32(1)).WillOnce(testing::Return(0b00000000)); // No bits

    EXPECT_CALL(mockValue, toUint32(2)).WillOnce(testing::Return(0b00000000)); // No bits



    printTagBitlistAllLE(os, mockValue, nullptr);



    EXPECT_EQ(os.str(), "None");

}



TEST_F(PrintTagBitlistAllLETest_185, BeyondArrayValues_185) {

    const TagDetailsBitlistSorted array[] = {{0, "Bit0"}, {1, "Bit1"}};

    MockValue mockValue;

    std::ostringstream os;



    EXPECT_CALL(mockValue, count()).WillOnce(testing::Return(2));

    EXPECT_CALL(mockValue, toUint32(0)).WillOnce(testing::Return(0b00000100)); // Bit2

    EXPECT_CALL(mockValue, toUint32(1)).WillOnce(testing::Return(0b00000010)); // Bit1



    printTagBitlistAllLE(os, mockValue, nullptr);



    EXPECT_EQ(os.str(), "[2], Bit1");

}



TEST_F(PrintTagBitlistAllLETest_185, SingleBitSet_185) {

    const TagDetailsBitlistSorted array[] = {{0, "Bit0"}, {1, "Bit1"}};

    MockValue mockValue;

    std::ostringstream os;



    EXPECT_CALL(mockValue, count()).WillOnce(testing::Return(1));

    EXPECT_CALL(mockValue, toUint32(0)).WillOnce(testing::Return(0b00000001)); // Bit0



    printTagBitlistAllLE(os, mockValue, nullptr);



    EXPECT_EQ(os.str(), "Bit0");

}



TEST_F(PrintTagBitlistAllLETest_185, MultipleValuesWithBitsSet_185) {

    const TagDetailsBitlistSorted array[] = {{0, "Bit0"}, {1, "Bit1"}, {2, "Bit2"}};

    MockValue mockValue;

    std::ostringstream os;



    EXPECT_CALL(mockValue, count()).WillOnce(testing::Return(3));

    EXPECT_CALL(mockValue, toUint32(0)).WillOnce(testing::Return(0b00000101)); // Bit0 and Bit2

    EXPECT_CALL(mockValue, toUint32(1)).WillOnce(testing::Return(0b00000010)); // Bit1

    EXPECT_CALL(mockValue, toUint32(2)).WillOnce(testing::Return(0b00000100)); // Bit2



    printTagBitlistAllLE(os, mockValue, nullptr);



    EXPECT_EQ(os.str(), "Bit0, Bit2, Bit1, Bit2");

}



TEST_F(PrintTagBitlistAllLETest_185, NoValues_185) {

    const TagDetailsBitlistSorted array[] = {{0, "Bit0"}, {1, "Bit1"}};

    MockValue mockValue;

    std::ostringstream os;



    EXPECT_CALL(mockValue, count()).WillOnce(testing::Return(0));



    printTagBitlistAllLE(os, mockValue, nullptr);



    EXPECT_EQ(os.str(), "None");

}
