#include <gtest/gtest.h>

#include "jobserver.h"



class JobserverTest_23 : public ::testing::Test {

protected:

    Jobserver::Slot validExplicitSlot;

    Jobserver::Slot invalidSlot;



    void SetUp() override {

        validExplicitSlot = Jobserver::Slot::CreateExplicit(42);

        invalidSlot = Jobserver::Slot();

    }

};



TEST_F(JobserverTest_23, IsValid_ReturnsTrueForValidExplicitSlot_23) {

    EXPECT_TRUE(validExplicitSlot.IsValid());

}



TEST_F(JobserverTest_23, IsValid_ReturnsFalseForInvalidSlot_23) {

    EXPECT_FALSE(invalidSlot.IsValid());

}



TEST_F(JobserverTest_23, CreateImplicit_ReturnsInvalidSlot_23) {

    Jobserver::Slot implicitSlot = Jobserver::Slot::CreateImplicit();

    EXPECT_FALSE(implicitSlot.IsValid());

}



TEST_F(JobserverTest_23, MoveConstructor_TransfersValidState_23) {

    Jobserver::Slot movedSlot = std::move(validExplicitSlot);

    EXPECT_TRUE(movedSlot.IsValid());

    EXPECT_FALSE(validExplicitSlot.IsValid()); // Original slot should be invalid after move

}



TEST_F(JobserverTest_23, MoveAssignment_TransfersValidState_23) {

    Jobserver::Slot targetSlot;

    targetSlot = std::move(validExplicitSlot);

    EXPECT_TRUE(targetSlot.IsValid());

    EXPECT_FALSE(validExplicitSlot.IsValid()); // Original slot should be invalid after move

}
