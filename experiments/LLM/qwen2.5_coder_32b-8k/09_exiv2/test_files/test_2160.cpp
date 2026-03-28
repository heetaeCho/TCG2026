#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/iptc.hpp"

#include "exiv2/value.hpp"



using namespace Exiv2;



class MockValue : public Value {

public:

    MOCK_METHOD(int, read, (const byte * buf, size_t len, ByteOrder byteOrder), (override));

    MOCK_METHOD(int, setDataArea, (const byte * buf, size_t len), (override));

    MOCK_METHOD(size_t, copy, (byte * buf, ByteOrder byteOrder), (const, override));

    MOCK_METHOD(size_t, count, (), (const, override));

    MOCK_METHOD(size_t, size, (), (const, override));

    MOCK_METHOD(const std::ostream &, write, (std::ostream & os), (const, override));

    MOCK_METHOD(std::string, toString, (), (const, override));

    MOCK_METHOD(std::string, toString, (size_t n), (const, override));

    MOCK_METHOD(int64_t, toInt64, (size_t n), (const, override));

    MOCK_METHOD(uint32_t, toUint32, (size_t n), (const, override));

    MOCK_METHOD(float, toFloat, (size_t n), (const, override));

    MOCK_METHOD(Rational, toRational, (size_t n), (const, override));

    MOCK_METHOD(size_t, sizeDataArea, (), (const, override));

    MOCK_METHOD(DataBuf, dataArea, (), (const, override));



    MockValue(TypeId typeId) : Value(typeId) {}

};



class IptcdatumTest_2160 : public ::testing::Test {

protected:

    IptcKey key{"IPTC.Key"};

    std::unique_ptr<MockValue> mock_value = std::make_unique<MockValue>(TypeId::invalid);

};



TEST_F(IptcdatumTest_2160, ConstructorWithKeyAndNullValue_2160) {

    Iptcdatum iptcDatum(key, nullptr);

    EXPECT_EQ(iptcDatum.key(), key.key());

}



TEST_F(IptcdatumTest_2160, ConstructorWithKeyAndNonNullValue_2160) {

    Iptcdatum iptcDatum(key, mock_value.get());

    EXPECT_EQ(iptcDatum.key(), key.key());

}



TEST_F(IptcdatumTest_2160, CopyConstructor_2160) {

    Iptcdatum originalIptcDatum(key, mock_value.get());

    Iptcdatum copiedIptcDatum(originalIptcDatum);

    EXPECT_EQ(copiedIptcDatum.key(), key.key());

}



TEST_F(IptcdatumTest_2160, OperatorEqualWithAnotherIptcdatum_2160) {

    Iptcdatum iptcDatum(key, mock_value.get());

    Iptcdatum anotherIptcDatum(key, nullptr);

    anotherIptcDatum = iptcDatum;

    EXPECT_EQ(anotherIptcDatum.key(), key.key());

}



TEST_F(IptcdatumTest_2160, SetValueWithPointerValue_2160) {

    Iptcdatum iptcDatum(key, nullptr);

    iptcDatum.setValue(mock_value.get());

}



TEST_F(IptcdatumTest_2160, SetStringValue_2160) {

    Iptcdatum iptcDatum(key, nullptr);

    EXPECT_EQ(iptcDatum.setValue("test"), 4);

}



TEST_F(IptcdatumTest_2160, ToString_ReturnsEmptyString_2160) {

    Iptcdatum iptcDatum(key, mock_value.get());

    EXPECT_CALL(*mock_value, toString()).WillOnce(::testing::Return("MockValue"));

    EXPECT_EQ(iptcDatum.toString(), "MockValue");

}



TEST_F(IptcdatumTest_2160, ToStringWithIndex_ReturnsEmptyString_2160) {

    Iptcdatum iptcDatum(key, mock_value.get());

    EXPECT_CALL(*mock_value, toString(0)).WillOnce(::testing::Return("MockValue"));

    EXPECT_EQ(iptcDatum.toString(0), "MockValue");

}
