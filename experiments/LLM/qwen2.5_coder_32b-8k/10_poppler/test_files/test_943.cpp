#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/OptionalContent.h"

#include <memory>



// Assuming State and UsageState are enums or types defined elsewhere

enum class State { On, Off };

enum class UsageState { Used, Unused };



class OptionalContentGroupTest_943 : public ::testing::Test {

protected:

    std::unique_ptr<OptionalContentGroup> ocg;



    void SetUp() override {

        // Assuming Dict is a type defined elsewhere and can be nullptr for testing purposes

        ocg = std::make_unique<OptionalContentGroup>(nullptr);

    }

};



TEST_F(OptionalContentGroupTest_943, DefaultStateIsOff_943) {

    EXPECT_EQ(ocg->getState(), State::Off);

}



TEST_F(OptionalContentGroupTest_943, SetAndGetStateOn_943) {

    ocg->setState(State::On);

    EXPECT_EQ(ocg->getState(), State::On);

}



TEST_F(OptionalContentGroupTest_943, SetAndGetStateOff_943) {

    ocg->setState(State::Off);

    EXPECT_EQ(ocg->getState(), State::Off);

}



TEST_F(OptionalContentGroupTest_943, DefaultViewStateIsUnused_943) {

    EXPECT_EQ(ocg->getViewState(), UsageState::Unused);

}



TEST_F(OptionalContentGroupTest_943, DefaultPrintStateIsUnused_943) {

    EXPECT_EQ(ocg->getPrintState(), UsageState::Unused);

}
