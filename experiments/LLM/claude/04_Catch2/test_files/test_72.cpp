#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <vector>
#include <string>
#include <initializer_list>

// Include necessary headers
#include "catch2/interfaces/catch_interfaces_enum_values_registry.hpp"
#include "catch2/internal/catch_stringref.hpp"
#include "catch2/internal/catch_enum_values_registry.hpp"

namespace {

// Mock implementation of IMutableEnumValuesRegistry for testing
class MockMutableEnumValuesRegistry : public Catch::IMutableEnumValuesRegistry {
public:
    MOCK_METHOD(const Catch::Detail::EnumInfo&, registerEnum,
                (Catch::StringRef enumName, Catch::StringRef allEnums, const std::vector<int>& values),
                (override));
    
    ~MockMutableEnumValuesRegistry() override = default;
};

// Test enums
enum class SimpleEnum { A = 0, B = 1, C = 2 };
enum class NegativeEnum { Neg = -1, Zero = 0, Pos = 1 };
enum class SingleValueEnum { Only = 42 };
enum SmallEnum : short { X = 0, Y = 1, Z = 2 };
enum class CharSizedEnum : char { Low = 0, Mid = 10, High = 100 };

class IMutableEnumValuesRegistryTest_72 : public ::testing::Test {
protected:
    MockMutableEnumValuesRegistry mockRegistry;
    // We need a real EnumInfo to return from the mock
    // We'll use a static one
};

TEST_F(IMutableEnumValuesRegistryTest_72, RegisterEnumWithSimpleEnum_72) {
    Catch::Detail::EnumInfo dummyInfo;
    
    EXPECT_CALL(mockRegistry, registerEnum(
        ::testing::_, ::testing::_, ::testing::Eq(std::vector<int>{0, 1, 2})))
        .WillOnce(::testing::ReturnRef(dummyInfo));
    
    auto& result = mockRegistry.registerEnum(
        "SimpleEnum", "A, B, C",
        std::initializer_list<SimpleEnum>{SimpleEnum::A, SimpleEnum::B, SimpleEnum::C});
    
    EXPECT_EQ(&result, &dummyInfo);
}

TEST_F(IMutableEnumValuesRegistryTest_72, RegisterEnumWithNegativeValues_72) {
    Catch::Detail::EnumInfo dummyInfo;
    
    EXPECT_CALL(mockRegistry, registerEnum(
        ::testing::_, ::testing::_, ::testing::Eq(std::vector<int>{-1, 0, 1})))
        .WillOnce(::testing::ReturnRef(dummyInfo));
    
    auto& result = mockRegistry.registerEnum(
        "NegativeEnum", "Neg, Zero, Pos",
        std::initializer_list<NegativeEnum>{NegativeEnum::Neg, NegativeEnum::Zero, NegativeEnum::Pos});
    
    EXPECT_EQ(&result, &dummyInfo);
}

TEST_F(IMutableEnumValuesRegistryTest_72, RegisterEnumWithSingleValue_72) {
    Catch::Detail::EnumInfo dummyInfo;
    
    EXPECT_CALL(mockRegistry, registerEnum(
        ::testing::_, ::testing::_, ::testing::Eq(std::vector<int>{42})))
        .WillOnce(::testing::ReturnRef(dummyInfo));
    
    auto& result = mockRegistry.registerEnum(
        "SingleValueEnum", "Only",
        std::initializer_list<SingleValueEnum>{SingleValueEnum::Only});
    
    EXPECT_EQ(&result, &dummyInfo);
}

TEST_F(IMutableEnumValuesRegistryTest_72, RegisterEnumWithSmallEnumType_72) {
    Catch::Detail::EnumInfo dummyInfo;
    
    EXPECT_CALL(mockRegistry, registerEnum(
        ::testing::_, ::testing::_, ::testing::Eq(std::vector<int>{0, 1, 2})))
        .WillOnce(::testing::ReturnRef(dummyInfo));
    
    auto& result = mockRegistry.registerEnum(
        "SmallEnum", "X, Y, Z",
        std::initializer_list<SmallEnum>{X, Y, Z});
    
    EXPECT_EQ(&result, &dummyInfo);
}

TEST_F(IMutableEnumValuesRegistryTest_72, RegisterEnumWithCharSizedEnum_72) {
    Catch::Detail::EnumInfo dummyInfo;
    
    EXPECT_CALL(mockRegistry, registerEnum(
        ::testing::_, ::testing::_, ::testing::Eq(std::vector<int>{0, 10, 100})))
        .WillOnce(::testing::ReturnRef(dummyInfo));
    
    auto& result = mockRegistry.registerEnum(
        "CharSizedEnum", "Low, Mid, High",
        std::initializer_list<CharSizedEnum>{CharSizedEnum::Low, CharSizedEnum::Mid, CharSizedEnum::High});
    
    EXPECT_EQ(&result, &dummyInfo);
}

TEST_F(IMutableEnumValuesRegistryTest_72, RegisterEnumPassesCorrectEnumName_72) {
    Catch::Detail::EnumInfo dummyInfo;
    
    EXPECT_CALL(mockRegistry, registerEnum(
        Catch::StringRef("MyTestEnum"), ::testing::_, ::testing::_))
        .WillOnce(::testing::ReturnRef(dummyInfo));
    
    mockRegistry.registerEnum(
        "MyTestEnum", "A, B, C",
        std::initializer_list<SimpleEnum>{SimpleEnum::A, SimpleEnum::B, SimpleEnum::C});
}

TEST_F(IMutableEnumValuesRegistryTest_72, RegisterEnumPassesCorrectAllEnums_72) {
    Catch::Detail::EnumInfo dummyInfo;
    
    EXPECT_CALL(mockRegistry, registerEnum(
        ::testing::_, Catch::StringRef("Alpha, Beta, Gamma"), ::testing::_))
        .WillOnce(::testing::ReturnRef(dummyInfo));
    
    mockRegistry.registerEnum(
        "SimpleEnum", "Alpha, Beta, Gamma",
        std::initializer_list<SimpleEnum>{SimpleEnum::A, SimpleEnum::B, SimpleEnum::C});
}

TEST_F(IMutableEnumValuesRegistryTest_72, RegisterEnumEmptyInitializerList_72) {
    Catch::Detail::EnumInfo dummyInfo;
    
    EXPECT_CALL(mockRegistry, registerEnum(
        ::testing::_, ::testing::_, ::testing::Eq(std::vector<int>{})))
        .WillOnce(::testing::ReturnRef(dummyInfo));
    
    auto& result = mockRegistry.registerEnum(
        "SimpleEnum", "",
        std::initializer_list<SimpleEnum>{});
    
    EXPECT_EQ(&result, &dummyInfo);
}

TEST_F(IMutableEnumValuesRegistryTest_72, RegisterEnumReturnsReference_72) {
    Catch::Detail::EnumInfo dummyInfo;
    
    EXPECT_CALL(mockRegistry, registerEnum(::testing::_, ::testing::_, ::testing::_))
        .WillOnce(::testing::ReturnRef(dummyInfo));
    
    const Catch::Detail::EnumInfo& result = mockRegistry.registerEnum(
        "SimpleEnum", "A",
        std::initializer_list<SimpleEnum>{SimpleEnum::A});
    
    // Verify it returns a const reference
    EXPECT_EQ(&result, &dummyInfo);
}

TEST_F(IMutableEnumValuesRegistryTest_72, RegisterEnumWithDuplicateValues_72) {
    Catch::Detail::EnumInfo dummyInfo;
    
    EXPECT_CALL(mockRegistry, registerEnum(
        ::testing::_, ::testing::_, ::testing::Eq(std::vector<int>{0, 0, 1, 1})))
        .WillOnce(::testing::ReturnRef(dummyInfo));
    
    auto& result = mockRegistry.registerEnum(
        "SimpleEnum", "A, A, B, B",
        std::initializer_list<SimpleEnum>{SimpleEnum::A, SimpleEnum::A, SimpleEnum::B, SimpleEnum::B});
    
    EXPECT_EQ(&result, &dummyInfo);
}

TEST_F(IMutableEnumValuesRegistryTest_72, RegisterEnumVectorSizeMatchesInitializerList_72) {
    Catch::Detail::EnumInfo dummyInfo;
    
    // Verify that the vector passed has exactly 3 elements
    EXPECT_CALL(mockRegistry, registerEnum(
        ::testing::_, ::testing::_, ::testing::Property(&std::vector<int>::size, 3u)))
        .WillOnce(::testing::ReturnRef(dummyInfo));
    
    mockRegistry.registerEnum(
        "SimpleEnum", "A, B, C",
        std::initializer_list<SimpleEnum>{SimpleEnum::A, SimpleEnum::B, SimpleEnum::C});
}

// Test that the virtual destructor can be called (polymorphic deletion)
TEST_F(IMutableEnumValuesRegistryTest_72, DestructorIsVirtual_72) {
    auto* registry = new MockMutableEnumValuesRegistry();
    Catch::IMutableEnumValuesRegistry* basePtr = registry;
    // Should not leak or crash - virtual destructor
    delete basePtr;
}

// Test with vector-based registerEnum directly
TEST_F(IMutableEnumValuesRegistryTest_72, RegisterEnumWithIntVector_72) {
    Catch::Detail::EnumInfo dummyInfo;
    std::vector<int> values = {10, 20, 30};
    
    EXPECT_CALL(mockRegistry, registerEnum(
        ::testing::_, ::testing::_, ::testing::Eq(values)))
        .WillOnce(::testing::ReturnRef(dummyInfo));
    
    auto& result = mockRegistry.registerEnum(
        Catch::StringRef("TestEnum"), Catch::StringRef("Ten, Twenty, Thirty"), values);
    
    EXPECT_EQ(&result, &dummyInfo);
}

} // namespace
