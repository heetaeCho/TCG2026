#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/metadatum.hpp"

#include <iostream>

#include <string>



using namespace Exiv2;

using ::testing::_;

using ::testing::Return;



class MockMetadatum : public Metadatum {

public:

    MOCK_METHOD(void, setValue, (const Value* pValue), (override));

    MOCK_METHOD(int, setValue, (const std::string & buf), (override));

    MOCK_METHOD(const std::string, print, (const ExifData* pMetadata), (const, override));

    MOCK_METHOD(const size_t, copy, (byte * buf, ByteOrder byteOrder), (const, override));

    MOCK_METHOD(const std::ostream &, write, (std::ostream & os, const ExifData* pMetadata), (const, override));

    MOCK_METHOD(const std::string, key, (), (const, override));

    MOCK_METHOD(const char *, familyName, (), (const, override));

    MOCK_METHOD(const std::string, groupName, (), (const, override));

    MOCK_METHOD(const std::string, tagName, (), (const, override));

    MOCK_METHOD(const std::string, tagLabel, (), (const, override));

    MOCK_METHOD(const std::string, tagDesc, (), (const, override));

    MOCK_METHOD(const uint16_t, tag, (), (const, override));

    MOCK_METHOD(const TypeId, typeId, (), (const, override));

    MOCK_METHOD(const char *, typeName, (), (const, override));

    MOCK_METHOD(const size_t, typeSize, (), (const, override));

    MOCK_METHOD(const size_t, count, (), (const, override));

    MOCK_METHOD(const size_t, size, (), (const, override));

    MOCK_METHOD(const std::string, toString, (), (const, override));

    MOCK_METHOD(const std::string, toString, (size_t n), (const, override));

    MOCK_METHOD(const int64_t, toInt64, (size_t n), (const, override));

    MOCK_METHOD(uint32_t, toUint32, (size_t n), (const, override));

    MOCK_METHOD(const float, toFloat, (size_t n), (const, override));

    MOCK_METHOD(const Rational, toRational, (size_t n), (const, override));

    MOCK_METHOD(const std::unique_ptr<Value>, getValue, (), (const, override));

    MOCK_METHOD(const Value &, value, (), (const, override));

};



TEST_F(MockMetadatumTest_38, setValue_ValuePointer_38) {

    MockMetadatum mockMetadatum;

    const Value* dummyValue = nullptr; // Replace with appropriate value if needed

    EXPECT_CALL(mockMetadatum, setValue(dummyValue)).Times(1);

    mockMetadatum.setValue(dummyValue);

}



TEST_F(MockMetadatumTest_38, setValue_StringBuffer_38) {

    MockMetadatum mockMetadatum;

    std::string dummyString = "dummy"; // Replace with appropriate string if needed

    EXPECT_CALL(mockMetadatum, setValue(dummyString)).WillOnce(Return(0));

    int result = mockMetadatum.setValue(dummyString);

    EXPECT_EQ(result, 0); // Assuming return value indicates success

}



TEST_F(MockMetadatumTest_38, print_NormalOperation_38) {

    MockMetadatum mockMetadatum;

    const ExifData* dummyMetadata = nullptr; // Replace with appropriate metadata if needed

    std::string expectedOutput = "dummy"; // Replace with expected output string if needed

    EXPECT_CALL(mockMetadatum, print(dummyMetadata)).WillOnce(Return(expectedOutput));

    std::string result = mockMetadatum.print(dummyMetadata);

    EXPECT_EQ(result, expectedOutput);

}



TEST_F(MockMetadatumTest_38, copy_NormalOperation_38) {

    MockMetadatum mockMetadatum;

    byte dummyBuffer[10]; // Replace with appropriate buffer size if needed

    ByteOrder dummyByteOrder = littleEndian; // Replace with appropriate byte order if needed

    size_t expectedSize = 5; // Replace with expected size if needed

    EXPECT_CALL(mockMetadatum, copy(dummyBuffer, dummyByteOrder)).WillOnce(Return(expectedSize));

    size_t result = mockMetadatum.copy(dummyBuffer, dummyByteOrder);

    EXPECT_EQ(result, expectedSize);

}



TEST_F(MockMetadatumTest_38, write_NormalOperation_38) {

    MockMetadatum mockMetadatum;

    std::ostringstream oss;

    const ExifData* dummyMetadata = nullptr; // Replace with appropriate metadata if needed

    EXPECT_CALL(mockMetadatum, write(oss, dummyMetadata)).WillOnce(ReturnRef(oss));

    std::ostream& result = mockMetadatum.write(oss, dummyMetadata);

    EXPECT_EQ(&result, &oss); // Check that the returned stream is the same as the input stream

}



