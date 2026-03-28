#include <gtest/gtest.h>

#include <gmock/gmock.h>



#include "./TestProjects/poppler/qt5/src/poppler-link-extractor-private.h"

#include "./TestProjects/poppler/poppler/Page.h"



using namespace testing;

using namespace Poppler;



class MockPage : public Page {

public:

    MOCK_METHOD(int, getRotate, (), (const));

    MOCK_METHOD(double, getCropWidth, (), (const));

    MOCK_METHOD(double, getCropHeight, (), (const));

    MOCK_METHOD(const PDFRectangle*, getCropBox, (), (const));

};



class LinkExtractorOutputDevTest : public Test {

protected:

    std::unique_ptr<MockPage> mockPage;

    PageData pageData;



    void SetUp() override {

        mockPage = std::make_unique<MockPage>();

        ON_CALL(*mockPage, getRotate()).WillByDefault(Return(0));

        ON_CALL(*mockPage, getCropWidth()).WillByDefault(Return(595.0)); // A4 width

        ON_CALL(*mockPage, getCropHeight()).WillByDefault(Return(842.0)); // A4 height

        auto cropBox = std::make_unique<PDFRectangle>(0, 0, 595, 842);

        ON_CALL(*mockPage, getCropBox()).WillByDefault(Return(cropBox.get()));

    }

};



TEST_F(LinkExtractorOutputDevTest, ConstructorInitializesCropWidthAndHeight_2774) {

    LinkExtractorOutputDev linkExtractor(&pageData);

    EXPECT_DOUBLE_EQ(595.0, linkExtractor.m_pageCropWidth);

    EXPECT_DOUBLE_EQ(842.0, linkExtractor.m_pageCropHeight);

}



TEST_F(LinkExtractorOutputDevTest, ConstructorSwapsWidthAndHeightFor90DegreeRotation_2774) {

    ON_CALL(*mockPage, getRotate()).WillByDefault(Return(90));

    LinkExtractorOutputDev linkExtractor(&pageData);

    EXPECT_DOUBLE_EQ(842.0, linkExtractor.m_pageCropWidth);

    EXPECT_DOUBLE_EQ(595.0, linkExtractor.m_pageCropHeight);

}



TEST_F(LinkExtractorOutputDevTest, ConstructorSwapsWidthAndHeightFor270DegreeRotation_2774) {

    ON_CALL(*mockPage, getRotate()).WillByDefault(Return(270));

    LinkExtractorOutputDev linkExtractor(&pageData);

    EXPECT_DOUBLE_EQ(842.0, linkExtractor.m_pageCropWidth);

    EXPECT_DOUBLE_EQ(595.0, linkExtractor.m_pageCropHeight);

}



TEST_F(LinkExtractorOutputDevTest, ConstructorDoesNotSwapForOtherRotations_2774) {

    ON_CALL(*mockPage, getRotate()).WillByDefault(Return(180));

    LinkExtractorOutputDev linkExtractor(&pageData);

    EXPECT_DOUBLE_EQ(595.0, linkExtractor.m_pageCropWidth);

    EXPECT_DOUBLE_EQ(842.0, linkExtractor.m_pageCropHeight);

}
