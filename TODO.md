# nfx-stringutils TODO

Project roadmap and task tracking for the nfx-stringutils library.

### Todo

- [ ] Substring Extraction
  - [ ] substringBefore(str, delimiter) - extract before first occurrence
  - [ ] substringAfter(str, delimiter) - extract after first occurrence
  - [ ] substringBeforeLast(str, delimiter) - extract before last occurrence
  - [ ] substringAfterLast(str, delimiter) - extract after last occurrence
  - [ ] extractBetween(str, start, end) - extract between delimiters
  - [ ] removePrefix(str, prefix) - remove prefix if present
  - [ ] removeSuffix(str, suffix) - remove suffix if present
- [ ] Character & String Removal
  - [ ] removeAll(str, char) - remove all occurrences of character
  - [ ] removeAll(str, substr) - remove all occurrences of substring
  - [ ] removeIf(str, predicate) - remove characters matching predicate
  - [ ] removeWhitespace(str) - remove all whitespace characters
  - [ ] collapseWhitespace(str) - collapse consecutive whitespace to single space
- [ ] URL encoding/decoding
  - [ ] urlEncode(str) - percent-encode special characters
  - [ ] urlDecode(str) - decode percent-encoded strings
- [ ] JSON escape/unescape
  - [ ] jsonEscape(str) - escape quotes, backslashes, control characters
  - [ ] jsonUnescape(str) - unescape JSON string literals
- [ ] XML/HTML escape/unescape
  - [ ] xmlEscape(str) - escape &, <, >, ", '
  - [ ] xmlUnescape(str) - unescape XML entities
- [ ] C/C++ escape sequences
  - [ ] cppEscape(str) - escape \n, \t, \r, \\, \"
  - [ ] cppUnescape(str) - unescape C++ string literals
- [ ] Predicate-Based Operations
  - [ ] trimIf(str, predicate) - trim characters matching predicate
  - [ ] trimStartIf(str, predicate) - trim start with predicate
  - [ ] trimEndIf(str, predicate) - trim end with predicate
  - [ ] countIf(str, predicate) - count characters matching predicate
  - [ ] replaceIf(str, predicate, replacement) - replace characters matching predicate
  - [ ] findIf(str, predicate) - find first character matching predicate
  - [ ] findIfNot(str, predicate) - find first character NOT matching predicate
- [ ] Advanced Comparison
  - [ ] compareIgnoreCase(lhs, rhs) - three-way comparison (returns int)
  - [ ] naturalCompare(lhs, rhs) - natural sorting (handles embedded numbers)
  - [ ] fuzzyMatch(str, pattern) - fuzzy string matching
  - [ ] levenshteinDistance(lhs, rhs) - edit distance algorithm
  - [ ] commonPrefix(lhs, rhs) - longest common prefix
  - [ ] commonSuffix(lhs, rhs) - longest common suffix
- [ ] String Formatting Utilities
  - [ ] truncate(str, maxLength) - truncate string to max length
  - [ ] truncate(str, maxLength, ellipsis) - truncate with ellipsis ("...")
  - [ ] leftJustify(str, width, fillChar) - alias for padRight
  - [ ] rightJustify(str, width, fillChar) - alias for padLeft
  - [ ] wordWrap(str, width) - wrap text to specified width
  - [ ] indent(str, spaces) - indent all lines
  - [ ] dedent(str) - remove common leading whitespace

### v2.0.0 (Breaking Changes)

- [ ] Remove deprecated isValidPort(T) template function
  - Migration: use manual range check (port >= 0 && port <= 65535)
  - Update all documentation and samples
- [ ] SIMD optimizations for character searching (SSE2/AVX2)
- [ ] Optimize contains() with Boyer-Moore for longer patterns
- [ ] Benchmark-driven optimization of hot paths
- [ ] Unicode support (UTF-8, UTF-16, UTF-32)
  - [ ] utf8Length() - count Unicode codepoints
  - [ ] utf8Valid() - validate UTF-8 encoding
  - [ ] utf8Normalize() - Unicode normalization (NFC, NFD, NFKC, NFKD)
- [ ] Case conversion with locale support
- [ ] Collation and locale-aware comparison
- [ ] Regular Expression Utilities
  - [ ] regexMatch(str, pattern) - simple regex matching wrapper
  - [ ] regexReplace(str, pattern, replacement) - regex replacement
  - [ ] regexSplit(str, pattern) - split by regex pattern
- [ ] StringBuilder class for efficient string concatenation
  - [ ] Amortized growth strategy
  - [ ] Move semantics
  - [ ] Format string support
- [ ] Refactor parsing API to modern C++ idioms
  - [ ] Replace tryParseBool/tryParseInt/etc with unified template interface
  - [ ] Add std::optional<T> fromString<T>(std::string_view str)
  - [ ] Add bool fromString<T>(std::string_view str, T& result)
  - [ ] Deprecate old tryParse\* functions in v1.x
  - [ ] Remove tryParse\* functions in v2.0.0
  - [ ] Support types: bool, int, uint32_t, int64_t, float, double
  - [ ] Update all tests, samples, and documentation

### In Progress

- NIL

### Done ✓

#### v1.2.0 (2025-11-08)

- [x] String operations (count, countOverlapping, replace, replaceAll, join)
- [x] Formatting & padding (padLeft, padRight, center, repeat)
- [x] Search & manipulation (reverse, indexOf, lastIndexOf)
- [x] Parsing: tryParseFloat with NaN/inf support
- [x] Updated documentation and samples

#### v1.1.0 (2025-10-30)

- [x] Zero-allocation string splitting (Splitter class, splitView() factory)

#### v1.0.3 (2025-10-30)

- [x] Bug fix: Removed unused variable in isIPv6Address

#### v1.0.2 (2025-10-29)

- [x] Bug fix: CMake directory paths and variable naming

#### v1.0.1 (2025-10-27)

- [x] Bug fix: Release workflow draft releases
