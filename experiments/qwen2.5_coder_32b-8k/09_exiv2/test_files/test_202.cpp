#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/exif.hpp"

#include "TestProjects/exiv2/src/pentaxmn_int.cpp"



namespace Exiv2 {

namespace Internal {



using namespace ::testing;



class getKeyLongTest : public Test {

protected:

    std::shared_ptr<ExifData> metadata;

    std::unique_ptr<Exifdatum> exifDatum;



    void SetUp() override {

        metadata = std::make_shared<ExifData>();

        exifDatum = std::make_unique<Exifdatum>(ExifKey("Exif.Image.Key"), new UShortValue(10));

        metadata->add(*exifDatum);

    }

};



TEST_F(getKeyLongTest, KeyExistsAndIsFloat_202) {

    // Arrange

    (*exifDatum)["0"] = 42.0f;

    

    // Act

    long result = getKeyLong("Exif.Image.Key", metadata.get());

    

    // Assert

    EXPECT_EQ(result, static_cast<long>(42.0f));

}



TEST_F(getKeyLongTest, KeyExistsAndIsInt_202) {

    // Arrange

    (*exifDatum)["0"] = 15;

    

    // Act

    long result = getKeyLong("Exif.Image.Key", metadata.get());

    

    // Assert

    EXPECT_EQ(result, static_cast<long>(15));

}



TEST_F(getKeyLongTest, KeyDoesNotExist_202) {

    // Arrange & Act

    long result = getKeyLong("Nonexistent.Key", metadata.get());

    

    // Assert

    EXPECT_EQ(result, -1);

}



TEST_F(getKeyLongTest, MetadataIsEmpty_202) {

    // Arrange

    metadata->clear();

    

    // Act

    long result = getKeyLong("Exif.Image.Key", metadata.get());

    

    // Assert

    EXPECT_EQ(result, -1);

}



TEST_F(getKeyLongTest, KeyExistsButValueIsNotConvertible_202) {

    // Arrange

    (*exifDatum)["0"] = "not_a_float";

    

    // Act

    long result = getKeyLong("Exif.Image.Key", metadata.get());

    

    // Assert

    EXPECT_EQ(result, -1);

}



}  // namespace Internal

}  // namespace Exiv2
