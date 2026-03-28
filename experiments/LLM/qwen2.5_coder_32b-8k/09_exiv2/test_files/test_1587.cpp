#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/exif.hpp"



namespace Exiv2 {

    namespace Internal {

        static auto getFocusMode2(const ExifData* metadata, uint32_t& val);

    }

}



using ::testing::Return;

using ::testing::_;



class MockExifdatum : public Exiv2::Exifdatum {

public:

    MOCK_METHOD(const std::ostream &, write, (std::ostream &os, const Exiv2::ExifData *pMetadata) const, (override));

    MOCK_METHOD(size_t, size, (), (const, override));

    MOCK_METHOD(Exiv2::TypeId, typeId, (), (const, override));

    MOCK_METHOD(uint32_t, toUint32, (size_t n), (const, override));

};



class MockMetadatum : public Exiv2::Metadatum {

public:

    MOCK_METHOD(const std::ostream &, write, (std::ostream &os, const Exiv2::ExifData *pMetadata) const, (override));

    MOCK_METHOD(size_t, size, (), (const, override));

    MOCK_METHOD(Exiv2::TypeId, typeId, (), (const, override));

    MOCK_METHOD(uint32_t, toUint32, (size_t n), (const, override));

};



class MockExifData : public Exiv2::ExifData {

public:

    using iterator = std::map<std::string, Exiv2::Metadatum*>::iterator;

    using const_iterator = std::map<std::string, Exiv2::Metadatum*>::const_iterator;



    MOCK_METHOD(MockExifdatum&, operator[], (const std::string &key));

    MOCK_METHOD(iterator, findKey, (const Exif2::ExifKey &key), (override));

    MOCK_METHOD(void, add, (const Exiv2::ExifKey &key, const Exiv2::Value *pValue), (override));

    MOCK_METHOD(void, clear, (), (override));

};



class FocusModeTest : public ::testing::Test {

protected:

    MockExifData exifData;

};



TEST_F(FocusModeTest_NormalOperation_1587, ValidFocusMode_ReturnsTrueAndSetsValue_1587) {

    Exiv2::ExifKey key("Exif.Sony1.FocusMode2");

    uint32_t val = 0;



    MockExifdatum mockMetadatum;

    EXPECT_CALL(mockMetadatum, size()).WillOnce(Return(1));

    EXPECT_CALL(mockMetadatum, typeId()).WillOnce(Return(Exiv2::unsignedByte));

    EXPECT_CALL(mockMetadatum, toUint32(_)).WillOnce(Return(42));



    auto mockFindKey = [&mockMetadatum](const Exiv2::ExifKey &key) -> MockExifData::iterator {

        return { new std::pair<std::string, Exiv2::Metadatum*>(key.key(), &mockMetadatum) };

    };



    EXPECT_CALL(exifData, findKey(key)).WillOnce(testing::Invoke(mockFindKey));



    bool result = Exiv2::Internal::getFocusMode2(&exifData, val);

    EXPECT_TRUE(result);

    EXPECT_EQ(val, 42U);

}



TEST_F(FocusModeTest_NormalOperation_1587, ValidFocusModeInSecondTag_ReturnsTrueAndSetsValue_1587) {

    Exiv2::ExifKey key("Exif.Sony2.FocusMode2");

    uint32_t val = 0;



    MockExifdatum mockMetadatum;

    EXPECT_CALL(mockMetadatum, size()).WillOnce(Return(1));

    EXPECT_CALL(mockMetadatum, typeId()).WillOnce(Return(Exiv2::unsignedByte));

    EXPECT_CALL(mockMetadatum, toUint32(_)).WillOnce(Return(42));



    auto mockFindKey = [&mockMetadatum](const Exiv2::ExifKey &key) -> MockExifData::iterator {

        if (key.key() == "Exif.Sony1.FocusMode2") {

            return exifData.end();

        }

        return { new std::pair<std::string, Exiv2::Metadatum*>(key.key(), &mockMetadatum) };

    };



    EXPECT_CALL(exifData, findKey(_)).WillRepeatedly(testing::Invoke(mockFindKey));



    bool result = Exiv2::Internal::getFocusMode2(&exifData, val);

    EXPECT_TRUE(result);

    EXPECT_EQ(val, 42U);

}



