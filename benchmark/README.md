# Benchmarks

---

## Test Environment

### Hardware Configuration

| Component                | Specification                                                 |
| ------------------------ | ------------------------------------------------------------- |
| **CPU**                  | 12th Gen Intel Core i7-12800H (20 logical, 14 physical cores) |
| **Base Clock**           | 2.80 GHz                                                      |
| **Turbo Clock**          | 4.80 GHz                                                      |
| **L1 Data Cache**        | 48 KiB (×6 P-cores) + 32 KiB (×8 E-cores)                     |
| **L1 Instruction Cache** | 32 KiB (×6 P-cores) + 64 KiB (×2 E-core clusters)             |
| **L2 Unified Cache**     | 1.25 MiB (×6 P-cores) + 2 MiB (×2 E-core clusters)            |
| **L3 Unified Cache**     | 24 MiB (×1 shared)                                            |
| **RAM**                  | DDR4-3200 (32GB)                                              |
| **GPU**                  | NVIDIA RTX A2000 4GB GDDR6                                    |

### Software Configuration

| Platform    | Benchmark Framework     | C++ Compiler              | nfx-stringutils Version |
| ----------- | ----------------------- | ------------------------- | ----------------------- |
| **Linux**   | Google Benchmark v1.9.4 | GCC 14.2.0-x64            | v1.0.0                  |
| **Linux**   | Google Benchmark v1.9.4 | Clang 19.1.7-x64          | v1.0.0                  |
| **Windows** | Google Benchmark v1.9.4 | MinGW GCC 14.2.0-x64      | v1.0.0                  |
| **Windows** | Google Benchmark v1.9.4 | Clang-GNU-CLI 19.1.5-x64  | v1.0.0                  |
| **Windows** | Google Benchmark v1.9.4 | Clang-MSVC-CLI 19.1.5-x64 | v1.0.0                  |
| **Windows** | Google Benchmark v1.9.4 | MSVC 19.44.35217.0-x64    | v1.0.0                  |

---

# Performance Results

## String Utilities Operations

