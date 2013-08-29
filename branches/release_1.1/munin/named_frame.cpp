// ==========================================================================
// Munin Named Frame.
//
// Copyright (C) 2010 Matthew Chaplain, All Rights Reserved.
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
#include "munin/named_frame.hpp"
#include "munin/ansi/protocol.hpp"
#include "munin/algorithm.hpp"
#include "munin/canvas.hpp"
#include "munin/filled_box.hpp"
#include "munin/frame.hpp"
#include "munin/grid_layout.hpp"
#include "odin/ansi/protocol.hpp"
#include <boost/assign/list_of.hpp>
#include <boost/make_shared.hpp>
#include <boost/typeof/typeof.hpp>

using namespace munin::ansi;
using namespace odin;
using namespace boost;
using namespace boost::assign;
using namespace std;

namespace munin {

// ==========================================================================
// TITLE_BAR
// ==========================================================================
class title_bar : public basic_component
{
public :
    // ======================================================================
    // CONSTRUCTOR
    // ======================================================================
    title_bar(
        vector<element_type>  title
      , element_type const   &filler_element)
        : title_(title)
        , filler_element_(filler_element)
    {
        set_can_focus(false);
    }

    // ======================================================================
    // SET_TITLE
    // ======================================================================
    void set_title(vector<element_type> title)
    {
        title_ = title;
        on_redraw(list_of(rectangle(point(), get_size())));
    }

    // ======================================================================
    // DO_GET_PREFERRED_SIZE
    // ======================================================================
    extent do_get_preferred_size() const
    {
        // The preferred width is the title's width, plus two blank either
        // side, plus at least one filler either side for an additional 2;
        // and a height of 1.
        return extent(title_.size() + 4, 1);
    }

    // ======================================================================
    // DO_DRAW
    // ======================================================================
    void do_draw(
        canvas          &cvs
      , rectangle const &region)
    {
        draw_filler(cvs, region);
        draw_title(cvs, region);
    }

protected :
    // ======================================================================
    // DO_SET_ATTRIBUTE
    // ======================================================================
    void do_set_attribute(string const &name, any const &attr)
    {
        if (name == ATTRIBUTE_PEN)
        {
            BOOST_AUTO(pen, any_cast<attribute>(&attr));

            if (pen != NULL)
            {
                filler_element_.attribute_ = *pen;
            }
        }

        on_redraw(list_of(rectangle(point(), get_size())));
    }

private :
    // ======================================================================
    // DRAW_FILLER
    // ======================================================================
    void draw_filler(
        canvas          &cvs
      , rectangle const &region)
    {
        for (s32 y_coord = region.origin.y; 
             y_coord < region.origin.y + region.size.height; 
             ++y_coord)
        {
            for (s32 x_coord = region.origin.x; 
                 x_coord < region.origin.x + region.size.width; 
                 ++x_coord)
            {
                cvs[x_coord][y_coord] = filler_element_;
            }
        }
    }

    // ======================================================================
    // DRAW_TITLE
    // ======================================================================
    void draw_title(
        canvas          &cvs
      , rectangle const &region)
    {
        static element_type const default_element(' ');

        for (s32 y_coord = region.origin.y; 
             y_coord < region.origin.y + region.size.height; 
             ++y_coord)
        {
            for (s32 x_coord = region.origin.x; 
                 x_coord < region.origin.x + region.size.width; 
                 ++x_coord)
            {
                BOOST_AUTO(index, x_coord - 2);

                if (index == -1 || index == s32(title_.size()))
                {
                    cvs[x_coord][y_coord] = default_element;
                }
                else if (index >= 0 && index < s32(title_.size()))
                {
                    cvs[x_coord][y_coord] = title_[index];
                }
            }
        }
    }

    vector<element_type> title_;
    element_type         filler_element_;
};

// ==========================================================================
// FRAME IMPLEMENTATION STRUCTURE
// ==========================================================================
struct named_frame::impl
{
public :
    impl(named_frame &self)
        : self_(self)
        , closeable_(false)
    {
    }
    
