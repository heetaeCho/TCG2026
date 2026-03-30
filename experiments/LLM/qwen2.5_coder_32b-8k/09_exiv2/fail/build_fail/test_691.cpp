#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/iptc.hpp"

#include "exiv2/datasets.hpp"



using namespace Exiv2;



class MockValue : public Value {

public:

    MOCK_METHOD(int, read, (const byte *buf, size_t len, ByteOrder byteOrder), (override));

    MOCK_METHOD(int, read, (const std::string &buf), (override));

    MOCK_METHOD(const size_t, copy, (byte *buf, ByteOrder byteOrder), (const, override));

    MOCK_METHOD(const size_t, count, (), (const, override));

    MOCK_METHOD(const size_t, size, (), (const, override));

    MOCK_METHOD(const std::ostream &, write, (std::ostream &os), (const, override));

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



class IptcdatumTest_691 : public ::testing::Test {

protected:

    std::unique_ptr<IptcKey> key;

    MockValue* mockValue;

    Iptcdatum* iptcdatum;



    void SetUp() override {

        key = std::make_unique<IptcKey>(0, 0);

        mockValue = new MockValue(TypeId::asciiString);

        iptcdatum = new Iptcdatum(*key, nullptr);

    }



    void TearDown() override {

        delete iptcdatum;

        delete mockValue;

    }

};



TEST_F(IptcdatumTest_691, SetValueWithValidString_691) {

    std::string value = "test";

    EXPECT_CALL(*mockValue, read(value)).WillOnce(::testing::Return(0));

    iptcdatum->setValue(value);

}



TEST_F(IptcdatumTest_691, SetValueWithEmptyString_691) {

    std::string value = "";

    EXPECT_CALL(*mockValue, read(value)).WillOnce(::testing::Return(0));

    iptcdatum->setValue(value);

}



TEST_F(IptcdatumTest_691, SetValueWithLargeString_691) {

    std::string largeValue(LARGE_INT, 'a');

    EXPECT_CALL(*mockValue, read(largeValue)).WillOnce(::testing::Return(0));

    iptcdatum->setValue(largeValue);

}



TEST_F(IptcdatumTest_691, SetValueReturnsError_691) {

    std::string value = "test";

    EXPECT_CALL(*mockValue, read(value)).WillOnce(::testing::Return(-1));

    int result = iptcdatum->setValue(value);

    EXPECT_EQ(result, -1);

}



TEST_F(IptcdatumTest_691, DataSetTypeCalledOnFirstSetValue_691) {

    std::string value = "test";

    EXPECT_CALL(IptcDataSets::dataSetType(0, 0), ::testing::Exactly(1)).WillOnce(::testing::Return(TypeId::asciiString));

    EXPECT_CALL(*mockValue, read(value)).WillOnce(::testing::Return(0));

    iptcdatum->setValue(value);

}



TEST_F(IptcdatumTest_691, DataSetTypeNotCalledOnSubsequentSetValue_691) {

    std::string value = "test";

    EXPECT_CALL(IptcDataSets::dataSetType(0, 0), ::testing::Exactly(1)).WillOnce(::testing::Return(TypeId::asciiString));

    iptcdatum->setValue(value);



    EXPECT_CALL(IptcDataSets::dataSetType(0, 0), ::testing::Exactly(0));

    EXPECT_CALL(*mockValue, read(value)).WillOnce(::testing::Return(0));

    iptcdatum->setValue(value);

}
