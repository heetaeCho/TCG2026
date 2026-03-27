// File: create_generator_tracker_test_355.cpp
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <string>
#include <cstring>

using ::testing::_;
using ::testing::Truly;

// ---- Minimal public-facing stubs for dependencies we interact with ----
namespace Catch {

class StringRef {
public:
    constexpr StringRef() noexcept : m_data(""), m_size(0) {}
    explicit StringRef(const char* s) : m_data(s ? s : ""), m_size(s ? std::strlen(s) : 0) {}
    const char* data() const noexcept { return m_data; }
    size_t size() const noexcept { return m_size; }
private:
    const char* m_data;
    size_t m_size;
};

struct SourceLineInfo {
    const char* file;
    std::size_t line;
    constexpr SourceLineInfo(const char* f, std::size_t l) noexcept : file(f), line(l) {}
};

struct IGeneratorTracker {};

namespace Generators {
struct GeneratorBase {};
using GeneratorBasePtr = std::unique_ptr<GeneratorBase>;
} // namespace Generators

class IResultCapture {
public:
    virtual ~IResultCapture() = default;
    virtual IGeneratorTracker* createGeneratorTracker(
        StringRef generatorName,
        SourceLineInfo lineInfo,
        Generators::GeneratorBasePtr&& generator) = 0;
};

IResultCapture& getResultCapture(); // defined below
} // namespace Catch

#ifndef CATCH_MOVE
#define CATCH_MOVE(x) std::move(x)
#endif

// ---- Mock for IResultCapture & global accessor wiring ----
class MockResultCapture : public Catch::IResultCapture {
public:
    MOCK_METHOD(Catch::IGeneratorTracker*, createGeneratorTracker,
                (Catch::StringRef, Catch::SourceLineInfo, Catch::Generators::GeneratorBasePtr&&),
                (override));
};

static MockResultCapture* g_mock_capture = nullptr;

namespace Catch {
IResultCapture& getResultCapture() {
    return *g_mock_capture;
}
} // namespace Catch

// ---- Include the code under test ----
#include "Catch2/src/catch2/generators/catch_generators.cpp"

// ---- Test fixture ----
class CreateGeneratorTrackerTest_355 : public ::testing::Test {
protected:
    MockResultCapture mock_;
    void SetUp() override { g_mock_capture = &mock_; }
    void TearDown() override { g_mock_capture = nullptr; }
    static Catch::Generators::GeneratorBasePtr makeGen() {
        return std::make_unique<Catch::Generators::GeneratorBase>();
    }
};

// ---- Tests ----

TEST_F(CreateGeneratorTrackerTest_355, ForwardsArgsAndReturnsValue_355) {
    Catch::IGeneratorTracker tracker; // dummy return object

    EXPECT_CALL(
        mock_,
        createGeneratorTracker(
            Truly([](const Catch::StringRef& s) {
                return std::string(s.data(), s.size()) == "my_generator";
            }),
            Truly([](const Catch::SourceLineInfo& li) {
                return std::string(li.file) == "file.cpp" && li.line == 123u;
            }),
            _))
        .WillOnce([&](Catch::StringRef, Catch::SourceLineInfo,
                      Catch::Generators::GeneratorBasePtr&& gen) {
            // The rvalue should still own the object inside the mock invocation
            EXPECT_NE(gen.get(), nullptr);
            return &tracker;
        });

    auto gen = makeGen();
    auto* ret = Catch::Generators::createGeneratorTracker(
        Catch::StringRef("my_generator"),
        Catch::SourceLineInfo("file.cpp", 123),
        std::move(gen));

    EXPECT_EQ(ret, &tracker);
    // After move, caller's pointer should be empty
    EXPECT_EQ(gen.get(), nullptr);
}

TEST_F(CreateGeneratorTrackerTest_355, AcceptsEmptyNameAndZeroLine_355) {
    Catch::IGeneratorTracker tracker;

    EXPECT_CALL(
        mock_,
        createGeneratorTracker(
            Truly([](const Catch::StringRef& s) { return s.size() == 0u; }),
            Truly([](const Catch::SourceLineInfo& li) {
                return std::string(li.file) == "" && li.line == 0u;
            }),
            _))
        .WillOnce([&](Catch::StringRef, Catch::SourceLineInfo,
                      Catch::Generators::GeneratorBasePtr&& gen) {
            EXPECT_NE(gen.get(), nullptr);
            return &tracker;
        });

    auto gen = makeGen();
    auto* ret = Catch::Generators::createGeneratorTracker(
        Catch::StringRef(), Catch::SourceLineInfo("", 0), std::move(gen));

    EXPECT_EQ(ret, &tracker);
    EXPECT_EQ(gen.get(), nullptr);
}

TEST_F(CreateGeneratorTrackerTest_355, ReturnsNullWhenUnderlyingReturnsNull_355) {
    EXPECT_CALL(mock_, createGeneratorTracker(_, _, _))
        .WillOnce([](Catch::StringRef, Catch::SourceLineInfo,
                     Catch::Generators::GeneratorBasePtr&& gen) -> Catch::IGeneratorTracker* {
            // Ensure we actually received ownership
            EXPECT_NE(gen.get(), nullptr);
            return nullptr;
        });

    auto gen = makeGen();
    auto* ret = Catch::Generators::createGeneratorTracker(
        Catch::StringRef("x"), Catch::SourceLineInfo("y.cpp", 1), std::move(gen));

    EXPECT_EQ(ret, nullptr);
    EXPECT_EQ(gen.get(), nullptr); // moved-from after call
}
