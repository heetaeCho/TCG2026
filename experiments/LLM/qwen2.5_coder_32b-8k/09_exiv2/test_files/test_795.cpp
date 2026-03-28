#include <gtest/gtest.h>

#include "value.cpp"



using namespace Exiv2;



class DataValueTest_795 : public ::testing::Test {

protected:

    void SetUp() override {

        // Initialize data for testing

        testData = {0x1, 0x2, 0x3, 0x4, 0x5};

        dataValue = DataValue();

        dataValue.value_ = testData;

    }



    std::vector<byte> testData;

    DataValue dataValue;

};



TEST_F(DataValueTest_795, CopyToBuffer_795) {

    // Arrange

    byte buffer[10] = {0};

    size_t expectedSize = testData.size();



    // Act

    size_t result = dataValue.copy(buffer, ByteOrder::big);



    // Assert

    EXPECT_EQ(result, expectedSize);

    for (size_t i = 0; i < testData.size(); ++i) {

        EXPECT_EQ(buffer[i], testData[i]);

    }

}



TEST_F(DataValueTest_795, CopyToSmallBuffer_795) {

    // Arrange

    byte buffer[3] = {0};

    size_t expectedSize = sizeof(buffer);



    // Act

    size_t result = dataValue.copy(buffer, ByteOrder::big);



    // Assert

    EXPECT_EQ(result, expectedSize);

    for (size_t i = 0; i < expectedSize; ++i) {

        EXPECT_EQ(buffer[i], testData[i]);

    }

}



TEST_F(DataValueTest_795, CopyToEmptyBuffer_795) {

    // Arrange

    byte buffer[0];

    size_t expectedSize = 0;



    // Act

    size_t result = dataValue.copy(buffer, ByteOrder::big);



    // Assert

    EXPECT_EQ(result, expectedSize);

}



TEST_F(DataValueTest_795, CopyWithDifferentByteOrder_795) {

    // Arrange

    byte buffer[10] = {0};

    size_t expectedSize = testData.size();



    // Act

    size_t resultBigEndian = dataValue.copy(buffer, ByteOrder::big);

    std::fill(std::begin(buffer), std::end(buffer), 0);

    size_t resultLittleEndian = dataValue.copy(buffer, ByteOrder::little);



    // Assert

    EXPECT_EQ(resultBigEndian, expectedSize);

    EXPECT_EQ(resultLittleEndian, expectedSize);

    for (size_t i = 0; i < testData.size(); ++i) {

        EXPECT_EQ(testData[i], buffer[i]);

    }

}
