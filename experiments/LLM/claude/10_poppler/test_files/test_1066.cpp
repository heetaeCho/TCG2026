#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "OutputDev.h"
#include "GfxState.h"
#include "Object.h"

// Concrete OutputDev subclass for testing (since OutputDev has pure virtual-like methods)
class TestOutputDev : public OutputDev
{
public:
    TestOutputDev() : OutputDev() { }
    ~TestOutputDev() override = default;

    // Required overrides for abstract/pure virtual methods
    bool upsideDown() override { return false; }
    bool useDrawChar() override { return false; }
    bool interpretType3Chars() override { return false; }
};

class OutputDevTest_1066 : public ::testing::Test
{
protected:
    void SetUp() override
    {
        dev = std::make_unique<TestOutputDev>();
    }

    void TearDown() override
    {
        dev.reset();
    }

    std::unique_ptr<TestOutputDev> dev;

    // Helper to create a basic GfxState
    std::unique_ptr<GfxState> createGfxState()
    {
        PDFRectangle pageBox;
        pageBox.x1 = 0;
        pageBox.y1 = 0;
        pageBox.x2 = 612;
        pageBox.y2 = 792;
        return std::make_unique<GfxState>(72.0, 72.0, &pageBox, 0, false);
    }
};

// Test that OutputDev can be constructed and destroyed without issues
TEST_F(OutputDevTest_1066, DefaultConstruction_1066)
{
    EXPECT_NE(dev.get(), nullptr);
}

// Test initGfxState with a valid GfxState and no profiles set
TEST_F(OutputDevTest_1066, InitGfxStateNoProfiles_1066)
{
    auto state = createGfxState();
    ASSERT_NE(state.get(), nullptr);

    // Should not crash even when no profiles are set
    EXPECT_NO_THROW(dev->initGfxState(state.get()));
}

// Test that display profile getter/setter work
TEST_F(OutputDevTest_1066, SetAndGetDisplayProfile_1066)
{
    GfxLCMSProfilePtr profile = dev->getDisplayProfile();
    // Initially should be null/empty
    EXPECT_FALSE(profile);

    // Set and get - set with empty profile
    GfxLCMSProfilePtr emptyProfile;
    dev->setDisplayProfile(emptyProfile);
    profile = dev->getDisplayProfile();
    EXPECT_FALSE(profile);
}

// Test that default gray profile getter/setter work
TEST_F(OutputDevTest_1066, SetAndGetDefaultGrayProfile_1066)
{
    GfxLCMSProfilePtr profile = dev->getDefaultGrayProfile();
    EXPECT_FALSE(profile);

    GfxLCMSProfilePtr emptyProfile;
    dev->setDefaultGrayProfile(emptyProfile);
    profile = dev->getDefaultGrayProfile();
    EXPECT_FALSE(profile);
}

// Test that default RGB profile getter/setter work
TEST_F(OutputDevTest_1066, SetAndGetDefaultRGBProfile_1066)
{
    GfxLCMSProfilePtr profile = dev->getDefaultRGBProfile();
    EXPECT_FALSE(profile);

    GfxLCMSProfilePtr emptyProfile;
    dev->setDefaultRGBProfile(emptyProfile);
    profile = dev->getDefaultRGBProfile();
    EXPECT_FALSE(profile);
}

// Test that default CMYK profile getter/setter work
TEST_F(OutputDevTest_1066, SetAndGetDefaultCMYKProfile_1066)
{
    GfxLCMSProfilePtr profile = dev->getDefaultCMYKProfile();
    EXPECT_FALSE(profile);

    GfxLCMSProfilePtr emptyProfile;
    dev->setDefaultCMYKProfile(emptyProfile);
    profile = dev->getDefaultCMYKProfile();
    EXPECT_FALSE(profile);
}

// Test default return values for virtual boolean methods
TEST_F(OutputDevTest_1066, DefaultUseTilingPatternFill_1066)
{
    EXPECT_FALSE(dev->useTilingPatternFill());
}

TEST_F(OutputDevTest_1066, DefaultUseFillColorStop_1066)
{
    EXPECT_FALSE(dev->useFillColorStop());
}

TEST_F(OutputDevTest_1066, DefaultUseDrawForm_1066)
{
    EXPECT_FALSE(dev->useDrawForm());
}

TEST_F(OutputDevTest_1066, DefaultNeedNonText_1066)
{
    EXPECT_TRUE(dev->needNonText());
}

TEST_F(OutputDevTest_1066, DefaultNeedCharCount_1066)
{
    EXPECT_FALSE(dev->needCharCount());
}

