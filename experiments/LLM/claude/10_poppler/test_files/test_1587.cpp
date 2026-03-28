#include <gtest/gtest.h>
#include <cstring>

// Include necessary headers
#include "splash/SplashTypes.h"

// We need access to the static function. Declare it with the same signature.
// Since it's static in the .cc file, we include the .cc to get access.
// Alternatively, we replicate the function pointer or use a wrapper.

// splashColorModeNComps is defined in SplashTypes.h or related
// We need to access the static function, so we include the source file
#include "poppler/SplashOutputDev.cc"

class SplashOutBlendExclusionTest_1587 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ===================== RGB8 Mode Tests =====================

TEST_F(SplashOutBlendExclusionTest_1587, RGB8_BothZero_1587) {
    SplashColor src = {0, 0, 0, 0};
    SplashColor dest = {0, 0, 0, 0};
    SplashColor blend = {0, 0, 0, 0};
    splashOutBlendExclusion(src, dest, blend, splashModeRGB8);
    // blend[i] = 0 + 0 - 0 = 0
    for (int i = 0; i < 3; ++i) {
        EXPECT_EQ(blend[i], 0) << "Channel " << i;
    }
}

TEST_F(SplashOutBlendExclusionTest_1587, RGB8_BothMax_1587) {
    SplashColor src = {255, 255, 255, 0};
    SplashColor dest = {255, 255, 255, 0};
    SplashColor blend = {0, 0, 0, 0};
    splashOutBlendExclusion(src, dest, blend, splashModeRGB8);
    // blend[i] = 255 + 255 - (2*255*255)/255 = 510 - 510 = 0
    for (int i = 0; i < 3; ++i) {
        EXPECT_EQ(blend[i], 0) << "Channel " << i;
    }
}

TEST_F(SplashOutBlendExclusionTest_1587, RGB8_SrcZeroDestMax_1587) {
    SplashColor src = {0, 0, 0, 0};
    SplashColor dest = {255, 255, 255, 0};
    SplashColor blend = {0, 0, 0, 0};
    splashOutBlendExclusion(src, dest, blend, splashModeRGB8);
    // blend[i] = 255 + 0 - 0 = 255
    for (int i = 0; i < 3; ++i) {
        EXPECT_EQ(blend[i], 255) << "Channel " << i;
    }
}

TEST_F(SplashOutBlendExclusionTest_1587, RGB8_SrcMaxDestZero_1587) {
    SplashColor src = {255, 255, 255, 0};
    SplashColor dest = {0, 0, 0, 0};
    SplashColor blend = {0, 0, 0, 0};
    splashOutBlendExclusion(src, dest, blend, splashModeRGB8);
    // blend[i] = 0 + 255 - 0 = 255
    for (int i = 0; i < 3; ++i) {
        EXPECT_EQ(blend[i], 255) << "Channel " << i;
    }
}

TEST_F(SplashOutBlendExclusionTest_1587, RGB8_MidValues_1587) {
    SplashColor src = {128, 128, 128, 0};
    SplashColor dest = {128, 128, 128, 0};
    SplashColor blend = {0, 0, 0, 0};
    splashOutBlendExclusion(src, dest, blend, splashModeRGB8);
    // blend[i] = 128 + 128 - (2*128*128)/255 = 256 - 128 = 128
    // (2*128*128)/255 = 32768/255 = 128 (integer division)
    int expected = 128 + 128 - (2 * 128 * 128) / 255;
    for (int i = 0; i < 3; ++i) {
        EXPECT_EQ(blend[i], expected) << "Channel " << i;
    }
}

TEST_F(SplashOutBlendExclusionTest_1587, RGB8_DifferentChannels_1587) {
    SplashColor src = {100, 200, 50, 0};
    SplashColor dest = {150, 50, 200, 0};
    SplashColor blend = {0, 0, 0, 0};
    splashOutBlendExclusion(src, dest, blend, splashModeRGB8);
    
    EXPECT_EQ(blend[0], 150 + 100 - (2 * 150 * 100) / 255);
    EXPECT_EQ(blend[1], 50 + 200 - (2 * 50 * 200) / 255);
    EXPECT_EQ(blend[2], 200 + 50 - (2 * 200 * 50) / 255);
}

