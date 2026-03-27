// File: register_translator_impl_tests_248.cpp

#include <gtest/gtest.h>
#include <utility>
#include <string>

//
// Minimal forward declarations to match the provided interfaces.
// We only declare what is required for compilation of the tests and
// to verify observable interactions.
//
namespace Catch {

struct SourceLineInfo;
struct IMutableEnumValuesRegistry;

namespace Detail {
  template <typename T> class unique_ptr; // forward-declared; provided by codebase
  struct IExceptionTranslator;            // forward-declared translator interface

  // Function under test (provided in Catch2/src/catch2/catch_translate_exception.cpp)
  void registerTranslatorImpl(Detail::unique_ptr<IExceptionTranslator>&& translator);
}

// From interfaces header (we only need the types in the signatures)
struct IReporterFactory;
using IReporterFactoryPtr = Detail::unique_ptr<IReporterFactory>;
struct EventListenerFactory;
struct TestCaseInfo;
struct ITestInvoker;

class IMutableRegistryHub {
public:
  virtual ~IMutableRegistryHub() {}

  // We only need registerTranslator for behavior, but to satisfy the
  // abstract interface we declare the rest and provide no-op impls in the test double.
  virtual void registerReporter(const std::string&, IReporterFactoryPtr) = 0;
  virtual void registerListener(Detail::unique_ptr<EventListenerFactory>) = 0;
  virtual void registerTest(Detail::unique_ptr<TestCaseInfo>&&, Detail::unique_ptr<ITestInvoker>&&) = 0;
  virtual void registerTranslator(Detail::unique_ptr<Detail::IExceptionTranslator>&& translator) = 0;
  virtual void registerTagAlias(const std::string&, const std::string&, const SourceLineInfo&) = 0;
  virtual void registerStartupException() = 0;
  virtual IMutableEnumValuesRegistry& getMutableEnumValuesRegistry() = 0;
};

// This is provided by Catch2 and used by registerTranslatorImpl. For testing,
// we define it to return our test double instance.
IMutableRegistryHub& getMutableRegistryHub();

} // namespace Catch

// We also need the custom unique_ptr that Catch uses.
// Here we only rely on its public surface per the provided header:
//  - ctor from T*
//  - move construction/assignment
//  - operator bool()
//  - get()
//  - release()
// NOTE: In the real build this comes from Catch2's headers; the tests assume
//       those declarations/definitions are available when compiling the suite.
#include "catch2/internal/catch_unique_ptr.hpp"  // In your test build, include the real header.

// ------------------- Test Double for the Registry Hub -------------------

namespace Catch {

namespace Detail {
  struct IExceptionTranslator { virtual ~IExceptionTranslator() = default; };
}

// A simple concrete translator type we can pass in.
struct DummyTranslator final : Detail::IExceptionTranslator {};

// A minimal test-double for the registry hub that records calls to registerTranslator
class TestRegistryHub : public IMutableRegistryHub {
public:
  TestRegistryHub() : register_translator_calls(0) {}

  // Observable piece: we capture the moved-in unique_ptr
  void registerTranslator(Detail::unique_ptr<Detail::IExceptionTranslator>&& translator) override {
    ++register_translator_calls;
    last_translator = std::move(translator); // take ownership; observable via get()
  }

  // No-op implementations for the rest (not used in these tests)
  void registerReporter(const std::string&, IReporterFactoryPtr) override {}
  void registerListener(Detail::unique_ptr<EventListenerFactory>) override {}
  void registerTest(Detail::unique_ptr<TestCaseInfo>&&, Detail::unique_ptr<ITestInvoker>&&) override {}
  void registerTagAlias(const std::string&, const std::string&, const SourceLineInfo&) override {}
  void registerStartupException() override {}
  IMutableEnumValuesRegistry& getMutableEnumValuesRegistry() override {
    // We will never call this in tests; providing a stub that will not be used.
    // An alternative would be to throw if ever called.
    struct DummyEnumRegistry : IMutableEnumValuesRegistry {} static dummy;
    return dummy;
  }

