#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/poppler/qt5/src/poppler-link.cc"

#include "./TestProjects/poppler/poppler/Page.h"



using namespace Poppler;

using ::testing::NiceMock;



class MockPage : public Page {

public:

    MOCK_METHOD(void, getDefaultCTM, (double *ctm, double hDPI, double vDPI, int rotate, bool useMediaBox, bool upsideDown), (override));

};



TEST_F(MockPageTest_1251, NormalOperation_1251) {

    MockPage mockPage(nullptr, 0, Object(), Ref(), std::make_unique<PageAttrs>());

    double ctm[6] = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};

    EXPECT_CALL(mockPage, getDefaultCTM(ctm, 72.0, 72.0, 0, false, true)).Times(1);

    

    int xd = 0;

    int yd = 0;

    cvtUserToDev(&mockPage, 1.0, 1.0, &xd, &yd);

    

    EXPECT_EQ(xd, 1);

    EXPECT_EQ(yd, 1);

}



TEST_F(MockPageTest_1251, BoundaryConditions_ZeroValues_1251) {

    MockPage mockPage(nullptr, 0, Object(), Ref(), std::make_unique<PageAttrs>());

    double ctm[6] = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};

    EXPECT_CALL(mockPage, getDefaultCTM(ctm, 72.0, 72.0, 0, false, true)).Times(1);

    

    int xd = 0;

    int yd = 0;

    cvtUserToDev(&mockPage, 0.0, 0.0, &xd, &yd);

    

    EXPECT_EQ(xd, 0);

    EXPECT_EQ(yd, 0);

}



TEST_F(MockPageTest_1251, BoundaryConditions_MaxValues_1251) {

    MockPage mockPage(nullptr, 0, Object(), Ref(), std::make_unique<PageAttrs>());

    double ctm[6] = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};

    EXPECT_CALL(mockPage, getDefaultCTM(ctm, 72.0, 72.0, 0, false, true)).Times(1);

    

    int xd = 0;

    int yd = 0;

    cvtUserToDev(&mockPage, std::numeric_limits<double>::max(), std::numeric_limits<double>::max(), &xd, &yd);

    

    // Expecting overflow or max integer value

    EXPECT_EQ(xd, std::numeric_limits<int>::max());

    EXPECT_EQ(yd, std::numeric_limits<int>::max());

}



TEST_F(MockPageTest_1251, BoundaryConditions_NegativeValues_1251) {

    MockPage mockPage(nullptr, 0, Object(), Ref(), std::make_unique<PageAttrs>());

    double ctm[6] = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};

    EXPECT_CALL(mockPage, getDefaultCTM(ctm, 72.0, 72.0, 0, false, true)).Times(1);

    

    int xd = 0;

    int yd = 0;

    cvtUserToDev(&mockPage, -1.0, -1.0, &xd, &yd);

    

    EXPECT_EQ(xd, -1);

    EXPECT_EQ(yd, -1);

}



TEST_F(MockPageTest_1251, CtmTransformation_1251) {

    MockPage mockPage(nullptr, 0, Object(), Ref(), std::make_unique<PageAttrs>());

    double ctm[6] = {2.0, 0.0, 0.0, 2.0, 10.0, 10.0};

    EXPECT_CALL(mockPage, getDefaultCTM(ctm, 72.0, 72.0, 0, false, true)).Times(1);

    

    int xd = 0;

    int yd = 0;

    cvtUserToDev(&mockPage, 1.0, 1.0, &xd, &yd);

    

    EXPECT_EQ(xd, 12);

    EXPECT_EQ(yd, 12);

}



TEST_F(MockPageTest_1251, CtmTransformationWithOffset_1251) {

    MockPage mockPage(nullptr, 0, Object(), Ref(), std::make_unique<PageAttrs>());

    double ctm[6] = {1.0, 0.0, 0.0, 1.0, 5.0, 5.0};

    EXPECT_CALL(mockPage, getDefaultCTM(ctm, 72.0, 72.0, 0, false, true)).Times(1);

    

    int xd = 0;

    int yd = 0;

    cvtUserToDev(&mockPage, 1.0, 1.0, &xd, &yd);

    

    EXPECT_EQ(xd, 6);

    EXPECT_EQ(yd, 6);

}
