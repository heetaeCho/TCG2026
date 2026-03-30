#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/iptc.hpp"

#include "exiv2/value.hpp"



using namespace Exiv2;



class MockValue : public Value {

public:

    MOCK_METHOD(int, read, (const byte *buf, size_t len, ByteOrder byteOrder), (override));

    MOCK_METHOD(int, setDataArea, (const byte* buf, size_t len), (override));

    MOCK_METHOD(const size_t, copy, (byte *buf, ByteOrder byteOrder), (const, override));

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

    MOCK_METHOD(DataBuf, dataArea, (), (const, override));



    MockValue(TypeId typeId) : Value(typeId) {}

};



class IptcdatumTest_689 : public ::testing::Test {

protected:

    std::unique_ptr<MockValue> mock_value_;

    IptcKey key_;

    Iptcdatum iptc_datum_;



    void SetUp() override {

        mock_value_ = std::make_unique<MockValue>(typeNameAscii);

        iptc_datum_ = Iptcdatum(key_, mock_value_.get());

    }

};



TEST_F(IptcdatumTest_689, OperatorAssignment_Value_689) {

    MockValue another_mock_value(typeNameAscii);

    EXPECT_CALL(another_mock_value, clone()).WillOnce(::testing::Return(std::make_unique<MockValue>(typeNameAscii)));

    iptc_datum_ = another_mock_value;

}



TEST_F(IptcdatumTest_689, OperatorAssignment_Uint16_t_689) {

    uint16_t value = 42;

    EXPECT_CALL(*mock_value_, setDataArea(::testing::NotNull(), sizeof(uint16_t))).WillOnce(::testing::Return(0));

    iptc_datum_ = value;

}



TEST_F(IptcdatumTest_689, OperatorAssignment_String_689) {

    std::string value = "test";

    EXPECT_CALL(*mock_value_, setDataArea(::testing::NotNull(), ::testing::_)).WillOnce(::testing::Return(0));

    iptc_datum_ = value;

}



TEST_F(IptcdatumTest_689, SetValue_ValuePointer_689) {

    Value* value_ptr = mock_value_.get();

    EXPECT_CALL(*mock_value_, clone()).WillOnce(::testing::Return(std::make_unique<MockValue>(typeNameAscii)));

    iptc_datum_.setValue(value_ptr);

}



TEST_F(IptcdatumTest_689, SetValue_String_689) {

    std::string value = "test";

    EXPECT_CALL(*mock_value_, setDataArea(::testing::NotNull(), ::testing::_)).WillOnce(::testing::Return(0));

    iptc_datum_.setValue(value);

}



TEST_F(IptcdatumTest_689, Count_NormalOperation_689) {

    size_t expected_count = 1;

    EXPECT_CALL(*mock_value_, count()).WillOnce(::testing::Return(expected_count));

    EXPECT_EQ(iptc_datum_.count(), expected_count);

}



TEST_F(IptcdatumTest_689, Size_NormalOperation_689) {

    size_t expected_size = 4;

    EXPECT_CALL(*mock_value_, size()).WillOnce(::testing::Return(expected_size));

    EXPECT_EQ(iptc_datum_.size(), expected_size);

}



TEST_F(IptcdatumTest_689, ToString_NormalOperation_689) {

    std::string expected_string = "test";

    EXPECT_CALL(*mock_value_, toString()).WillOnce(::testing::Return(expected_string));

    EXPECT_EQ(iptc_datum_.toString(), expected_string);

}



TEST_F(IptcdatumTest_689, ToInt64_NormalOperation_689) {

    int64_t expected_int = 123;

    EXPECT_CALL(*mock_value_, toInt64(0)).WillOnce(::testing::Return(expected_int));

    EXPECT_EQ(iptc_datum_.toInt64(), expected_int);

}



TEST_F(IptcdatumTest_689, ToFloat_NormalOperation_689) {

    float expected_float = 123.45f;

    EXPECT_CALL(*mock_value_, toFloat(0)).WillOnce(::testing::Return(expected_float));

    EXPECT_FLOAT_EQ(iptc_datum_.toFloat(), expected_float);

}



TEST_F(IptcdatumTest_689, ToRational_NormalOperation_689) {

    Rational expected_rational(1, 2);

    EXPECT_CALL(*mock_value_, toRational(0)).WillOnce(::testing::Return(expected_rational));

    EXPECT_EQ(iptc_datum_.toRational(), expected_rational);

}



TEST_F(IptcdatumTest_689, Copy_NormalOperation_689) {

    byte buffer[10];

    ByteOrder byte_order = littleEndian;

    size_t expected_size = 4;

    EXPECT_CALL(*mock_value_, copy(::testing::NotNull(), byte_order)).WillOnce(::testing::Return(expected_size));

    EXPECT_EQ(iptc_datum_.copy(buffer, byte_order), expected_size);

}



TEST_F(IptcdatumTest_689, Write_NormalOperation_689) {

    std::ostringstream oss;

    EXPECT_CALL(*mock_value_, write(::testing::_)).WillOnce(::testing::ReturnRef(oss));

    iptc_datum_.write(oss, nullptr);

}
