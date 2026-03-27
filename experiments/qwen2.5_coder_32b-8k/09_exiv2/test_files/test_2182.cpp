#include <gtest/gtest.h>

#include "exiv2/tags.hpp"

#include "exiv2/error.hpp"



namespace {



using namespace Exiv2;



class ExifKeyTest : public ::testing::Test {

protected:

    TagInfo createTagInfo(IfdId ifdId) {

        TagInfo ti;

        ti.ifdId_ = ifdId;

        return ti;

    }

};



TEST_F(ExifKeyTest, ConstructorWithValidExifIfd_2182) {

    // Arrange

    TagInfo ti = createTagInfo(IfdId::exifIfd0);



    // Act & Assert

    EXPECT_NO_THROW(ExifKey key(ti));

}



TEST_F(ExifKeyTest, ConstructorWithValidMakerIfd_2182) {

    // Arrange

    TagInfo ti = createTagInfo(IfdId::makerIfd);



    // Act & Assert

    EXPECT_NO_THROW(ExifKey key(ti));

}



TEST_F(ExifKeyTest, ConstructorWithInvalidIfdIdThrowsError_2182) {

    // Arrange

    TagInfo ti = createTagInfo(static_cast<IfdId>(99));  // Invalid IfdId



    // Act & Assert

    EXPECT_THROW(ExifKey key(ti), Error);

}



TEST_F(ExifKeyTest, ConstructorWithDefaultConstructor_2182) {

    // Arrange & Act & Assert (Not applicable as there's no default constructor)

}



TEST_F(ExifKeyTest, CopyConstructorCreatesValidInstance_2182) {

    // Arrange

    TagInfo ti = createTagInfo(IfdId::exifIfd0);

    ExifKey original(ti);



    // Act

    ExifKey copy(original);



    // Assert (No specific checks as the object should be created without throwing)

}



TEST_F(ExifKeyTest, AssignmentOperatorCreatesValidInstance_2182) {

    // Arrange

    TagInfo ti = createTagInfo(IfdId::exifIfd0);

    ExifKey original(ti);

    ExifKey copy;



    // Act

    copy = original;



    // Assert (No specific checks as the object should be created without throwing)

}



TEST_F(ExifKeyTest, GetterMethodsReturnConsistentData_2182) {

    // Arrange

    TagInfo ti;

    ti.ifdId_ = IfdId::exifIfd0;

    ti.tag_ = 256; // Example tag value



    ExifKey key(ti);



    // Act & Assert

    EXPECT_EQ(key.ifdId(), ti.ifdId_);

    EXPECT_EQ(key.tag(), ti.tag_);

}



}  // namespace
