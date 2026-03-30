#include <gtest/gtest.h>

#include "exiv2/iptc.hpp"

#include "exiv2/value.hpp"



using namespace Exiv2;



// Mock class for Value to use in testing Iptcdatum

class MockValue : public Value {

public:

    MOCK_METHOD(int, read, (const byte *buf, size_t len, ByteOrder byteOrder), (override));

    MOCK_METHOD(int, read, (const std::string &buf), (override));

    MOCK_METHOD(int, setDataArea, (const byte *buf, size_t len), (override));

    MOCK_METHOD(size_t, copy, (byte *buf, ByteOrder byteOrder), (const, override));

    MOCK_METHOD(size_t, count, (), (const, override));

    MOCK_METHOD(size_t, size, (), (const, override));

    MOCK_METHOD(std::ostream&, write, (std::ostream &os), (const, override));

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



class IptcdatumTest_679 : public ::testing::Test {

protected:

    void SetUp() override {

        mock_value = std::make_unique<MockValue>(TypeId::string);

        iptc_key = IptcKey("Iptc.Envelope.DateSent");

        iptc_datum = std::make_unique<Iptcdatum>(iptc_key, mock_value.get());

    }



    std::unique_ptr<MockValue> mock_value;

    IptcKey iptc_key;

    std::unique_ptr<Iptcdatum> iptc_datum;

};



TEST_F(IptcdatumTest_679, ToString_ReturnsEmptyStringWhenNoValue_679) {

    // Arrange

    iptc_datum->setValue(nullptr);



    // Act & Assert

    EXPECT_EQ(iptc_datum->toString(), "");

}



TEST_F(IptcdatumTest_679, ToString_DelegatesToValueToString_679) {

    // Arrange

    EXPECT_CALL(*mock_value, toString()).WillOnce(testing::Return("MockValueString"));



    // Act & Assert

    EXPECT_EQ(iptc_datum->toString(), "MockValueString");

}



TEST_F(IptcdatumTest_679, SetStringValue_SetsCorrectly_679) {

    // Arrange & Act

    iptc_datum->setValue("TestString");



    // We don't have direct access to the internal value, so we can only test via observable behavior (toString)

    EXPECT_EQ(iptc_datum->toString(), "TestString");

}



TEST_F(IptcdatumTest_679, SetStringValue_CallsSetValueOnValueObject_679) {

    // Arrange

    EXPECT_CALL(*mock_value, setValue("TestString")).WillOnce(testing::Return(0));



    // Act

    iptc_datum->setValue("TestString");



    // No assert needed here as the call is verified in the mock expectation

}



TEST_F(IptcdatumTest_679, SetStringValue_ReturnsSelfReference_679) {

    // Arrange & Act & Assert

    EXPECT_EQ(&(*iptc_datum = "TestString"), iptc_datum.get());

}



TEST_F(IptcdatumTest_679, CopyFunction_DelegatesToValueCopy_679) {

    // Arrange

    byte buffer[100];

    ByteOrder byteOrder = littleEndian;

    EXPECT_CALL(*mock_value, copy(buffer, byteOrder)).WillOnce(testing::Return(42));



    // Act & Assert

    EXPECT_EQ(iptc_datum->copy(buffer, byteOrder), 42);

}



TEST_F(IptcdatumTest_679, WriteFunction_DelegatesToValueWrite_679) {

    // Arrange

    std::ostringstream oss;

    EXPECT_CALL(*mock_value, write(testing::_)).WillOnce(testing::ReturnRef(oss));



    // Act & Assert

    EXPECT_EQ(&iptc_datum->write(oss, nullptr), &oss);

}



TEST_F(IptcdatumTest_679, KeyFunction_ReturnsCorrectKeyString_679) {

    // Arrange & Act & Assert

    EXPECT_EQ(iptc_datum->key(), "Iptc.Envelope.DateSent");

}
