// File: tests/ITracker_NameAndLocation_440.cpp

#include <gtest/gtest.h>
#include <type_traits>

// Include the real header under test
#include "catch2/internal/catch_test_case_tracker.hpp"

// The tests rely only on the public interface. To instantiate an ITracker,
// we define a minimal concrete subclass that does NOT re-implement any internal
// logic and only satisfies virtual requirements to allow construction.
namespace Catch { namespace TestCaseTracking {

class ConcreteTracker_440 final : public ITracker {
public:
    using ITracker::ITracker; // inherit (NameAndLocation&&, ITracker*)

    // Provide minimal overrides; behavior of these is not under test here.
    ~ConcreteTracker_440() override = default;
    bool isComplete() override { return false; }
    void close() override {}
    void fail() override {}
    bool isSectionTracker() const override { return false; }
    bool isGeneratorTracker() const override { return false; }
};

}} // namespace Catch::TestCaseTracking

using Catch::TestCaseTracking::ConcreteTracker_440;
using Catch::TestCaseTracking::ITracker;

// Helper to create a NameAndLocation with recognizable values.
// This uses only public constructors/fields available from the included headers.
static Catch::NameAndLocation makeNAL_440(const char* name,
                                          const char* file = "file_440.cpp",
                                          std::size_t line = 440) {
    return Catch::NameAndLocation{name, Catch::SourceLineInfo{file, static_cast<std::uint32_t>(line)}};
}

// --- Tests ---

// Ensures the return type is exactly "const NameAndLocation&" (API/ABI contract).
TEST(ITracker_NameAndLocation_440, ReturnsConstRefType_440) {
    static_assert(std::is_same_v<decltype(std::declval<const ITracker&>().nameAndLocation()),
                                 const Catch::NameAndLocation&>,
                  "nameAndLocation() must return const Catch::NameAndLocation&");
    SUCCEED();
}

// Ensures that calling nameAndLocation() twice returns the same reference
// (observable via reference identity).
TEST(ITracker_NameAndLocation_440, ReturnsStableReferenceIdentity_440) {
    auto nal = makeNAL_440("stable_identity");
    ConcreteTracker_440 tracker{std::move(nal), /*parent*/nullptr};

    auto const& ref1 = tracker.nameAndLocation();
    auto const& ref2 = tracker.nameAndLocation();

    // Same object reference each time
    EXPECT_EQ(&ref1, &ref2);
}

// Ensures that the returned NameAndLocation reflects the values provided at construction.
TEST(ITracker_NameAndLocation_440, ReflectsProvidedValues_440) {
    const char* kName = "provided_values_440";
    const char* kFile = "provided_file_440.cpp";
    const std::size_t kLine = 123u;

    auto nal = makeNAL_440(kName, kFile, kLine);
    ConcreteTracker_440 tracker{std::move(nal), /*parent*/nullptr};

    auto const& out = tracker.nameAndLocation();

    // Only using public fields/observables of NameAndLocation
    EXPECT_EQ(out.name, kName);
    EXPECT_EQ(out.location.file, std::string{kFile});
    EXPECT_EQ(out.location.line, kLine);
}

// Ensures that moving a temporary (rvalue) into the tracker still yields
// a valid, accessible reference afterwards (lifetime managed by the tracker).
TEST(ITracker_NameAndLocation_440, ReferenceValidAfterRvalueCtor_440) {
    ConcreteTracker_440 tracker{makeNAL_440("rvalue_ctor_440"), /*parent*/nullptr};

    auto const& out = tracker.nameAndLocation();
    EXPECT_EQ(out.name, "rvalue_ctor_440");  // observable data remains intact
}

// Boundary-ish case: empty name (if permitted by the public type). We only
// verify observable values as seen through the accessor.
TEST(ITracker_NameAndLocation_440, HandlesEmptyName_440) {
    auto nal = makeNAL_440("");
    ConcreteTracker_440 tracker{std::move(nal), /*parent*/nullptr};

    auto const& out = tracker.nameAndLocation();
    EXPECT_TRUE(out.name.empty());
}

