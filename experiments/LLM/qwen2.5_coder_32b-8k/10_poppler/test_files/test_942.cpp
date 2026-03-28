#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/OptionalContent.h"



class OptionalContentGroupTest_942 : public ::testing::Test {

protected:

    Dict* dict;

    OptionalContentGroup* ocg;



    void SetUp() override {

        dict = new Dict();

        ocg = new OptionalContentGroup(dict);

    }



    void TearDown() override {

        delete ocg;

        delete dict;

    }

};



TEST_F(OptionalContentGroupTest_942, DefaultStateIsOff_942) {

    EXPECT_EQ(ocg->getState(), State::Off);

}



TEST_F(OptionalContentGroupTest_942, SetAndGetState_942) {

    ocg->setState(State::On);

    EXPECT_EQ(ocg->getState(), State::On);



    ocg->setState(State::Toggle);

    EXPECT_EQ(ocg->getState(), State::Toggle);

}



TEST_F(OptionalContentGroupTest_942, GetRefInitiallyEmpty_942) {

    Ref ref = ocg->getRef();

    EXPECT_TRUE(ref.num == 0 && ref.gen == 0);

}



TEST_F(OptionalContentGroupTest_942, SetAndGetRef_942) {

    Ref newRef{123, 456};

    ocg->setRef(newRef);



    Ref retrievedRef = ocg->getRef();

    EXPECT_EQ(retrievedRef.num, 123);

    EXPECT_EQ(retrievedRef.gen, 456);

}



TEST_F(OptionalContentGroupTest_942, DefaultViewStateIsUnchanged_942) {

    EXPECT_EQ(ocg->getViewState(), UsageState::Unchanged);

}



TEST_F(OptionalContentGroupTest_942, DefaultPrintStateIsUnchanged_942) {

    EXPECT_EQ(ocg->getPrintState(), UsageState::Unchanged);

}
