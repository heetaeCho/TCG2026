#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-annot.cc"

#include "Annot.h"

#include "poppler-private.h"



using ::testing::_;

using ::testing::NiceMock;

using ::testing::Return;



// Mock classes for dependencies

class MockPopplerDocument : public PopplerDocument {

public:

    MOCK_METHOD0(output_dev, CairoOutputDev*());

};



class MockLinkAction : public LinkAction {

public:

    MockLinkAction() = default;

    ~MockLinkAction() override = default;

};



class MockAnnotScreen : public AnnotScreen {

public:

    MockAnnotScreen(PDFDoc *docA, PDFRectangle *rect) : AnnotScreen(docA, rect) {}

    MOCK_METHOD0(getAction, LinkAction*());

};



TEST_F(PopplerAnnotTest_2052, NormalOperationWithAction_2052) {

    NiceMock<MockPopplerDocument> mock_doc;

    MockAnnotScreen mock_annot_screen(nullptr, nullptr);

    MockLinkAction mock_action;



    EXPECT_CALL(mock_annot_screen, getAction()).WillOnce(Return(&mock_action));



    PopplerAnnot* poppler_annot = _poppler_annot_screen_new(&mock_doc, std::make_shared<MockAnnotScreen>(nullptr, nullptr));

    ASSERT_NE(poppler_annot, nullptr);

    EXPECT_NE(poppler_annot->action, nullptr);



    delete poppler_annot;

}



TEST_F(PopplerAnnotTest_2052, NormalOperationWithoutAction_2052) {

    NiceMock<MockPopplerDocument> mock_doc;

    MockAnnotScreen mock_annot_screen(nullptr, nullptr);



    EXPECT_CALL(mock_annot_screen, getAction()).WillOnce(Return(static_cast<LinkAction*>(nullptr)));



    PopplerAnnot* poppler_annot = _poppler_annot_screen_new(&mock_doc, std::make_shared<MockAnnotScreen>(nullptr, nullptr));

    ASSERT_NE(poppler_annot, nullptr);

    EXPECT_EQ(poppler_annot->action, nullptr);



    delete poppler_annot;

}



TEST_F(PopplerAnnotTest_2052, BoundaryConditionNullDocument_2052) {

    MockAnnotScreen mock_annot_screen(nullptr, nullptr);

    EXPECT_CALL(mock_annot_screen, getAction()).WillOnce(Return(static_cast<LinkAction*>(nullptr)));



    PopplerAnnot* poppler_annot = _poppler_annot_screen_new(nullptr, std::make_shared<MockAnnotScreen>(nullptr, nullptr));

    ASSERT_NE(poppler_annot, nullptr);

    EXPECT_EQ(poppler_annot->action, nullptr);



    delete poppler_annot;

}



TEST_F(PopplerAnnotTest_2052, BoundaryConditionNullAnnotation_2052) {

    NiceMock<MockPopplerDocument> mock_doc;



    PopplerAnnot* poppler_annot = _poppler_annot_screen_new(&mock_doc, nullptr);

    EXPECT_EQ(poppler_annot, nullptr);

}
