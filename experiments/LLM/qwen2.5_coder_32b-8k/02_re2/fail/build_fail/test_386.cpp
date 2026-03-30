#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "re2/re2.h"

#include "fuzzing/re2_fuzzer.h"



using namespace re2;



// Mock for TestOneInput function to verify interactions

class MockTestOneInput {

public:

    MOCK_FUNCTION4(TestOneInput, void(const std::string&, const RE2::Options&, RE2::Anchor, const std::string&));

};



TEST_F(MockTestOneInput_386, NormalOperationWithRandomData_386) {

    uint8_t data[] = { /* Random bytes */ 0x01, 0x02, 0x03, 0x04, 0x05 };

    size_t size = sizeof(data);



    EXPECT_CALL(*this, TestOneInput(::testing::_, ::testing::_, ::testing::_, ::testing::_));



    LLVMFuzzerTestOneInput(data, size);

}



TEST_F(MockTestOneInput_386, ZeroSizeData_ReturnsZero_386) {

    uint8_t data[] = { /* Random bytes */ 0x01, 0x02 };

    size_t size = 0;



    EXPECT_CALL(*this, TestOneInput(::testing::_, ::testing::_, ::testing::_, ::testing::_)).Times(0);



    int result = LLVMFuzzerTestOneInput(data, size);

    EXPECT_EQ(result, 0);

}



TEST_F(MockTestOneInput_386, MaxSizeData_ReturnsZero_386) {

    uint8_t data[4097] = { /* Random bytes */ };

    size_t size = sizeof(data);



    EXPECT_CALL(*this, TestOneInput(::testing::_, ::testing::_, ::testing::_, ::testing::_)).Times(0);



    int result = LLVMFuzzerTestOneInput(data, size);

    EXPECT_EQ(result, 0);

}



TEST_F(MockTestOneInput_386, BoundarySizeData_CallsTestOneInput_386) {

    uint8_t data[4096] = { /* Random bytes */ };

    size_t size = sizeof(data);



    EXPECT_CALL(*this, TestOneInput(::testing::_, ::testing::_, ::testing::_, ::testing::_));



    LLVMFuzzerTestOneInput(data, size);

}



TEST_F(MockTestOneInput_386, EncodingLatin1_CallsTestOneInputWithLatin1_386) {

    uint8_t data[] = { 0x01 }; // First bit set to false for Latin1 encoding

    size_t size = sizeof(data);



    EXPECT_CALL(*this, TestOneInput(::testing::_, ::testing::Property(&RE2::Options::encoding, RE2::EncodingLatin1), ::testing::_, ::testing::_));



    LLVMFuzzerTestOneInput(data, size);

}



TEST_F(MockTestOneInput_386, EncodingUTF8_CallsTestOneInputWithUTF8_386) {

    uint8_t data[] = { 0x02 }; // First bit set to true for UTF8 encoding

    size_t size = sizeof(data);



    EXPECT_CALL(*this, TestOneInput(::testing::_, ::testing::Property(&RE2::Options::encoding, RE2::EncodingUTF8), ::testing::_, ::testing::_));



    LLVMFuzzerTestOneInput(data, size);

}



TEST_F(MockTestOneInput_386, PosixSyntaxEnabled_CallsTestOneInputWithPosixSyntax_386) {

    uint8_t data[] = { 0x02, 0x01 }; // Second bit set to true for POSIX syntax

    size_t size = sizeof(data);



    EXPECT_CALL(*this, TestOneInput(::testing::_, ::testing::Property(&RE2::Options::posix_syntax, true), ::testing::_, ::testing::_));



    LLVMFuzzerTestOneInput(data, size);

}



TEST_F(MockTestOneInput_386, LongestMatchEnabled_CallsTestOneInputWithLongestMatch_386) {

    uint8_t data[] = { 0x02, 0x02 }; // Third bit set to true for longest match

    size_t size = sizeof(data);



    EXPECT_CALL(*this, TestOneInput(::testing::_, ::testing::Property(&RE2::Options::longest_match, true), ::testing::_, ::testing::_));



    LLVMFuzzerTestOneInput(data, size);

}



TEST_F(MockTestOneInput_386, LogErrorsDisabled_CallsTestOneInputWithLogErrorsFalse_386) {

    uint8_t data[] = { 0x02, 0x04 }; // Fourth bit set to true for disabling log errors

    size_t size = sizeof(data);



    EXPECT_CALL(*this, TestOneInput(::testing::_, ::testing::Property(&RE2::Options::log_errors, false), ::testing::_, ::testing::_));



    LLVMFuzzerTestOneInput(data, size);

}



