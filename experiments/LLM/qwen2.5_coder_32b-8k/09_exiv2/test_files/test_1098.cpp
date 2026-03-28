#include <gtest/gtest.h>

#include "exiv2/image.hpp"



using namespace Exiv2;



class ImageTest : public ::testing::Test {

protected:

    std::unique_ptr<BasicIo> io = BasicIo::createMemIo();

    std::unique_ptr<Image> image = ImageFactory::open(io);

};



TEST_F(ImageTest, CheckMode_ValidMetadataId_1098) {

    MetadataId metadataId = mdExif;

    AccessMode expectedAccessMode = amRead | amWrite; // Assuming this is a valid mode for demonstration

    EXPECT_EQ(image->checkMode(metadataId), expectedAccessMode);

}



TEST_F(ImageTest, CheckMode_InvalidMetadataId_1098) {

    MetadataId metadataId = static_cast<MetadataId>(-1); // Assuming -1 is an invalid MetadataId for demonstration

    AccessMode expectedAccessMode = amNone;

    EXPECT_EQ(image->checkMode(metadataId), expectedAccessMode);

}



TEST_F(ImageTest, CheckMode_BoundaryCondition_1098) {

    MetadataId metadataId = mdXmp; // Boundary condition test with another valid MetadataId

    AccessMode expectedAccessMode = amRead | amWrite; // Assuming this is a valid mode for demonstration

    EXPECT_EQ(image->checkMode(metadataId), expectedAccessMode);

}