TEST_F(SplashOutBlendExclusionTest_1587, RGB8_SrcUnchanged_1587) {
    SplashColor src = {100, 200, 50, 0};
    SplashColor dest = {150, 50, 200, 0};
    SplashColor blend = {0, 0, 0, 0};
    SplashColor src_copy = {100, 200, 50, 0};
    splashOutBlendExclusion(src, dest, blend, splashModeRGB8);
    for (int i = 0; i < 3; ++i) {
        EXPECT_EQ(src[i], src_copy[i]) << "src channel " << i << " was modified";
    }
}

TEST_F(SplashOutBlendExclusionTest_1587, RGB8_DestUnchanged_1587) {
    SplashColor src = {100, 200, 50, 0};
    SplashColor dest = {150, 50, 200, 0};
    SplashColor blend = {0, 0, 0, 0};
    SplashColor dest_copy = {150, 50, 200, 0};
    splashOutBlendExclusion(src, dest, blend, splashModeRGB8);
    for (int i = 0; i < 3; ++i) {
        EXPECT_EQ(dest[i], dest_copy[i]) << "dest channel " << i << " was modified";
    }
}

// ===================== Mono8 Mode Tests =====================

TEST_F(SplashOutBlendExclusionTest_1587, Mono8_BothZero_1587) {
    SplashColor src = {0};
    SplashColor dest = {0};
    SplashColor blend = {0};
    splashOutBlendExclusion(src, dest, blend, splashModeMono8);
    EXPECT_EQ(blend[0], 0);
}

TEST_F(SplashOutBlendExclusionTest_1587, Mono8_BothMax_1587) {
    SplashColor src = {255};
    SplashColor dest = {255};
    SplashColor blend = {0};
    splashOutBlendExclusion(src, dest, blend, splashModeMono8);
    EXPECT_EQ(blend[0], 0);
}

TEST_F(SplashOutBlendExclusionTest_1587, Mono8_MixedValues_1587) {
    SplashColor src = {100};
    SplashColor dest = {200};
    SplashColor blend = {0};
    splashOutBlendExclusion(src, dest, blend, splashModeMono8);
    int expected = 200 + 100 - (2 * 200 * 100) / 255;
    EXPECT_EQ(blend[0], expected);
}

// ===================== BGR8 Mode Tests =====================

TEST_F(SplashOutBlendExclusionTest_1587, BGR8_DifferentChannels_1587) {
    SplashColor src = {30, 60, 90, 0};
    SplashColor dest = {120, 150, 180, 0};
    SplashColor blend = {0, 0, 0, 0};
    splashOutBlendExclusion(src, dest, blend, splashModeBGR8);
    for (int i = 0; i < 3; ++i) {
        int expected = dest[i] + src[i] - (2 * dest[i] * src[i]) / 255;
        EXPECT_EQ(blend[i], expected) << "Channel " << i;
    }
}

// ===================== XBGR8 Mode Tests =====================

TEST_F(SplashOutBlendExclusionTest_1587, XBGR8_DifferentChannels_1587) {
    SplashColor src = {30, 60, 90, 120};
    SplashColor dest = {120, 150, 180, 210};
    SplashColor blend = {0, 0, 0, 0};
    splashOutBlendExclusion(src, dest, blend, splashModeXBGR8);
    // XBGR8 has 4 components
    for (int i = 0; i < splashColorModeNComps[splashModeXBGR8]; ++i) {
        int expected = dest[i] + src[i] - (2 * dest[i] * src[i]) / 255;
        EXPECT_EQ(blend[i], expected) << "Channel " << i;
    }
}

