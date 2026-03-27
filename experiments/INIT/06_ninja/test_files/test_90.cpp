// File: ./TestProjects/ninja/tests/builder_set_jobserver_client_test_90.cc

#include "gtest/gtest.h"
#include "build.h"

#include <cstdint>
#include <memory>

// NOTE:
// These tests treat Builder as a black box and only verify observable behavior
// via its public interface and public data members. We do *not* assume or
// re-implement internal logic beyond standard unique_ptr move semantics.
//
// They assume the real project provides concrete definitions for State,
// BuildConfig, BuildLog, DepsLog, DiskInterface, and Status that can be
// default-constructed or otherwise adapted for testing.

// Helper to build a minimal Builder instance.
// Adjust construction as needed to match your actual types/constructors.
static Builder MakeTestBuilder_90() {
  static State state;          // assuming default constructible or static test instance
  static BuildConfig config;   // assuming default constructible
  static BuildLog build_log;   // assuming default constructible
  static DepsLog deps_log;     // assuming default constructible
  static DiskInterface disk;   // assuming default constructible
  static Status status;        // assuming default constructible

  // start_time_millis can be any value for this test
  int64_t start_time_millis = 0;
  return Builder(&state, config, &build_log, &deps_log, &disk, &status,
                 start_time_millis);
}

// Normal operation: non-null client is stored and ownership is transferred.
TEST(BuilderSetJobserverClientTest_90, StoresNonNullClientAndTransfersOwnership_90) {
  Builder builder = MakeTestBuilder_90();

  // Precondition: jobserver_ should be empty before we set it.
  EXPECT_EQ(nullptr, builder.jobserver_.get());

  // Use a dummy non-null pointer value to exercise move semantics
  // without depending on Jobserver::Client's actual constructor.
  auto client = std::unique_ptr<Jobserver::Client>(
      reinterpret_cast<Jobserver::Client*>(0x1));
  Jobserver::Client* raw_client = client.get();

  builder.SetJobserverClient(std::move(client));

  // After moving, Builder should now own the pointer.
  EXPECT_EQ(raw_client, builder.jobserver_.get());
  // Local unique_ptr should be empty after move.
  EXPECT_EQ(nullptr, client.get());

  // Avoid deleting a non-owned dummy pointer at the end of the test.
  builder.jobserver_.release();
}

// Boundary condition: SetJobserverClient accepts nullptr and leaves jobserver_ null.
TEST(BuilderSetJobserverClientTest_90, AcceptsNullptrClient_90) {
  Builder builder = MakeTestBuilder_90();

  // Ensure initial state is well-defined.
  builder.jobserver_.reset();  // explicitly clear if anything existed

  std::unique_ptr<Jobserver::Client> null_client;  // nullptr
  EXPECT_EQ(nullptr, null_client.get());

  builder.SetJobserverClient(std::move(null_client));

  // Builder should still have a null jobserver_ after setting nullptr.
  EXPECT_EQ(nullptr, builder.jobserver_.get());
}

// Normal operation / replacement behavior:
// Setting a new client replaces the previous one.
TEST(BuilderSetJobserverClientTest_90, ReplacesExistingClient_90) {
  Builder builder = MakeTestBuilder_90();

  // First client
  auto client1 = std::unique_ptr<Jobserver::Client>(
      reinterpret_cast<Jobserver::Client*>(0x1));
  Jobserver::Client* raw_client1 = client1.get();
  builder.SetJobserverClient(std::move(client1));

  EXPECT_EQ(raw_client1, builder.jobserver_.get());

  // Second client, should replace the first one in the Builder.
  auto client2 = std::unique_ptr<Jobserver::Client>(
      reinterpret_cast<Jobserver::Client*>(0x2));
  Jobserver::Client* raw_client2 = client2.get();
  builder.SetJobserverClient(std::move(client2));

  // Now Builder should point to the second client.
  EXPECT_EQ(raw_client2, builder.jobserver_.get());
  EXPECT_NE(raw_client1, builder.jobserver_.get());
  EXPECT_EQ(nullptr, client2.get());

  // Prevent the dummy pointer from being deleted.
  builder.jobserver_.release();
}
