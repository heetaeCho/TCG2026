#include <gtest/gtest.h>
#include <signal.h>
#include <cstring>
#include <cstdlib>

// We need access to the Catch namespace internals for testing
// Forward declarations based on known/inferred dependencies
namespace Catch {
    struct SignalDefs {
        int id;
        const char* name;
    };

    extern SignalDefs signalDefs[6];
    extern stack_t oldSigStack;
    extern struct sigaction oldSigActions[6];

    void restorePreviousSignalHandlers() noexcept;
}

// Dummy signal handler for testing
static void dummyHandler(int) {}
static void anotherDummyHandler(int) {}

class RestorePreviousSignalHandlersTest_483 : public ::testing::Test {
protected:
    struct sigaction savedActions[6];
    stack_t savedStack;

    void SetUp() override {
        // Save current state of oldSigActions and oldSigStack
        std::memcpy(savedActions, Catch::oldSigActions, sizeof(savedActions));
        std::memcpy(&savedStack, &Catch::oldSigStack, sizeof(savedStack));
    }

    void TearDown() override {
        // Restore the original oldSigActions and oldSigStack to avoid side effects
        std::memcpy(Catch::oldSigActions, savedActions, sizeof(savedActions));
        std::memcpy(&Catch::oldSigStack, &savedStack, sizeof(savedStack));
    }
};

TEST_F(RestorePreviousSignalHandlersTest_483, RestoresSignalHandlersToDefault_483) {
    // Set oldSigActions to SIG_DFL for all signals
    for (std::size_t i = 0; i < 6; ++i) {
        std::memset(&Catch::oldSigActions[i], 0, sizeof(struct sigaction));
        Catch::oldSigActions[i].sa_handler = SIG_DFL;
    }
    std::memset(&Catch::oldSigStack, 0, sizeof(stack_t));
    Catch::oldSigStack.ss_flags = SS_DISABLE;

    Catch::restorePreviousSignalHandlers();

    // Verify each signal handler was restored to SIG_DFL
    for (std::size_t i = 0; i < 6; ++i) {
        struct sigaction currentAction;
        sigaction(Catch::signalDefs[i].id, nullptr, &currentAction);
        EXPECT_EQ(currentAction.sa_handler, SIG_DFL)
            << "Signal " << Catch::signalDefs[i].name << " was not restored to SIG_DFL";
    }
}

TEST_F(RestorePreviousSignalHandlersTest_483, RestoresCustomSignalHandlers_483) {
    // Set oldSigActions to a custom handler for all signals
    for (std::size_t i = 0; i < 6; ++i) {
        std::memset(&Catch::oldSigActions[i], 0, sizeof(struct sigaction));
        Catch::oldSigActions[i].sa_handler = dummyHandler;
        sigemptyset(&Catch::oldSigActions[i].sa_mask);
        Catch::oldSigActions[i].sa_flags = 0;
    }
    std::memset(&Catch::oldSigStack, 0, sizeof(stack_t));
    Catch::oldSigStack.ss_flags = SS_DISABLE;

    Catch::restorePreviousSignalHandlers();

    // Verify each signal handler was set to dummyHandler
    for (std::size_t i = 0; i < 6; ++i) {
        struct sigaction currentAction;
        sigaction(Catch::signalDefs[i].id, nullptr, &currentAction);
        EXPECT_EQ(currentAction.sa_handler, dummyHandler)
            << "Signal " << Catch::signalDefs[i].name << " was not restored to dummyHandler";
    }

    // Clean up: restore defaults
    for (std::size_t i = 0; i < 6; ++i) {
        struct sigaction defaultAction;
        std::memset(&defaultAction, 0, sizeof(defaultAction));
        defaultAction.sa_handler = SIG_DFL;
        sigaction(Catch::signalDefs[i].id, &defaultAction, nullptr);
    }
}

