# C Code Standard

This standard applies to all production C source and header files in `src/`.
Its rules are mandatory unless an approved project-specific exception documents
the rule identifier, rationale, risk, and reviewer approval.

## 1. Language and build

| ID | Rule |
|---|---|
| CS-001 | Every `if`, `else`, `for`, `while`, and `do` body shall use braces, even for one statement. |
| CS-002 | Numeric literals other than `0` and `1` shall be named constants, macros, or enumeration values. |
| CS-003 | Every externally visible function declared in a header shall have a Doxygen-style documentation comment in its implementation. |
| CS-004 | Functions returning `aq_status_t` shall have their return value checked by the caller. |
| CS-005 | Source shall compile cleanly as C11 with `-Wall -Wextra -Werror`. |
| CS-006 | A source file with a corresponding module header shall include that header first, followed by standard-library headers and then other project headers. |
| CS-007 | Code shall not rely on compiler extensions, undefined behavior, unspecified behavior, or implementation-defined behavior unless the dependency is documented and controlled. |
| CS-008 | Each translation unit shall expose only the symbols required by other translation units; file-local functions and objects shall be declared `static`. |

## 2. Traceability and documentation

| ID | Rule |
|---|---|
| CS-009 | Each production function implementing behavior from a requirement shall identify the applicable HLR or LLR identifier in its Doxygen-style documentation comment. |
| CS-010 | A requirement shall be implemented by one or more identified source functions, and every implemented requirement shall be traceable from its requirement identifier to source code. |
| CS-011 | When a function implements a requirement with safety, range, timing, unit, or boundary constraints, its documentation shall state the constraint and the requirement identifier. |
| CS-012 | Comments shall explain intent, assumptions, units, ownership, or non-obvious decisions; they shall not restate the code. |
| CS-013 | A source change affecting requirement behavior shall update the relevant requirement traceability and verification evidence in the same change. |

## 3. Naming and declarations

| ID | Rule |
|---|---|
| CS-014 | Names shall be descriptive, unambiguous, and written in English. Abbreviations shall be avoided unless they are domain-standard, such as `aqi`. |
| CS-015 | Functions, variables, parameters, and structure members shall use `lower_snake_case`. |
| CS-016 | Type names shall use `lower_snake_case_t`; enumeration constants and macros shall use `UPPER_SNAKE_CASE`. |
| CS-017 | Boolean names shall express a predicate or state, such as `is_valid`, `has_data`, or `alert_active`. |
| CS-018 | Names shall include units when a value can be confused without them, for example `timeout_ms`, `temperature_c`, or `distance_mm`. |
| CS-019 | A pointer name shall indicate the pointed-to role, and an output parameter shall use a name such as `result`, `output`, or the produced value. |
| CS-020 | Variables shall be declared in the smallest scope that permits their use and initialized before their first read. |
| CS-021 | A declaration shall use a fixed-width integer type from `<stdint.h>` when storage width, range, protocol layout, or arithmetic bounds are relevant. |

## 4. Types, interfaces, and data validation

| ID | Rule |
|---|---|
| CS-022 | Public interfaces shall validate pointer parameters before dereferencing them, unless their non-null contract is explicitly documented. |
| CS-023 | Input values shall be validated at the boundary where they enter the module. Invalid input shall produce an explicit error status and shall not update state. |
| CS-024 | Enumerations shall be used for finite sets of named states, status values, and classifications. |
| CS-025 | Implicit narrowing conversions shall not be used. A narrowing conversion shall be justified by a prior range check and written as an explicit cast. |
| CS-026 | Signed and unsigned integer values shall not be mixed in comparisons or arithmetic without an explicit, reviewed conversion. |
| CS-027 | Array indexing shall be bounded by the array capacity. Capacity, length, and index types shall be compatible. |

## 5. Expressions and arithmetic

| ID | Rule |
|---|---|
| CS-028 | Each arithmetic expression shall use operands with compatible types and units. Values with different units shall be converted explicitly before the operation. |
| CS-029 | Intermediate types shall be selected so that addition, subtraction, multiplication, and accumulation cannot overflow for the documented input range. |
| CS-030 | Every division shall demonstrate that its divisor is non-zero before the division is performed. |
| CS-031 | Expressions containing more than one arithmetic, relational, logical, bitwise, or conditional operator shall use parentheses to make evaluation order explicit. |
| CS-032 | Side effects shall not be combined with other operations in an expression. In particular, `++`, `--`, assignments, and function calls with side effects shall appear in standalone statements, except for the iteration expression of a `for` loop. |
| CS-033 | Integer rounding, truncation, saturation, and overflow behavior shall be explicit and consistent with the applicable requirement. |
| CS-034 | Floating-point comparisons shall not use direct equality unless the compared value is an exact, documented representable value. Use a defined tolerance for calculated values. |
| CS-035 | Bitwise operations shall use unsigned operands and named masks, shifts, and bit positions. |

## 6. Control flow and error handling

| ID | Rule |
|---|---|
| CS-036 | Conditions shall express the positive intended state where practical. Complex conditions shall be decomposed into named Boolean variables or helper functions. |
| CS-037 | Every `switch` shall handle all enumeration values and include a `default` branch that fails safely or records the unexpected value. |
| CS-038 | Functions shall return errors to their caller rather than silently substituting a success-shaped value or ignoring a failed operation. |
| CS-039 | Error paths shall leave module state valid and shall not partially commit an operation unless that behavior is explicitly required. |
| CS-040 | Recursion, `goto`, and unbounded loops are prohibited unless a documented exception demonstrates bounded execution and stack use. |

## 7. Maintainability and verification

| ID | Rule |
|---|---|
| CS-041 | A function shall have one clear responsibility. Functions whose behavior cannot be understood without excessive nesting or multiple unrelated phases shall be decomposed. |
| CS-042 | Public functions shall document parameters, return values, side effects, ownership, units, valid ranges, and error conditions where applicable. |
| CS-043 | Dead code, commented-out code, unused functions, unused variables, and unused includes are prohibited. |
| CS-044 | Each behavioral requirement shall have at least one verification case covering its normal behavior, boundary values, and invalid inputs where applicable. |
| CS-045 | Test cases and review findings shall cite the requirement or standard identifier they verify. |
