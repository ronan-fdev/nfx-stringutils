/*
 * MIT License
 *
 * Copyright (c) 2025 nfx
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/**
 * @file Utils.h
 * @brief High-performance string utilities for NFX C++ library
 * @details Provides fast, zero-allocation string operations including validation,
 *          parsing, and comparison functions using std::string_view for maximum performance.
 */

#pragma once

#include <cstdint>
#include <string>
#include <string_view>

namespace nfx::string
{
	//=====================================================================
	// String utilities
	//=====================================================================

	//----------------------------------------------
	// String validation
	//----------------------------------------------

	/**
	 * @brief Fast check if string has exact length
	 * @param str String to check
	 * @param expectedLength Expected length
	 * @return True if string has exact expected length
	 * @note This function is marked [[nodiscard]] - the return value should not be ignored
	 */
	[[nodiscard]] inline constexpr bool hasExactLength( std::string_view str, std::size_t expectedLength ) noexcept;

	/**
	 * @brief Fast check if string is empty
	 * @param str String to check
	 * @return True if string is empty
	 * @note This function is marked [[nodiscard]] - the return value should not be ignored
	 */
	[[nodiscard]] inline constexpr bool isEmpty( std::string_view str ) noexcept;

	/**
	 * @brief Fast check if string is null, empty, or contains only whitespace
	 * @param str String to check
	 * @return True if string is empty or contains only whitespace characters
	 * @details Considers space, tab, newline, carriage return, form feed, and vertical tab as whitespace
	 * @note This function is marked [[nodiscard]] - the return value should not be ignored
	 */
	[[nodiscard]] inline constexpr bool isNullOrWhiteSpace( std::string_view str ) noexcept;

	/**
	 * @brief Check if string contains only ASCII digits
	 * @param str String to check
	 * @return True if string is non-empty and contains only digits (0-9)
	 * @details Returns false for empty strings. Uses the existing isDigit() function for validation.
	 * @note This function is marked [[nodiscard]] - the return value should not be ignored
	 */
	[[nodiscard]] inline constexpr bool isAllDigits( std::string_view str ) noexcept;

	//----------------------------------------------
	// Character classification
	//----------------------------------------------

	/**
	 * @brief Check if character is whitespace
	 * @param c Character to check
	 * @return True if character is space, tab, newline, carriage return, form feed, or vertical tab
	 * @note This function is marked [[nodiscard]] - the return value should not be ignored
	 */
	[[nodiscard]] inline constexpr bool isWhitespace( char c ) noexcept;

	/**
	 * @brief Check if character is ASCII digit
	 * @param c Character to check
	 * @return True if character is 0-9
	 * @note This function is marked [[nodiscard]] - the return value should not be ignored
	 */
	[[nodiscard]] inline constexpr bool isDigit( char c ) noexcept;

	/**
	 * @brief Check if character is ASCII alphabetic
	 * @param c Character to check
	 * @return True if character is a-z or A-Z
	 * @note This function is marked [[nodiscard]] - the return value should not be ignored
	 */
	[[nodiscard]] inline constexpr bool isAlpha( char c ) noexcept;

	/**
	 * @brief Check if character is ASCII alphanumeric
	 * @param c Character to check
	 * @return True if character is a-z, A-Z, or 0-9
	 * @note This function is marked [[nodiscard]] - the return value should not be ignored
	 */
	[[nodiscard]] inline constexpr bool isAlphaNumeric( char c ) noexcept;

	//----------------------------------------------
	// String operations
	//----------------------------------------------

	/**
	 * @brief Fast check if string starts with prefix
	 * @param str String to check
	 * @param prefix Prefix to find
	 * @return True if str starts with prefix
	 * @note This function is marked [[nodiscard]] - the return value should not be ignored
	 */
	[[nodiscard]] inline constexpr bool startsWith( std::string_view str, std::string_view prefix ) noexcept;

	/**
	 * @brief Fast check if string ends with suffix
	 * @param str String to check
	 * @param suffix Suffix to find
	 * @return True if str ends with suffix
	 * @note This function is marked [[nodiscard]] - the return value should not be ignored
	 */
	[[nodiscard]] inline constexpr bool endsWith( std::string_view str, std::string_view suffix ) noexcept;

