#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/catch_tag_alias_autoregistrar.hpp"

#include "catch2/internal/catch_source_line_info.hpp"

#include "catch2/interfaces/catch_interfaces_registry_hub.hpp"



using namespace Catch;

using ::testing::_;

using ::testing::Return;



class MockMutableRegistryHub : public IMutableRegistryHub {

public:

    MOCK_METHOD3(registerTagAlias, void(const std::string&, const std::string&, const SourceLineInfo&));

    MOCK_METHOD0(registerStartupException, void());

};



class RegistrarForTagAliasesTest_1101 : public ::testing::Test {

protected:

    MockMutableRegistryHub mockHub;

    SourceLineInfo lineInfo{"test_file.cpp", 42};



    void SetUp() override {

        // Set the mock object as the mutable registry hub for testing

        setMockMutableRegistryHub(&mockHub);

    }



    void TearDown() override {

        // Reset to original state after test

        resetToOriginalMutableRegistryHub();

    }

};



TEST_F(RegistrarForTagAliasesTest_1101, RegistersTagAliasNormally_1101) {

    EXPECT_CALL(mockHub, registerTagAlias("alias", "tag", lineInfo));



    RegistrarForTagAliases registrar{"alias", "tag", lineInfo};

}



TEST_F(RegistrarForTagAliasesTest_1101, HandlesExceptionDuringRegistration_1101) {

    EXPECT_CALL(mockHub, registerTagAlias("alias", "tag", lineInfo)).WillOnce(testing::Throw(std::exception()));

    EXPECT_CALL(mockHub, registerStartupException());



    RegistrarForTagAliases registrar{"alias", "tag", lineInfo};

}



TEST_F(RegistrarForTagAliasesTest_1101, RegistersWithEmptyAliasAndTag_1101) {

    EXPECT_CALL(mockHub, registerTagAlias("", "", lineInfo));



    RegistrarForTagAliases registrar{"", "", lineInfo};

}

```


