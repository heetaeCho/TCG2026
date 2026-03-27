#include <gtest/gtest.h>

#include "exiv2/value.hpp"



using namespace Exiv2;



class DataValueTest_792 : public ::testing::Test {

protected:

    DataValue* dataValue;



    void SetUp() override {

        dataValue = new DataValue(TypeId::asciiString);

    }



    void TearDown() override {

        delete dataValue;

    }

};



TEST_F(DataValueTest_792, CountReturnsZeroInitially_792) {

    EXPECT_EQ(dataValue->count(), 0);

}



TEST_F(DataValueTest_792, SizeReturnsZeroInitially_792) {

    EXPECT_EQ(dataValue->size(), 0);

}



TEST_F(DataValueTest_792, ReadFromBufferSetsCount_792) {

    const byte buffer[] = "test";

    dataValue->read(buffer, sizeof(buffer), ByteOrder::littleEndian);

    EXPECT_EQ(dataValue->count(), 1); // Assuming a single item is read

}



TEST_F(DataValueTest_792, ReadFromStringSetsCount_792) {

    dataValue->read("test");

    EXPECT_EQ(dataValue->count(), 1); // Assuming a single item is read

}



TEST_F(DataValueTest_792, CopyToBufferReturnsCorrectSize_792) {

    byte buffer[5];

    const size_t copied = dataValue->copy(buffer, ByteOrder::littleEndian);

    EXPECT_EQ(copied, 0); // Assuming no data to copy initially

}



TEST_F(DataValueTest_792, WriteToStreamDoesNotThrow_792) {

    std::ostringstream os;

    ASSERT_NO_THROW(dataValue->write(os));

}



TEST_F(DataValueTest_792, ToStringReturnsEmptyStringInitially_792) {

    EXPECT_EQ(dataValue->toString(0), "");

}



TEST_F(DataValueTest_792, ToInt64ThrowsForInvalidIndex_792) {

    EXPECT_THROW(dataValue->toInt64(0), Error); // Assuming out-of-range access throws

}



TEST_F(DataValueTest_792, ToUint32ThrowsForInvalidIndex_792) {

    EXPECT_THROW(dataValue->toUint32(0), Error); // Assuming out-of-range access throws

}



TEST_F(DataValueTest_792, ToFloatThrowsForInvalidIndex_792) {

    EXPECT_THROW(dataValue->toFloat(0), Error); // Assuming out-of-range access throws

}



TEST_F(DataValueTest_792, ToRationalThrowsForInvalidIndex_792) {

    EXPECT_THROW(dataValue->toRational(0), Error); // Assuming out-of-range access throws

}
