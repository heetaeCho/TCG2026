// TEST_ID: 152
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "TestProjects/tinyxml2/tinyxml2.h"

#include <cstdio>
#include <cstring>
#include <memory>
#include <string>
#include <type_traits>

using ::testing::_;
using ::testing::InSequence;
using ::testing::StrictMock;

namespace {

class XMLPrinterWriteSpy_152 : public tinyxml2::XMLPrinter {
public:
    // Inherit constructors if available.
    using tinyxml2::XMLPrinter::XMLPrinter;

    // Expose the (likely protected) inline Write(const char*) via a public wrapper.
    void CallInlineWrite_152(const char* data) {
        // Fully qualify to ensure we call the base inline overload, not our mock.
        this->tinyxml2::XMLPrinter::Write(data);
    }

    // Observe the forwarding target: virtual Write(const char*, size_t).
    MOCK_METHOD(void, Write, (const char* data, size_t size), (override));
};

// Construct XMLPrinterWriteSpy_152 in a way that tolerates different tinyxml2 versions/signatures.
std::unique_ptr<StrictMock<XMLPrinterWriteSpy_152>> MakePrinter_152() {
    using P = StrictMock<XMLPrinterWriteSpy_152>;

    if constexpr (std::is_constructible_v<P, FILE*, bool, int>) {
        return std::make_unique<P>(nullptr, false, 0);
    } else if constexpr (std::is_constructible_v<P, FILE*, bool, int, int>) {
        // Some versions add a 4th parameter (e.g., escaping mode). Many accept an int-like value.
        return std::make_unique<P>(nullptr, false, 0, 0);
    } else if constexpr (std::is_default_constructible_v<P>) {
        return std::make_unique<P>();
    } else {
        // If construction changes drastically, fail loudly at compile time.
        static_assert(std::is_constructible_v<P, FILE*, bool, int> ||
                          std::is_constructible_v<P, FILE*, bool, int, int> ||
                          std::is_default_constructible_v<P>,
                      "Unsupported XMLPrinter constructor signature for tests.");
        return nullptr;
    }
}

class XMLPrinterWriteTest_152 : public ::testing::Test {
protected:
    std::unique_ptr<StrictMock<XMLPrinterWriteSpy_152>> printer_;

    void SetUp() override { printer_ = MakePrinter_152(); }
};

TEST_F(XMLPrinterWriteTest_152, ForwardsCStringAndLength_152) {
    const char* s = "abc";
    EXPECT_CALL(*printer_, Write(s, 3u)).Times(1);

    printer_->CallInlineWrite_152(s);
}

TEST_F(XMLPrinterWriteTest_152, ForwardsEmptyStringWithZeroLength_152) {
    const char* s = "";
    EXPECT_CALL(*printer_, Write(s, 0u)).Times(1);

    printer_->CallInlineWrite_152(s);
}

TEST_F(XMLPrinterWriteTest_152, LengthStopsAtFirstNullTerminator_152) {
    const char buf[] = {'a', '\0', 'b', '\0'};
    const char* s = buf;

    // strlen("a\0b") == 1
    EXPECT_CALL(*printer_, Write(s, 1u)).Times(1);

    printer_->CallInlineWrite_152(s);
}

TEST_F(XMLPrinterWriteTest_152, ForwardsLongStringLength_152) {
    std::string longStr(1024, 'x');
    const char* s = longStr.c_str();

    EXPECT_CALL(*printer_, Write(s, static_cast<size_t>(longStr.size()))).Times(1);

    printer_->CallInlineWrite_152(s);
}

TEST_F(XMLPrinterWriteTest_152, MultipleCallsForwardEachTime_152) {
    const char* a = "hi";
    const char* b = "there";

    InSequence seq;
    EXPECT_CALL(*printer_, Write(a, 2u)).Times(1);
    EXPECT_CALL(*printer_, Write(b, 5u)).Times(1);

    printer_->CallInlineWrite_152(a);
    printer_->CallInlineWrite_152(b);
}

}  // namespace