TEST_F(RestorePreviousSignalHandlersTest_483, RestoresSigIgnHandlers_483) {
    // Set oldSigActions to SIG_IGN for all signals
    for (std::size_t i = 0; i < 6; ++i) {
        std::memset(&Catch::oldSigActions[i], 0, sizeof(struct sigaction));
        Catch::oldSigActions[i].sa_handler = SIG_IGN;
        sigemptyset(&Catch::oldSigActions[i].sa_mask);
        Catch::oldSigActions[i].sa_flags = 0;
    }
    std::memset(&Catch::oldSigStack, 0, sizeof(stack_t));
    Catch::oldSigStack.ss_flags = SS_DISABLE;

    Catch::restorePreviousSignalHandlers();

    for (std::size_t i = 0; i < 6; ++i) {
        struct sigaction currentAction;
        sigaction(Catch::signalDefs[i].id, nullptr, &currentAction);
        EXPECT_EQ(currentAction.sa_handler, SIG_IGN)
            << "Signal " << Catch::signalDefs[i].name << " was not restored to SIG_IGN";
    }

    // Clean up
    for (std::size_t i = 0; i < 6; ++i) {
        struct sigaction defaultAction;
        std::memset(&defaultAction, 0, sizeof(defaultAction));
        defaultAction.sa_handler = SIG_DFL;
        sigaction(Catch::signalDefs[i].id, &defaultAction, nullptr);
    }
}

TEST_F(RestorePreviousSignalHandlersTest_483, RestoresAlternateSignalStack_483) {
    // Allocate an alternate signal stack
    void* stackMem = malloc(SIGSTKSZ);
    ASSERT_NE(stackMem, nullptr);

    Catch::oldSigStack.ss_sp = stackMem;
    Catch::oldSigStack.ss_size = SIGSTKSZ;
    Catch::oldSigStack.ss_flags = 0;

    // Set oldSigActions to defaults
    for (std::size_t i = 0; i < 6; ++i) {
        std::memset(&Catch::oldSigActions[i], 0, sizeof(struct sigaction));
        Catch::oldSigActions[i].sa_handler = SIG_DFL;
    }

    Catch::restorePreviousSignalHandlers();

    // Verify the alternate stack was restored
    stack_t currentStack;
    sigaltstack(nullptr, &currentStack);
    EXPECT_EQ(currentStack.ss_sp, stackMem);
    EXPECT_EQ(currentStack.ss_size, static_cast<size_t>(SIGSTKSZ));

    // Clean up: disable the alt stack
    stack_t disableStack;
    disableStack.ss_flags = SS_DISABLE;
    disableStack.ss_sp = nullptr;
    disableStack.ss_size = 0;
    sigaltstack(&disableStack, nullptr);
    free(stackMem);
}

TEST_F(RestorePreviousSignalHandlersTest_483, RestoresSignalMasks_483) {
    // Set oldSigActions with specific signal masks
    for (std::size_t i = 0; i < 6; ++i) {
        std::memset(&Catch::oldSigActions[i], 0, sizeof(struct sigaction));
        Catch::oldSigActions[i].sa_handler = SIG_DFL;
        sigemptyset(&Catch::oldSigActions[i].sa_mask);
        sigaddset(&Catch::oldSigActions[i].sa_mask, SIGUSR1);
        Catch::oldSigActions[i].sa_flags = 0;
    }
    std::memset(&Catch::oldSigStack, 0, sizeof(stack_t));
    Catch::oldSigStack.ss_flags = SS_DISABLE;

    Catch::restorePreviousSignalHandlers();

    // Verify signal masks contain SIGUSR1
    for (std::size_t i = 0; i < 6; ++i) {
        struct sigaction currentAction;
        sigaction(Catch::signalDefs[i].id, nullptr, &currentAction);
        EXPECT_EQ(sigismember(&currentAction.sa_mask, SIGUSR1), 1)
            << "Signal " << Catch::signalDefs[i].name << " mask does not contain SIGUSR1";
    }

    // Clean up
    for (std::size_t i = 0; i < 6; ++i) {
        struct sigaction defaultAction;
        std::memset(&defaultAction, 0, sizeof(defaultAction));
        defaultAction.sa_handler = SIG_DFL;
        sigaction(Catch::signalDefs[i].id, &defaultAction, nullptr);
    }
}

TEST_F(RestorePreviousSignalHandlersTest_483, CoversAllSixSignals_483) {
    // Verify that signalDefs contains the expected signal IDs
    int expectedSignals[] = {SIGINT, SIGILL, SIGFPE, SIGSEGV, SIGTERM, SIGABRT};
    for (std::size_t i = 0; i < 6; ++i) {
        EXPECT_EQ(Catch::signalDefs[i].id, expectedSignals[i])
            << "signalDefs[" << i << "] has unexpected signal id";
    }
}

