#include <gtest/gtest.h>

#include "exiv2/xmp_exiv2.hpp"

#include "exiv2/value.hpp"



namespace Exiv2 {

    class MockValue : public Value {

    public:

        MOCK_METHOD(size_t, size, (), const);

        MockValue(TypeId typeId) : Value(typeId) {}

    };

}



class XmpdatumTest_1290 : public ::testing::Test {

protected:

    void SetUp() override {

        xmpKey = std::make_unique<Exiv2::XmpKey>("testKey");

        mockValue = std::make_unique<Exiv2::MockValue>(Exiv2::unsignedRational);

        xmpDatum = std::make_unique<Exiv2::Xmpdatum>(*xmpKey, mockValue.get());

    }



    void TearDown() override {

        xmpDatum.reset();

        mockValue.reset();

        xmpKey.reset();

    }



    std::unique_ptr<Exiv2::XmpKey> xmpKey;

    std::unique_ptr<Exiv2::MockValue> mockValue;

    std::unique_ptr<Exiv2::Xmpdatum> xmpDatum;

};



TEST_F(XmpdatumTest_1290, Size_ReturnsCorrectSize_1290) {

    EXPECT_CALL(*mockValue, size()).WillOnce(::testing::Return(42));

    EXPECT_EQ(xmpDatum->size(), 42);

}



TEST_F(XmpdatumTest_1290, Size_ReturnsZeroWhenNoValue_1290) {

    xmpDatum = std::make_unique<Exiv2::Xmpdatum>(*xmpKey, nullptr);

    EXPECT_EQ(xmpDatum->size(), 0);

}



TEST_F(XmpdatumTest_1290, Copy_CallsDataCopy_1290) {

    byte buffer[10];

    Exiv2::ByteOrder byteOrder = Exiv2::bigEndian;

    EXPECT_CALL(*mockValue, copy(::testing::NotNull(), byteOrder)).WillOnce(::testing::Return(10));

    xmpDatum->copy(buffer, byteOrder);

}



TEST_F(XmpdatumTest_1290, Write_CallsDataWrite_1290) {

    std::ostringstream os;

    const Exiv2::ExifData* metadata = nullptr;

    EXPECT_CALL(*mockValue, write(::testing::Ref(os))).WillOnce(::testing::ReturnRef(os));

    xmpDatum->write(os, metadata);

}



TEST_F(XmpdatumTest_1290, SetValue_SetsNewValue_1290) {

    auto newValue = std::make_unique<Exiv2::MockValue>(Exiv2::unsignedRational);

    EXPECT_CALL(*newValue, size()).WillOnce(::testing::Return(56));

    xmpDatum->setValue(newValue.get());

    EXPECT_EQ(xmpDatum->size(), 56);

}



TEST_F(XmpdatumTest_1290, SetValueString_ReturnsSuccess_1290) {

    std::string value = "testValue";

    EXPECT_CALL(*mockValue, read(value)).WillOnce(::testing::Return(0));

    int result = xmpDatum->setValue(value);

    EXPECT_EQ(result, 0);

}



TEST_F(XmpdatumTest_1290, SetValueString_ReturnsError_1290) {

    std::string value = "testValue";

    EXPECT_CALL(*mockValue, read(value)).WillOnce(::testing::Return(-1));

    int result = xmpDatum->setValue(value);

    EXPECT_EQ(result, -1);

}
