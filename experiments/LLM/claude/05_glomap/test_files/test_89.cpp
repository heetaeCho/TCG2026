#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <functional>
#include <string>
#include <vector>
#include <utility>
#include <cstdlib>

// Replicate the dispatch logic from main for testability
typedef std::function<int(int, char**)> command_func_t;

static int ShowHelp(const std::vector<std::pair<std::string, command_func_t>>& commands) {
    return EXIT_SUCCESS;
}

class CommandDispatcher {
public:
    std::vector<std::pair<std::string, command_func_t>> commands;

    int dispatch(int argc, char** argv) {
        if (argc == 1) {
            return ShowHelp(commands);
        }

        const std::string command = argv[1];
        if (command == "help" || command == "-h" || command == "--help") {
            return ShowHelp(commands);
        } else {
            command_func_t matched_command_func = nullptr;
            for (const auto& command_func : commands) {
                if (command == command_func.first) {
                    matched_command_func = command_func.second;
                    break;
                }
            }
            if (matched_command_func == nullptr) {
                return EXIT_FAILURE;
            } else {
                int command_argc = argc - 1;
                char** command_argv = &argv[1];
                command_argv[0] = argv[0];
                return matched_command_func(command_argc, command_argv);
            }
        }
        return ShowHelp(commands);
    }
};

class GlomapDispatchTest_89 : public ::testing::Test {
protected:
    CommandDispatcher dispatcher;
    int mockCallCount;
    int lastArgc;
    
    void SetUp() override {
        mockCallCount = 0;
        lastArgc = 0;
        
        dispatcher.commands.emplace_back("mapper", [this](int argc, char** argv) -> int {
            mockCallCount++;
            lastArgc = argc;
            return 0;
        });
        dispatcher.commands.emplace_back("mapper_resume", [this](int argc, char** argv) -> int {
            mockCallCount++;
            lastArgc = argc;
            return 42;
        });
        dispatcher.commands.emplace_back("rotation_averager", [this](int argc, char** argv) -> int {
            mockCallCount++;
            lastArgc = argc;
            return 7;
        });
    }
    
    std::vector<char*> makeArgv(std::vector<std::string>& args) {
        std::vector<char*> argv;
        for (auto& s : args) {
            argv.push_back(&s[0]);
        }
        argv.push_back(nullptr);
        return argv;
    }
};

TEST_F(GlomapDispatchTest_89, NoArguments_ShowsHelp_89) {
    std::vector<std::string> args = {"glomap"};
    auto argv = makeArgv(args);
    int result = dispatcher.dispatch(static_cast<int>(args.size()), argv.data());
    EXPECT_EQ(result, EXIT_SUCCESS);
    EXPECT_EQ(mockCallCount, 0);
}

TEST_F(GlomapDispatchTest_89, HelpCommand_ShowsHelp_89) {
    std::vector<std::string> args = {"glomap", "help"};
    auto argv = makeArgv(args);
    int result = dispatcher.dispatch(static_cast<int>(args.size()), argv.data());
    EXPECT_EQ(result, EXIT_SUCCESS);
    EXPECT_EQ(mockCallCount, 0);
}

TEST_F(GlomapDispatchTest_89, DashHFlag_ShowsHelp_89) {
    std::vector<std::string> args = {"glomap", "-h"};
    auto argv = makeArgv(args);
    int result = dispatcher.dispatch(static_cast<int>(args.size()), argv.data());
    EXPECT_EQ(result, EXIT_SUCCESS);
    EXPECT_EQ(mockCallCount, 0);
}

TEST_F(GlomapDispatchTest_89, DoubleDashHelpFlag_ShowsHelp_89) {
    std::vector<std::string> args = {"glomap", "--help"};
    auto argv = makeArgv(args);
    int result = dispatcher.dispatch(static_cast<int>(args.size()), argv.data());
    EXPECT_EQ(result, EXIT_SUCCESS);
    EXPECT_EQ(mockCallCount, 0);
}

TEST_F(GlomapDispatchTest_89, MapperCommand_DispatchesToMapper_89) {
    std::vector<std::string> args = {"glomap", "mapper"};
    auto argv = makeArgv(args);
    int result = dispatcher.dispatch(static_cast<int>(args.size()), argv.data());
    EXPECT_EQ(result, 0);
    EXPECT_EQ(mockCallCount, 1);
}

TEST_F(GlomapDispatchTest_89, MapperResumeCommand_DispatchesToMapperResume_89) {
    std::vector<std::string> args = {"glomap", "mapper_resume"};
    auto argv = makeArgv(args);
    int result = dispatcher.dispatch(static_cast<int>(args.size()), argv.data());
    EXPECT_EQ(result, 42);
    EXPECT_EQ(mockCallCount, 1);
}

TEST_F(GlomapDispatchTest_89, RotationAveragerCommand_Dispatches_89) {
    std::vector<std::string> args = {"glomap", "rotation_averager"};
    auto argv = makeArgv(args);
    int result = dispatcher.dispatch(static_cast<int>(args.size()), argv.data());
    EXPECT_EQ(result, 7);
    EXPECT_EQ(mockCallCount, 1);
}

