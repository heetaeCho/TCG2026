#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <sstream>

#include "nikonmn_int.hpp"



namespace Exiv2 {

    class Value;

    class ExifData;

}



using namespace testing;



TEST(Nikon3MakerNoteTest_428, TagListFiReturnsConstantValue_428) {

    auto result = Exiv2::Internal::Nikon3MakerNote::tagListFi();

    EXPECT_TRUE(result != nullptr);

}



TEST(Nikon3MakerNoteTest_428, PrintIiIsoNormalOperation_428) {

    std::ostringstream os;

    Exiv2::Value value; // Assuming Value is default constructible

    const Exiv2::ExifData* metadata = nullptr;

    auto& result = Exiv2::Internal::Nikon3MakerNote::printIiIso(os, value, metadata);

    EXPECT_EQ(&result, &os); // Check if the function returns the same stream object

}



TEST(Nikon3MakerNoteTest_428, PrintAf2AreaModeWithMetadata_428) {

    std::ostringstream os;

    Exiv2::Value value; // Assuming Value is default constructible

    const Exiv2::ExifData metadata; // Mocking an empty ExifData object

    auto& result = Exiv2::Internal::Nikon3MakerNote::printAf2AreaMode(os, value, &metadata);

    EXPECT_EQ(&result, &os); // Check if the function returns the same stream object

}



TEST(Nikon3MakerNoteTest_428, PrintLensIdWithMetadataAndGroup_428) {

    std::ostringstream os;

    Exiv2::Value value; // Assuming Value is default constructible

    const Exiv2::ExifData metadata; // Mocking an empty ExifData object

    auto& result = Exiv2::Internal::Nikon3MakerNote::printLensId(os, value, &metadata, "Group1");

    EXPECT_EQ(&result, &os); // Check if the function returns the same stream object

}



TEST(Nikon3MakerNoteTest_428, PrintExternalFlashData1Fl6WithMetadata_428) {

    std::ostringstream os;

    Exiv2::Value value; // Assuming Value is default constructible

    const Exiv2::ExifData metadata; // Mocking an empty ExifData object

    auto& result = Exiv2::Internal::Nikon3MakerNote::printExternalFlashData1Fl6(os, value, &metadata);

    EXPECT_EQ(&result, &os); // Check if the function returns the same stream object

}



TEST(Nikon3MakerNoteTest_428, PrintFlashGroupAControlDataWithMetadata_428) {

    std::ostringstream os;

    Exiv2::Value value; // Assuming Value is default constructible

    const Exiv2::ExifData metadata; // Mocking an empty ExifData object

    auto& result = Exiv2::Internal::Nikon3MakerNote::printFlashGroupAControlData(os, value, &metadata);

    EXPECT_EQ(&result, &os); // Check if the function returns the same stream object

}



TEST(Nikon3MakerNoteTest_428, PrintPictureControlNormalOperation_428) {

    std::ostringstream os;

    Exiv2::Value value; // Assuming Value is default constructible

    const Exiv2::ExifData* metadata = nullptr;

    auto& result = Exiv2::Internal::Nikon3MakerNote::printPictureControl(os, value, metadata);

    EXPECT_EQ(&result, &os); // Check if the function returns the same stream object

}



TEST(Nikon3MakerNoteTest_428, PrintCameraExposureCompensationNormalOperation_428) {

    std::ostringstream os;

    Exiv2::Value value; // Assuming Value is default constructible

    const Exiv2::ExifData* metadata = nullptr;

    auto& result = Exiv2::Internal::Nikon3MakerNote::printCameraExposureCompensation(os, value, metadata);

    EXPECT_EQ(&result, &os); // Check if the function returns the same stream object

}
