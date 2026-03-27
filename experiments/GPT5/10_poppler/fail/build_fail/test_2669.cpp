// printStruct_test_2669.cc
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <cstdio>
#include <memory>
#include <string>
#include <utility>
#include <vector>

using ::testing::_;
using ::testing::Eq;
using ::testing::InSequence;
using ::testing::MockFunction;

// ----------------------------
// Minimal stubs to compile the provided implementation (black-box tests)
// ----------------------------

struct Ref {
  int num;
  int gen;
};

// Minimal GooString compatible with usage in printStruct
class GooString {
 public:
  explicit GooString(const char *s) : s_(s ? s : "") {}
  explicit GooString(std::string s) : s_(std::move(s)) {}
  const char *c_str() const { return s_.c_str(); }
  const std::string &toStr() const { return s_; }

 private:
  std::string s_;
};

// Attribute stub (content irrelevant to printStruct beyond pointer identity)
struct Attribute {
  int id = 0;
};

// Global from prompt
bool ::printStructureText = false;

// External helpers used by printStruct
static void printIndent(unsigned indent) {
  // Deterministic indentation for assertions: 2 spaces per indent level.
  for (unsigned i = 0; i < indent; ++i) {
    std::fputs("  ", stdout);
  }
}

// TextStringToUtf8 stub: return the raw string (sufficient for observable output tests)
static std::string TextStringToUtf8(const std::string &s) { return s; }

// Hookable printAttribute stub for verifying external interactions
static MockFunction<void(const Attribute *, unsigned)> *g_print_attr_mock = nullptr;

static void printAttribute(const Attribute *attr, unsigned indent) {
  // Produce some output so the stdout stream reflects attribute printing happened,
  // and also allow verification via the mock.
  if (g_print_attr_mock) {
    g_print_attr_mock->Call(attr, indent);
  }
  printIndent(indent);
  std::printf("Attr(%p)\n", static_cast<const void *>(attr));
}

// Minimal StructElement with only methods used by printStruct
class StructElement {
 public:
  // Builder-style setters for convenience in tests
  StructElement &SetIsObjectRef(bool v) {
    isObjectRef_ = v;
    return *this;
  }
  StructElement &SetObjectRef(Ref r) {
    objRef_ = r;
    return *this;
  }
  StructElement &SetIsContent(bool v) {
    isContent_ = v;
    return *this;
  }
  StructElement &SetText(std::unique_ptr<GooString> t) {
    text_ = std::move(t);
    return *this;
  }
  StructElement &SetTypeName(const char *t) {
    typeName_ = t ? t : "";
    return *this;
  }
  StructElement &SetID(std::unique_ptr<GooString> id) {
    id_ = std::move(id);
    return *this;
  }
  StructElement &SetTitle(std::unique_ptr<GooString> title) {
    title_ = std::move(title);
    return *this;
  }
  StructElement &SetRevision(unsigned r) {
    revision_ = r;
    return *this;
  }
  StructElement &SetInline(bool v) {
    isInline_ = v;
    return *this;
  }
  StructElement &SetBlock(bool v) {
    isBlock_ = v;
    return *this;
  }
  StructElement &SetAltText(std::unique_ptr<GooString> alt) {
    altText_ = std::move(alt);
    return *this;
  }
  StructElement &AddAttribute(const Attribute *a) {
    attrs_.push_back(a);
    return *this;
  }
  StructElement &AddChild(const StructElement *c) {
    children_.push_back(c);
    return *this;
  }

  // Interface used by printStruct
  bool isObjectRef() const { return isObjectRef_; }
  Ref getObjectRef() const { return objRef_; }

  bool isContent() const { return isContent_; }

  // printStruct calls getText(false) and then delete's it.
  GooString *getText(bool /*recursive*/ = true) const {
    if (!text_) {
      return nullptr;
    }
    return new GooString(text_->toStr());
  }

  const char *getTypeName() const { return typeName_.c_str(); }
  const GooString *getID() const { return id_.get(); }
  const GooString *getTitle() const { return title_.get(); }
  unsigned int getRevision() const { return revision_; }

  bool isInline() const { return isInline_; }
  bool isBlock() const { return isBlock_; }

