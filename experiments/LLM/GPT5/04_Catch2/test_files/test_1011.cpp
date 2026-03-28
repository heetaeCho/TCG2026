// File: tests/TestCaseInfoHasher_tests_1011.cpp

#include <gtest/gtest.h>
#include <vector>
#include <string>

// Catch2 headers (interfaces used by the tests)
#include "catch2/catch_test_case_info.hpp"
#include "catch_amalgamated.hpp"

using namespace Catch;

namespace {

// Small helper to build a TestCaseInfo with public interface only.
// We avoid depending on internal parsing; we set tags explicitly via the public vector.
static TestCaseInfo makeTestCaseInfo(
    const std::string& name,
    const std::string& className,
    const std::vector<std::string>& tagOriginals = {}
) {
    // Minimal NameAndTags and SourceLineInfo construction:
    // - We do not rely on internal parsing of tags; we assign tags directly.
    NameAndTags nt;
    nt.name = name;
    // Leave nt.tags default/empty; we will set TestCaseInfo::tags after construction.

    SourceLineInfo sli;
    sli.file = "dummy.cpp";
    sli.line = 123;

    TestCaseInfo tci{ StringRef(className), nt, sli };
    tci.tags.clear();
    tci.tags.reserve(tagOriginals.size());
    for (const auto& t : tagOriginals) {
        tci.tags.emplace_back(StringRef(t));
    }
    return tci;
}

} // namespace

// Same input + same seed => deterministic and equal
TEST(TestCaseInfoHasher_1011, DeterministicWithSameInputAndSeed_1011) {
    const hash_t seed = 0xABCDEF0123456789ull;

    auto tc1 = makeTestCaseInfo("SampleTest", "SuiteA", {"[fast]", "[unit]"});
    auto tc2 = makeTestCaseInfo("SampleTest", "SuiteA", {"[fast]", "[unit]"});

    TestCaseInfoHasher hasher(seed);
    const auto h1 = hasher(tc1);
    const auto h2 = hasher(tc2);

    EXPECT_EQ(h1, h2) << "Hasher must be deterministic for identical inputs and seed";
}

// Same input + different seed => (very likely) different hash
TEST(TestCaseInfoHasher_1011, DifferentSeedsUsuallyProduceDifferentHash_1011) {
    auto tc = makeTestCaseInfo("SampleTest", "SuiteA", {"[fast]", "[unit]"});

    TestCaseInfoHasher hasher1(0x1111111111111111ull);
    TestCaseInfoHasher hasher2(0x2222222222222222ull);

    const auto h1 = hasher1(tc);
    const auto h2 = hasher2(tc);

    // We assert inequality as an observable property of the hash function using the seed.
    // Collisions are theoretically possible, but extremely unlikely.
    EXPECT_NE(h1, h2) << "Changing the seed should change the resulting hash in general";
}

// Changing the test name should affect the hash
TEST(TestCaseInfoHasher_1011, NameAffectsHash_1011) {
    const hash_t seed = 0x1234567890ABCDEFull;

    auto tcA = makeTestCaseInfo("AlphaTest", "SuiteA", {"[fast]"});
    auto tcB = makeTestCaseInfo("AlphaTesT", "SuiteA", {"[fast]"}); // subtle change

    TestCaseInfoHasher hasher(seed);
    const auto hA = hasher(tcA);
    const auto hB = hasher(tcB);

    EXPECT_NE(hA, hB) << "Changing the test name should change the hash";
}

// Changing the class/suite name should affect the hash
TEST(TestCaseInfoHasher_1011, ClassNameAffectsHash_1011) {
    const hash_t seed = 0xFEDCBA0987654321ull;

    auto tcA = makeTestCaseInfo("MyTest", "SuiteA", {"[fast]"});
    auto tcB = makeTestCaseInfo("MyTest", "SuiteB", {"[fast]"});

    TestCaseInfoHasher hasher(seed);
    const auto hA = hasher(tcA);
    const auto hB = hasher(tcB);

    EXPECT_NE(hA, hB) << "Changing the className should change the hash";
}

// Changing tags (including order) should affect the hash — observable via public vector<Tag>
TEST(TestCaseInfoHasher_1011, TagsAndOrderAffectHash_1011) {
    const hash_t seed = 0xCAFEBABECAFED00Dull;

    auto tcAB = makeTestCaseInfo("Tagged", "Suite",
                                 {"[fast]", "[unit]"}); // order: fast, unit
    auto tcBA = makeTestCaseInfo("Tagged", "Suite",
                                 {"[unit]", "[fast]"}); // order: unit, fast

    TestCaseInfoHasher hasher(seed);
    const auto hAB = hasher(tcAB);
    const auto hBA = hasher(tcBA);

    // The hasher iterates over the tag container; order in container is observable input.
    EXPECT_NE(hAB, hBA) << "Changing tag order should change the hash";
}

// Empty fields should be handled and yield a stable (deterministic) value
TEST(TestCaseInfoHasher_1011, HandlesEmptyNameClassAndNoTags_1011) {
    const hash_t seed = 0x0ull;

    auto empty = makeTestCaseInfo("", "", {}); // empty name, empty className, no tags

    TestCaseInfoHasher hasher(seed);
    const auto h1 = hasher(empty);
    const auto h2 = hasher(empty);

    // We only assert determinism and that a value is produced.
    EXPECT_EQ(h1, h2) << "Hash should be stable for identical empty inputs";
    // Also ensure it's a 32-bit value by type — no runtime check needed beyond compilation.
}

// Adding a new tag changes the hash
TEST(TestCaseInfoHasher_1011, AddingTagChangesHash_1011) {
    const hash_t seed = 0x55AA55AA55AA55AAull;

    auto tc1 = makeTestCaseInfo("Tagged", "Suite", {"[fast]"});
    auto tc2 = makeTestCaseInfo("Tagged", "Suite", {"[fast]", "[ci]"});

    TestCaseInfoHasher hasher(seed);
    const auto h1 = hasher(tc1);
    const auto h2 = hasher(tc2);

    EXPECT_NE(h1, h2) << "Adding a tag should change the hash";
}
