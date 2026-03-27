#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/metadatum.hpp"

#include "exiv2/exif.hpp"



using namespace Exiv2;



class MetadatumTest_110 : public ::testing::Test {

protected:

    void SetUp() override {

        metadata = std::make_unique<ExifData>();

        metadatum = std::make_unique<Metadatum>();

    }



    std::unique_ptr<ExifData> metadata;

    std::unique_ptr<Metadatum> metadatum;

};



TEST_F(MetadatumTest_110, PrintWithEmptyMetadata_110) {

    std::string result = metadatum->print(metadata.get());

    EXPECT_EQ(result, "");

}



TEST_F(MetadatumTest_110, PrintWithNonEmptyMetadata_110) {

    ExifKey key("Exif.Image.Artist");

    auto value = Value::create(undef);

    value->read("John Doe");



    metadata->add(key, value.get());

    std::string result = metadatum->print(metadata.get());



    EXPECT_NE(result, "");

}



TEST_F(MetadatumTest_110, PrintBoundaryCondition_110) {

    // Assuming print should not crash with null pointer

    std::string result = metadatum->print(nullptr);

    EXPECT_EQ(result, "");

}
