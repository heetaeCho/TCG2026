#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/value.hpp"



using namespace Exiv2;

using ::testing::_;

using ::testing::Return;



class ValueTest_127 : public ::testing::Test {

protected:

    std::unique_ptr<Value> value;



    void SetUp() override {

        value = Value::create(TypeId::invalidTypeId); // Assuming TypeId::invalidTypeId is a valid type for testing

    }

};



TEST_F(ValueTest_127, OkReturnsTrueByDefault_127) {

    EXPECT_TRUE(value->ok());

}



TEST_F(ValueTest_127, ReadWithBufferAndLengthReturnsZeroForInvalidData_127) {

    byte buffer[] = {0x00};

    EXPECT_EQ(value->read(buffer, sizeof(buffer), ByteOrder::littleEndian), 0);

}



TEST_F(ValueTest_127, ReadWithStringBufferReturnsZeroForInvalidData_127) {

    std::string buffer = "test";

    EXPECT_EQ(value->read(buffer), 0);

}



TEST_F(ValueTest_127, SetDataAreaWithBufferAndLengthReturnsSuccess_127) {

    byte buffer[] = {0x00};

    EXPECT_EQ(value->setDataArea(buffer, sizeof(buffer)), 0);

}



TEST_F(ValueTest_127, CopyWithDataBufferReturnsZeroForInvalidData_127) {

    byte buffer[] = {0x00};

    EXPECT_EQ(value->copy(buffer, ByteOrder::littleEndian), 0);

}



TEST_F(ValueTest_127, CountReturnsZeroForDefaultInstance_127) {

    EXPECT_EQ(value->count(), 0);

}



TEST_F(ValueTest_127, SizeReturnsZeroForDefaultInstance_127) {

    EXPECT_EQ(value->size(), 0);

}



TEST_F(ValueTest_127, WriteToStreamReturnsReferenceToStream_127) {

    std::ostringstream oss;

    EXPECT_EQ(&value->write(oss), &oss);

}



TEST_F(ValueTest_127, ToStringReturnsEmptyStringForDefaultInstance_127) {

    EXPECT_EQ(value->toString(), "");

}



TEST_F(ValueTest_127, ToStringWithIndexReturnsEmptyStringForDefaultInstance_127) {

    EXPECT_EQ(value->toString(0), "");

}



TEST_F(ValueTest_127, ToInt64ReturnsZeroForDefaultInstance_127) {

    EXPECT_EQ(value->toInt64(0), 0);

}



TEST_F(ValueTest_127, ToUint32ReturnsZeroForDefaultInstance_127) {

    EXPECT_EQ(value->toUint32(0), 0);

}



TEST_F(ValueTest_127, ToFloatReturnsZeroForDefaultInstance_127) {

    EXPECT_FLOAT_EQ(value->toFloat(0), 0.0f);

}



TEST_F(ValueTest_127, ToRationalThrowsExceptionForInvalidData_127) {

    EXPECT_THROW(value->toRational(0), std::exception);

}



TEST_F(ValueTest_127, SizeDataAreaReturnsZeroForDefaultInstance_127) {

    EXPECT_EQ(value->sizeDataArea(), 0);

}



TEST_F(ValueTest_127, DataAreaReturnsEmptyBufferForDefaultInstance_127) {

    EXPECT_TRUE(value->dataArea().pData == nullptr && value->dataArea().size_ == 0);

}



TEST_F(ValueTest_127, CreateWithInvalidTypeIdReturnsUniquePtrToValue_127) {

    std::unique_ptr<Value> createdValue = Value::create(TypeId::invalidTypeId);

    EXPECT_NE(createdValue.get(), nullptr);

}
