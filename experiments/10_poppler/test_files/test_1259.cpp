#include <gtest/gtest.h>

#include <QPainterPath>

#include "TestProjects/poppler/poppler/GfxState.h"



// Mock GfxSubpath for testing purposes

class MockGfxSubpath : public GfxSubpath {

public:

    MOCK_CONST_METHOD0(getNumPoints, int());

    MOCK_CONST_METHOD1(getX, double(int));

    MOCK_CONST_METHOD1(getY, double(int));

    MOCK_CONST_METHOD1(getCurve, bool(int));

    MOCK_CONST_METHOD0(isClosed, bool());

};



// Mock GfxPath for testing purposes

class MockGfxPath : public GfxPath {

public:

    MOCK_CONST_METHOD0(getNumSubpaths, int());

    MOCK_CONST_METHOD1(getSubpath, GfxSubpath*(int));

};



TEST_F(ConvertPathTest_1259, EmptyPath_ReturnsEmptyQPainterPath_1259) {

    MockGfxPath mockPath;

    EXPECT_CALL(mockPath, getNumSubpaths()).WillOnce(::testing::Return(0));



    QPainterPath qPath = convertPath(&mockPath, Qt::OddEvenFill);

    EXPECT_TRUE(qPath.isEmpty());

}



TEST_F(ConvertPathTest_1259, SingleLine_ReturnsQPainterPathWithOneSegment_1259) {

    MockGfxPath mockPath;

    MockGfxSubpath mockSubpath;



    EXPECT_CALL(mockPath, getNumSubpaths()).WillOnce(::testing::Return(1));

    EXPECT_CALL(mockPath, getSubpath(0)).WillOnce(::testing::Return(&mockSubpath));



    EXPECT_CALL(mockSubpath, getNumPoints()).WillOnce(::testing::Return(2));

    EXPECT_CALL(mockSubpath, getX(0)).WillOnce(::testing::Return(0.0));

    EXPECT_CALL(mockSubpath, getY(0)).WillOnce(::testing::Return(0.0));

    EXPECT_CALL(mockSubpath, getX(1)).WillOnce(::testing::Return(1.0));

    EXPECT_CALL(mockSubpath, getY(1)).WillOnce(::testing::Return(1.0));



    QPainterPath qPath = convertPath(&mockPath, Qt::OddEvenFill);

    ASSERT_EQ(qPath.elementCount(), 2);

    EXPECT_EQ(qPath.elementAt(0).type, QPainterPath::MoveToElement);

    EXPECT_EQ(qPath.elementAt(0).x, 0.0);

    EXPECT_EQ(qPath.elementAt(0).y, 0.0);

    EXPECT_EQ(qPath.elementAt(1).type, QPainterPath::LineToElement);

    EXPECT_EQ(qPath.elementAt(1).x, 1.0);

    EXPECT_EQ(qPath.elementAt(1).y, 1.0);

}



TEST_F(ConvertPathTest_1259, SingleCurve_ReturnsQPainterPathWithOneCubicSegment_1259) {

    MockGfxPath mockPath;

    MockGfxSubpath mockSubpath;



    EXPECT_CALL(mockPath, getNumSubpaths()).WillOnce(::testing::Return(1));

    EXPECT_CALL(mockPath, getSubpath(0)).WillOnce(::testing::Return(&mockSubpath));



    EXPECT_CALL(mockSubpath, getNumPoints()).WillOnce(::testing::Return(4));

    EXPECT_CALL(mockSubpath, getX(0)).WillOnce(::testing::Return(0.0));

    EXPECT_CALL(mockSubpath, getY(0)).WillOnce(::testing::Return(0.0));

    EXPECT_CALL(mockSubpath, getX(1)).WillOnce(::testing::Return(0.5));

    EXPECT_CALL(mockSubpath, getY(1)).WillOnce(::testing::Return(0.5));

    EXPECT_CALL(mockSubpath, getX(2)).WillOnce(::testing::Return(1.0));

    EXPECT_CALL(mockSubpath, getY(2)).WillOnce(::testing::Return(1.0));

    EXPECT_CALL(mockSubpath, getX(3)).WillOnce(::testing::Return(1.5));

    EXPECT_CALL(mockSubpath, getY(3)).WillOnce(::testing::Return(1.5));



    EXPECT_CALL(mockSubpath, getCurve(1)).WillOnce(::testing::Return(true));



    QPainterPath qPath = convertPath(&mockPath, Qt::OddEvenFill);

    ASSERT_EQ(qPath.elementCount(), 2);

    EXPECT_EQ(qPath.elementAt(0).type, QPainterPath::MoveToElement);

    EXPECT_EQ(qPath.elementAt(0).x, 0.0);

    EXPECT_EQ(qPath.elementAt(0).y, 0.0);

    EXPECT_EQ(qPath.elementAt(1).type, QPainterPath::CurveToElement);

    EXPECT_EQ(qPath.elementAt(1).x, 1.5);

    EXPECT_EQ(qPath.elementAt(1).y, 1.5);

}



