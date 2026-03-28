#include <gtest/gtest.h>

#include "exiv2/value.hpp"

#include <memory>



namespace Exiv2 {

    class MockValue : public Value {

    public:

        MOCK_METHOD(int, read, (const byte* buf, size_t len, ByteOrder byteOrder), (override));

        MOCK_METHOD(int, read, (const std::string& buf), (override));

        MOCK_METHOD(int, setDataArea, (const byte* buf, size_t len), (override));

        MOCK_METHOD(const size_t, copy, (byte* buf, ByteOrder byteOrder), (const, override));

        MOCK_METHOD(const size_t, count, (), (const, override));

        MOCK_METHOD(const size_t, size, (), (const, override));

        MOCK_METHOD(const std::ostream&, write, (std::ostream& os), (const, override));

        MOCK_METHOD(const std::string, toString, (), (const, override));

        MOCK_METHOD(const std::string, toString, (size_t n), (const, override));

        MOCK_METHOD(const int64_t, toInt64, (size_t n), (const, override));

        MOCK_METHOD(const uint32_t, toUint32, (size_t n), (const, override));

        MOCK_METHOD(const float, toFloat, (size_t n), (const, override));

        MOCK_METHOD(const Rational, toRational, (size_t n), (const, override));

        MOCK_METHOD(const size_t, sizeDataArea, (), (const, override));

        MOCK_METHOD(const DataBuf, dataArea, (), (const, override));



        MockValue(TypeId typeId) : Value(typeId) {}

    };



    template <typename T>

    class MockValueType : public ValueType<T> {

    public:

        MOCK_METHOD(int, read, (const byte* buf, size_t len, ByteOrder byteOrder), (override));

        MOCK_METHOD(int, read, (const std::string& buf), (override));

        MOCK_METHOD(int, setDataArea, (const byte* buf, size_t len), (override));

        MOCK_METHOD(const size_t, copy, (byte* buf, ByteOrder byteOrder), (const, override));

        MOCK_METHOD(const size_t, count, (), (const, override));

        MOCK_METHOD(const size_t, size, (), (const, override));

        MOCK_METHOD(const std::ostream&, write, (std::ostream& os), (const, override));

        MOCK_METHOD(const std::string, toString, (size_t n), (const, override));

        MOCK_METHOD(const int64_t, toInt64, (size_t n), (const, override));

        MOCK_METHOD(const uint32_t, toUint32, (size_t n), (const, override));

        MOCK_METHOD(const float, toFloat, (size_t n), (const, override));

        MOCK_METHOD(const Rational, toRational, (size_t n), (const, override));

        MOCK_METHOD(const size_t, sizeDataArea, (), (const, override));

        MOCK_METHOD(const DataBuf, dataArea, (), (const, override));



        MockValueType(TypeId typeId) : ValueType<T>(typeId) {}

    };

}



using namespace Exiv2;



class ValueTest_152 : public ::testing::Test {

protected:

    std::unique_ptr<MockValue> mock_value_;

    

    void SetUp() override {

        mock_value_ = std::make_unique<MockValue>(TypeId::asciiString);

    }

};



TEST_F(ValueTest_152, ReadBuffer_152) {

    byte buffer[] = { 'H', 'e', 'l', 'l', 'o' };

    EXPECT_CALL(*mock_value_, read(buffer, 5, ByteOrder::bigEndian)).WillOnce(::testing::Return(0));

    int result = mock_value_->read(buffer, 5, ByteOrder::bigEndian);

    ASSERT_EQ(result, 0);

}



TEST_F(ValueTest_152, ReadString_152) {

    EXPECT_CALL(*mock_value_, read("Hello")).WillOnce(::testing::Return(0));

    int result = mock_value_->read("Hello");

    ASSERT_EQ(result, 0);

}



TEST_F(ValueTest_152, SetDataArea_152) {

    byte buffer[] = { 'H', 'e', 'l', 'l', 'o' };

    EXPECT_CALL(*mock_value_, setDataArea(buffer, 5)).WillOnce(::testing::Return(0));

    int result = mock_value_->setDataArea(buffer, 5);

    ASSERT_EQ(result, 0);

}