| Operation                           | Linux GCC   | Linux Clang | Windows MinGW GCC | Windows Clang-GNU-CLI | Windows Clang-MSVC-CLI | Windows MSVC |
| ----------------------------------- | ----------- | ----------- | ----------------- | --------------------- | ---------------------- | ------------ |
| **std::isspace**                    | 23.8 ns     | **22.7 ns** | 38.8 ns           | 30.8 ns               | 31.4 ns                | 39.6 ns      |
| **nfx::string::isWhitespace**       | 7.92 ns     | **6.87 ns** | 11.5 ns           | 9.39 ns               | 10.1 ns                | 20.1 ns      |
| **std::isdigit**                    | **4.98 ns** | 6.30 ns     | 7.00 ns           | 7.60 ns               | 7.55 ns                | 34.0 ns      |
| **nfx::string::isDigit**            | **5.09 ns** | 5.11 ns     | 7.21 ns           | 8.25 ns               | 7.80 ns                | 15.6 ns      |
| **std::isalpha**                    | **24.9 ns** | 26.1 ns     | 39.5 ns           | 38.2 ns               | 38.6 ns                | 37.7 ns      |
| **nfx::string::isAlpha**            | **5.17 ns** | 6.80 ns     | 6.80 ns           | 7.05 ns               | 7.88 ns                | 27.2 ns      |
| **std::string_view::empty**         | **5.24 ns** | 6.60 ns     | 6.60 ns           | 9.17 ns               | 9.23 ns                | 17.4 ns      |
| **nfx::string::isEmpty**            | **4.66 ns** | 6.57 ns     | 6.57 ns           | 8.84 ns               | 9.04 ns                | 18.0 ns      |
| **Manual isNullOrWhiteSpace**       | 53.1 ns     | **49.3 ns** | 71.2 ns           | 49.3 ns               | 50.2 ns                | 68.0 ns      |
| **nfx::string::isNullOrWhiteSpace** | **14.5 ns** | 17.4 ns     | 21.1 ns           | 29.1 ns               | 25.0 ns                | 38.8 ns      |
| **Manual isAllDigits**              | 22.8 ns     | **22.1 ns** | 29.6 ns           | 33.3 ns               | 34.2 ns                | 85.5 ns      |
| **nfx::string::isAllDigits**        | **24.7 ns** | 25.5 ns     | 32.5 ns           | 32.3 ns               | 34.3 ns                | 41.4 ns      |
| **std::starts_with**                | 11.7 ns     | **10.4 ns** | 24.9 ns           | 14.9 ns               | 14.3 ns                | 30.2 ns      |
| **nfx::string::startsWith**         | **11.7 ns** | 13.4 ns     | 18.3 ns           | 17.7 ns               | 15.2 ns                | 31.6 ns      |
| **std::ends_with**                  | 10.4 ns     | **10.3 ns** | 14.4 ns           | 16.8 ns               | 15.2 ns                | 37.2 ns      |
| **nfx::string::endsWith**           | 10.4 ns     | **10.3 ns** | 18.1 ns           | 14.8 ns               | 14.8 ns                | 32.4 ns      |
| **std::contains**                   | 57.0 ns     | **51.9 ns** | 109 ns            | 172 ns                | 169 ns                 | 176 ns       |
| **nfx::string::contains**           | **56.8 ns** | 57.0 ns     | 107 ns            | 187 ns                | 173 ns                 | 176 ns       |
| **Manual trim**                     | **36.0 ns** | 38.2 ns     | 50.9 ns           | 135 ns                | 135 ns                 | 297 ns       |
| **nfx::string::trim**               | **30.3 ns** | 37.6 ns     | 37.6 ns           | 56.3 ns               | 42.9 ns                | 51.7 ns      |
| **std::tolower (char)**             | 30.6 ns     | **27.3 ns** | 27.3 ns           | 31.3 ns               | 30.6 ns                | 42.7 ns      |
| **nfx::string::toLower (char)**     | **3.55 ns** | 4.80 ns     | 4.80 ns           | 8.07 ns               | 8.54 ns                | 17.0 ns      |
| **std::transform tolower**          | **490 ns**  | 522 ns      | 690 ns            | 705 ns                | 670 ns                 | 661 ns       |
| **nfx::string::toLower (string)**   | 472 ns      | **432 ns**  | 601 ns            | 660 ns                | 621 ns                 | 932 ns       |
| **std::toupper (char)**             | 30.3 ns     | **27.3 ns** | 27.3 ns           | 42.2 ns               | 41.4 ns                | 44.0 ns      |
| **nfx::string::toUpper (char)**     | **3.57 ns** | 4.73 ns     | 4.73 ns           | 7.31 ns               | 7.12 ns                | 16.5 ns      |
| **std::transform toupper**          | **529 ns**  | 538 ns      | 667 ns            | 863 ns                | 798 ns                 | 692 ns       |
| **nfx::string::toUpper (string)**   | 488 ns      | **435 ns**  | 644 ns            | 668 ns                | 643 ns                 | 910 ns       |
| **std::from_chars (int)**           | **13.5 ns** | 15.2 ns     | 24.7 ns           | 22.5 ns               | 20.6 ns                | 32.5 ns      |
| **nfx::string::tryParseInt**        | **13.2 ns** | 17.9 ns     | 22.3 ns           | 20.2 ns               | 20.2 ns                | 45.7 ns      |
| **std::from_chars (double)**        | **46.7 ns** | 47.0 ns     | 76.1 ns           | 138 ns                | 143 ns                 | 188 ns       |
| **nfx::string::tryParseDouble**     | **47.8 ns** | 49.2 ns     | 80.1 ns           | 142 ns                | 146 ns                 | 193 ns       |
| **Manual isURIReserved**            | 8.67 ns     | **8.07 ns** | 14.6 ns           | 10.2 ns               | 9.51 ns                | 25.6 ns      |
| **nfx::string::isURIReserved**      | 8.85 ns     | **7.78 ns** | 11.2 ns           | 9.69 ns               | 9.34 ns                | 26.5 ns      |
| **Manual isURIUnreserved**          | **10.6 ns** | 12.1 ns     | 14.4 ns           | 15.1 ns               | 14.5 ns                | 28.5 ns      |
| **nfx::string::isURIUnreserved**    | **10.7 ns** | 12.1 ns     | 13.8 ns           | 14.4 ns               | 14.3 ns                | 28.3 ns      |

---

_Benchmarks executed on October 26, 2025_
