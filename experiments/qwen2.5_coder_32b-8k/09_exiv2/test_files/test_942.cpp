#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/canonmn_int.hpp"

#include "exiv2/exif.hpp"

#include "exiv2/tags.hpp"

#include "exiv2/value.hpp"



using namespace Exiv2;

using namespace Exiv2::Internal;



class CanonMakerNoteTest_942 : public ::testing::Test {

protected:

    std::ostringstream os;

    Value value;

    ExifData metadata;



    void SetUp() override {

        // Initialize the value with a valid type and count for testing

        value = Value(unsignedShort);

    }

};



TEST_F(CanonMakerNoteTest_942, NullMetadata_942) {

    EXPECT_EQ(&os, &CanonMakerNote::printFocalLength(os, value, nullptr));

}



TEST_F(CanonMakerNoteTest_942, InvalidCount_942) {

    value = Value(unsignedShort);

    metadata.add(ExifKey("Exif.CanonCs.Lens"), new UShortValue({10, 20}));

    EXPECT_EQ(&os, &CanonMakerNote::printFocalLength(os, value, &metadata));

}



TEST_F(CanonMakerNoteTest_942, InvalidTypeId_942) {

    value = Value(asciiString);

    metadata.add(ExifKey("Exif.CanonCs.Lens"), new UShortValue({10, 20, 30}));

    EXPECT_EQ(&os, &CanonMakerNote::printFocalLength(os, value, &metadata));

}



TEST_F(CanonMakerNoteTest_942, LensNotFound_942) {

    metadata.add(ExifKey("Exif.CanonCs.SomeOtherKey"), new UShortValue({10, 20, 30}));

    EXPECT_EQ(&os, &CanonMakerNote::printFocalLength(os, value, &metadata));

}



TEST_F(CanonMakerNoteTest_942, LensInvalidCount_942) {

    metadata.add(ExifKey("Exif.CanonCs.Lens"), new UShortValue({10}));

    EXPECT_EQ(&os, &CanonMakerNote::printFocalLength(os, value, &metadata));

}



TEST_F(CanonMakerNoteTest_942, LensInvalidTypeId_942) {

    metadata.add(ExifKey("Exif.CanonCs.Lens"), new AsciiValue("invalid"));

    EXPECT_EQ(&os, &CanonMakerNote::printFocalLength(os, value, &metadata));

}



TEST_F(CanonMakerNoteTest_942, LensFuZero_942) {

    metadata.add(ExifKey("Exif.CanonCs.Lens"), new UShortValue({10, 20, 0}));

    EXPECT_EQ(&os, &CanonMakerNote::printFocalLength(os, value, &metadata));

}



TEST_F(CanonMakerNoteTest_942, ValidInput_942) {

    value = Value(unsignedShort);

    metadata.add(ExifKey("Exif.CanonCs.Lens"), new UShortValue({10, 20, 50}));

    value.setValue(new UShortValue({300}));

    EXPECT_EQ(&os, &CanonMakerNote::printFocalLength(os, value, &metadata));

    EXPECT_EQ(os.str(), "6.0 mm");

}



TEST_F(CanonMakerNoteTest_942, BoundaryCount_942) {

    metadata.add(ExifKey("Exif.CanonCs.Lens"), new UShortValue({10, 20, 30, 40}));

    EXPECT_EQ(&os, &CanonMakerNote::printFocalLength(os, value, &metadata));

}



TEST_F(CanonMakerNoteTest_942, BoundaryFu_942) {

    metadata.add(ExifKey("Exif.CanonCs.Lens"), new UShortValue({10, 20, 30}));

    EXPECT_EQ(&os, &CanonMakerNote::printFocalLength(os, value, &metadata));

}
