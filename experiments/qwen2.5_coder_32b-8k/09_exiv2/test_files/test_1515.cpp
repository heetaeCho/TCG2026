#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/makernote_int.cpp"



using namespace Exiv2::Internal;



TEST_F(MakernoteFactoryTest_1515, CreateOMSystemMn2WithValidTagAndGroup_ReturnsNonNullPointer_1515) {

    auto makernote = newOMSystemMn2(0x0001, IfdId::ifdExif, IfdId::ifdExif);

    EXPECT_NE(makernote.get(), nullptr);

}



TEST_F(MakernoteFactoryTest_1515, CreateOMSystemMn2WithZeroTag_ReturnsNonNullPointer_1515) {

    auto makernote = newOMSystemMn2(0x0000, IfdId::ifdExif, IfdId::ifdExif);

    EXPECT_NE(makernote.get(), nullptr);

}



TEST_F(MakernoteFactoryTest_1515, CreateOMSystemMn2WithMaxTag_ReturnsNonNullPointer_1515) {

    auto makernote = newOMSystemMn2(0xFFFF, IfdId::ifdExif, IfdId::ifdExif);

    EXPECT_NE(makernote.get(), nullptr);

}



TEST_F(MakernoteFactoryTest_1515, CreateOMSystemMn2WithVariousGroups_ReturnsNonNullPointer_1515) {

    auto makernote1 = newOMSystemMn2(0x0001, IfdId::ifdExif, IfdId::ifdExif);

    EXPECT_NE(makernote1.get(), nullptr);



    auto makernote2 = newOMSystemMn2(0x0001, IfdId::ifdGpsInfo, IfdId::ifdGpsInfo);

    EXPECT_NE(makernote2.get(), nullptr);



    auto makernote3 = newOMSystemMn2(0x0001, IfdId::ifdInterop, IfdId::ifdInterop);

    EXPECT_NE(makernote3.get(), nullptr);



    auto makernote4 = newOMSystemMn2(0x0001, IfdId::ifdThumbnail, IfdId::ifdThumbnail);

    EXPECT_NE(makernote4.get(), nullptr);



    auto makernote5 = newOMSystemMn2(0x0001, IfdId::ifdRiffInfo, IfdId::ifdRiffInfo);

    EXPECT_NE(makernote5.get(), nullptr);



    auto makernote6 = newOMSystemMn2(0x0001, IfdId::ifdPhotoshop, IfdId::ifdPhotoshop);

    EXPECT_NE(makernote6.get(), nullptr);



    auto makernote7 = newOMSystemMn2(0x0001, IfdId::ifdDucky, IfdId::ifdDucky);

    EXPECT_NE(makernote7.get(), nullptr);

}



TEST_F(MakernoteFactoryTest_1515, CreateOMSystemMn2WithSameTagAndGroup_ReturnsDifferentInstances_1515) {

    auto makernote1 = newOMSystemMn2(0x0001, IfdId::ifdExif, IfdId::ifdExif);

    auto makernote2 = newOMSystemMn2(0x0001, IfdId::ifdExif, IfdId::ifdExif);

    EXPECT_NE(makernote1.get(), makernote2.get());

}