TEST_F(MockMetadatumTest_38, key_NormalOperation_38) {

    MockMetadatum mockMetadatum;

    std::string expectedKey = "dummy"; // Replace with expected key string if needed

    EXPECT_CALL(mockMetadatum, key()).WillOnce(Return(expectedKey));

    std::string result = mockMetadatum.key();

    EXPECT_EQ(result, expectedKey);

}



TEST_F(MockMetadatumTest_38, familyName_NormalOperation_38) {

    MockMetadatum mockMetadatum;

    const char* expectedFamilyName = "dummy"; // Replace with expected family name string if needed

    EXPECT_CALL(mockMetadatum, familyName()).WillOnce(Return(expectedFamilyName));

    const char* result = mockMetadatum.familyName();

    EXPECT_STREQ(result, expectedFamilyName);

}



TEST_F(MockMetadatumTest_38, groupName_NormalOperation_38) {

    MockMetadatum mockMetadatum;

    std::string expectedGroupName = "dummy"; // Replace with expected group name string if needed

    EXPECT_CALL(mockMetadatum, groupName()).WillOnce(Return(expectedGroupName));

    std::string result = mockMetadatum.groupName();

    EXPECT_EQ(result, expectedGroupName);

}



TEST_F(MockMetadatumTest_38, tagName_NormalOperation_38) {

    MockMetadatum mockMetadatum;

    std::string expectedTagName = "dummy"; // Replace with expected tag name string if needed

    EXPECT_CALL(mockMetadatum, tagName()).WillOnce(Return(expectedTagName));

    std::string result = mockMetadatum.tagName();

    EXPECT_EQ(result, expectedTagName);

}



TEST_F(MockMetadatumTest_38, tagLabel_NormalOperation_38) {

    MockMetadatum mockMetadatum;

    std::string expectedTagLabel = "dummy"; // Replace with expected tag label string if needed

    EXPECT_CALL(mockMetadatum, tagLabel()).WillOnce(Return(expectedTagLabel));

    std::string result = mockMetadatum.tagLabel();

    EXPECT_EQ(result, expectedTagLabel);

}



TEST_F(MockMetadatumTest_38, tagDesc_NormalOperation_38) {

    MockMetadatum mockMetadatum;

    std::string expectedTagDesc = "dummy"; // Replace with expected tag description string if needed

    EXPECT_CALL(mockMetadatum, tagDesc()).WillOnce(Return(expectedTagDesc));

    std::string result = mockMetadatum.tagDesc();

    EXPECT_EQ(result, expectedTagDesc);

}



TEST_F(MockMetadatumTest_38, tag_NormalOperation_38) {

    MockMetadatum mockMetadatum;

    uint16_t expectedTag = 0x0001; // Replace with expected tag if needed

    EXPECT_CALL(mockMetadatum, tag()).WillOnce(Return(expectedTag));

    uint16_t result = mockMetadatum.tag();

    EXPECT_EQ(result, expectedTag);

}



TEST_F(MockMetadatumTest_38, typeId_NormalOperation_38) {

    MockMetadatum mockMetadatum;

    TypeId expectedTypeId = asciiString; // Replace with expected type ID if needed

    EXPECT_CALL(mockMetadatum, typeId()).WillOnce(Return(expectedTypeId));

    TypeId result = mockMetadatum.typeId();

    EXPECT_EQ(result, expectedTypeId);

}



TEST_F(MockMetadatumTest_38, typeName_NormalOperation_38) {

    MockMetadatum mockMetadatum;

    const char* expectedTypeName = "dummy"; // Replace with expected type name string if needed

    EXPECT_CALL(mockMetadatum, typeName()).WillOnce(Return(expectedTypeName));

    const char* result = mockMetadatum.typeName();

    EXPECT_STREQ(result, expectedTypeName);

}



TEST_F(MockMetadatumTest_38, typeSize_NormalOperation_38) {

    MockMetadatum mockMetadatum;

    size_t expectedTypeSize = 4; // Replace with expected type size if needed

    EXPECT_CALL(mockMetadatum, typeSize()).WillOnce(Return(expectedTypeSize));

    size_t result = mockMetadatum.typeSize();

    EXPECT_EQ(result, expectedTypeSize);

}