// ===================== CMYK8 Mode Tests =====================

TEST_F(SplashOutBlendExclusionTest_1587, CMYK8_BothZero_1587) {
    SplashColor src = {0, 0, 0, 0};
    SplashColor dest = {0, 0, 0, 0};
    SplashColor blend = {0, 0, 0, 0};
    splashOutBlendExclusion(src, dest, blend, splashModeCMYK8);
    // After inversion: src=255, dest=255
    // blend = 255 + 255 - (2*255*255)/255 = 0
    // After re-inversion: blend = 255
    for (int i = 0; i < 4; ++i) {
        // src_inv=255, dest_inv=255 -> blend_raw = 255+255-510 = 0 -> blend_final = 255-0 = 255
        // Wait, let me recalculate...
        // Actually let me trace through:
        // Step 1: dest[i] = 255-0 = 255, src[i] = 255-0 = 255
        // Step 2: blend[i] = 255 + 255 - (2*255*255)/255 = 510 - 510 = 0
        // Step 3: dest[i] = 255-255=0, src[i] = 255-255=0, blend[i] = 255-0 = 255
        // Hmm, but blend is stored as unsigned char, 510 would overflow...
        // Actually 510 truncated to unsigned char = 254. Let's check.
        // No wait, the computation is: blend[i] = dest[i] + src[i] - (2 * dest[i] * src[i]) / 255
        // These are SplashColorPtr = unsigned char*
        // But the computation might be done in int due to promotion rules
        // dest[i]=255, src[i]=255: 255 + 255 - (2*255*255)/255 = 510 - 510 = 0
        // So blend[i] = 0, then inverted to 255
    }
    for (int i = 0; i < 4; ++i) {
        EXPECT_EQ(blend[i], 255) << "Channel " << i;
    }
}

TEST_F(SplashOutBlendExclusionTest_1587, CMYK8_BothMax_1587) {
    SplashColor src = {255, 255, 255, 255};
    SplashColor dest = {255, 255, 255, 255};
    SplashColor blend = {0, 0, 0, 0};
    splashOutBlendExclusion(src, dest, blend, splashModeCMYK8);
    // Step 1: dest[i] = 0, src[i] = 0
    // Step 2: blend[i] = 0 + 0 - 0 = 0
    // Step 3: dest[i]=255, src[i]=255, blend[i]=255
    for (int i = 0; i < 4; ++i) {
        EXPECT_EQ(blend[i], 255) << "Channel " << i;
    }
}

TEST_F(SplashOutBlendExclusionTest_1587, CMYK8_SrcZeroDestMax_1587) {
    SplashColor src = {0, 0, 0, 0};
    SplashColor dest = {255, 255, 255, 255};
    SplashColor blend = {0, 0, 0, 0};
    splashOutBlendExclusion(src, dest, blend, splashModeCMYK8);
    // Step 1: dest[i] = 0, src[i] = 255
    // Step 2: blend[i] = 0 + 255 - 0 = 255
    // Step 3: dest[i]=255, src[i]=0, blend[i]=0
    for (int i = 0; i < 4; ++i) {
        EXPECT_EQ(blend[i], 0) << "Channel " << i;
    }
}

TEST_F(SplashOutBlendExclusionTest_1587, CMYK8_SrcMaxDestZero_1587) {
    SplashColor src = {255, 255, 255, 255};
    SplashColor dest = {0, 0, 0, 0};
    SplashColor blend = {0, 0, 0, 0};
    splashOutBlendExclusion(src, dest, blend, splashModeCMYK8);
    // Step 1: dest[i] = 255, src[i] = 0
    // Step 2: blend[i] = 255 + 0 - 0 = 255
    // Step 3: dest[i]=0, src[i]=255, blend[i]=0
    for (int i = 0; i < 4; ++i) {
        EXPECT_EQ(blend[i], 0) << "Channel " << i;
    }
}

