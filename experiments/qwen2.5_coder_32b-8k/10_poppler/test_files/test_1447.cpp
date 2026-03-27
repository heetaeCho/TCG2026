#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-link-extractor-private.h"



using namespace Poppler;

using ::testing::Test;



class LinkExtractorOutputDevTest : public Test {

protected:

    // Mock PageData if necessary, though it's not required based on given interface

    class MockPageData { /* ... */ };

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



TEST_F(LinkExtractorOutputDevTest_1447, LinksInitiallyEmpty_1447) {

    QList<Link*> links = linkExtractorOutputDev->links();

    EXPECT_TRUE(links.isEmpty());

}



TEST_F(LinkExtractorOutputDevTest_1447, ProcessLinkAndGetLinks_1447) {

    // Assuming processLink adds a Link to m_links

    AnnotLink mockAnnotLink;  // Mock or create an actual instance of AnnotLink

    linkExtractorOutputDev->processLink(&mockAnnotLink);

    

    QList<Link*> links = linkExtractorOutputDev->links();

    EXPECT_EQ(links.size(), 1);

}



TEST_F(LinkExtractorOutputDevTest_1447, LinksClearedAfterRetrieval_1447) {

    AnnotLink mockAnnotLink;  // Mock or create an actual instance of AnnotLink

    linkExtractorOutputDev->processLink(&mockAnnotLink);



    QList<Link*> links = linkExtractorOutputDev->links();

    EXPECT_EQ(links.size(), 1);

    

    links = linkExtractorOutputDev->links();  // Retrieve again to check clearing

    EXPECT_TRUE(links.isEmpty());

}



// Assuming there are boundary conditions or error cases, but no specific ones were identified.

// If processLink could fail in certain ways, those should be tested here.

```


