#include <gtest/gtest.h>

#include "jobserver.h"



using namespace testing;



class JobserverTest_169 : public ::testing::Test {

protected:

    Jobserver::Slot slot;

};



// Normal operation tests



TEST_F(JobserverTest_169, DefaultConstructorInitializesInvalidSlot_169) {

    EXPECT_FALSE(slot.IsValid());

}



TEST_F(JobserverTest_169, MoveConstructorTransfersValue_169) {

    auto explicit_slot = Jobserver::Slot::CreateExplicit(5);

    Jobserver::Slot moved_slot(std::move(explicit_slot));

    EXPECT_TRUE(moved_slot.IsValid());

    EXPECT_EQ(moved_slot.GetExplicitValue(), 5);

    EXPECT_FALSE(explicit_slot.IsValid());

}



TEST_F(JobserverTest_169, MoveAssignmentTransfersValue_169) {

    auto explicit_slot = Jobserver::Slot::CreateExplicit(3);

    slot = std::move(explicit_slot);

    EXPECT_TRUE(slot.IsValid());

    EXPECT_EQ(slot.GetExplicitValue(), 3);

    EXPECT_FALSE(explicit_slot.IsValid());

}



TEST_F(JobserverTest_169, CreateExplicitCreatesValidSlot_169) {

    auto explicit_slot = Jobserver::Slot::CreateExplicit(255);

    EXPECT_TRUE(explicit_slot.IsValid());

    EXPECT_EQ(explicit_slot.GetExplicitValue(), 255);

}



TEST_F(JobserverTest_169, CreateImplicitCreatesInvalidSlot_169) {

    auto implicit_slot = Jobserver::Slot::CreateImplicit();

    EXPECT_FALSE(implicit_slot.IsValid());

}



// Boundary conditions tests



TEST_F(JobserverTest_169, GetExplicitValueReturnsCorrectBoundaryValues_169) {

    auto min_value_slot = Jobserver::Slot::CreateExplicit(0);

    EXPECT_EQ(min_value_slot.GetExplicitValue(), 0);



    auto max_value_slot = Jobserver::Slot::CreateExplicit(255);

    EXPECT_EQ(max_value_slot.GetExplicitValue(), 255);

}



// Exceptional or error cases



TEST_F(JobserverTest_169, GetExplicitValueOnInvalidSlotThrowsOrReturnsZero_169) {

    EXPECT_EQ(slot.GetExplicitValue(), 0); // Assuming it returns zero for invalid slots

}



// Verification of external interactions (not applicable in this case)


