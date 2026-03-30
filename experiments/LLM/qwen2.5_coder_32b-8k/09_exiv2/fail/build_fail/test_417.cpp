#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/nikonmn_int.hpp"

#include <sstream>



using namespace Exiv2::Internal;

using ::testing::_;



class Nikon1MakerNoteTest_417 : public ::testing::Test {

protected:

    Nikon1MakerNote nikon1MakerNote;

};



TEST_F(Nikon1MakerNoteTest_417, TagList_ReturnsStaticTagInfo_417) {

    auto tagList = Nikon1MakerNote::tagList();

    EXPECT_NE(tagList, nullptr);

}



TEST_F(Nikon1MakerNoteTest_417, Print0x0002_OutputStreamIsModified_417) {

    std::ostringstream os;

    Value value; // Assuming Value is a valid type

    const ExifData* exifData = nullptr;



    nikon1MakerNote.print0x0002(os, value, exifData);



    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon1MakerNoteTest_417, Print0x0007_OutputStreamIsModified_417) {

    std::ostringstream os;

    Value value; // Assuming Value is a valid type

    const ExifData* exifData = nullptr;



    nikon1MakerNote.print0x0007(os, value, exifData);



    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon1MakerNoteTest_417, Print0x0085_OutputStreamIsModified_417) {

    std::ostringstream os;

    Value value; // Assuming Value is a valid type

    const ExifData* exifData = nullptr;



    nikon1MakerNote.print0x0085(os, value, exifData);



    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon1MakerNoteTest_417, Print0x0086_OutputStreamIsModified_417) {

    std::ostringstream os;

    Value value; // Assuming Value is a valid type

    const ExifData* exifData = nullptr;



    nikon1MakerNote.print0x0086(os, value, exifData);



    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon1MakerNoteTest_417, Print0x0088_OutputStreamIsModified_417) {

    std::ostringstream os;

    Value value; // Assuming Value is a valid type

    const ExifData* exifData = nullptr;



    nikon1MakerNote.print0x0088(os, value, exifData);



    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon1MakerNoteTest_417, PrintBarValue_OutputStreamIsModified_417) {

    std::ostringstream os;

    Value value; // Assuming Value is a valid type

    const ExifData* exifData = nullptr;



    nikon1MakerNote.printBarValue(os, value, exifData);



    EXPECT_FALSE(os.str().empty());

}



// Boundary conditions and error cases can be added if there are specific known conditions or exceptions that the interface handles.

// However, based on the provided information, no specific boundary conditions or errors are known to test for.
