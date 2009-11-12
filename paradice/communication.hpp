// ==========================================================================
// Paradice Communication
//
// Copyright (C) 2009 Matthew Chaplain, All Rights Reserved.
//
// Permission to reproduce, distribute, perform, display, and to prepare
// derivitive works from this file under the following conditions:
//
// 1. Any copy, reproduction or derivitive work of any part of this file 
//    contains this copyright notice and licence in its entirety.
//
// 2. The rights granted to you under this license automatically terminate
//    should you attempt to assert any patent claims against the licensor 
//    or contributors, which in any way restrict the ability of any party 
//    from using this software or portions thereof in any form under the
//    terms of this license.
//
// Disclaimer: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY
//             KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE 
//             WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR 
//             PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS 
//             OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR 
//             OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
//             OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE 
//             SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. 
// ==========================================================================
#ifndef PARADICE_COMMUNICATION_HPP_
#define PARADICE_COMMUNICATION_HPP_

#include <boost/shared_ptr.hpp>
#include <string>

namespace paradice {

class client;

// These messages all get backtraced.
void message_to_all(std::string const &text);

void message_to_player(
    std::string const         &text
  , boost::shared_ptr<client> &conn);

void message_to_room(
    std::string const               &text
  , boost::shared_ptr<client> const &conn);

// Sending doesn't backtrace
void send_to_all(std::string const &text);

void send_to_player(
    std::string const         &text
  , boost::shared_ptr<client> &conn);

void send_to_room(
    std::string const               &text
  , boost::shared_ptr<client> const &conn);

}

#endif