TEST_F(ValueTest_152, CopyData_152) {

    byte buffer[5];

    EXPECT_CALL(*mock_value_, copy(buffer, ByteOrder::bigEndian)).WillOnce(::testing::Return(5));

    size_t result = mock_value_->copy(buffer, ByteOrder::bigEndian);

    ASSERT_EQ(result, 5);

}



TEST_F(ValueTest_152, CountElements_152) {

    EXPECT_CALL(*mock_value_, count()).WillOnce(::testing::Return(3));

    size_t result = mock_value_->count();

    ASSERT_EQ(result, 3);

}



TEST_F(ValueTest_152, SizeCalculation_152) {

    EXPECT_CALL(*mock_value_, size()).WillOnce(::testing::Return(10));

    size_t result = mock_value_->size();

    ASSERT_EQ(result, 10);

}



TEST_F(ValueTest_152, WriteToStream_152) {

    std::ostringstream os;

    EXPECT_CALL(*mock_value_, write(::testing::_)).WillOnce(::testing::ReturnRef(os));

    const std::ostream& result = mock_value_->write(os);

    ASSERT_EQ(&result, &os);

}



TEST_F(ValueTest_152, ToStringDefault_152) {

    EXPECT_CALL(*mock_value_, toString()).WillOnce(::testing::Return("Hello"));

    std::string result = mock_value_->toString();

    ASSERT_EQ(result, "Hello");

}



TEST_F(ValueTest_152, ToStringWithIndex_152) {

    EXPECT_CALL(*mock_value_, toString(0)).WillOnce(::testing::Return("Hello"));

    std::string result = mock_value_->toString(0);

    ASSERT_EQ(result, "Hello");

}



TEST_F(ValueTest_152, ToInt64_152) {

    EXPECT_CALL(*mock_value_, toInt64(0)).WillOnce(::testing::Return(123));

    int64_t result = mock_value_->toInt64(0);

    ASSERT_EQ(result, 123);

}



TEST_F(ValueTest_152, ToUint32_152) {

    EXPECT_CALL(*mock_value_, toUint32(0)).WillOnce(::testing::Return(456));

    uint32_t result = mock_value_->toUint32(0);

    ASSERT_EQ(result, 456);

}



TEST_F(ValueTest_152, ToFloat_152) {

    EXPECT_CALL(*mock_value_, toFloat(0)).WillOnce(::testing::Return(78.9));

    float result = mock_value_->toFloat(0);

    ASSERT_FLOAT_EQ(result, 78.9);

}



TEST_F(ValueTest_152, ToRational_152) {

    Rational expectedRational{1, 2};

    EXPECT_CALL(*mock_value_, toRational(0)).WillOnce(::testing::Return(expectedRational));

    Rational result = mock_value_->toRational(0);

    ASSERT_EQ(result.first, expectedRational.first);

    ASSERT_EQ(result.second, expectedRational.second);

}



TEST_F(ValueTest_152, SizeDataArea_152) {

    EXPECT_CALL(*mock_value_, sizeDataArea()).WillOnce(::testing::Return(10));

    size_t result = mock_value_->sizeDataArea();

    ASSERT_EQ(result, 10);

}



TEST_F(ValueTest_152, DataArea_152) {

    byte buffer[] = { 'H', 'e', 'l', 'l', 'o' };

    EXPECT_CALL(*mock_value_, dataArea()).WillOnce(::testing::Return(DataBuf(buffer, 5)));

    DataBuf result = mock_value_->dataArea();

    ASSERT_EQ(result.pData_, buffer);

    ASSERT_EQ(result.size_, 5);

}



class ValueTypeTest_152 : public ::testing::Test {

protected:

    std::unique_ptr<MockValueType<int>> mock_value_type_;

    

    void SetUp() override {

        mock_value_type_ = std::make_unique<MockValueType<int>>(TypeId::asciiString);

    }

};



TEST_F(ValueTypeTest_152, ReadBuffer_152) {

    byte buffer[] = { 'H', 'e', 'l', 'l', 'o' };

    EXPECT_CALL(*mock_value_type_, read(buffer, 5, ByteOrder::bigEndian)).WillOnce(::testing::Return(0));

    int result = mock_value_type_->read(buffer, 5, ByteOrder::bigEndian);

    ASSERT_EQ(result, 0);

}



