#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch_amalgamated.cpp"

#include "catch_noncopyable.hpp"

#include "catch_stringref.hpp"

#include "catch_unique_ptr.hpp"

#include "catch_source_line_info.hpp"

#include "catch_interfaces_registry_hub.hpp"

#include "catch_test_registry.hpp"



using namespace Catch;

using namespace Catch::Detail;



class MockIMutableRegistryHub : public IMutableRegistryHub {

public:

    MOCK_METHOD(void, registerReporter, (const std::string &, IReporterFactoryPtr), (override));

    MOCK_METHOD(void, registerListener, (unique_ptr<EventListenerFactory>), (override));

    MOCK_METHOD(void, registerTest, (unique_ptr<TestCaseInfo>&&, unique_ptr<ITestInvoker>&&), (override));

    MOCK_METHOD(void, registerTranslator, (unique_ptr<IExceptionTranslator>&&), (override));

    MOCK_METHOD(void, registerTagAlias, (const std::string &, const std::string &, const SourceLineInfo &), (override));

    MOCK_METHOD(void, registerStartupException, (), (override));

    MOCK_METHOD(IMutableEnumValuesRegistry&, getMutableEnumValuesRegistry, (), (override));

};



class AutoRegTest : public ::testing::Test {

protected:

    MockIMutableRegistryHub mockRegistryHub;

    SourceLineInfo lineInfo = {"test_file.cpp", 42};

    StringRef classOrMethod = "TestClass";

    NameAndTags nameAndTags = NameAndTags("test_case_name", "[tag1][tag2]");

};



TEST_F(AutoRegTest, RegistersTest_1115) {

    auto mockInvoker = unique_ptr<ITestInvoker>(new ITestInvoker());

    EXPECT_CALL(mockRegistryHub, registerTest(_, _))

        .Times(1);



    AutoReg autoReg(std::move(mockInvoker), lineInfo, classOrMethod, nameAndTags);

}



TEST_F(AutoRegTest, RegistersStartupExceptionOnException_1115) {

    EXPECT_CALL(mockRegistryHub, registerStartupException())

        .Times(1);



    try {

        throw std::runtime_error("test exception");

    } catch (...) {

        AutoReg autoReg(nullptr, lineInfo, classOrMethod, nameAndTags);

    }

}



TEST_F(AutoRegTest, HandlesEmptyName_1115) {

    NameAndTags emptyNameTags = NameAndTags(StringRef(), "[tag1][tag2]");

    auto mockInvoker = unique_ptr<ITestInvoker>(new ITestInvoker());

    EXPECT_CALL(mockRegistryHub, registerTest(_, _))

        .Times(1);



    AutoReg autoReg(std::move(mockInvoker), lineInfo, classOrMethod, emptyNameTags);

}



TEST_F(AutoRegTest, HandlesEmptyTags_1115) {

    NameAndTags emptyTags = NameAndTags("test_case_name", StringRef());

    auto mockInvoker = unique_ptr<ITestInvoker>(new ITestInvoker());

    EXPECT_CALL(mockRegistryHub, registerTest(_, _))

        .Times(1);



    AutoReg autoReg(std::move(mockInvoker), lineInfo, classOrMethod, emptyTags);

}



TEST_F(AutoRegTest, HandlesEmptyClassOrMethod_1115) {

    StringRef emptyClassOrMethod = StringRef();

    auto mockInvoker = unique_ptr<ITestInvoker>(new ITestInvoker());

    EXPECT_CALL(mockRegistryHub, registerTest(_, _))

        .Times(1);



    AutoReg autoReg(std::move(mockInvoker), lineInfo, emptyClassOrMethod, nameAndTags);

}
