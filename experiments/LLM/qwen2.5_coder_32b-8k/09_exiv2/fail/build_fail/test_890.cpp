#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/exiv2/src/olympusmn_int.hpp"

#include <sstream>



using namespace Exiv2::Internal;

using ::testing::_;

using ::testing::Ref;



class OlympusMakerNoteTest_890 : public ::testing::Test {

protected:

    Value dummyValue;

    const ExifData* dummyMetadata = nullptr;

};



TEST_F(OlympusMakerNoteTest_890, PrintFunctionsReturnStreamReference_890) {

    std::ostringstream os;



    EXPECT_EQ(&os, &OlympusMakerNote::print0x0200(os, dummyValue, dummyMetadata));

    EXPECT_EQ(&os, &OlympusMakerNote::print0x0204(os, dummyValue, dummyMetadata));

    EXPECT_EQ(&os, &OlympusMakerNote::print0x1015(os, dummyValue, dummyMetadata));

    EXPECT_EQ(&os, &OlympusMakerNote::print0x0201(os, dummyValue, dummyMetadata));

    EXPECT_EQ(&os, &OlympusMakerNote::print0x0209(os, dummyValue, dummyMetadata));

    EXPECT_EQ(&os, &OlympusMakerNote::printEq0x0301(os, dummyValue, dummyMetadata));

    EXPECT_EQ(&os, &OlympusMakerNote::printCs0x0301(os, dummyValue, dummyMetadata));

    EXPECT_EQ(&os, &OlympusMakerNote::print0x050f(os, dummyValue, dummyMetadata));

    EXPECT_EQ(&os, &OlympusMakerNote::print0x0527(os, dummyValue, dummyMetadata));

    EXPECT_EQ(&os, &OlympusMakerNote::print0x0529(os, dummyValue, dummyMetadata));

    EXPECT_EQ(&os, &OlympusMakerNote::print0x1209(os, dummyValue, dummyMetadata));

    EXPECT_EQ(&os, &OlympusMakerNote::print0x0305(os, dummyValue, dummyMetadata));

    EXPECT_EQ(&os, &OlympusMakerNote::print0x0308(os, dummyValue, dummyMetadata));

    EXPECT_EQ(&os, &OlympusMakerNote::printGeneric(os, dummyValue, dummyMetadata));

}



TEST_F(OlympusMakerNoteTest_890, TagListFunctionsReturnTagInfoArrays_890) {

    auto tagListRd2 = OlympusMakerNote::tagListRd2();



    EXPECT_TRUE(tagListRd2 != nullptr);

}



// Since the implementation is a black box and we can't infer internal behavior,

// we cannot directly test for specific outputs or side effects of the print functions.

// We can only verify that they return a stream reference as expected.



TEST_F(OlympusMakerNoteTest_890, TagListFunctionsReturnNonEmptyArrays_890) {

    EXPECT_TRUE(OlympusMakerNote::tagListRd2() != nullptr);

}
