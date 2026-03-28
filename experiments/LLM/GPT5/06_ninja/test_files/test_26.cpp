// File: jobserver_slot_test_26.cc

#include "jobserver.h"

#include "gtest/gtest.h"

#include <cstdint>
#include <utility>

// Basic construction / category tests.

TEST(JobserverSlotTest_26, DefaultConstructionIsInvalid_26) {
  Jobserver::Slot slot;

  EXPECT_FALSE(slot.IsValid());
  EXPECT_FALSE(slot.IsImplicit());
  EXPECT_FALSE(slot.IsExplicit());
}

TEST(JobserverSlotTest_26, CreateImplicitProducesValidImplicitSlot_26) {
  Jobserver::Slot slot = Jobserver::Slot::CreateImplicit();

  EXPECT_TRUE(slot.IsValid());
  EXPECT_TRUE(slot.IsImplicit());
  EXPECT_FALSE(slot.IsExplicit());
}

TEST(JobserverSlotTest_26, CreateExplicitProducesValidExplicitSlot_26) {
  Jobserver::Slot slot = Jobserver::Slot::CreateExplicit(10u);

  EXPECT_TRUE(slot.IsValid());
  EXPECT_FALSE(slot.IsImplicit());
  EXPECT_TRUE(slot.IsExplicit());
  EXPECT_EQ(10u, slot.GetExplicitValue());
}

// Boundary tests for explicit values (0 and 255).

TEST(JobserverSlotTest_26, CreateExplicitWithZeroValue_26) {
  Jobserver::Slot slot = Jobserver::Slot::CreateExplicit(static_cast<uint8_t>(0));

  EXPECT_TRUE(slot.IsValid());
  EXPECT_FALSE(slot.IsImplicit());
  EXPECT_TRUE(slot.IsExplicit());
  EXPECT_EQ(static_cast<uint8_t>(0), slot.GetExplicitValue());
}

TEST(JobserverSlotTest_26, CreateExplicitWithMaxUint8Value_26) {
  Jobserver::Slot slot =
      Jobserver::Slot::CreateExplicit(static_cast<uint8_t>(255));

  EXPECT_TRUE(slot.IsValid());
  EXPECT_FALSE(slot.IsImplicit());
  EXPECT_TRUE(slot.IsExplicit());
  EXPECT_EQ(static_cast<uint8_t>(255), slot.GetExplicitValue());
}

// Move-construction tests.

TEST(JobserverSlotTest_26, MoveConstructFromExplicitTransfersValue_26) {
  Jobserver::Slot src = Jobserver::Slot::CreateExplicit(42u);

  Jobserver::Slot dst(std::move(src));

  EXPECT_FALSE(src.IsValid());
  EXPECT_TRUE(dst.IsValid());
  EXPECT_TRUE(dst.IsExplicit());
  EXPECT_EQ(42u, dst.GetExplicitValue());
}

TEST(JobserverSlotTest_26, MoveConstructFromImplicitTransfersCategory_26) {
  Jobserver::Slot src = Jobserver::Slot::CreateImplicit();

  Jobserver::Slot dst(std::move(src));

  EXPECT_FALSE(src.IsValid());
  EXPECT_TRUE(dst.IsValid());
  EXPECT_TRUE(dst.IsImplicit());
  EXPECT_FALSE(dst.IsExplicit());
}

// Move-assignment tests.

TEST(JobserverSlotTest_26, MoveAssignExplicitTransfersValueAndInvalidatesSource_26) {
  Jobserver::Slot src = Jobserver::Slot::CreateExplicit(10u);
  Jobserver::Slot dst = Jobserver::Slot::CreateExplicit(99u);

  dst = std::move(src);

  EXPECT_FALSE(src.IsValid());
  EXPECT_TRUE(dst.IsValid());
  EXPECT_TRUE(dst.IsExplicit());
  EXPECT_EQ(10u, dst.GetExplicitValue());
}

TEST(JobserverSlotTest_26, MoveAssignImplicitTransfersCategoryAndInvalidatesSource_26) {
  Jobserver::Slot src = Jobserver::Slot::CreateImplicit();
  Jobserver::Slot dst;  // starts invalid

  dst = std::move(src);

  EXPECT_FALSE(src.IsValid());
  EXPECT_TRUE(dst.IsValid());
  EXPECT_TRUE(dst.IsImplicit());
  EXPECT_FALSE(dst.IsExplicit());
}

TEST(JobserverSlotTest_26, MoveAssignFromInvalidMakesDestinationInvalid_26) {
  Jobserver::Slot src;  // invalid
  Jobserver::Slot dst = Jobserver::Slot::CreateExplicit(7u);

  dst = std::move(src);

  EXPECT_FALSE(src.IsValid());
  EXPECT_FALSE(dst.IsValid());
  EXPECT_FALSE(dst.IsImplicit());
  EXPECT_FALSE(dst.IsExplicit());
}
