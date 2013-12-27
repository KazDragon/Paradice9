// ==========================================================================
// Paradice Encounters
//
// Copyright (C) 2013 Matthew Chaplain, All Rights Reserved.  
// This file is covered by the MIT Licence:
//
// Permission is hereby granted, free of charge, to any person obtaining a 
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation 
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the 
// Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER 
// DEALINGS IN THE SOFTWARE.
// ==========================================================================
#include "paradice/gm.hpp"
#include "paradice/active_encounter.hpp"
#include "paradice/client.hpp"
#include "paradice/communication.hpp"
#include "paradice/context.hpp"
#include "hugin/user_interface.hpp"
#include "odin/tokenise.hpp"
#include <boost/lambda/bind.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/foreach.hpp>
#include <boost/format.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/typeof/typeof.hpp>

using namespace odin;
using namespace boost;
using namespace std;

namespace paradice {

namespace {

PARADICE_COMMAND_IMPL(gm_tools)
{
    BOOST_AUTO(user_interface, player->get_user_interface());
    user_interface->select_face(hugin::FACE_GM_TOOLS);
    user_interface->set_focus();
}

PARADICE_COMMAND_IMPL(gm_encounter_show)
{
    ctx->set_active_encounter_visible(true);
}

PARADICE_COMMAND_IMPL(gm_encounter_hide)
{
    ctx->set_active_encounter_visible(false);
}

static void add_encounter_player(
    shared_ptr<character> ch
  , shared_ptr<context> ctx)
{
    // Don't add the GM.
    if (ch->get_gm_level() != 0)
    {
        return;
    }

    bool found = false;

    BOOST_AUTO(enc, ctx->get_active_encounter());
    BOOST_FOREACH(active_encounter::entry &entry, enc->entries_)
    {
        BOOST_AUTO(
            participant_player
          , get<active_encounter::player>(&entry.participant_));

        // If this entry is not a character, then move to the next entry.
        if (!participant_player)
        {
            continue;
        }

        BOOST_AUTO(
            participant_character
          , participant_player->character_.lock());

        // If this entry is the same as the character, then it has already 
        // been added, so we can skip to the next player.
        if (participant_character == ch)
        {
            found = true;
            break;
        }
    }

    // Only add characters that are not already in the encounter.
    if (!found)
    {
        add_character(enc, ch);
    }
}

static void remove_encounter_participant(
    u32 id
  , shared_ptr<context> ctx)
{
    namespace bll = boost::lambda;

    BOOST_AUTO(enc, ctx->get_active_encounter());

    enc->entries_.erase(
        remove_if(
            enc->entries_.begin()
          , enc->entries_.end()
          , bll::bind(&active_encounter::entry::id_, bll::_1) == id)
      , enc->entries_.end());

    ctx->update_active_encounter();
}

PARADICE_COMMAND_IMPL(gm_encounter_add_player)
{
    BOOST_AUTO(arg0, tokenise(arguments));
    string argument = arg0.first;

    BOOST_FOREACH(shared_ptr<client> cli, ctx->get_clients())
    {
        BOOST_AUTO(ch, cli->get_character());

        if (ch->get_name() == argument)
        {
            add_encounter_player(ch, ctx);
            break;
        }
    }

    ctx->update_active_encounter();
}

PARADICE_COMMAND_IMPL(gm_encounter_add_players)
{
    BOOST_FOREACH(shared_ptr<client> cli, ctx->get_clients())
    {
        add_encounter_player(cli->get_character(), ctx);
    }

    ctx->update_active_encounter();
}

PARADICE_COMMAND_IMPL(gm_encounter_add)
{
    BOOST_AUTO(arg0, tokenise(arguments));
    string argument = arg0.first;

#define DISPATCH_GM_ENCOUNTER_ADD_COMMAND(cmd) \
    if (argument == #cmd) \
    { \
        INVOKE_PARADICE_COMMAND(gm_encounter_add_##cmd, ctx, arg0.second, player); \
        return; \
    }

    DISPATCH_GM_ENCOUNTER_ADD_COMMAND(player);
    DISPATCH_GM_ENCOUNTER_ADD_COMMAND(players);
#undef DISPATCH_GM_ENCOUNTER_ADD_COMMAND

    send_to_player(
        ctx
      , "Unknown: gm encounter add " + argument
      , player);

}

PARADICE_COMMAND_IMPL(gm_encounter_remove)
{
    BOOST_AUTO(arg0, tokenise(arguments));
    string argument = arg0.first;

    if (argument == "all")
    {
        BOOST_AUTO(enc, ctx->get_active_encounter());
        enc->entries_.clear();
        ctx->update_active_encounter();
    }
    else
    {
        u32 id = 0;
 
        try
        {
            id = lexical_cast<u32>(argument);
        }
        catch(bad_lexical_cast const &)
        {
            send_to_player(
                ctx
              , "USAGE: gm encounter remove (all|<id>)\n"
              , player);
            return;
        }

        remove_encounter_participant(id, ctx);
        ctx->update_active_encounter();
        return;
    }

    send_to_player(
        ctx
      , "USAGE: gm encounter remove (all|<id>)\n"
      , player);
}

PARADICE_COMMAND_IMPL(gm_encounter_move)
{
    BOOST_AUTO(arg0, tokenise(arguments));
    string id_arg = arg0.first;

    u32 id = 0;

    try
    {
        id = lexical_cast<u32>(id_arg);
    }
    catch(bad_lexical_cast const &)
    {
        send_to_player(
            ctx
          , "USAGE: gm encounter move <id> (up|down|top|bottom)\n"
          , player);
        return;
    }

    BOOST_AUTO(enc, ctx->get_active_encounter());
    BOOST_AUTO(entry_it, enc->entries_.begin());

    for (; entry_it != enc->entries_.end(); ++entry_it)
    {
        if (entry_it->id_ == id)
        {
            break;
        }
    }

    if (entry_it == enc->entries_.end())
    {
        send_to_player(
            ctx
          , str(format(
                "Error: No entry in the active encounter with id %d\n")
                % id)
          , player);
        return;
    }

    BOOST_AUTO(arg1, tokenise(arg0.second));
    string dir_arg = arg1.first;

    if (dir_arg == "up")
    {
        if (entry_it != enc->entries_.begin())
        {
            iter_swap(entry_it, entry_it - 1);
            ctx->update_active_encounter();
        }
    }
    else if (dir_arg == "down")
    {
        if (entry_it + 1 != enc->entries_.end())
        {
            iter_swap(entry_it, entry_it + 1);
            ctx->update_active_encounter();
        }
    }
    else if (dir_arg == "top")
    {
        active_encounter::entry cloned_entry = *entry_it;
        enc->entries_.erase(entry_it);
        enc->entries_.insert(enc->entries_.begin(), cloned_entry);
        ctx->update_active_encounter();
    }
    else if (dir_arg == "bottom")
    {
        active_encounter::entry cloned_entry = *entry_it;
        enc->entries_.erase(entry_it);
        enc->entries_.insert(enc->entries_.end(), cloned_entry);
        ctx->update_active_encounter();
    }
    else
    {
        send_to_player(
            ctx
          , "USAGE: gm encounter move <id> (up|down|top|bottom)\n"
          , player);
    }
}

PARADICE_COMMAND_IMPL(gm_encounter)
{
    BOOST_AUTO(arg0, tokenise(arguments));
    string argument = arg0.first;

#define DISPATCH_GM_ENCOUNTER_COMMAND(cmd) \
    if (argument == #cmd) \
    { \
        INVOKE_PARADICE_COMMAND(gm_encounter_##cmd, ctx, arg0.second, player); \
        return; \
    }

    DISPATCH_GM_ENCOUNTER_COMMAND(add);
    DISPATCH_GM_ENCOUNTER_COMMAND(hide);
    DISPATCH_GM_ENCOUNTER_COMMAND(move);
    DISPATCH_GM_ENCOUNTER_COMMAND(remove);
    DISPATCH_GM_ENCOUNTER_COMMAND(show);

#undef DISPATCH_GM_ENCOUNTER_COMMAND

    send_to_player(
        ctx
      , "Unknown: gm encounter " + argument
      , player);
}

}

// ==========================================================================
// PARADICE COMMAND: GM
// ==========================================================================
PARADICE_COMMAND_IMPL(gm)
{
    BOOST_AUTO(arg0, tokenise(arguments));
    string argument = arg0.first;

#define DISPATCH_GM_COMMAND(cmd) \
    if (argument == #cmd) \
    { \
        INVOKE_PARADICE_COMMAND(gm_##cmd, ctx, arg0.second, player); \
        return; \
    }
    
    DISPATCH_GM_COMMAND(tools);
    DISPATCH_GM_COMMAND(encounter);
#undef DISPATCH_GM_COMMAND

    send_to_player(
        ctx
      , "USAGE:   gm <command> [<arguments>...]\n"
        "EXAMPLE: gm tools\n"
        "EXAMPLE: gm encounter show\n"
        "EXAMPLE: gm encounter hide\n"
        "EXAMPLE: gm encounter add player <player>\n"
        "EXAMPLE: gm encounter add players\n"
        "EXAMPLE: gm encounter remove (all|<id>)\n"
        "EXAMPLE: gm encounter move <id> (up|down|top|bottom)\n"
        "\n"
      , player);
}

}
