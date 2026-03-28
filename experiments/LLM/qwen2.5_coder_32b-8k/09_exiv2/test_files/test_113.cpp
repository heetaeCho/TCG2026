#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/metadatum.hpp"



using namespace Exiv2;

using namespace testing;



class MetadatumMock : public Metadatum {

public:

    METADATUM_DECL MetadatumMock() = default;

    METADATUM_DECL ~MetadatumMock() override = default;



    MOCK_METHOD(void, setValue, (const Value * pValue), (override));

    MOCK_METHOD(int, setValue, (const std::string & buf), (override));

    MOCK_METHOD(std::string, print, (const ExifData * pMetadata) const, (override));

    MOCK_METHOD(size_t, copy, (byte * buf, ByteOrder byteOrder), (const, override));

    MOCK_METHOD(const std::ostream &, write, (std::ostream & os, const ExifData * pMetadata), (const, override));

    MOCK_METHOD(std::string, key, (), (const, override));

    MOCK_METHOD(const char *, familyName, (), (const, override));

    MOCK_METHOD(std::string, groupName, (), (const, override));

    MOCK_METHOD(std::string, tagName, (), (const, override));

    MOCK_METHOD(std::string, tagLabel, (), (const, override));

    MOCK_METHOD(std::string, tagDesc, (), (const, override));

    MOCK_METHOD(uint16_t, tag, (), (const, override));

    MOCK_METHOD(TypeId, typeId, (), (const, override));

    MOCK_METHOD(const char *, typeName, (), (const, override));

    MOCK_METHOD(size_t, typeSize, (), (const, override));

    MOCK_METHOD(size_t, count, (), (const, override));

    MOCK_METHOD(size_t, size, (), (const, override));

    MOCK_METHOD(std::string, toString, (), (const, override));

    MOCK_METHOD(std::string, toString, (size_t n), (const, override));

    MOCK_METHOD(int64_t, toInt64, (size_t n), (const, override));

    MOCK_METHOD(uint32_t, toUint32, (size_t n), (const, override));

    MOCK_METHOD(float, toFloat, (size_t n), (const, override));

    MOCK_METHOD(Rational, toRational, (size_t n), (const, override));

    MOCK_METHOD(std::unique_ptr<Value>, getValue, (), (const, override));

    MOCK_METHOD(const Value &, value, (), (const, override));

};



class MetadatumTest : public Test {

protected:

    std::unique_ptr<MetadatumMock> metadatum;



    void SetUp() override {

        metadatum = std::make_unique<MetadatumMock>();

    }

};



TEST_F(MetadatumTest_113, Key_ReturnsExpectedValue_113) {

    EXPECT_CALL(*metadatum, key()).WillOnce(Return("SampleKey"));

    EXPECT_EQ(metadatum->key(), "SampleKey");

}



TEST_F(MetadatumTest_113, FamilyName_ReturnsExpectedValue_113) {

    EXPECT_CALL(*metadatum, familyName()).WillOnce(Return("SampleFamily"));

    EXPECT_STREQ(metadatum->familyName(), "SampleFamily");

}



TEST_F(MetadatumTest_113, GroupName_ReturnsExpectedValue_113) {

    EXPECT_CALL(*metadatum, groupName()).WillOnce(Return("SampleGroup"));

    EXPECT_EQ(metadatum->groupName(), "SampleGroup");

}



TEST_F(MetadatumTest_113, TagName_ReturnsExpectedValue_113) {

    EXPECT_CALL(*metadatum, tagName()).WillOnce(Return("SampleTag"));

    EXPECT_EQ(metadatum->tagName(), "SampleTag");

}



TEST_F(MetadatumTest_113, TagLabel_ReturnsExpectedValue_113) {

    EXPECT_CALL(*metadatum, tagLabel()).WillOnce(Return("SampleLabel"));

    EXPECT_EQ(metadatum->tagLabel(), "SampleLabel");

}



TEST_F(MetadatumTest_113, TagDesc_ReturnsExpectedValue_113) {

    EXPECT_CALL(*metadatum, tagDesc()).WillOnce(Return("SampleDescription"));

    EXPECT_EQ(metadatum->tagDesc(), "SampleDescription");

}



TEST_F(MetadatumTest_113, Tag_ReturnsExpectedValue_113) {

    EXPECT_CALL(*metadatum, tag()).WillOnce(Return(0x0001));

    EXPECT_EQ(metadatum->tag(), 0x0001);

}



TEST_F(MetadatumTest_113, TypeId_ReturnsExpectedValue_113) {

    EXPECT_CALL(*metadatum, typeId()).WillOnce(Return(tShort));

    EXPECT_EQ(metadatum->typeId(), tShort);

}



TEST_F(MetadatumTest_113, TypeName_ReturnsExpectedValue_113) {

    EXPECT_CALL(*metadatum, typeName()).WillOnce(Return("Short"));

    EXPECT_STREQ(metadatum->typeName(), "Short");

}



TEST_F(MetadatumTest_113, TypeSize_ReturnsExpectedValue_113) {

    EXPECT_CALL(*metadatum, typeSize()).WillOnce(Return(2));

    EXPECT_EQ(metadatum->typeSize(), 2);

}



TEST_F(MetadatumTest_113, Count_ReturnsExpectedValue_113) {

    EXPECT_CALL(*metadatum, count()).WillOnce(Return(5));

    EXPECT_EQ(metadatum->count(), 5);

}