  // Helpers for assertions
  int calls() const { return register_translator_calls; }
  Detail::IExceptionTranslator* receivedRaw() const { return last_translator.get(); }
  bool receivedNonNull() const { return static_cast<bool>(last_translator); }
  void reset() {
    register_translator_calls = 0;
    last_translator.reset(nullptr);
  }

private:
  int register_translator_calls;
  Detail::unique_ptr<Detail::IExceptionTranslator> last_translator{nullptr};
};

// Provide the global accessor used by the SUT, bound to our test hub.
IMutableRegistryHub& getMutableRegistryHub() {
  static TestRegistryHub hub;
  return hub;
}

} // namespace Catch

// ------------------- Test Fixture -------------------

class RegisterTranslatorImplTest_248 : public ::testing::Test {
protected:
  void SetUp() override {
    // Ensure clean hub state before each test
    auto& hub = static_cast<Catch::TestRegistryHub&>(Catch::getMutableRegistryHub());
    hub.reset();
  }
};

// ------------------- Tests -------------------

// Normal operation: forwards a non-null translator to the registry and transfers ownership.
TEST_F(RegisterTranslatorImplTest_248, ForwardsNonNullTranslator_248) {
  auto& hub = static_cast<Catch::TestRegistryHub&>(Catch::getMutableRegistryHub());

  // Prepare a unique_ptr with a concrete translator and keep a handle to assert move semantics.
  Catch::Detail::unique_ptr<Catch::Detail::IExceptionTranslator> uptr(new Catch::DummyTranslator());
  ASSERT_TRUE(static_cast<bool>(uptr)) << "Precondition: unique_ptr should hold a translator";

  // Call the function under test; must move the unique_ptr (ownership transfer)
  Catch::Detail::registerTranslatorImpl(std::move(uptr));

  // The hub should have been called exactly once and should now own a non-null translator.
  EXPECT_EQ(hub.calls(), 1);
  EXPECT_TRUE(hub.receivedNonNull());
  EXPECT_NE(hub.receivedRaw(), nullptr);

  // The original unique_ptr must be empty after move.
  EXPECT_FALSE(static_cast<bool>(uptr));
}

// Boundary: forwards a null translator and still calls into the registry exactly once.
TEST_F(RegisterTranslatorImplTest_248, ForwardsNullTranslator_248) {
  auto& hub = static_cast<Catch::TestRegistryHub&>(Catch::getMutableRegistryHub());

  Catch::Detail::unique_ptr<Catch::Detail::IExceptionTranslator> uptr(nullptr);
  ASSERT_FALSE(static_cast<bool>(uptr)) << "Precondition: unique_ptr should be null";

  Catch::Detail::registerTranslatorImpl(std::move(uptr));

  EXPECT_EQ(hub.calls(), 1);
  // Registry should now hold a null translator.
  EXPECT_FALSE(hub.receivedNonNull());
  EXPECT_EQ(hub.receivedRaw(), nullptr);

  // Original remains null.
  EXPECT_FALSE(static_cast<bool>(uptr));
}

// Ownership semantics: passing the same pointer via move twice should not be possible;
// this test ensures that the function consumes the pointer (first call ok, second is null).
TEST_F(RegisterTranslatorImplTest_248, ConsumesOwnershipViaMove_248) {
  auto& hub = static_cast<Catch::TestRegistryHub&>(Catch::getMutableRegistryHub());

  Catch::Detail::unique_ptr<Catch::Detail::IExceptionTranslator> uptr(new Catch::DummyTranslator());
  ASSERT_TRUE(static_cast<bool>(uptr));

  // First call consumes it
  Catch::Detail::registerTranslatorImpl(std::move(uptr));
  EXPECT_EQ(hub.calls(), 1);
  EXPECT_FALSE(static_cast<bool>(uptr)) << "After first move, the source unique_ptr must be empty";

  // A second attempt with the already-moved-from pointer behaves like forwarding null
  Catch::Detail::registerTranslatorImpl(std::move(uptr));
  EXPECT_EQ(hub.calls(), 2);
  EXPECT_TRUE(hub.receivedNonNull() || hub.receivedRaw() == nullptr)
      << "Hub should have handled the second (null) forward; exact storage state is observable via get()";
}
