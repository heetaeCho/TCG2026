#include <gtest/gtest.h>

#include "exiv2/iptc.hpp"

#include "exiv2/value.hpp"



using namespace Exiv2;



// Mock class for Value to simulate external dependency behavior

class MockValue : public Value {

public:

    MOCK_METHOD(int, read, (const byte* buf, size_t len, ByteOrder byteOrder), (override));

    MOCK_METHOD(int, read, (const std::string &buf), (override));

    MOCK_METHOD(int, setDataArea, (const byte* buf, size_t len), (override));

    MOCK_METHOD(const size_t, copy, (byte* buf, ByteOrder byteOrder), (const, override));

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



class IptcdatumTest_678 : public ::testing::Test {

protected:

    void SetUp() override {

        // Create a mock value

        auto mock_value = std::make_unique<MockValue>(stringType);

        pMockValue = mock_value.get();



        // Initialize Iptcdatum with the mock value

        iptcDatum = Iptcdatum(IptcKey("IPTC.Envelope.RecordVersion"), mock_value.release());

    }



    MockValue* pMockValue;

    Iptcdatum iptcDatum;

};



TEST_F(IptcdatumTest_678, Size_ReturnsZeroWhenNoValueSet_678) {

    EXPECT_CALL(*pMockValue, size()).WillOnce(::testing::Return(0));

    EXPECT_EQ(iptcDatum.size(), 0);

}



TEST_F(IptcdatumTest_678, Size_ReturnsCorrectSizeWhenValueSet_678) {

    EXPECT_CALL(*pMockValue, size()).WillOnce(::testing::Return(10));

    EXPECT_EQ(iptcDatum.size(), 10);

}



TEST_F(IptcdatumTest_678, Copy_DelegatesToValueCopyMethod_678) {

    byte buffer[10];

    ByteOrder order = littleEndian;

    EXPECT_CALL(*pMockValue, copy(buffer, order)).WillOnce(::testing::Return(10));

    EXPECT_EQ(iptcDatum.copy(buffer, order), 10);

}



TEST_F(IptcdatumTest_678, Write_DelegatesToValueWriteMethod_678) {

    std::ostringstream os;

    const ExifData* pMetadata = nullptr;

    EXPECT_CALL(*pMockValue, write(::testing::_)).WillOnce(::testing::ReturnRef(os));

    EXPECT_EQ(&iptcDatum.write(os, pMetadata), &os);

}



TEST_F(IptcdatumTest_678, Key_ReturnsExpectedKeyString_678) {

    EXPECT_EQ(iptcDatum.key(), "IPTC.Envelope.RecordVersion");

}



TEST_F(IptcdatumTest_678, RecordName_ReturnsExpectedRecordName_678) {

    EXPECT_EQ(iptcDatum.recordName(), "Envelope");

}



TEST_F(IptcdatumTest_678, TagName_ReturnsExpectedTagName_678) {

    EXPECT_EQ(iptcDatum.tagName(), "RecordVersion");

}
