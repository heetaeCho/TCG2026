#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "GfxState.h"



using ::testing::NiceMock;

using ::testing::Return;



class MockGfxColorSpace : public GfxColorSpace {

public:

    MOCK_METHOD(std::unique_ptr<GfxColorSpace>, copy, (), (const, override));

};



TEST_F(GfxStateTest_660, CopyDefaultCMYKColorSpace_ReturnsNewInstance_660) {

    GfxState gfxState(1.0, 1.0, nullptr, 0, false);

    auto cmykColorSpace = std::make_unique<MockGfxColorSpace>();

    gfxState.setDefaultCMYKColorSpace(std::move(cmykColorSpace));



    auto copiedColorSpace = gfxState.copyDefaultCMYKColorSpace();



    EXPECT_NE(copiedColorSpace.get(), nullptr);

}



TEST_F(GfxStateTest_660, CopyDefaultCMYKColorSpace_ReturnsNewInstanceWhenDefaultIsNull_660) {

    GfxState gfxState(1.0, 1.0, nullptr, 0, false);



    auto copiedColorSpace = gfxState.copyDefaultCMYKColorSpace();



    EXPECT_NE(copiedColorSpace.get(), nullptr);

}



TEST_F(GfxStateTest_660, CopyDefaultCMYKColorSpace_CallsCopyMethodOfGfxColorSpace_660) {

    GfxState gfxState(1.0, 1.0, nullptr, 0, false);

    auto mockColorSpace = std::make_unique<NiceMock<MockGfxColorSpace>>();

    EXPECT_CALL(*mockColorSpace, copy()).WillOnce(Return(std::make_unique<GfxDeviceCMYKColorSpace>()));

    gfxState.setDefaultCMYKColorSpace(std::move(mockColorSpace));



    gfxState.copyDefaultCMYKColorSpace();

}
