#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "jobserver.h"



using namespace testing;



// Test fixture for Jobserver::Slot

class SlotTest_25 : public ::testing::Test {

protected:

    Jobserver::Slot slot;

};



TEST_F(SlotTest_25, DefaultConstructorInvalid_25) {

    EXPECT_FALSE(slot.IsValid());

}



TEST_F(SlotTest_25, MoveConstructorValid_25) {

    auto explicitSlot = Jobserver::Slot::CreateExplicit(1);

    Jobserver::Slot movedSlot(std::move(explicitSlot));

    EXPECT_TRUE(movedSlot.IsValid());

}



TEST_F(SlotTest_25, CreateExplicitValid_25) {

    auto slot = Jobserver::Slot::CreateExplicit(1);

    EXPECT_TRUE(slot.IsValid());

}



TEST_F(SlotTest_25, CreateImplicitValid_25) {

    auto slot = Jobserver::Slot::CreateImplicit();

    EXPECT_TRUE(slot.IsValid());

}



TEST_F(SlotTest_25, IsExplicitTrueWhenExplicit_25) {

    auto slot = Jobserver::Slot::CreateExplicit(1);

    EXPECT_TRUE(slot.IsExplicit());

}



TEST_F(SlotTest_25, IsExplicitFalseWhenImplicit_25) {

    auto slot = Jobserver::Slot::CreateImplicit();

    EXPECT_FALSE(slot.IsExplicit());

}



TEST_F(SlotTest_25, IsImplicitTrueWhenImplicit_25) {

    auto slot = Jobserver::Slot::CreateImplicit();

    EXPECT_TRUE(slot.IsImplicit());

}



TEST_F(SlotTest_25, IsImplicitFalseWhenExplicit_25) {

    auto slot = Jobserver::Slot::CreateExplicit(1);

    EXPECT_FALSE(slot.IsImplicit());

}
