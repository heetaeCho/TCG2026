#include <gtest/gtest.h>

#include "GfxState.h"

#include <memory>



class GfxDeviceNColorSpaceTest_486 : public ::testing::Test {

protected:

    std::unique_ptr<GfxColorSpace> altCS;

    std::unique_ptr<Function> tintTransformFunc;

    std::vector<std::string> names = {"name1", "name2"};

    std::vector<std::unique_ptr<GfxSeparationColorSpace>> sepsCS;



    void SetUp() override {

        altCS = nullptr; // Assuming no alternative color space for simplicity

        tintTransformFunc = nullptr; // Assuming no tint transform function for simplicity

    }



    GfxDeviceNColorSpace createGfxDeviceNColorSpace(int nComps, std::vector<std::string>&& names, std::unique_ptr<GfxColorSpace>&& alt, std::unique_ptr<Function> func, std::vector<std::unique_ptr<GfxSeparationColorSpace>>&& sepsCS) {

        return GfxDeviceNColorSpace(nComps, std::move(names), std::move(alt), std::move(func), std::move(sepsCS));

    }

};



TEST_F(GfxDeviceNColorSpaceTest_486, GetTintTransformFunc_ReturnsNullptr_486) {

    auto deviceN = createGfxDeviceNColorSpace(2, {"name1", "name2"}, nullptr, nullptr, {});

    EXPECT_EQ(deviceN.getTintTransformFunc(), nullptr);

}



TEST_F(GfxDeviceNColorSpaceTest_486, GetTintTransformFunc_ReturnsValidFunctionPointer_486) {

    tintTransformFunc = std::make_unique<Function>(); // Assuming Function is default constructible

    auto deviceN = createGfxDeviceNColorSpace(2, {"name1", "name2"}, nullptr, std::move(tintTransformFunc), {});

    EXPECT_NE(deviceN.getTintTransformFunc(), nullptr);

}



TEST_F(GfxDeviceNColorSpaceTest_486, GetNComps_ReturnsCorrectNumberOfComponents_486) {

    auto deviceN = createGfxDeviceNColorSpace(3, {"name1", "name2", "name3"}, nullptr, nullptr, {});

    EXPECT_EQ(deviceN.getNComps(), 3);

}



TEST_F(GfxDeviceNColorSpaceTest_486, GetColorantName_ReturnsCorrectNameForValidIndex_486) {

    auto deviceN = createGfxDeviceNColorSpace(2, {"name1", "name2"}, nullptr, nullptr, {});

    EXPECT_EQ(deviceN.getColorantName(0), "name1");

    EXPECT_EQ(deviceN.getColorantName(1), "name2");

}



TEST_F(GfxDeviceNColorSpaceTest_486, GetColorantName_ReturnsEmptyStringForInvalidIndex_486) {

    auto deviceN = createGfxDeviceNColorSpace(2, {"name1", "name2"}, nullptr, nullptr, {});

    EXPECT_EQ(deviceN.getColorantName(-1), "");

    EXPECT_EQ(deviceN.getColorantName(2), "");

}



TEST_F(GfxDeviceNColorSpaceTest_486, GetAlt_ReturnsNullptrWhenNoAlternativeColorSpace_486) {

    auto deviceN = createGfxDeviceNColorSpace(2, {"name1", "name2"}, nullptr, nullptr, {});

    EXPECT_EQ(deviceN.getAlt(), nullptr);

}



TEST_F(GfxDeviceNColorSpaceTest_486, GetAlt_ReturnsValidPointerWhenAlternativeColorSpaceExists_486) {

    altCS = std::make_unique<GfxCalGray>(GfxRenderingIntent::AbsoluteColorimetric); // Assuming GfxCalGray is a valid alternative

    auto deviceN = createGfxDeviceNColorSpace(2, {"name1", "name2"}, std::move(altCS), nullptr, {});

    EXPECT_NE(deviceN.getAlt(), nullptr);

}
