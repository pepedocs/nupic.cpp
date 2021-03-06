/* ---------------------------------------------------------------------
 * Numenta Platform for Intelligent Computing (NuPIC)
 * Copyright (C) 2013, Numenta, Inc.  Unless you have an agreement
 * with Numenta, Inc., for a separate license for this software code, the
 * following terms and conditions apply:
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero Public License version 3 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Affero Public License for more details.
 *
 * You should have received a copy of the GNU Affero Public License
 * along with this program.  If not, see http://www.gnu.org/licenses.
 *
 * http://numenta.org/licenses/
 * ---------------------------------------------------------------------
 */

/**
 * @file
 * Definition of C++ macros for logging.
 */

#ifndef NTA_LOG2_HPP
#define NTA_LOG2_HPP

#include <nupic/utils/LogItem.hpp>
#include <nupic/utils/LoggingException.hpp>

#define NTA_DEBUG                                                              \
  nupic::LogItem(__FILE__, __LINE__, nupic::LogItem::debug).stream()

// Can be used in Loggable classes
#define NTA_LDEBUG(level)                                                      \
  if (logLevel_ < (level)) {                                                   \
  } else                                                                       \
    nupic::LogItem(__FILE__, __LINE__, nupic::LogItem::debug).stream()

// For informational messages that report status but do not indicate that
// anything is wrong
#define NTA_INFO                                                               \
  nupic::LogItem(__FILE__, __LINE__, nupic::LogItem::info).stream()

// For messages that indicate a recoverable error or something else that it may
// be important for the end user to know about.
#define NTA_WARN                                                               \
  nupic::LogItem(__FILE__, __LINE__, nupic::LogItem::warn).stream()

// To throw an exception and make sure the exception message is logged
// appropriately
#define NTA_THROW throw nupic::LoggingException(__FILE__, __LINE__)

// The difference between CHECK and ASSERT is that ASSERT is for
// performance critical code and can be disabled in a release
// build. Both throw an exception on error (if NTA_ASSERTIONS_ON is set).

#define NTA_CHECK(condition)                                                   \
  if (condition) {                                                             \
  } else                                                                       \
    NTA_THROW << "CHECK FAILED: \"" << #condition << "\" "

#ifdef NTA_ASSERTIONS_ON
// With NTA_ASSERTIONS_ON, NTA_ASSERT macro throws exception if condition is false.
// NTA_ASSERTIONS_ON should be set ON only in debug mode.
#define NTA_ASSERT(condition)                                                  \
  if (condition) {                                                             \
  } else                                                                       \
    NTA_THROW << "ASSERTION FAILED: \"" << #condition << "\" "

#else
// Without NTA_ASSERTIONS_ON, NTA_ASSERT macro does nothing.
// The second line (with LogItem) should never be executed, or even compiled, but we
// need something that is syntactically compatible with NTA_ASSERT
#define NTA_ASSERT(condition)                                                  \
  if (1) {                                                                     \
  } else                                                                       \
    nupic::LogItem(__FILE__, __LINE__, nupic::LogItem::debug).stream()

#endif // NTA_ASSERTIONS_ON

#endif // NTA_LOG2_HPP
