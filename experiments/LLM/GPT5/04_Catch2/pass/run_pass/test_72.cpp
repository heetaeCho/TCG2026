// File: test_enum_values_registry_72.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <vector>
#include <string>
#include <climits>

// Headers from the provided interface
#include "catch2/interfaces/catch_interfaces_enum_values_registry.hpp"
#include "catch2/internal/catch_stringref.hpp"

using ::testing::ElementsAre;
using ::testing::IsEmpty;
using ::testing::ReturnRef;

namespace {

// Helper matcher: compare Catch::StringRef to std::string by content
MATCHER_P(StringRefContentEq, expected, "Matches Catch::StringRef by content") {
    const auto& s = arg;
    const std::string actual{s.data(), s.size()};
    return actual == expected;
}

// Minimal mock of the registry that verifies the virtual overload is invoked
class MockEnumValuesRegistry : public Catch::IMutableEnumValuesRegistry {
public:
    // Bring the base-class template into scope; otherwise the mock's
    // non-template virtual overload would hide it.
    using Catch::IMutableEnumValuesRegistry::registerEnum;

    // Mock the virtual overload that the template must delegate to
    MOCK_METHOD((const Catch::Detail::EnumInfo&),
                registerEnum,
                (Catch::StringRef enumName,
                 Catch::StringRef allEnums,
                 const std::vector<int>& values),
                (override));
};

} // namespace

// ---------- Tests ----------

class IMutableEnumValuesRegistryTest_72 : public ::testing::Test {
protected:
    MockEnumValuesRegistry reg_;
    Catch::Detail::EnumInfo info_; // Returned by the mocked virtual method
};

// Verifies: enum values are converted to int, name & allEnums forwarded,
// and the returned reference is propagated.
TEST_F(IMutableEnumValuesRegistryTest_72, ForwardsArgsAndConvertsValues_72) {
    enum class Color : int { Red = -1, Green = 0, Blue = 5 };

    EXPECT_CALL(
        reg_,
        registerEnum(
            StringRefContentEq("Color"),
            StringRefContentEq("Red,Green,Blue"),
            ElementsAre(-1, 5))) // order & exact ints
        .WillOnce(ReturnRef(info_));

    const auto& out =
        reg_.registerEnum<Color>(Catch::StringRef("Color"),
                                 Catch::StringRef("Red,Green,Blue"),
                                 {Color::Red, Color::Blue});

    // Must be exactly the reference returned by the virtual function
    EXPECT_EQ(&out, &info_);
}

// Verifies: empty initializer_list results in forwarding an empty vector<int>.
TEST_F(IMutableEnumValuesRegistryTest_72, ForwardsEmptyValues_72) {
    enum class Emptyish : int { A = 0 };

    EXPECT_CALL(
        reg_,
        registerEnum(StringRefContentEq("Emptyish"),
                     StringRefContentEq(""),
                     IsEmpty()))
        .WillOnce(ReturnRef(info_));

    const auto& out =
        reg_.registerEnum<Emptyish>(Catch::StringRef("Emptyish"),
                                    Catch::StringRef(""),
                                    {}); // empty list

    EXPECT_EQ(&out, &info_);
}

// Verifies: value order and duplicates are preserved during conversion.
TEST_F(IMutableEnumValuesRegistryTest_72, PreservesOrderAndDuplicates_72) {
    enum class Numbers : int { A = 2, B = 2, C = -7 };

    std::string n = "Numbers";
    std::string all = "A,B,C";

    EXPECT_CALL(
        reg_,
        registerEnum(StringRefContentEq("Numbers"),
                     StringRefContentEq("A,B,C"),
                     ElementsAre(2, 2, -7)))
        .WillOnce(ReturnRef(info_));

    const auto& out =
        reg_.registerEnum<Numbers>(Catch::StringRef(n),
                                   Catch::StringRef(all),
                                   {Numbers::A, Numbers::B, Numbers::C});

    EXPECT_EQ(&out, &info_);
}

// Verifies: large (but int-sized) enum values are correctly cast and forwarded.
TEST_F(IMutableEnumValuesRegistryTest_72, HandlesExtremeIntValues_72) {
    enum class Big : int {
        NearMin = INT_MIN + 1,
        NearMax = INT_MAX - 2
    };

    EXPECT_CALL(
        reg_,
        registerEnum(StringRefContentEq("Big"),
                     StringRefContentEq("NearMin,NearMax"),
                     ElementsAre(INT_MIN + 1, INT_MAX - 2)))
        .WillOnce(ReturnRef(info_));

    const auto& out =
        reg_.registerEnum<Big>(Catch::StringRef("Big"),
                               Catch::StringRef("NearMin,NearMax"),
                               {Big::NearMin, Big::NearMax});

    EXPECT_EQ(&out, &info_);
}

// Verifies: unsigned underlying enums also convert to int and forward correctly.
TEST_F(IMutableEnumValuesRegistryTest_72, SupportsUnsignedUnderlyingEnums_72) {
    enum class Flags : unsigned int { A = 0u, B = 3u, C = 9u };

    EXPECT_CALL(
        reg_,
        registerEnum(StringRefContentEq("Flags"),
                     StringRefContentEq("A,B,C"),
                     ElementsAre(0, 3, 9)))
        .WillOnce(ReturnRef(info_));

    const auto& out =
        reg_.registerEnum<Flags>(Catch::StringRef("Flags"),
                                 Catch::StringRef("A,B,C"),
                                 {Flags::A, Flags::B, Flags::C});

    EXPECT_EQ(&out, &info_);
}