TEST_F(OutputDevTest_1066, DefaultNeedClipToCropBox_1066)
{
    EXPECT_FALSE(dev->needClipToCropBox());
}

TEST_F(OutputDevTest_1066, DefaultGetVectorAntialias_1066)
{
    EXPECT_FALSE(dev->getVectorAntialias());
}

// Test profiling start/end
TEST_F(OutputDevTest_1066, ProfileStartEnd_1066)
{
    dev->startProfile();
    auto profileData = dev->endProfile();
    EXPECT_NE(profileData.get(), nullptr);
    // After starting a profile, ending should return a valid map (possibly empty)
    EXPECT_TRUE(profileData->empty());
}

// Test getProfileHash returns nullptr when profiling not started
TEST_F(OutputDevTest_1066, GetProfileHashBeforeStart_1066)
{
    auto *hash = dev->getProfileHash();
    EXPECT_EQ(hash, nullptr);
}

// Test getProfileHash returns non-null after profiling started
TEST_F(OutputDevTest_1066, GetProfileHashAfterStart_1066)
{
    dev->startProfile();
    auto *hash = dev->getProfileHash();
    EXPECT_NE(hash, nullptr);
}

// Test getIccColorSpaceCache returns a valid pointer
TEST_F(OutputDevTest_1066, GetIccColorSpaceCache_1066)
{
    auto *cache = dev->getIccColorSpaceCache();
    EXPECT_NE(cache, nullptr);
}

// Test setDefaultCTM
TEST_F(OutputDevTest_1066, SetDefaultCTM_1066)
{
    std::array<double, 6> ctm = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
    EXPECT_NO_THROW(dev->setDefaultCTM(ctm));
}

// Test cvtUserToDev with identity CTM
TEST_F(OutputDevTest_1066, CvtUserToDevIdentity_1066)
{
    std::array<double, 6> ctm = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
    dev->setDefaultCTM(ctm);

    int dx = 0, dy = 0;
    dev->cvtUserToDev(100.0, 200.0, &dx, &dy);
    EXPECT_EQ(dx, 100);
    EXPECT_EQ(dy, 200);
}

// Test cvtUserToDev with scaled CTM
TEST_F(OutputDevTest_1066, CvtUserToDevScaled_1066)
{
    std::array<double, 6> ctm = {2.0, 0.0, 0.0, 2.0, 0.0, 0.0};
    dev->setDefaultCTM(ctm);

    int dx = 0, dy = 0;
    dev->cvtUserToDev(50.0, 100.0, &dx, &dy);
    EXPECT_EQ(dx, 100);
    EXPECT_EQ(dy, 200);
}

// Test cvtUserToDev with translation CTM
TEST_F(OutputDevTest_1066, CvtUserToDevTranslated_1066)
{
    std::array<double, 6> ctm = {1.0, 0.0, 0.0, 1.0, 10.0, 20.0};
    dev->setDefaultCTM(ctm);

    int dx = 0, dy = 0;
    dev->cvtUserToDev(5.0, 5.0, &dx, &dy);
    EXPECT_EQ(dx, 15);
    EXPECT_EQ(dy, 25);
}

// Test that various no-op virtual methods don't crash
TEST_F(OutputDevTest_1066, NoOpVirtualMethods_1066)
{
    auto state = createGfxState();

    EXPECT_NO_THROW(dev->saveState(state.get()));
    EXPECT_NO_THROW(dev->restoreState(state.get()));
    EXPECT_NO_THROW(dev->updateAll(state.get()));
    EXPECT_NO_THROW(dev->updateCTM(state.get(), 1.0, 0.0, 0.0, 1.0, 0.0, 0.0));
    EXPECT_NO_THROW(dev->updateLineDash(state.get()));
    EXPECT_NO_THROW(dev->updateFlatness(state.get()));
    EXPECT_NO_THROW(dev->updateLineJoin(state.get()));
    EXPECT_NO_THROW(dev->updateLineCap(state.get()));
    EXPECT_NO_THROW(dev->updateMiterLimit(state.get()));
    EXPECT_NO_THROW(dev->updateLineWidth(state.get()));
    EXPECT_NO_THROW(dev->updateFillColor(state.get()));
    EXPECT_NO_THROW(dev->updateStrokeColor(state.get()));
    EXPECT_NO_THROW(dev->updateBlendMode(state.get()));
    EXPECT_NO_THROW(dev->updateFillOpacity(state.get()));
    EXPECT_NO_THROW(dev->updateStrokeOpacity(state.get()));
    EXPECT_NO_THROW(dev->updateFont(state.get()));
    EXPECT_NO_THROW(dev->stroke(state.get()));
    EXPECT_NO_THROW(dev->fill(state.get()));
    EXPECT_NO_THROW(dev->eoFill(state.get()));
    EXPECT_NO_THROW(dev->clip(state.get()));
    EXPECT_NO_THROW(dev->eoClip(state.get()));
    EXPECT_NO_THROW(dev->dump());
}