TEST_F(SplashOutBlendExclusionTest_1587, CMYK8_MidValues_1587) {
    SplashColor src = {128, 128, 128, 128};
    SplashColor dest = {128, 128, 128, 128};
    SplashColor blend = {0, 0, 0, 0};
    splashOutBlendExclusion(src, dest, blend, splashModeCMYK8);
    // Step 1: dest[i] = 127, src[i] = 127
    // Step 2: blend[i] = 127 + 127 - (2*127*127)/255 = 254 - 126 = 128
    // Step 3: blend[i] = 255 - 128 = 127
    int inv = 255 - 128; // 127
    int raw = inv + inv - (2 * inv * inv) / 255;
    int expected = 255 - raw;
    for (int i = 0; i < 4; ++i) {
        EXPECT_EQ(blend[i], expected) << "Channel " << i;
    }
}

TEST_F(SplashOutBlendExclusionTest_1587, CMYK8_SrcDestRestored_1587) {
    SplashColor src = {100, 150, 200, 50};
    SplashColor dest = {50, 100, 150, 200};
    SplashColor blend = {0, 0, 0, 0};
    SplashColor src_copy, dest_copy;
    memcpy(src_copy, src, sizeof(SplashColor));
    memcpy(dest_copy, dest, sizeof(SplashColor));
    splashOutBlendExclusion(src, dest, blend, splashModeCMYK8);
    // src and dest should be restored after double inversion
    for (int i = 0; i < 4; ++i) {
        EXPECT_EQ(src[i], src_copy[i]) << "src channel " << i << " not restored";
        EXPECT_EQ(dest[i], dest_copy[i]) << "dest channel " << i << " not restored";
    }
}

TEST_F(SplashOutBlendExclusionTest_1587, CMYK8_DifferentChannels_1587) {
    SplashColor src = {100, 150, 200, 50};
    SplashColor dest = {50, 100, 150, 200};
    SplashColor blend = {0, 0, 0, 0};
    splashOutBlendExclusion(src, dest, blend, splashModeCMYK8);
    for (int i = 0; i < 4; ++i) {
        int s_inv = 255 - src[i];
        int d_inv = 255 - dest[i];
        int raw = d_inv + s_inv - (2 * d_inv * s_inv) / 255;
        int expected = 255 - raw;
        // Need to use original src/dest values since they get restored
        s_inv = 255 - 100;
        d_inv = 255 - 50;
        if (i == 0) {
            s_inv = 255 - 100; d_inv = 255 - 50;
        } else if (i == 1) {
            s_inv = 255 - 150; d_inv = 255 - 100;
        } else if (i == 2) {
            s_inv = 255 - 200; d_inv = 255 - 150;
        } else {
            s_inv = 255 - 50; d_inv = 255 - 200;
        }
        raw = d_inv + s_inv - (2 * d_inv * s_inv) / 255;
        expected = 255 - raw;
        EXPECT_EQ(blend[i], (unsigned char)expected) << "Channel " << i;
    }
}

// ===================== DeviceN8 Mode Tests =====================

TEST_F(SplashOutBlendExclusionTest_1587, DeviceN8_BothZero_SpotChannelsZero_1587) {
    SplashColor src = {};
    SplashColor dest = {};
    SplashColor blend = {};
    memset(src, 0, sizeof(SplashColor));
    memset(dest, 0, sizeof(SplashColor));
    memset(blend, 0, sizeof(SplashColor));
    splashOutBlendExclusion(src, dest, blend, splashModeDeviceN8);
    int nComps = splashColorModeNComps[splashModeDeviceN8];
    // For CMYK channels (0-3): same as CMYK8 both zero -> 255
    for (int i = 0; i < 4; ++i) {
        EXPECT_EQ(blend[i], 255) << "Channel " << i;
    }
    // For spot color channels (4+): both dest=0, src=0, so blend forced to 0
    for (int i = 4; i < nComps; ++i) {
        EXPECT_EQ(blend[i], 0) << "Spot channel " << i;
    }
}

