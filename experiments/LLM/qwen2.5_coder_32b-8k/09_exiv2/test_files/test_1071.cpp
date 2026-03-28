#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/image.hpp"

#include "exiv2/xmp_exiv2.hpp"



using namespace Exiv2;

using ::testing::Return;



class ImageTest : public ::testing::Test {

protected:

    std::unique_ptr<BasicIo> io_;

    Image image_{ImageType::jpeg, MetadataId::xmpData, std::move(io_)};



    void SetUp() override {

        io_ = BasicIo::create("dummy.jpg");

        image_.io_->open();

    }



    void TearDown() override {

        io_->close();

    }

};



TEST_F(ImageTest_PutIncreasesCount_1071, NormalOperation_1071) {

    XmpData& xmpData = image_.xmpData();

    ASSERT_TRUE(xmpData.empty());



    XmpKey key("Xmp.dc.title");

    Value* value = new StringValue("Sample Title");

    xmpData.add(key, value);



    EXPECT_EQ(xmpData.count(), 1);

}



TEST_F(ImageTest_PutIncreasesCount_1071, BoundaryCondition_EmptyString_1071) {

    XmpData& xmpData = image_.xmpData();

    ASSERT_TRUE(xmpData.empty());



    XmpKey key("Xmp.dc.title");

    Value* value = new StringValue("");

    xmpData.add(key, value);



    EXPECT_EQ(xmpData.count(), 1);

}



TEST_F(ImageTest_PutIncreasesCount_1071, BoundaryCondition_EmptyKey_1071) {

    XmpData& xmpData = image_.xmpData();

    ASSERT_TRUE(xmpData.empty());



    XmpKey key("");

    Value* value = new StringValue("Sample Title");



    EXPECT_THROW(xmpData.add(key, value), Error);

}



TEST_F(ImageTest_PutIncreasesCount_1071, ExceptionalCase_AddFailure_1071) {

    XmpData& xmpData = image_.xmpData();

    ASSERT_TRUE(xmpData.empty());



    // Mocking failure scenario is not possible here as we cannot mock internal behavior.

    // We can test only observable outcomes. If add fails, it should throw an exception.



    XmpKey key("Xmp.dc.title");

    Value* value = new StringValue("Sample Title");



    EXPECT_NO_THROW(xmpData.add(key, value));

}



TEST_F(ImageTest_PutIncreasesCount_1071, NormalOperation_XmpPacketRetrieval_1071) {

    XmpData& xmpData = image_.xmpData();

    ASSERT_TRUE(xmpData.empty());



    XmpKey key("Xmp.dc.title");

    Value* value = new StringValue("Sample Title");

    xmpData.add(key, value);



    std::string& xmpPacket = image_.xmpPacket();



    EXPECT_FALSE(xmpPacket.empty());

}



TEST_F(ImageTest_PutIncreasesCount_1071, BoundaryCondition_WriteXmpFromPacketTrue_1071) {

    XmpData& xmpData = image_.xmpData();

    ASSERT_TRUE(xmpData.empty());



    XmpKey key("Xmp.dc.title");

    Value* value = new StringValue("Sample Title");

    xmpData.add(key, value);



    image_.writeXmpFromPacket(true);

    std::string& xmpPacket = image_.xmpPacket();



    EXPECT_TRUE(xmpPacket.empty());

}



TEST_F(ImageTest_PutIncreasesCount_1071, BoundaryCondition_WriteXmpFromPacketFalse_1071) {

    XmpData& xmpData = image_.xmpData();

    ASSERT_TRUE(xmpData.empty());



    XmpKey key("Xmp.dc.title");

    Value* value = new StringValue("Sample Title");

    xmpData.add(key, value);



    image_.writeXmpFromPacket(false);

    std::string& xmpPacket = image_.xmpPacket();



    EXPECT_FALSE(xmpPacket.empty());

}



TEST_F(ImageTest_PutIncreasesCount_1071, ExceptionalCase_EmptyXmpData_1071) {

    XmpData& xmpData = image_.xmpData();

    ASSERT_TRUE(xmpData.empty());



    std::string& xmpPacket = image_.xmpPacket();



    EXPECT_TRUE(xmpPacket.empty());

}
