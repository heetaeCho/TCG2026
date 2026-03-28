#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/exif.hpp"

#include "exiv2/xmp_exiv2.hpp"

#include "exiv2/value.hpp"

#include "convert.cpp"



namespace Exiv2 {

class MockXmpData : public XmpData {

public:

    MOCK_METHOD(iterator, findKey, (const XmpKey& key), (override));

    MOCK_METHOD(void, erase, (iterator pos), (override));

    MOCK_METHOD(Xmpdatum&, operator[], (const std::string & key), (override));

};



class MockXmpDatum : public Xmpdatum {

public:

    using Xmpdatum::Xmpdatum;

    MOCK_CONST_METHOD0(count, size_t());

    MOCK_CONST_METHOD1(toString, std::string(size_t n));

    MOCK_CONST_METHOD0(value, const Value&());

};



TEST_F(CnvXmpArrayTest_1845, NormalOperation_1845) {

    MockXmpData mockXmpData;

    ExifData exifData;

    Converter converter(exifData, mockXmpData);



    XmpKey key("Xmp.some.array");

    std::vector<std::string> values = {"value1", "value2", "value3"};

    MockXmpDatum xmpDatum(key, nullptr);

    EXPECT_CALL(xmpDatum, count()).WillOnce(::testing::Return(values.size()));

    for (size_t i = 0; i < values.size(); ++i) {

        EXPECT_CALL(xmpDatum, toString(i)).WillOnce(::testing::Return(values[i]));

        EXPECT_CALL(xmpDatum.value(), ok()).WillOnce(::testing::Return(true));

    }

    auto findKeyResult = mockXmpData.findKey(key);

    EXPECT_CALL(mockXmpData, findKey(key)).WillOnce(::testing::Return(findKeyResult));



    converter.cnvXmpArray("Xmp.some.array", "Exif.Some.Array");



    std::string expectedValue = "value1 value2 value3";

    EXPECT_EQ(exifData["Exif.Some.Array"].toString(), expectedValue);

}



TEST_F(CnvXmpArrayTest_1845, BoundaryCondition_EmptyArray_1845) {

    MockXmpData mockXmpData;

    ExifData exifData;

    Converter converter(exifData, mockXmpData);



    XmpKey key("Xmp.some.emptyArray");

    MockXmpDatum xmpDatum(key, nullptr);

    EXPECT_CALL(xmpDatum, count()).WillOnce(::testing::Return(0));

    auto findKeyResult = mockXmpData.findKey(key);

    EXPECT_CALL(mockXmpData, findKey(key)).WillOnce(::testing::Return(findKeyResult));



    converter.cnvXmpArray("Xmp.some.emptyArray", "Exif.Some.EmptyArray");



    std::string expectedValue = "";

    EXPECT_EQ(exifData["Exif.Some.EmptyArray"].toString(), expectedValue);

}



TEST_F(CnvXmpArrayTest_1845, BoundaryCondition_SingleElementArray_1845) {

    MockXmpData mockXmpData;

    ExifData exifData;

    Converter converter(exifData, mockXmpData);



    XmpKey key("Xmp.some.singleArray");

    std::string value = "singleValue";

    MockXmpDatum xmpDatum(key, nullptr);

    EXPECT_CALL(xmpDatum, count()).WillOnce(::testing::Return(1));

    EXPECT_CALL(xmpDatum, toString(0)).WillOnce(::testing::Return(value));

    EXPECT_CALL(xmpDatum.value(), ok()).WillOnce(::testing::Return(true));

    auto findKeyResult = mockXmpData.findKey(key);

    EXPECT_CALL(mockXmpData, findKey(key)).WillOnce(::testing::Return(findKeyResult));



    converter.cnvXmpArray("Xmp.some.singleArray", "Exif.Some.SingleArray");



    std::string expectedValue = "singleValue";

    EXPECT_EQ(exifData["Exif.Some.SingleArray"].toString(), expectedValue);

}



TEST_F(CnvXmpArrayTest_1845, ErrorCase_ValueNotOk_1845) {

    MockXmpData mockXmpData;

    ExifData exifData;

    Converter converter(exifData, mockXmpData);



    XmpKey key("Xmp.some.errorArray");

    MockXmpDatum xmpDatum(key, nullptr);

    EXPECT_CALL(xmpDatum, count()).WillOnce(::testing::Return(1));

    EXPECT_CALL(xmpDatum.value(), ok()).WillOnce(::testing::Return(false));

    auto findKeyResult = mockXmpData.findKey(key);

    EXPECT_CALL(mockXmpData, findKey(key)).WillOnce(::testing::Return(findKeyResult));



    converter.cnvXmpArray("Xmp.some.errorArray", "Exif.Some.ErrorArray");



    std::string expectedValue = "";

    EXPECT_EQ(exifData["Exif.Some.ErrorArray"].toString(), expectedValue);

}



TEST_F(CnvXmpArrayTest_1845, ErrorCase_KeyNotFound_1845) {

    MockXmpData mockXmpData;

    ExifData exifData;

    Converter converter(exifData, mockXmpData);



    XmpKey key("Xmp.some.nonExistentArray");

    auto findKeyResult = mockXmpData.end();

    EXPECT_CALL(mockXmpData, findKey(key)).WillOnce(::testing::Return(findKeyResult));



    converter.cnvXmpArray("Xmp.some.nonExistentArray", "Exif.Some.NonExistentArray");



    std::string expectedValue = "";

    EXPECT_EQ(exifData["Exif.Some.NonExistentArray"].toString(), expectedValue);

}

}  // namespace Exiv2
