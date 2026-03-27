#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Mock LinkRendition class to simulate behavior for testing purposes

class MockLinkRendition : public LinkRendition {

public:

    MOCK_CONST_METHOD0(getOperation, RenditionOperation());

    MOCK_CONST_METHOD0(getMedia, const MediaRendition*());

};



TEST_F(PopplerActionTest_2300, BuildRendition_SetsCorrectOperation_2300) {

    MockLinkRendition mock_link;

    PopplerAction action;



    RenditionOperation expected_op = RenditionOperation::ACTIVATE;

    EXPECT_CALL(mock_link, getOperation()).WillOnce(testing::Return(expected_op));

    EXPECT_CALL(mock_link, getMedia()).WillOnce(testing::Return(nullptr));



    build_rendition(&action, &mock_link);



    ASSERT_EQ(action.rendition.op, expected_op);

}



TEST_F(PopplerActionTest_2300, BuildRendition_SetsCorrectMedia_2300) {

    MockLinkRendition mock_link;

    PopplerAction action;



    const MediaRendition* expected_media = reinterpret_cast<const MediaRendition*>(0x12345678); // Arbitrary address

    EXPECT_CALL(mock_link, getOperation()).WillOnce(testing::Return(RenditionOperation::ACTIVATE));

    EXPECT_CALL(mock_link, getMedia()).WillOnce(testing::Return(expected_media));



    build_rendition(&action, &mock_link);



    ASSERT_EQ(action.rendition.media, expected_media);

}



TEST_F(PopplerActionTest_2300, BuildRendition_NoMedia_SetsNull_2300) {

    MockLinkRendition mock_link;

    PopplerAction action;



    EXPECT_CALL(mock_link, getOperation()).WillOnce(testing::Return(RenditionOperation::ACTIVATE));

    EXPECT_CALL(mock_link, getMedia()).WillOnce(testing::Return(nullptr));



    build_rendition(&action, &mock_link);



    ASSERT_EQ(action.rendition.media, nullptr);

}
