#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <streambuf>
#include <string>
#include <limits>
#include <functional>

// We need to include the actual header
#include "JsonBox/OutputFilter.h"

namespace {

// A simple inserter functor that just puts the character to the destination streambuf
struct SimpleInserter {
    int operator()(std::streambuf& dest, std::streambuf::int_type ch) {
        return dest.sputc(static_cast<char>(ch));
    }
};

// An inserter that doubles every character (writes it twice)
struct DoublingInserter {
    int operator()(std::streambuf& dest, std::streambuf::int_type ch) {
        dest.sputc(static_cast<char>(ch));
        return dest.sputc(static_cast<char>(ch));
    }
};

// An inserter that tracks how many times it was called
struct CountingInserter {
    int callCount = 0;
    int operator()(std::streambuf& dest, std::streambuf::int_type ch) {
        ++callCount;
        return dest.sputc(static_cast<char>(ch));
    }
};

// An inserter that always returns EOF to simulate failure
struct FailingInserter {
    int operator()(std::streambuf& dest, std::streambuf::int_type ch) {
        (void)dest;
        (void)ch;
        return std::char_traits<char>::eof();
    }
};

// An inserter that converts lowercase to uppercase
struct UpperCaseInserter {
    int operator()(std::streambuf& dest, std::streambuf::int_type ch) {
        char c = static_cast<char>(ch);
        if (c >= 'a' && c <= 'z') {
            c = c - 'a' + 'A';
        }
        return dest.sputc(c);
    }
};

class OutputFilterTest_7 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test: Constructor with destination and inserter
TEST_F(OutputFilterTest_7, ConstructorWithInserter_7) {
    std::stringbuf destBuf;
    SimpleInserter inserter;
    JsonBox::OutputFilter<SimpleInserter> filter(&destBuf, inserter);
    EXPECT_EQ(filter.getDestination(), &destBuf);
}

// Test: Constructor with destination only (no inserter)
TEST_F(OutputFilterTest_7, ConstructorWithoutInserter_7) {
    std::stringbuf destBuf;
    JsonBox::OutputFilter<SimpleInserter> filter(&destBuf);
    EXPECT_EQ(filter.getDestination(), &destBuf);
}

// Test: getDestination returns the correct destination
TEST_F(OutputFilterTest_7, GetDestination_7) {
    std::stringbuf destBuf;
    SimpleInserter inserter;
    JsonBox::OutputFilter<SimpleInserter> filter(&destBuf, inserter);
    EXPECT_EQ(filter.getDestination(), &destBuf);
}

// Test: getInserter returns a reference to the inserter
TEST_F(OutputFilterTest_7, GetInserterReturnsReference_7) {
    std::stringbuf destBuf;
    CountingInserter inserter;
    JsonBox::OutputFilter<CountingInserter> filter(&destBuf, inserter);
    // Access inserter through getInserter
    CountingInserter& ref = filter.getInserter();
    // Initially callCount should be 0 (or whatever was copied)
    EXPECT_EQ(ref.callCount, 0);
}

// Test: overflow with a normal character writes to destination
TEST_F(OutputFilterTest_7, OverflowNormalCharacter_7) {
    std::stringbuf destBuf;
    SimpleInserter inserter;
    JsonBox::OutputFilter<SimpleInserter> filter(&destBuf, inserter);

    auto result = filter.overflow('A');
    EXPECT_NE(result, std::char_traits<char>::eof());
    EXPECT_EQ(destBuf.str(), "A");
}

// Test: overflow with multiple characters
TEST_F(OutputFilterTest_7, OverflowMultipleCharacters_7) {
    std::stringbuf destBuf;
    SimpleInserter inserter;
    JsonBox::OutputFilter<SimpleInserter> filter(&destBuf, inserter);

    filter.overflow('H');
    filter.overflow('i');
    EXPECT_EQ(destBuf.str(), "Hi");
}

// Test: overflow with EOF character
TEST_F(OutputFilterTest_7, OverflowEOF_7) {
    std::stringbuf destBuf;
    SimpleInserter inserter;
    JsonBox::OutputFilter<SimpleInserter> filter(&destBuf, inserter);

    auto result = filter.overflow(std::char_traits<char>::eof());
    // When EOF is passed, sync() is called; result should indicate success (0 mapped or not eof)
    // The exact return depends on sync(), but it shouldn't crash
    // destBuf should be empty since no character was written
    EXPECT_EQ(destBuf.str(), "");
}

// Test: overflow with null character (boundary)
TEST_F(OutputFilterTest_7, OverflowNullCharacter_7) {
    std::stringbuf destBuf;
    SimpleInserter inserter;
    JsonBox::OutputFilter<SimpleInserter> filter(&destBuf, inserter);

    auto result = filter.overflow('\0');
    EXPECT_NE(result, std::char_traits<char>::eof());
    std::string expected(1, '\0');
    EXPECT_EQ(destBuf.str(), expected);
}

// Test: overflow with max unsigned char value (boundary)
TEST_F(OutputFilterTest_7, OverflowMaxChar_7) {
    std::stringbuf destBuf;
    SimpleInserter inserter;
    JsonBox::OutputFilter<SimpleInserter> filter(&destBuf, inserter);

    auto result = filter.overflow(static_cast<std::streambuf::int_type>(std::numeric_limits<unsigned char>::max()));
    EXPECT_NE(result, std::char_traits<char>::eof());
}

// Test: overflow with null destination
TEST_F(OutputFilterTest_7, OverflowNullDestination_7) {
    SimpleInserter inserter;
    JsonBox::OutputFilter<SimpleInserter> filter(nullptr, inserter);

    // With null destination, overflow should return EOF for non-EOF characters
    auto result = filter.overflow('A');
    EXPECT_EQ(result, std::char_traits<char>::eof());
}

// Test: Inserter is called correctly - counting calls
TEST_F(OutputFilterTest_7, InserterCalledOnOverflow_7) {
    std::stringbuf destBuf;
    CountingInserter inserter;
    JsonBox::OutputFilter<CountingInserter> filter(&destBuf, inserter);

    filter.overflow('A');
    filter.overflow('B');
    filter.overflow('C');

    EXPECT_EQ(filter.getInserter().callCount, 3);
}

// Test: Doubling inserter produces doubled output
TEST_F(OutputFilterTest_7, DoublingInserterProducesDoubledOutput_7) {
    std::stringbuf destBuf;
    DoublingInserter inserter;
    JsonBox::OutputFilter<DoublingInserter> filter(&destBuf, inserter);

    filter.overflow('A');
    EXPECT_EQ(destBuf.str(), "AA");
}

// Test: UpperCase inserter transforms characters
TEST_F(OutputFilterTest_7, UpperCaseInserterTransforms_7) {
    std::stringbuf destBuf;
    UpperCaseInserter inserter;
    JsonBox::OutputFilter<UpperCaseInserter> filter(&destBuf, inserter);

    filter.overflow('a');
    filter.overflow('B');
    filter.overflow('c');
    EXPECT_EQ(destBuf.str(), "ABC");
}

// Test: underflow returns EOF (since this is an output filter)
TEST_F(OutputFilterTest_7, UnderflowReturnsEOF_7) {
    std::stringbuf destBuf;
    SimpleInserter inserter;
    JsonBox::OutputFilter<SimpleInserter> filter(&destBuf, inserter);

    auto result = filter.underflow();
    EXPECT_EQ(result, std::char_traits<char>::eof());
}

// Test: Using OutputFilter through ostream interface
TEST_F(OutputFilterTest_7, UseWithOstream_7) {
    std::stringbuf destBuf;
    SimpleInserter inserter;
    JsonBox::OutputFilter<SimpleInserter> filter(&destBuf, inserter);

    std::ostream os(&filter);
    os << "Hello";
    os.flush();

    EXPECT_EQ(destBuf.str(), "Hello");
}

// Test: Using OutputFilter through ostream with single character put
TEST_F(OutputFilterTest_7, UseWithOstreamPut_7) {
    std::stringbuf destBuf;
    SimpleInserter inserter;
    JsonBox::OutputFilter<SimpleInserter> filter(&destBuf, inserter);

    std::ostream os(&filter);
    os.put('X');
    os.flush();

    EXPECT_EQ(destBuf.str(), "X");
}

// Test: Failing inserter causes overflow to return EOF
TEST_F(OutputFilterTest_7, FailingInserterReturnsEOF_7) {
    std::stringbuf destBuf;
    FailingInserter inserter;
    JsonBox::OutputFilter<FailingInserter> filter(&destBuf, inserter);

    auto result = filter.overflow('A');
    EXPECT_EQ(result, std::char_traits<char>::eof());
}

// Test: deleteWhenFinished default is false
TEST_F(OutputFilterTest_7, DeleteWhenFinishedDefaultFalse_7) {
    std::stringbuf destBuf;
    SimpleInserter inserter;
    // Default deleteWhenFinished should be false - no crash on destruction
    JsonBox::OutputFilter<SimpleInserter> filter(&destBuf, inserter);
    // Just ensure no crash on destruction
}

// Test: deleteWhenFinished true with heap-allocated destination
TEST_F(OutputFilterTest_7, DeleteWhenFinishedTrue_7) {
    std::stringbuf* destBuf = new std::stringbuf();
    SimpleInserter inserter;
    {
        JsonBox::OutputFilter<SimpleInserter> filter(destBuf, inserter, true);
        filter.overflow('A');
        // On destruction, destBuf should be deleted
    }
    // If we get here without crash, the test passes
    SUCCEED();
}

// Test: Writing special characters (newline, tab, etc.)
TEST_F(OutputFilterTest_7, OverflowSpecialCharacters_7) {
    std::stringbuf destBuf;
    SimpleInserter inserter;
    JsonBox::OutputFilter<SimpleInserter> filter(&destBuf, inserter);

    filter.overflow('\n');
    filter.overflow('\t');
    filter.overflow('\r');
    EXPECT_EQ(destBuf.str(), "\n\t\r");
}

// Test: Overflow with space character
TEST_F(OutputFilterTest_7, OverflowSpaceCharacter_7) {
    std::stringbuf destBuf;
    SimpleInserter inserter;
    JsonBox::OutputFilter<SimpleInserter> filter(&destBuf, inserter);

    filter.overflow(' ');
    EXPECT_EQ(destBuf.str(), " ");
}

// Test: Writing a long string through the filter
TEST_F(OutputFilterTest_7, OverflowLongString_7) {
    std::stringbuf destBuf;
    SimpleInserter inserter;
    JsonBox::OutputFilter<SimpleInserter> filter(&destBuf, inserter);

    std::string longStr(1000, 'x');
    for (char c : longStr) {
        filter.overflow(c);
    }
    EXPECT_EQ(destBuf.str(), longStr);
}

// Test: GetDestination with null destination
TEST_F(OutputFilterTest_7, GetDestinationNull_7) {
    SimpleInserter inserter;
    JsonBox::OutputFilter<SimpleInserter> filter(nullptr, inserter);
    EXPECT_EQ(filter.getDestination(), nullptr);
}

} // namespace
