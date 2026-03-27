#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/interfaces/catch_interfaces_enum_values_registry.hpp"

#include "./TestProjects/Catch2/src/catch2/internal/catch_stringref.hpp"



namespace Catch {

    namespace Detail {

        struct EnumInfo {};

    }

}



using namespace Catch;

using namespace testing;



class MockIMutableEnumValuesRegistry : public IMutableEnumValuesRegistry {

public:

    MOCK_METHOD3(registerEnum, const Detail::EnumInfo&(StringRef enumName, StringRef allEnums, const std::vector<int>& values));

};



TEST_F(MockIMutableEnumValuesRegistryTest_72, RegisterEnumWithValidData_72) {

    MockIMutableEnumValuesRegistry mockRegistry;

    StringRef enumName("TestEnum");

    StringRef allEnums("Value1 Value2 Value3");

    std::initializer_list<int> values = {0, 1, 2};



    EXPECT_CALL(mockRegistry, registerEnum(enumName, allEnums, ElementsAreArray(values)))

        .WillOnce(Return(Detail::EnumInfo{}));



    mockRegistry.registerEnum(enumName, allEnums, values);

}



TEST_F(MockIMutableEnumValuesRegistryTest_72, RegisterEnumWithEmptyEnumName_72) {

    MockIMutableEnumValuesRegistry mockRegistry;

    StringRef enumName("");

    StringRef allEnums("Value1 Value2 Value3");

    std::initializer_list<int> values = {0, 1, 2};



    EXPECT_CALL(mockRegistry, registerEnum(enumName, allEnums, ElementsAreArray(values)))

        .WillOnce(Return(Detail::EnumInfo{}));



    mockRegistry.registerEnum(enumName, allEnums, values);

}



TEST_F(MockIMutableEnumValuesRegistryTest_72, RegisterEnumWithEmptyAllEnums_72) {

    MockIMutableEnumValuesRegistry mockRegistry;

    StringRef enumName("TestEnum");

    StringRef allEnums("");

    std::initializer_list<int> values = {0, 1, 2};



    EXPECT_CALL(mockRegistry, registerEnum(enumName, allEnums, ElementsAreArray(values)))

        .WillOnce(Return(Detail::EnumInfo{}));



    mockRegistry.registerEnum(enumName, allEnums, values);

}



TEST_F(MockIMutableEnumValuesRegistryTest_72, RegisterEnumWithEmptyValues_72) {

    MockIMutableEnumValuesRegistry mockRegistry;

    StringRef enumName("TestEnum");

    StringRef allEnums("Value1 Value2 Value3");

    std::initializer_list<int> values = {};



    EXPECT_CALL(mockRegistry, registerEnum(enumName, allEnums, ElementsAreArray(values)))

        .WillOnce(Return(Detail::EnumInfo{}));



    mockRegistry.registerEnum(enumName, allEnums, values);

}



TEST_F(MockIMutableEnumValuesRegistryTest_72, RegisterEnumWithSingleValue_72) {

    MockIMutableEnumValuesRegistry mockRegistry;

    StringRef enumName("TestEnum");

    StringRef allEnums("Value1");

    std::initializer_list<int> values = {0};



    EXPECT_CALL(mockRegistry, registerEnum(enumName, allEnums, ElementsAreArray(values)))

        .WillOnce(Return(Detail::EnumInfo{}));



    mockRegistry.registerEnum(enumName, allEnums, values);

}



TEST_F(MockIMutableEnumValuesRegistryTest_72, RegisterEnumWithMultipleValues_72) {

    MockIMutableEnumValuesRegistry mockRegistry;

    StringRef enumName("TestEnum");

    StringRef allEnums("Value1 Value2 Value3 Value4");

    std::initializer_list<int> values = {0, 1, 2, 3};



    EXPECT_CALL(mockRegistry, registerEnum(enumName, allEnums, ElementsAreArray(values)))

        .WillOnce(Return(Detail::EnumInfo{}));



    mockRegistry.registerEnum(enumName, allEnums, values);

}
