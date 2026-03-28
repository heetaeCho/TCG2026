#include <gtest/gtest.h>

#include "catch2/catch_message.hpp"

#include <string>



using namespace Catch;



// Mock MessageStream for external interactions verification if needed

class MockMessageStream : public MessageStream {

public:

    MOCK_METHOD1(operator<<, MessageStream&(const std::string& value));

};



TEST_F(MessageBuilderTest_107, ConstructorInitializesInfo_107) {

    SourceLineInfo lineInfo("test_file.cpp", 42);

    MessageBuilder builder("TEST_MACRO", lineInfo, ResultWas::OfType::ExpressionFailed);



    EXPECT_EQ(builder.m_info.m_macroName, "TEST_MACRO");

    EXPECT_EQ(builder.m_info.m_lineInfo.file, "test_file.cpp");

    EXPECT_EQ(builder.m_info.m_lineInfo.line, 42);

    EXPECT_EQ(builder.m_info.m_resultType, ResultWas::OfType::ExpressionFailed);

}



TEST_F(MessageBuilderTest_107, OperatorLeftShiftAppendsValueToStringStream_107) {

    SourceLineInfo lineInfo("test_file.cpp", 42);

    MessageBuilder builder("TEST_MACRO", lineInfo, ResultWas::OfType::ExpressionFailed);



    builder << "Hello" << " " << "World";



    EXPECT_EQ(builder.m_stream.str(), "Hello World");

}



TEST_F(MessageBuilderTest_107, OperatorLeftShiftChainsCorrectly_107) {

    SourceLineInfo lineInfo("test_file.cpp", 42);

    MessageBuilder builder("TEST_MACRO", lineInfo, ResultWas::OfType::ExpressionFailed);



    auto&& result = builder << "Hello" << " ";



    EXPECT_EQ(builder.m_stream.str(), "Hello ");

    EXPECT_TRUE(&result == &builder); // Check if chaining works

}



TEST_F(MessageBuilderTest_107, OperatorLeftShiftHandlesVariousTypes_107) {

    SourceLineInfo lineInfo("test_file.cpp", 42);

    MessageBuilder builder("TEST_MACRO", lineInfo, ResultWas::OfType::ExpressionFailed);



    builder << 42 << " " << 3.14 << " " << true;



    EXPECT_EQ(builder.m_stream.str(), "42 3.14 1");

}



// Boundary condition tests

TEST_F(MessageBuilderTest_107, OperatorLeftShiftHandlesEmptyString_107) {

    SourceLineInfo lineInfo("test_file.cpp", 42);

    MessageBuilder builder("TEST_MACRO", lineInfo, ResultWas::OfType::ExpressionFailed);



    builder << "";



    EXPECT_EQ(builder.m_stream.str(), "");

}



TEST_F(MessageBuilderTest_107, OperatorLeftShiftHandlesLargeNumber_107) {

    SourceLineInfo lineInfo("test_file.cpp", 42);

    MessageBuilder builder("TEST_MACRO", lineInfo, ResultWas::OfType::ExpressionFailed);



    builder << 987654321;



    EXPECT_EQ(builder.m_stream.str(), "987654321");

}



// Exceptional or error cases (if observable through the interface)

// In this case, there are no obvious exceptional/error cases based on the provided interface.



// Verification of external interactions

TEST_F(MessageBuilderTest_107, OperatorLeftShiftDoesNotCallExternalMethods_107) {

    SourceLineInfo lineInfo("test_file.cpp", 42);

    MockMessageStream mockStream;

    MessageBuilder builder("TEST_MACRO", lineInfo, ResultWas::OfType::ExpressionFailed);



    EXPECT_CALL(mockStream, operator<<(_)).Times(0); // Expect no calls to external methods



    builder << "Hello";



    EXPECT_EQ(builder.m_stream.str(), "Hello");

}
