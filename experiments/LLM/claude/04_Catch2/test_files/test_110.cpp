#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "./TestProjects/Catch2/src/catch2/internal/catch_istream.hpp"
#include <ostream>
#include <sstream>

// Concrete implementation for testing the base class default behavior
class ConcreteIStream : public Catch::IStream {
public:
    ~ConcreteIStream() override = default;
    
    std::ostream& stream() {
        return m_stream;
    }
    
private:
    std::stringstream m_stream;
};

// Test fixture
class IStreamTest_110 : public ::testing::Test {
protected:
    void SetUp() override {
        concreteStream = std::make_unique<ConcreteIStream>();
    }
    
    void TearDown() override {
        concreteStream.reset();
    }
    
    std::unique_ptr<ConcreteIStream> concreteStream;
};

// Test that the default implementation of isConsole returns false
TEST_F(IStreamTest_110, IsConsoleReturnsFalseByDefault_110) {
    EXPECT_FALSE(concreteStream->isConsole());
}

// Test that we can create and destroy an IStream-derived object without issues
TEST_F(IStreamTest_110, CanCreateAndDestroyDerivedObject_110) {
    ConcreteIStream* stream = new ConcreteIStream();
    EXPECT_NO_THROW(delete stream);
}

// Test that isConsole is consistent across multiple calls
TEST_F(IStreamTest_110, IsConsoleConsistentAcrossMultipleCalls_110) {
    bool first = concreteStream->isConsole();
    bool second = concreteStream->isConsole();
    EXPECT_EQ(first, second);
    EXPECT_FALSE(first);
}

// Test polymorphic behavior through base pointer
TEST_F(IStreamTest_110, IsConsoleViaBasePointer_110) {
    Catch::IStream* basePtr = concreteStream.get();
    EXPECT_FALSE(basePtr->isConsole());
}

// Test that a derived class can override isConsole
class ConsoleStream : public Catch::IStream {
public:
    ~ConsoleStream() override = default;
    bool isConsole() const override { return true; }
    std::ostream& stream() {
        return m_stream;
    }
private:
    std::stringstream m_stream;
};

TEST_F(IStreamTest_110, DerivedClassCanOverrideIsConsole_110) {
    ConsoleStream consoleStream;
    EXPECT_TRUE(consoleStream.isConsole());
}

TEST_F(IStreamTest_110, DerivedClassOverrideIsConsoleViaBasePointer_110) {
    ConsoleStream consoleStream;
    Catch::IStream* basePtr = &consoleStream;
    EXPECT_TRUE(basePtr->isConsole());
}

// Test that the stream() function returns a valid ostream reference
TEST_F(IStreamTest_110, StreamReturnsValidOstream_110) {
    std::ostream& os = concreteStream->stream();
    EXPECT_TRUE(os.good());
}

// Test that we can write to the stream
TEST_F(IStreamTest_110, CanWriteToStream_110) {
    std::ostream& os = concreteStream->stream();
    os << "test";
    EXPECT_TRUE(os.good());
}

// Test deletion through base pointer (virtual destructor)
TEST_F(IStreamTest_110, CanDeleteThroughBasePointer_110) {
    Catch::IStream* basePtr = new ConcreteIStream();
    EXPECT_NO_THROW(delete basePtr);
}

// Test multiple instances have independent isConsole behavior
TEST_F(IStreamTest_110, MultipleInstancesIndependent_110) {
    ConcreteIStream stream1;
    ConsoleStream stream2;
    
    EXPECT_FALSE(stream1.isConsole());
    EXPECT_TRUE(stream2.isConsole());
}
