#include <gtest/gtest.h>

// Mock the dependencies based on the provided interface

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

// Function under test - declared here to match the implementation
static int toPdfFlags(int qtflags)
{
    int flags = 0;
    if (qtflags & Annotation::Hidden) {
        flags |= Annot::flagHidden;
    }
    if (qtflags & Annotation::FixedSize) {
        flags |= Annot::flagNoZoom;
    }
    if (qtflags & Annotation::FixedRotation) {
        flags |= Annot::flagNoRotate;
    }
    if (!(qtflags & Annotation::DenyPrint)) {
        flags |= Annot::flagPrint;
    }
    if (qtflags & Annotation::DenyWrite) {
        flags |= Annot::flagReadOnly;
    }
    if (qtflags & Annotation::DenyDelete) {
        flags |= Annot::flagLocked;
    }
    if (qtflags & Annotation::ToggleHidingOnMouse) {
        flags |= Annot::flagToggleNoView;
    }
    return flags;
}

} // namespace Poppler

class ToPdfFlagsTest_1395 : public ::testing::Test {
protected:
    int callToPdfFlags(int qtflags) {
        return Poppler::toPdfFlags(qtflags);
    }
};

// Test: When no flags are set, only Print flag should be set (DenyPrint is not set)
TEST_F(ToPdfFlagsTest_1395, NoFlagsSetDefaultsPrintEnabled_1395)
{
    int result = callToPdfFlags(0);
    EXPECT_EQ(result, Annot::flagPrint);
}

// Test: Hidden flag mapping
TEST_F(ToPdfFlagsTest_1395, HiddenFlagMapsToFlagHidden_1395)
{
    int result = callToPdfFlags(Poppler::Annotation::Hidden);
    EXPECT_TRUE(result & Annot::flagHidden);
    // Print should still be set since DenyPrint is not set
    EXPECT_TRUE(result & Annot::flagPrint);
}

// Test: FixedSize flag mapping
TEST_F(ToPdfFlagsTest_1395, FixedSizeFlagMapsToFlagNoZoom_1395)
{
    int result = callToPdfFlags(Poppler::Annotation::FixedSize);
    EXPECT_TRUE(result & Annot::flagNoZoom);
    EXPECT_TRUE(result & Annot::flagPrint);
}

// Test: FixedRotation flag mapping
TEST_F(ToPdfFlagsTest_1395, FixedRotationFlagMapsToFlagNoRotate_1395)
{
    int result = callToPdfFlags(Poppler::Annotation::FixedRotation);
    EXPECT_TRUE(result & Annot::flagNoRotate);
    EXPECT_TRUE(result & Annot::flagPrint);
}

// Test: DenyPrint flag disables Print
TEST_F(ToPdfFlagsTest_1395, DenyPrintFlagDisablesFlagPrint_1395)
{
    int result = callToPdfFlags(Poppler::Annotation::DenyPrint);
    EXPECT_FALSE(result & Annot::flagPrint);
}

// Test: DenyWrite flag mapping
TEST_F(ToPdfFlagsTest_1395, DenyWriteFlagMapsToFlagReadOnly_1395)
{
    int result = callToPdfFlags(Poppler::Annotation::DenyWrite);
    EXPECT_TRUE(result & Annot::flagReadOnly);
    EXPECT_TRUE(result & Annot::flagPrint);
}

// Test: DenyDelete flag mapping
TEST_F(ToPdfFlagsTest_1395, DenyDeleteFlagMapsToFlagLocked_1395)
{
    int result = callToPdfFlags(Poppler::Annotation::DenyDelete);
    EXPECT_TRUE(result & Annot::flagLocked);
    EXPECT_TRUE(result & Annot::flagPrint);
}

// Test: ToggleHidingOnMouse flag mapping
TEST_F(ToPdfFlagsTest_1395, ToggleHidingOnMouseFlagMapsToFlagToggleNoView_1395)
{
    int result = callToPdfFlags(Poppler::Annotation::ToggleHidingOnMouse);
    EXPECT_TRUE(result & Annot::flagToggleNoView);
    EXPECT_TRUE(result & Annot::flagPrint);
}

