// TEST_ID 383
// Unit tests for PostScriptFunction::getType() via public Function::parse() API.
//
// File: FunctionPostScriptFunctionGetTypeTest_383.cpp

#include <gtest/gtest.h>

#include "poppler/Function.h"
#include "poppler/Object.h"
#include "poppler/Array.h"
#include "poppler/Dict.h"
#include "poppler/Stream.h"

namespace {

class PostScriptFunctionTest_383 : public ::testing::Test {
protected:
  // Build a minimal PDF FunctionType 4 stream object and parse it.
  // Returns nullptr if parsing fails.
  static std::unique_ptr<Function> ParsePostScriptFunctionFromStream(const char* ps_code,
                                                                     int m_inputs,
                                                                     int n_outputs,
                                                                     bool include_range = true) {
    // Build Domain array of size 2*m: [0 1] repeated for each input.
    auto* domainArr = new Array(nullptr);
    for (int i = 0; i < m_inputs; ++i) {
      domainArr->add(Object(0.0));
      domainArr->add(Object(1.0));
    }

    // Build Range array of size 2*n: [0 1] repeated for each output.
    Array* rangeArr = nullptr;
    if (include_range) {
      rangeArr = new Array(nullptr);
      for (int i = 0; i < n_outputs; ++i) {
        rangeArr->add(Object(0.0));
        rangeArr->add(Object(1.0));
      }
    }

    // Stream dictionary for the function stream.
    auto* dict = new Dict(nullptr);
    dict->add("FunctionType", Object(4));
    dict->add("Domain", Object(domainArr));
    if (include_range) {
      dict->add("Range", Object(rangeArr));
    }

    const int len = ps_code ? static_cast<int>(std::strlen(ps_code)) : 0;
    dict->add("Length", Object(len));

    Object dictObj(dict);

    // Create a memory-backed stream whose dict is the function dictionary.
    std::unique_ptr<Stream> mem =
        std::make_unique<MemStream>(ps_code ? ps_code : "", /*start=*/0, /*length=*/len, std::move(dictObj));

    // Wrap stream into an Object and parse.
    Object funcObj(std::move(mem));
    return Function::parse(&funcObj);
  }
};

} // namespace

TEST_F(PostScriptFunctionTest_383, ParseValidType4Stream_YieldsPostScriptType_383) {
  // 1 input, 1 output: pop input, push constant 0.
  auto fn = ParsePostScriptFunctionFromStream("pop 0", /*m_inputs=*/1, /*n_outputs=*/1);
  ASSERT_NE(fn, nullptr);
  EXPECT_EQ(fn->getType(), Function::Type::PostScript);
}

TEST_F(PostScriptFunctionTest_383, GetTypeIsStableViaBasePointer_383) {
  auto fn = ParsePostScriptFunctionFromStream("pop 0", /*m_inputs=*/1, /*n_outputs=*/1);
  ASSERT_NE(fn, nullptr);

  const Function* base = fn.get();
  EXPECT_EQ(base->getType(), Function::Type::PostScript);
}

TEST_F(PostScriptFunctionTest_383, ParseNonStreamObject_ReturnsNull_383) {
  // Function::parse(Object*) is public; passing a non-stream object should fail.
  Object notAStream(42);
  auto fn = Function::parse(&notAStream);
  EXPECT_EQ(fn, nullptr);
}

TEST_F(PostScriptFunctionTest_383, ParseStreamWithWrongFunctionType_DoesNotProducePostScriptFunction_383) {
  // Build a stream dictionary with FunctionType != 4 and verify it does not parse as PostScriptFunction.
  const char* ps_code = "pop 0";
  const int len = static_cast<int>(std::strlen(ps_code));

  auto* domainArr = new Array(nullptr);
  domainArr->add(Object(0.0));
  domainArr->add(Object(1.0));

  auto* dict = new Dict(nullptr);
  dict->add("FunctionType", Object(3)); // Exponential, not PostScript (4)
  dict->add("Domain", Object(domainArr));
  dict->add("Length", Object(len));

  Object dictObj(dict);
  std::unique_ptr<Stream> mem = std::make_unique<MemStream>(ps_code, 0, len, std::move(dictObj));
  Object funcObj(std::move(mem));

  auto fn = Function::parse(&funcObj);
  if (fn) {
    EXPECT_NE(fn->getType(), Function::Type::PostScript);
  } else {
    SUCCEED(); // acceptable: parse may reject this outright
  }
}

TEST_F(PostScriptFunctionTest_383, ParseType4MissingRange_IsHandledGracefully_383) {
  // Boundary-ish: omit Range and ensure parse either fails (nullptr) or returns a Function safely.
  auto fn = ParsePostScriptFunctionFromStream("pop 0", /*m_inputs=*/1, /*n_outputs=*/1, /*include_range=*/false);

  if (!fn) {
    SUCCEED();
    return;
  }

  // If it parses, it should still be a PostScript function type.
  EXPECT_EQ(fn->getType(), Function::Type::PostScript);
  // isOk() is observable via interface; accept either outcome depending on implementation requirements.
  (void)fn->isOk();
}

TEST_F(PostScriptFunctionTest_383, ParseType4WithEmptyCode_IsHandledGracefully_383) {
  // Boundary: empty stream content.
  auto fn = ParsePostScriptFunctionFromStream("", /*m_inputs=*/1, /*n_outputs=*/1);

  if (!fn) {
    SUCCEED();
    return;
  }

  EXPECT_EQ(fn->getType(), Function::Type::PostScript);
  // If parse succeeds, implementation may mark it not ok; ensure call is safe.
  (void)fn->isOk();
}