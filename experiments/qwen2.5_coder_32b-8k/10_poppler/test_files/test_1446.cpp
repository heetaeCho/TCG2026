#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-link-extractor.cc"

#include "Annot.h"



using namespace Poppler;

using ::testing::NiceMock;



class MockAnnotLink : public AnnotLink {

public:

    MOCK_METHOD(LinkAction*, getAction, (), (const, override));

    MOCK_METHOD(bool, isOk, (), (const, override));

    MOCK_METHOD(void, getRect, (double* left, double* top, double* right, double* bottom), (const, override));

};



class LinkExtractorOutputDevTest : public ::testing::Test {

protected:

    void SetUp() override {

        m_data = new PageData();

        m_linkExtractor = new LinkExtractorOutputDev(m_data);

        m_linkExtractor->m_pageCropWidth = 100.0;

        m_linkExtractor->m_pageCropHeight = 200.0;

    }



    void TearDown() override {

        delete m_linkExtractor;

        delete m_data;

    }



    PageData* m_data;

    LinkExtractorOutputDev* m_linkExtractor;

};



TEST_F(LinkExtractorOutputDevTest_1446, ProcessLink_NormalOperation_1446) {

    NiceMock<MockAnnotLink> mockLink;

    EXPECT_CALL(mockLink, isOk()).WillOnce(::testing::Return(true));

    EXPECT_CALL(mockLink, getRect(::testing::_, ::testing::_, ::testing::_, ::testing::_))

        .WillOnce([](double* left, double* top, double* right, double* bottom) {

            *left = 10.0;

            *top = 20.0;

            *right = 30.0;

            *bottom = 40.0;

        });

    EXPECT_CALL(mockLink, getAction()).WillOnce(::testing::Return(nullptr));



    m_linkExtractor->processLink(&mockLink);

    EXPECT_EQ(m_linkExtractor->links().size(), 0);



    // Assuming convertLinkActionToLink returns a valid link if action is not null

    LinkAction* mockAction = new LinkAction();

    EXPECT_CALL(mockLink, getAction()).WillOnce(::testing::Return(mockAction));



    m_linkExtractor->processLink(&mockLink);

    EXPECT_EQ(m_linkExtractor->links().size(), 1);



    delete mockAction;

}



TEST_F(LinkExtractorOutputDevTest_1446, ProcessLink_BoundaryConditions_1446) {

    NiceMock<MockAnnotLink> mockLink;

    EXPECT_CALL(mockLink, isOk()).WillOnce(::testing::Return(true));

    EXPECT_CALL(mockLink, getRect(::testing::_, ::testing::_, ::testing::_, ::testing::_))

        .WillOnce([](double* left, double* top, double* right, double* bottom) {

            *left = 0.0;

            *top = 0.0;

            *right = 100.0;

            *bottom = 200.0;

        });

    EXPECT_CALL(mockLink, getAction()).WillOnce(::testing::Return(nullptr));



    m_linkExtractor->processLink(&mockLink);

    EXPECT_EQ(m_linkExtractor->links().size(), 0);



    // Assuming convertLinkActionToLink returns a valid link if action is not null

    LinkAction* mockAction = new LinkAction();

    EXPECT_CALL(mockLink, getAction()).WillOnce(::testing::Return(mockAction));



    m_linkExtractor->processLink(&mockLink);

    EXPECT_EQ(m_linkExtractor->links().size(), 1);



    delete mockAction;

}



TEST_F(LinkExtractorOutputDevTest_1446, ProcessLink_ErrorCase_NotOk_1446) {

    NiceMock<MockAnnotLink> mockLink;

    EXPECT_CALL(mockLink, isOk()).WillOnce(::testing::Return(false));



    m_linkExtractor->processLink(&mockLink);

    EXPECT_EQ(m_linkExtractor->links().size(), 0);

}



TEST_F(LinkExtractorOutputDevTest_1446, ProcessLink_ErrorCase_NullAction_1446) {

    NiceMock<MockAnnotLink> mockLink;

    EXPECT_CALL(mockLink, isOk()).WillOnce(::testing::Return(true));

    EXPECT_CALL(mockLink, getRect(::testing::_, ::testing::_, ::testing::_, ::testing::_))

        .WillOnce([](double* left, double* top, double* right, double* bottom) {

            *left = 10.0;

            *top = 20.0;

            *right = 30.0;

            *bottom = 40.0;

        });

    EXPECT_CALL(mockLink, getAction()).WillOnce(::testing::Return(nullptr));



    m_linkExtractor->processLink(&mockLink);

    EXPECT_EQ(m_linkExtractor->links().size(), 0);

}
