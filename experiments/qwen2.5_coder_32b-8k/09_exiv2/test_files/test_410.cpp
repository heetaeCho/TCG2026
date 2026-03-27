#include <gtest/gtest.h>

#include <exiv2/tags.hpp>



namespace Exiv2 {

    namespace Internal {

        static const TagInfo* findTagInfo(uint16_t tag, IfdId group);

    }

}



// Mock class for TagListProvider to simulate the behavior of exifTagList and gpsTagList

class TagListProviderMock {

public:

    virtual ~TagListProviderMock() = default;

    MOCK_CONST_METHOD0(exifTagList, const Exiv2::TagInfo*());

    MOCK_CONST_METHOD0(gpsTagList, const Exiv2::TagInfo*());

};



// Test fixture for findTagInfo function

class FindTagInfoTest_410 : public ::testing::Test {

protected:

    TagListProviderMock mock;

    

    // Mock implementation of exifTagList and gpsTagList

    static const Exiv2::TagInfo* getExifTagList() {

        static Exiv2::TagInfo tags[] = {{Exiv2::SectionId::unknown, Exiv2::TypeId::unsignedLong, 1, nullptr}, {0xffff, Exiv2::TypeId::undefined, 0, nullptr}};

        return tags;

    }



    static const Exiv2::TagInfo* getGpsTagList() {

        static Exiv2::TagInfo tags[] = {{Exiv2::SectionId::unknown, Exiv2::TypeId::unsignedLong, 1, nullptr}, {0xffff, Exiv2::TypeId::undefined, 0, nullptr}};

        return tags;

    }



    void SetUp() override {

        EXPECT_CALL(mock, exifTagList()).WillRepeatedly(::testing::Return(getExifTagList()));

        EXPECT_CALL(mock, gpsTagList()).WillRepeatedly(::testing::Return(getGpsTagList()));

    }

};



TEST_F(FindTagInfoTest_410, FindExistingTagInExif_410) {

    const Exiv2::TagInfo* result = Exiv2::Internal::findTagInfo(0x9003, Exiv2::IfdId::exifId);

    EXPECT_NE(result, nullptr);

    EXPECT_EQ(result->tag_, 0x9003);

}



TEST_F(FindTagInfoTest_410, FindExistingTagInGps_410) {

    const Exiv2::TagInfo* result = Exiv2::Internal::findTagInfo(0x0000, Exiv2::IfdId::gpsId);

    EXPECT_NE(result, nullptr);

    EXPECT_EQ(result->tag_, 0x0000);

}



TEST_F(FindTagInfoTest_410, FindNonExistingTagInExif_410) {

    const Exiv2::TagInfo* result = Exiv2::Internal::findTagInfo(0xFFFF, Exiv2::IfdId::exifId);

    EXPECT_EQ(result, nullptr);

}



TEST_F(FindTagInfoTest_410, FindNonExistingTagInGps_410) {

    const Exiv2::TagInfo* result = Exiv2::Internal::findTagInfo(0xFFFF, Exiv2::IfdId::gpsId);

    EXPECT_EQ(result, nullptr);

}



TEST_F(FindTagInfoTest_410, FindTagInUnsupportedGroup_410) {

    const Exiv2::TagInfo* result = Exiv2::Internal::findTagInfo(0x9003, Exiv2::IfdId::ifd0Id);

    EXPECT_EQ(result, nullptr);

}



TEST_F(FindTagInfoTest_410, FindBoundaryTagInExif_410) {

    const Exiv2::TagInfo* result = Exiv2::Internal::findTagInfo(0x9003, Exiv2::IfdId::exifId);

    EXPECT_NE(result, nullptr);

    EXPECT_EQ(result->tag_, 0x9003);

}



TEST_F(FindTagInfoTest_410, FindBoundaryTagInGps_410) {

    const Exiv2::TagInfo* result = Exiv2::Internal::findTagInfo(0x0000, Exiv2::IfdId::gpsId);

    EXPECT_NE(result, nullptr);

    EXPECT_EQ(result->tag_, 0x0000);

}
