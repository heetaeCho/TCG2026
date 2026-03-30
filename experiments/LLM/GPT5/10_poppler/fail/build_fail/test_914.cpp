// TEST_ID: 914
#include <gtest/gtest.h>

#include <memory>
#include <set>
#include <utility>

// Poppler headers
#include "poppler/Form.h"
#include "goo/GooString.h"

namespace {

// Test helper that gives us a predictable, constructible object and a safe way
// to control observable behavior of getExportVal() without relying on private state.
class TestableFormFieldChoice_914 : public FormFieldChoice {
public:
  using FormFieldChoice::FormFieldChoice;

  // Keep the backing storage alive for the duration of a test.
  void AdoptChoices(std::unique_ptr<ChoiceOpt[]> arr, int n) {
    ownedChoices_ = std::move(arr);
    numChoices_ = n;

    // FormFieldChoice::getExportVal() only depends on whether `choices` is null and on choices[i].exportVal.
    // We ensure `choices` points to valid memory for tests that need it.
    choices = ownedChoices_.get();
  }

  void ClearChoices() {
    ownedChoices_.reset();
    numChoices_ = 0;
    choices = nullptr;
  }

  int numChoicesForTest() const { return numChoices_; }

private:
  std::unique_ptr<ChoiceOpt[]> ownedChoices_;
  int numChoices_ = 0;
};

static std::unique_ptr<TestableFormFieldChoice_914> MakeChoiceField_914() {
  // Construct with minimal/dummy args. Tests only exercise getExportVal().
  PDFDoc* doc = nullptr;
  Object aobj; // default/null object in Poppler
  Ref ref{0, 0};
  FormField* parent = nullptr;
  auto usedParents = std::make_unique<std::set<int>>();

  return std::make_unique<TestableFormFieldChoice_914>(doc, std::move(aobj), ref, parent, usedParents.get());
}

} // namespace

class FormFieldChoiceTest_914 : public ::testing::Test {
protected:
  void SetUp() override { field = MakeChoiceField_914(); }

  std::unique_ptr<TestableFormFieldChoice_914> field;
};

TEST_F(FormFieldChoiceTest_914, GetExportValReturnsNullWhenChoicesIsNull_914) {
  field->ClearChoices();
  EXPECT_EQ(field->getExportVal(0), nullptr);
  EXPECT_EQ(field->getExportVal(123), nullptr);
}

TEST_F(FormFieldChoiceTest_914, GetExportValReturnsSamePointerAsStoredExportVal_914) {
  auto arr = std::make_unique<FormFieldChoice::ChoiceOpt[]>(1);
  arr[0].exportVal = std::make_unique<GooString>("A");

  const GooString* expected = arr[0].exportVal.get();
  field->AdoptChoices(std::move(arr), 1);

  const GooString* got = field->getExportVal(0);
  ASSERT_NE(got, nullptr);
  EXPECT_EQ(got, expected);
}

TEST_F(FormFieldChoiceTest_914, GetExportValReturnsNullWhenExportValIsNullEvenIfChoicesExist_914) {
  auto arr = std::make_unique<FormFieldChoice::ChoiceOpt[]>(1);
  // exportVal left as nullptr
  field->AdoptChoices(std::move(arr), 1);

  EXPECT_EQ(field->getExportVal(0), nullptr);
}

TEST_F(FormFieldChoiceTest_914, GetExportValSupportsIndexingAcrossMultipleChoices_BoundaryLastIndex_914) {
  auto arr = std::make_unique<FormFieldChoice::ChoiceOpt[]>(3);
  arr[0].exportVal = std::make_unique<GooString>("Zero");
  arr[1].exportVal = std::make_unique<GooString>("One");
  arr[2].exportVal = std::make_unique<GooString>("Two");

  const GooString* expected0 = arr[0].exportVal.get();
  const GooString* expected2 = arr[2].exportVal.get();
  field->AdoptChoices(std::move(arr), 3);

  ASSERT_NE(field->getExportVal(0), nullptr);
  EXPECT_EQ(field->getExportVal(0), expected0);

  // Boundary: last valid index
  ASSERT_NE(field->getExportVal(2), nullptr);
  EXPECT_EQ(field->getExportVal(2), expected2);
}