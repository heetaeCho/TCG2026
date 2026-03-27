#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_fatal_condition_handler.cpp"



using ::testing::_;

using ::testing::MockFunction;



namespace Catch {



class MockFatalReporter {

public:

    MOCK_METHOD1(reportFatal, void(const char*));

};



MockFunction<void(int)> mockRaise;

void raise(int sig) { mockRaise.Call(sig); }



TEST_F(CatchSignalHandlerTest_484, HandleKnownSignal_484) {

    MockFatalReporter mockReporter;

    reportFatal = [&mockReporter](const char* name) { mockReporter.reportFatal(name); };



    EXPECT_CALL(mockReporter, reportFatal("SIGINT - Terminal interrupt signal")).Times(1);

    EXPECT_CALL(mockRaise, Call(SIGINT)).Times(1);



    handleSignal(SIGINT);

}



TEST_F(CatchSignalHandlerTest_484, HandleUnknownSignal_484) {

    MockFatalReporter mockReporter;

    reportFatal = [&mockReporter](const char* name) { mockReporter.reportFatal(name); };



    EXPECT_CALL(mockReporter, reportFatal("<unknown signal>")).Times(1);

    EXPECT_CALL(mockRaise, Call(SIGUSR1)).Times(1);



    handleSignal(SIGUSR1);

}



TEST_F(CatchSignalHandlerTest_484, HandleBoundarySignalLow_484) {

    MockFatalReporter mockReporter;

    reportFatal = [&mockReporter](const char* name) { mockReporter.reportFatal(name); };



    EXPECT_CALL(mockReporter, reportFatal("<unknown signal>")).Times(1);

    EXPECT_CALL(mockRaise, Call(-1)).Times(1);



    handleSignal(-1);

}



TEST_F(CatchSignalHandlerTest_484, HandleBoundarySignalHigh_484) {

    MockFatalReporter mockReporter;

    reportFatal = [&mockReporter](const char* name) { mockReporter.reportFatal(name); };



    EXPECT_CALL(mockReporter, reportFatal("<unknown signal>")).Times(1);

    EXPECT_CALL(mockRaise, Call(32)).Times(1);



    handleSignal(32);

}



}  // namespace Catch