TEST_F(ConvertPathTest_1259, ClosedSubpath_ReturnsClosedQPainterPath_1259) {

    MockGfxPath mockPath;

    MockGfxSubpath mockSubpath;



    EXPECT_CALL(mockPath, getNumSubpaths()).WillOnce(::testing::Return(1));

    EXPECT_CALL(mockPath, getSubpath(0)).WillOnce(::testing::Return(&mockSubpath));



    EXPECT_CALL(mockSubpath, getNumPoints()).WillOnce(::testing::Return(2));

    EXPECT_CALL(mockSubpath, getX(0)).WillOnce(::testing::Return(0.0));

    EXPECT_CALL(mockSubpath, getY(0)).WillOnce(::testing::Return(0.0));

    EXPECT_CALL(mockSubpath, getX(1)).WillOnce(::testing::Return(1.0));

    EXPECT_CALL(mockSubpath, getY(1)).WillOnce(::testing::Return(1.0));



    EXPECT_CALL(mockSubpath, isClosed()).WillOnce(::testing::Return(true));



    QPainterPath qPath = convertPath(&mockPath, Qt::OddEvenFill);

    ASSERT_EQ(qPath.elementCount(), 3);

    EXPECT_EQ(qPath.elementAt(0).type, QPainterPath::MoveToElement);

    EXPECT_EQ(qPath.elementAt(0).x, 0.0);

    EXPECT_EQ(qPath.elementAt(0).y, 0.0);

    EXPECT_EQ(qPath.elementAt(1).type, QPainterPath::LineToElement);

    EXPECT_EQ(qPath.elementAt(1).x, 1.0);

    EXPECT_EQ(qPath.elementAt(1).y, 1.0);

    EXPECT_EQ(qPath.elementAt(2).type, QPainterPath::CloseSubpathElement);

}



TEST_F(ConvertPathTest_1259, MultipleSubpaths_ReturnsQPainterPathWithMultipleSegments_1259) {

    MockGfxPath mockPath;

    MockGfxSubpath mockSubpath1, mockSubpath2;



    EXPECT_CALL(mockPath, getNumSubpaths()).WillOnce(::testing::Return(2));

    EXPECT_CALL(mockPath, getSubpath(0)).WillOnce(::testing::Return(&mockSubpath1));

    EXPECT_CALL(mockPath, getSubpath(1)).WillOnce(::testing::Return(&mockSubpath2));



    // Subpath 1

    EXPECT_CALL(mockSubpath1, getNumPoints()).WillOnce(::testing::Return(2));

    EXPECT_CALL(mockSubpath1, getX(0)).WillOnce(::testing::Return(0.0));

    EXPECT_CALL(mockSubpath1, getY(0)).WillOnce(::testing::Return(0.0));

    EXPECT_CALL(mockSubpath1, getX(1)).WillOnce(::testing::Return(1.0));

    EXPECT_CALL(mockSubpath1, getY(1)).WillOnce(::testing::Return(1.0));



    // Subpath 2

    EXPECT_CALL(mockSubpath2, getNumPoints()).WillOnce(::testing::Return(2));

    EXPECT_CALL(mockSubpath2, getX(0)).WillOnce(::testing::Return(2.0));

    EXPECT_CALL(mockSubpath2, getY(0)).WillOnce(::testing::Return(2.0));

    EXPECT_CALL(mockSubpath2, getX(1)).WillOnce(::testing::Return(3.0));

    EXPECT_CALL(mockSubpath2, getY(1)).WillOnce(::testing::Return(3.0));



    QPainterPath qPath = convertPath(&mockPath, Qt::OddEvenFill);

    ASSERT_EQ(qPath.elementCount(), 4);

    EXPECT_EQ(qPath.elementAt(0).type, QPainterPath::MoveToElement);

    EXPECT_EQ(qPath.elementAt(0).x, 0.0);

    EXPECT_EQ(qPath.elementAt(0).y, 0.0);

    EXPECT_EQ(qPath.elementAt(1).type, QPainterPath::LineToElement);

    EXPECT_EQ(qPath.elementAt(1).x, 1.0);

    EXPECT_EQ(qPath.elementAt(1).y, 1.0);

    EXPECT_EQ(qPath.elementAt(2).type, QPainterPath::MoveToElement);

    EXPECT_EQ(qPath.elementAt(2).x, 2.0);

    EXPECT_EQ(qPath.elementAt(2).y, 2.0);

    EXPECT_EQ(qPath.elementAt(3).type, QPainterPath::LineToElement);

    EXPECT_EQ(qPath.elementAt(3).x, 3.0);

    EXPECT_EQ(qPath.elementAt(3).y, 3.0);

}
