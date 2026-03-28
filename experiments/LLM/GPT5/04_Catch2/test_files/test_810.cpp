// File: tests/registerReporterImpl_tests_810.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <stdexcept>
#include <utility>

// ---- Minimal scaffolding to compile the unit under test -----------------
// We only declare the *interfaces* that the implementation touches.
// No internal logic is re-implemented.

#ifndef CATCH_TRY
#define CATCH_TRY try
#endif
#ifndef CATCH_CATCH_ALL
#define CATCH_CATCH_ALL catch(...)
#endif
#ifndef CATCH_MOVE
#define CATCH_MOVE(x) std::move(x)
#endif

namespace Catch {
    namespace Detail {
        // Minimal unique_ptr interface sufficient for constructing/moving in tests.
        template <typename T>
        class unique_ptr {
            T* m_ptr;
        public:
            constexpr unique_ptr(std::nullptr_t = nullptr) : m_ptr(nullptr) {}
            explicit constexpr unique_ptr(T* ptr) : m_ptr(ptr) {}
            unique_ptr(unique_ptr const&) = delete;
            unique_ptr& operator=(unique_ptr const&) = delete;
            unique_ptr(unique_ptr&& rhs) noexcept : m_ptr(rhs.m_ptr) { rhs.m_ptr = nullptr; }
            unique_ptr& operator=(unique_ptr&& rhs) noexcept {
                if (this != &rhs) { reset(); m_ptr = rhs.m_ptr; rhs.m_ptr = nullptr; }
                return *this;
            }
            ~unique_ptr() { reset(); }
            T* get() const { return m_ptr; }
            void reset(T* ptr = nullptr) { if (m_ptr) delete m_ptr; m_ptr = ptr; }
            T* release() { T* p = m_ptr; m_ptr = nullptr; return p; }
            explicit operator bool() const { return m_ptr != nullptr; }
            T& operator*() { return *m_ptr; }
            T* operator->() { return m_ptr; }
        };
    } // namespace Detail

    // Forward-declare IReporterFactory and alias pointer type used in the registrar.
    struct IReporterFactory;
    using IReporterFactoryPtr = Detail::unique_ptr<IReporterFactory>;

    // Minimal IMutableRegistryHub interface with only the members the unit touches.
    class IMutableRegistryHub {
    public:
        virtual ~IMutableRegistryHub() = default;
        virtual void registerReporter(const std::string& name, IReporterFactoryPtr factory) = 0;
        virtual void registerStartupException() = 0;
    };

    // Test shim: provide the accessor used by the implementation so we can inject our mock.
    inline IMutableRegistryHub*& testHubStorage() {
        static IMutableRegistryHub* hub = nullptr;
        return hub;
    }
    inline IMutableRegistryHub& getMutableRegistryHub() {
        return *testHubStorage();
    }
} // namespace Catch

// ---- Include the unit under test (registerReporterImpl) -----------------
namespace Catch { namespace Detail {
    // Original function (copied verbatim from prompt)
    inline void registerReporterImpl( std::string const& name, IReporterFactoryPtr reporterPtr ) {
        CATCH_TRY {
            getMutableRegistryHub().registerReporter( name, CATCH_MOVE( reporterPtr ) );
        } CATCH_CATCH_ALL {
            getMutableRegistryHub().registerStartupException();
        }
    }
} } // namespace Catch::Detail

// ---- Test doubles -------------------------------------------------------
namespace Catch {
    // Dummy reporter factory concrete type (opaque to the code under test)
    struct IReporterFactory {
        virtual ~IReporterFactory() = default;
    };
}

class MockMutableRegistryHub : public Catch::IMutableRegistryHub {
public:
    // Note: Move-only arg is supported; use _ matcher or custom actions if needed.
    MOCK_METHOD(void, registerReporter,
                (const std::string& name, Catch::IReporterFactoryPtr factory), (override));
    MOCK_METHOD(void, registerStartupException, (), (override));
};

// ---- Test Fixture -------------------------------------------------------
class RegisterReporterImplTest_810 : public ::testing::Test {
protected:
    MockMutableRegistryHub mockHub;

    void SetUp() override {
        Catch::testHubStorage() = &mockHub;
    }
    void TearDown() override {
        Catch::testHubStorage() = nullptr;
    }
};

// ---- Tests --------------------------------------------------------------

// Normal operation: forwards name and transfers ownership to registry.
TEST_F(RegisterReporterImplTest_810, ForwardsNameAndMovesFactory_810) {
    using ::testing::_;
    using ::testing::StrEq;

    // Prepare a non-null factory and keep a handle to verify it is moved-from.
    auto factory = Catch::IReporterFactoryPtr(new Catch::IReporterFactory{});
    ASSERT_TRUE(factory) << "Precondition: factory should be non-null before call";

    EXPECT_CALL(mockHub, registerReporter(StrEq("console"), _))
        .Times(1);

    // Act
    Catch::Detail::registerReporterImpl("console", CATCH_MOVE(factory));

    // Assert: caller's unique_ptr should be moved-from (null).
    EXPECT_FALSE(factory) << "Factory should be moved-from after call";
}

// Boundary: empty reporter name still forwarded without error.
TEST_F(RegisterReporterImplTest_810, AllowsEmptyName_810) {
    using ::testing::_;
    using ::testing::StrEq;

    auto factory = Catch::IReporterFactoryPtr(new Catch::IReporterFactory{});

    EXPECT_CALL(mockHub, registerReporter(StrEq(""), _)).Times(1);

    Catch::Detail::registerReporterImpl("", CATCH_MOVE(factory));

    EXPECT_FALSE(factory); // moved-from
}

// Boundary: nullptr factory is forwarded (no crash), name is preserved.
TEST_F(RegisterReporterImplTest_810, AllowsNullFactory_810) {
    using ::testing::_;
    using ::testing::StrEq;

    Catch::IReporterFactoryPtr nullFactory(nullptr);

    EXPECT_CALL(mockHub, registerReporter(StrEq("xml"), _)).Times(1);

    Catch::Detail::registerReporterImpl("xml", CATCH_MOVE(nullFactory));

    EXPECT_FALSE(nullFactory); // remains null / moved-from
}

// Exceptional path: if registry throws, implementation swallows and reports startup exception.
TEST_F(RegisterReporterImplTest_810, ReportsStartupExceptionOnThrow_810) {
    using ::testing::_;
    using ::testing::StrEq;
    using ::testing::Invoke;

    auto factory = Catch::IReporterFactoryPtr(new Catch::IReporterFactory{});

    // Make registerReporter throw
    EXPECT_CALL(mockHub, registerReporter(StrEq("fancy"), _))
        .WillOnce(Invoke([](const std::string&, Catch::IReporterFactoryPtr) {
            throw std::runtime_error("simulate failure");
        }));
    EXPECT_CALL(mockHub, registerStartupException())
        .Times(1);

    // Act + Assert: no exception should escape
    EXPECT_NO_THROW(Catch::Detail::registerReporterImpl("fancy", CATCH_MOVE(factory)));

    // The argument was moved into the call site; the caller's pointer should be moved-from.
    EXPECT_FALSE(factory);
}
