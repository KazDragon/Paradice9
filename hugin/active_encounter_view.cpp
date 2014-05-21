// ==========================================================================
// Hugin Active Encounter view
//
// Copyright (C) 2013 Matthew Chaplain, All Rights Reserved.
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
#include "hugin/active_encounter_view.hpp"
#include <munin/algorithm.hpp>
#include <munin/grid_layout.hpp>
#include <munin/list.hpp>
#include <munin/scroll_pane.hpp>
#include <paradice/beast.hpp>
#include <paradice/character.hpp>
#include <boost/foreach.hpp>
#include <boost/format.hpp>
#include <boost/make_shared.hpp>
#include <boost/typeof/typeof.hpp>
#include <numeric>

using namespace paradice;
using namespace munin;
using namespace odin;
using namespace boost;
using namespace std;

namespace hugin {

// ==========================================================================
// ACTIVE_ENCOUNTER_VIEW::IMPLEMENTATION STRUCTURE
// ==========================================================================
struct active_encounter_view::impl
{
    shared_ptr<active_encounter> encounter_;
    bool                         gm_mode_;

    shared_ptr<munin::list>      participant_list_;

    struct active_encounter_entry_visitor : static_visitor<string>
    {
        string operator()(active_encounter::player ply)
        {
            shared_ptr<character> ch = ply.character_.lock();

            if (ch)
            {
                return ch->get_name();
            }
            else
            {
                return ply.name_;
            }
        }

        string operator()(shared_ptr<beast> beast)
        {
            return beast->get_name();
        }
    };
    
    void update()
    {
        if (!encounter_)
        {
            participant_list_->set_items(vector< vector<element_type> >());
            return;
        }

        BOOST_AUTO(selected_index, participant_list_->get_item_index());

        active_encounter_entry_visitor entry_visitor;
        vector< vector<element_type> > list_data;

        BOOST_FOREACH(active_encounter::entry const &entry, encounter_->entries_)
        {
            string name = apply_visitor(entry_visitor, entry.participant_);
            string text = str(format("(%d)") % entry.id_)
                 + " "
                 + name;

            if (!entry.annotation_.empty())
            {
                text += str(format(" [%s]") % entry.annotation_);
            }

            boost::optional<dice_result> const &last_roll =
                entry.roll_data_.empty()
              ? boost::optional<dice_result>()
              : entry.roll_data_.back();

            if (last_roll)
            {
                s32 total_score = 0;

                for (vector< vector<s32> >::const_iterator repetition = last_roll->results_.begin();
                     repetition != last_roll->results_.end();
                     ++repetition)
                {
                    total_score += std::accumulate(
                        repetition->begin(),
                        repetition->end(),
                        last_roll->roll_.bonus_);
                }

                text += str(
                    format(" | %s -> %d")
                        % describe_dice(last_roll->roll_) 
                        % total_score);
            }

            list_data.push_back(string_to_elements(text));
        }

        participant_list_->set_items(list_data);
        participant_list_->set_item_index(selected_index);
    }
};

// ==========================================================================
// CONSTRUCTOR
// ==========================================================================
active_encounter_view::active_encounter_view()
    : pimpl_(make_shared<impl>())
{
    pimpl_->gm_mode_ = false;
    pimpl_->participant_list_ = make_shared<munin::list>();

    BOOST_AUTO(content, get_container());
    content->set_layout(make_shared<grid_layout>(1, 1));
    content->add_component(
        make_shared<scroll_pane>(pimpl_->participant_list_));
}

// ==========================================================================
// DESTRUCTOR
// ==========================================================================
active_encounter_view::~active_encounter_view()
{
}

// ==========================================================================
// SET_GM_MODE
// ==========================================================================
void active_encounter_view::set_gm_mode(bool mode)
{
    pimpl_->gm_mode_ = mode;
    pimpl_->update();
}

// ==========================================================================
// SET_ENCOUNTER
// ==========================================================================
void active_encounter_view::set_encounter(
    shared_ptr<active_encounter> encounter)
{
    pimpl_->encounter_ = encounter;
    pimpl_->update();
}

}