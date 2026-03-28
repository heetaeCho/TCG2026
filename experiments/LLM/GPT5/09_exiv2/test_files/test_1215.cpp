#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "exiv2/preview.hpp"
#include "exiv2/types.hpp"
#include "exiv2/loader.hpp"

// Mock class for Loader to simulate behavior for testing
class MockLoader : public Exiv2::Loader {
public:
    MockLoader(Exiv2::PreviewId id, const Exiv2::Image& image) : Exiv2::Loader(id, image) {}

    MOCK_CONST_METHOD0(getProperties, const Exiv2::PreviewProperties());
    MOCK_CONST_METHOD0(getData, const Exiv2::DataBuf());
    MOCK_METHOD0(readDimensions, bool());
    MOCK_CONST_METHOD0(valid, bool());
    static MOCK_METHOD2(create, Exiv2::Loader::UniquePtr(Exiv2::PreviewId, const Exiv2::Image&));
    static MOCK_METHOD0(getNumLoaders, Exiv2::PreviewId());
};

// Test Fixture for PreviewManager tests
class PreviewManagerTest : public ::testing::Test {
protected:
    Exiv2::Image image_;  // Mock image instance
    PreviewManagerTest() : image_(/* image initialization */) {}

    void SetUp() override {
        // Set up mock behaviors if needed
    }
};

// Test case: getPreviewProperties - Normal Operation
TEST_F(PreviewManagerTest, GetPreviewProperties_Normal_1215) {
    // Arrange
    MockLoader mockLoader1(0, image_);
    MockLoader mockLoader2(1, image_);
    Exiv2::PreviewProperties expectedProps;
    expectedProps.extension_ = "jpg";
    expectedProps.id_ = 0;
    
    // Expect that create and methods are called correctly
    EXPECT_CALL(MockLoader::create(0, testing::_), Times(1));
    EXPECT_CALL(mockLoader1, readDimensions()).WillOnce(testing::Return(true));
    EXPECT_CALL(mockLoader1, getProperties()).WillOnce(testing::Return(expectedProps));
    EXPECT_CALL(mockLoader1, getData()).WillOnce(testing::Return(Exiv2::DataBuf(1024)));

    // Act
    Exiv2::PreviewManager previewManager(image_);
    auto previewPropertiesList = previewManager.getPreviewProperties();

    // Assert
    ASSERT_EQ(previewPropertiesList.size(), 1);
    EXPECT_EQ(previewPropertiesList[0].extension_, "jpg");
    EXPECT_EQ(previewPropertiesList[0].id_, 0);
}

// Test case: getPreviewProperties - Boundary Condition (empty loaders)
TEST_F(PreviewManagerTest, GetPreviewProperties_EmptyLoaders_1216) {
    // Arrange
    MockLoader mockLoader(0, image_);
    
    // Expect that no loader is created
    EXPECT_CALL(MockLoader::create(0, testing::_), Times(0));
    EXPECT_CALL(mockLoader, readDimensions()).WillOnce(testing::Return(false));

    // Act
    Exiv2::PreviewManager previewManager(image_);
    auto previewPropertiesList = previewManager.getPreviewProperties();

    // Assert
    EXPECT_TRUE(previewPropertiesList.empty());
}

// Test case: getPreviewProperties - Exceptional Case (readDimensions fails)
TEST_F(PreviewManagerTest, GetPreviewProperties_ReadDimensionsFails_1217) {
    // Arrange
    MockLoader mockLoader(0, image_);
    Exiv2::PreviewProperties expectedProps;
    
    // Expect that create and methods are called correctly
    EXPECT_CALL(MockLoader::create(0, testing::_), Times(1));
    EXPECT_CALL(mockLoader, readDimensions()).WillOnce(testing::Return(false));

    // Act
    Exiv2::PreviewManager previewManager(image_);
    auto previewPropertiesList = previewManager.getPreviewProperties();

    // Assert
    EXPECT_TRUE(previewPropertiesList.empty());
}

// Test case: getPreviewProperties - Verify External Interaction (calls create with correct parameters)
TEST_F(PreviewManagerTest, GetPreviewProperties_VerifyCreateCall_1218) {
    // Arrange
    MockLoader mockLoader(0, image_);
    Exiv2::PreviewProperties expectedProps;
    expectedProps.extension_ = "png";
    expectedProps.id_ = 1;
    
    // Expect that create is called and returns a valid loader
    EXPECT_CALL(MockLoader::create(0, testing::_), Times(1)).WillOnce(testing::Return(std::make_unique<MockLoader>(0, image_)));
    EXPECT_CALL(mockLoader, readDimensions()).WillOnce(testing::Return(true));
    EXPECT_CALL(mockLoader, getProperties()).WillOnce(testing::Return(expectedProps));
    EXPECT_CALL(mockLoader, getData()).WillOnce(testing::Return(Exiv2::DataBuf(2048)));

    // Act
    Exiv2::PreviewManager previewManager(image_);
    auto previewPropertiesList = previewManager.getPreviewProperties();

    // Assert
    ASSERT_EQ(previewPropertiesList.size(), 1);
    EXPECT_EQ(previewPropertiesList[0].extension_, "png");
    EXPECT_EQ(previewPropertiesList[0].id_, 1);
}

// Test case: getPreviewProperties - Sort order test
TEST_F(PreviewManagerTest, GetPreviewProperties_SortOrder_1219) {
    // Arrange
    MockLoader mockLoader1(0, image_);
    MockLoader mockLoader2(1, image_);
    Exiv2::PreviewProperties props1, props2;
    props1.width_ = 800;
    props1.height_ = 600;
    props2.width_ = 400;
    props2.height_ = 300;

    // Expect that create and methods are called correctly
    EXPECT_CALL(MockLoader::create(0, testing::_), Times(1));
    EXPECT_CALL(mockLoader1, readDimensions()).WillOnce(testing::Return(true));
    EXPECT_CALL(mockLoader1, getProperties()).WillOnce(testing::Return(props1));
    EXPECT_CALL(mockLoader1, getData()).WillOnce(testing::Return(Exiv2::DataBuf(1024)));
    
    EXPECT_CALL(MockLoader::create(1, testing::_), Times(1));
    EXPECT_CALL(mockLoader2, readDimensions()).WillOnce(testing::Return(true));
    EXPECT_CALL(mockLoader2, getProperties()).WillOnce(testing::Return(props2));
    EXPECT_CALL(mockLoader2, getData()).WillOnce(testing::Return(Exiv2::DataBuf(1024)));

    // Act
    Exiv2::PreviewManager previewManager(image_);
    auto previewPropertiesList = previewManager.getPreviewProperties();

    // Assert
    ASSERT_EQ(previewPropertiesList.size(), 2);
    EXPECT_EQ(previewPropertiesList[0].width_, 400);  // Smaller width first
    EXPECT_EQ(previewPropertiesList[1].width_, 800);
}