	/**
	 * @brief Fast check if string contains substring
	 * @param str String to check
	 * @param substr Substring to find
	 * @return True if str contains substr
	 * @note This function is marked [[nodiscard]] - the return value should not be ignored
	 */
	[[nodiscard]] inline constexpr bool contains( std::string_view str, std::string_view substr ) noexcept;

	/**
	 * @brief Fast case-sensitive string comparison
	 * @param lhs First string
	 * @param rhs Second string
	 * @return True if strings are exactly equal
	 * @note This function is marked [[nodiscard]] - the return value should not be ignored
	 */
	[[nodiscard]] inline constexpr bool equals( std::string_view lhs, std::string_view rhs ) noexcept;

	/**
	 * @brief Fast case-insensitive string comparison
	 * @param lhs First string
	 * @param rhs Second string
	 * @return True if strings are equal (case-insensitive)
	 * @note This function is marked [[nodiscard]] - the return value should not be ignored
	 */
	[[nodiscard]] inline bool iequals( std::string_view lhs, std::string_view rhs ) noexcept;

	/**
	 * @brief Count occurrences of substring in string
	 * @param str String to search in
	 * @param substr Substring to count
	 * @return Number of non-overlapping occurrences of substr in str
	 * @details Returns 0 if substr is empty or not found. Counts non-overlapping matches.
	 * @note This function is marked [[nodiscard]] - the return value should not be ignored
	 */
	[[nodiscard]] inline std::size_t count( std::string_view str, std::string_view substr ) noexcept;

	/**
	 * @brief Count overlapping occurrences of substring in string
	 * @param str String to search in
	 * @param substr Substring to count
	 * @return Number of overlapping occurrences of substr in str
	 * @details Returns 0 if substr is empty or not found. Counts all matches including overlapping ones.
	 *          Example: countOverlapping("aaaa", "aa") returns 3 (positions 0, 1, 2)
	 * @note This function is marked [[nodiscard]] - the return value should not be ignored
	 */
	[[nodiscard]] inline std::size_t countOverlapping( std::string_view str, std::string_view substr ) noexcept;

	/**
	 * @brief Count occurrences of character in string
	 * @param str String to search in
	 * @param ch Character to count
	 * @return Number of occurrences of ch in str
	 * @note This function is marked [[nodiscard]] - the return value should not be ignored
	 */
	[[nodiscard]] inline constexpr std::size_t count( std::string_view str, char ch ) noexcept;

	/**
	 * @brief Replace first occurrence of substring with replacement
	 * @param str String to search in
	 * @param oldStr Substring to replace
	 * @param newStr Replacement string
	 * @return New string with first occurrence replaced, or copy of original if oldStr not found
	 * @details Returns original string if oldStr is empty
	 * @note This function is marked [[nodiscard]] - the return value should not be ignored
	 */
	[[nodiscard]] inline std::string replace( std::string_view str, std::string_view oldStr, std::string_view newStr );

	/**
	 * @brief Replace all occurrences of substring with replacement
	 * @param str String to search in
	 * @param oldStr Substring to replace
	 * @param newStr Replacement string
	 * @return New string with all non-overlapping occurrences replaced
	 * @details Returns original string if oldStr is empty or not found
	 * @note This function is marked [[nodiscard]] - the return value should not be ignored
	 */
	[[nodiscard]] inline std::string replaceAll( std::string_view str, std::string_view oldStr, std::string_view newStr );

	/**
	 * @brief Join container elements with delimiter
	 * @tparam Container Container type (must support begin()/end() and value_type convertible to string_view)
	 * @param elements Container of elements to join
	 * @param delimiter Delimiter to insert between elements
	 * @return Joined string with delimiter between elements
	 * @details Returns empty string for empty container. Single element returns that element without delimiter.
	 * @note This function is marked [[nodiscard]] - the return value should not be ignored
	 */
	template <typename Container>
	[[nodiscard]] inline std::string join( const Container& elements, std::string_view delimiter );

