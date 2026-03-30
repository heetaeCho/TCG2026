#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/tags.cpp"

#include "exiv2/error.hpp"



namespace Exiv2 {

    struct TagInfo {};

}



using namespace Exiv2;



// Mock for TagInfo function since it's external and we can't access internal logic.

class MockInternalFunctions {

public:

    MOCK_CONST_METHOD1(groupId, IfdId(const std::string& groupName));

    MOCK_CONST_METHOD3(tagNumber, uint16_t(const std::string& tn, IfdId ifdId, bool /*isLittleEndian*/));

    MOCK_CONST_METHOD2(tagInfo, const TagInfo*(uint16_t tag, IfdId ifdId));



    static MockInternalFunctions& getInstance() {

        static MockInternalFunctions instance;

        return instance;

    }

};



// Redirect calls to the mock

IfdId groupId(const std::string& groupName) { return MockInternalFunctions::getInstance().groupId(groupName); }

uint16_t tagNumber(const std::string& tn, IfdId ifdId) { return MockInternalFunctions::getInstance().tagNumber(tn, ifdId, true); }

const TagInfo* tagInfo(uint16_t tag, IfdId ifdId) { return MockInternalFunctions::getInstance().tagInfo(tag, ifdId); }



class ExifKeyImplTest : public ::testing::Test {

protected:

    ExifKey::Impl impl;

};



TEST_F(ExifKeyImplTest, DecomposeKey_ValidKey_1332) {

    const std::string key = "Iptc.Exif.ImageDescription";

    EXPECT_CALL(MockInternalFunctions::getInstance(), groupId("Exif")).WillOnce(::testing::Return(IfdId::exifId));

    EXPECT_CALL(MockInternalFunctions::getInstance(), tagNumber("ImageDescription", IfdId::exifId)).WillOnce(::testing::Return(270u));

    EXPECT_CALL(MockInternalFunctions::getInstance(), tagInfo(270u, IfdId::exifId)).WillOnce(::testing::Return(new TagInfo()));



    EXPECT_NO_THROW(impl.decomposeKey(key));



    EXPECT_EQ(impl.ifdId_, IfdId::exifId);

    EXPECT_EQ(impl.tag_, 270u);

}



TEST_F(ExifKeyImplTest, DecomposeKey_InvalidFamilyName_1332) {

    const std::string key = "Invalid.Exif.ImageDescription";

    EXPECT_THROW(impl.decomposeKey(key), Error);

}



TEST_F(ExifKeyImplTest, DecomposeKey_NoGroupName_1332) {

    const std::string key = "Iptc..ImageDescription";

    EXPECT_THROW(impl.decomposeKey(key), Error);

}



TEST_F(ExifKeyImplTest, DecomposeKey_NoTagName_1332) {

    const std::string key = "Iptc.Exif.";

    EXPECT_THROW(impl.decomposeKey(key), Error);

}



TEST_F(ExifKeyImplTest, DecomposeKey_InvalidGroupName_1332) {

    const std::string key = "Iptc.Invalid.ImageDescription";

    EXPECT_CALL(MockInternalFunctions::getInstance(), groupId("Invalid")).WillOnce(::testing::Return(IfdId::ifdIdNotSet));

    EXPECT_THROW(impl.decomposeKey(key), Error);

}



TEST_F(ExifKeyImplTest, DecomposeKey_InvalidTagNumber_1332) {

    const std::string key = "Iptc.Exif.Invalid";

    EXPECT_CALL(MockInternalFunctions::getInstance(), groupId("Exif")).WillOnce(::testing::Return(IfdId::exifId));

    EXPECT_CALL(MockInternalFunctions::getInstance(), tagNumber("Invalid", IfdId::exifId)).WillOnce(::testing::Return(0u));

    EXPECT_THROW(impl.decomposeKey(key), Error);

}



TEST_F(ExifKeyImplTest, DecomposeKey_TagInfoNotFound_1332) {

    const std::string key = "Iptc.Exif.ImageDescription";

    EXPECT_CALL(MockInternalFunctions::getInstance(), groupId("Exif")).WillOnce(::testing::Return(IfdId::exifId));

    EXPECT_CALL(MockInternalFunctions::getInstance(), tagNumber("ImageDescription", IfdId::exifId)).WillOnce(::testing::Return(270u));

    EXPECT_CALL(MockInternalFunctions::getInstance(), tagInfo(270u, IfdId::exifId)).WillOnce(::testing::Return(nullptr));

    EXPECT_THROW(impl.decomposeKey(key), Error);

}
