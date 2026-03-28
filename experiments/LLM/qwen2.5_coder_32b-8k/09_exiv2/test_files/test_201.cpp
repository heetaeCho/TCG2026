#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/exif.hpp"

#include "./TestProjects/exiv2/src/pentaxmn_int.cpp"



using namespace Exiv2;

using namespace Exiv2::Internal;



class GetKeyStringTest : public ::testing::Test {

protected:

    std::unique_ptr<ExifData> metadata;

    std::string key = "Exif.Image.Artist";



    void SetUp() override {

        metadata = std::make_unique<ExifData>();

    }

};



TEST_F(GetKeyStringTest, KeyExists_201) {

    // Arrange

    metadata->add(ExifKey(key), new Value);

    auto& exifdatum = (*metadata)[key];

    exifdatum.setValue("John Doe");



    // Act

    std::string result = getKeyString(key, metadata.get());



    // Assert

    EXPECT_EQ(result, "John Doe");

}



TEST_F(GetKeyStringTest, KeyDoesNotExist_201) {

    // Arrange & Act

    std::string result = getKeyString("NonExistentKey", metadata.get());



    // Assert

    EXPECT_TRUE(result.empty());

}



TEST_F(GetKeyStringTest, EmptyMetadata_201) {

    // Arrange & Act

    std::string result = getKeyString(key, metadata.get());



    // Assert

    EXPECT_TRUE(result.empty());

}