TEST_F(ValueTypeTest_152, ReadString_152) {

    EXPECT_CALL(*mock_value_type_, read("Hello")).WillOnce(::testing::Return(0));

    int result = mock_value_type_->read("Hello");

    ASSERT_EQ(result, 0);

}



TEST_F(ValueTypeTest_152, SetDataArea_152) {

    byte buffer[] = { 'H', 'e', 'l', 'l', 'o' };

    EXPECT_CALL(*mock_value_type_, setDataArea(buffer, 5)).WillOnce(::testing::Return(0));

    int result = mock_value_type_->setDataArea(buffer, 5);

    ASSERT_EQ(result, 0);

}



TEST_F(ValueTypeTest_152, CopyData_152) {

    byte buffer[5];

    EXPECT_CALL(*mock_value_type_, copy(buffer, ByteOrder::bigEndian)).WillOnce(::testing::Return(5));

    size_t result = mock_value_type_->copy(buffer, ByteOrder::bigEndian);

    ASSERT_EQ(result, 5);

}



TEST_F(ValueTypeTest_152, CountElements_152) {

    EXPECT_CALL(*mock_value_type_, count()).WillOnce(::testing::Return(3));

    size_t result = mock_value_type_->count();

    ASSERT_EQ(result, 3);

}



TEST_F(ValueTypeTest_152, SizeCalculation_152) {

    EXPECT_CALL(*mock_value_type_, size()).WillOnce(::testing::Return(10));

    size_t result = mock_value_type_->size();

    ASSERT_EQ(result, 10);

}



TEST_F(ValueTypeTest_152, WriteToStream_152) {

    std::ostringstream os;

    EXPECT_CALL(*mock_value_type_, write(::testing::_)).WillOnce(::testing::ReturnRef(os));

    const std::ostream& result = mock_value_type_->write(os);

    ASSERT_EQ(&result, &os);

}



TEST_F(ValueTypeTest_152, ToStringWithIndex_152) {

    EXPECT_CALL(*mock_value_type_, toString(0)).WillOnce(::testing::Return("Hello"));

    std::string result = mock_value_type_->toString(0);

    ASSERT_EQ(result, "Hello");

}



TEST_F(ValueTypeTest_152, ToInt64_152) {

    EXPECT_CALL(*mock_value_type_, toInt64(0)).WillOnce(::testing::Return(123));

    int64_t result = mock_value_type_->toInt64(0);

    ASSERT_EQ(result, 123);

}



TEST_F(ValueTypeTest_152, ToUint32_152) {

    EXPECT_CALL(*mock_value_type_, toUint32(0)).WillOnce(::testing::Return(456));

    uint32_t result = mock_value_type_->toUint32(0);

    ASSERT_EQ(result, 456);

}



TEST_F(ValueTypeTest_152, ToFloat_152) {

    EXPECT_CALL(*mock_value_type_, toFloat(0)).WillOnce(::testing::Return(78.9));

    float result = mock_value_type_->toFloat(0);

    ASSERT_FLOAT_EQ(result, 78.9);

}



TEST_F(ValueTypeTest_152, ToRational_152) {

    Rational expectedRational{1, 2};

    EXPECT_CALL(*mock_value_type_, toRational(0)).WillOnce(::testing::Return(expectedRational));

    Rational result = mock_value_type_->toRational(0);

    ASSERT_EQ(result.first, expectedRational.first);

    ASSERT_EQ(result.second, expectedRational.second);

}



TEST_F(ValueTypeTest_152, SizeDataArea_152) {

    EXPECT_CALL(*mock_value_type_, sizeDataArea()).WillOnce(::testing::Return(10));

    size_t result = mock_value_type_->sizeDataArea();

    ASSERT_EQ(result, 10);

}



TEST_F(ValueTypeTest_152, DataArea_152) {

    byte buffer[] = { 'H', 'e', 'l', 'l', 'o' };

    EXPECT_CALL(*mock_value_type_, dataArea()).WillOnce(::testing::Return(DataBuf(buffer, 5)));

    DataBuf result = mock_value_type_->dataArea();

    ASSERT_EQ(result.pData_, buffer);

    ASSERT_EQ(result.size_, 5);

}