// Test: All flags set at once
TEST_F(ToPdfFlagsTest_1395, AllFlagsSet_1395)
{
    int qtflags = Poppler::Annotation::Hidden
                | Poppler::Annotation::FixedSize
                | Poppler::Annotation::FixedRotation
                | Poppler::Annotation::DenyPrint
                | Poppler::Annotation::DenyWrite
                | Poppler::Annotation::DenyDelete
                | Poppler::Annotation::ToggleHidingOnMouse;

    int result = callToPdfFlags(qtflags);

    EXPECT_TRUE(result & Annot::flagHidden);
    EXPECT_TRUE(result & Annot::flagNoZoom);
    EXPECT_TRUE(result & Annot::flagNoRotate);
    EXPECT_FALSE(result & Annot::flagPrint);  // DenyPrint is set
    EXPECT_TRUE(result & Annot::flagReadOnly);
    EXPECT_TRUE(result & Annot::flagLocked);
    EXPECT_TRUE(result & Annot::flagToggleNoView);
}

// Test: All flags except DenyPrint - print should be enabled
TEST_F(ToPdfFlagsTest_1395, AllFlagsExceptDenyPrint_1395)
{
    int qtflags = Poppler::Annotation::Hidden
                | Poppler::Annotation::FixedSize
                | Poppler::Annotation::FixedRotation
                | Poppler::Annotation::DenyWrite
                | Poppler::Annotation::DenyDelete
                | Poppler::Annotation::ToggleHidingOnMouse;

    int result = callToPdfFlags(qtflags);

    EXPECT_TRUE(result & Annot::flagHidden);
    EXPECT_TRUE(result & Annot::flagNoZoom);
    EXPECT_TRUE(result & Annot::flagNoRotate);
    EXPECT_TRUE(result & Annot::flagPrint);  // DenyPrint is NOT set
    EXPECT_TRUE(result & Annot::flagReadOnly);
    EXPECT_TRUE(result & Annot::flagLocked);
    EXPECT_TRUE(result & Annot::flagToggleNoView);
}

// Test: Only DenyPrint set results in zero flags (no print, nothing else)
TEST_F(ToPdfFlagsTest_1395, OnlyDenyPrintResultsInZero_1395)
{
    int result = callToPdfFlags(Poppler::Annotation::DenyPrint);
    EXPECT_EQ(result, 0);
}

// Test: Combination of Hidden and DenyPrint
TEST_F(ToPdfFlagsTest_1395, HiddenAndDenyPrint_1395)
{
    int qtflags = Poppler::Annotation::Hidden | Poppler::Annotation::DenyPrint;
    int result = callToPdfFlags(qtflags);

    EXPECT_TRUE(result & Annot::flagHidden);
    EXPECT_FALSE(result & Annot::flagPrint);
    // Only Hidden and no Print
    EXPECT_EQ(result, Annot::flagHidden);
}

// Test: Combination of DenyWrite and DenyDelete
TEST_F(ToPdfFlagsTest_1395, DenyWriteAndDenyDelete_1395)
{
    int qtflags = Poppler::Annotation::DenyWrite | Poppler::Annotation::DenyDelete;
    int result = callToPdfFlags(qtflags);

    EXPECT_TRUE(result & Annot::flagReadOnly);
    EXPECT_TRUE(result & Annot::flagLocked);
    EXPECT_TRUE(result & Annot::flagPrint);
    EXPECT_EQ(result, Annot::flagPrint | Annot::flagReadOnly | Annot::flagLocked);
}

// Test: FixedSize and FixedRotation together
TEST_F(ToPdfFlagsTest_1395, FixedSizeAndFixedRotation_1395)
{
    int qtflags = Poppler::Annotation::FixedSize | Poppler::Annotation::FixedRotation;
    int result = callToPdfFlags(qtflags);

    EXPECT_TRUE(result & Annot::flagNoZoom);
    EXPECT_TRUE(result & Annot::flagNoRotate);
    EXPECT_TRUE(result & Annot::flagPrint);
    EXPECT_EQ(result, Annot::flagNoZoom | Annot::flagNoRotate | Annot::flagPrint);
}

