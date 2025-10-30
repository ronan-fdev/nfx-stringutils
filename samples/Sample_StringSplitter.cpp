/**
 * @file Sample_StringSplitter.cpp
 * @brief Demonstrates zero-allocation string splitting with Splitter
 * @details This sample shows how to use Splitter for high-performance
 *          string processing in real-world scenarios like CSV parsing, configuration
 *          files, log analysis, and path manipulation
 */

#include <array>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include <nfx/string/Splitter.h>

int main()
{
	std::cout << "=== nfx StringSplitter Usage ===" << std::endl;
	std::cout << std::endl;

	//=========================================================================
	// Basic string splitting - CSV data processing
	//=========================================================================

	std::cout << "--- CSV Data Processing ---" << std::endl;

	const std::string_view csvLine{ "John,Doe,30,Engineer,NewYork,75000" };
	auto csvSplitter{ nfx::string::splitView( csvLine, ',' ) };

	std::cout << "Original CSV line: " << csvLine << std::endl;
	std::cout << "Parsed fields:" << std::endl;

	// Using range-based for loop (most convenient)
	size_t fieldIndex{};
	const std::array<const char*, 6> fieldNames{ "First Name", "Last Name", "Age", "Job", "City", "Salary" };

	for ( const auto field : csvSplitter )
	{
		const char* fieldName = ( fieldIndex < fieldNames.size() ) ? fieldNames.at( fieldIndex ) : "Unknown";
		std::cout << "  " << fieldName << ": " << field << std::endl;
		++fieldIndex;
	}

	std::cout << "Total fields: " << fieldIndex << std::endl;
	std::cout << std::endl;

	//=========================================================================
	// Configuration file processing
	//=========================================================================

	std::cout << "--- Configuration File Processing ---" << std::endl;

	const std::string_view configData{ "server=localhost;port=8080;database=mydb;timeout=30;ssl=true;debug=false" };
	auto configSplitter{ nfx::string::splitView( configData, ';' ) };

	std::cout << "Configuration string: " << configData << std::endl;
	std::cout << "Configuration settings:" << std::endl;

	for ( const auto setting : configSplitter )
	{
		// Further split each setting by '=' to get key-value pairs
		auto kvSplitter{ nfx::string::splitView( setting, '=' ) };
		auto it{ kvSplitter.begin() };

		if ( it != kvSplitter.end() )
		{
			std::string_view key{ *it };
			++it;

			if ( it != kvSplitter.end() )
			{
				std::string_view value{ *it };
				std::cout << "  " << std::setw( 10 ) << key << " = " << value << std::endl;
			}
		}
	}

	std::cout << std::endl;

	//=========================================================================
	// Log file analysis
	//=========================================================================

	std::cout << "--- Log File Analysis ---" << std::endl;

	const std::string_view logEntries[] = {
		"2025-08-31 09:15:32 INFO Application started successfully",
		"2025-08-31 09:15:33 DEBUG Loading configuration from config.xml",
		"2025-08-31 09:15:34 INFO Database connection established",
		"2025-08-31 09:15:35 WARN Cache size limit reached, cleaning up",
		"2025-08-31 09:15:36 ERROR Failed to process request: timeout" };

	std::cout << "Analyzing log entries:" << std::endl;

	for ( const auto& logEntry : logEntries )
	{
		auto logSplitter{ nfx::string::splitView( logEntry, ' ' ) };
		auto it{ logSplitter.begin() };

		// Extract log components
		std::string_view date{};
		std::string_view time{};
		std::string_view level{};

		if ( it != logSplitter.end() )
		{
			date = *it;
			++it;
		}
		if ( it != logSplitter.end() )
		{
			time = *it;
			++it;
		}
		if ( it != logSplitter.end() )
		{
			level = *it;
			++it;
		}

		// Collect remaining parts as message
		std::string message;
		while ( it != logSplitter.end() )
		{
			if ( !message.empty() )
			{
				message += " ";
			}
			message += *it;
			++it;
		}

		std::cout << "  [" << level << "] " << date << " " << time << " - " << message << std::endl;
	}

	std::cout << std::endl;

	//=========================================================================
	// Path manipulation
	//=========================================================================

	std::cout << "--- Path Manipulation ---" << std::endl;

	const std::string_view paths[]{
		"/usr/local/bin/myapp",
		"C:\\Program Files\\MyApp\\bin\\app.exe",
		"../config/settings.ini",
		"./data/output.csv" };

	for ( const auto& path : paths )
	{
		std::cout << "Original path: " << path << std::endl;

		// Determine delimiter based on path style
		char delimiter{ ( path.find( '\\' ) != std::string_view::npos ) ? '\\' : '/' };
		auto pathSplitter{ nfx::string::splitView( path, delimiter ) };

		std::cout << "  Components: ";
		bool first{ true };
		for ( const auto component : pathSplitter )
		{
			if ( !first )
			{
				std::cout << " -> ";
			}
			if ( component.empty() )
			{
				std::cout << "[root]";
			}
			else
			{
				std::cout << component;
			}
			first = false;
		}
		std::cout << std::endl;
	}

	std::cout << std::endl;

	//=========================================================================
	// Performance demonstration - Zero allocation
	//=========================================================================

	std::cout << "--- Performance Demonstration ---" << std::endl;

	// Large CSV-like data for performance testing
	std::string largeData;
	for ( int i{}; i < 1000; ++i )
	{
		if ( i > 0 )
		{
			largeData += ",";
		}
		largeData += "field" + std::to_string( i );
	}

	auto startTime{ std::chrono::high_resolution_clock::now() };

	// Process large data with zero allocations
	auto largeSplitter{ nfx::string::splitView( largeData, ',' ) };
	size_t count{};
	for ( const auto field : largeSplitter )
	{
		count++;
		(void)field;
	}

	auto endTime{ std::chrono::high_resolution_clock::now() };
	auto duration{ std::chrono::duration_cast<std::chrono::microseconds>( endTime - startTime ) };

	std::cout << "Processed " << count << " fields from large dataset" << std::endl;
	std::cout << "Time taken: " << duration.count() << " microseconds" << std::endl;
	std::cout << "Performance: " << ( static_cast<double>( count ) * 1000000.0 / static_cast<double>( duration.count() ) ) << " fields/second" << std::endl;
	std::cout << "Memory allocations: 0 (all stringViews point to original data)" << std::endl;

	std::cout << std::endl;

	//=========================================================================
	// Edge cases and delimiter variations
	//=========================================================================

	std::cout << "--- Edge Cases and Different Delimiters ---" << std::endl;

	// Test various edge cases
	const std::string_view edgeCases[]{
		"",		  // Empty string
		",",	  // Single delimiter
		"hello,", // Trailing delimiter
		",world", // Leading delimiter
		"a,,b",	  // Consecutive delimiters
		"single"  // No delimiters
	};

	for ( const auto& testCase : edgeCases )
	{
		std::cout << "Input: \"" << testCase << "\"" << std::endl;
		std::cout << "  Segments: ";

		auto edgeSplitter{ nfx::string::splitView( testCase, ',' ) };
		bool first{ true };
		for ( const auto segment : edgeSplitter )
		{
			if ( !first )
			{
				std::cout << " | ";
			}
			std::cout << "\"" << segment << "\"";
			first = false;
		}
		if ( first )
			std::cout << "(no segments)";
		std::cout << std::endl;
	}

	std::cout << std::endl;

	// Different delimiter examples
	const struct
	{
		std::string_view data;
		char delimiter;
		const char* description;
	} delimiterExamples[]{
		{ "apple banana cherry date", ' ', "Space-separated words" },
		{ "line1\nline2\nline3", '\n', "Newline-separated lines" },
		{ "col1\tcol2\tcol3", '\t', "Tab-separated columns" },
		{ "key1=val1;key2=val2;key3=val3", ';', "Semicolon-separated pairs" },
		{ "192.168.1.1", '.', "Dot-separated IP address" } };

	std::cout << "--- Different Delimiter Examples ---" << std::endl;

	for ( const auto& example : delimiterExamples )
	{
		std::cout << example.description << ":" << std::endl;
		std::cout << "  Input: \"" << example.data << "\"" << std::endl;
		std::cout << "  Parts: ";

		auto delimSplitter{ nfx::string::splitView( example.data, example.delimiter ) };
		bool first{ true };
		for ( const auto part : delimSplitter )
		{
			if ( !first )
			{
				std::cout << " | ";
			}
			std::cout << "\"" << part << "\"";
			first = false;
		}
		std::cout << std::endl;
	}

	std::cout << std::endl;

	//=========================================================================
	// Manual iterator usage
	//=========================================================================

	std::cout << "--- Manual Iterator Usage ---" << std::endl;

	const std::string_view manualData{ "first,second,third,fourth,fifth" };
	auto manualSplitter{ nfx::string::splitView( manualData, ',' ) };

	std::cout << "Manual iteration through: " << manualData << std::endl;

	auto it{ manualSplitter.begin() };
	auto end{ manualSplitter.end() };
	size_t index{};

	while ( it != end )
	{
		std::cout << "  [" << index++ << "] = \"" << *it << "\"" << std::endl;
		++it;
	}

	// Demonstrate iterator comparison
	auto it1{ manualSplitter.begin() };
	auto it2{ manualSplitter.begin() };
	std::cout << "Two begin iterators are equal: " << ( it1 == it2 ? "Yes" : "No" ) << std::endl;

	++it1;
	std::cout << "After advancing first iterator: " << ( it1 == it2 ? "Equal" : "Different" ) << std::endl;

	std::cout << std::endl;

	//=========================================================================
	// Memory safety demonstration
	//=========================================================================

	std::cout << "--- Memory Safety Demonstration ---" << std::endl;

	const std::string originalString{ "memory,safety,test,data" };
	const std::string_view stringView{ originalString };

	auto safetySplitter{ nfx::string::splitView( stringView, ',' ) };
	auto safety_it{ safetySplitter.begin() };

	std::string_view firstSegment{ *safety_it };

	std::cout << "Original string: \"" << originalString << "\"" << std::endl;
	std::cout << "First segment: \"" << firstSegment << "\"" << std::endl;
	std::cout << "Segment points to original memory: " << ( firstSegment.data() == originalString.data() ? "Yes" : "No" ) << std::endl;
	std::cout << "No additional memory allocated: Splitter uses zero-copy design" << std::endl;

	return 0;
}
