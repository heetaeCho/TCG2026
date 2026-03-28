// File: message_builder_stream_tests_107.cpp

#include <gtest/gtest.h>
#include <type_traits>
#include <utility>
#include <string>

// Include the provided header path from the prompt
#include "Catch2/src/catch2/catch_message.hpp"

using Catch::MessageBuilder;
using Catch::MessageStream;
using Catch::StringRef;
using Catch::SourceLineInfo;
using Catch::ResultWas;

namespace {

// Helper to construct a MessageBuilder via its public constructor.
// We avoid depending on specific enum values by static_cast.
MessageBuilder MakeBuilder() {
    return MessageBuilder(
        StringRef("TEST_MACRO"),
        SourceLineInfo{__FILE__, static_cast<std::size_t>(__LINE__)},
        static_cast<ResultWas::OfType>(0));
}

} // namespace

// ---------- Compile-time interface checks (no side effects) ----------
static_assert(std::is_same<
                  decltype(std::declval<MessageStream&>() << 123),
                  MessageStream&>::value,
              "Lvalue insertion on MessageStream must return MessageStream&");

static_assert(std::is_same<
                  decltype(std::declval<MessageBuilder&&>() << 123),
                  MessageBuilder&&>::value,
              "Rvalue insertion on MessageBuilder must return MessageBuilder&&");

// ---------- Test fixture ----------
class MessageBuilderTest_107 : public ::testing::Test {};

// Verifies that inserting into an lvalue MessageBuilder resolves to the base
// MessageStream::operator<< and returns a MessageStream& to the same object.
TEST_F(MessageBuilderTest_107, LvalueInsertionReturnsBaseRef_107) {
    MessageBuilder b = MakeBuilder();

    MessageStream& baseRef = (b << "abc");
    // Returned reference should alias the same base subobject
    EXPECT_EQ(&baseRef, static_cast<MessageStream*>(&b));

    // Chaining via the base should continue to work
    (void)(baseRef << 42 << std::string("x"));
    SUCCEED(); // Observable via type/aliasing; stream contents are not asserted per interface.
}

// Verifies that inserting into an rvalue returns MessageBuilder&& and aliases
// the same object (i.e., the operator returns *this as an rvalue).
TEST_F(MessageBuilderTest_107, RvalueInsertionReturnsRvalueBuilder_107) {
    MessageBuilder b = MakeBuilder();

    auto&& r = std::move(b) << "hello";
    EXPECT_EQ(&r, &b) << "Rvalue operator<< should return the same object";

    auto&& r2 = std::move(r) << 99;
    EXPECT_EQ(&r2, &b) << "Chained rvalue insertions should still alias the same object";

    // Further chaining on rvalue should compile and be valid
    (void)(std::move(r2) << std::string("bye"));
    SUCCEED();
}

// Mixing lvalue and rvalue insertions should be valid and keep identity.
TEST_F(MessageBuilderTest_107, MixedLvalueThenRvalueInsertion_107) {
    MessageBuilder b = MakeBuilder();

    // Start with lvalue insertion (hits base operator<<)
    MessageStream& baseRef = (b << "first");
    EXPECT_EQ(&baseRef, static_cast<MessageStream*>(&b));

    // Then switch to rvalue insertion (hits MessageBuilder&& operator<<)
    auto&& r = std::move(b) << "second" << 3.14;
    EXPECT_EQ(&r, &b);

    SUCCEED();
}

// Ensure that a temporary MessageBuilder supports chained rvalue insertions.
// This exercises the move-qualified operator<< on a prvalue.
TEST_F(MessageBuilderTest_107, TemporaryBuilderChaining_107) {
    auto&& tmp = MakeBuilder() << "a" << 1 << std::string("b");
    // Binding to auto&& extends the temporary's lifetime within this scope;
    // primary check is that this compiles and runs without UB.
    (void)tmp;
    SUCCEED();
}

// The templated operator<< should accept a variety of common types.
TEST_F(MessageBuilderTest_107, SupportsVariousInsertedTypes_107) {
    MessageBuilder b = MakeBuilder();
    (void)(b << 0           // int
             << 'c'         // char
             << 123u        // unsigned
             << 45ll        // long long
             << 3.14f       // float
             << 2.718       // double
             << std::string("std")  // std::string
             << "cstr");    // C string
    SUCCEED();
}
