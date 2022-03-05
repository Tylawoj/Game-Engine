/** @file Exception.cpp
 *  @brief Implementation of functions for the Exception class.
 */

#include "Exception.h"
#include <iostream>

namespace vita
{
    Exception::Exception(const std::string& _message)
    {
      this->m_message = _message;
    }

    const char* Exception::What() const throw()
    {
      return m_message.c_str();
    }
}
