PATTERNS = {
    # 선언에서 타입 지정자 누락
    1: (r"a type specifier is required for all declarations", "missing type specifier in declaration"),
    # 추상 클래스 타입 객체 할당 시도
    2: (r"allocating an object of abstract class type '.+?'(?:\s*\(aka '.+?'\))?", "allocating object of abstract class type"),
    # 불완전한 타입 객체 할당 시도
    3: (r"allocation of incomplete type '.+?'", "allocation of incomplete type"),
    # 함수형 캐스트에서 모호한 변환
    4: (r"ambiguous conversion for functional-style cast from '.+?' to '.+?'", "ambiguous conversion for functional-style cast"),
    # 속성 목록이 올 수 없는 위치
    5: (r"an attribute list cannot appear here", "attribute list in invalid position"),
    # 불완전한 타입 포인터에 대한 산술 연산
    6: (r"arithmetic on a pointer to an incomplete type '.+?'", "arithmetic on pointer to incomplete type"),
    # 기본 멤버 초기화자에서 배열 크기 추론 불가
    7: (r"array bound cannot be deduced from a default member initializer", "array bound cannot be deduced from default member initializer"),
    # 배열 타입 대입 불가
    8: (r"array type '.+?'(?:\s*\(aka '.+?'\))? is not assignable", "array type is not assignable"),
    # const 한정자 무시하고 대입
    9: (r"assigning to '.+?' from '.+?' discards qualifiers", "assigning discards qualifiers"),
    # 호환되지 않는 타입 대입
    10: (r"assigning to '.+?'(?:\s*\(aka '.+?'\))? from incompatible type '.+?'", "assigning from incompatible type"),
    # 삭제된 함수 사용 시도
    11: (r"attempt to use a deleted function", "attempt to use deleted function"),
    # final로 표시된 클래스 상속 시도
    12: (r"base '.+?' is marked 'final'", "base class marked final"),
    # 기본 클래스의 생성자가 private
    13: (r"base class '.+?' has private constructor", "base class has private constructor"),
    # 기본 클래스의 기본 생성자가 private
    14: (r"base class '.+?' has private default constructor", "base class has private default constructor"),
    # 기본 클래스의 소멸자가 private
    15: (r"base class '.+?' has private destructor", "base class has private destructor"),
    # 기본 클래스가 불완전한 타입
    16: (r"base class has incomplete type", "base class has incomplete type"),
    # 멤버 참조의 베이스가 함수
    17: (r"base of member reference is a function; perhaps you meant to call it with no arguments\?", "base of member reference is function"),
    # 베이스 지정자가 클래스를 가리키지 않음
    18: (r"base specifier must name a class", "base specifier must name a class"),
    # 참조 바인딩 시 한정자 제거
    19: (r"binding reference of type '.+?' to value of type '.+?' drops '(?:const|volatile)' qualifier", "binding reference drops qualifier"),
    # 배열 선언 시 괄호 위치 오류
    20: (r"brackets are not allowed here; to declare an array, place the brackets after the name", "brackets not allowed here"),
    # 삭제된 생성자 호출
    21: (r"call to deleted constructor of '.+?'(?:\s*\(aka '.+?'\))?", "call to deleted constructor"),
    # 암묵적으로 삭제된 생성자 호출
    22: (r"call to implicitly-deleted (?:copy|default) constructor of '.+?'(?:\s*\(aka '.+?'\))?", "call to implicitly-deleted constructor"),
    # 삭제된 함수 호출
    23: (r"call to deleted function '.+?'", "call to deleted function"),
    # 모호한 함수/생성자/멤버 함수 호출
    24: (r"call to (?:constructor of|member function|'.+?') '.+?' is ambiguous|call to '.+?' is ambiguous", "ambiguous call"),
    # 객체 인자 없이 비정적 멤버 함수 호출
    25: (r"call to non-static member function without an object argument", "call to non-static member function without object argument"),
    # 함수가 아닌 타입 호출 시도
    26: (r"called object type '.+?'(?:\s*\(aka '.+?'\))? is not a function or function pointer", "called object type is not a function or function pointer"),
    # 불완전한 반환 타입으로 함수 호출
    27: (r"calling '.+?'(?:\s*\(aka '.+?'\))? with incomplete return type '.+?'(?:\s*\(aka '.+?'\))?", "calling with incomplete return type"),
    # private/protected 생성자/소멸자 호출
    28: (r"calling a (?:private|protected) (?:constructor|destructor) of class '.+?'", "calling private or protected constructor or destructor"),
    # const 한정 타입에 대입 불가
    29: (r"cannot assign to (?:non-static data member|variable) '.+?' with const-qualified type '.+?'(?:\s*\(aka '.+?'\))?", "cannot assign to const-qualified type"),
    # 변환 연산자 없이 타입 변환 불가
    30: (r"cannot convert '.+?'(?:\s*\(aka '.+?'\))? to '.+?'(?:\s*\(aka '.+?'\))? without a conversion operator", "cannot convert without conversion operator"),
    # 네임스페이스 범위 밖에서 정의/재선언 불가
    31: (r"cannot define or redeclare '.+?' here because namespace '.*?' does not enclose namespace '.+?'", "cannot define or redeclare outside enclosing namespace"),
    # unique_ptr 표현식 delete 불가
    32: (r"cannot delete expression of type '.+?'", "cannot delete expression of type"),
    # void에 대한 참조 생성 불가
    33: (r"cannot form a reference to 'void'", "cannot form reference to void"),
    # 추론된 클래스 템플릿 특수화 타입에 대한 포인터/참조 생성 불가
    34: (r"cannot form (?:pointer|reference) to deduced class template specialization type", "cannot form pointer or reference to deduced class template specialization type"),
    # 타입 불일치로 초기화 불가
    35: (r"cannot initialize (?:a parameter|a variable|a member subobject|an array element|object parameter|return object) of type '.+?'(?:\s*\(aka '.+?'\))? with (?:an lvalue|an rvalue|an expression) of type '.+?'(?:\s*\(aka '.+?'\))?", "cannot initialize with incompatible type"),
    # ref-qualifier 없는 멤버 함수와 ref-qualifier 있는 멤버 함수 오버로드 불가
    36: (r"cannot overload a member function without a ref-qualifier with a member function with ref-qualifier '.+?'", "cannot overload member function with ref-qualifier mismatch"),
    # 종속 템플릿 특수화 불가
    37: (r"cannot specialize a dependent template", "cannot specialize dependent template"),
    # rvalue 주소 참조 불가
    38: (r"cannot take the address of an rvalue of type '.+?'", "cannot take address of rvalue"),
    # 예외 비활성화 상태에서 try/throw 사용 불가
    39: (r"cannot use '(?:try|throw)' with exceptions disabled", "cannot use try or throw with exceptions disabled"),
    # 불완전한 타입을 range로 사용 불가
    40: (r"cannot use incomplete type '.+?' as a range", "cannot use incomplete type as range"),
    # 식별자에 허용되지 않는 문자
    41: (r"character <.+?> not allowed in an identifier", "character not allowed in identifier"),
    # 문자 리터럴 타입에 비해 너무 큰 문자
    42: (r"character too large for enclosing character literal type", "character too large for character literal type"),
    # 클래스 멤버 재선언 불가
    43: (r"class member cannot be redeclared", "class member cannot be redeclared"),
    # 클래스 템플릿 부분 특수화가 올바른 네임스페이스 안에 없음
    44: (r"class template partial specialization of '.+?' not in a namespace enclosing '.+?'", "class template partial specialization not in enclosing namespace"),
    # 상수 표현식이 타입으로 좁혀질 수 없음
    45: (r"constant expression evaluates to .+? which cannot be narrowed to type '.+?'(?:\s*\(aka '.+?'\))?", "constant expression cannot be narrowed"),
    # constexpr 생성자의 매개변수 타입이 리터럴 타입이 아님
    46: (r"constexpr constructor's .+? parameter type '.+?'(?:\s*\(aka '.+?'\))? is not a literal type", "constexpr constructor parameter is not literal type"),
    # constexpr if 조건이 상수 표현식이 아님
    47: (r"constexpr if condition is not a constant expression", "constexpr if condition is not constant expression"),
    # constexpr 변수가 상수 표현식으로 초기화되지 않음
    48: (r"constexpr variable '.+?' must be initialized by a constant expression", "constexpr variable must be initialized by constant expression"),
    # constexpr 변수가 비리터럴 타입을 가질 수 없음
    49: (r"constexpr variable cannot have non-literal type '.+?'", "constexpr variable cannot have non-literal type"),
    # 생성자가 void 표현식을 반환하면 안됨
    50: (r"constructor '.+?' must not return void expression", "constructor must not return void expression"),
    # 기본 생성자 없는 기본 클래스/멤버 명시적 초기화 필요
    51: (r"constructor for '.+?' must explicitly initialize the (?:base class|member) '.+?' which does not have a default constructor", "constructor must explicitly initialize base class or member without default constructor"),
    # 초기화 리스트 원소 타입 추론 충돌
    52: (r"deduced conflicting types \('.+?' vs '.+?'(?:\s*\(aka '.+?'\))?\) for initializer list element type", "deduced conflicting types for initializer list element type"),
    # user-provided 기본 생성자 없는 const 타입 기본 초기화
    53: (r"default initialization of an object of const type '.+?' without a user-provided default constructor", "default initialization of const type without user-provided default constructor"),
    # 멤버 함수 밖에서 기본 멤버 초기화자 필요
    54: (r"default member initializer for '.+?' needed within definition of enclosing class '.+?' outside of member functions", "default member initializer needed outside of member functions"),
    # 타입 정의가 동일한 이름의 타입 별칭과 충돌
    55: (r"definition of type '.+?' conflicts with type alias of the same name", "definition conflicts with type alias"),
    # 삭제된 함수가 비삭제 함수를 오버라이드할 수 없음
    56: (r"deleted function '.+?' cannot override a non-deleted function", "deleted function cannot override non-deleted function"),
    # 불완전한 타입 포인터 삭제로 인한 미정의 동작
    57: (r"deleting pointer to incomplete type '.+?' may cause undefined behavior", "deleting pointer to incomplete type may cause undefined behavior"),
    # 중복 멤버 선언
    58: (r"duplicate member '.+?'", "duplicate member"),
    # 다른 기본 타입으로 열거형 재선언
    59: (r"enumeration redeclared with different underlying type '.+?' \(was '.+?'(?:\s*\(aka '.+?'\))?\)", "enumeration redeclared with different underlying type"),
    # 오버라이딩 함수의 예외 명세가 기본 버전보다 느슨함
    60: (r"exception specification of overriding function is more lax than base version", "exception specification more lax than base version"),
    # 스칼라 초기화자에 초과 원소
    61: (r"excess elements in scalar initializer", "excess elements in scalar initializer"),
    # 구문 기호/키워드 필요 (구체적인 패턴 먼저)
    62: (r"expected '\(' for function-style cast or type construction", "expected '(' for function-style cast or type construction"),
    63: (r"expected class name", "expected class name"),
    64: (r"expected expression", "expected expression"),
    65: (r"expected namespace name", "expected namespace name"),
    66: (r"expected parameter declarator", "expected parameter declarator"),
    67: (r"expected statement", "expected statement"),
    68: (r"expected unqualified-id", "expected unqualified-id"),
    # 구문 기호 누락 (일반, 위의 구체적 패턴 이후에 위치)
    69: (r"expected .+", "expected punctuation or keyword"),
    # 명시적으로 기본 설정된 생성자/소멸자가 암묵적으로 삭제됨
    70: (r"explicitly defaulted (?:default constructor|destructor) is implicitly deleted", "explicitly defaulted constructor or destructor is implicitly deleted"),
    # 대입 불가능한 표현식
    71: (r"expression is not assignable", "expression is not assignable"),
    # 사용되지 않는 표현식 결과
    72: (r"expression result unused", "expression result unused"),
    # 불필요한 닫는 중괄호
    73: (r"extraneous closing brace \('}'\)", "extraneous closing brace"),
    # 필드가 사용될 때 초기화되지 않음
    74: (r"field '.+?' is uninitialized when used here", "field is uninitialized when used"),
    # 필드가 불완전한 타입
    75: (r"field has incomplete type '.+?'", "field has incomplete type"),
    # 필드 타입의 기본 생성자/소멸자가 private
    76: (r"field of type '.+?' has private (?:(?:default )?constructor|destructor)", "field of type has private constructor or destructor"),
    # 필드 타입이 추상 클래스
    77: (r"field type '.+?'(?:\s*\(aka '.+?'\))? is an abstract class", "field type is abstract class"),
    # 포맷 문자열이 문자열 리터럴이 아님
    78: (r"format string is not a string literal \(potentially insecure\)", "format string is not a string literal"),
    # 함수가 함수 타입을 반환할 수 없음
    79: (r"function cannot return function type '.+?'(?:\s*\(aka '.+?'\))?", "function cannot return function type"),
    # 반환 타입만 다른 함수 오버로드 불가
    80: (r"functions that differ only in their return type cannot be overloaded", "functions differ only in return type cannot be overloaded"),
    # 암묵적 기본 생성자가 기본 생성자 없는 멤버 명시적 초기화 필요
    81: (r"implicit default constructor for '.+?' must explicitly initialize the member '.+?' which does not have a default constructor", "implicit default constructor must explicitly initialize member without default constructor"),
    # 정의되지 않은 템플릿의 암묵적 인스턴스화
    82: (r"implicit instantiation of undefined template '.+?'", "implicit instantiation of undefined template"),
    # 호환되지 않는 포인터 타입 대입
    83: (r"incompatible pointer types assigning to '.+?' from '.+?'", "incompatible pointer types assigning"),
    # 타입의 불완전한 정의
    84: (r"incomplete definition of type '.+?'", "incomplete definition of type"),
    # 함수 정의/람다에서 불완전한 결과 타입
    85: (r"incomplete result type '.+?'(?:\s*\(aka '.+?'\))? in (?:function definition|lambda expression)", "incomplete result type in function definition or lambda expression"),
    # 중첩 이름 지정자에 불완전한 타입
    86: (r"incomplete type '.+?' named in nested name specifier", "incomplete type in nested name specifier"),
    # 포인터 피연산자가 필요한 간접 참조
    87: (r"indirection requires pointer operand \('.+?'(?:\s*\(aka '.+?'\))? invalid\)", "indirection requires pointer operand"),
    # 불완전한 타입 초기화
    88: (r"initialization of incomplete type '.+?'(?:\s*\(aka '.+?'\))?", "initialization of incomplete type"),
    # 선언 끝에 잘못된 '=='
    89: (r"invalid '==' at end of declaration; did you mean '='\?", "invalid '==' at end of declaration"),
    # 불완전한 타입에 alignas/sizeof 적용 불가
    90: (r"invalid application of '(?:alignas|sizeof)' to an incomplete type '.+?'", "invalid application of alignas or sizeof to incomplete type"),
    # 이항 표현식에 잘못된 피연산자
    91: (r"invalid operands to binary expression \('.+?'(?:\s*\(aka '.+?'\))? and '.+?'(?:\s*\(aka '.+?'\))?\)", "invalid operands to binary expression"),
    # 잘못된 매개변수 이름 (키워드 사용)
    92: (r"invalid parameter name: '.+?' is a keyword", "invalid parameter name is keyword"),
    # 상수에 잘못된 접미사
    93: (r"invalid suffix '.+?' on (?:floating|integer) constant", "invalid suffix on constant"),
    # 잘못된 유니버설 문자
    94: (r"invalid universal character", "invalid universal character"),
    # 불완전한 타입 사용
    95: (r"invalid use of incomplete type '.+?'", "invalid use of incomplete type"),
    # 비정적 멤버 함수 외부에서 this 사용
    96: (r"invalid use of 'this' outside of a non-static member function", "invalid use of this outside non-static member function"),
    # enum 전방 선언 금지
    97: (r"ISO C\+\+ forbids forward references to 'enum' types", "ISO C++ forbids forward references to enum types"),
    # 불완전한 타입으로 멤버 접근
    98: (r"member access into incomplete type '.+?'(?:\s*\(aka '.+?'\))?", "member access into incomplete type"),
    # 멤버 초기화자가 비정적 데이터 멤버 또는 기본 클래스를 가리키지 않음
    99: (r"member initializer '.+?' does not name a non-static data member or base class", "member initializer does not name non-static data member or base class"),
    # 멤버 참조 기본 타입이 구조체 또는 유니온이 아님
    100: (r"member reference base type '.+?'(?:\s*\(aka '.+?'\))? is not a structure or union", "member reference base type is not structure or union"),
    # 잘못된 멤버 접근 연산자 사용
    101: (r"member reference type '.+?'(?:\s*\(aka '.+?'\))? is (?:not a pointer; did you mean to use '\.'|a pointer; did you mean to use '->')\?", "member reference type wrong operator"),
    # 'defined' 뒤에 ')' 누락
    102: (r"missing '\)' after 'defined'", "missing ')' after defined"),
    # 타입 참조 시 'class' 태그 필요
    103: (r"must use 'class' tag to refer to type '.+?' in this scope", "must use class tag to refer to type"),
    # 네임스페이스는 전역 또는 네임스페이스 범위에서만 정의 가능
    104: (r"namespaces can only be defined in global or namespace scope", "namespaces can only be defined in global or namespace scope"),
    # 네임스페이스에 해당 클래스 없음
    105: (r"no class named '.+?' in namespace '.+?'", "no class named in namespace"),
    # 함수 템플릿 특수화에 매칭되는 함수 템플릿 없음
    106: (r"no function template matches function template specialization '.+?'", "no function template matches specialization"),
    # 초기화에 매칭되는 생성자 없음
    107: (r"no matching constructor for initialization of '.+?'(?:\s*\(aka '.+?'\))?", "no matching constructor for initialization"),
    # 함수 스타일 캐스트에 매칭되는 변환 없음
    108: (r"no matching conversion for functional-style cast from '.+?'(?:\s*\(aka '.+?'\))? to '.+?'(?:\s*\(aka '.+?'\))?", "no matching conversion for functional-style cast"),
    # 매칭되는 함수/멤버 함수 없음
    109: (r"no matching (?:member )?function for call to (?:object of type )?'.+?'(?:\s*\(aka '.+?'\))?", "no matching function or member function for call"),
    # 매칭되는 리터럴 연산자 없음
    110: (r"no matching literal operator for call to '.+?' with arguments of types '.+?' and '.+?', and no matching literal operator template", "no matching literal operator for call"),
    # 네임스페이스/클래스/전역에 해당 멤버 없음
    111: (r"no member named '.+?' in (?:namespace '.+?'|'.+?'|the global namespace)(?:; did you mean .+?)?", "no member named in namespace or class"),
    # 네임스페이스/클래스/전역에 해당 타입/템플릿 없음 (113번 통합)
    112: (r"no (?:type|template) named '.+?'(?: in (?:namespace '.+?'|'.+?'|the global namespace))?(?:; did you mean (?:simply )?'.+?')?", "no type or template named in namespace or class"),
    # 템플릿 인수 추론을 위한 생성자 또는 추론 가이드 없음
    113: (r"no viable constructor or deduction guide for deduction of template arguments of '.+?'", "no viable constructor or deduction guide"),
    # 반환값 타입 변환 불가
    114: (r"no viable conversion from returned value of type '.+?'(?:\s*\(aka '.+?'\))? to function return type '.+?'(?:\s*\(aka '.+?'\))?", "no viable conversion from returned value"),
    # 타입 변환 불가
    115: (r"no viable conversion from '.+?'(?:\s*\(aka '.+?'\))? to (?:incomplete type )?'.+?'(?:\s*\(aka '.+?'\))?", "no viable conversion"),
    # 오버로드된 '=' 연산자 없음
    116: (r"no viable overloaded '='", "no viable overloaded '='"),
    # 오버로드된 [] 연산자 없음
    117: (r"no viable overloaded operator\[\] for type '.+?'(?:\s*\(aka '.+?'\))?", "no viable overloaded operator[]"),
    # non-const lvalue 참조 바인딩 불가
    118: (r"non-const lvalue reference to type '.+?'(?:\s*\(aka '.+?'\))? cannot bind to (?:a value of unrelated type|a temporary of type) '.+?'(?:\s*\(aka '.+?'\))?", "non-const lvalue reference cannot bind"),
    # 비친구 클래스 멤버에 한정된 이름 불가
    119: (r"non-friend class member '.+?' cannot have a qualified name", "non-friend class member cannot have qualified name"),
    # 비가상 멤버 함수가 가상 멤버 함수를 숨김
    120: (r"non-virtual member function marked 'override' hides virtual member function(?:s)?", "non-virtual member function marked override hides virtual member function"),
    # 네임스페이스에 해당 네임스페이스 없음
    121: (r"no namespace named '.+?' in namespace '.+?'(?:; did you mean '.+?')?", "no namespace named in namespace"),
    # constexpr 함수에 return 문 없음
    122: (r"no return statement in constexpr function", "no return statement in constexpr function"),
    # 변수 템플릿 특수화에 매칭되는 변수 템플릿 없음
    123: (r"no variable template matches specialization", "no variable template matches specialization"),
    # 복사 대입 연산자가 암묵적으로 삭제되어 대입 불가
    124: (r"object of type '.+?'(?:\s*\(aka '.+?'\))? cannot be assigned because its copy assignment operator is implicitly deleted", "object cannot be assigned because copy assignment operator is implicitly deleted"),
    # 가상 멤버 함수만 override 표시 가능
    125: (r"only virtual member functions can be marked 'override'", "only virtual member functions can be marked override"),
    # out-of-line 정의가 클래스 내 선언과 불일치
    126: (r"out-of-line definition of '.+?' does not match any declaration in '.+?'", "out-of-line definition does not match any declaration"),
    # 오버로드 해결 시 삭제된 연산자 선택
    127: (r"overload resolution selected deleted operator '='", "overload resolution selected deleted operator"),
    # 유효하지 않은 전처리 토큰 생성
    128: (r"pasting formed '.+?', an invalid preprocessing token", "pasting formed invalid preprocessing token"),
    # raw 문자열 종료 구분자 누락
    129: (r"raw string missing terminating delimiter \).+?\"", "raw string missing terminating delimiter"),
    # 다른 타입으로 재선언
    130: (r"redeclaration of '.+?' with a different type: '.+?' vs '.+?'", "redeclaration with different type"),
    # 재정의
    131: (r"redefinition of '.+?'(?: as different kind of symbol)?", "redefinition"),
    # 람다 표현식에서 선언된 지역 변수 참조
    132: (r"reference to local variable '.+?' declared in enclosing lambda expression", "reference to local variable in enclosing lambda"),
    # 비정적 멤버 함수 참조는 호출되어야 함
    133: (r"reference to non-static member function must be called(?:; did you mean to call it with no arguments\?)?", "reference to non-static member function must be called"),
    # 오버로드된 함수 참조 해결 불가
    134: (r"reference to overloaded function could not be resolved(?:; did you mean to call it\?)?", "reference to overloaded function could not be resolved"),
    # 타입 참조가 lvalue/rvalue에 바인딩 불가
    135: (r"reference to type '.+?' could not bind to (?:an lvalue|an rvalue) of type '.+?'", "reference to type could not bind"),
    # reinterpret_cast 불가
    136: (r"reinterpret_cast from '.+?' to '.+?'(?:\s*\(aka '.+?'\))? is not allowed", "reinterpret_cast is not allowed"),
    # 람다 반환 타입 불일치
    137: (r"return type '.+?'(?:\s*\(aka '.+?'\))? must match previous return type '.+?' when lambda expression has unspecified explicit return type", "return type must match previous return type in lambda"),
    # 반환 타입이 추상 클래스
    138: (r"return type '.+?'(?:\s*\(aka '.+?'\))? is an abstract class", "return type is abstract class"),
    # 가상 함수의 반환 타입이 공변적이지 않음
    139: (r"return type of virtual function '.+?' is not covariant with the return type of the function it overrides", "return type of virtual function is not covariant"),
    # .* 연산자의 우측 피연산자가 멤버 포인터 타입이 아님
    140: (r"right hand operand to \.\* has non-pointer-to-member type '.+?'(?:\s*\(aka '.+?'\))?", "right hand operand to .* has non-pointer-to-member type"),
    # rvalue 참조가 lvalue에 바인딩 불가
    141: (r"rvalue reference to type '.+?' cannot bind to lvalue of type '.+?'", "rvalue reference cannot bind to lvalue"),
    # 모호한 참조
    142: (r"reference to '.+?' is ambiguous", "reference is ambiguous"),
    # 정적 어서션 표현식이 정수 상수 표현식이 아님
    143: (r"static assertion expression is not an integral constant expression", "static assertion expression is not integral constant expression"),
    # 정적 어서션 실패
    144: (r"static assertion failed.*", "static assertion failed"),
    # 지역 구조체에 정적 데이터 멤버 불가
    145: (r"static data member '.+?' not allowed in local struct '.+?'", "static data member not allowed in local struct"),
    # 상속 관계 없는 타입 간 static_cast 불가
    146: (r"static_cast from '.+?'(?:\s*\(aka '.+?'\))? to '.+?', which are not related by inheritance, is not allowed", "static_cast between unrelated types is not allowed"),
    # 불완전한 타입 포인터 서브스크립트
    147: (r"subscript of pointer to incomplete type '.+?'", "subscript of pointer to incomplete type"),
    # 서브스크립트 대상이 배열/포인터/벡터가 아님
    148: (r"subscripted value is not an array, pointer, or vector", "subscripted value is not array pointer or vector"),
    # 템플릿 타입 매개변수에 타입이 아닌 인자
    149: (r"template argument for template type parameter must be a type", "template argument must be a type"),
    # 템플릿 템플릿 매개변수에 클래스 템플릿 또는 타입 별칭 템플릿이 아닌 인자
    150: (r"template argument for template template parameter must be a class template or type alias template", "template argument for template template parameter must be class template or type alias template"),
    # 템플릿 특수화에 'template<>' 필요
    151: (r"template specialization requires 'template<>'", "template specialization requires template<>"),
    # 템플릿 템플릿 인자의 템플릿 매개변수가 다름
    152: (r"template template argument has different template parameters than its corresponding template template parameter", "template template argument has different template parameters"),
    # 지역 클래스 내부에 템플릿 선언 불가
    153: (r"templates cannot be declared inside of a local class", "templates cannot be declared inside local class"),
    # 함수 호출 인자 부족
    154: (r"too few arguments to function call, expected \d+, have \d+(?:; did you mean '.+?')?", "too few arguments to function call"),
    # 템플릿 인자 부족
    155: (r"too few template arguments for (?:alias template|class template) '.+?'", "too few template arguments"),
    # 함수형 매크로 인자 과다
    156: (r"too many arguments provided to function-like macro invocation", "too many arguments to function-like macro"),
    # 함수 호출 인자 과다
    157: (r"too many arguments to function call, expected .+?, have .+?", "too many arguments to function call"),
    # 직접/가상 기본 클래스가 아닌 타입
    158: (r"type '.+?' is not a direct or virtual base of '.+?'", "type is not direct or virtual base"),
    # 타입이 좁혀질 수 없음
    159: (r"type '.+?' cannot be narrowed to '.+?'(?:\s*\(aka '.+?'\))? in initializer list", "type cannot be narrowed in initializer list"),
    # 타입이 서브스크립트 연산자를 제공하지 않음
    160: (r"type '.+?'(?:\s*\(aka '.+?'\))? does not provide a (?:subscript|call) operator", "type does not provide subscript or call operator"),
    # 타입 별칭 재정의 시 타입 불일치
    161: (r"type alias redefinition with different types \('.+?' vs '.+?'\)", "type alias redefinition with different types"),
    # 참조의 참조 타입 이름 선언
    162: (r"type name declared as a reference to a reference", "type name declared as reference to reference"),
    # 예상치 못한 문자
    163: (r"unexpected character <.+?>", "unexpected character"),
    # 예상치 못한 네임스페이스 이름
    164: (r"unexpected namespace name '.+?': expected expression", "unexpected namespace name"),
    # 알 수 없는 클래스 이름
    165: (r"unknown class name '.+?'(?:; did you mean '.+?')?", "unknown class name"),
    # 알 수 없는 타입 이름
    166: (r"unknown type name '.+?'(?:; did you mean '.+?')?", "unknown type name"),
    # 함수형 매크로 호출이 종료되지 않음
    167: (r"unterminated function-like macro invocation", "unterminated function-like macro invocation"),
    # 이전 선언과 일치하지 않는 태그 타입으로 OfType 사용
    168: (r"use of 'OfType' with tag type that does not match previous declaration", "use of OfType with mismatched tag type"),
    # 클래스 템플릿에 템플릿 인자 필요
    169: (r"use of class template '.+?' requires template arguments(?:; argument deduction not allowed .+?)?", "use of class template requires template arguments"),
    # 오버로드된 [] 연산자 사용이 모호함
    170: (r"use of overloaded operator '\[\]' is ambiguous \(with operand types '.+?' and '.+?'\)", "use of overloaded operator[] is ambiguous"),
    # 선언되지 않은 식별자 사용
    171: (r"use of undeclared identifier '.+?'(?:; did you mean '.+?')?", "use of undeclared identifier"),
    # 선언되지 않은 operator() 사용
    172: (r"use of undeclared 'operator\(\)'", "use of undeclared operator()"),
    # using 선언이 클래스 멤버를 참조할 수 없음
    173: (r"using declaration cannot refer to (?:class member|a namespace)", "using declaration cannot refer to class member or namespace"),
    # using 선언이 클래스가 아닌 네임스페이스를 참조함
    174: (r"using declaration in class refers into '.+?', which is not a class", "using declaration in class refers to non-class"),
    # bool로 문맥 변환 불가
    175: (r"value of type '.+?'(?:\s*\(aka '.+?'\))? is not contextually convertible to 'bool'", "value is not contextually convertible to bool"),
    # 캡처 기본값 없는 람다에서 암묵적 캡처 불가
    176: (r"variable '.+?' cannot be implicitly captured in a lambda with no capture-default specified", "variable cannot be implicitly captured in lambda"),
    # auto 타입 변수의 호환되지 않는 초기화자
    177: (r"variable '.+?' with type 'auto' has incompatible initializer of type '.+?'", "variable with auto type has incompatible initializer"),
    # auto 추론 타입 변수가 자신의 초기화자에 등장
    178: (r"variable '.+?' declared with deduced type 'auto' cannot appear in its own initializer", "variable with deduced auto type cannot appear in its own initializer"),
    # 불완전한 타입의 변수
    179: (r"variable has incomplete type '.+?'(?:\s*\(aka '.+?'\))?", "variable has incomplete type"),
    # private/protected 소멸자를 가진 타입의 변수
    180: (r"variable of type '.+?' has (?:private|protected) destructor", "variable of type has private or protected destructor"),
    # 변수 타입이 추상 클래스
    181: (r"variable type '.+?'(?:\s*\(aka '.+?'\))? is an abstract class", "variable type is abstract class"),
    # 가상 함수의 반환 타입이 오버라이드하는 함수와 다름
    182: (r"virtual function '.+?' has a different return type \('.+?'(?:\s*\(aka '.+?'\))?\) than the function it overrides \(which has return type '.+?'\)", "virtual function has different return type than overridden function"),
    # 가변 크기 객체 초기화 불가
    183: (r"variable-sized object may not be initialized", "variable-sized object may not be initialized"),
    # 파일을 찾을 수 없음
    185: (r"'.+?' file not found", "file not found"),
    # private/protected 멤버 접근
    186: (r"'.+?' is a (?:private|protected) member of '.+?'", "private or protected member access"),
    # 불완전한 타입
    187: (r"'.+?' is an incomplete type", "incomplete type"),
    # const가 아닌 함수에 const 객체로 this 인자 전달
    188: (r"'this' argument to member function '.+?' has type '.+?'(?:\s*\(aka '.+?'\))?, but function is not marked const", "this argument to non-const member function"),
    # auto가 함수 프로토타입에서 허용되지 않음
    189: (r"'auto' not allowed in function prototype", "auto not allowed in function prototype"),
    # const 한정자가 참조에 적용될 수 없음
    190: (r"'const' qualifier may not be applied to a reference", "const qualifier may not be applied to reference"),
    # mutable이 함수에 적용될 수 없음
    191: (r"'mutable' cannot be applied to functions", "mutable cannot be applied to functions"),
    # using namespace가 클래스 내부에서 허용되지 않음
    192: (r"'using namespace' is not allowed in classes", "using namespace not allowed in classes"),
    # void가 첫 번째이자 유일한 매개변수여야 함
    193: (r"'void' must be the first and only parameter if specified", "void must be first and only parameter"),
    # override가 표시됐지만 오버라이드하는 함수가 없음
    194: (r"'.+?' marked 'override' but does not override any member functions", "marked override but does not override any member functions"),
    # 값을 참조할 수 없는 식별자
    195: (r"'.+?' does not refer to a value", "does not refer to a value"),
    # gmock_xxx가 함수 배열로 선언됨
    196: (r"'.+?' declared as array of functions of type '.+?'(?:\s*\(aka '.+?'\))?", "declared as array of functions"),
    # va_start가 고정 인자 함수에서 사용됨
    197: (r"'va_start' used in function with fixed args", "va_start used in function with fixed args"),
    # 클래스, 네임스페이스, 열거형이 아닌 식별자
    198: (r"'.+?' is not a class, namespace, or enumeration", "is not a class namespace or enumeration"),
    # 참조에 대한 포인터로 선언된 타입 이름
    199: (r"'.+?' declared as a pointer to a reference of type '.+?'(?:\s*\(aka '.+?'\))?", "declared as pointer to reference"),
    # 다형성이 아닌 타입
    200: (r"'.+?' is not polymorphic", "is not polymorphic"),
}