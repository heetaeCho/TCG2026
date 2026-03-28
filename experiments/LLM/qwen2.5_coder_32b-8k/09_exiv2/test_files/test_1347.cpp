#include <gtest/gtest.h>

#include "exiv2/tags.hpp"

#include "exiv2/types.hpp"



namespace Exiv2 {

    std::ostream& operator<<(std::ostream& os, const TagInfo& ti);

}



using namespace Exiv2;



class TagInfoTest_1347 : public ::testing::Test {

protected:

    TagInfo tagInfo;

};



TEST_F(TagInfoTest_1347, NormalOperation_1347) {

    tagInfo.sectionId_ = 0x01;

    tagInfo.typeId_ = static_cast<TypeId>(2);

    tagInfo.count_ = 1;

    tagInfo.printFct_ = nullptr;



    ExifKey exifKey(tagInfo);



    std::ostringstream oss;

    oss << tagInfo;



    EXPECT_EQ(oss.str(), R"(TagName,0x0001,0x0001,GroupName,KeyName,typeName,"TagDescription")");

}



TEST_F(TagInfoTest_1347, BoundaryConditions_EmptyStrings_1347) {

    TagInfo tagInfo;

    tagInfo.sectionId_ = 0x01;

    tagInfo.typeId_ = static_cast<TypeId>(2);

    tagInfo.count_ = 1;

    tagInfo.printFct_ = nullptr;



    ExifKey exifKey(tagInfo);



    std::ostringstream oss;

    oss << tagInfo;



    EXPECT_EQ(oss.str(), R"(,0x0000,0x0000,,,"")");

}



TEST_F(TagInfoTest_1347, BoundaryConditions_MaxValues_1347) {

    TagInfo tagInfo;

    tagInfo.sectionId_ = 0xFFFF;

    tagInfo.typeId_ = static_cast<TypeId>(255);

    tagInfo.count_ = 65535;

    tagInfo.printFct_ = nullptr;



    ExifKey exifKey(tagInfo);



    std::ostringstream oss;

    oss << tagInfo;



    EXPECT_EQ(oss.str(), R"(TagName,0xffff,0xffff,GroupName,KeyName,typeName,"TagDescription")");

}



TEST_F(TagInfoTest_1347, ExceptionalCases_TypeIdOutOfRange_1347) {

    TagInfo tagInfo;

    tagInfo.sectionId_ = 0x01;

    tagInfo.typeId_ = static_cast<TypeId>(256); // Assuming TypeId is uint8_t and out of range

    tagInfo.count_ = 1;

    tagInfo.printFct_ = nullptr;



    ExifKey exifKey(tagInfo);



    std::ostringstream oss;

    oss << tagInfo;



    EXPECT_EQ(oss.str(), R"(TagName,0x0001,0x0001,GroupName,KeyName,,TagDescription")");

}



TEST_F(TagInfoTest_1347, VerificationOfExternalInteractions_DefaultTypeName_1347) {

    TagInfo tagInfo;

    tagInfo.sectionId_ = 0x01;

    tagInfo.typeId_ = static_cast<TypeId>(2);

    tagInfo.count_ = 1;

    tagInfo.printFct_ = nullptr;



    ExifKey exifKey(tagInfo);



    std::ostringstream oss;

    oss << tagInfo;



    EXPECT_EQ(oss.str(), R"(TagName,0x0001,0x0001,GroupName,KeyName,typeName,"TagDescription")");

}



TEST_F(TagInfoTest_1347, VerificationOfExternalInteractions_EmptyTypeDesc_1347) {

    TagInfo tagInfo;

    tagInfo.sectionId_ = 0x01;

    tagInfo.typeId_ = static_cast<TypeId>(255); // Assuming this typeId returns an empty string

    tagInfo.count_ = 1;

    tagInfo.printFct_ = nullptr;



    ExifKey exifKey(tagInfo);



    std::ostringstream oss;

    oss << tagInfo;



    EXPECT_EQ(oss.str(), R"(TagName,0x0001,0x0001,GroupName,KeyName,,TagDescription")");

}



TEST_F(TagInfoTest_1347, VerificationOfExternalInteractions_EscapedDesc_1347) {

    TagInfo tagInfo;

    tagInfo.sectionId_ = 0x01;

    tagInfo.typeId_ = static_cast<TypeId>(2);

    tagInfo.count_ = 1;

    tagInfo.printFct_ = nullptr;



    ExifKey exifKey(tagInfo);



    std::ostringstream oss;

    oss << tagInfo;



    EXPECT_EQ(oss.str(), R"(TagName,0x0001,0x0001,GroupName,KeyName,typeName,"TagDescription")");

}
