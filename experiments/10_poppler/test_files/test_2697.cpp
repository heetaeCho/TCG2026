#include <gtest/gtest.h>

#include "GooString.h"

#include <memory>



// Mock GooString for testing purposes if needed.

class MockGooString : public GooString {

public:

    MOCK_METHOD(std::unique_ptr<GooString>, copy, (), (const override));

};



extern bool singleFile;

extern bool ps;

extern bool eps;

extern bool pdf;

extern bool printToWin32;

extern bool svg;

extern bool printing;



TEST(getOutputFileNameTest_2697, OutputNameProvided_2697) {

    GooString fileName("input.pdf");

    GooString outputName("output.ps");

    auto result = getOutputFileName(&fileName, &outputName);

    EXPECT_EQ(result->toStr(), "output.ps");

}



TEST(getOutputFileNameTest_2697, OutputNameIsStdoutAndValidFormat_2697) {

    GooString fileName("input.pdf");

    GooString outputName("-");

    ps = true; // Setting a valid format

    auto result = getOutputFileName(&fileName, &outputName);

    EXPECT_EQ(result->toStr(), "fd://0");

}



TEST(getOutputFileNameTest_2697, OutputNameIsStdoutAndInvalidFormat_2697) {

    GooString fileName("input.pdf");

    GooString outputName("-");

    ps = false; // Invalid format

    EXPECT_EXIT({

        getOutputFileName(&fileName, &outputName);

    }, testing::ExitedWithCode(99), "Error: stdout may only be used with the ps, eps, pdf, svg output options or if -singlefile is used.");

}



TEST(getOutputFileNameTest_2697, PrintToWin32WithoutOutputName_2697) {

    GooString fileName("input.pdf");

    printToWin32 = true;

    auto result = getOutputFileName(&fileName, nullptr);

    EXPECT_EQ(result.get(), nullptr);

}



TEST(getOutputFileNameTest_2697, InputIsStdinWithoutOutputNameOrDash_2697) {

    GooString fileName("fd://0");

    EXPECT_EXIT({

        getOutputFileName(&fileName, nullptr);

    }, testing::ExitedWithCode(99), "Error: an output filename or '-' must be supplied when the PDF file is stdin.");

}



TEST(getOutputFileNameTest_2697, LocalPDFInputWithoutOutputNameOrDash_2697) {

    GooString fileName("input.pdf");

    pdf = true;

    EXPECT_EXIT({

        getOutputFileName(&fileName, nullptr);

    }, testing::ExitedWithCode(99), "Error: an output filename or '-' must be supplied when the output format is PDF and input PDF file is a local file.");

}



TEST(getOutputFileNameTest_2697, ValidLocalPDFInputWithoutExtension_2697) {

    GooString fileName("input");

    pdf = true;

    auto result = getOutputFileName(&fileName, nullptr);

    EXPECT_EQ(result->toStr(), "input.pdf");

}



TEST(getOutputFileNameTest_2697, InvalidPathFormat_2697) {

    GooString fileName("/invalid/path/");

    auto result = getOutputFileName(&fileName, nullptr);

    EXPECT_EXIT({

        getOutputFileName(&fileName, nullptr);

    }, testing::ExitedWithCode(99), "Error: invalid output filename.");

}



TEST(getOutputFileNameTest_2697, ValidPDFInputWithPSFormat_2697) {

    GooString fileName("input.pdf");

    ps = true;

    auto result = getOutputFileName(&fileName, nullptr);

    EXPECT_EQ(result->toStr(), "input.ps");

}



TEST(getOutputFileNameTest_2697, ValidPDFInputWithEPSFormat_2697) {

    GooString fileName("input.pdf");

    eps = true;

    auto result = getOutputFileName(&fileName, nullptr);

    EXPECT_EQ(result->toStr(), "input.eps");

}



TEST(getOutputFileNameTest_2697, ValidPDFInputWithSVGFormat_2697) {

    GooString fileName("input.pdf");

    svg = true;

    auto result = getOutputFileName(&fileName, nullptr);

    EXPECT_EQ(result->toStr(), "input.svg");

}
