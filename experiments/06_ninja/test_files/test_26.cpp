#include <gtest/gtest.h>

#include "./TestProjects/ninja/src/jobserver.h"



class JobserverSlotTest_26 : public ::testing::Test {};



TEST_F(JobserverSlotTest_26, CreateExplicit_ValidValue_ReturnsValidSlot_26) {

    uint8_t value = 42;

    Jobserver::Slot slot = Jobserver::Slot::CreateExplicit(value);

    EXPECT_TRUE(slot.IsValid());

    EXPECT_TRUE(slot.IsExplicit());

    EXPECT_EQ(slot.GetExplicitValue(), value);

}



TEST_F(JobserverSlotTest_26, CreateExplicit_MaxValue_ReturnsValidSlot_26) {

    uint8_t value = 255;

    Jobserver::Slot slot = Jobserver::Slot::CreateExplicit(value);

    EXPECT_TRUE(slot.IsValid());

    EXPECT_TRUE(slot.IsExplicit());

    EXPECT_EQ(slot.GetExplicitValue(), value);

}



TEST_F(JobserverSlotTest_26, CreateExplicit_MinValue_ReturnsValidSlot_26) {

    uint8_t value = 0;

    Jobserver::Slot slot = Jobserver::Slot::CreateExplicit(value);

    EXPECT_TRUE(slot.IsValid());

    EXPECT_TRUE(slot.IsExplicit());

    EXPECT_EQ(slot.GetExplicitValue(), value);

}



TEST_F(JobserverSlotTest_26, CreateImplicit_ReturnsValidImplicitSlot_26) {

    Jobserver::Slot slot = Jobserver::Slot::CreateImplicit();

    EXPECT_TRUE(slot.IsValid());

    EXPECT_TRUE(slot.IsImplicit());

    EXPECT_FALSE(slot.IsExplicit());

}



TEST_F(JobserverSlotTest_26, DefaultConstructor_ReturnsInvalidSlot_26) {

    Jobserver::Slot slot;

    EXPECT_FALSE(slot.IsValid());

    EXPECT_FALSE(slot.IsImplicit());

    EXPECT_FALSE(slot.IsExplicit());

}



TEST_F(JobserverSlotTest_26, MoveConstructor_PreservesState_26) {

    uint8_t value = 42;

    Jobserver::Slot original = Jobserver::Slot::CreateExplicit(value);

    Jobserver::Slot moved = std::move(original);



    EXPECT_TRUE(moved.IsValid());

    EXPECT_TRUE(moved.IsExplicit());

    EXPECT_EQ(moved.GetExplicitValue(), value);

}



TEST_F(JobserverSlotTest_26, MoveAssignment_PreservesState_26) {

    uint8_t value = 42;

    Jobserver::Slot original = Jobserver::Slot::CreateExplicit(value);

    Jobserver::Slot moved;

    moved = std::move(original);



    EXPECT_TRUE(moved.IsValid());

    EXPECT_TRUE(moved.IsExplicit());

    EXPECT_EQ(moved.GetExplicitValue(), value);

}