// Test: Verify no unrelated flags are set for a single input flag
TEST_F(ToPdfFlagsTest_1395, HiddenDoesNotSetUnrelatedFlags_1395)
{
    int result = callToPdfFlags(Poppler::Annotation::Hidden);

    // Should only have flagHidden and flagPrint
    EXPECT_EQ(result, Annot::flagHidden | Annot::flagPrint);

    // Verify unrelated flags are NOT set
    EXPECT_FALSE(result & Annot::flagNoZoom);
    EXPECT_FALSE(result & Annot::flagNoRotate);
    EXPECT_FALSE(result & Annot::flagReadOnly);
    EXPECT_FALSE(result & Annot::flagLocked);
    EXPECT_FALSE(result & Annot::flagToggleNoView);
    EXPECT_FALSE(result & Annot::flagInvisible);
    EXPECT_FALSE(result & Annot::flagNoView);
    EXPECT_FALSE(result & Annot::flagLockedContents);
}

// Test: Exact value for all flags except DenyPrint
TEST_F(ToPdfFlagsTest_1395, ExactValueAllFlagsExceptDenyPrint_1395)
{
    int qtflags = Poppler::Annotation::Hidden
                | Poppler::Annotation::FixedSize
                | Poppler::Annotation::FixedRotation
                | Poppler::Annotation::DenyWrite
                | Poppler::Annotation::DenyDelete
                | Poppler::Annotation::ToggleHidingOnMouse;

    int result = callToPdfFlags(qtflags);

    int expected = Annot::flagHidden | Annot::flagNoZoom | Annot::flagNoRotate
                 | Annot::flagPrint | Annot::flagReadOnly | Annot::flagLocked
                 | Annot::flagToggleNoView;

    EXPECT_EQ(result, expected);
}

// Test: Exact value for all flags including DenyPrint
TEST_F(ToPdfFlagsTest_1395, ExactValueAllFlags_1395)
{
    int qtflags = Poppler::Annotation::Hidden
                | Poppler::Annotation::FixedSize
                | Poppler::Annotation::FixedRotation
                | Poppler::Annotation::DenyPrint
                | Poppler::Annotation::DenyWrite
                | Poppler::Annotation::DenyDelete
                | Poppler::Annotation::ToggleHidingOnMouse;

    int result = callToPdfFlags(qtflags);

    int expected = Annot::flagHidden | Annot::flagNoZoom | Annot::flagNoRotate
                 | Annot::flagReadOnly | Annot::flagLocked
                 | Annot::flagToggleNoView;

    EXPECT_EQ(result, expected);
}

// Test: Unknown/extra bits in input should be ignored
TEST_F(ToPdfFlagsTest_1395, UnknownBitsIgnored_1395)
{
    // Set bits beyond defined flags
    int qtflags = 0x0080 | 0x0100;  // bits not defined in Annotation::Flag
    int result = callToPdfFlags(qtflags);

    // Only print should be set since no known flags are set (except possibly unrelated bits)
    // DenyPrint is not set so flagPrint should be present
    EXPECT_TRUE(result & Annot::flagPrint);
}

// Test: Inverse of DenyPrint behavior - default is print enabled
TEST_F(ToPdfFlagsTest_1395, PrintIsDefaultBehavior_1395)
{
    // Various combinations without DenyPrint should all have flagPrint
    EXPECT_TRUE(callToPdfFlags(0) & Annot::flagPrint);
    EXPECT_TRUE(callToPdfFlags(Poppler::Annotation::Hidden) & Annot::flagPrint);
    EXPECT_TRUE(callToPdfFlags(Poppler::Annotation::FixedSize) & Annot::flagPrint);
    EXPECT_TRUE(callToPdfFlags(Poppler::Annotation::DenyWrite) & Annot::flagPrint);

    // With DenyPrint, flagPrint should NOT be present
    EXPECT_FALSE(callToPdfFlags(Poppler::Annotation::DenyPrint) & Annot::flagPrint);
}
