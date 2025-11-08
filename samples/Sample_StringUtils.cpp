/**
 * @file Sample_StringUtils.cpp
 * @brief Comprehensive demonstration of NFX StringUtils library
 * @details This sample shows how to use StringUtils for high-performance string operations
 *          including validation, parsing, matching, comparison, and case conversion with
 *          zero-allocation design for maximum efficiency.
 */

#include <iostream>
#include <vector>
#include <chrono>

#include <nfx/string/Utils.h>

using namespace nfx::string;

int main()
{
	std::cout << "=== nfx StringUtils Library Usage ===" << std::endl;
	std::cout << std::endl;

	//=========================================================================
	// String Validation - Fast length and emptiness checks
	//=========================================================================

	std::cout << "--- String Validation ---" << std::endl;

	// Length validation examples
	std::string_view password{ "MySecurePassword123!" };
	std::cout << "Password validation:" << std::endl;
	std::cout << "  Password: \"" << password << "\"" << std::endl;
	std::cout << "  Has exactly 20 characters: " << ( hasExactLength( password, 20 ) ? "Yes" : "No" ) << std::endl;
	std::cout << "  Has exactly 8 characters: " << ( hasExactLength( password, 8 ) ? "Yes" : "No" ) << std::endl;

	// Empty string checks
	std::vector<std::string_view> inputs{ "", "   ", "content", "\t", "a" };
	std::cout << std::endl
			  << "Empty string detection:" << std::endl;

	for ( const auto& input : inputs )
	{
		std::cout << "  \"" << input << "\" is empty: " << ( isEmpty( input ) ? "Yes" : "No" ) << std::endl;
	}
	std::cout << std::endl;

	//=========================================================================
	// Boolean Parsing - Comprehensive format support
	//=========================================================================

	std::cout << "--- Boolean Parsing ---" << std::endl;

	// Test various boolean formats
	std::vector<std::string_view> boolInputs{
		"true", "TRUE", "True",
		"1", "t", "T", "yes",
		"YES", "on", "ON",
		"false", "FALSE", "False",
		"0", "f", "F", "no",
		"NO", "off", "OFF",
		"maybe", "2", "",
		"invalid" };

	std::cout << "Boolean parsing results:" << std::endl;
	for ( const auto& input : boolInputs )
	{
		bool result{};
		bool success{ tryParseBool( input, result ) };
		std::cout << "  \"" << input << "\" -> ";
		if ( success )
		{
			std::cout << ( result ? "true" : "false" );
		}
		else
		{
			std::cout << "invalid";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

	//=========================================================================
	// Numeric Parsing - Safe conversion with error handling
	//=========================================================================

	std::cout << "--- Numeric Parsing ---" << std::endl;

	// Integer parsing examples
	std::vector<std::string_view> intInputs{ "123", "-456", "0", "2147483647", "invalid", "12.34", "" };
	std::cout << "Integer parsing:" << std::endl;
	for ( const auto& input : intInputs )
	{
		int result{};
		bool success{ tryParseInt( input, result ) };
		std::cout << "  \"" << input << "\" -> ";
		if ( success )
		{
			std::cout << result;
		}
		else
		{
			std::cout << "invalid";
		}
		std::cout << std::endl;
	}

	// Double parsing examples
	std::vector<std::string_view> doubleInputs{ "123.456", "-78.9", "1.23e-4", "0.0", "invalid", "" };
	std::cout << std::endl
			  << "Double parsing:" << std::endl;
	for ( const auto& input : doubleInputs )
	{
		double result{};
		bool success{ tryParseDouble( input, result ) };
		std::cout << "  \"" << input << "\" -> ";
		if ( success )
		{
			std::cout << result;
		}
		else
		{
			std::cout << "invalid";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

	//=========================================================================
	// String Operations - Fast matching and comparison
	//=========================================================================

	std::cout << "--- String Operations ---" << std::endl;

	// File extension checking
	std::vector<std::string_view> filenames{ "document.pdf", "image.PNG", "script.js", "data.CSV", "readme" };
	std::cout << "File extension detection:" << std::endl;
	for ( const auto& filename : filenames )
	{
		std::cout << "  " << filename << ":" << std::endl;

		bool isPdf{ iequals( filename.substr( filename.find_last_of( '.' ) + 1 ), "pdf" ) };
		bool isImage{ endsWith( filename, ".png" ) || endsWith( filename, ".PNG" ) };
		bool hasExtension{ contains( filename, "." ) };

		std::cout << "    PDF: " << ( isPdf ? "Yes" : "No" ) << std::endl;
		std::cout << "    Image: " << ( isImage ? "Yes" : "No" ) << std::endl;
		std::cout << "    Has extension: " << ( hasExtension ? "Yes" : "No" ) << std::endl;
	}

	// URL validation example
	std::cout << std::endl
			  << "URL validation:" << std::endl;

	std::vector<std::string_view> urls{
		"https://api.example.com/v1/data",
		"http://localhost:8080/test",
		"ftp://files.server.com/download",
		"invalid-url",
		"https://secure.bank.com/api" };

	for ( const auto& url : urls )
	{
		std::cout << "  " << url << ":" << std::endl;

		bool isHttps{ startsWith( url, "https://" ) };
		bool isApiEndpoint{ contains( url, "/api" ) };
		bool isLocal{ contains( url, "localhost" ) };

		std::cout << "    HTTPS: " << ( isHttps ? "Yes" : "No" ) << std::endl;
		std::cout << "    API endpoint: " << ( isApiEndpoint ? "Yes" : "No" ) << std::endl;
		std::cout << "    Local: " << ( isLocal ? "Yes" : "No" ) << std::endl;
	}
	std::cout << std::endl;

	//=========================================================================
	// Case Conversion - ASCII-optimized transformations
	//=========================================================================

	std::cout << "--- Case Conversion ---" << std::endl;

	// Character conversion examples
	std::cout << "Character conversion:" << std::endl;
	std::string alphabet{ "AaBbCcDdEeFf123!@#" };
	std::cout << "  Original: " << alphabet << std::endl;

	std::string lowerResult{};
	std::string upperResult{};
	for ( char c : alphabet )
	{
		lowerResult += toLower( c );
		upperResult += toUpper( c );
	}
	std::cout << "  Lowercase: " << lowerResult << std::endl;
	std::cout << "  Uppercase: " << upperResult << std::endl;

	// String conversion examples
	std::cout << std::endl
			  << "String conversion:" << std::endl;
	std::vector<std::string_view> testStrings{
		"Hello World",
		"MixedCASE123!",
		"ALREADY_UPPER",
		"already_lower",
		"Café_Unicode_Ñoël", // Unicode should remain unchanged
		"" };

	for ( const auto& str : testStrings )
	{
		std::cout << "  Original:  \"" << str << "\"" << std::endl;
		std::cout << "  Lowercase: \"" << toLower( str ) << "\"" << std::endl;
		std::cout << "  Uppercase: \"" << toUpper( str ) << "\"" << std::endl;
		std::cout << std::endl;
	}

	//=========================================================================
	// Real-World use cases
	//=========================================================================

	std::cout << "--- Real-World Use Cases ---" << std::endl;

	// Configuration parsing
	std::cout << "Configuration file parsing:" << std::endl;
	std::vector<std::string_view> configLines{
		"debug=true",
		"port=8080",
		"ssl=false",
		"timeout=30.5",
		"retries=3" };

	for ( const auto& line : configLines )
	{
		auto pos{ line.find( '=' ) };
		if ( pos != std::string_view::npos )
		{
			auto key{ line.substr( 0, pos ) };
			auto value{ line.substr( pos + 1 ) };

			std::cout << "  " << key << " = " << value;

			// Try parsing as different types
			bool boolVal{};
			int intVal{};
			double doubleVal{};

			if ( tryParseBool( value, boolVal ) )
			{
				std::cout << " (boolean: " << ( boolVal ? "true" : "false" ) << ")";
			}
			else if ( tryParseInt( value, intVal ) )
			{
				std::cout << " (integer: " << intVal << ")";
			}
			else if ( tryParseDouble( value, doubleVal ) )
			{
				std::cout << " (double: " << doubleVal << ")";
			}
			else
			{
				std::cout << " (string)";
			}
			std::cout << std::endl;
		}
	}

	// Command validation
	std::cout << std::endl
			  << "Command validation:" << std::endl;
	std::vector<std::string_view> commands{ "start", "STOP", "restart", "Status", "invalid" };
	std::vector<std::string_view> validCommands{ "start", "stop", "restart", "status" };

	for ( const auto& cmd : commands )
	{
		std::cout << "  Command \"" << cmd << "\": ";
		bool valid{ false };
		for ( const auto& validCmd : validCommands )
		{
			if ( iequals( cmd, validCmd ) )
			{
				valid = true;
				break;
			}
		}
		std::cout << ( valid ? "Valid" : "Invalid" ) << std::endl;
	}
	std::cout << std::endl;

	//=========================================================================
	// String counting and pattern matching
	//=========================================================================

	std::cout << "--- String Counting and Pattern Matching ---" << std::endl;

	// Character counting
	std::string_view dnaSequence{ "ATCGATCGATCG" };
	std::cout << "DNA sequence analysis: " << dnaSequence << std::endl;
	std::cout << "  Adenine (A) count: " << count( dnaSequence, 'A' ) << std::endl;
	std::cout << "  Thymine (T) count: " << count( dnaSequence, 'T' ) << std::endl;
	std::cout << "  Cytosine (C) count: " << count( dnaSequence, 'C' ) << std::endl;
	std::cout << "  Guanine (G) count: " << count( dnaSequence, 'G' ) << std::endl;

	// Substring counting (non-overlapping)
	std::string_view logData{ "ERROR: Failed to connect. ERROR: Timeout. ERROR: Retry failed." };
	std::cout << std::endl
			  << "Log analysis: " << logData << std::endl;
	std::cout << "  ERROR occurrences: " << count( logData, "ERROR" ) << std::endl;
	std::cout << "  Failed occurrences: " << count( logData, "Failed" ) << std::endl;

	// Overlapping pattern detection
	std::string_view repeatPattern{ "aaaa" };
	std::cout << std::endl
			  << "Pattern: " << repeatPattern << std::endl;
	std::cout << "  Non-overlapping 'aa': " << count( repeatPattern, "aa" ) << std::endl;
	std::cout << "  Overlapping 'aa': " << countOverlapping( repeatPattern, "aa" ) << std::endl;

	std::string_view genome{ "AGAGAGAG" };
	std::cout << std::endl
			  << "Genome: " << genome << std::endl;
	std::cout << "  Non-overlapping 'AGA': " << count( genome, "AGA" ) << std::endl;
	std::cout << "  Overlapping 'AGA': " << countOverlapping( genome, "AGA" ) << std::endl;
	std::cout << std::endl;

	//=========================================================================
	// String replacement
	//=========================================================================

	std::cout << "--- String Replacement ---" << std::endl;

	// Replace first occurrence
	std::string_view template1{ "Hello {name}, welcome to {name}!" };
	std::string replaced1{ replace( template1, "{name}", "Alice" ) };
	std::cout << "Replace first:" << std::endl;
	std::cout << "  Original:  " << template1 << std::endl;
	std::cout << "  Result:    " << replaced1 << std::endl;

	// Replace all occurrences
	std::string replacedAll{ replaceAll( template1, "{name}", "Bob" ) };
	std::cout << std::endl
			  << "Replace all:" << std::endl;
	std::cout << "  Original:  " << template1 << std::endl;
	std::cout << "  Result:    " << replacedAll << std::endl;

	// Path normalization
	std::string_view windowsPath{ "C:\\Users\\Documents\\file.txt" };
	std::string unixPath{ replaceAll( windowsPath, "\\", "/" ) };
	std::cout << std::endl
			  << "Path normalization:" << std::endl;
	std::cout << "  Windows:   " << windowsPath << std::endl;
	std::cout << "  Unix:      " << unixPath << std::endl;

	// HTML escaping
	std::string_view htmlText{ "Use <script> tags carefully & escape \"quotes\"" };
	std::string escaped{ replaceAll( htmlText, "<", "&lt;" ) };
	escaped = replaceAll( escaped, ">", "&gt;" );
	escaped = replaceAll( escaped, "&", "&amp;" );
	std::cout << std::endl
			  << "HTML escaping:" << std::endl;
	std::cout << "  Original:  " << htmlText << std::endl;
	std::cout << "  Escaped:   " << escaped << std::endl;
	std::cout << std::endl;

	//=========================================================================
	// String joining
	//=========================================================================

	std::cout << "--- String Joining ---" << std::endl;

	// Join vector with delimiter
	std::vector<std::string> tags{ "cpp", "performance", "zero-copy", "string-utils" };
	std::string tagString{ join( tags, ", " ) };
	std::cout << "Tags: " << tagString << std::endl;

	// CSV generation
	std::vector<std::string> csvRow{ "John", "Doe", "30", "Engineer", "75000" };
	std::string csvLine{ join( csvRow, "," ) };
	std::cout << "CSV: " << csvLine << std::endl;

	// URL query parameters
	std::vector<std::string> params{ "page=1", "limit=10", "sort=name", "order=asc" };
	std::string queryString{ "?" + join( params, "&" ) };
	std::cout << "Query: " << queryString << std::endl;

	// Join with custom range
	std::vector<std::string> words{ "The", "quick", "brown", "fox", "jumps" };
	std::string sentence{ join( words.begin(), words.begin() + 3, " " ) };
	std::cout << "Partial join: " << sentence << std::endl;

	// Empty and single element
	std::vector<std::string> empty{};
	std::vector<std::string> single{ "alone" };
	std::cout << "Empty join: \"" << join( empty, "," ) << "\"" << std::endl;
	std::cout << "Single join: \"" << join( single, "," ) << "\"" << std::endl;
	std::cout << std::endl;

	//=========================================================================
	// String formatting and padding
	//=========================================================================

	std::cout << "--- String Formatting and Padding ---" << std::endl;

	// Table formatting
	std::cout << "Financial report (padded):" << std::endl;
	std::cout << "  " << padRight( "Item", 20 ) << padLeft( "Amount", 12 ) << std::endl;
	std::cout << "  " << repeat( "-", 32 ) << std::endl;
	std::cout << "  " << padRight( "Revenue", 20 ) << padLeft( "1,250,000", 12 ) << std::endl;
	std::cout << "  " << padRight( "Expenses", 20 ) << padLeft( "875,000", 12 ) << std::endl;
	std::cout << "  " << padRight( "Profit", 20 ) << padLeft( "375,000", 12 ) << std::endl;

	// Number formatting
	std::cout << std::endl
			  << "Number formatting:" << std::endl;
	std::cout << "  " << padLeft( "42", 5, '0' ) << " (zero-padded)" << std::endl;
	std::cout << "  " << padLeft( "123", 8, '0' ) << " (transaction ID)" << std::endl;
	std::cout << "  $" << padLeft( "99.99", 10, ' ' ) << " (price)" << std::endl;

	// Centered headers
	std::cout << std::endl
			  << "Centered headers:" << std::endl;
	std::cout << "  " << center( "MENU", 40, '=' ) << std::endl;
	std::cout << "  " << center( "Daily Specials", 40, ' ' ) << std::endl;
	std::cout << "  " << center( "***", 40, '-' ) << std::endl;

	// Progress bars and separators
	std::cout << std::endl
			  << "Visual elements:" << std::endl;
	std::cout << "  Progress: [" << repeat( "#", 7 ) << repeat( "-", 3 ) << "] 70%" << std::endl;
	std::cout << "  " << repeat( "=", 50 ) << std::endl;
	std::cout << "  Loading" << repeat( ".", 3 ) << std::endl;

	// Box drawing
	std::cout << std::endl
			  << "Text box:" << std::endl;
	std::string boxContent{ "Important Message" };
	int boxWidth{ 40 };
	std::cout << "  " << repeat( "*", boxWidth ) << std::endl;
	std::cout << "  *" << center( boxContent, boxWidth - 2 ) << "*" << std::endl;
	std::cout << "  " << repeat( "*", boxWidth ) << std::endl;
	std::cout << std::endl;

	//=========================================================================
	// String search and reversal
	//=========================================================================

	std::cout << "--- String Search and Reversal ---" << std::endl;

	// Palindrome detection
	std::vector<std::string_view> palindromeTests{ "radar", "hello", "level", "world", "noon" };
	std::cout << "Palindrome detection:" << std::endl;
	for ( const auto& word : palindromeTests )
	{
		bool isPalindrome{ word == reverse( word ) };
		std::cout << "  " << word << " -> " << ( isPalindrome ? "palindrome" : "not palindrome" ) << std::endl;
	}

	// String reversal use cases
	std::cout << std::endl
			  << "Reversal examples:" << std::endl;
	std::cout << "  \"hello\" reversed: " << reverse( "hello" ) << std::endl;
	std::cout << "  \"12345\" reversed: " << reverse( "12345" ) << std::endl;
	std::cout << "  DNA \"ATCG\" reversed: " << reverse( "ATCG" ) << std::endl;

	// Finding first occurrence
	std::string_view url{ "https://api.example.com/v1/users?id=123" };
	std::cout << std::endl
			  << "URL parsing: " << url << std::endl;
	auto protocolPos{ indexOf( url, "://" ) };
	auto pathPos{ indexOf( url, "/v1" ) };
	auto queryPos{ indexOf( url, "?" ) };
	std::cout << "  Protocol separator at: " << protocolPos << std::endl;
	std::cout << "  API path at: " << pathPos << std::endl;
	std::cout << "  Query string at: " << queryPos << std::endl;

	// Finding last occurrence
	std::string_view filePath{ "C:/Users/Documents/project/src/utils/helper.cpp" };
	std::cout << std::endl
			  << "File path: " << filePath << std::endl;
	auto lastSlash{ lastIndexOf( filePath, "/" ) };
	auto lastDot{ lastIndexOf( filePath, "." ) };
	if ( lastSlash != std::string_view::npos )
	{
		std::cout << "  Filename: " << filePath.substr( lastSlash + 1 ) << std::endl;
	}
	if ( lastDot != std::string_view::npos )
	{
		std::cout << "  Extension: " << filePath.substr( lastDot ) << std::endl;
	}

	// Email parsing
	std::string_view email{ "user.name@mail.example.com" };
	std::cout << std::endl
			  << "Email: " << email << std::endl;
	auto atPos{ indexOf( email, "@" ) };
	auto lastDotPos{ lastIndexOf( email, "." ) };
	if ( atPos != std::string_view::npos && lastDotPos != std::string_view::npos )
	{
		std::cout << "  Username: " << email.substr( 0, atPos ) << std::endl;
		std::cout << "  Domain: " << email.substr( atPos + 1 ) << std::endl;
		std::cout << "  TLD: " << email.substr( lastDotPos + 1 ) << std::endl;
	}

	// Search not found
	std::cout << std::endl
			  << "Search results:" << std::endl;
	std::cout << "  indexOf(\"hello\", \"xyz\"): "
			  << ( indexOf( "hello", "xyz" ) == std::string_view::npos ? "not found" : "found" ) << std::endl;
	std::cout << "  lastIndexOf(\"test\", \"missing\"): "
			  << ( lastIndexOf( "test", "missing" ) == std::string_view::npos ? "not found" : "found" ) << std::endl;
	std::cout << std::endl;

	//=========================================================================
	// Performance demonstration
	//=========================================================================

	std::cout << "--- Performance Demonstration ---" << std::endl;

	// Large string processing
	const std::string largeText( 10000, 'X' );
	const std::string searchPattern{ "XXXX" };

	auto start{ std::chrono::high_resolution_clock::now() };

	// Perform multiple operations
	bool hasLength{ hasExactLength( largeText, 10000 ) };
	bool containsPattern{ contains( largeText, searchPattern ) };
	bool startsWithX{ startsWith( largeText, "XXX" ) };
	bool endsWithX{ endsWith( largeText, "XXX" ) };
	std::string lowerCase{ toLower( largeText ) };

	auto end{ std::chrono::high_resolution_clock::now() };
	auto duration{ std::chrono::duration_cast<std::chrono::microseconds>( end - start ) };

	std::cout << "Large string operations (10,000 characters):" << std::endl;
	std::cout << "  Length check: " << ( hasLength ? "Passed" : "Failed" ) << std::endl;
	std::cout << "  Contains pattern: " << ( containsPattern ? "Yes" : "No" ) << std::endl;
	std::cout << "  Starts with XXX: " << ( startsWithX ? "Yes" : "No" ) << std::endl;
	std::cout << "  Ends with XXX: " << ( endsWithX ? "Yes" : "No" ) << std::endl;
	std::cout << "  Case conversion: " << ( lowerCase.size() == 10000 ? "Success" : "Failed" ) << std::endl;
	std::cout << "  Total time: " << duration.count() << " microseconds" << std::endl;
	std::cout << std::endl;

	return 0;
}