TEST_F(SplashOutBlendExclusionTest_1587, DeviceN8_SpotChannelsNonZero_1587) {
    SplashColor src = {};
    SplashColor dest = {};
    SplashColor blend = {};
    memset(src, 0, sizeof(SplashColor));
    memset(dest, 0, sizeof(SplashColor));
    memset(blend, 0, sizeof(SplashColor));
    int nComps = splashColorModeNComps[splashModeDeviceN8];
    // Set spot channels to non-zero
    for (int i = 4; i < nComps; ++i) {
        src[i] = 100;
        dest[i] = 100;
    }
    splashOutBlendExclusion(src, dest, blend, splashModeDeviceN8);
    // Spot channels where both original src and dest are non-zero
    // After inversion and computation, they should follow the exclusion formula
    for (int i = 4; i < nComps; ++i) {
        int s_inv = 255 - 100;
        int d_inv = 255 - 100;
        int raw = d_inv + s_inv - (2 * d_inv * s_inv) / 255;
        int expected = 255 - raw;
        EXPECT_EQ(blend[i], (unsigned char)expected) << "Spot channel " << i;
    }
}

TEST_F(SplashOutBlendExclusionTest_1587, DeviceN8_SpotChannelOneSrcZero_1587) {
    SplashColor src = {};
    SplashColor dest = {};
    SplashColor blend = {};
    memset(src, 0, sizeof(SplashColor));
    memset(dest, 0, sizeof(SplashColor));
    memset(blend, 0, sizeof(SplashColor));
    int nComps = splashColorModeNComps[splashModeDeviceN8];
    // Set only dest spot channels to non-zero, src is 0
    for (int i = 4; i < nComps; ++i) {
        dest[i] = 100;
    }
    splashOutBlendExclusion(src, dest, blend, splashModeDeviceN8);
    // src[i]=0 but dest[i]!=0, so the special zeroing doesn't apply
    for (int i = 4; i < nComps; ++i) {
        int s_inv = 255 - 0;
        int d_inv = 255 - 100;
        int raw = d_inv + s_inv - (2 * d_inv * s_inv) / 255;
        int expected = 255 - raw;
        EXPECT_EQ(blend[i], (unsigned char)expected) << "Spot channel " << i;
    }
}

TEST_F(SplashOutBlendExclusionTest_1587, DeviceN8_SpotChannelOneDestZero_1587) {
    SplashColor src = {};
    SplashColor dest = {};
    SplashColor blend = {};
    memset(src, 0, sizeof(SplashColor));
    memset(dest, 0, sizeof(SplashColor));
    memset(blend, 0, sizeof(SplashColor));
    int nComps = splashColorModeNComps[splashModeDeviceN8];
    for (int i = 4; i < nComps; ++i) {
        src[i] = 100;
    }
    splashOutBlendExclusion(src, dest, blend, splashModeDeviceN8);
    // dest[i]=0 but src[i]!=0, so the special zeroing doesn't apply
    for (int i = 4; i < nComps; ++i) {
        int s_inv = 255 - 100;
        int d_inv = 255 - 0;
        int raw = d_inv + s_inv - (2 * d_inv * s_inv) / 255;
        int expected = 255 - raw;
        EXPECT_EQ(blend[i], (unsigned char)expected) << "Spot channel " << i;
    }
}

TEST_F(SplashOutBlendExclusionTest_1587, DeviceN8_SrcDestRestored_1587) {
    SplashColor src = {};
    SplashColor dest = {};
    SplashColor blend = {};
    memset(blend, 0, sizeof(SplashColor));
    int nComps = splashColorModeNComps[splashModeDeviceN8];
    for (int i = 0; i < nComps; ++i) {
        src[i] = (unsigned char)(i * 17);
        dest[i] = (unsigned char)(255 - i * 17);
    }
    SplashColor src_copy, dest_copy;
    memcpy(src_copy, src, sizeof(SplashColor));
    memcpy(dest_copy, dest, sizeof(SplashColor));
    splashOutBlendExclusion(src, dest, blend, splashModeDeviceN8);
    for (int i = 0; i < nComps; ++i) {
        EXPECT_EQ(src[i], src_copy[i]) << "src channel " << i;
        EXPECT_EQ(dest[i], dest_copy[i]) << "dest channel " << i;
    }
}

