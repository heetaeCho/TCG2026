The TEST_ID is 581

--- PROMPT START ---

You are given a partial implementation of a C++ class.
This class is already implemented and used in the actual codebase.
Your task is to write unit tests for the given interface, using Google Test (and Google Mock if needed), while strictly following the constraints below.

[Constraints]
1. **Do NOT re-implement or infer the internal logic** of any function.  
   You must treat the implementation as a black box.
2. **Write tests only based on the provided interface** — that is, based on:
   - Function signatures
   - Observable behavior (e.g., return values, effects visible through public functions or callback invocations)
3. **You may use Google Mock**:
   - Only when mocking external collaborators (e.g., passed-in handlers, callbacks, or dependencies)
   - Not to simulate internal behavior of the class under test
4. **Do NOT access or rely on private/internal state**, such as internal buffers, counters, or helper function behavior.
5. Include test cases for:
   - Normal operation
   - Boundary conditions
   - Exceptional or error cases (if observable through the interface)
   - Verification of external interactions (e.g., mock handler calls and their parameters)
6. Each test case should clearly indicate what behavior is being tested, and should follow consistent naming conventions.

[Requirements]
1. add TEST_ID for every Test name
   e.g.) TEST_F(WriteBatchTest_85, PutIncreasesCount_85), where The TEST_ID is 85

[Partial Code]
File name : Catch2/src/catch2/internal/catch_section.cpp
```cpp
namespace Catch { class Section { public: ~Section() { if( m_sectionIncluded ) { SectionEndInfo endInfo{ CATCH_MOVE(m_info), m_assertions, m_timer.getElapsedSeconds() }; if ( uncaught_exceptions() ) { getResultCapture().sectionEndedEarly( CATCH_MOVE(endInfo) ); } else { getResultCapture().sectionEnded( CATCH_MOVE( endInfo ) ); } } } }; }
```

---
[Known or Inferred Dependencies (Optional)]
File name : Catch2/src/catch2/catch_section_info.hpp
```cpp
namespace Catch { struct SectionEndInfo { public SectionInfo sectionInfo; public Counts prevAssertions; public double durationInSeconds; }; }}
```

File name : Catch2/src/catch2/interfaces/catch_interfaces_capture.hpp
```cpp
namespace Catch { class IResultCapture { public virtual void ~IResultCapture (); public virtual void notifyAssertionStarted (const AssertionInfo & info); public virtual bool sectionStarted (StringRef sectionName, const SourceLineInfo & sectionLineInfo, Counts & assertions); public virtual void sectionEnded (SectionEndInfo && endInfo); public virtual void sectionEndedEarly (SectionEndInfo && endInfo); public virtual IGeneratorTracker * acquireGeneratorTracker (StringRef generatorName, const SourceLineInfo & lineInfo); public virtual IGeneratorTracker * createGeneratorTracker (StringRef generatorName, SourceLineInfo lineInfo, Generators::GeneratorBasePtr && generator); public virtual void benchmarkPreparing (StringRef name); public virtual void benchmarkStarting (const BenchmarkInfo & info); public virtual void benchmarkEnded (const BenchmarkStats<> & stats); public virtual void benchmarkFailed (StringRef error); public virtual void pushScopedMessage (const MessageInfo & message); public virtual void popScopedMessage (const MessageInfo & message); public virtual void emplaceUnscopedMessage (MessageBuilder && builder); public virtual void handleFatalErrorCondition (StringRef message); public virtual void handleExpr (const AssertionInfo & info, const ITransientExpression & expr, AssertionReaction & reaction); public virtual void handleMessage (const AssertionInfo & info, struct ResultWas::OfType resultType, std::string && message, AssertionReaction & reaction); public virtual void handleUnexpectedExceptionNotThrown (const AssertionInfo & info, AssertionReaction & reaction); public virtual void handleUnexpectedInflightException (const AssertionInfo & info, std::string && message, AssertionReaction & reaction); public virtual void handleIncomplete (const AssertionInfo & info); public virtual void handleNonExpr (const AssertionInfo & info, struct ResultWas::OfType resultType, AssertionReaction & reaction); public virtual bool lastAssertionPassed (); public virtual void assertionPassed (); public virtual const std::string getCurrentTestName (); public virtual const const AssertionResult * getLastResult (); public virtual void exceptionEarlyReported (); public IResultCapture::~IResultCapture(); }; }}
```

File name : Catch2/src/catch2/catch_timer.hpp
```cpp
namespace Catch { class Timer { private uint64_t m_nanoseconds= 0; public  void start (); public const uint64_t getElapsedNanoseconds (); public const uint64_t getElapsedMicroseconds (); public const unsigned int getElapsedMilliseconds (); public const double getElapsedSeconds (); public void Timer::start(); public auto Timer::getElapsedNanoseconds() const -> uint64_t; public auto Timer::getElapsedMicroseconds() const -> uint64_t; public auto Timer::getElapsedMilliseconds() const -> unsigned int; public auto Timer::getElapsedSeconds() const -> double; }; }}
```

File name : Catch2/src/catch2/internal/catch_section.hpp
```cpp
namespace Catch { class Section : private Detail::NonCopyable { private SectionInfo m_info; private Counts m_assertions; private bool m_sectionIncluded; private Timer m_timer; public  Section (SectionInfo && info); public  Section (const SourceLineInfo & _lineInfo, StringRef _name, const char *const unnamed); public Section::Section( SectionInfo&& info ): m_info( CATCH_MOVE( info ) ), m_sectionIncluded( getResultCapture().sectionStarted( m_info.name, m_info.lineInfo, m_assertions ) ); public Section::Section( SourceLineInfo const& _lineInfo, StringRef _name, const char* const ): m_info(; public  void ~Section (); public const bool operator bool (); public Section::~Section(); public Section::operator bool() const; }; }}
```


--- PROMPT END ---
