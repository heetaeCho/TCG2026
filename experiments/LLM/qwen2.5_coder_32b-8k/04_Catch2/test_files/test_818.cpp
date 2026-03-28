#include <gmock/gmock.h>

#include <gtest/gtest.h>

#include "catch_interfaces_config.hpp"



using namespace Catch;

using ::testing::Return;



class MockConfig : public IConfig {

public:

    MOCK_CONST_METHOD0(showDurations, ShowDurations());

    MOCK_CONST_METHOD0(minDuration, double());

};



class ReporterHelpersTest_818 : public ::testing::Test {

protected:

    std::unique_ptr<MockConfig> mock_config;

    void SetUp() override {

        mock_config = std::make_unique<MockConfig>();

    }

};



TEST_F(ReporterHelpersTest_818, ShouldShowDuration_Always_ReturnsTrue_818) {

    EXPECT_CALL(*mock_config, showDurations()).WillOnce(Return(ShowDurations::Always));

    bool result = shouldShowDuration(*mock_config.get(), 0.0);

    EXPECT_TRUE(result);

}



TEST_F(ReporterHelpersTest_818, ShouldShowDuration_Never_ReturnsFalse_818) {

    EXPECT_CALL(*mock_config, showDurations()).WillOnce(Return(ShowDurations::Never));

    bool result = shouldShowDuration(*mock_config.get(), 0.0);

    EXPECT_FALSE(result);

}



TEST_F(ReporterHelpersTest_818, ShouldShowDuration_DefaultForReporter_ZeroMinDuration_ReturnsTrue_818) {

    EXPECT_CALL(*mock_config, showDurations()).WillOnce(Return(ShowDurations::DefaultForReporter));

    EXPECT_CALL(*mock_config, minDuration()).WillOnce(Return(0.0));

    bool result = shouldShowDuration(*mock_config.get(), 1.0);

    EXPECT_TRUE(result);

}



TEST_F(ReporterHelpersTest_818, ShouldShowDuration_DefaultForReporter_NonZeroMinDuration_LessThanDuration_ReturnsTrue_818) {

    EXPECT_CALL(*mock_config, showDurations()).WillOnce(Return(ShowDurations::DefaultForReporter));

    EXPECT_CALL(*mock_config, minDuration()).WillOnce(Return(0.5));

    bool result = shouldShowDuration(*mock_config.get(), 1.0);

    EXPECT_TRUE(result);

}



TEST_F(ReporterHelpersTest_818, ShouldShowDuration_DefaultForReporter_NonZeroMinDuration_GreaterThanDuration_ReturnsFalse_818) {

    EXPECT_CALL(*mock_config, showDurations()).WillOnce(Return(ShowDurations::DefaultForReporter));

    EXPECT_CALL(*mock_config, minDuration()).WillOnce(Return(2.0));

    bool result = shouldShowDuration(*mock_config.get(), 1.0);

    EXPECT_FALSE(result);

}



TEST_F(ReporterHelpersTest_818, ShouldShowDuration_DefaultForReporter_NegativeMinDuration_ReturnsFalse_818) {

    EXPECT_CALL(*mock_config, showDurations()).WillOnce(Return(ShowDurations::DefaultForReporter));

    EXPECT_CALL(*mock_config, minDuration()).WillOnce(Return(-1.0));

    bool result = shouldShowDuration(*mock_config.get(), 1.0);

    EXPECT_FALSE(result);

}
