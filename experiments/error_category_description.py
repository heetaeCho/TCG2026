CATEGORIE_DESCRIPTIONS = {
    "Lexical": {
        "description": "Errors occurring during preprocessing or tokenization, including invalid characters, macro argument mismatches, or missing header files.",
        "solution": "Consider fixing invalid characters or tokens, correcting macro argument counts, or including missing header files."
    },
    "Syntactic": {
        "description": "Errors caused by missing or misplaced syntactic elements such as parentheses, semicolons, or keywords.",
        "solution": "Consider adding missing syntactic elements or moving misplaced elements to the correct position."
    },
    "Linker": {
        "description": "Errors occurring during linking, such as undefined symbols, multiple definitions, or missing libraries.",
        "solution": "Consider adding missing symbol definitions, removing duplicate definitions, or adding required libraries to the link target."
    },
    "Semantic": {
        "description": "Errors that are syntactically valid but violate semantic constraints such as the type system, name lookup rules, access control, or initialization requirements.",
        "solution": "",
        "Abstract-Type Instantiation": {
            "description": "Attempt to directly instantiate, return, or assign an abstract class that has one or more unimplemented pure virtual functions.",
            "solution": "Consider verifying that all pure virtual functions are implemented in the concrete class that inherits from the abstract class, or replacing direct usage of the abstract class with a concrete class."
        },
        "Access Control": {
            "description": "Attempt to access private or protected members, constructors, or destructors that are not accessible in the current scope.",
            "solution": "Consider accessing through a public interface, or adopting test-friendly access patterns such as adding friend declarations or getters."
        },
        "Constexpr/Enum/Assert/Literal": {
            "description": "Violations of constexpr constraints, forward references to enum types, static_assert failures, or misuse of literal suffixes.",
            "solution": "Consider fixing expressions to be constant in constexpr contexts, including the header defining the enum, verifying the type/value logic of static_assert conditions, or checking literal suffixes."
        },
        "Construction/Initialization": {
            "description": "Failure to provide a valid constructor call, or violation of initialization rules for members or base classes.",
            "solution": "Consider verifying the number and types of constructor arguments, or adding missing default constructors or member initializations."
        },
        "Deleted/Special Member": {
            "description": "Attempt to invoke a deleted or implicitly deleted function, operator, or special member.",
            "solution": "Consider removing code that calls the deleted function, or passing the object by reference or other means instead of copying or moving."
        },
        "Functions/Call Resolution": {
            "description": "Function call is ambiguous or unresolvable due to overload conflicts or the absence of a callable target.",
            "solution": "Consider narrowing overload candidates with explicit casts or type specifications, or adjusting argument types to match the target signature."
        },
        "Operator/Call": {
            "description": "Failure to use an operator or call expression due to incompatible operand types or missing operator definitions.",
            "solution": "Consider verifying operand types and correcting them to compatible types, or checking whether the operator used is defined for the given type."
        },
        "Override/Inheritance": {
            "description": "Incorrect override signature, return type, or inheritance relationship defined in a subclass or mock class.",
            "solution": "Consider verifying the virtual function signature and return type in the base class, and aligning the override declaration in the subclass or mock class accordingly."
        },
        "Incomplete Type": {
            "description": "Attempt to use a type that is not fully defined at the point of use.",
            "solution": "Consider including the header containing the full definition of the type, or replacing the forward declaration with a complete definition."
        },
        "Symbol/Lookup": {
            "description": "Attempt to reference an identifier, member, namespace, or type that cannot be resolved in the current scope.",
            "solution": "Consider checking for typos, explicitly specifying the required namespace, or verifying that the referenced symbol actually exists."
        },
        "Templates/Generics": {
            "description": "Misuse of template arguments, specializations, or instantiations in a way the compiler cannot resolve.",
            "solution": "Consider explicitly specifying template arguments, fixing specialization syntax, or verifying that the template definition is included in the header."
        },
        "Type Conversion/Reference Binding": {
            "description": "Attempt to perform an invalid implicit or explicit type conversion, or to bind a reference to an incompatible value.",
            "solution": "Consider adding explicit casts, adjusting argument or variable types to match the target type, or verifying the type and lifetime of the object being bound to the reference."
        },
        "Type Redefinition/Redeclaration": {
            "description": "Attempt to redefine or redeclare a type, alias, or symbol that conflicts with an existing declaration.",
            "solution": "Consider removing duplicate declarations, checking header guards or include order, or verifying that the signature matches the existing declaration."
        },
        "Qualifier/Specifier Misuse": {
            "description": "Misuse of qualifiers or specifiers such as const, mutable, auto, or void in a context where they are not permitted.",
            "solution": "Consider verifying that the qualifier or specifier usage conforms to language rules, and removing or relocating it to a valid context."
        },
        "Pointer/Reference Misuse": {
            "description": "Violation of pointer or reference rules, such as taking the address of an rvalue or forming a pointer to a reference.",
            "solution": "Consider reviewing pointer and reference formation rules, using an lvalue instead of an rvalue, or removing unnecessary indirection."
        },
        "This/Non-Static Member/Using Misuse": {
            "description": "Incorrect use of this, non-static member references, or using declarations in an invalid context.",
            "solution": "Consider verifying that this is used within a non-static member function, accessing non-static members through an object, or checking that the target of the using declaration is valid."
        },
    },
}

