// ==========================================================================
// Munin ANSI Framed Component.
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
#include "munin/ansi/framed_component.hpp"
#include "munin/ansi/basic_container.hpp"
#include "munin/ansi/frame.hpp"
#include "munin/layout.hpp"
#include "odin/ansi/protocol.hpp"
#include <boost/typeof/typeof.hpp>
#include <boost/make_shared.hpp>

using namespace odin;
using namespace boost;
using namespace std;

namespace munin { namespace ansi {
    
namespace {
        
//* =========================================================================
/// \brief A specialised layout for frames that place the interior component
/// inside the frame's borders.
//* =========================================================================
class framed_component_layout
    : public munin::layout<munin::ansi::element_type>
{
public :
    enum hint_type
    {
        hint_type_border
      , hint_type_interior
    };

private :
    //* =====================================================================
    /// \brief Called by get_preferred_size().  Derived classes must override
    /// this function in order to retrieve the preferred size of the layout
    /// in a custom manner.
    //* =====================================================================
    virtual extent do_get_preferred_size(
        boost::shared_ptr<container_type const> const &cont) const
    {
        extent preferred_size;
        
        for (u32 index = 0; index < cont->get_number_of_components(); ++index)
        {
            BOOST_AUTO(comp, cont->get_component(index));
            
            preferred_size += comp->get_preferred_size();
        }
        
        return preferred_size;
    }

    //* =====================================================================
    /// \brief Called by operator().  Derived classes must override this
    /// function in order to lay a container's components out in a custom
    /// manner.
    //* =====================================================================
    virtual void do_layout(shared_ptr<container_type> const &cont)
    {
        // This layout expects only two subcomponents: a frame, and a central
        // component.  It lays them out in the expected format.  In addition,
        BOOST_AUTO(size, cont->get_size());

        for (u32 index = 0; index < cont->get_number_of_components(); ++index)
        {
            BOOST_AUTO(comp, cont->get_component(index));
            BOOST_AUTO(any_hint, cont->get_component_hint(index));

            BOOST_AUTO(hint, any_cast<hint_type>(any_hint));

            if (hint == hint_type_border)
            {
                comp->set_position(munin::point(0, 0));
                comp->set_size(size);
            }
            else if (hint == hint_type_interior)
            {
                comp->set_position(munin::point(1, 1));
                comp->set_size(
                    munin::extent(size.width - 2, size.height - 2));
            }
        }
    }
};

}

// ==========================================================================
// FRAMED_COMPONENT::IMPLEMENTATION_STRUCTURE
// ==========================================================================
struct framed_component::impl
{
    impl(shared_ptr< munin::frame<munin::ansi::element_type> > border
       , shared_ptr< munin::component<munin::ansi::element_type> > interior)
        : border_(border)
        , interior_(interior)
    {
    }
        
    void update_pen()
    {
        BOOST_AUTO(border,   border_.lock());
        BOOST_AUTO(interior, interior_.lock());
        
        if (border != NULL && interior != NULL)
        {
            border->set_attribute(
                ATTRIBUTE_PEN
              , interior->has_focus()
                    ? focussed_pen_
                    : unfocussed_pen_);
        }
    }
    
    weak_ptr< munin::frame<munin::ansi::element_type> >     border_;
    weak_ptr< munin::component<munin::ansi::element_type> > interior_;
    
    attribute focussed_pen_;
    attribute unfocussed_pen_;
};

// ==========================================================================
// CONSTRUCTOR
// ==========================================================================
framed_component::framed_component(
    shared_ptr< munin::frame<munin::ansi::element_type> >     border
  , shared_ptr< munin::component<munin::ansi::element_type> > interior)
    : munin::composite_component<element_type>(make_shared<basic_container>())
    , pimpl_(new impl(border, interior))
{
    BOOST_AUTO(container, get_container());
    
    container->set_layout(make_shared<framed_component_layout>());
    container->add_component(
        border, framed_component_layout::hint_type_border);
    container->add_component(
        interior, framed_component_layout::hint_type_interior);
    
    interior->on_focus_set.connect(bind(&impl::update_pen, pimpl_.get()));
    interior->on_focus_lost.connect(bind(&impl::update_pen, pimpl_.get()));
    
    pimpl_->focussed_pen_.foreground_colour = 
        odin::ansi::graphics::COLOUR_CYAN;
    pimpl_->focussed_pen_.intensity = 
        odin::ansi::graphics::INTENSITY_BOLD;
}

// ==========================================================================
// DESTRUCTOR
// ==========================================================================
framed_component::~framed_component()
{
}

// ==========================================================================
// DO_SET_ATTRIBUTE
// ==========================================================================
void framed_component::do_set_attribute(string const &name, any const &attr)
{
    if (name == FOCUSSED_BORDER_PEN)
    {
        attribute const *pen = any_cast<attribute>(&attr);
        
        if (pen != NULL)
        {
            pimpl_->focussed_pen_ = *pen;
            pimpl_->update_pen();
        }
    }
    else if (name == UNFOCUSSED_BORDER_PEN)
    {
        attribute const *pen = any_cast<attribute>(&attr);
        
        if (pen != NULL)
        {
            pimpl_->unfocussed_pen_ = *pen;
            pimpl_->update_pen();
        }
    }
}

}}