    // ======================================================================
    // SET_NAME
    // ======================================================================
    void set_name(vector<element_type> name)
    {
        title_bar_->set_title(name);
    }
    
    // ======================================================================
    // SET_CLOSEABLE
    // ======================================================================
    void set_closeable(bool closeable)
    {
        closeable_ = closeable;

        if (closeable_)
        {
            attribute pen;
            pen.foreground_colour_ = odin::ansi::graphics::COLOUR_RED;
            pen.intensity_ = odin::ansi::graphics::INTENSITY_BOLD;

            top_right_->set_attribute(ATTRIBUTE_LOCK,  false);
            top_right_->set_attribute(ATTRIBUTE_GLYPH, single_lined_top_right_corner);
            top_right_->set_attribute(ATTRIBUTE_PEN,   pen);
            top_right_->set_attribute(ATTRIBUTE_LOCK,  true);
        }
        else
        {
            top_right_->set_attribute(ATTRIBUTE_LOCK,  false);
            top_right_->set_attribute(ATTRIBUTE_GLYPH, double_lined_top_right_corner);
            top_right_->set_attribute(ATTRIBUTE_PEN,   attribute());
        }
    }
    
    // ======================================================================
    // HANDLE_MOUSE_CLICK
    // ======================================================================
    bool handle_mouse_click(odin::ansi::mouse_report const *report)
    {
        bool handled = false;
        
        // If we're closeable, then check to see if the close button has been
        // pressed.  If so, fire the close signal.
        if (closeable_)
        {
            BOOST_AUTO(position, self_.get_position());
            BOOST_AUTO(size,     self_.get_size());
            
            point close_button((position.x + size.width) - 1, 0);
            
            if (report->x_position_ == close_button.x
             && report->y_position_ == close_button.y)
            {
                self_.on_close();
                handled = true;
            }
        }
        
        return handled;
    }
    
    named_frame                 &self_;
    shared_ptr<title_bar>        title_bar_;
    shared_ptr<component>        top_right_;
    bool                         closeable_;
};

// ==========================================================================
// CONSTRUCTOR
// ==========================================================================
named_frame::named_frame()
    : basic_frame(
          make_shared<filled_box>(element_type(double_lined_top_left_corner))
        , make_shared<title_bar>(
              elements_from_string(""), element_type(double_lined_horizontal_beam))
        , make_shared<filled_box>(element_type(double_lined_top_right_corner))
        , make_shared<filled_box>(element_type(double_lined_vertical_beam))
        , make_shared<filled_box>(element_type(double_lined_vertical_beam))
        , make_shared<filled_box>(element_type(double_lined_bottom_left_corner))
        , make_shared<filled_box>(element_type(double_lined_horizontal_beam))
        , make_shared<filled_box>(element_type(double_lined_bottom_right_corner)))
{
    pimpl_ = make_shared<impl>(ref(*this));
    pimpl_->title_bar_ = dynamic_pointer_cast<title_bar>(get_top_component());
    pimpl_->top_right_ = get_top_right_component();
}

// ==========================================================================
// DESTRUCTOR
// ==========================================================================
named_frame::~named_frame()
{
}

// ==========================================================================
// SET_NAME
// ==========================================================================
void named_frame::set_name(string const &name)
{
    set_name(elements_from_string(name));
}

// ==========================================================================
// SET_NAME
// ==========================================================================
void named_frame::set_name(vector<element_type> name)
{
    pimpl_->set_name(name);
    on_redraw(list_of(rectangle(point(), extent(get_size().width, 1))));
}

// ==========================================================================
// SET_CLOSEABLE
// ==========================================================================
void named_frame::set_closeable(bool closeable)
{
    pimpl_->set_closeable(closeable);
}

// ==========================================================================
// DO_EVENT
// ==========================================================================
void named_frame::do_event(any const &event)
{
    bool handled = false;
    
    odin::ansi::mouse_report const *report =
        any_cast<odin::ansi::mouse_report>(&event);
     
    if (report != NULL)
    {
        handled = pimpl_->handle_mouse_click(report);
    }
    
    if (!handled)
    {
        composite_component::do_event(event);
    }
}

}