#include <gtest/gtest.h>

#include "jobserver.h"



using namespace testing;



class JobserverSlotTest : public ::testing::Test {

protected:

    Jobserver::Slot slot;

};



TEST_F(JobserverSlotTest_22, DefaultConstructorInitializesInvalidSlot_22) {

    EXPECT_FALSE(slot.IsValid());

}



TEST_F(JobserverSlotTest_22, MoveAssignmentTransfersValue_22) {

    Jobserver::Slot source = Jobserver::Slot::CreateExplicit(42);

    slot = std::move(source);



    EXPECT_TRUE(slot.IsValid());

    EXPECT_EQ(slot.GetExplicitValue(), 42);

    EXPECT_FALSE(source.IsValid());

}



TEST_F(JobserverSlotTest_22, CreateExplicitInitializesValidSlot_22) {

    Jobserver::Slot explicitSlot = Jobserver::Slot::CreateExplicit(10);



    EXPECT_TRUE(explicitSlot.IsValid());

    EXPECT_TRUE(explicitSlot.IsExplicit());

    EXPECT_EQ(explicitSlot.GetExplicitValue(), 10);

}



TEST_F(JobserverSlotTest_22, CreateImplicitInitializesValidImplicitSlot_22) {

    Jobserver::Slot implicitSlot = Jobserver::Slot::CreateImplicit();



    EXPECT_TRUE(implicitSlot.IsValid());

    EXPECT_TRUE(implicitSlot.IsImplicit());

}



TEST_F(JobserverSlotTest_22, MoveConstructorTransfersValue_22) {

    Jobserver::Slot source = Jobserver::Slot::CreateExplicit(5);

    Jobserver::Slot movedSlot = std::move(source);



    EXPECT_TRUE(movedSlot.IsValid());

    EXPECT_EQ(movedSlot.GetExplicitValue(), 5);

    EXPECT_FALSE(source.IsValid());

}



TEST_F(JobserverSlotTest_22, GetExplicitValueReturnsCorrectValue_22) {

    uint8_t value = 3;

    Jobserver::Slot slot = Jobserver::Slot::CreateExplicit(value);



    EXPECT_EQ(slot.GetExplicitValue(), value);

}
