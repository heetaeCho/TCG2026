#include <gtest/gtest.h>

#include "exiv2/exif.hpp"



using namespace Exiv2;



class ExposureModeTest_514 : public ::testing::Test {

protected:

    ExifData ed;

};



TEST_F(ExposureModeTest_514, NormalOperationWithValidKey_514) {

    const char* key = "Exif.Photo.ExposureProgram";

    Value* value = new StringValue("Manual");

    Exifdatum datum(key, value);

    ed.add(datum);



    auto result = exposureMode(ed);

    ASSERT_NE(result, ed.end());

    EXPECT_EQ(result->key(), key);

}



TEST_F(ExposureModeTest_514, NormalOperationWithMultipleKeys_514) {

    const char* keys[] = {"Exif.Image.ExposureProgram", "Exif.CanonCs.ExposureProgram"};

    Value* values[] = {new StringValue("Auto"), new StringValue("Aperture Priority")};

    Exifdatum datums[] = {Exifdatum(keys[0], values[0]), Exifdatum(keys[1], values[1])};



    ed.add(datums[0]);

    ed.add(datums[1]);



    auto result = exposureMode(ed);

    ASSERT_NE(result, ed.end());

    EXPECT_EQ(result->key(), keys[0]); // Should return the first key found

}



TEST_F(ExposureModeTest_514, BoundaryConditionWithNoKeys_514) {

    auto result = exposureMode(ed);

    EXPECT_EQ(result, ed.end()); // Expect end iterator if no keys are present

}



TEST_F(ExposureModeTest_514, BoundaryConditionWithEmptyValue_514) {

    const char* key = "Exif.Photo.ExposureProgram";

    Value* value = new StringValue(""); // Empty string as value

    Exifdatum datum(key, value);

    ed.add(datum);



    auto result = exposureMode(ed);

    ASSERT_NE(result, ed.end());

    EXPECT_EQ(result->key(), key); // Should still find the key even with empty value

}



TEST_F(ExposureModeTest_514, ExceptionalCaseWithInvalidKey_514) {

    const char* key = "Exif.Invalid.Key";

    Value* value = new StringValue("Manual");

    Exifdatum datum(key, value);

    ed.add(datum);



    auto result = exposureMode(ed);

    EXPECT_EQ(result, ed.end()); // Should not find the invalid key

}
