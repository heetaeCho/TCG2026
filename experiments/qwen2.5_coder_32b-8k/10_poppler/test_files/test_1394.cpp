#include <gtest/gtest.h>

#include "poppler/qt5/src/poppler-annotation.cc"

#include "./TestProjects/poppler/poppler/Annot.h"



namespace Poppler {

    static int fromPdfFlags(int flags);

}



class FromPdfFlagsTest_1394 : public ::testing::Test {};



TEST_F(FromPdfFlagsTest_1394, NormalOperation_AllFlagsSet_1394) {

    int pdfFlags = Annot::flagHidden | Annot::flagNoZoom | Annot::flagNoRotate |

                   Annot::flagPrint | Annot::flagReadOnly | Annot::flagLocked |

                   Annot::flagToggleNoView;

    EXPECT_EQ(Poppler::fromPdfFlags(pdfFlags),

              Annotation::Hidden | Annotation::FixedSize | Annotation::FixedRotation |

              (Annotation::DenyWrite | Annotation::DenyDelete) | Annotation::ToggleHidingOnMouse);

}



TEST_F(FromPdfFlagsTest_1394, NormalOperation_NoFlagsSet_1394) {

    int pdfFlags = 0;

    EXPECT_EQ(Poppler::fromPdfFlags(pdfFlags), 0);

}



TEST_F(FromPdfFlagsTest_1394, BoundaryCondition_FlagPrintClear_1394) {

    int pdfFlags = Annot::flagHidden | Annot::flagNoZoom | Annot::flagNoRotate |

                   Annot::flagReadOnly | Annot::flagLocked | Annot::flagToggleNoView;

    EXPECT_EQ(Poppler::fromPdfFlags(pdfFlags),

              Annotation::Hidden | Annotation::FixedSize | Annotation::FixedRotation |

              (Annotation::DenyWrite | Annotation::DenyDelete) | Annotation::DenyPrint | Annotation::ToggleHidingOnMouse);

}



TEST_F(FromPdfFlagsTest_1394, BoundaryCondition_FlagReadOnlyAndLocked_1394) {

    int pdfFlags = Annot::flagReadOnly | Annot::flagLocked;

    EXPECT_EQ(Poppler::fromPdfFlags(pdfFlags), Annotation::DenyWrite | (Annotation::DenyDelete * 2));

}



TEST_F(FromPdfFlagsTest_1394, BoundaryCondition_FlagHiddenAndToggleNoView_1394) {

    int pdfFlags = Annot::flagHidden | Annot::flagToggleNoView;

    EXPECT_EQ(Poppler::fromPdfFlags(pdfFlags), Annotation::Hidden | Annotation::ToggleHidingOnMouse);

}



TEST_F(FromPdfFlagsTest_1394, ExceptionalCase_FlagUnknownIgnored_1394) {

    int pdfFlags = Annot::flagUnknown; // flagUnknown should be ignored as it has no corresponding qtflags

    EXPECT_EQ(Poppler::fromPdfFlags(pdfFlags), 0);

}
