// File: test_testregistry_registerTest_1016.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Catch2 — keep includes minimal and rely on public interfaces only.
#include <catch2/internal/catch_test_case_registry_impl.hpp>  // TestRegistry decl (public funcs)
#include <catch2/catch_test_case_info.hpp>                    // TestCaseInfo
#include <catch2/internal/catch_unique_ptr.hpp>               // Detail::unique_ptr
#include <catch2/interfaces/catch_interfaces_testcase.hpp>    // ITestInvoker

using ::testing::_;
using ::testing::Exactly;
using ::testing::IsEmpty;
using ::testing::SizeIs;
using ::testing::UnorderedElementsAreArray;

namespace {

class MockInvoker : public Catch::ITestInvoker {
public:
    MOCK_METHOD(void, invoke, (), (const, override));
};

// Minimal helper to construct a TestCaseInfo for registration.
// If your TestCaseInfo requires arguments, adapt this to your ctor.
static Catch::Detail::unique_ptr<Catch::TestCaseInfo> MakeTestCaseInfo(const char* name = "T") {
#if defined(CATCH_VERSION_MAJOR)
// If you know the exact ctor in your tree, prefer using it here.
// Fallback to default construction if available.
    return Catch::Detail::unique_ptr<Catch::TestCaseInfo>(new Catch::TestCaseInfo());
#else
    return Catch::Detail::unique_ptr<Catch::TestCaseInfo>(new Catch::TestCaseInfo());
#endif
}

static Catch::Detail::unique_ptr<Catch::ITestInvoker> MakeMockInvoker(MockInvoker*& outRaw) {
    auto p = std::make_unique<MockInvoker>();
    outRaw = p.get();
    // Wrap the raw MockInvoker in Catch::Detail::unique_ptr<ITestInvoker>
    return Catch::Detail::unique_ptr<Catch::ITestInvoker>(p.release());
}

class TestRegistry_RegisterTest_1016 : public ::testing::Test {
protected:
    Catch::TestRegistry registry;
};

} // namespace

// --- Tests ---

// Verifies that registering a single test updates the public views:
// - getAllInfos() contains exactly the pointer passed in.
// - getAllTests() size reflects the registration.
// - registerTest does NOT invoke the invoker by itself (no external interaction).
TEST_F(TestRegistry_RegisterTest_1016, RegisterSingle_AddsInfoAndHandle_DoesNotInvoke_1016) {
    // Arrange
    auto info = MakeTestCaseInfo("A");
    Catch::TestCaseInfo* rawInfo = info.get();

    MockInvoker* rawMock = nullptr;
    auto inv = MakeMockInvoker(rawMock);

    EXPECT_CALL(*rawMock, invoke()).Times(0); // registerTest should not invoke

    // Act
    registry.registerTest(Catch::Detail::unique_ptr<Catch::TestCaseInfo>(CATCH_MOVE(info)),
                          Catch::Detail::unique_ptr<Catch::ITestInvoker>(CATCH_MOVE(inv)));

    // Assert (observable via public getters only)
    const auto& infos = registry.getAllInfos();
    EXPECT_THAT(infos, SizeIs(1));
    EXPECT_EQ(infos[0], rawInfo);

    const auto& tests = registry.getAllTests();
    EXPECT_THAT(tests, SizeIs(1));
}

// Verifies that multiple registrations are all reflected via public getters.
// We also check that all pointers we passed in are present among getAllInfos().
TEST_F(TestRegistry_RegisterTest_1016, RegisterMultiple_AllAppearInInfosAndTests_1016) {
    // Arrange
    auto info1 = MakeTestCaseInfo("A");
    auto info2 = MakeTestCaseInfo("B");
    auto info3 = MakeTestCaseInfo("C");

    Catch::TestCaseInfo* p1 = info1.get();
    Catch::TestCaseInfo* p2 = info2.get();
    Catch::TestCaseInfo* p3 = info3.get();

    MockInvoker *m1 = nullptr, *m2 = nullptr, *m3 = nullptr;
    auto inv1 = MakeMockInvoker(m1);
    auto inv2 = MakeMockInvoker(m2);
    auto inv3 = MakeMockInvoker(m3);

    EXPECT_CALL(*m1, invoke()).Times(0);
    EXPECT_CALL(*m2, invoke()).Times(0);
    EXPECT_CALL(*m3, invoke()).Times(0);

    // Act
    registry.registerTest(Catch::Detail::unique_ptr<Catch::TestCaseInfo>(CATCH_MOVE(info1)),
                          Catch::Detail::unique_ptr<Catch::ITestInvoker>(CATCH_MOVE(inv1)));
    registry.registerTest(Catch::Detail::unique_ptr<Catch::TestCaseInfo>(CATCH_MOVE(info2)),
                          Catch::Detail::unique_ptr<Catch::ITestInvoker>(CATCH_MOVE(inv2)));
    registry.registerTest(Catch::Detail::unique_ptr<Catch::TestCaseInfo>(CATCH_MOVE(info3)),
                          Catch::Detail::unique_ptr<Catch::ITestInvoker>(CATCH_MOVE(inv3)));

    // Assert
    const auto& infos = registry.getAllInfos();
    ASSERT_THAT(infos, SizeIs(3));
    // Because only the interface guarantees "all infos", verify set membership (not internal order).
    // If your implementation guarantees insertion order via the interface, you can make this check ordered.
    std::vector<Catch::TestCaseInfo*> expected{p1, p2, p3};
    EXPECT_THAT(std::vector<Catch::TestCaseInfo*>{infos.begin(), infos.end()},
                UnorderedElementsAreArray(expected));

    const auto& tests = registry.getAllTests();
    EXPECT_THAT(tests, SizeIs(3));
}

// Boundary-ish observable behavior: registering then querying getters immediately
// should be safe and not require any sorting/config. We also check that prior to
// registration, the getters are empty (purely observable via the interface).
TEST_F(TestRegistry_RegisterTest_1016, GettersEmptyBeforeRegistration_PopulatedAfter_1016) {
    // Before
    EXPECT_THAT(registry.getAllInfos(), IsEmpty());
    EXPECT_THAT(registry.getAllTests(), IsEmpty());

    // Register one
    auto info = MakeTestCaseInfo("Solo");
    MockInvoker* raw = nullptr;
    auto inv = MakeMockInvoker(raw);
    EXPECT_CALL(*raw, invoke()).Times(0);

    registry.registerTest(Catch::Detail::unique_ptr<Catch::TestCaseInfo>(CATCH_MOVE(info)),
                          Catch::Detail::unique_ptr<Catch::ITestInvoker>(CATCH_MOVE(inv)));

    // After
    EXPECT_THAT(registry.getAllInfos(), SizeIs(1));
    EXPECT_THAT(registry.getAllTests(), SizeIs(1));
}
