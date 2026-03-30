// File: tests/json_value_writer_writeObject_rvalue_535.cpp

#include <gtest/gtest.h>
#include <sstream>
#include <string>

// Header under test
#include <catch2/internal/catch_jsonwriter.hpp>

using namespace Catch;

class JsonValueWriterWriteObjectTest_535 : public ::testing::Test {};

// [535] Normal operation: calling rvalue-qualified writeObject on a temporary
// should produce an empty JSON object with correct braces and newline/indent.
TEST_F(JsonValueWriterWriteObjectTest_535, WritesEmptyObjectFromTemporary_535) {
    std::ostringstream os;

    {
        // rvalue call (temporary)
        auto obj = JsonValueWriter{ os }.writeObject();
        // nothing else written; let ~JsonObjectWriter close the object
        (void)obj;
    }

    // For indent level 0: "{\n}"
    EXPECT_EQ(os.str(), "{\n}");
}

// [535] Normal operation: calling rvalue-qualified writeObject on an rvalue
// created from an lvalue should behave the same.
TEST_F(JsonValueWriterWriteObjectTest_535, WritesEmptyObjectFromMovedLvalue_535) {
    std::ostringstream os;

    {
        JsonValueWriter vw{ os };
        auto obj = std::move(vw).writeObject(); // rvalue-qualified overload
        (void)obj;
    }

    EXPECT_EQ(os.str(), "{\n}");
}

// [535] Boundary/formatting: indent level is propagated to the returned
// JsonObjectWriter, affecting the closing brace indentation.
TEST_F(JsonValueWriterWriteObjectTest_535, PropagatesIndentLevelToReturnedObject_535) {
    std::ostringstream os;

    {
        // Start with non-zero indent (e.g., 2)
        JsonValueWriter vw{ os, /*indent_level*/ 2 };
        auto obj = std::move(vw).writeObject();
        (void)obj;
    }

    // For indent level 2, closing brace is indented by 2 levels (2 spaces per level)
    // -> 4 spaces before the closing '}'.
    EXPECT_EQ(os.str(), "{\n    }");
}

// [535] Interaction/observable side-effect: the returned JsonObjectWriter
// can be used to write a key-value pair; this validates the object is active
// and correctly configured by writeObject().
TEST_F(JsonValueWriterWriteObjectTest_535, ReturnedObjectIsUsableForKeyValue_535) {
    std::ostringstream os;

    {
        auto obj = JsonValueWriter{ os }.writeObject();
        // Write a boolean value under key "ok"
        // JsonObjectWriter::write returns a JsonValueWriter for the value,
        // on which we can call rvalue-qualified write(bool)
        std::move(obj.write("ok")).write(true);
    }

    // Expected pretty-printed JSON (2-space indent for the member line)
    EXPECT_EQ(os.str(), "{\n  \"ok\": true\n}");
}

// [535] Exceptional-ish/move semantics (observable effect only):
// Moving the returned JsonObjectWriter should keep only the destination active,
// so braces are still balanced once — ensures the object from writeObject() is valid
// even after being moved.
TEST_F(JsonValueWriterWriteObjectTest_535, MovedReturnedObjectClosesOnce_535) {
    std::ostringstream os;

    {
        auto obj1 = JsonValueWriter{ os }.writeObject();
        auto obj2 = std::move(obj1); // move the returned object
        (void)obj2;
    }

    // Still exactly one object written
    EXPECT_EQ(os.str(), "{\n}");
}
