#include <gtest/gtest.h>

// Define the Annot flags as they appear in the dependency
namespace Annot {
    enum AnnotFlag {
        flagUnknown = 0,
        flagInvisible = 1,
        flagHidden = 2,
        flagPrint = 4,
        flagNoZoom = 8,
        flagNoRotate = 16,
        flagNoView = 32,
        flagReadOnly = 64,
        flagLocked = 128,
        flagToggleNoView = 256,
        flagLockedContents = 512
    };
}

// Define the Annotation flags as used by the Poppler Qt interface
namespace Poppler {
    class Annotation {
    public:
        enum Flag {
            Hidden = 0x0001,
            FixedSize = 0x0002,
            FixedRotation = 0x0004,
            DenyPrint = 0x0008,
            DenyWrite = 0x0010,
            DenyDelete = 0x0020,
            ToggleHidingOnMouse = 0x0040
        };
    };

    // Declare the function under test (it's static in the .cc, so we redefine it here for testing)
    static int fromPdfFlags(int flags)
    {
        int qtflags = 0;
        if (flags & Annot::flagHidden) {
            qtflags |= Annotation::Hidden;
        }
        if (flags & Annot::flagNoZoom) {
            qtflags |= Annotation::FixedSize;
        }
        if (flags & Annot::flagNoRotate) {
            qtflags |= Annotation::FixedRotation;
        }
        if (!(flags & Annot::flagPrint)) {
            qtflags |= Annotation::DenyPrint;
        }
        if (flags & Annot::flagReadOnly) {
            qtflags |= (Annotation::DenyWrite | Annotation::DenyDelete);
        }
        if (flags & Annot::flagLocked) {
            qtflags |= Annotation::DenyDelete;
        }
        if (flags & Annot::flagToggleNoView) {
            qtflags |= Annotation::ToggleHidingOnMouse;
        }
        return qtflags;
    }
}

using namespace Poppler;

class FromPdfFlagsTest_1394 : public ::testing::Test {
protected:
};

TEST_F(FromPdfFlagsTest_1394, ZeroFlagsReturnsDenyPrint_1394)
{
    // When no flags are set, flagPrint is not set, so DenyPrint should be set
    int result = fromPdfFlags(0);
    EXPECT_EQ(result, Annotation::DenyPrint);
}

TEST_F(FromPdfFlagsTest_1394, FlagHiddenMapsToHidden_1394)
{
    int result = fromPdfFlags(Annot::flagHidden);
    EXPECT_TRUE(result & Annotation::Hidden);
    // flagPrint not set, so DenyPrint should also be present
    EXPECT_TRUE(result & Annotation::DenyPrint);
}

TEST_F(FromPdfFlagsTest_1394, FlagNoZoomMapsToFixedSize_1394)
{
    int result = fromPdfFlags(Annot::flagNoZoom);
    EXPECT_TRUE(result & Annotation::FixedSize);
    EXPECT_TRUE(result & Annotation::DenyPrint);
}

TEST_F(FromPdfFlagsTest_1394, FlagNoRotateMapsToFixedRotation_1394)
{
    int result = fromPdfFlags(Annot::flagNoRotate);
    EXPECT_TRUE(result & Annotation::FixedRotation);
    EXPECT_TRUE(result & Annotation::DenyPrint);
}

TEST_F(FromPdfFlagsTest_1394, FlagPrintClearsDenyPrint_1394)
{
    // When flagPrint is set, DenyPrint should NOT be set
    int result = fromPdfFlags(Annot::flagPrint);
    EXPECT_FALSE(result & Annotation::DenyPrint);
}

TEST_F(FromPdfFlagsTest_1394, FlagReadOnlyMapsToDenyWriteAndDenyDelete_1394)
{
    int result = fromPdfFlags(Annot::flagReadOnly);
    EXPECT_TRUE(result & Annotation::DenyWrite);
    EXPECT_TRUE(result & Annotation::DenyDelete);
    EXPECT_TRUE(result & Annotation::DenyPrint);
}

TEST_F(FromPdfFlagsTest_1394, FlagLockedMapsToDenyDelete_1394)
{
    int result = fromPdfFlags(Annot::flagLocked);
    EXPECT_TRUE(result & Annotation::DenyDelete);
    // DenyWrite should NOT be set from flagLocked alone
    EXPECT_FALSE(result & Annotation::DenyWrite);
    EXPECT_TRUE(result & Annotation::DenyPrint);
}