CATEGORIE_DESCRIPTIONS_KR = { # Lexical = 15, Syntactic = 25, Linker = 4, Semantic = 227, Total = 271
    "Lexical": {"description": "잘못된 문자, 매크로 인자 오류, 헤더 파일 누락 등 전처리 또는 토크나이징 단계에서 발생하는 오류",
                "solution": "잘못된 문자나 토큰을 수정하거나, 매크로 인자 개수를 맞추거나, 누락된 헤더 파일을 include를 고려"},
    "Syntactic": {"description": "괄호, 세미콜론, 키워드 등 문법 요소의 누락 또는 잘못된 위치로 인해 발생하는 오류",
                "solution": "누락된 문법 요소를 추가하거나, 잘못된 위치의 문법 요소를 올바른 위치로 수정을 고려"},
    "Linker": {"description": "미정의 심볼, 중복 정의, 라이브러리 누락 등 링킹 단계에서 발생하는 오류",
                "solution": "누락된 심볼의 정의를 추가하거나, 중복 정의를 제거하거나, 필요한 라이브러리를 링크 대상에 추가를 고려"},
    # subtype = 16
    "Semantic": { 
        "description": "문법적으로는 올바르나 언어의 타입 시스템, 이름 조회, 접근 제어, 초기화 규칙 등 의미론적 제약을 위반하여 발생하는 오류",
        "solution": "",
        "Abstract-Type Instantiation": {"description": "순수 가상 함수(pure virtual functions)가 구현되지 않은 추상 클래스를 직접 인스턴스화, 리턴 또는 할당을 시도",
                "solution": "해당 추상 클래스를 상속한 Mock/Fake 클래스에서 모든 순수 가상 함수가 구현되어 있는지 확인하거나, 추상 클래스를 직접 사용하는 코드를 구체 클래스로 교체를 고려"},
        "Access Control": {"description": "현재 스코프에서 접근할 수 없는 private or protected 멤버, 생성자, 또는 소멸자에 접근을 시도",
                "solution": "Public 인터페이스를 통해 접근하거나, 테스트용 접근 방식(friend 선언, getter 추가 등)을 고려"},
        "Constexpr/Enum/Assert/Literal": {"description": "constexpr 제약 위반, enum 전방 선언, static_assert 실패, 또는 리터럴 suffix 오용",
                "solution": "constexpr 문맥에서 상수 표현식으로 수정, enum 정의 헤더 include, static_assert 조건의 타입/값 로직 확인 또는 literal suffix 확인을 고려"},
        "Construction/Initialization": {"description": "유효한 생성자 호출에 실패했거나, 멤버/베이스 클래스의 초기화 규칙을 위반",
                "solution": "생성자의 인자 타입/개수를 확인하고 일치시키거나, 누락된 기본 생성자 또는 멤버 초기화 추가를 고려"},
        "Deleted/Special Member": {"description": "삭제되었거나 암묵적으로(implicitly) 삭제된 함수, 연산자 또는 특수 멤버를 호출하려 시도",
                "solution": "삭제된 함수를 호출하는 코드를 제거하거나, 복사나 이동 대신 참조 등 다른 방식으로 객체 전달을 고려"},
        "Functions/Call Resolution": {"description": "오버로드 충돌 또는 호출 대상 부재로 함수 호출이 모호하거나 해석 불가능",
                "solution": "명시적 캐스트나 타입 지정으로 오버로드 후보를 좁히거나, 인자 타입을 호출 대상 시그니처에 맞게 수정을 고려"},
        "Operator/Call": {"description": "호환되지 않는 피연산자 타입이나 연산자 정의 누락으로 연산자 또는 호출 표현식 사용 실패",
                "solution": "피연산자 타입을 확인하고 호환되는 타입으로 수정하거나, 사용하는 연산자가 해당 타입에 정의되어 있는지 확인을 고려"},
        "Override/Inheritance": {"description": "Mock 또는 서브 클래스에서 override 시그니처, 반환 타입, 또는 상속 관계가 잘못 정의",
                "solution": "베이스 클래스의 가상 함수 시그니처와 반환 타입을 확인하고 Mock 클래스의 override 선언 일치를 고려"},
        "Incomplete Type": {"description": "사용 시점에 완전히 정의되지 않은 타입의 사용 시도",
                "solution": "해당 타입의 정의가 포함된 헤더를 include 하거나, 전방 선언을 완전한 정의로 교체를 고려"},
        "Symbol/Lookup": {"description": "현재 스코프에서 해석할 수 없는 식별자, 멤버, 네임스페이스 또는 타입을 참조하려 시도",
                "solution": "오타 여부를 확인하고, 필요한 네임스페이스를 명시하거나, 참조하는 심볼이 실제로 존재하는지 확인을 고려"},
        "Templates/Generics": {"description": "템플릿 인자, 특수화 또는 인스턴스화를 컴파일러가 해석할 수 없는 방식으로 사용",
                "solution": "템플릿 인자를 명시적으로 지정하거나, 특수화 문법 수정 및 템플릿 정의 헤더 include 확인을 고려"},
        "Type Conversion/Reference Binding": {"description": "유효하지 않은 암묵적/명시적 타입 변환을 수행하거나, 호환되지 않는 값(value)에 레퍼런스를 바인딩 시도",
                "solution": "명시적 캐스트를 추가하거나, 인자/변수 타입을 대상 타입에 맞게 수정하거나, 레퍼런스 바인딩 대상의 타입과 수명 확인을 고려"},
        "Type Redefinition/Redeclaration": {"description": "기존 타입, 별칭, 또는 심볼과 충돌하는 재정의 또는 재선언 시도",
                "solution": "중복 선언을 제거하거나, 헤더 가드 또는 include 순서를 확인하고, 시그니처가 기존 선언과 일치하는지 확인을 고려"},
        "Qualifier/Specifier Misuse": {"description": "const, mutable, auto, void 등의 한정자 또는 지정자를 허용되지 않는 문맥에서 오용",
                "solution": "해당 한정자/지정자의 사용 문맥이 언어 규칙에 맞는지 확인하고, 잘못 적용된 위치에서 제거하거나 올바른 문맥으로 이동을 고려"},
        "Pointer/Reference Misuse": {"description": "rvalue의 주소 취득, 레퍼런스에 대한 포인터 형성 등 포인터/레퍼런스 관련 규칙을 위반",
                "solution": "포인터/레퍼런스 형성 규칙을 확인하고, rvalue 대신 lvalue를 사용하거나 불필요한 간접 참조의 제거를 고려"},
        "This/Non-Static Member/Using Misuse": {"description": "this, non-static 멤버 참조 또는 using 선언을 유효하지 않은 문맥에서 잘못 사용함",
                "solution": "this 사용 문맥이 non-static 멤버 함수 내인지 확인하고, non-static 멤버는 객체를 통해 접근하도록 수정하거나, using 선언의 대상이 유효한지 확인을 고려"},
    },
}