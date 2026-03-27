#include <gtest/gtest.h>

#include "jobserver.h"



class JobserverSlotTest : public ::testing::Test {

protected:

    Jobserver::Slot slot;

};



TEST_F(JobserverSlotTest_27, DefaultConstructorCreatesInvalidSlot_27) {

    EXPECT_FALSE(slot.IsValid());

}



TEST_F(JobserverSlotTest_27, CreateImplicitCreatesValidImplicitSlot_27) {

    auto implicit_slot = Jobserver::Slot::CreateImplicit();

    EXPECT_TRUE(implicit_slot.IsValid());

    EXPECT_TRUE(implicit_slot.IsImplicit());

    EXPECT_FALSE(implicit_slot.IsExplicit());

}



TEST_F(JobserverSlotTest_27, MoveConstructorPreservesValidity_27) {

    auto original_slot = Jobserver::Slot::CreateImplicit();

    bool is_valid_before_move = original_slot.IsValid();

    Jobserver::Slot moved_slot(std::move(original_slot));

    EXPECT_EQ(is_valid_before_move, moved_slot.IsValid());

}



TEST_F(JobserverSlotTest_27, MoveAssignmentPreservesValidity_27) {

    auto original_slot = Jobserver::Slot::CreateImplicit();

    bool is_valid_before_move = original_slot.IsValid();

    Jobserver::Slot target_slot;

    target_slot = std::move(original_slot);

    EXPECT_EQ(is_valid_before_move, target_slot.IsValid());

}



TEST_F(JobserverSlotTest_27, CreateExplicitCreatesValidExplicitSlot_27) {

    uint8_t value = 5;

    auto explicit_slot = Jobserver::Slot::CreateExplicit(value);

    EXPECT_TRUE(explicit_slot.IsValid());

    EXPECT_FALSE(explicit_slot.IsImplicit());

    EXPECT_TRUE(explicit_slot.IsExplicit());

    EXPECT_EQ(explicit_slot.GetExplicitValue(), value);

}



TEST_F(JobserverSlotTest_27, InvalidSlotIsNeitherImplicitNorExplicit_27) {

    EXPECT_FALSE(slot.IsImplicit());

    EXPECT_FALSE(slot.IsExplicit());

}
