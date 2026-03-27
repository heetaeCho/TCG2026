#include "jobserver.h"

#include <gtest/gtest.h>

// Tests for Jobserver::Client (TEST_ID = 29)
//
// These tests treat Jobserver::Client as a black box and only rely on its
// public interface and the observable behavior of its default virtual methods.

namespace {

class JobserverClientTest_29 : public ::testing::Test {
 protected:
  // Concrete testable subclass, exposing the protected constructor of
  // Jobserver::Client without changing any behavior.
  class TestClient : public Jobserver::Client {
   public:
    TestClient() = default;
    ~TestClient() override = default;
  };
};

// Verifies that the default implementation of TryAcquire returns a Slot
// that is equal to a default-constructed Slot.
TEST_F(JobserverClientTest_29, TryAcquireReturnsDefaultConstructedSlot_29) {
  TestClient client;

  Slot acquired = client.TryAcquire();

  // We only rely on the fact that TryAcquire returns *some* Slot value and
  // compare it against a default-constructed Slot as exposed by the interface.
  Slot expected;
  EXPECT_EQ(acquired, expected);
}

// Verifies that Release accepts a default-constructed Slot and completes
// without any observable failure (e.g., crash or exception).
TEST_F(JobserverClientTest_29, ReleaseAcceptsDefaultConstructedSlot_29) {
  TestClient client;
  Slot slot;

  // The test simply ensures that calling Release with a Slot obtained from the
  // interface is allowed and does not result in errors.
  client.Release(slot);

  SUCCEED();  // If we get here, Release behaved acceptably from the interface POV.
}

// Verifies that the destructor of Jobserver::Client is virtual by ensuring
// deletion through a base-class pointer is safe and well-defined.
TEST_F(JobserverClientTest_29, DeletionThroughBasePointerIsSafe_29) {
  Jobserver::Client* client = new TestClient();

  // Deleting through a base pointer must be safe due to the virtual destructor.
  delete client;

  SUCCEED();  // Reaching here means no UB was observed in this context.
}

}  // namespace