  const GooString *getAltText() const { return altText_.get(); }

  unsigned getNumAttributes() const { return static_cast<unsigned>(attrs_.size()); }
  const Attribute *getAttribute(int i) const { return attrs_.at(static_cast<size_t>(i)); }

  unsigned getNumChildren() const { return static_cast<unsigned>(children_.size()); }
  const StructElement *getChild(int i) const { return children_.at(static_cast<size_t>(i)); }

 private:
  bool isObjectRef_ = false;
  Ref objRef_{0, 0};

  bool isContent_ = false;
  std::unique_ptr<GooString> text_;

  std::string typeName_ = "Unknown";
  std::unique_ptr<GooString> id_;
  std::unique_ptr<GooString> title_;
  unsigned revision_ = 0;

  bool isInline_ = false;
  bool isBlock_ = false;

  std::unique_ptr<GooString> altText_;

  std::vector<const Attribute *> attrs_;
  std::vector<const StructElement *> children_;
};

// ----------------------------
// Provided implementation under test (verbatim from prompt)
// ----------------------------
static void printStruct(const StructElement *element, unsigned indent) {
  if (element->isObjectRef()) {
    printIndent(indent);
    printf("Object %i %i\n", element->getObjectRef().num, element->getObjectRef().gen);
    return;
  }
  if (printStructureText && element->isContent()) {
    GooString *text = element->getText(false);
    printIndent(indent);
    if (text) {
      printf("\"%s\"\n", text->c_str());
    } else {
      printf("(No content?)\n");
    }
    delete text;
  }
  if (!element->isContent()) {
    printIndent(indent);
    printf("%s", element->getTypeName());
    if (element->getID()) {
      printf(" <%s>", element->getID()->c_str());
    }
    if (element->getTitle()) {
      printf(" \"%s\"", element->getTitle()->c_str());
    }
    if (element->getRevision() > 0) {
      printf(" r%u", element->getRevision());
    }
    if (element->isInline() || element->isBlock()) {
      printf(" (%s)", element->isInline() ? "inline" : "block");
    }
    if (element->getAltText()) {
      printf(" [\"%s\"]", TextStringToUtf8(element->getAltText()->toStr()).c_str());
    }
    if (element->getNumAttributes()) {
      putchar(':');
      for (unsigned i = 0; i < element->getNumAttributes(); i++) {
        putchar('\n');
        printAttribute(element->getAttribute(i), indent + 1);
      }
    }
    putchar('\n');
    for (unsigned i = 0; i < element->getNumChildren(); i++) {
      printStruct(element->getChild(i), indent + 1);
    }
  }
}

// ----------------------------
// Tests
// ----------------------------

class PrintStructTest_2669 : public ::testing::Test {
 protected:
  void SetUp() override {
    ::printStructureText = false;
    g_print_attr_mock = nullptr;
  }

  void TearDown() override {
    g_print_attr_mock = nullptr;
    ::printStructureText = false;
  }
};

TEST_F(PrintStructTest_2669, ObjectRef_PrintsObjectLineAndStops_2669) {
  StructElement e;
  e.SetIsObjectRef(true).SetObjectRef(Ref{12, 34}).SetIsContent(false).SetTypeName("ShouldNotPrint");

  testing::internal::CaptureStdout();
  printStruct(&e, /*indent=*/2);
  const std::string out = testing::internal::GetCapturedStdout();

  EXPECT_EQ(out, "    Object 12 34\n");  // 2 indents => 4 spaces (2 per level)
}

TEST_F(PrintStructTest_2669, Content_WhenPrintStructureTextTrue_PrintsQuotedText_2669) {
  ::printStructureText = true;

  StructElement e;
  e.SetIsObjectRef(false).SetIsContent(true).SetText(std::make_unique<GooString>("Hello"));

  testing::internal::CaptureStdout();
  printStruct(&e, /*indent=*/1);
  const std::string out = testing::internal::GetCapturedStdout();

  EXPECT_EQ(out, "  \"Hello\"\n");
}

