#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/exif.hpp"

#include "exiv2/value.hpp"

#include "./TestProjects/exiv2/src/sonymn_int.hpp"

#include <sstream>



using namespace ::testing;

using namespace Exiv2::Internal;

using namespace Exiv2;



class SonyMakerNoteTest_1623 : public Test {

protected:

    SonyMakerNote sonyMakerNote;

    std::ostringstream oss;

    NiceMock<MockValue> mockValue;

    NiceMock<MockExifData> mockMetadata;



    void SetUp() override {

        ON_CALL(mockValue, count()).WillByDefault(Return(1));

        ON_CALL(mockValue, typeId()).WillByDefault(Return(unsignedByte));

        ON_CALL(mockValue, toInt64()).WillByDefault(Return(0));

        ON_CALL(mockMetadata, empty()).WillByDefault(Return(false));

    }

};



class MockExifData : public Exiv2::ExifData {

public:

    MOCK_METHOD1(findKey, const_iterator(const ExifKey& key)) const;

};



class MockValue : public Exiv2::Value {

public:

    using Value::Value;

    MOCK_CONST_METHOD0(count, size_t());

    MOCK_CONST_METHOD0(typeId, TypeId());

    MOCK_CONST_METHOD1(toInt64, int64_t(size_t n));

};



TEST_F(SonyMakerNoteTest_1623, PrintSonyMisc3cModelReleaseYear_NormalOperation_ModelILCE1_1623) {

    EXPECT_CALL(mockMetadata, findKey(_)).WillOnce(ReturnPointee(new Exifdatum("Exif.Sony.Model", &mockValue)));

    ON_CALL(mockMetadata, empty()).WillByDefault(Return(false));

    oss.str("");

    sonyMakerNote.printSonyMisc3cModelReleaseYear(oss, mockValue, &mockMetadata);

    EXPECT_EQ(oss.str(), "n/a");

}



TEST_F(SonyMakerNoteTest_1623, PrintSonyMisc3cModelReleaseYear_NormalOperation_ModelILCE7M4_1623) {

    EXPECT_CALL(mockMetadata, findKey(_)).WillOnce(ReturnPointee(new Exifdatum("Exif.Sony.Model", &mockValue)));

    ON_CALL(mockValue, toString()).WillByDefault(Return("ILCE-7M4"));

    oss.str("");

    sonyMakerNote.printSonyMisc3cModelReleaseYear(oss, mockValue, &mockMetadata);

    EXPECT_EQ(oss.str(), "n/a");

}



TEST_F(SonyMakerNoteTest_1623, PrintSonyMisc3cModelReleaseYear_NormalOperation_ModelNotInList_1623) {

    EXPECT_CALL(mockMetadata, findKey(_)).WillOnce(ReturnPointee(new Exifdatum("Exif.Sony.Model", &mockValue)));

    ON_CALL(mockValue, toString()).WillByDefault(Return("UNKNOWN_MODEL"));

    oss.str("");

    sonyMakerNote.printSonyMisc3cModelReleaseYear(oss, mockValue, &mockMetadata);

    EXPECT_EQ(oss.str(), "2000");

}



TEST_F(SonyMakerNoteTest_1623, PrintSonyMisc3cModelReleaseYear_ValueCountNotOne_1623) {

    ON_CALL(mockValue, count()).WillByDefault(Return(2));

    oss.str("");

    sonyMakerNote.printSonyMisc3cModelReleaseYear(oss, mockValue, &mockMetadata);

    EXPECT_EQ(oss.str(), "(0)");

}



TEST_F(SonyMakerNoteTest_1623, PrintSonyMisc3cModelReleaseYear_ValueTypeIdNotUnsignedByte_1623) {

    ON_CALL(mockValue, typeId()).WillByDefault(Return(unsignedShort));

    oss.str("");

    sonyMakerNote.printSonyMisc3cModelReleaseYear(oss, mockValue, &mockMetadata);

    EXPECT_EQ(oss.str(), "(0)");

}



TEST_F(SonyMakerNoteTest_1623, PrintSonyMisc3cModelReleaseYear_MetadataNull_1623) {

    oss.str("");

    sonyMakerNote.printSonyMisc3cModelReleaseYear(oss, mockValue, nullptr);

    EXPECT_EQ(oss.str(), "(0)");

}



TEST_F(SonyMakerNoteTest_1623, PrintSonyMisc3cModelReleaseYear_ValueGreaterThan99_1623) {

    ON_CALL(mockValue, toInt64()).WillByDefault(Return(100));

    oss.str("");

    sonyMakerNote.printSonyMisc3cModelReleaseYear(oss, mockValue, &mockMetadata);

    EXPECT_EQ(oss.str(), "(100)");

}



TEST_F(SonyMakerNoteTest_1623, PrintSonyMisc3cModelReleaseYear_ValueZero_1623) {

    oss.str("");

    sonyMakerNote.printSonyMisc3cModelReleaseYear(oss, mockValue, &mockMetadata);

    EXPECT_EQ(oss.str(), "2000");

}



TEST_F(SonyMakerNoteTest_1623, PrintSonyMisc3cModelReleaseYear_ValueLessThan99_1623) {

    ON_CALL(mockValue, toInt64()).WillByDefault(Return(23));

    oss.str("");

    sonyMakerNote.printSonyMisc3cModelReleaseYear(oss, mockValue, &mockMetadata);

    EXPECT_EQ(oss.str(), "2023");

}
