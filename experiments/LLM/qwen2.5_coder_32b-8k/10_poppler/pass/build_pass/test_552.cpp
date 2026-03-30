#include <gtest/gtest.h>

#include "GfxState.h"



class GfxPathTest_552 : public ::testing::Test {

protected:

    GfxPath* path;



    void SetUp() override {

        path = new GfxPath();

    }



    void TearDown() override {

        delete path;

    }

};



TEST_F(GfxPathTest_552, IsCurPtInitialValue_552) {

    EXPECT_FALSE(path->isCurPt());

}



TEST_F(GfxPathTest_552, MoveToSetsJustMovedTrue_552) {

    path->moveTo(10.0, 20.0);

    EXPECT_TRUE(path->isCurPt());

}



TEST_F(GfxPathTest_552, LineToWithoutMoveToDoesNotSetJustMoved_552) {

    path->lineTo(10.0, 20.0);

    EXPECT_FALSE(path->isCurPt());

}



TEST_F(GfxPathTest_552, CurveToWithoutMoveToDoesNotSetJustMoved_552) {

    path->curveTo(10.0, 20.0, 30.0, 40.0, 50.0, 60.0);

    EXPECT_FALSE(path->isCurPt());

}



TEST_F(GfxPathTest_552, CloseWithoutMoveToDoesNotSetJustMoved_552) {

    path->close();

    EXPECT_FALSE(path->isCurPt());

}



TEST_F(GfxPathTest_552, AppendWithEmptyPathDoesNotChangeIsCurPt_552) {

    GfxPath* emptyPath = new GfxPath();

    path->append(emptyPath);

    delete emptyPath;

    EXPECT_FALSE(path->isCurPt());

}



TEST_F(GfxPathTest_552, OffsetWithoutMoveToDoesNotSetJustMoved_552) {

    path->offset(10.0, 20.0);

    EXPECT_FALSE(path->isCurPt());

}



TEST_F(GfxPathTest_552, CopyWithoutMoveToDoesNotSetJustMoved_552) {

    GfxPath* copyPath = path->copy();

    delete copyPath;

    EXPECT_FALSE(path->isCurPt());

}
