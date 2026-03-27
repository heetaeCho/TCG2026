#include <gtest/gtest.h>

#include "exiv2/exif.hpp"

#include "./TestProjects/exiv2/src/easyaccess.cpp"



using namespace Exiv2;



class MeteringModeTest_524 : public ::testing::Test {

protected:

    ExifData ed;

};



TEST_F(MeteringModeTest_524, NormalOperation_524) {

    const char* key = "Exif.Photo.MeteringMode";

    Exifdatum exifDatum(key, 1);

    ed.add(exifDatum);



    auto result = meteringMode(ed);

    EXPECT_NE(result, ed.end());

    EXPECT_EQ(result->key(), key);

}



TEST_F(MeteringModeTest_524, BoundaryConditions_EmptyExifData_524) {

    auto result = meteringMode(ed);

    EXPECT_EQ(result, ed.end());

}



TEST_F(MeteringModeTest_524, BoundaryConditions_LastKeyPresent_524) {

    const char* key = "Exif.Sony1MltCsA100.MeteringMode";

    Exifdatum exifDatum(key, 1);

    ed.add(exifDatum);



    auto result = meteringMode(ed);

    EXPECT_NE(result, ed.end());

    EXPECT_EQ(result->key(), key);

}



TEST_F(MeteringModeTest_524, ExceptionalOrErrorCase_KeyNotPresent_524) {

    const char* key = "Exif.NonExistent.MeteringMode";

    Exifdatum exifDatum(key, 1);

    ed.add(exifDatum);



    auto result = meteringMode(ed);

    EXPECT_EQ(result, ed.end());

}



TEST_F(MeteringModeTest_524, VerificationOfExternalInteractions_NoInteraction_524) {

    // Since there are no external collaborators involved, this test is implicitly covered by the other tests.

    // We assume that the function does not interact with any external systems or dependencies.

}