	/**
	 * @brief Join iterator range with delimiter
	 * @tparam Iterator Forward iterator type (value_type must be convertible to string_view)
	 * @param begin Iterator to first element
	 * @param end Iterator past last element
	 * @param delimiter Delimiter to insert between elements
	 * @return Joined string with delimiter between elements
	 * @details Returns empty string for empty range. Single element returns that element without delimiter.
	 * @note This function is marked [[nodiscard]] - the return value should not be ignored
	 */
	template <typename Iterator>
	[[nodiscard]] inline std::string join( Iterator begin, Iterator end, std::string_view delimiter );

	//----------------------------------------------
	// String trimming
	//----------------------------------------------

	/**
	 * @brief Remove leading whitespace from string
	 * @param str String to trim
	 * @return String view with leading whitespace removed
	 * @details Returns a view into the original string, no allocation performed
	 * @note This function is marked [[nodiscard]] - the return value should not be ignored
	 */
	[[nodiscard]] inline constexpr std::string_view trimStart( std::string_view str ) noexcept;

	/**
	 * @brief Remove trailing whitespace from string
	 * @param str String to trim
	 * @return String view with trailing whitespace removed
	 * @details Returns a view into the original string, no allocation performed
	 * @note This function is marked [[nodiscard]] - the return value should not be ignored
	 */
	[[nodiscard]] inline constexpr std::string_view trimEnd( std::string_view str ) noexcept;

	/**
	 * @brief Remove leading and trailing whitespace from string
	 * @param str String to trim
	 * @return String view with leading and trailing whitespace removed
	 * @details Returns a view into the original string, no allocation performed
	 * @note This function is marked [[nodiscard]] - the return value should not be ignored
	 */
	[[nodiscard]] inline constexpr std::string_view trim( std::string_view str ) noexcept;

	//----------------------------------------------
	// String case conversion
	//----------------------------------------------

	/**
	 * @brief Convert string to lowercase
	 * @param str String to convert
	 * @return New string with all ASCII characters converted to lowercase
	 * @details Only ASCII characters (A-Z) are converted. Non-ASCII characters are preserved unchanged.
	 *          This function allocates a new std::string.
	 * @note This function is marked [[nodiscard]] - the return value should not be ignored
	 */
	[[nodiscard]] inline std::string toLower( std::string_view str );

	/**
	 * @brief Convert string to uppercase
	 * @param str String to convert
	 * @return New string with all ASCII characters converted to uppercase
	 * @details Only ASCII characters (a-z) are converted. Non-ASCII characters are preserved unchanged.
	 *          This function allocates a new std::string.
	 * @note This function is marked [[nodiscard]] - the return value should not be ignored
	 */
	[[nodiscard]] inline std::string toUpper( std::string_view str );

	//----------------------------------------------
	// Character case conversion
	//----------------------------------------------

	/**
	 * @brief Convert ASCII character to lowercase
	 * @param c Character to convert
	 * @return Lowercase character if ASCII letter, otherwise unchanged
	 * @details Only works with ASCII characters (A-Z, a-z). Non-ASCII characters are returned unchanged.
	 * @note This function is marked [[nodiscard]] - the return value should not be ignored
	 */
	[[nodiscard]] inline constexpr char toLower( char c ) noexcept;

	/**
	 * @brief Convert ASCII character to uppercase
	 * @param c Character to convert
	 * @return Uppercase character if ASCII letter, otherwise unchanged
	 * @details Only works with ASCII characters (A-Z, a-z). Non-ASCII characters are returned unchanged.
	 * @note This function is marked [[nodiscard]] - the return value should not be ignored
	 */
	[[nodiscard]] inline constexpr char toUpper( char c ) noexcept;

	//----------------------------------------------
	// String parsing
	//----------------------------------------------

	/**
	 * @brief Fast boolean parsing with error handling
	 * @param str String to parse (case-insensitive)
	 * @param result Output boolean value
	 * @return True if parsing succeeded, false otherwise
	 * @details Supports: "true"/"false", "1"/"0", "yes"/"no", "on"/"off", "t"/"f", "y"/"n"
	 * @note This function is marked [[nodiscard]] - the return value should not be ignored
	 */
	[[nodiscard]] inline bool tryParseBool( std::string_view str, bool& result ) noexcept;

