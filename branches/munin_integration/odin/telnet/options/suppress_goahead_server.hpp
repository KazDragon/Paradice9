// ==========================================================================
// Odin Telnet Suppress Go-Ahead Server Option
//
// Copyright (C) 2003 Matthew Chaplain, All Rights Reserved.
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
#ifndef ODIN_TELNET_OPTIONS_SUPPRESS_GOAHEAD_SERVER_HPP_
#define ODIN_TELNET_OPTIONS_SUPPRESS_GOAHEAD_SERVER_HPP_

#include "odin/telnet/options/subnegotiationless_server.hpp"

namespace odin { namespace telnet { namespace options {

//* =========================================================================
/// \class odin::telnet::options::suppress_goahead_server
/// \brief A class that implements the Telnet Server side of the Suppress
/// Goahead option (RFC 858/STD2 9)
//* =========================================================================
typedef subnegotiationless_server<odin::telnet::SUPPRESS_GOAHEAD>
    suppress_goahead_server;
            
}}}

#endif