#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "lcms2.h"



// Mocking GfxLCMSProfilePtr for dependency injection in tests.

class MockGfxLCMSProfile {

public:

    MOCK_METHOD(cmsHPROFILE, get, (), (const));

};



using GfxLCMSProfilePtr = std::shared_ptr<MockGfxLCMSProfile>;



TEST_F(SanityChecksTest_2635, NullProfile_ReturnsFalseAndLogsError_2635) {

    GfxLCMSProfilePtr profile = nullptr;

    testing::internal::CaptureStderr();

    bool result = checkICCProfile(profile, "test.icc", LCMS_USED_AS_OUTPUT, cmsSigRgbData);

    std::string output = testing::internal::GetCapturedStderr();



    EXPECT_FALSE(result);

    EXPECT_EQ(output, "Could not open the ICC profile \"test.icc\".\n");

}



TEST_F(SanityChecksTest_2635, UnsupportedIntents_ReturnsFalseAndLogsErrorForOutputProfile_2635) {

    auto mockProfile = std::make_shared<MockGfxLCMSProfile>();

    EXPECT_CALL(*mockProfile, get())

        .WillRepeatedly(::testing::Return(reinterpret_cast<cmsHPROFILE>(1)));



    ON_CALL(*mockProfile, get()).WillByDefault(::testing::Return(reinterpret_cast<cmsHPROFILE>(1)));

    EXPECT_CALL(::testing::A<cmsHPROFILE>(), cmsIsIntentSupported(testing::_, INTENT_RELATIVE_COLORIMETRIC, LCMS_USED_AS_OUTPUT))

        .WillOnce(::testing::Return(false));

    EXPECT_CALL(::testing::A<cmsHPROFILE>(), cmsIsIntentSupported(testing::_, INTENT_ABSOLUTE_COLORIMETRIC, LCMS_USED_AS_OUTPUT))

        .WillOnce(::testing::Return(false));

    EXPECT_CALL(::testing::A<cmsHPROFILE>(), cmsIsIntentSupported(testing::_, INTENT_SATURATION, LCMS_USED_AS_OUTPUT))

        .WillOnce(::testing::Return(false));

    EXPECT_CALL(::testing::A<cmsHPROFILE>(), cmsIsIntentSupported(testing::_, INTENT_PERCEPTUAL, LCMS_USED_AS_OUTPUT))

        .WillOnce(::testing::Return(false));



    testing::internal::CaptureStderr();

    bool result = checkICCProfile(mockProfile, "test.icc", LCMS_USED_AS_OUTPUT, cmsSigRgbData);

    std::string output = testing::internal::GetCapturedStderr();



    EXPECT_FALSE(result);

    EXPECT_EQ(output, "ICC profile \"test.icc\" is not an output profile.\n");

}



TEST_F(SanityChecksTest_2635, UnsupportedIntents_ReturnsFalseAndLogsErrorForInputProfile_2635) {

    auto mockProfile = std::make_shared<MockGfxLCMSProfile>();

    EXPECT_CALL(*mockProfile, get())

        .WillRepeatedly(::testing::Return(reinterpret_cast<cmsHPROFILE>(1)));



    ON_CALL(*mockProfile, get()).WillByDefault(::testing::Return(reinterpret_cast<cmsHPROFILE>(1)));

    EXPECT_CALL(::testing::A<cmsHPROFILE>(), cmsIsIntentSupported(testing::_, INTENT_RELATIVE_COLORIMETRIC, LCMS_USED_AS_INPUT))

        .WillOnce(::testing::Return(false));

    EXPECT_CALL(::testing::A<cmsHPROFILE>(), cmsIsIntentSupported(testing::_, INTENT_ABSOLUTE_COLORIMETRIC, LCMS_USED_AS_INPUT))

        .WillOnce(::testing::Return(false));

    EXPECT_CALL(::testing::A<cmsHPROFILE>(), cmsIsIntentSupported(testing::_, INTENT_SATURATION, LCMS_USED_AS_INPUT))

        .WillOnce(::testing::Return(false));

    EXPECT_CALL(::testing::A<cmsHPROFILE>(), cmsIsIntentSupported(testing::_, INTENT_PERCEPTUAL, LCMS_USED_AS_INPUT))

        .WillOnce(::testing::Return(false));



    testing::internal::CaptureStderr();

    bool result = checkICCProfile(mockProfile, "test.icc", LCMS_USED_AS_INPUT, cmsSigRgbData);

    std::string output = testing::internal::GetCapturedStderr();



    EXPECT_FALSE(result);

    EXPECT_EQ(output, "ICC profile \"test.icc\" is not an input profile.\n");

}