	/**
	 * @brief Fast integer parsing with error handling
	 * @param str String to parse
	 * @param result Output integer value
	 * @return True if parsing succeeded, false otherwise
	 * @note This function is marked [[nodiscard]] - the return value should not be ignored
	 */
	[[nodiscard]] inline bool tryParseInt( std::string_view str, int& result ) noexcept;

	/**
	 * @brief Fast unsigned integer parsing with error handling
	 * @param str String to parse
	 * @param result Output unsigned integer value
	 * @return True if parsing succeeded, false otherwise
	 * @note This function is marked [[nodiscard]] - the return value should not be ignored
	 */
	[[nodiscard]] inline bool tryParseUInt( std::string_view str, std::uint32_t& result ) noexcept;

	/**
	 * @brief Fast long integer parsing with error handling
	 * @param str String to parse
	 * @param result Output long integer value
	 * @return True if parsing succeeded, false otherwise
	 * @note This function is marked [[nodiscard]] - the return value should not be ignored
	 */
	[[nodiscard]] inline bool tryParseLong( std::string_view str, std::int64_t& result ) noexcept;

	/**
	 * @brief Fast float parsing with error handling
	 * @param str String to parse
	 * @param result Output float value
	 * @return True if parsing succeeded, false otherwise
	 * @details Supports decimal, scientific notation, and special values (nan, inf, infinity).
	 *          Examples: "123.456", "1.23e-2", "nan", "inf", "-infinity"
	 * @note This function is marked [[nodiscard]] - the return value should not be ignored
	 */
	[[nodiscard]] inline bool tryParseFloat( std::string_view str, float& result ) noexcept;

	/**
	 * @brief Fast double parsing with error handling
	 * @param str String to parse
	 * @param result Output double value
	 * @return True if parsing succeeded, false otherwise
	 * @details Supports decimal, scientific notation, and special values (nan, inf, infinity).
	 *          Examples: "123.456", "1.23e-2", "nan", "inf", "-infinity"
	 * @note This function is marked [[nodiscard]] - the return value should not be ignored
	 */
	[[nodiscard]] inline bool tryParseDouble( std::string_view str, double& result ) noexcept;

	//----------------------------------------------
	// Network and URI validation
	//----------------------------------------------

	//-----------------------------
	// URI character classification
	//-----------------------------

	/**
	 * @brief Check if character is URI reserved (RFC 3986 Section 2.2)
	 * @param c Character to check
	 * @return True if character is a reserved URI character (:/?#[]@!$&'()*+,;=)
	 * @note This function is marked [[nodiscard]] - the return value should not be ignored
	 */
	[[nodiscard]] inline constexpr bool isURIReserved( char c ) noexcept;

	/**
	 * @brief Check if string contains only URI reserved characters
	 * @param str String to check
	 * @return True if string is non-empty and contains only reserved characters
	 * @details Returns false for empty strings. Uses RFC 3986 Section 2.2 definition.
	 * @note This function is marked [[nodiscard]] - the return value should not be ignored
	 */
	[[nodiscard]] inline constexpr bool isURIReserved( std::string_view str ) noexcept;

	/**
	 * @brief Check if character is URI unreserved (RFC 3986 Section 2.3)
	 * @param c Character to check
	 * @return True if character is A-Z, a-z, 0-9, -, ., _, or ~
	 * @note This function is marked [[nodiscard]] - the return value should not be ignored
	 */
	[[nodiscard]] inline constexpr bool isURIUnreserved( char c ) noexcept;

	/**
	 * @brief Check if string contains only URI unreserved characters
	 * @param str String to check
	 * @return True if string is non-empty and contains only unreserved characters
	 * @details Returns false for empty strings. Uses RFC 3986 Section 2.3 definition.
	 * @note This function is marked [[nodiscard]] - the return value should not be ignored
	 */
	[[nodiscard]] inline constexpr bool isURIUnreserved( std::string_view str ) noexcept;

	//-----------------------------
	// IP address validation
	//-----------------------------