TEST_F(GlomapDispatchTest_89, UnknownCommand_ReturnsFailure_89) {
    std::vector<std::string> args = {"glomap", "unknown_command"};
    auto argv = makeArgv(args);
    int result = dispatcher.dispatch(static_cast<int>(args.size()), argv.data());
    EXPECT_EQ(result, EXIT_FAILURE);
    EXPECT_EQ(mockCallCount, 0);
}

TEST_F(GlomapDispatchTest_89, MapperWithExtraArgs_PassesReducedArgc_89) {
    std::vector<std::string> args = {"glomap", "mapper", "--database_path", "/tmp/db"};
    auto argv = makeArgv(args);
    int result = dispatcher.dispatch(static_cast<int>(args.size()), argv.data());
    EXPECT_EQ(result, 0);
    EXPECT_EQ(mockCallCount, 1);
    EXPECT_EQ(lastArgc, 3); // argc - 1 = 4 - 1 = 3
}

TEST_F(GlomapDispatchTest_89, MapperCommand_Argv0IsProgName_89) {
    std::string progName = "glomap";
    std::string cmdName = "mapper";
    char* rawArgv[] = {&progName[0], &cmdName[0], nullptr};
    
    char* expectedProgName = rawArgv[0];
    
    dispatcher.commands.clear();
    dispatcher.commands.emplace_back("mapper", [expectedProgName](int argc, char** argv) -> int {
        // argv[0] should be the original program name
        EXPECT_EQ(argv[0], expectedProgName);
        return 0;
    });
    
    int result = dispatcher.dispatch(2, rawArgv);
    EXPECT_EQ(result, 0);
}

TEST_F(GlomapDispatchTest_89, EmptyStringCommand_ReturnsFailure_89) {
    std::vector<std::string> args = {"glomap", ""};
    auto argv = makeArgv(args);
    int result = dispatcher.dispatch(static_cast<int>(args.size()), argv.data());
    EXPECT_EQ(result, EXIT_FAILURE);
    EXPECT_EQ(mockCallCount, 0);
}

TEST_F(GlomapDispatchTest_89, CaseSensitiveCommand_ReturnsFailure_89) {
    std::vector<std::string> args = {"glomap", "MAPPER"};
    auto argv = makeArgv(args);
    int result = dispatcher.dispatch(static_cast<int>(args.size()), argv.data());
    EXPECT_EQ(result, EXIT_FAILURE);
    EXPECT_EQ(mockCallCount, 0);
}

TEST_F(GlomapDispatchTest_89, PartialCommandName_ReturnsFailure_89) {
    std::vector<std::string> args = {"glomap", "map"};
    auto argv = makeArgv(args);
    int result = dispatcher.dispatch(static_cast<int>(args.size()), argv.data());
    EXPECT_EQ(result, EXIT_FAILURE);
    EXPECT_EQ(mockCallCount, 0);
}

TEST_F(GlomapDispatchTest_89, CommandWithLeadingSpace_ReturnsFailure_89) {
    std::vector<std::string> args = {"glomap", " mapper"};
    auto argv = makeArgv(args);
    int result = dispatcher.dispatch(static_cast<int>(args.size()), argv.data());
    EXPECT_EQ(result, EXIT_FAILURE);
    EXPECT_EQ(mockCallCount, 0);
}

TEST_F(GlomapDispatchTest_89, FirstMatchIsUsed_89) {
    // Verify that the first matching command is selected
    int firstCalled = 0;
    int secondCalled = 0;
    
    dispatcher.commands.clear();
    dispatcher.commands.emplace_back("dup", [&firstCalled](int, char**) -> int {
        firstCalled++;
        return 1;
    });
    dispatcher.commands.emplace_back("dup", [&secondCalled](int, char**) -> int {
        secondCalled++;
        return 2;
    });
    
    std::vector<std::string> args = {"glomap", "dup"};
    auto argv = makeArgv(args);
    int result = dispatcher.dispatch(static_cast<int>(args.size()), argv.data());
    EXPECT_EQ(result, 1);
    EXPECT_EQ(firstCalled, 1);
    EXPECT_EQ(secondCalled, 0);
}

TEST_F(GlomapDispatchTest_89, HelpIsNotDispatchedAsCommand_89) {
    // Even if "help" is added as a command, the special handling should take priority
    int helpCalled = 0;
    dispatcher.commands.emplace_back("help", [&helpCalled](int, char**) -> int {
        helpCalled++;
        return 99;
    });
    
    std::vector<std::string> args = {"glomap", "help"};
    auto argv = makeArgv(args);
    int result = dispatcher.dispatch(static_cast<int>(args.size()), argv.data());
    EXPECT_EQ(result, EXIT_SUCCESS);
    EXPECT_EQ(helpCalled, 0);
}
