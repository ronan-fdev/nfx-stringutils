# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

### Added

- NIL

### Changed

- NIL

### Deprecated

- NIL

### Removed

- NIL

### Fixed

- NIL

### Security

- NIL

## [1.1.0] - 2025-10-30

### Added

- **String Splitter**: Zero-allocation string splitting with C++20 iterator support
  - `Splitter` class for memory-efficient string splitting using `std::string_view`
  - `splitView()` factory function for convenient usage
  - Full C++20 forward iterator implementation with proper iterator traits
  - STL algorithm compatibility (`std::distance`, `std::find`, `std::count`, etc.)
  - Range-based for loop support for ergonomic iteration
  - Zero-copy design - segments reference original string memory without allocation

## [1.0.3] - 2025-10-30

### Fixed

- Removed unused variable `lastColonPos` in `isIPv6Address` function to eliminate dead code

## [1.0.2] - 2025-10-29

### Changed

- Refactored directory variable naming from `NFX_STRINGUTILS_ROOT_DIR` to `NFX_STRINGUTILS_DIR` for consistency

### Fixed

- Fixed incorrect CMake directory paths that would cause build failures in certain configurations:
  `CMAKE_CURRENT_SOURCE_DIR` was incorrectly used instead of `PROJECT_SOURCE_DIR` for root directory path

## [1.0.1] - 2025-10-27

### Fixed

- Fixed release workflow to create draft releases and avoid immutable release restrictions

## [1.0.0] - 2025-10-26 - Initial Release

### Added

- **String Utilities**: Common string manipulation functions

  - Case conversion
  - Whitespace trimming
  - String testing
  - All functions use `std::string_view` for zero-copy operations where possible
  - constexpr implementations for compile-time evaluation

- **Network & URI Validation**: RFC-compliant validation functions

  - IPv4 Validation (RFC 791)
  - IPv6 Validation (RFC 4291/5952)
  - Hostname Validation (RFC 1123)
  - Domain Name Validation (RFC 1035)
  - Port Validation (RFC 6335)
  - URI Character Classification (RFC 3986)
  - Endpoint Parsing

- **Build System**

  - CMake 3.20+ configuration with modular structure
  - Header-only interface library target
  - Cross-platform support (Linux GCC/Clang, Windows MinGW/Clang/MSVC)
  - Google Test integration for unit testing
  - Google Benchmark integration for performance benchmarking
  - Doxygen documentation generation with GitHub Pages deployment
  - CPack packaging for distribution (DEB, RPM, TGZ, ZIP, WiX MSI)
  - Installation support with CMake package config files

- **Documentation**

  - README with feature overview and usage examples
  - Detailed API documentation with Doxygen comments and RFC references
  - Sample applications
  - Build and installation instructions

- **Testing & Benchmarking**
  - Unit test suite
  - Performance benchmarks for all operations
  - Cross-compiler performance validation
