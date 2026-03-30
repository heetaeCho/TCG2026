#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/reporters/catch_reporter_common_base.hpp"

#include "catch2/interfaces/catch_interfaces_registry_hub.hpp"



using namespace Catch;

using ::testing::ElementsAre;



class MockListenerDescription : public ListenerDescription {

public:

    MOCK_CONST_METHOD0(getName, std::string());

};



class ReporterBaseTest_778 : public ::testing::Test {

protected:

    struct TestReporterConfig : public ReporterConfig {

        TestReporterConfig() 

            : ReporterConfig(Catch::Ptr<IRegistryHub>(), Catch::ColourMode::None) {}

        virtual ~TestReporterConfig() override = default;

    };



    std::vector<ListenerDescription> listenerDescriptions;

    MockListenerDescription mockListener1;

    MockListenerDescription mockListener2;



    TestReporterConfig config;

    ReporterBase* reporterBase;



    ReporterBaseTest_778() {

        listenerDescriptions.push_back(mockListener1);

        listenerDescriptions.push_back(mockListener2);



        reporterBase = new ReporterBase(std::move(config));

    }



    ~ReporterBaseTest_778() override {

        delete reporterBase;

    }

};



TEST_F(ReporterBaseTest_778, ListListeners_CallsDefaultListListenersWithCorrectArguments_778) {

    EXPECT_CALL(mockListener1, getName()).WillOnce(::testing::Return("listener1"));

    EXPECT_CALL(mockListener2, getName()).WillOnce(::testing::Return("listener2"));



    reporterBase->listListeners(listenerDescriptions);

}



TEST_F(ReporterBaseTest_778, ListListeners_EmptyList_NoCrashOrError_778) {

    std::vector<ListenerDescription> emptyDescriptions;

    EXPECT_NO_THROW(reporterBase->listListeners(emptyDescriptions));

}



TEST_F(ReporterBaseTest_778, ListReporters_CallsDefaultListReportersWithCorrectArguments_778) {

    struct MockReporterDescription : public ReporterDescription {

        MOCK_CONST_METHOD0(getName, std::string());

    };



    MockReporterDescription mockReporter1;

    MockReporterDescription mockReporter2;



    std::vector<ReporterDescription> reporterDescriptions = {mockReporter1, mockReporter2};



    EXPECT_CALL(mockReporter1, getName()).WillOnce(::testing::Return("reporter1"));

    EXPECT_CALL(mockReporter2, getName()).WillOnce(::testing::Return("reporter2"));



    reporterBase->listReporters(reporterDescriptions);

}



TEST_F(ReporterBaseTest_778, ListReporters_EmptyList_NoCrashOrError_778) {

    std::vector<ReporterDescription> emptyDescriptions;

    EXPECT_NO_THROW(reporterBase->listReporters(emptyDescriptions));

}