TEST_F(FromPdfFlagsTest_1394, FlagToggleNoViewMapsToToggleHidingOnMouse_1394)
{
    int result = fromPdfFlags(Annot::flagToggleNoView);
    EXPECT_TRUE(result & Annotation::ToggleHidingOnMouse);
    EXPECT_TRUE(result & Annotation::DenyPrint);
}

TEST_F(FromPdfFlagsTest_1394, FlagPrintOnlyNoDenyPrint_1394)
{
    int result = fromPdfFlags(Annot::flagPrint);
    EXPECT_EQ(result, 0);
}

TEST_F(FromPdfFlagsTest_1394, AllFlagsCombined_1394)
{
    int allFlags = Annot::flagHidden | Annot::flagNoZoom | Annot::flagNoRotate |
                   Annot::flagPrint | Annot::flagReadOnly | Annot::flagLocked |
                   Annot::flagToggleNoView;
    int result = fromPdfFlags(allFlags);

    EXPECT_TRUE(result & Annotation::Hidden);
    EXPECT_TRUE(result & Annotation::FixedSize);
    EXPECT_TRUE(result & Annotation::FixedRotation);
    EXPECT_FALSE(result & Annotation::DenyPrint); // flagPrint is set
    EXPECT_TRUE(result & Annotation::DenyWrite);
    EXPECT_TRUE(result & Annotation::DenyDelete);
    EXPECT_TRUE(result & Annotation::ToggleHidingOnMouse);
}

TEST_F(FromPdfFlagsTest_1394, FlagInvisibleHasNoEffect_1394)
{
    // flagInvisible is not mapped, should only produce DenyPrint (since flagPrint not set)
    int result = fromPdfFlags(Annot::flagInvisible);
    EXPECT_EQ(result, Annotation::DenyPrint);
}

TEST_F(FromPdfFlagsTest_1394, FlagNoViewHasNoEffect_1394)
{
    // flagNoView is not mapped
    int result = fromPdfFlags(Annot::flagNoView);
    EXPECT_EQ(result, Annotation::DenyPrint);
}

TEST_F(FromPdfFlagsTest_1394, FlagLockedContentsHasNoEffect_1394)
{
    // flagLockedContents is not mapped
    int result = fromPdfFlags(Annot::flagLockedContents);
    EXPECT_EQ(result, Annotation::DenyPrint);
}

TEST_F(FromPdfFlagsTest_1394, ReadOnlyAndLockedCombined_1394)
{
    // Both set DenyDelete; ReadOnly also sets DenyWrite
    int result = fromPdfFlags(Annot::flagReadOnly | Annot::flagLocked);
    EXPECT_TRUE(result & Annotation::DenyWrite);
    EXPECT_TRUE(result & Annotation::DenyDelete);
    // Verify no extra bits beyond expected
    int expected = Annotation::DenyWrite | Annotation::DenyDelete | Annotation::DenyPrint;
    EXPECT_EQ(result, expected);
}

TEST_F(FromPdfFlagsTest_1394, HiddenWithPrint_1394)
{
    int result = fromPdfFlags(Annot::flagHidden | Annot::flagPrint);
    EXPECT_TRUE(result & Annotation::Hidden);
    EXPECT_FALSE(result & Annotation::DenyPrint);
    EXPECT_EQ(result, Annotation::Hidden);
}

TEST_F(FromPdfFlagsTest_1394, AllUnmappedFlagsOnly_1394)
{
    int unmapped = Annot::flagInvisible | Annot::flagNoView | Annot::flagLockedContents;
    int result = fromPdfFlags(unmapped);
    // Only DenyPrint should be set since flagPrint is not set
    EXPECT_EQ(result, Annotation::DenyPrint);
}

TEST_F(FromPdfFlagsTest_1394, NegativeInput_1394)
{
    // Negative value has all bits set including flagPrint
    int result = fromPdfFlags(-1);
    // flagPrint bit is set so DenyPrint should not appear
    EXPECT_FALSE(result & Annotation::DenyPrint);
    // All other mapped flags should be present
    EXPECT_TRUE(result & Annotation::Hidden);
    EXPECT_TRUE(result & Annotation::FixedSize);
    EXPECT_TRUE(result & Annotation::FixedRotation);
    EXPECT_TRUE(result & Annotation::DenyWrite);
    EXPECT_TRUE(result & Annotation::DenyDelete);
    EXPECT_TRUE(result & Annotation::ToggleHidingOnMouse);
}
