#include <gtest/gtest.h>

#include "exiv2/preview.hpp"

#include "exiv2/types.hpp"



namespace Exiv2 {



class MockLoader : public Loader {

public:

    MOCK_METHOD(bool, valid, (), (const, override));

    MOCK_METHOD(bool, readDimensions, (), (override));

    MOCK_METHOD(PreviewProperties, getProperties, (), (const, override));

    MOCK_METHOD(DataBuf, getData, (), (override));



    static UniquePtr create(PreviewId id, const Image &image) {

        auto mockLoader = std::make_unique<MockLoader>(id, image);

        return mockLoader;

    }



protected:

    MockLoader(PreviewId id, const Image &image) : Loader(id, image) {}

};



class PreviewManagerTest_1215 : public ::testing::Test {

protected:

    class MockImage {};

    MockImage mockImage_;

    PreviewManager previewManager_{mockImage_};

};



TEST_F(PreviewManagerTest_1215, NoLoadersAvailable_1215) {

    EXPECT_CALL(*Loader::create(0, mockImage_), readDimensions()).WillOnce(testing::Return(false));

    EXPECT_EQ(previewManager_.getPreviewProperties().size(), 0);

}



TEST_F(PreviewManagerTest_1215, SingleValidLoader_1215) {

    PreviewProperties expectedProps;

    expectedProps.extension_ = "jpg";

    expectedProps.id_ = 0;



    DataBuf expectedData(10);



    EXPECT_CALL(*Loader::create(0, mockImage_), readDimensions()).WillOnce(testing::Return(true));

    EXPECT_CALL(*Loader::create(0, mockImage_), getProperties()).WillOnce(testing::Return(expectedProps));

    EXPECT_CALL(*Loader::create(0, mockImage_), getData()).WillOnce(testing::Return(expectedData));



    auto propertiesList = previewManager_.getPreviewProperties();

    ASSERT_EQ(propertiesList.size(), 1);

    EXPECT_EQ(propertiesList[0].extension_, expectedProps.extension_);

    EXPECT_EQ(propertiesList[0].id_, expectedProps.id_);

}



TEST_F(PreviewManagerTest_1215, MultipleLoaders_1215) {

    PreviewProperties props1, props2;

    props1.extension_ = "jpg";

    props1.width_ = 320;

    props1.height_ = 240;

    props1.id_ = 0;



    PreviewProperties props2;

    props2.extension_ = "png";

    props2.width_ = 640;

    props2.height_ = 480;

    props2.id_ = 1;



    DataBuf data1(10);

    DataBuf data2(20);



    EXPECT_CALL(*Loader::create(0, mockImage_), readDimensions()).WillOnce(testing::Return(true));

    EXPECT_CALL(*Loader::create(0, mockImage_), getProperties()).WillOnce(testing::Return(props1));

    EXPECT_CALL(*Loader::create(0, mockImage_), getData()).WillOnce(testing::Return(data1));



    EXPECT_CALL(*Loader::create(1, mockImage_), readDimensions()).WillOnce(testing::Return(true));

    EXPECT_CALL(*Loader::create(1, mockImage_), getProperties()).WillOnce(testing::Return(props2));

    EXPECT_CALL(*Loader::create(1, mockImage_), getData()).WillOnce(testing::Return(data2));



    auto propertiesList = previewManager_.getPreviewProperties();

    ASSERT_EQ(propertiesList.size(), 2);

    EXPECT_EQ(propertiesList[0].extension_, props1.extension_);

    EXPECT_EQ(propertiesList[1].extension_, props2.extension_);

}



TEST_F(PreviewManagerTest_1215, LoadersWithInvalidDimensions_1215) {

    PreviewProperties expectedProps;

    expectedProps.extension_ = "jpg";

    expectedProps.id_ = 0;



    DataBuf expectedData(10);



    EXPECT_CALL(*Loader::create(0, mockImage_), readDimensions()).WillOnce(testing::Return(false));

    EXPECT_CALL(*Loader::create(1, mockImage_), readDimensions()).WillOnce(testing::Return(true));

    EXPECT_CALL(*Loader::create(1, mockImage_), getProperties()).WillOnce(testing::Return(expectedProps));

    EXPECT_CALL(*Loader::create(1, mockImage_), getData()).WillOnce(testing::Return(expectedData));



    auto propertiesList = previewManager_.getPreviewProperties();

    ASSERT_EQ(propertiesList.size(), 1);

    EXPECT_EQ(propertiesList[0].extension_, expectedProps.extension_);

}



TEST_F(PreviewManagerTest_1215, SortingByArea_1215) {

    PreviewProperties props1, props2;

    props1.width_ = 320;

    props1.height_ = 240; // Area: 76800

    props1.id_ = 0;



    props2.width_ = 160;

    props2.height_ = 120; // Area: 19200

    props2.id_ = 1;



    DataBuf data1(10);

    DataBuf data2(20);



    EXPECT_CALL(*Loader::create(0, mockImage_), readDimensions()).WillOnce(testing::Return(true));

    EXPECT_CALL(*Loader::create(0, mockImage_), getProperties()).WillOnce(testing::Return(props1));

    EXPECT_CALL(*Loader::create(0, mockImage_), getData()).WillOnce(testing::Return(data1));



    EXPECT_CALL(*Loader::create(1, mockImage_), readDimensions()).WillOnce(testing::Return(true));

    EXPECT_CALL(*Loader::create(1, mockImage_), getProperties()).WillOnce(testing::Return(props2));

    EXPECT_CALL(*Loader::create(1, mockImage_), getData()).WillOnce(testing::Return(data2));



    auto propertiesList = previewManager_.getPreviewProperties();

    ASSERT_EQ(propertiesList.size(), 2);

    EXPECT_EQ(propertiesList[0].width_ * propertiesList[0].height_, 19200);

    EXPECT_EQ(propertiesList[1].width_ * propertiesList[1].height_, 76800);

}



} // namespace Exiv2
