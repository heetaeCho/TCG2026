#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/metadatum.hpp"

#include <sstream>



using namespace testing;

using namespace Exiv2;



class MetadatumMock : public Metadatum {

public:

    MOCK_METHOD(void, setValue, (const Value* pValue), (override));

    MOCK_METHOD(int, setValue, (const std::string& buf), (override));

    MOCK_METHOD(const std::string&, print, (const ExifData* pMetadata) const, (override));

    MOCK_METHOD(size_t, copy, (byte* buf, ByteOrder byteOrder), (const, override));

    MOCK_METHOD(const std::ostream&, write, (std::ostream& os, const ExifData* pMetadata), (const, override));

    MOCK_METHOD(const std::string&, key, (), (const, override));

    MOCK_METHOD(const char*, familyName, (), (const, override));

    MOCK_METHOD(const std::string&, groupName, (), (const, override));

    MOCK_METHOD(const std::string&, tagName, (), (const, override));

    MOCK_METHOD(const std::string&, tagLabel, (), (const, override));

    MOCK_METHOD(const std::string&, tagDesc, (), (const, override));

    MOCK_METHOD(uint16_t, tag, (), (const, override));

    MOCK_METHOD(TypeId, typeId, (), (const, override));

    MOCK_METHOD(const char*, typeName, (), (const, override));

    MOCK_METHOD(size_t, typeSize, (), (const, override));

    MOCK_METHOD(size_t, count, (), (const, override));

    MOCK_METHOD(size_t, size, (), (const, override));

    MOCK_METHOD(const std::string&, toString, (), (const, override));

    MOCK_METHOD(const std::string&, toString, (size_t n), (const, override));

    MOCK_METHOD(int64_t, toInt64, (size_t n), (const, override));

    MOCK_METHOD(uint32_t, toUint32, (size_t n), (const, override));

    MOCK_METHOD(float, toFloat, (size_t n), (const, override));

    MOCK_METHOD(Rational, toRational, (size_t n), (const, override));

    MOCK_METHOD(const std::unique_ptr<Value>&, getValue, (), (override));

    MOCK_METHOD(const Value&, value, (), (const, override));

};



TEST(MetadatumTest_112, Key_ReturnsExpectedString_112) {

    MetadatumMock mock;

    EXPECT_CALL(mock, key()).WillOnce(Return("key_value"));

    EXPECT_EQ(mock.key(), "key_value");

}



TEST(MetadatumTest_112, FamilyName_ReturnsExpectedCString_112) {

    MetadatumMock mock;

    EXPECT_CALL(mock, familyName()).WillOnce(Return("family_name"));

    EXPECT_STREQ(mock.familyName(), "family_name");

}



TEST(MetadatumTest_112, GroupName_ReturnsExpectedString_112) {

    MetadatumMock mock;

    EXPECT_CALL(mock, groupName()).WillOnce(Return("group_name"));

    EXPECT_EQ(mock.groupName(), "group_name");

}



TEST(MetadatumTest_112, TagName_ReturnsExpectedString_112) {

    MetadatumMock mock;

    EXPECT_CALL(mock, tagName()).WillOnce(Return("tag_name"));

    EXPECT_EQ(mock.tagName(), "tag_name");

}



TEST(MetadatumTest_112, TagLabel_ReturnsExpectedString_112) {

    MetadatumMock mock;

    EXPECT_CALL(mock, tagLabel()).WillOnce(Return("tag_label"));

    EXPECT_EQ(mock.tagLabel(), "tag_label");

}



TEST(MetadatumTest_112, TagDesc_ReturnsExpectedString_112) {

    MetadatumMock mock;

    EXPECT_CALL(mock, tagDesc()).WillOnce(Return("tag_desc"));

    EXPECT_EQ(mock.tagDesc(), "tag_desc");

}



TEST(MetadatumTest_112, Tag_ReturnsExpectedUint16_112) {

    MetadatumMock mock;

    EXPECT_CALL(mock, tag()).WillOnce(Return(10));

    EXPECT_EQ(mock.tag(), 10);

}



TEST(MetadatumTest_112, TypeId_ReturnsExpectedTypeId_112) {

    MetadatumMock mock;

    EXPECT_CALL(mock, typeId()).WillOnce(Return(tShort));

    EXPECT_EQ(mock.typeId(), tShort);

}



TEST(MetadatumTest_112, TypeName_ReturnsExpectedCString_112) {

    MetadatumMock mock;

    EXPECT_CALL(mock, typeName()).WillOnce(Return("short"));

    EXPECT_STREQ(mock.typeName(), "short");

}



