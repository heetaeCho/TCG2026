#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-link-extractor-private.h"



using namespace Poppler;

using ::testing::_;

using ::testing::Return;



class LinkExtractorOutputDevTest_1435 : public ::testing::Test {

protected:

    class MockPageData {};

    class MockAnnotLink {};



    std::unique_ptr<MockPageData> mockPageData;

    LinkExtractorOutputDev* linkExtractorOutputDev;



    void SetUp() override {

        mockPageData = std::make_unique<MockPageData>();

        linkExtractorOutputDev = new LinkExtractorOutputDev(mockPageData.get());

    }



    void TearDown() override {

        delete linkExtractorOutputDev;

    }

};



TEST_F(LinkExtractorOutputDevTest_1435, interpretType3Chars_ReturnsFalse_1435) {

    EXPECT_FALSE(linkExtractorOutputDev->interpretType3Chars());

}



TEST_F(LinkExtractorOutputDevTest_1435, LinksCountInitiallyZero_1435) {

    EXPECT_EQ(0, linkExtractorOutputDev->links());

}



TEST_F(LinkExtractorOutputDevTest_1435, UpsideDown_ReturnsFalseByDefault_1435) {

    EXPECT_FALSE(linkExtractorOutputDev->upsideDown());

}



TEST_F(LinkExtractorOutputDevTest_1435, UseDrawChar_ReturnsFalseByDefault_1435) {

    EXPECT_FALSE(linkExtractorOutputDev->useDrawChar());

}



// Assuming processLink modifies the links count, which is observable.

// This test checks if processLink increases the link count.

TEST_F(LinkExtractorOutputDevTest_1435, ProcessLink_IncreasesLinksCount_1435) {

    MockAnnotLink mockAnnotLink;

    linkExtractorOutputDev->processLink(&mockAnnotLink);

    EXPECT_EQ(1, linkExtractorOutputDev->links());

}



// Assuming links() returns a QList<Link*>, which can be checked for size.

TEST_F(LinkExtractorOutputDevTest_1435, Links_ReturnsEmptyListInitially_1435) {

    EXPECT_TRUE(linkExtractorOutputDev->links().isEmpty());

}