	/**
	 * @brief Validate IPv4 address format (RFC 791)
	 * @param str String to validate
	 * @return True if string is a valid IPv4 address (e.g., "192.168.1.1")
	 * @details Validates dotted-decimal notation with four octets (0-255 each).
	 *          Does not allocate memory. Examples: "127.0.0.1", "192.168.0.1"
	 * @note This function is marked [[nodiscard]] - the return value should not be ignored
	 */
	[[nodiscard]] inline constexpr bool isIPv4Address( std::string_view str ) noexcept;

	/**
	 * @brief Validate IPv6 address format (RFC 4291, RFC 5952)
	 * @param str String to validate
	 * @return True if string is a valid IPv6 address
	 * @details Validates standard and compressed notation. Supports :: compression.
	 *          Examples: "2001:db8::1", "::1", "fe80::1%eth0"
	 * @note This function is marked [[nodiscard]] - the return value should not be ignored
	 */
	[[nodiscard]] inline constexpr bool isIPv6Address( std::string_view str ) noexcept;

	//-----------------------------
	// Host validation
	//-----------------------------

	/**
	 * @brief Validate hostname format (RFC 1123)
	 * @param str String to validate
	 * @return True if string is a valid hostname
	 * @details Validates DNS hostname format: labels separated by dots, alphanumeric with hyphens.
	 *          Max length 253 characters, labels max 63 characters. Case-insensitive.
	 *          Examples: "localhost", "example.com", "my-server-01.local"
	 * @note This function is marked [[nodiscard]] - the return value should not be ignored
	 */
	[[nodiscard]] inline constexpr bool isValidHostname( std::string_view str ) noexcept;

	/**
	 * @brief Validate domain name format (RFC 1035)
	 * @param str String to validate
	 * @return True if string is a valid domain name
	 * @details Validates fully qualified domain names (FQDN). Stricter than hostname validation.
	 *          Must contain at least one dot. Examples: "example.com", "mail.google.com"
	 * @note This function is marked [[nodiscard]] - the return value should not be ignored
	 */
	[[nodiscard]] inline constexpr bool isDomainName( std::string_view str ) noexcept;

	//-----------------------------
	// Port validation
	//-----------------------------

	/**
	 * @brief Validate port number string (RFC 6335)
	 * @param str String to validate
	 * @return True if string represents a valid port number (0-65535)
	 * @details Validates string contains only digits and value is in valid port range.
	 *          Examples: "80", "8080", "443", "65535"
	 * @note This function is marked [[nodiscard]] - the return value should not be ignored
	 */
	[[nodiscard]] inline constexpr bool isValidPort( std::string_view str ) noexcept;

	/**
	 * @brief Validate port number value (RFC 6335)
	 * @tparam T Integral type (int, uint16_t, uint32_t, uint64_t, etc.)
	 * @param port Port number to validate
	 * @return True if port is in valid range (0-65535)
	 * @details Accepts any integral type and validates the value is within the valid port range.
	 *          Prevents implicit narrowing conversions that could silently accept invalid values.
	 *          Examples: isValidPort(80) = true, isValidPort(70000) = false, isValidPort(-1) = false
	 * @note This function is marked [[nodiscard]] - the return value should not be ignored
	 */
	template <typename T, typename = std::enable_if_t<std::is_integral_v<T>>>
	[[nodiscard]] inline constexpr bool isValidPort( T port ) noexcept;

	//-----------------------------
	// Endpoint parsing
	//-----------------------------

	/**
	 * @brief Parse network endpoint into host and port
	 * @param endpoint Endpoint string to parse
	 * @param host Output parameter for host portion
	 * @param port Output parameter for port number
	 * @return True if parsing succeeded, false otherwise
	 * @details Supports formats: "host:port", "ipv4:port", "[ipv6]:port"
	 *          IPv6 addresses must be enclosed in brackets.
	 *          Examples: "localhost:8080", "192.168.1.1:80", "[::1]:443"
	 * @note This function is marked [[nodiscard]] - the return value should not be ignored
	 */
	[[nodiscard]] inline bool tryParseEndpoint( std::string_view endpoint,
		std::string_view& host,
		uint16_t& port ) noexcept;
} // namespace nfx::string

#include "nfx/detail/string/Utils.inl"
