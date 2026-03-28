#include <gtest/gtest.h>

#include "jobserver.h"



using namespace testing;



class JobserverSlotTest_24 : public ::testing::Test {

protected:

    Jobserver::Slot slot;

};



TEST_F(JobserverSlotTest_24, DefaultConstructorIsImplicit_24) {

    EXPECT_TRUE(slot.IsImplicit());

}



TEST_F(JobserverSlotTest_24, CreateExplicitSetsValueCorrectly_24) {

    uint8_t value = 5;

    Jobserver::Slot explicitSlot = Jobserver::Slot::CreateExplicit(value);

    EXPECT_EQ(explicitSlot.GetExplicitValue(), value);

}



TEST_F(JobserverSlotTest_24, CreateImplicitIsImplicit_24) {

    Jobserver::Slot implicitSlot = Jobserver::Slot::CreateImplicit();

    EXPECT_TRUE(implicitSlot.IsImplicit());

}



TEST_F(JobserverSlotTest_24, MoveConstructorPreservesExplicitValue_24) {

    uint8_t value = 5;

    Jobserver::Slot originalSlot = Jobserver::Slot::CreateExplicit(value);

    Jobserver::Slot movedSlot = std::move(originalSlot);

    EXPECT_EQ(movedSlot.GetExplicitValue(), value);

}



TEST_F(JobserverSlotTest_24, MoveAssignmentPreservesExplicitValue_24) {

    uint8_t value = 5;

    Jobserver::Slot originalSlot = Jobserver::Slot::CreateExplicit(value);

    Jobserver::Slot movedSlot;

    movedSlot = std::move(originalSlot);

    EXPECT_EQ(movedSlot.GetExplicitValue(), value);

}



TEST_F(JobserverSlotTest_24, IsValidReturnsTrueForExplicitSlot_24) {

    uint8_t value = 5;

    Jobserver::Slot slot = Jobserver::Slot::CreateExplicit(value);

    EXPECT_TRUE(slot.IsValid());

}



TEST_F(JobserverSlotTest_24, IsValidReturnsFalseForImplicitSlot_24) {

    Jobserver::Slot slot = Jobserver::Slot::CreateImplicit();

    EXPECT_FALSE(slot.IsValid());

}
