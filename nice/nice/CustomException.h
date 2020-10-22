#pragma once
#include <exception>
#include <string>

class CustomException : public std::exception
{
public:
	CustomException(int line, const char* file) noexcept;
	int GetLine() const noexcept;
	const std::string& GetFile() const noexcept;
	const char* what() const noexcept override; // override function from std::exception - gives the actual error
	virtual const char* GetType() const noexcept;
private:
	int line;
	std::string file;
private:
	// yes yes fancy bullshit
	mutable std::string msg_buffer;

};

