#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <signal.h>



namespace Catch {

    struct SignalDefs { 

        int id; 

        const char * name; 

    };



    extern SignalDefs signalDefs[6];

    extern stack_t oldSigStack;

    extern struct sigaction oldSigActions[6];



    static void restorePreviousSignalHandlers() noexcept;

}



using ::testing::StrictMock;



class MockSignalHandler {

public:

    MOCK_METHOD(void, mock_sigaction, (int signum, const struct sigaction *act, struct sigaction *oldact), ());

    MOCK_METHOD(int, mock_sigaltstack, (const stack_t *ss, stack_t *oss), ());

};



extern "C" {

    int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact) {

        return global_mock_signal_handler->mock_sigaction(signum, act, oldact);

    }



    int sigaltstack(const stack_t *ss, stack_t *oss) {

        return global_mock_signal_handler->mock_sigaltstack(ss, oss);

    }

}



MockSignalHandler* global_mock_signal_handler = nullptr;



class CatchFatalConditionHandlerTest_483 : public ::testing::Test {

protected:

    StrictMock<MockSignalHandler> mock;

    

    void SetUp() override {

        global_mock_signal_handler = &mock;

    }



    void TearDown() override {

        global_mock_signal_handler = nullptr;

    }

};



TEST_F(CatchFatalConditionHandlerTest_483, RestorePreviousSignalHandlers_NormalOperation_483) {

    EXPECT_CALL(mock, mock_sigaction(Catch::signalDefs[0].id, &Catch::oldSigActions[0], nullptr)).Times(1);

    EXPECT_CALL(mock, mock_sigaction(Catch::signalDefs[1].id, &Catch::oldSigActions[1], nullptr)).Times(1);

    EXPECT_CALL(mock, mock_sigaction(Catch::signalDefs[2].id, &Catch::oldSigActions[2], nullptr)).Times(1);

    EXPECT_CALL(mock, mock_sigaction(Catch::signalDefs[3].id, &Catch::oldSigActions[3], nullptr)).Times(1);

    EXPECT_CALL(mock, mock_sigaction(Catch::signalDefs[4].id, &Catch::oldSigActions[4], nullptr)).Times(1);

    EXPECT_CALL(mock, mock_sigaction(Catch::signalDefs[5].id, &Catch::oldSigActions[5], nullptr)).Times(1);

    

    EXPECT_CALL(mock, mock_sigaltstack(&Catch::oldSigStack, nullptr)).Times(1);



    Catch::restorePreviousSignalHandlers();

}



TEST_F(CatchFatalConditionHandlerTest_483, RestorePreviousSignalHandlers_SigactionFailure_483) {

    for (int i = 0; i < sizeof(Catch::signalDefs) / sizeof(Catch::SignalDefs); ++i) {

        EXPECT_CALL(mock, mock_sigaction(Catch::signalDefs[i].id, &Catch::oldSigActions[i], nullptr)).WillOnce(::testing::Return(-1));

    }

    

    EXPECT_CALL(mock, mock_sigaltstack(&Catch::oldSigStack, nullptr)).Times(0);



    Catch::restorePreviousSignalHandlers();

}



TEST_F(CatchFatalConditionHandlerTest_483, RestorePreviousSignalHandlers_SigaltstackFailure_483) {

    for (int i = 0; i < sizeof(Catch::signalDefs) / sizeof(Catch::SignalDefs); ++i) {

        EXPECT_CALL(mock, mock_sigaction(Catch::signalDefs[i].id, &Catch::oldSigActions[i], nullptr)).Times(1);

    }

    

    EXPECT_CALL(mock, mock_sigaltstack(&Catch::oldSigStack, nullptr)).WillOnce(::testing::Return(-1));



    Catch::restorePreviousSignalHandlers();

}



TEST_F(CatchFatalConditionHandlerTest_483, RestorePreviousSignalHandlers_AllFailures_483) {

    for (int i = 0; i < sizeof(Catch::signalDefs) / sizeof(Catch::SignalDefs); ++i) {

        EXPECT_CALL(mock, mock_sigaction(Catch::signalDefs[i].id, &Catch::oldSigActions[i], nullptr)).WillOnce(::testing::Return(-1));

    }

    

    EXPECT_CALL(mock, mock_sigaltstack(&Catch::oldSigStack, nullptr)).WillOnce(::testing::Return(-1));



    Catch::restorePreviousSignalHandlers();

}