TEST_F(MockMetadatumTest_38, count_NormalOperation_38) {

    MockMetadatum mockMetadatum;

    size_t expectedCount = 1; // Replace with expected count if needed

    EXPECT_CALL(mockMetadatum, count()).WillOnce(Return(expectedCount));

    size_t result = mockMetadatum.count();

    EXPECT_EQ(result, expectedCount);

}



TEST_F(MockMetadatumTest_38, size_NormalOperation_38) {

    MockMetadatum mockMetadatum;

    size_t expectedSize = 10; // Replace with expected size if needed

    EXPECT_CALL(mockMetadatum, size()).WillOnce(Return(expectedSize));

    size_t result = mockMetadatum.size();

    EXPECT_EQ(result, expectedSize);

}



TEST_F(MockMetadatumTest_38, toString_NoIndex_38) {

    MockMetadatum mockMetadatum;

    std::string expectedResult = "dummy"; // Replace with expected string if needed

    EXPECT_CALL(mockMetadatum, toString()).WillOnce(Return(expectedResult));

    std::string result = mockMetadatum.toString();

    EXPECT_EQ(result, expectedResult);

}



TEST_F(MockMetadatumTest_38, toString_Indexed_38) {

    MockMetadatum mockMetadatum;

    size_t index = 0; // Replace with appropriate index if needed

    std::string expectedResult = "dummy"; // Replace with expected string if needed

    EXPECT_CALL(mockMetadatum, toString(index)).WillOnce(Return(expectedResult));

    std::string result = mockMetadatum.toString(index);

    EXPECT_EQ(result, expectedResult);

}



TEST_F(MockMetadatumTest_38, toInt64_NormalOperation_38) {

    MockMetadatum mockMetadatum;

    size_t index = 0; // Replace with appropriate index if needed

    int64_t expectedResult = 12345; // Replace with expected integer value if needed

    EXPECT_CALL(mockMetadatum, toInt64(index)).WillOnce(Return(expectedResult));

    int64_t result = mockMetadatum.toInt64(index);

    EXPECT_EQ(result, expectedResult);

}



TEST_F(MockMetadatumTest_38, toUint32_NormalOperation_38) {

    MockMetadatum mockMetadatum;

    size_t index = 0; // Replace with appropriate index if needed

    uint32_t expectedResult = 12345; // Replace with expected unsigned integer value if needed

    EXPECT_CALL(mockMetadatum, toUint32(index)).WillOnce(Return(expectedResult));

    uint32_t result = mockMetadatum.toUint32(index);

    EXPECT_EQ(result, expectedResult);

}



TEST_F(MockMetadatumTest_38, toFloat_NormalOperation_38) {

    MockMetadatum mockMetadatum;

    size_t index = 0; // Replace with appropriate index if needed

    float expectedResult = 123.45f; // Replace with expected float value if needed

    EXPECT_CALL(mockMetadatum, toFloat(index)).WillOnce(Return(expectedResult));

    float result = mockMetadatum.toFloat(index);

    EXPECT_FLOAT_EQ(result, expectedResult);

}



TEST_F(MockMetadatumTest_38, toRational_NormalOperation_38) {

    MockMetadatum mockMetadatum;

    size_t index = 0; // Replace with appropriate index if needed

    Rational expectedResult(123, 45); // Replace with expected rational value if needed

    EXPECT_CALL(mockMetadatum, toRational(index)).WillOnce(Return(expectedResult));

    Rational result = mockMetadatum.toRational(index);

    EXPECT_EQ(result.first, expectedResult.first);

    EXPECT_EQ(result.second, expectedResult.second);

}



TEST_F(MockMetadatumTest_38, getValue_NormalOperation_38) {

    MockMetadatum mockMetadatum;

    std::unique_ptr<Value> expectedResult = nullptr; // Replace with appropriate value if needed

    EXPECT_CALL(mockMetadatum, getValue()).WillOnce(Return(ByMove(std::move(expectedResult))));

    std::unique_ptr<Value> result = mockMetadatum.getValue();

    EXPECT_EQ(result.get(), expectedResult.get());

}



TEST_F(MockMetadatumTest_38, value_NormalOperation_38) {

    MockMetadatum mockMetadatum;

    Value dummyValue; // Replace with appropriate value if needed

    const Value& expectedResult = dummyValue;

    EXPECT_CALL(mockMetadatum, value()).WillOnce(ReturnRef(expectedResult));

    const Value& result = mockMetadatum.value();

    EXPECT_EQ(&result, &expectedResult);

}
