#include <gtest/gtest.h>
#include <sstream>
#include <iostream>

// Declaration of the function under test
namespace Catch {
    std::ostream& cerr();
}

// Test that cerr() returns a valid ostream reference
TEST(CatchStdStreamsTest_548, CerrReturnsValidOstream_548) {
    std::ostream& result = Catch::cerr();
    // The returned stream should not be in a bad state
    EXPECT_TRUE(result.good() || !result.fail());
}

// Test that cerr() returns a reference to std::cerr
TEST(CatchStdStreamsTest_548, CerrReturnsStdCerr_548) {
    std::ostream& result = Catch::cerr();
    // Verify that the address of the returned reference matches std::cerr
    EXPECT_EQ(&result, &std::cerr);
}

// Test that calling cerr() multiple times returns the same reference
TEST(CatchStdStreamsTest_548, CerrReturnsSameReferencOnMultipleCalls_548) {
    std::ostream& first = Catch::cerr();
    std::ostream& second = Catch::cerr();
    EXPECT_EQ(&first, &second);
}

// Test that we can write to the returned stream without error
TEST(CatchStdStreamsTest_548, CerrIsWritable_548) {
    std::ostream& result = Catch::cerr();
    // Save the original buffer
    std::streambuf* originalBuf = std::cerr.rdbuf();
    
    // Redirect cerr to a stringstream to capture output
    std::ostringstream captured;
    std::cerr.rdbuf(captured.rdbuf());
    
    result << "test_output_548";
    
    // Restore the original buffer
    std::cerr.rdbuf(originalBuf);
    
    EXPECT_EQ(captured.str(), "test_output_548");
}

// Test that the returned stream reflects the state of std::cerr
TEST(CatchStdStreamsTest_548, CerrReflectsStdCerrState_548) {
    std::ostream& result = Catch::cerr();
    // rdstate should match since they should be the same object
    EXPECT_EQ(result.rdstate(), std::cerr.rdstate());
}

// Test writing different types through the returned reference
TEST(CatchStdStreamsTest_548, CerrSupportsVariousTypes_548) {
    std::ostream& result = Catch::cerr();
    
    // Redirect to capture
    std::streambuf* originalBuf = std::cerr.rdbuf();
    std::ostringstream captured;
    std::cerr.rdbuf(captured.rdbuf());
    
    result << 42 << " " << 3.14 << " " << "hello";
    
    std::cerr.rdbuf(originalBuf);
    
    EXPECT_FALSE(captured.str().empty());
    EXPECT_NE(captured.str().find("42"), std::string::npos);
    EXPECT_NE(captured.str().find("hello"), std::string::npos);
}
