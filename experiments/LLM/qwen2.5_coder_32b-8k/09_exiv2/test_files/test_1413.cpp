#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/exif.hpp"

#include "exiv2/value.hpp"



using namespace Exiv2;

using namespace testing;



class Print0xa403Test : public Test {

protected:

    std::ostringstream os;

    NiceMock<MockValue> mockValue;

    const ExifData* metadata = nullptr;

};



class MockValue : public Value {

public:

    MOCK_METHOD(int, read, (const byte * buf, size_t len, ByteOrder byteOrder), (override));

    MOCK_METHOD(int, read, (const std::string & buf), (override));

    MOCK_METHOD(int, setDataArea, (const byte * buf, size_t len), (override));

    MOCK_METHOD(const size_t, copy, (byte * buf, ByteOrder byteOrder), (const override));

    MOCK_METHOD(const size_t, count, (), (const override));

    MOCK_METHOD(const size_t, size, (), (const override));

    MOCK_METHOD(const std::ostream &, write, (std::ostream & os), (const override));

    MOCK_METHOD(const std::string, toString, (), (const override));

    MOCK_METHOD(const std::string, toString, (size_t n), (const override));

    MOCK_METHOD(const int64_t, toInt64, (size_t n), (const override));

    MOCK_METHOD(const uint32_t, toUint32, (size_t n), (const override));

    MOCK_METHOD(const float, toFloat, (size_t n), (const override));

    MOCK_METHOD(const Rational, toRational, (size_t n), (const override));

    MOCK_METHOD(const size_t, sizeDataArea, (), (const override));

    MOCK_METHOD(const DataBuf, dataArea, (), (const override));



    MockValue(TypeId typeId) : Value(typeId) {}

};



TEST_F(Print0xa403Test_1413, NormalOperation_Auto_1413) {

    EXPECT_CALL(mockValue, toString()).WillOnce(Return("0"));

    Internal::print0xa403(os, mockValue, metadata);

    EXPECT_EQ(os.str(), "Auto");

}



TEST_F(Print0xa403Test_1413, NormalOperation_Manual_1413) {

    EXPECT_CALL(mockValue, toString()).WillOnce(Return("1"));

    Internal::print0xa403(os, mockValue, metadata);

    EXPECT_EQ(os.str(), "Manual");

}



TEST_F(Print0xa403Test_1413, BoundaryCondition_OutOfRange_1413) {

    EXPECT_CALL(mockValue, toString()).WillOnce(Return("2"));

    Internal::print0xa403(os, mockValue, metadata);

    EXPECT_EQ(os.str(), "2");

}



TEST_F(Print0xa403Test_1413, ExceptionalCase_EmptyString_1413) {

    EXPECT_CALL(mockValue, toString()).WillOnce(Return(""));

    Internal::print0xa403(os, mockValue, metadata);

    EXPECT_EQ(os.str(), "");

}



TEST_F(Print0xa403Test_1413, ExceptionalCase_NegativeValue_1413) {

    EXPECT_CALL(mockValue, toString()).WillOnce(Return("-1"));

    Internal::print0xa403(os, mockValue, metadata);

    EXPECT_EQ(os.str(), "-1");

}
