#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/poppler/poppler/OutputDev.h"

#include "TestProjects/poppler/poppler/GfxState.h"



using namespace testing;



class MockGfxState : public GfxState {

public:

    MOCK_METHOD(void, setDisplayProfile, (const GfxLCMSProfilePtr&), (override));

    MOCK_METHOD(void, setDefaultGrayColorSpace, (std::unique_ptr<GfxColorSpace>&&), (override));

    MOCK_METHOD(void, setDefaultRGBColorSpace, (std::unique_ptr<GfxColorSpace>&&), (override));

    MOCK_METHOD(void, setDefaultCMYKColorSpace, (std::unique_ptr<GfxColorSpace>&&), (override));

};



class OutputDevTest : public ::testing::Test {

protected:

    std::unique_ptr<MockGfxState> mock_state;

    OutputDev output_dev;



    void SetUp() override {

        mock_state = std::make_unique<MockGfxState>();

    }

};



TEST_F(OutputDevTest_1066, InitGfxState_CallsSetDisplayProfile_1066) {

    EXPECT_CALL(*mock_state, setDisplayProfile(_)).Times(1);

    output_dev.initGfxState(mock_state.get());

}



TEST_F(OutputDevTest_1066, InitGfxState_SetsDefaultGrayColorSpaceIfPresent_1066) {

    auto gray_profile = GfxLCMSProfilePtr();

    output_dev.setDefaultGrayProfile(gray_profile);



    EXPECT_CALL(*mock_state, setDisplayProfile(_)).Times(1);

    EXPECT_CALL(*mock_state, setDefaultGrayColorSpace(_)).Times(1);

    output_dev.initGfxState(mock_state.get());

}



TEST_F(OutputDevTest_1066, InitGfxState_SetsDefaultRGBColorSpaceIfPresent_1066) {

    auto rgb_profile = GfxLCMSProfilePtr();

    output_dev.setDefaultRGBProfile(rgb_profile);



    EXPECT_CALL(*mock_state, setDisplayProfile(_)).Times(1);

    EXPECT_CALL(*mock_state, setDefaultRGBColorSpace(_)).Times(1);

    output_dev.initGfxState(mock_state.get());

}



TEST_F(OutputDevTest_1066, InitGfxState_SetsDefaultCMYKColorSpaceIfPresent_1066) {

    auto cmyk_profile = GfxLCMSProfilePtr();

    output_dev.setDefaultCMYKProfile(cmyk_profile);



    EXPECT_CALL(*mock_state, setDisplayProfile(_)).Times(1);

    EXPECT_CALL(*mock_state, setDefaultCMYKColorSpace(_)).Times(1);

    output_dev.initGfxState(mock_state.get());

}



TEST_F(OutputDevTest_1066, InitGfxState_DoesNotSetAnyProfilesIfNonePresent_1066) {

    EXPECT_CALL(*mock_state, setDisplayProfile(_)).Times(1);

    EXPECT_CALL(*mock_state, setDefaultGrayColorSpace(_)).Times(0);

    EXPECT_CALL(*mock_state, setDefaultRGBColorSpace(_)).Times(0);

    EXPECT_CALL(*mock_state, setDefaultCMYKColorSpace(_)).Times(0);

    output_dev.initGfxState(mock_state.get());

}