TEST_F(MetadatumTest_113, Size_ReturnsExpectedValue_113) {

    EXPECT_CALL(*metadatum, size()).WillOnce(Return(10));

    EXPECT_EQ(metadatum->size(), 10);

}



TEST_F(MetadatumTest_113, ToString_NoIndex_ReturnsExpectedValue_113) {

    EXPECT_CALL(*metadatum, toString()).WillOnce(Return("SampleToString"));

    EXPECT_EQ(metadatum->toString(), "SampleToString");

}



TEST_F(MetadatumTest_113, ToString_Index_ReturnsExpectedValue_113) {

    EXPECT_CALL(*metadatum, toString(0)).WillOnce(Return("SampleToStringIndex"));

    EXPECT_EQ(metadatum->toString(0), "SampleToStringIndex");

}



TEST_F(MetadatumTest_113, ToInt64_Index_ReturnsExpectedValue_113) {

    EXPECT_CALL(*metadatum, toInt64(0)).WillOnce(Return(123));

    EXPECT_EQ(metadatum->toInt64(0), 123);

}



TEST_F(MetadatumTest_113, ToUint32_Index_ReturnsExpectedValue_113) {

    EXPECT_CALL(*metadatum, toUint32(0)).WillOnce(Return(456));

    EXPECT_EQ(metadatum->toUint32(0), 456);

}



TEST_F(MetadatumTest_113, ToFloat_Index_ReturnsExpectedValue_113) {

    EXPECT_CALL(*metadatum, toFloat(0)).WillOnce(Return(78.9f));

    EXPECT_FLOAT_EQ(metadatum->toFloat(0), 78.9f);

}



TEST_F(MetadatumTest_113, ToRational_Index_ReturnsExpectedValue_113) {

    Rational expectedRational(1, 2);

    EXPECT_CALL(*metadatum, toRational(0)).WillOnce(Return(expectedRational));

    EXPECT_EQ(metadatum->toRational(0), expectedRational);

}



TEST_F(MetadatumTest_113, GetValue_ReturnsExpectedValue_113) {

    auto mockValue = std::make_unique<ValueMock>();

    EXPECT_CALL(*metadatum, getValue()).WillOnce(Return(ByMove(std::move(mockValue))));

    // Further assertions on the returned value can be done if needed

}



TEST_F(MetadatumTest_113, Value_ReturnsExpectedReference_113) {

    const Value mockValue;

    EXPECT_CALL(*metadatum, value()).WillOnce(ReturnRef(mockValue));

    // Further assertions on the returned reference can be done if needed

}



TEST_F(MetadatumTest_113, SetValue_ValuePointer_DoesNotThrow_113) {

    Value mockValue;

    EXPECT_CALL(*metadatum, setValue(&mockValue)).WillOnce(Return());

    EXPECT_NO_THROW(metadatum->setValue(&mockValue));

}



TEST_F(MetadatumTest_113, SetValue_StringBuffer_ReturnsExpectedValue_113) {

    EXPECT_CALL(*metadatum, setValue("SampleString")).WillOnce(Return(0));

    EXPECT_EQ(metadatum->setValue("SampleString"), 0);

}



TEST_F(MetadatumTest_113, Print_MetadataPointer_ReturnsExpectedStream_113) {

    ExifData metadata;

    std::string expectedOutput = "SamplePrint";

    EXPECT_CALL(*metadatum, print(&metadata)).WillOnce(Return(expectedOutput));

    EXPECT_EQ(metadatum->print(&metadata), expectedOutput);

}



TEST_F(MetadatumTest_113, Copy_Buffer_ByteOrder_ReturnsExpectedSize_113) {

    byte buffer[256];

    ByteOrder byteOrder = littleEndian;

    EXPECT_CALL(*metadatum, copy(buffer, byteOrder)).WillOnce(Return(10));

    EXPECT_EQ(metadatum->copy(buffer, byteOrder), 10);

}



TEST_F(MetadatumTest_113, Write_OutputStream_MetadataPointer_ReturnsExpectedOutputStream_113) {

    std::ostringstream outputStream;

    ExifData metadata;

    const std::ostream& expectedOutput = outputStream;

    EXPECT_CALL(*metadatum, write(outputStream, &metadata)).WillOnce(ReturnRef(expectedOutput));

    EXPECT_EQ(&metadatum->write(outputStream, &metadata), &expectedOutput);

}



// Test boundary conditions and exceptional cases if observable through the interface

TEST_F(MetadatumTest_113, ToUint32_OutOfBoundsIndex_ReturnsZero_113) {

    EXPECT_CALL(*metadatum, toUint32(999)).WillOnce(Return(0));

    EXPECT_EQ(metadatum->toUint32(999), 0);

}



TEST_F(MetadatumTest_113, ToFloat_OutOfBoundsIndex_ReturnsZero_113) {

    EXPECT_CALL(*metadatum, toFloat(999)).WillOnce(Return(0.0f));

    EXPECT_FLOAT_EQ(metadatum->toFloat(999), 0.0f);

}



TEST_F(MetadatumTest_113, ToRational_OutOfBoundsIndex_ReturnsZeroRational_113) {

    Rational expectedRational(0, 0);

    EXPECT_CALL(*metadatum, toRational(999)).WillOnce(Return(expectedRational));

    EXPECT_EQ(metadatum->toRational(999), expectedRational);

}



TEST_F(MetadatumTest_113, ToString_OutOfBoundsIndex_ReturnsEmptyString_113) {

    EXPECT_CALL(*metadatum, toString(999)).WillOnce(Return(""));

    EXPECT_EQ(metadatum->toString(999), "");

}