TEST_F(MockTestOneInput_386, LiteralEnabled_CallsTestOneInputWithLiteralTrue_386) {

    uint8_t data[] = { 0x02, 0x08 }; // Fifth bit set to true for literal

    size_t size = sizeof(data);



    EXPECT_CALL(*this, TestOneInput(::testing::_, ::testing::Property(&RE2::Options::literal, true), ::testing::_, ::testing::_));



    LLVMFuzzerTestOneInput(data, size);

}



TEST_F(MockTestOneInput_386, NeverNLEnabled_CallsTestOneInputWithNeverNLTrue_386) {

    uint8_t data[] = { 0x02, 0x10 }; // Sixth bit set to true for never_nl

    size_t size = sizeof(data);



    EXPECT_CALL(*this, TestOneInput(::testing::_, ::testing::Property(&RE2::Options::never_nl, true), ::testing::_, ::testing::_));



    LLVMFuzzerTestOneInput(data, size);

}



TEST_F(MockTestOneInput_386, DotNLEnabled_CallsTestOneInputWithDotNLTrue_386) {

    uint8_t data[] = { 0x02, 0x20 }; // Seventh bit set to true for dot_nl

    size_t size = sizeof(data);



    EXPECT_CALL(*this, TestOneInput(::testing::_, ::testing::Property(&RE2::Options::dot_nl, true), ::testing::_, ::testing::_));



    LLVMFuzzerTestOneInput(data, size);

}



TEST_F(MockTestOneInput_386, NeverCaptureEnabled_CallsTestOneInputWithNeverCaptureTrue_386) {

    uint8_t data[] = { 0x02, 0x40 }; // Eighth bit set to true for never_capture

    size_t size = sizeof(data);



    EXPECT_CALL(*this, TestOneInput(::testing::_, ::testing::Property(&RE2::Options::never_capture, true), ::testing::_, ::testing::_));



    LLVMFuzzerTestOneInput(data, size);

}



TEST_F(MockTestOneInput_386, CaseInsensitive_CallsTestOneInputWithCaseSensitiveFalse_386) {

    uint8_t data[] = { 0x02, 0x80 }; // Ninth bit set to true for case insensitive

    size_t size = sizeof(data);



    EXPECT_CALL(*this, TestOneInput(::testing::_, ::testing::Property(&RE2::Options::case_sensitive, false), ::testing::_, ::testing::_));



    LLVMFuzzerTestOneInput(data, size);

}



TEST_F(MockTestOneInput_386, PerlClassesEnabled_CallsTestOneInputWithPerlClassesTrue_386) {

    uint8_t data[] = { 0x04 }; // Tenth bit set to true for perl_classes

    size_t size = sizeof(data);



    EXPECT_CALL(*this, TestOneInput(::testing::_, ::testing::Property(&RE2::Options::perl_classes, true), ::testing::_, ::testing::_));



    LLVMFuzzerTestOneInput(data, size);

}



TEST_F(MockTestOneInput_386, WordBoundaryEnabled_CallsTestOneInputWithWordBoundaryTrue_386) {

    uint8_t data[] = { 0x05 }; // Eleventh bit set to true for word_boundary

    size_t size = sizeof(data);



    EXPECT_CALL(*this, TestOneInput(::testing::_, ::testing::Property(&RE2::Options::word_boundary, true), ::testing::_, ::testing::_));



    LLVMFuzzerTestOneInput(data, size);

}



TEST_F(MockTestOneInput_386, OneLineEnabled_CallsTestOneInputWithOneLineTrue_386) {

    uint8_t data[] = { 0x06 }; // Twelfth bit set to true for one_line

    size_t size = sizeof(data);



    EXPECT_CALL(*this, TestOneInput(::testing::_, ::testing::Property(&RE2::Options::one_line, true), ::testing::_, ::testing::_));



    LLVMFuzzerTestOneInput(data, size);

}



TEST_F(MockTestOneInput_386, AnchorStart_CallsTestOneInputWithAnchorStart_386) {

    uint8_t data[] = { 0x07, 0x01 }; // Random bytes with anchor set to ANCHOR_START

    size_t size = sizeof(data);



    EXPECT_CALL(*this, TestOneInput(::testing::_, ::testing::_, RE2::ANCHOR_START, ::testing::_));



    LLVMFuzzerTestOneInput(data, size);

}



TEST_F(MockTestOneInput_386, AnchorBoth_CallsTestOneInputWithAnchorBoth_386) {

    uint8_t data[] = { 0x07, 0x02 }; // Random bytes with anchor set to ANCHOR_BOTH

    size_t size = sizeof(data);



    EXPECT_CALL(*this, TestOneInput(::testing::_, ::testing::_, RE2::ANCHOR_BOTH, ::testing::_));



    LLVMFuzzerTestOneInput(data, size);

}
