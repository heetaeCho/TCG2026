#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <streambuf>
#include <sstream>
#include <string>
#include <functional>

// Include the header under test
#include "JsonBox/OutputFilter.h"

namespace {

// A simple inserter that just passes characters through
struct PassThroughInserter {
    std::streambuf::int_type operator()(std::streambuf *destination, std::streambuf::int_type ch) {
        if (destination) {
            return destination->sputc(static_cast<char>(ch));
        }
        return std::streambuf::traits_type::eof();
    }
};

// An inserter that converts lowercase to uppercase
struct UpperCaseInserter {
    std::streambuf::int_type operator()(std::streambuf *destination, std::streambuf::int_type ch) {
        if (destination && ch != std::streambuf::traits_type::eof()) {
            char c = static_cast<char>(ch);
            if (c >= 'a' && c <= 'z') {
                c = c - 'a' + 'A';
            }
            return destination->sputc(c);
        }
        return std::streambuf::traits_type::eof();
    }
};

// An inserter that counts characters
struct CountingInserter {
    int count = 0;
    std::streambuf::int_type operator()(std::streambuf *destination, std::streambuf::int_type ch) {
        if (destination && ch != std::streambuf::traits_type::eof()) {
            ++count;
            return destination->sputc(static_cast<char>(ch));
        }
        return std::streambuf::traits_type::eof();
    }
};

// Test fixture
class OutputFilterTest_6 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: Construction with destination and inserter, deleteWhenFinished defaults to false
TEST_F(OutputFilterTest_6, ConstructWithDestinationAndInserter_6) {
    std::stringbuf sbuf;
    JsonBox::OutputFilter<PassThroughInserter> filter(&sbuf, PassThroughInserter());
    EXPECT_EQ(filter.getDestination(), &sbuf);
}

// Test: Construction with destination, inserter, and explicit deleteWhenFinished = false
TEST_F(OutputFilterTest_6, ConstructWithDeleteWhenFinishedFalse_6) {
    std::stringbuf sbuf;
    JsonBox::OutputFilter<PassThroughInserter> filter(&sbuf, PassThroughInserter(), false);
    EXPECT_EQ(filter.getDestination(), &sbuf);
}

// Test: Construction with destination, inserter, and deleteWhenFinished = true
TEST_F(OutputFilterTest_6, ConstructWithDeleteWhenFinishedTrue_6) {
    std::stringbuf *sbuf = new std::stringbuf();
    // When deleteWhenFinished is true, the filter should delete the destination on destruction
    {
        JsonBox::OutputFilter<PassThroughInserter> filter(sbuf, PassThroughInserter(), true);
        EXPECT_EQ(filter.getDestination(), sbuf);
    }
    // sbuf is deleted by the filter; no manual delete needed
    // If this doesn't crash, the test passes (no double-free, no leak)
}

// Test: Construction with only destination (two-parameter constructor)
TEST_F(OutputFilterTest_6, ConstructWithDestinationOnly_6) {
    std::stringbuf sbuf;
    JsonBox::OutputFilter<PassThroughInserter> filter(&sbuf);
    EXPECT_EQ(filter.getDestination(), &sbuf);
}

// Test: Construction with destination and deleteWhenFinished (two-parameter overload)
TEST_F(OutputFilterTest_6, ConstructWithDestinationAndDeleteFlag_6) {
    std::stringbuf *sbuf = new std::stringbuf();
    {
        JsonBox::OutputFilter<PassThroughInserter> filter(sbuf, true);
        EXPECT_EQ(filter.getDestination(), sbuf);
    }
    // sbuf deleted by filter
}

// Test: getDestination returns the correct destination
TEST_F(OutputFilterTest_6, GetDestinationReturnsCorrectPointer_6) {
    std::stringbuf sbuf;
    JsonBox::OutputFilter<PassThroughInserter> filter(&sbuf, PassThroughInserter(), false);
    EXPECT_EQ(filter.getDestination(), &sbuf);
}

// Test: getInserter returns a reference to the inserter
TEST_F(OutputFilterTest_6, GetInserterReturnsReference_6) {
    std::stringbuf sbuf;
    CountingInserter inserter;
    JsonBox::OutputFilter<CountingInserter> filter(&sbuf, inserter, false);
    CountingInserter &ref = filter.getInserter();
    // Should be able to access the inserter
    EXPECT_EQ(ref.count, 0);
}

// Test: overflow writes a character to the destination via the inserter
TEST_F(OutputFilterTest_6, OverflowWritesCharacter_6) {
    std::stringbuf sbuf;
    JsonBox::OutputFilter<PassThroughInserter> filter(&sbuf, PassThroughInserter(), false);
    
    auto result = filter.overflow('A');
    EXPECT_NE(result, std::streambuf::traits_type::eof());
    EXPECT_EQ(sbuf.str(), "A");
}

// Test: overflow writes multiple characters
TEST_F(OutputFilterTest_6, OverflowWritesMultipleCharacters_6) {
    std::stringbuf sbuf;
    JsonBox::OutputFilter<PassThroughInserter> filter(&sbuf, PassThroughInserter(), false);
    
    filter.overflow('H');
    filter.overflow('i');
    filter.overflow('!');
    
    EXPECT_EQ(sbuf.str(), "Hi!");
}

// Test: overflow with EOF character
TEST_F(OutputFilterTest_6, OverflowWithEOF_6) {
    std::stringbuf sbuf;
    JsonBox::OutputFilter<PassThroughInserter> filter(&sbuf, PassThroughInserter(), false);
    
    auto result = filter.overflow(std::streambuf::traits_type::eof());
    // Writing EOF should either return EOF or not write anything meaningful
    EXPECT_EQ(sbuf.str(), "");
}

// Test: underflow returns EOF (since this is an output filter)
TEST_F(OutputFilterTest_6, UnderflowReturnsEOF_6) {
    std::stringbuf sbuf;
    JsonBox::OutputFilter<PassThroughInserter> filter(&sbuf, PassThroughInserter(), false);
    
    auto result = filter.underflow();
    EXPECT_EQ(result, std::streambuf::traits_type::eof());
}

// Test: Using the filter with an ostream
TEST_F(OutputFilterTest_6, UseWithOstream_6) {
    std::stringbuf sbuf;
    JsonBox::OutputFilter<PassThroughInserter> filter(&sbuf, PassThroughInserter(), false);
    
    std::ostream os(&filter);
    os << "Hello";
    os.flush();
    
    EXPECT_EQ(sbuf.str(), "Hello");
}

// Test: Using a transforming inserter (uppercase)
TEST_F(OutputFilterTest_6, UpperCaseInserterTransforms_6) {
    std::stringbuf sbuf;
    JsonBox::OutputFilter<UpperCaseInserter> filter(&sbuf, UpperCaseInserter(), false);
    
    std::ostream os(&filter);
    os << "hello";
    os.flush();
    
    EXPECT_EQ(sbuf.str(), "HELLO");
}

// Test: CountingInserter counts characters through getInserter
TEST_F(OutputFilterTest_6, CountingInserterTracksCount_6) {
    std::stringbuf sbuf;
    JsonBox::OutputFilter<CountingInserter> filter(&sbuf, CountingInserter(), false);
    
    filter.overflow('a');
    filter.overflow('b');
    filter.overflow('c');
    
    EXPECT_EQ(filter.getInserter().count, 3);
    EXPECT_EQ(sbuf.str(), "abc");
}

// Test: Null destination with deleteWhenFinished = false
TEST_F(OutputFilterTest_6, NullDestinationNoDelete_6) {
    // Construction with null destination should not crash
    JsonBox::OutputFilter<PassThroughInserter> filter(nullptr, PassThroughInserter(), false);
    EXPECT_EQ(filter.getDestination(), nullptr);
}

// Test: Null destination with deleteWhenFinished = true
TEST_F(OutputFilterTest_6, NullDestinationWithDeleteTrue_6) {
    // Should not crash on destruction even with deleteWhenFinished=true and null destination
    {
        JsonBox::OutputFilter<PassThroughInserter> filter(nullptr, PassThroughInserter(), true);
        EXPECT_EQ(filter.getDestination(), nullptr);
    }
    // No crash expected
}

// Test: overflow with various character values including boundary
TEST_F(OutputFilterTest_6, OverflowBoundaryCharacters_6) {
    std::stringbuf sbuf;
    JsonBox::OutputFilter<PassThroughInserter> filter(&sbuf, PassThroughInserter(), false);
    
    // Null character
    filter.overflow('\0');
    // Check that something was written (null char is valid)
    EXPECT_EQ(sbuf.str().size(), 1u);
    
    // Newline
    filter.overflow('\n');
    EXPECT_EQ(sbuf.str().size(), 2u);
}

// Test: Writing a large amount of data through the filter
TEST_F(OutputFilterTest_6, LargeDataThroughput_6) {
    std::stringbuf sbuf;
    JsonBox::OutputFilter<PassThroughInserter> filter(&sbuf, PassThroughInserter(), false);
    
    std::ostream os(&filter);
    std::string largeString(10000, 'x');
    os << largeString;
    os.flush();
    
    EXPECT_EQ(sbuf.str(), largeString);
}

// Test: Mixed characters including special characters
TEST_F(OutputFilterTest_6, MixedSpecialCharacters_6) {
    std::stringbuf sbuf;
    JsonBox::OutputFilter<PassThroughInserter> filter(&sbuf, PassThroughInserter(), false);
    
    std::ostream os(&filter);
    os << "Hello\tWorld\n{\"key\": \"value\"}";
    os.flush();
    
    EXPECT_EQ(sbuf.str(), "Hello\tWorld\n{\"key\": \"value\"}");
}

// Test: getDestination is const-correct
TEST_F(OutputFilterTest_6, GetDestinationConstCorrectness_6) {
    std::stringbuf sbuf;
    const JsonBox::OutputFilter<PassThroughInserter> filter(&sbuf, PassThroughInserter(), false);
    // getDestination is const, so this should compile
    EXPECT_EQ(filter.getDestination(), &sbuf);
}

} // anonymous namespace
