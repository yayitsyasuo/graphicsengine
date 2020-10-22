#include "CustomException.h"
#include <sstream>

CustomException::CustomException(int line_, const char * file)
	:
	line(line_),
	file(file)
{
}

int CustomException::GetLine() const noexcept
{
	return line;
}

const std::string & CustomException::GetFile() const noexcept
{
	return file;
}

const char * CustomException::what() const noexcept
{
	std::ostringstream oss;
	oss << "Exception Type: " << GetType() << std::endl;
	oss << "FILE:      " << file << std::endl;
	oss << "LINE:      " << line << std::endl;
	msg_buffer = oss.str();	// there's apparently no direct conversion from OSS to char*
							// and oss.str().c_str();	will point to dead memory when this guy gets deleted after return
							// .c_str() pointers are freakin dangerous man
	return msg_buffer.c_str();
}

const char * CustomException::GetType() const noexcept
{
	return "CustomException inherited from std::exception";
}
