#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "olympusmn_int.hpp"

#include <sstream>



using namespace Exiv2::Internal;

using ::testing::_;

using ::testing::Ref;



class OlympusMakerNoteTest_892 : public ::testing::Test {

protected:

    std::ostringstream os;

    Value dummyValue;  // Assuming Value is a type that can be default constructed

    const ExifData* dummyMetadata = nullptr;  // Assuming ExifData can be null or has a suitable mock

};



TEST_F(OlympusMakerNoteTest_892, Print0x0200_NormalOperation_892) {

    OlympusMakerNote::print0x0200(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(OlympusMakerNoteTest_892, Print0x0204_NormalOperation_892) {

    OlympusMakerNote::print0x0204(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(OlympusMakerNoteTest_892, Print0x1015_NormalOperation_892) {

    OlympusMakerNote::print0x1015(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(OlympusMakerNoteTest_892, Print0x0201_NormalOperation_892) {

    OlympusMakerNote::print0x0201(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(OlympusMakerNoteTest_892, Print0x0209_NormalOperation_892) {

    OlympusMakerNote::print0x0209(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(OlympusMakerNoteTest_892, PrintEq0x0301_NormalOperation_892) {

    OlympusMakerNote::printEq0x0301(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(OlympusMakerNoteTest_892, PrintCs0x0301_NormalOperation_892) {

    OlympusMakerNote::printCs0x0301(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(OlympusMakerNoteTest_892, Print0x050f_NormalOperation_892) {

    OlympusMakerNote::print0x050f(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(OlympusMakerNoteTest_892, Print0x0527_NormalOperation_892) {

    OlympusMakerNote::print0x0527(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(OlympusMakerNoteTest_892, Print0x0529_NormalOperation_892) {

    OlympusMakerNote::print0x0529(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(OlympusMakerNoteTest_892, Print0x1209_NormalOperation_892) {

    OlympusMakerNote::print0x1209(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(OlympusMakerNoteTest_892, Print0x0305_NormalOperation_892) {

    OlympusMakerNote::print0x0305(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(OlympusMakerNoteTest_892, Print0x0308_NormalOperation_892) {

    OlympusMakerNote::print0x0308(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(OlympusMakerNoteTest_892, PrintGeneric_NormalOperation_892) {

    OlympusMakerNote::printGeneric(os, dummyValue, dummyMetadata);

    EXPECT_FALSE(os.str().empty());

}
