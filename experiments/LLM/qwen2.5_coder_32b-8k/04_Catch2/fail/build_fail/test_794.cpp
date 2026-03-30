#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/reporters/catch_reporter_multi.hpp"

#include "catch2/interfaces/catch_interfaces_reporter.hpp"

#include "catch2/internal/catch_stringref.hpp"



using namespace Catch;

using testing::NiceMock;



class MockEventListener : public IEventListener {

public:

    MOCK_METHOD(void, benchmarkFailed, (StringRef error), (override));

};



class MultiReporterTest_794 : public ::testing::Test {

protected:

    NiceMock<MockEventListener> mockListener1;

    NiceMock<MockEventListener> mockListener2;

    MultiReporter multiReporter;



    void SetUp() override {

        multiReporter.addListener(std::make_unique<NiceMock<MockEventListener>>(mockListener1));

        multiReporter.addListener(std::make_unique<NiceMock<MockEventListener>>(mockListener2));

    }

};



TEST_F(MultiReporterTest_794, BenchmarkFailed_DelegatesToAllListeners_794) {

    StringRef error("Benchmark failed");

    

    EXPECT_CALL(mockListener1, benchmarkFailed(error)).Times(1);

    EXPECT_CALL(mockListener2, benchmarkFailed(error)).Times(1);



    multiReporter.benchmarkFailed(error);

}



TEST_F(MultiReporterTest_794, BenchmarkFailed_EmptyErrorString_DelegatesToAllListeners_794) {

    StringRef emptyError("");



    EXPECT_CALL(mockListener1, benchmarkFailed(emptyError)).Times(1);

    EXPECT_CALL(mockListener2, benchmarkFailed(emptyError)).Times(1);



    multiReporter.benchmarkFailed(emptyError);

}



TEST_F(MultiReporterTest_794, BenchmarkFailed_LongErrorString_DelegatesToAllListeners_794) {

    StringRef longError("This is a very long error message that should be handled correctly by the MultiReporter class.");



    EXPECT_CALL(mockListener1, benchmarkFailed(longError)).Times(1);

    EXPECT_CALL(mockListener2, benchmarkFailed(longError)).Times(1);



    multiReporter.benchmarkFailed(longError);

}



TEST_F(MultiReporterTest_794, BenchmarkFailed_NoListeners_DoesNotCrash_794) {

    MultiReporter emptyMultiReporter;

    

    StringRef error("Benchmark failed");



    EXPECT_NO_THROW(emptyMultiReporter.benchmarkFailed(error));

}
