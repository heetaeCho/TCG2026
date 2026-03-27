#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/preview.hpp"

#include "exiv2/types.hpp"



using namespace Exiv2;

using testing::NiceMock;

using testing::_;



// Mock the Loader class to simulate its behavior without modifying its internal logic.

class MockLoader : public Loader {

public:

    MOCK_METHOD(PreviewProperties, getProperties, (), const);

    MOCK_METHOD(DataBuf, getData, (), const);

    MOCK_METHOD(bool, valid, (), const);



    explicit MockLoader(PreviewId id, const Image & image) : Loader(id, image) {}

};



// Mock the Image class to simulate its behavior without modifying its internal logic.

class MockImage : public Image {

public:

    MockImage() = default;

};



// Fixture for PreviewManager tests

class PreviewManagerTest_1216 : public ::testing::Test {

protected:

    NiceMock<MockImage> mock_image_;

    std::unique_ptr<MockLoader> mock_loader_;

    PreviewManager preview_manager_;



    void SetUp() override {

        ON_CALL(*mock_loader_, valid()).WillByDefault(testing::Return(true));

        EXPECT_CALL(*mock_loader_, getData()).WillRepeatedly(testing::Return(DataBuf(10)));

        preview_manager_ = PreviewManager(mock_image_);

        mock_loader_->id_ = 42; // Assign an ID to the mock loader

    }



    void setMockLoader() {

        ON_CALL(MockLoader::create, (PreviewId, const Image &)).WillByDefault(testing::Return(std::move(mock_loader_)));

    }

};



// Test normal operation of getPreviewImage with valid PreviewProperties.

TEST_F(PreviewManagerTest_1216, GetPreviewImage_NormalOperation_1216) {

    setMockLoader();

    PreviewProperties properties;

    properties.id_ = 42;



    PreviewImage preview_image = preview_manager_.getPreviewImage(properties);



    EXPECT_EQ(preview_image.properties_.id_, properties.id_);

    EXPECT_FALSE(preview_image.buf_.empty());

}



// Test boundary condition where PreviewProperties ID is at the minimum possible value.

TEST_F(PreviewManagerTest_1216, GetPreviewImage_MinID_BoundaryCondition_1216) {

    setMockLoader();

    PreviewProperties properties;

    properties.id_ = std::numeric_limits<PreviewId>::min();



    PreviewImage preview_image = preview_manager_.getPreviewImage(properties);



    EXPECT_EQ(preview_image.properties_.id_, properties.id_);

    EXPECT_FALSE(preview_image.buf_.empty());

}



// Test boundary condition where PreviewProperties ID is at the maximum possible value.

TEST_F(PreviewManagerTest_1216, GetPreviewImage_MaxID_BoundaryCondition_1216) {

    setMockLoader();

    PreviewProperties properties;

    properties.id_ = std::numeric_limits<PreviewId>::max();



    PreviewImage preview_image = preview_manager_.getPreviewImage(properties);



    EXPECT_EQ(preview_image.properties_.id_, properties.id_);

    EXPECT_FALSE(preview_image.buf_.empty());

}



// Test exceptional case where Loader is not valid.

TEST_F(PreviewManagerTest_1216, GetPreviewImage_InvalidLoader_ExceptionalCase_1216) {

    setMockLoader();

    ON_CALL(*mock_loader_, valid()).WillByDefault(testing::Return(false));

    PreviewProperties properties;

    properties.id_ = 42;



    PreviewImage preview_image = preview_manager_.getPreviewImage(properties);



    EXPECT_EQ(preview_image.properties_.id_, properties.id_);

    EXPECT_TRUE(preview_image.buf_.empty());

}



// Test exceptional case where Loader creation fails.

TEST_F(PreviewManagerTest_1216, GetPreviewImage_LoaderCreationFailure_ExceptionalCase_1216) {

    ON_CALL(MockLoader::create, (PreviewId, const Image &)).WillByDefault(testing::Return(nullptr));

    PreviewProperties properties;

    properties.id_ = 42;



    PreviewImage preview_image = preview_manager_.getPreviewImage(properties);



    EXPECT_EQ(preview_image.properties_.id_, properties.id_);

    EXPECT_TRUE(preview_image.buf_.empty());

}



// Test external interaction where getData is called on Loader.

TEST_F(PreviewManagerTest_1216, GetPreviewImage_VerifyLoaderGetData_Call_1216) {

    setMockLoader();

    PreviewProperties properties;

    properties.id_ = 42;



    EXPECT_CALL(*mock_loader_, getData()).WillOnce(testing::Return(DataBuf(10)));



    preview_manager_.getPreviewImage(properties);

}