// ===================== Edge case: single value 1 =====================

TEST_F(SplashOutBlendExclusionTest_1587, RGB8_SmallValues_1587) {
    SplashColor src = {1, 1, 1, 0};
    SplashColor dest = {1, 1, 1, 0};
    SplashColor blend = {0, 0, 0, 0};
    splashOutBlendExclusion(src, dest, blend, splashModeRGB8);
    // blend[i] = 1 + 1 - (2*1*1)/255 = 2 - 0 = 2
    for (int i = 0; i < 3; ++i) {
        EXPECT_EQ(blend[i], 2) << "Channel " << i;
    }
}

TEST_F(SplashOutBlendExclusionTest_1587, RGB8_Value254_1587) {
    SplashColor src = {254, 254, 254, 0};
    SplashColor dest = {254, 254, 254, 0};
    SplashColor blend = {0, 0, 0, 0};
    splashOutBlendExclusion(src, dest, blend, splashModeRGB8);
    int expected = 254 + 254 - (2 * 254 * 254) / 255;
    for (int i = 0; i < 3; ++i) {
        EXPECT_EQ(blend[i], (unsigned char)expected) << "Channel " << i;
    }
}

TEST_F(SplashOutBlendExclusionTest_1587, RGB8_Asymmetric_1587) {
    SplashColor src = {0, 255, 128, 0};
    SplashColor dest = {255, 0, 128, 0};
    SplashColor blend = {0, 0, 0, 0};
    splashOutBlendExclusion(src, dest, blend, splashModeRGB8);
    // Channel 0: 255 + 0 - 0 = 255
    EXPECT_EQ(blend[0], 255);
    // Channel 1: 0 + 255 - 0 = 255
    EXPECT_EQ(blend[1], 255);
    // Channel 2: 128 + 128 - (2*128*128)/255 = 256 - 128 = 128
    int expected = 128 + 128 - (2 * 128 * 128) / 255;
    EXPECT_EQ(blend[2], (unsigned char)expected);
}

// ===================== Commutativity check =====================

TEST_F(SplashOutBlendExclusionTest_1587, RGB8_CommutativeProperty_1587) {
    SplashColor src1 = {50, 100, 200, 0};
    SplashColor dest1 = {200, 150, 50, 0};
    SplashColor blend1 = {0, 0, 0, 0};
    
    SplashColor src2 = {200, 150, 50, 0};
    SplashColor dest2 = {50, 100, 200, 0};
    SplashColor blend2 = {0, 0, 0, 0};
    
    splashOutBlendExclusion(src1, dest1, blend1, splashModeRGB8);
    splashOutBlendExclusion(src2, dest2, blend2, splashModeRGB8);
    
    // Exclusion blend is commutative: f(a,b) = f(b,a)
    for (int i = 0; i < 3; ++i) {
        EXPECT_EQ(blend1[i], blend2[i]) << "Channel " << i;
    }
}

// ===================== Mono1 mode (1 component) =====================

TEST_F(SplashOutBlendExclusionTest_1587, Mono1_BasicTest_1587) {
    SplashColor src = {128};
    SplashColor dest = {64};
    SplashColor blend = {0};
    splashOutBlendExclusion(src, dest, blend, splashModeMono1);
    // splashModeMono1 has 1 component
    // blend[0] = 64 + 128 - (2*64*128)/255 = 192 - 64 = 128
    int expected = 64 + 128 - (2 * 64 * 128) / 255;
    EXPECT_EQ(blend[0], (unsigned char)expected);
}