TEST_F(PrintStructTest_2669, Content_WhenPrintStructureTextTrueAndNoText_PrintsNoContentMarker_2669) {
  ::printStructureText = true;

  StructElement e;
  e.SetIsObjectRef(false).SetIsContent(true);  // no text provided => nullptr

  testing::internal::CaptureStdout();
  printStruct(&e, /*indent=*/0);
  const std::string out = testing::internal::GetCapturedStdout();

  EXPECT_EQ(out, "(No content?)\n");
}

TEST_F(PrintStructTest_2669, Content_WhenPrintStructureTextFalse_PrintsNothing_2669) {
  ::printStructureText = false;

  StructElement e;
  e.SetIsObjectRef(false).SetIsContent(true).SetText(std::make_unique<GooString>("Ignored"));

  testing::internal::CaptureStdout();
  printStruct(&e, /*indent=*/3);
  const std::string out = testing::internal::GetCapturedStdout();

  EXPECT_TRUE(out.empty());
}

TEST_F(PrintStructTest_2669, NonContent_PrintsHeaderWithOptionalFields_2669) {
  StructElement e;
  e.SetIsObjectRef(false)
      .SetIsContent(false)
      .SetTypeName("Sect")
      .SetID(std::make_unique<GooString>("id-1"))
      .SetTitle(std::make_unique<GooString>("Title A"))
      .SetRevision(7)
      .SetInline(true)
      .SetBlock(false)
      .SetAltText(std::make_unique<GooString>("Alt"));

  testing::internal::CaptureStdout();
  printStruct(&e, /*indent=*/1);
  const std::string out = testing::internal::GetCapturedStdout();

  EXPECT_EQ(out, "  Sect <id-1> \"Title A\" r7 (inline) [\"Alt\"]\n");
}

TEST_F(PrintStructTest_2669, NonContent_WithNoOptionalFields_PrintsTypeAndNewlineOnly_2669) {
  StructElement e;
  e.SetIsObjectRef(false).SetIsContent(false).SetTypeName("P").SetRevision(0).SetInline(false).SetBlock(false);

  testing::internal::CaptureStdout();
  printStruct(&e, /*indent=*/0);
  const std::string out = testing::internal::GetCapturedStdout();

  EXPECT_EQ(out, "P\n");
}

TEST_F(PrintStructTest_2669, NonContent_WithAttributes_CallsPrintAttributeWithIndentPlusOne_2669) {
  Attribute a1{1};
  Attribute a2{2};

  StructElement e;
  e.SetIsObjectRef(false).SetIsContent(false).SetTypeName("Span").AddAttribute(&a1).AddAttribute(&a2);

  MockFunction<void(const Attribute *, unsigned)> mock;
  g_print_attr_mock = &mock;

  {
    InSequence seq;
    EXPECT_CALL(mock, Call(Eq(&a1), 2u));
    EXPECT_CALL(mock, Call(Eq(&a2), 2u));
  }

  testing::internal::CaptureStdout();
  printStruct(&e, /*indent=*/1);
  const std::string out = testing::internal::GetCapturedStdout();

  // Header line has ':' then each attribute printed on its own line with indent+1.
  // We don't assert the Attr(%p) pointer text exactly (platform-dependent formatting),
  // but we do assert key structural pieces.
  EXPECT_THAT(out, ::testing::StartsWith("  Span:\n"));
  EXPECT_THAT(out, ::testing::HasSubstr("\n    Attr("));  // 2 indents for attributes (indent+1)
}

TEST_F(PrintStructTest_2669, NonContent_WithChildren_PrintsChildrenRecursivelyWithIncreasedIndent_2669) {
  StructElement child1;
  child1.SetIsObjectRef(false).SetIsContent(false).SetTypeName("ChildA");

  StructElement child2;
  child2.SetIsObjectRef(true).SetObjectRef(Ref{9, 0});  // exercise child object-ref path

  StructElement parent;
  parent.SetIsObjectRef(false).SetIsContent(false).SetTypeName("Parent").AddChild(&child1).AddChild(&child2);

  testing::internal::CaptureStdout();
  printStruct(&parent, /*indent=*/0);
  const std::string out = testing::internal::GetCapturedStdout();

  // Expect:
  // Parent\n
  //   ChildA\n
  //   Object 9 0\n
  EXPECT_EQ(out, "Parent\n  ChildA\n  Object 9 0\n");
}