#include <gtest/gtest.h>

#include "poppler-link-extractor-private.h"

#include <QList>



using namespace Poppler;



class LinkExtractorOutputDevTest_1433 : public ::testing::Test {

protected:

    class MockPageData {};

    MockPageData mockPageData;

    LinkExtractorOutputDev linkExtractorOutputDev{&mockPageData};



    virtual void SetUp() override {}

    virtual void TearDown() override {}

};



TEST_F(LinkExtractorOutputDevTest_1433, UpsideDownReturnsFalse_1433) {

    EXPECT_FALSE(linkExtractorOutputDev.upsideDown());

}



TEST_F(LinkExtractorOutputDevTest_1433, UseDrawCharReturnsDefault_1433) {

    // Since the implementation is a black box, we assume default behavior.

    EXPECT_TRUE(linkExtractorOutputDev.useDrawChar());  // Assuming true by default

}



TEST_F(LinkExtractorOutputDevTest_1433, InterpretType3CharsReturnsDefault_1433) {

    // Since the implementation is a black box, we assume default behavior.

    EXPECT_FALSE(linkExtractorOutputDev.interpretType3Chars());  // Assuming false by default

}



TEST_F(LinkExtractorOutputDevTest_1433, LinksInitiallyZero_1433) {

    EXPECT_EQ(linkExtractorOutputDev.links(), 0);

}



// Mocking ::AnnotLink to test processLink and links count

class MockAnnotLink : public ::AnnotLink {

public:

    MOCK_METHOD(void, accept, (OutputDev *, Catalog *), (override));

};



TEST_F(LinkExtractorOutputDevTest_1433, ProcessLinkIncreasesLinksCount_1433) {

    MockAnnotLink mockAnnotLink;

    linkExtractorOutputDev.processLink(&mockAnnotLink);

    EXPECT_EQ(linkExtractorOutputDev.links(), 1);

}



// Assuming links() returns a QList<Link *> and we can check its size

TEST_F(LinkExtractorOutputDevTest_1433, ProcessMultipleLinksIncreasesLinksCount_1433) {

    MockAnnotLink mockAnnotLink1;

    MockAnnotLink mockAnnotLink2;

    linkExtractorOutputDev.processLink(&mockAnnotLink1);

    linkExtractorOutputDev.processLink(&mockAnnotLink2);

    EXPECT_EQ(linkExtractorOutputDev.links(), 2);

}



TEST_F(LinkExtractorOutputDevTest_1433, LinksReturnsEmptyListInitially_1433) {

    QList<Link *> links = linkExtractorOutputDev.links();

    EXPECT_TRUE(links.isEmpty());

}



// Assuming processLink adds to the list of links

TEST_F(LinkExtractorOutputDevTest_1433, ProcessLinkAddsToLinksList_1433) {

    MockAnnotLink mockAnnotLink;

    linkExtractorOutputDev.processLink(&mockAnnotLink);

    QList<Link *> links = linkExtractorOutputDev.links();

    EXPECT_EQ(links.size(), 1);

}