TEST_F(RestorePreviousSignalHandlersTest_483, CallingRestoreTwiceIsIdempotent_483) {
    for (std::size_t i = 0; i < 6; ++i) {
        std::memset(&Catch::oldSigActions[i], 0, sizeof(struct sigaction));
        Catch::oldSigActions[i].sa_handler = SIG_DFL;
        sigemptyset(&Catch::oldSigActions[i].sa_mask);
    }
    std::memset(&Catch::oldSigStack, 0, sizeof(stack_t));
    Catch::oldSigStack.ss_flags = SS_DISABLE;

    Catch::restorePreviousSignalHandlers();
    Catch::restorePreviousSignalHandlers();

    // Verify all signals are still at SIG_DFL
    for (std::size_t i = 0; i < 6; ++i) {
        struct sigaction currentAction;
        sigaction(Catch::signalDefs[i].id, nullptr, &currentAction);
        EXPECT_EQ(currentAction.sa_handler, SIG_DFL)
            << "Signal " << Catch::signalDefs[i].name << " not SIG_DFL after double restore";
    }
}

TEST_F(RestorePreviousSignalHandlersTest_483, RestoresDisabledAltStack_483) {
    // Set old stack to disabled
    std::memset(&Catch::oldSigStack, 0, sizeof(stack_t));
    Catch::oldSigStack.ss_flags = SS_DISABLE;

    for (std::size_t i = 0; i < 6; ++i) {
        std::memset(&Catch::oldSigActions[i], 0, sizeof(struct sigaction));
        Catch::oldSigActions[i].sa_handler = SIG_DFL;
    }

    Catch::restorePreviousSignalHandlers();

    stack_t currentStack;
    sigaltstack(nullptr, &currentStack);
    EXPECT_TRUE(currentStack.ss_flags & SS_DISABLE);
}

TEST_F(RestorePreviousSignalHandlersTest_483, RestoresMixedHandlers_483) {
    // Set different handlers for different signals
    Catch::oldSigActions[0].sa_handler = SIG_DFL;
    sigemptyset(&Catch::oldSigActions[0].sa_mask);
    Catch::oldSigActions[0].sa_flags = 0;

    Catch::oldSigActions[1].sa_handler = SIG_IGN;
    sigemptyset(&Catch::oldSigActions[1].sa_mask);
    Catch::oldSigActions[1].sa_flags = 0;

    Catch::oldSigActions[2].sa_handler = dummyHandler;
    sigemptyset(&Catch::oldSigActions[2].sa_mask);
    Catch::oldSigActions[2].sa_flags = 0;

    Catch::oldSigActions[3].sa_handler = anotherDummyHandler;
    sigemptyset(&Catch::oldSigActions[3].sa_mask);
    Catch::oldSigActions[3].sa_flags = 0;

    Catch::oldSigActions[4].sa_handler = SIG_DFL;
    sigemptyset(&Catch::oldSigActions[4].sa_mask);
    Catch::oldSigActions[4].sa_flags = 0;

    Catch::oldSigActions[5].sa_handler = SIG_IGN;
    sigemptyset(&Catch::oldSigActions[5].sa_mask);
    Catch::oldSigActions[5].sa_flags = 0;

    std::memset(&Catch::oldSigStack, 0, sizeof(stack_t));
    Catch::oldSigStack.ss_flags = SS_DISABLE;

    Catch::restorePreviousSignalHandlers();

    struct sigaction act;
    sigaction(Catch::signalDefs[0].id, nullptr, &act);
    EXPECT_EQ(act.sa_handler, SIG_DFL);

    sigaction(Catch::signalDefs[1].id, nullptr, &act);
    EXPECT_EQ(act.sa_handler, SIG_IGN);

    sigaction(Catch::signalDefs[2].id, nullptr, &act);
    EXPECT_EQ(act.sa_handler, dummyHandler);

    sigaction(Catch::signalDefs[3].id, nullptr, &act);
    EXPECT_EQ(act.sa_handler, anotherDummyHandler);

    sigaction(Catch::signalDefs[4].id, nullptr, &act);
    EXPECT_EQ(act.sa_handler, SIG_DFL);

    sigaction(Catch::signalDefs[5].id, nullptr, &act);
    EXPECT_EQ(act.sa_handler, SIG_IGN);

    // Clean up
    for (std::size_t i = 0; i < 6; ++i) {
        struct sigaction defaultAction;
        std::memset(&defaultAction, 0, sizeof(defaultAction));
        defaultAction.sa_handler = SIG_DFL;
        sigaction(Catch::signalDefs[i].id, &defaultAction, nullptr);
    }
}