TEST_F(FocusModeTest_BoundaryConditions_1587, EmptyExifData_ReturnsFalseAndSetsValueToZero_1587) {

    uint32_t val = 0;

    Exiv2::ExifKey key("Exif.Sony1.FocusMode2");



    EXPECT_CALL(exifData, findKey(key)).WillOnce(Return(exifData.end()));



    bool result = Exiv2::Internal::getFocusMode2(&exifData, val);

    EXPECT_FALSE(result);

    EXPECT_EQ(val, 0U);

}



TEST_F(FocusModeTest_BoundaryConditions_1587, InvalidSize_ReturnsFalseAndSetsValueToZero_1587) {

    uint32_t val = 0;

    Exiv2::ExifKey key("Exif.Sony1.FocusMode2");



    MockExifdatum mockMetadatum;

    EXPECT_CALL(mockMetadatum, size()).WillOnce(Return(0));



    auto mockFindKey = [&mockMetadatum](const Exiv2::ExifKey &key) -> MockExifData::iterator {

        return { new std::pair<std::string, Exiv2::Metadatum*>(key.key(), &mockMetadatum) };

    };



    EXPECT_CALL(exifData, findKey(key)).WillOnce(testing::Invoke(mockFindKey));



    bool result = Exiv2::Internal::getFocusMode2(&exifData, val);

    EXPECT_FALSE(result);

    EXPECT_EQ(val, 0U);

}



TEST_F(FocusModeTest_BoundaryConditions_1587, InvalidTypeId_ReturnsFalseAndSetsValueToZero_1587) {

    uint32_t val = 0;

    Exiv2::ExifKey key("Exif.Sony1.FocusMode2");



    MockExifdatum mockMetadatum;

    EXPECT_CALL(mockMetadatum, size()).WillOnce(Return(1));

    EXPECT_CALL(mockMetadatum, typeId()).WillOnce(Return(Exiv2::asciiString));



    auto mockFindKey = [&mockMetadatum](const Exiv2::ExifKey &key) -> MockExifData::iterator {

        return { new std::pair<std::string, Exiv2::Metadatum*>(key.key(), &mockMetadatum) };

    };



    EXPECT_CALL(exifData, findKey(key)).WillOnce(testing::Invoke(mockFindKey));



    bool result = Exiv2::Internal::getFocusMode2(&exifData, val);

    EXPECT_FALSE(result);

    EXPECT_EQ(val, 0U);

}



TEST_F(FocusModeTest_ErrorCases_1587, NADBoundedValue_ReturnsFalseAndSetsValueToZero_1587) {

    uint32_t val = 0;

    Exiv2::ExifKey key("Exif.Sony1.FocusMode2");



    MockExifdatum mockMetadatum;

    EXPECT_CALL(mockMetadatum, size()).WillOnce(Return(1));

    EXPECT_CALL(mockMetadatum, typeId()).WillOnce(Return(Exiv2::unsignedByte));

    EXPECT_CALL(mockMetadatum, write(_, _)).WillOnce([](std::ostream &os, const Exif2::ExifData *pMetadata) {

        os << "n/a";

        return os;

    });



    auto mockFindKey = [&mockMetadatum](const Exiv2::ExifKey &key) -> MockExifData::iterator {

        return { new std::pair<std::string, Exiv2::Metadatum*>(key.key(), &mockMetadatum) };

    };



    EXPECT_CALL(exifData, findKey(key)).WillOnce(testing::Invoke(mockFindKey));



    bool result = Exiv2::Internal::getFocusMode2(&exifData, val);

    EXPECT_FALSE(result);

    EXPECT_EQ(val, 0U);

}
