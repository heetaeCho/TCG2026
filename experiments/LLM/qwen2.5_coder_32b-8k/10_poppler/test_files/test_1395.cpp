#include <gtest/gtest.h>



namespace Poppler {

    static int toPdfFlags(int qtflags);

}



using namespace Annot;



class ToPdfFlagsTest_1395 : public ::testing::Test {};



TEST_F(ToPdfFlagsTest_1395, NormalOperation_AllFlagsSet_1395) {

    int qtflags = Annotation::Hidden | Annotation::FixedSize | Annotation::FixedRotation |

                  Annotation::DenyPrint | Annotation::DenyWrite | Annotation::DenyDelete |

                  Annotation::ToggleHidingOnMouse;

    EXPECT_EQ(Poppler::toPdfFlags(qtflags), flagHidden | flagNoZoom | flagNoRotate | flagReadOnly | flagLocked | flagToggleNoView);

}



TEST_F(ToPdfFlagsTest_1395, NormalOperation_NoFlagsSet_1395) {

    int qtflags = 0;

    EXPECT_EQ(Poppler::toPdfFlags(qtflags), flagPrint);

}



TEST_F(ToPdfFlagsTest_1395, BoundaryCondition_SingleFlagHidden_1395) {

    int qtflags = Annotation::Hidden;

    EXPECT_EQ(Poppler::toPdfFlags(qtflags), flagHidden | flagPrint);

}



TEST_F(ToPdfFlagsTest_1395, BoundaryCondition_SingleFlagFixedSize_1395) {

    int qtflags = Annotation::FixedSize;

    EXPECT_EQ(Poppler::toPdfFlags(qtflags), flagNoZoom | flagPrint);

}



TEST_F(ToPdfFlagsTest_1395, BoundaryCondition_SingleFlagFixedRotation_1395) {

    int qtflags = Annotation::FixedRotation;

    EXPECT_EQ(Poppler::toPdfFlags(qtflags), flagNoRotate | flagPrint);

}



TEST_F(ToPdfFlagsTest_1395, BoundaryCondition_SingleFlagDenyPrint_1395) {

    int qtflags = Annotation::DenyPrint;

    EXPECT_EQ(Poppler::toPdfFlags(qtflags), 0); // No print flag set

}



TEST_F(ToPdfFlagsTest_1395, BoundaryCondition_SingleFlagDenyWrite_1395) {

    int qtflags = Annotation::DenyWrite;

    EXPECT_EQ(Poppler::toPdfFlags(qtflags), flagReadOnly | flagPrint);

}



TEST_F(ToPdfFlagsTest_1395, BoundaryCondition_SingleFlagDenyDelete_1395) {

    int qtflags = Annotation::DenyDelete;

    EXPECT_EQ(Poppler::toPdfFlags(qtflags), flagLocked | flagPrint);

}



TEST_F(ToPdfFlagsTest_1395, BoundaryCondition_SingleFlagToggleHidingOnMouse_1395) {

    int qtflags = Annotation::ToggleHidingOnMouse;

    EXPECT_EQ(Poppler::toPdfFlags(qtflags), flagToggleNoView | flagPrint);

}