TEST(MetadatumTest_112, TypeSize_ReturnsExpectedSize_112) {

    MetadatumMock mock;

    EXPECT_CALL(mock, typeSize()).WillOnce(Return(2));

    EXPECT_EQ(mock.typeSize(), 2);

}



TEST(MetadatumTest_112, Count_ReturnsExpectedCount_112) {

    MetadatumMock mock;

    EXPECT_CALL(mock, count()).WillOnce(Return(3));

    EXPECT_EQ(mock.count(), 3);

}



TEST(MetadatumTest_112, Size_ReturnsExpectedSize_112) {

    MetadatumMock mock;

    EXPECT_CALL(mock, size()).WillOnce(Return(6));

    EXPECT_EQ(mock.size(), 6);

}



TEST(MetadatumTest_112, ToString_Default_ReturnsExpectedString_112) {

    MetadatumMock mock;

    EXPECT_CALL(mock, toString()).WillOnce(Return("to_string_default"));

    EXPECT_EQ(mock.toString(), "to_string_default");

}



TEST(MetadatumTest_112, ToString_Index_ReturnsExpectedString_112) {

    MetadatumMock mock;

    EXPECT_CALL(mock, toString(0)).WillOnce(Return("to_string_index_0"));

    EXPECT_EQ(mock.toString(0), "to_string_index_0");

}



TEST(MetadatumTest_112, ToInt64_Index_ReturnsExpectedInt64_112) {

    MetadatumMock mock;

    EXPECT_CALL(mock, toInt64(0)).WillOnce(Return(12345));

    EXPECT_EQ(mock.toInt64(0), 12345);

}



TEST(MetadatumTest_112, ToUint32_Index_ReturnsExpectedUint32_112) {

    MetadatumMock mock;

    EXPECT_CALL(mock, toUint32(0)).WillOnce(Return(54321));

    EXPECT_EQ(mock.toUint32(0), 54321);

}



TEST(MetadatumTest_112, ToFloat_Index_ReturnsExpectedFloat_112) {

    MetadatumMock mock;

    EXPECT_CALL(mock, toFloat(0)).WillOnce(Return(1.23f));

    EXPECT_FLOAT_EQ(mock.toFloat(0), 1.23f);

}



TEST(MetadatumTest_112, ToRational_Index_ReturnsExpectedRational_112) {

    MetadatumMock mock;

    EXPECT_CALL(mock, toRational(0)).WillOnce(Return(Rational(1, 2)));

    EXPECT_EQ(mock.toRational(0), Rational(1, 2));

}



TEST(MetadatumTest_112, GetValue_ReturnsExpectedUniquePtrValue_112) {

    MetadatumMock mock;

    auto value = std::make_unique<Value>();

    EXPECT_CALL(mock, getValue()).WillOnce(Return(ByMove(std::move(value))));

    mock.getValue();

}



TEST(MetadatumTest_112, Value_ReturnsExpectedValueRef_112) {

    MetadatumMock mock;

    const Value val;

    EXPECT_CALL(mock, value()).WillOnce(ReturnRef(val));

    EXPECT_EQ(&mock.value(), &val);

}



TEST(MetadatumTest_112, SetValue_ValuePtr_SetsValue_112) {

    MetadatumMock mock;

    const Value* pValue = nullptr;

    EXPECT_CALL(mock, setValue(pValue)).WillOnce(Return());

    mock.setValue(pValue);

}



TEST(MetadatumTest_112, SetValue_StringBuffer_SetsValue_112) {

    MetadatumMock mock;

    EXPECT_CALL(mock, setValue("test")).WillOnce(Return(0));

    EXPECT_EQ(mock.setValue("test"), 0);

}



TEST(MetadatumTest_112, Print_Metadata_ReturnsExpectedString_112) {

    MetadatumMock mock;

    const ExifData* pMetadata = nullptr;

    EXPECT_CALL(mock, print(pMetadata)).WillOnce(Return("print_output"));

    EXPECT_EQ(mock.print(pMetadata), "print_output");

}



TEST(MetadatumTest_112, Copy_Buffer_ReturnsExpectedSize_112) {

    MetadatumMock mock;

    byte buf[10];

    ByteOrder order = bigEndian;

    EXPECT_CALL(mock, copy(buf, order)).WillOnce(Return(5));

    EXPECT_EQ(mock.copy(buf, order), 5);

}



TEST(MetadatumTest_112, Write_Stream_ReturnsExpectedStream_112) {

    MetadatumMock mock;

    std::ostringstream os;

    const ExifData* pMetadata = nullptr;

    EXPECT_CALL(mock, write(Ref(os), pMetadata)).WillOnce(ReturnRef(os));

    EXPECT_EQ(&mock.write(os, pMetadata), &os);

}