// Test endPage doesn't crash
TEST_F(OutputDevTest_1066, EndPage_1066)
{
    EXPECT_NO_THROW(dev->endPage());
}

// Test setVectorAntialias
TEST_F(OutputDevTest_1066, SetVectorAntialias_1066)
{
    EXPECT_NO_THROW(dev->setVectorAntialias(true));
    EXPECT_NO_THROW(dev->setVectorAntialias(false));
}

// Test checkTransparencyGroup default
TEST_F(OutputDevTest_1066, CheckTransparencyGroupDefault_1066)
{
    auto state = createGfxState();
    EXPECT_TRUE(dev->checkTransparencyGroup(state.get(), false));
}

// Test beginString/endString no-ops
TEST_F(OutputDevTest_1066, BeginEndStringOp_1066)
{
    auto state = createGfxState();
    EXPECT_NO_THROW(dev->beginStringOp(state.get()));
    EXPECT_NO_THROW(dev->endStringOp(state.get()));
}

// Test useShadedFills default
TEST_F(OutputDevTest_1066, UseShadedFillsDefault_1066)
{
    EXPECT_FALSE(dev->useShadedFills(1));
    EXPECT_FALSE(dev->useShadedFills(2));
    EXPECT_FALSE(dev->useShadedFills(3));
}

// Test markPoint doesn't crash
TEST_F(OutputDevTest_1066, MarkPoint_1066)
{
    EXPECT_NO_THROW(dev->markPoint("test"));
}

// Test beginMarkedContent/endMarkedContent
TEST_F(OutputDevTest_1066, MarkedContent_1066)
{
    auto state = createGfxState();
    EXPECT_NO_THROW(dev->beginMarkedContent("test", nullptr));
    EXPECT_NO_THROW(dev->endMarkedContent(state.get()));
}

// Test multiple profile start/end cycles
TEST_F(OutputDevTest_1066, MultipleProfileCycles_1066)
{
    dev->startProfile();
    auto profileData1 = dev->endProfile();
    EXPECT_NE(profileData1.get(), nullptr);

    dev->startProfile();
    auto profileData2 = dev->endProfile();
    EXPECT_NE(profileData2.get(), nullptr);
}

// Test initGfxState with nullptr should be handled (or crash - boundary test)
// Note: This tests behavior but may crash depending on implementation
// Commenting out to avoid undefined behavior
// TEST_F(OutputDevTest_1066, InitGfxStateNullptr_1066) { ... }

// Test beginType3Char default returns false
TEST_F(OutputDevTest_1066, BeginType3CharDefault_1066)
{
    auto state = createGfxState();
    bool result = dev->beginType3Char(state.get(), 0.0, 0.0, 0.0, 0.0, 0, nullptr, 0);
    EXPECT_FALSE(result);
}

// Test supportJPXtransparency default
TEST_F(OutputDevTest_1066, SupportJPXTransparencyDefault_1066)
{
    EXPECT_FALSE(dev->supportJPXtransparency());
}

// Test incCharCount no-op
TEST_F(OutputDevTest_1066, IncCharCount_1066)
{
    EXPECT_NO_THROW(dev->incCharCount(0));
    EXPECT_NO_THROW(dev->incCharCount(10));
    EXPECT_NO_THROW(dev->incCharCount(-1));
}

// Test initGfxState is idempotent (calling multiple times)
TEST_F(OutputDevTest_1066, InitGfxStateMultipleCalls_1066)
{
    auto state = createGfxState();
    EXPECT_NO_THROW(dev->initGfxState(state.get()));
    EXPECT_NO_THROW(dev->initGfxState(state.get()));
}

// Test clearSoftMask
TEST_F(OutputDevTest_1066, ClearSoftMask_1066)
{
    auto state = createGfxState();
    EXPECT_NO_THROW(dev->clearSoftMask(state.get()));
}

// Test endTransparencyGroup
TEST_F(OutputDevTest_1066, EndTransparencyGroup_1066)
{
    auto state = createGfxState();
    EXPECT_NO_THROW(dev->endTransparencyGroup(state.get()));
}

// Test processLink with nullptr
TEST_F(OutputDevTest_1066, ProcessLinkNull_1066)
{
    EXPECT_NO_THROW(dev->processLink(nullptr));
}
