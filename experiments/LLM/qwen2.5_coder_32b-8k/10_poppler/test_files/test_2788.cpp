#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Annot.h"

#include "TextOutputDev.cc"



using ::testing::NiceMock;

using ::testing::_;



class MockAnnotLink : public AnnotLink {

public:

    MockAnnotLink(PDFDoc* docA, PDFRectangle* rect) : AnnotLink(docA, rect) {}

    MOCK_METHOD(LinkAction*, getAction, (), (const));

    MOCK_METHOD(AnnotLinkEffect, getLinkEffect, (), (const));

    MOCK_METHOD(AnnotQuadrilaterals*, getQuadrilaterals, (), (const));

};



class TextLinkTest : public ::testing::Test {

protected:

    PDFDoc* mockPDFDoc = nullptr;

    PDFRectangle* mockRect = nullptr;



    void SetUp() override {

        // Initialize any necessary mock objects or setup

        mockPDFDoc = new NiceMock<PDFDoc>();

        mockRect = new NiceMock<PDFRectangle>();

    }



    void TearDown() override {

        delete mockPDFDoc;

        delete mockRect;

    }

};



TEST_F(TextLinkTest_2788, ConstructorSetsCoordinatesAndLink_2788) {

    MockAnnotLink* link = new MockAnnotLink(mockPDFDoc, mockRect);

    int xMin = 10, yMin = 20, xMax = 30, yMax = 40;

    TextLink textLink(xMin, yMin, xMax, yMax, link);



    // Assuming we can verify the coordinates and link through public methods or observers

    EXPECT_EQ(textLink.xMin, xMin);

    EXPECT_EQ(textLink.yMin, yMin);

    EXPECT_EQ(textLink.xMax, xMax);

    EXPECT_EQ(textLink.yMax, yMax);

    EXPECT_EQ(textLink.link, link);



    delete link;

}



TEST_F(TextLinkTest_2788, ConstructorWithZeroCoordinates_2788) {

    MockAnnotLink* link = new MockAnnotLink(mockPDFDoc, mockRect);

    int xMin = 0, yMin = 0, xMax = 0, yMax = 0;

    TextLink textLink(xMin, yMin, xMax, yMax, link);



    EXPECT_EQ(textLink.xMin, xMin);

    EXPECT_EQ(textLink.yMin, yMin);

    EXPECT_EQ(textLink.xMax, xMax);

    EXPECT_EQ(textLink.yMax, yMax);

    EXPECT_EQ(textLink.link, link);



    delete link;

}



TEST_F(TextLinkTest_2788, ConstructorWithNegativeCoordinates_2788) {

    MockAnnotLink* link = new MockAnnotLink(mockPDFDoc, mockRect);

    int xMin = -10, yMin = -20, xMax = -30, yMax = -40;

    TextLink textLink(xMin, yMin, xMax, yMax, link);



    EXPECT_EQ(textLink.xMin, xMin);

    EXPECT_EQ(textLink.yMin, yMin);

    EXPECT_EQ(textLink.xMax, xMax);

    EXPECT_EQ(textLink.yMax, yMax);

    EXPECT_EQ(textLink.link, link);



    delete link;

}



TEST_F(TextLinkTest_2788, ConstructorWithNullLink_2788) {

    int xMin = 10, yMin = 20, xMax = 30, yMax = 40;

    TextLink textLink(xMin, yMin, xMax, yMax, nullptr);



    EXPECT_EQ(textLink.xMin, xMin);

    EXPECT_EQ(textLink.yMin, yMin);

    EXPECT_EQ(textLink.xMax, xMax);

    EXPECT_EQ(textLink.yMax, yMax);

    EXPECT_EQ(textLink.link, nullptr);

}
