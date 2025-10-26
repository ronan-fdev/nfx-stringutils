# nfx-stringutils

<!-- Project Info -->

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg?style=flat-square)](https://github.com/ronan-fdev/nfx-stringutils/blob/main/LICENSE.txt) [![GitHub release (latest by date)](https://img.shields.io/github/v/release/ronan-fdev/nfx-stringutils?style=flat-square)](https://github.com/ronan-fdev/nfx-stringutils/releases) [![GitHub tag (latest by date)](https://img.shields.io/github/tag/ronan-fdev/nfx-stringutils?style=flat-square)](https://github.com/ronan-fdev/nfx-stringutils/tags)<br/>

![C++20](https://img.shields.io/badge/C%2B%2B-20-blue?style=flat-square) ![CMake](https://img.shields.io/badge/CMake-3.20%2B-green.svg?style=flat-square) ![Cross Platform](https://img.shields.io/badge/Platform-Linux_Windows-lightgrey?style=flat-square)

<!-- CI/CD Status -->

[![Linux GCC](https://img.shields.io/github/actions/workflow/status/ronan-fdev/nfx-stringutils/build-linux-gcc.yml?branch=main&label=Linux%20GCC&style=flat-square)](https://github.com/ronan-fdev/nfx-stringutils/actions/workflows/build-linux-gcc.yml) [![Linux Clang](https://img.shields.io/github/actions/workflow/status/ronan-fdev/nfx-stringutils/build-linux-clang.yml?branch=main&label=Linux%20Clang&style=flat-square)](https://github.com/ronan-fdev/nfx-stringutils/actions/workflows/build-linux-clang.yml) [![Windows MinGW](https://img.shields.io/github/actions/workflow/status/ronan-fdev/nfx-stringutils/build-windows-mingw.yml?branch=main&label=Windows%20MinGW&style=flat-square)](https://github.com/ronan-fdev/nfx-stringutils/actions/workflows/build-windows-mingw.yml) [![Windows MSVC](https://img.shields.io/github/actions/workflow/status/ronan-fdev/nfx-stringutils/build-windows-msvc.yml?branch=main&label=Windows%20MSVC&style=flat-square)](https://github.com/ronan-fdev/nfx-stringutils/actions/workflows/build-windows-msvc.yml) [![CodeQL](https://img.shields.io/github/actions/workflow/status/ronan-fdev/nfx-stringutils/codeql.yml?branch=main&label=CodeQL&style=flat-square)](https://github.com/ronan-fdev/nfx-stringutils/actions/workflows/codeql.yml)

> A C++20 string utilities library with validation and manipulation functions for cross-platform string operations

## Overview

nfx-stringutils is a modern C++20 header-only library providing high-performance string validation, and manipulation utilities. It offers comprehensive string operations including character classification, case conversion, trimming, boolean/numeric and URI validation optimized for performance across multiple platforms and compilers.

## Features

### ✅ String Validation & Classification

- **Character Classification**: `isWhitespace()`, `isDigit()`, `isAlpha()`, `isAlphaNumeric()`
- **String Validation**: `isEmpty()`, `isNullOrWhiteSpace()`, `isAllDigits()`, `hasExactLength()`
- **URI Character Classification**: `isURIReserved()`, `isURIUnreserved()` with RFC 3986 compliance

### 🌐 Network & URI Validation

- **IPv4 Address Validation**: `isIPv4Address()` with RFC 791 compliance (rejects leading zeros)
- **IPv6 Address Validation**: `isIPv6Address()` with RFC 4291/5952 compliance (supports compression and IPv4-mapped)
- **Hostname Validation**: `isValidHostname()` with RFC 1123 compliance (max 253 chars, labels max 63 chars)
- **Domain Name Validation**: `isDomainName()` with RFC 1035 compliance (requires FQDN format)
- **Port Validation**: `isValidPort()` with RFC 6335 compliance (0-65535 range, compile-time type safety)
- **Endpoint Parsing**: `tryParseEndpoint()` supports IPv4:port, hostname:port, [IPv6]:port formats

### 🔧 String Operations

- **String Comparison**: `startsWith()`, `endsWith()`, `contains()`, `equals()`, `iequals()` (case-insensitive)
- **String Trimming**: `trim()`, `trimStart()`, `trimEnd()` with non-allocating stringView versions
- **Case Conversion**: `toLower()`, `toUpper()` for both characters and strings

### ⚡ Performance Optimized

- Header-only library with zero runtime dependencies
- Highly optimized parsing and validation
- Efficient string operations with minimal allocations
- Zero-cost abstractions with constexpr support
- Compiler-optimized inline implementations

### 🌍 Cross-Platform Support

- Linux, Windows
- GCC 14+, Clang 19+, MSVC 2022+
- Thread-safe operations
- Consistent behavior across platforms

## Quick Start

### Requirements

- C++20 compatible compiler:
  - **GCC 14+** (14.2.0 tested)
  - **Clang 18+** (19.1.7 tested)
  - **MSVC 2022+** (19.44+ tested)
- CMake 3.20 or higher

### CMake Integration

```cmake
# Development options
option(NFX_STRINGUTILS_BUILD_TESTS          "Build tests"                        ON  )
option(NFX_STRINGUTILS_BUILD_SAMPLES        "Build samples"                      ON  )
option(NFX_STRINGUTILS_BUILD_BENCHMARKS     "Build benchmarks"                   ON  )
option(NFX_STRINGUTILS_BUILD_DOCUMENTATION  "Build Doxygen documentation"        ON  )

# Installation and packaging
option(NFX_STRINGUTILS_INSTALL_PROJECT      "Install project"                    ON  )
option(NFX_STRINGUTILS_PACKAGE_SOURCE       "Enable source package generation"   ON  )
option(NFX_STRINGUTILS_PACKAGE_ARCHIVE      "Enable TGZ/ZIP package generation"  ON  )
option(NFX_STRINGUTILS_PACKAGE_DEB          "Enable DEB package generation"      ON  )
option(NFX_STRINGUTILS_PACKAGE_RPM          "Enable RPM package generation"      ON  )
option(NFX_STRINGUTILS_PACKAGE_WIX          "Enable WiX MSI installer"           ON  )
```

### Using in Your Project

#### Option 1: Using FetchContent (Recommended)

```cmake
include(FetchContent)
FetchContent_Declare(
  nfx-stringutils
  GIT_REPOSITORY https://github.com/ronan-fdev/nfx-stringutils.git
  GIT_TAG        main  # or use specific version tag like "1.0.0"
)
FetchContent_MakeAvailable(nfx-stringutils)

# Link with header-only interface library
target_link_libraries(your_target PRIVATE nfx-stringutils::nfx-stringutils)
```

#### Option 2: As a Git Submodule

```bash
# Add as submodule
git submodule add https://github.com/ronan-fdev/nfx-stringutils.git third-party/nfx-stringutils
```

```cmake
# In your CMakeLists.txt
add_subdirectory(third-party/nfx-stringutils)
target_link_libraries(your_target PRIVATE nfx-stringutils::nfx-stringutils)
```

#### Option 3: Using find_package (After Installation)

```cmake
find_package(nfx-stringutils REQUIRED)
target_link_libraries(your_target PRIVATE nfx-stringutils::nfx-stringutils)
```

###Building

```bash
# Clone the repository
git clone https://github.com/ronan-fdev/nfx-stringutils.git
cd nfx-stringutils

# Create build directory
mkdir build && cd build

# Configure with CMake
cmake .. -DCMAKE_BUILD_TYPE=Release

# Build the library
cmake --build . --config Release --parallel

# Run tests (optional)
ctest -C Release --output-on-failure

# Run benchmarks (optional)
./build/bin/benchmarks/BM_StringUtilities
```

### Documentation

nfx-stringutils includes comprehensive API documentation generated with Doxygen.

#### 📚 Online Documentation

The complete API documentation is available online at:
**https://ronan-fdev.github.io/nfx-stringutils**

#### Building Documentation Locally

```bash
# Configure with documentation enabled
cmake .. -DCMAKE_BUILD_TYPE=Release -DNFX_STRINGUTILS_BUILD_DOCUMENTATION=ON

# Build the documentation
cmake --build . --target documentation
```

#### Requirements

- **Doxygen** - Documentation generation tool
- **Graphviz Dot** (optional) - For generating class diagrams

#### Accessing Local Documentation

After building, open `./build/doc/html/index.html` in your web browser.

## Usage Examples

### String Validation & Classification

```cpp
#include <nfx/string/Utils.h>

using namespace nfx::string;

// String validation
bool empty = isEmpty("");                    // true
bool whitespace = isNullOrWhiteSpace("   "); // true
bool digits = isAllDigits("12345");          // true
bool length = hasExactLength("password", 8); // true

// Character classification
bool space = isWhitespace(' ');              // true
bool digit = isDigit('5');                   // true
bool alpha = isAlpha('A');                   // true
bool alnum = isAlphaNumeric('Z');            // true

// URI classification (RFC 3986)
bool reserved = isURIReserved(':');          // true
bool unreserved = isURIUnreserved('A');      // true
```

### String Operations & Manipulation

```cpp
#include <nfx/string/Utils.h>

using namespace nfx::string;

std::string_view text = "  Hello World  ";

// String operations
bool starts = startsWith(text, "  Hello");      // true
bool ends = endsWith(text, "World  ");          // true
bool contains_word = contains(text, "World");   // true
bool equal = equals(text, "  Hello World  ");   // true
bool iequal = iequals("HELLO", "hello");        // true (case-insensitive)

// String trimming (non-allocating)
std::string_view trimmed = trim(text);          // "Hello World"
std::string_view left = trimStart(text);        // "Hello World  "
std::string_view right = trimEnd(text);         // "  Hello World"

// Case conversion
char lower = toLower('A');                      // 'a'
char upper = toUpper('z');                      // 'Z'
std::string lowerStr = toLower("Hello World");  // "hello world"
std::string upperStr = toUpper("Hello World");  // "HELLO WORLD"
```

### Parsing Utilities

```cpp
#include <nfx/string/Utils.h>

using namespace nfx::string;

// Boolean parsing (supports multiple formats)
bool result;
bool success1 = tryParseBool("true", result);    // true, result = true
bool success2 = tryParseBool("yes", result);     // true, result = true
bool success3 = tryParseBool("1", result);       // true, result = true
bool success4 = tryParseBool("false", result);   // true, result = false
bool success5 = tryParseBool("invalid", result); // false

// Numeric parsing
int intValue;
bool intOk = tryParseInt("12345", intValue);     // true, intValue = 12345

std::uint32_t uintValue;
bool uintOk = tryParseUInt("42", uintValue);     // true, uintValue = 42

std::int64_t longValue;
bool longOk = tryParseLong("-9223372036854775808", longValue); // true

double doubleValue;
bool doubleOk = tryParseDouble("123.456", doubleValue); // true, doubleValue = 123.456
```

### Network & URI Validation

```cpp
#include <nfx/string/Utils.h>

using namespace nfx::string;

// IP address validation
bool ipv4Valid = isIPv4Address("192.168.1.1");       // true
bool ipv4Invalid = isIPv4Address("256.1.1.1");       // false (out of range)
bool ipv4LeadingZero = isIPv4Address("01.02.03.04"); // false (leading zeros)

bool ipv6Valid = isIPv6Address("2001:db8::1");       // true
bool ipv6Loopback = isIPv6Address("::1");            // true
bool ipv6Mapped = isIPv6Address("::ffff:192.0.2.1"); // true (IPv4-mapped)
bool ipv6Zone = isIPv6Address("fe80::1%eth0");       // true (with zone ID)

// Hostname and domain validation
bool hostnameValid = isValidHostname("example.com");  // true
bool hostnameLocal = isValidHostname("localhost");    // true
bool hostnameInvalid = isValidHostname("-invalid");   // false (starts with hyphen)

bool domainValid = isDomainName("example.com");       // true (has dot)
bool domainInvalid = isDomainName("localhost");       // false (no dot, not FQDN)

// Port validation (compile-time type safety)
bool portValid = isValidPort(80);                    // true
bool portMax = isValidPort(65535);                   // true
bool portInvalid = isValidPort(70000);               // false (out of range)
bool portStringValid = isValidPort("8080");          // true

// Endpoint parsing (host:port format)
std::string_view host;
uint16_t port;

// IPv4 endpoint
bool ep1 = tryParseEndpoint("192.168.1.1:80", host, port);
// host = "192.168.1.1", port = 80

// IPv6 endpoint (requires brackets)
bool ep2 = tryParseEndpoint("[2001:db8::1]:443", host, port);
// host = "2001:db8::1", port = 443

// Hostname endpoint
bool ep3 = tryParseEndpoint("example.com:8080", host, port);
// host = "example.com", port = 8080
```

## Installation & Packaging

nfx-stringutils provides comprehensive packaging options for distribution.

### Package Generation

```bash
# Configure with packaging options
cmake .. -DCMAKE_BUILD_TYPE=Release \
         -DNFX_STRINGUTILS_PACKAGE_ARCHIVE=ON \
         -DNFX_STRINGUTILS_PACKAGE_DEB=ON \
         -DNFX_STRINGUTILS_PACKAGE_RPM=ON

# Generate binary packages
cmake --build . --target package
# or
cd build && cpack

# Generate source packages
cd build && cpack --config CPackSourceConfig.cmake
```

### Supported Package Formats

| Format      | Platform       | Description                        | Requirements |
| ----------- | -------------- | ---------------------------------- | ------------ |
| **TGZ/ZIP** | Cross-platform | Compressed archive packages        | None         |
| **DEB**     | Debian/Ubuntu  | Native Debian packages             | `dpkg-dev`   |
| **RPM**     | RedHat/SUSE    | Native RPM packages                | `rpm-build`  |
| **WiX**     | Windows        | Professional MSI installer         | `WiX 3.11+`  |
| **Source**  | Cross-platform | Source code distribution (TGZ+ZIP) | None         |

### Installation

```bash
# Linux (DEB-based systems)
sudo dpkg -i nfx-stringutils_*_amd64.deb

# Linux (RPM-based systems)
sudo rpm -ivh nfx-stringutils-*-Linux.rpm

# Windows
# Run the .exe installer with administrator privileges
nfx-stringutils-*-win64.exe

# Manual installation (extract archive)
tar -xzf nfx-stringutils-*-Linux.tar.gz -C /usr/local/
```

## Project Structure

```
nfx-stringutils/
├── benchmark/             # Performance benchmarks with Google Benchmark
├── cmake/                 # CMake modules and configuration
├── include/nfx/           # Public headers: string utilities
├── samples/               # Example usage and demonstrations
└── test/                  # Comprehensive unit tests with GoogleTest
```

## Performance

nfx-stringutils is optimized for high performance with:

- **Zero-allocation operations** where possible (e.g., string trimming with stringView)
- **Constexpr functions** for compile-time optimization
- **Highly optimized character classification** (faster than std library equivalents)
- **Efficient string parsing** with minimal overhead

For detailed performance metrics and benchmarks, see the [benchmark documentation](benchmark/README.md).

## Changelog

See the [changelog](CHANGELOG.md) for a detailed history of changes, new features, and bug fixes.

## License

This project is licensed under the MIT License.

## Dependencies

- **[GoogleTest](https://github.com/google/googletest)**: Testing framework (BSD 3-Clause License) - Development only
- **[Google Benchmark](https://github.com/google/benchmark)**: Performance benchmarking framework (Apache 2.0 License) - Development only

All dependencies are automatically fetched via CMake FetchContent when building tests or benchmarks.

---

_Updated on October 26, 2025_
