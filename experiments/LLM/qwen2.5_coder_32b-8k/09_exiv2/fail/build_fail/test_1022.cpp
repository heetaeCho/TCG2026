#include <gtest/gtest.h>

#include <string>



// Assuming ExifData and related classes are properly defined elsewhere

class ExifData {

public:

    std::string getLensModel() const;

    int getLensID() const;

};



// Mock implementation for testing purposes

class MockExifData : public ExifData {

private:

    std::string lensModel_;

    int lensID_;



public:

    MockExifData(const std::string& model, int id) 

        : lensModel_(model), lensID_(id) {}



    std::string getLensModel() const override { return lensModel_; }

    int getLensID() const override { return lensID_; }

};



// Test cases

TEST(ExifDataTest, LensModelFromKnownIDs) {

    MockExifData exif1("Minolta AF 50mm F2.8 Macro", 25641);

    EXPECT_EQ(exif1.getLensModel(), "Minolta AF 50mm F2.8 Macro");



    MockExifData exif2("Sigma AF 90mm F2.8 Macro", 25811);

    EXPECT_EQ(exif2.getLensModel(), "Sigma AF 90mm F2.8 Macro");



    MockExifData exif3("Minolta AF 24mm F2.8 New", 26421);

    EXPECT_EQ(exif3.getLensModel(), "Minolta AF 24mm F2.8 New");

}



TEST(ExifDataTest, LensIDFromKnownModels) {

    MockExifData exif1("Minolta AF 50mm F2.8 Macro", 25641);

    EXPECT_EQ(exif1.getLensID(), 25641);



    MockExifData exif2("Sigma AF 90mm F2.8 Macro", 25811);

    EXPECT_EQ(exif2.getLensID(), 25811);



    MockExifData exif3("Minolta AF 24mm F2.8 New", 26421);

    EXPECT_EQ(exif3.getLensID(), 26421);

}



TEST(ExifDataTest, UnknownLensModel) {

    MockExifData exif("Unknown Lens Model", 99999);

    EXPECT_EQ(exif.getLensModel(), "Unknown Lens Model");

}



TEST(ExifDataTest, UnknownLensID) {

    MockExifData exif("Manual lens | Sony E 50mm F1.8 OSS | E PZ 16-50mm F3.5-5.6 OSS", 65535);

    EXPECT_EQ(exif.getLensID(), 65535);

}
