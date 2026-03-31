#include <gtest/gtest.h>
#include <string>
#include <sstream>

#include "catch2/catch_message.hpp"
#include "catch2/internal/catch_source_line_info.hpp"
#include "catch2/interfaces/catch_interfaces_capture.hpp"
#include "catch2/internal/catch_result_type.hpp"

class MessageBuilderTest_107 : public ::testing::Test {
protected:
    Catch::SourceLineInfo makeSourceLineInfo() {
        return Catch::SourceLineInfo("test_file.cpp", 42);
    }
};

TEST_F(MessageBuilderTest_107, ConstructMessageBuilder_107) {
    Catch::MessageBuilder builder("TEST_MACRO", makeSourceLineInfo(), Catch::ResultWas::Info);
    // Should construct without throwing
    SUCCEED();
}

TEST_F(MessageBuilderTest_107, StreamStringValue_107) {
    Catch::MessageBuilder builder("TEST_MACRO", makeSourceLineInfo(), Catch::ResultWas::Info);
    auto&& result = std::move(builder) << "hello";
    // The operator<< should return an rvalue reference to MessageBuilder
    // We verify it doesn't crash and the stream contains the value
    std::string streamContent = result.m_stream.str();
    EXPECT_NE(streamContent.find("hello"), std::string::npos);
}

TEST_F(MessageBuilderTest_107, StreamIntegerValue_107) {
    Catch::MessageBuilder builder("TEST_MACRO", makeSourceLineInfo(), Catch::ResultWas::Info);
    auto&& result = std::move(builder) << 42;
    std::string streamContent = result.m_stream.str();
    EXPECT_NE(streamContent.find("42"), std::string::npos);
}

TEST_F(MessageBuilderTest_107, StreamDoubleValue_107) {
    Catch::MessageBuilder builder("TEST_MACRO", makeSourceLineInfo(), Catch::ResultWas::Info);
    auto&& result = std::move(builder) << 3.14;
    std::string streamContent = result.m_stream.str();
    EXPECT_NE(streamContent.find("3.14"), std::string::npos);
}

TEST_F(MessageBuilderTest_107, StreamMultipleValues_107) {
    Catch::MessageBuilder builder("TEST_MACRO", makeSourceLineInfo(), Catch::ResultWas::Info);
    auto&& result = std::move(builder) << "value=" << 100;
    std::string streamContent = result.m_stream.str();
    EXPECT_NE(streamContent.find("value="), std::string::npos);
    EXPECT_NE(streamContent.find("100"), std::string::npos);
}

TEST_F(MessageBuilderTest_107, StreamEmptyString_107) {
    Catch::MessageBuilder builder("TEST_MACRO", makeSourceLineInfo(), Catch::ResultWas::Info);
    auto&& result = std::move(builder) << "";
    // Should not crash with empty string
    SUCCEED();
}

TEST_F(MessageBuilderTest_107, StreamCharValue_107) {
    Catch::MessageBuilder builder("TEST_MACRO", makeSourceLineInfo(), Catch::ResultWas::Info);
    auto&& result = std::move(builder) << 'A';
    std::string streamContent = result.m_stream.str();
    EXPECT_NE(streamContent.find("A"), std::string::npos);
}

TEST_F(MessageBuilderTest_107, StreamBoolValue_107) {
    Catch::MessageBuilder builder("TEST_MACRO", makeSourceLineInfo(), Catch::ResultWas::Info);
    auto&& result = std::move(builder) << true;
    std::string streamContent = result.m_stream.str();
    // bool streamed as 1 or "true" depending on format
    EXPECT_FALSE(streamContent.empty());
}

TEST_F(MessageBuilderTest_107, StreamNegativeInteger_107) {
    Catch::MessageBuilder builder("TEST_MACRO", makeSourceLineInfo(), Catch::ResultWas::Info);
    auto&& result = std::move(builder) << -99;
    std::string streamContent = result.m_stream.str();
    EXPECT_NE(streamContent.find("-99"), std::string::npos);
}

TEST_F(MessageBuilderTest_107, StreamLongString_107) {
    Catch::MessageBuilder builder("TEST_MACRO", makeSourceLineInfo(), Catch::ResultWas::Info);
    std::string longStr(1000, 'x');
    auto&& result = std::move(builder) << longStr;
    std::string streamContent = result.m_stream.str();
    EXPECT_NE(streamContent.find(longStr), std::string::npos);
}

TEST_F(MessageBuilderTest_107, MessageInfoMacroNamePreserved_107) {
    Catch::MessageBuilder builder("MY_MACRO", makeSourceLineInfo(), Catch::ResultWas::Info);
    EXPECT_EQ(builder.m_info.macroName, "MY_MACRO");
}

TEST_F(MessageBuilderTest_107, MessageInfoLineInfoPreserved_107) {
    auto lineInfo = makeSourceLineInfo();
    Catch::MessageBuilder builder("TEST_MACRO", lineInfo, Catch::ResultWas::Info);
    EXPECT_EQ(builder.m_info.lineInfo.line, 42u);
}

TEST_F(MessageBuilderTest_107, MessageInfoTypePreserved_107) {
    Catch::MessageBuilder builder("TEST_MACRO", makeSourceLineInfo(), Catch::ResultWas::Warning);
    EXPECT_EQ(builder.m_info.type, Catch::ResultWas::Warning);
}

TEST_F(MessageBuilderTest_107, StreamZeroValue_107) {
    Catch::MessageBuilder builder("TEST_MACRO", makeSourceLineInfo(), Catch::ResultWas::Info);
    auto&& result = std::move(builder) << 0;
    std::string streamContent = result.m_stream.str();
    EXPECT_NE(streamContent.find("0"), std::string::npos);
}

TEST_F(MessageBuilderTest_107, StreamCStringPointer_107) {
    Catch::MessageBuilder builder("TEST_MACRO", makeSourceLineInfo(), Catch::ResultWas::Info);
    const char* cstr = "c_string_test";
    auto&& result = std::move(builder) << cstr;
    std::string streamContent = result.m_stream.str();
    EXPECT_NE(streamContent.find("c_string_test"), std::string::npos);
}

TEST_F(MessageBuilderTest_107, StreamUnsignedValue_107) {
    Catch::MessageBuilder builder("TEST_MACRO", makeSourceLineInfo(), Catch::ResultWas::Info);
    unsigned int val = 12345u;
    auto&& result = std::move(builder) << val;
    std::string streamContent = result.m_stream.str();
    EXPECT_NE(streamContent.find("12345"), std::string::npos);
}

TEST_F(MessageBuilderTest_107, ChainedStreamOperations_107) {
    Catch::MessageBuilder builder("TEST_MACRO", makeSourceLineInfo(), Catch::ResultWas::Info);
    auto&& result = std::move(builder) << "a" << "b" << "c" << 1 << 2 << 3;
    std::string streamContent = result.m_stream.str();
    EXPECT_NE(streamContent.find("abc123"), std::string::npos);
}
