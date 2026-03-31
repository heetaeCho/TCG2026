#include <gtest/gtest.h>
#include <ostream>
#include <string>
#include <sstream>

// Include the header under test
#include "./TestProjects/Catch2/fuzzing/NullOStream.h"

// Test fixture for NullOStream
class NullOStreamTest_19 : public ::testing::Test {
protected:
    NullOStream stream;
};

// Test that NullOStream can be constructed without errors
TEST_F(NullOStreamTest_19, Construction_19) {
    NullOStream os;
    // Should construct without throwing
    SUCCEED();
}

// Test that rdbuf() returns a non-null pointer
TEST_F(NullOStreamTest_19, RdbufReturnsNonNull_19) {
    NullStreambuf* buf = stream.rdbuf();
    ASSERT_NE(buf, nullptr);
}

// Test that rdbuf() returns a consistent pointer (same object each call)
TEST_F(NullOStreamTest_19, RdbufReturnsConsistentPointer_19) {
    NullStreambuf* buf1 = stream.rdbuf();
    NullStreambuf* buf2 = stream.rdbuf();
    EXPECT_EQ(buf1, buf2);
}

// Test that writing to the stream does not cause errors
TEST_F(NullOStreamTest_19, WriteStringDoesNotFail_19) {
    stream << "Hello, World!";
    EXPECT_TRUE(stream.good());
}

// Test that writing integers does not cause errors
TEST_F(NullOStreamTest_19, WriteIntegerDoesNotFail_19) {
    stream << 42;
    EXPECT_TRUE(stream.good());
}

// Test that writing floating point does not cause errors
TEST_F(NullOStreamTest_19, WriteFloatDoesNotFail_19) {
    stream << 3.14159;
    EXPECT_TRUE(stream.good());
}

// Test that writing an empty string does not cause errors
TEST_F(NullOStreamTest_19, WriteEmptyStringDoesNotFail_19) {
    stream << "";
    EXPECT_TRUE(stream.good());
}

// Test that writing a large amount of data does not cause errors
TEST_F(NullOStreamTest_19, WriteLargeDataDoesNotFail_19) {
    std::string largeStr(10000, 'A');
    stream << largeStr;
    EXPECT_TRUE(stream.good());
}

// Test that endl/flush does not cause errors
TEST_F(NullOStreamTest_19, EndlDoesNotFail_19) {
    stream << "test" << std::endl;
    EXPECT_TRUE(stream.good());
}

// Test that flush does not cause errors
TEST_F(NullOStreamTest_19, FlushDoesNotFail_19) {
    stream << std::flush;
    EXPECT_TRUE(stream.good());
}

// Test that the stream is an std::ostream
TEST_F(NullOStreamTest_19, IsOstream_19) {
    std::ostream* os = &stream;
    ASSERT_NE(os, nullptr);
    *os << "Writing via base class pointer";
    EXPECT_TRUE(os->good());
}

// Test that write() method works without error
TEST_F(NullOStreamTest_19, WriteMethodDoesNotFail_19) {
    const char data[] = "binary data\0with null";
    stream.write(data, sizeof(data));
    EXPECT_TRUE(stream.good());
}

// Test that put() method works without error
TEST_F(NullOStreamTest_19, PutMethodDoesNotFail_19) {
    stream.put('c');
    EXPECT_TRUE(stream.good());
}

// Test that multiple sequential writes don't cause errors
TEST_F(NullOStreamTest_19, MultipleWritesDoNotFail_19) {
    for (int i = 0; i < 1000; ++i) {
        stream << "iteration " << i << "\n";
    }
    EXPECT_TRUE(stream.good());
}

// Test that NullOStream doesn't produce any output (it's /dev/null equivalent)
// We verify this indirectly by checking the stream state remains good
TEST_F(NullOStreamTest_19, StreamStateRemainsGoodAfterWrites_19) {
    stream << "test1";
    EXPECT_FALSE(stream.fail());
    EXPECT_FALSE(stream.bad());
    stream << 123;
    EXPECT_FALSE(stream.fail());
    EXPECT_FALSE(stream.bad());
    stream << std::endl;
    EXPECT_FALSE(stream.fail());
    EXPECT_FALSE(stream.bad());
}

// Test that tellp works or at least doesn't crash
TEST_F(NullOStreamTest_19, TellpDoesNotCrash_19) {
    // tellp may return -1 for null streams, but should not crash
    auto pos = stream.tellp();
    // We don't assert a specific value since it's implementation-defined
    (void)pos;
    SUCCEED();
}

// Test copy of NullOStream is not possible (streams are non-copyable)
// This is a compile-time property, so we just verify the stream works standalone
TEST_F(NullOStreamTest_19, IndependentInstances_19) {
    NullOStream os1;
    NullOStream os2;
    os1 << "to os1";
    os2 << "to os2";
    EXPECT_TRUE(os1.good());
    EXPECT_TRUE(os2.good());
}