TEST_F(SanityChecksTest_2635, UnsupportedIntents_ReturnsFalseAndLogsGenericError_2635) {

    auto mockProfile = std::make_shared<MockGfxLCMSProfile>();

    EXPECT_CALL(*mockProfile, get())

        .WillRepeatedly(::testing::Return(reinterpret_cast<cmsHPROFILE>(1)));



    ON_CALL(*mockProfile, get()).WillByDefault(::testing::Return(reinterpret_cast<cmsHPROFILE>(1)));

    EXPECT_CALL(::testing::A<cmsHPROFILE>(), cmsIsIntentSupported(testing::_, INTENT_RELATIVE_COLORIMETRIC, 3))

        .WillOnce(::testing::Return(false));

    EXPECT_CALL(::testing::A<cmsHPROFILE>(), cmsIsIntentSupported(testing::_, INTENT_ABSOLUTE_COLORIMETRIC, 3))

        .WillOnce(::testing::Return(false));

    EXPECT_CALL(::testing::A<cmsHPROFILE>(), cmsIsIntentSupported(testing::_, INTENT_SATURATION, 3))

        .WillOnce(::testing::Return(false));

    EXPECT_CALL(::testing::A<cmsHPROFILE>(), cmsIsIntentSupported(testing::_, INTENT_PERCEPTUAL, LCMS_USED_AS_OUTPUT))

        .WillOnce(::testing::Return(false));



    testing::internal::CaptureStderr();

    bool result = checkICCProfile(mockProfile, "test.icc", 3, cmsSigRgbData);

    std::string output = testing::internal::GetCapturedStderr();



    EXPECT_FALSE(result);

    EXPECT_EQ(output, "ICC profile \"test.icc\" is not suitable.\n");

}



TEST_F(SanityChecksTest_2635, WrongColorSpace_ReturnsFalseAndLogsErrorForCMYK_2635) {

    auto mockProfile = std::make_shared<MockGfxLCMSProfile>();

    EXPECT_CALL(*mockProfile, get())

        .WillRepeatedly(::testing::Return(reinterpret_cast<cmsHPROFILE>(1)));



    ON_CALL(*mockProfile, get()).WillByDefault(::testing::Return(reinterpret_cast<cmsHPROFILE>(1)));

    EXPECT_CALL(::testing::A<cmsHPROFILE>(), cmsIsIntentSupported(testing::_, INTENT_RELATIVE_COLORIMETRIC, LCMS_USED_AS_OUTPUT))

        .WillOnce(::testing::Return(true));

    EXPECT_CALL(::testing::A<cmsHPROFILE>(), cmsGetColorSpace(testing::_))

        .WillOnce(::testing::Return(cmsSigRgbData));



    testing::internal::CaptureStderr();

    bool result = checkICCProfile(mockProfile, "test.icc", LCMS_USED_AS_OUTPUT, cmsSigCmykData);

    std::string output = testing::internal::GetCapturedStderr();



    EXPECT_FALSE(result);

    EXPECT_EQ(output, "Supplied ICC profile \"test.icc\" is not a CMYK profile.\n");

}



TEST_F(SanityChecksTest_2635, WrongColorSpace_ReturnsFalseAndLogsErrorForGray_2635) {

    auto mockProfile = std::make_shared<MockGfxLCMSProfile>();

    EXPECT_CALL(*mockProfile, get())

        .WillRepeatedly(::testing::Return(reinterpret_cast<cmsHPROFILE>(1)));



    ON_CALL(*mockProfile, get()).WillByDefault(::testing::Return(reinterpret_cast<cmsHPROFILE>(1)));

    EXPECT_CALL(::testing::A<cmsHPROFILE>(), cmsIsIntentSupported(testing::_, INTENT_RELATIVE_COLORIMETRIC, LCMS_USED_AS_OUTPUT))

        .WillOnce(::testing::Return(true));

    EXPECT_CALL(::testing::A<cmsHPROFILE>(), cmsGetColorSpace(testing::_))

        .WillOnce(::testing::Return(cmsSigRgbData));



    testing::internal::CaptureStderr();

    bool result = checkICCProfile(mockProfile, "test.icc", LCMS_USED_AS_OUTPUT, cmsSigGrayData);

    std::string output = testing::internal::GetCapturedStderr();



    EXPECT_FALSE(result);

    EXPECT_EQ(output, "Supplied ICC profile \"test.icc\" is not a monochrome profile.\n");

}



TEST_F(SanityChecksTest_2635, CorrectProfileAndColorSpace_ReturnsTrue_2635) {

    auto mockProfile = std::make_shared<MockGfxLCMSProfile>();

    EXPECT_CALL(*mockProfile, get())

        .WillRepeatedly(::testing::Return(reinterpret_cast<cmsHPROFILE>(1)));



    ON_CALL(*mockProfile, get()).WillByDefault(::testing::Return(reinterpret_cast<cmsHPROFILE>(1)));

    EXPECT_CALL(::testing::A<cmsHPROFILE>(), cmsIsIntentSupported(testing::_, INTENT_RELATIVE_COLORIMETRIC, LCMS_USED_AS_OUTPUT))

        .WillOnce(::testing::Return(true));

    EXPECT_CALL(::testing::A<cmsHPROFILE>(), cmsGetColorSpace(testing::_))

        .WillOnce(::testing::Return(cmsSigRgbData));



    bool result = checkICCProfile(mockProfile, "test.icc", LCMS_USED_AS_OUTPUT, cmsSigRgbData);

    

    EXPECT_TRUE(result);

}
