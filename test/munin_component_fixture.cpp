#include "munin_component_fixture.hpp"
#include "munin/component.hpp"
#include "fake_munin_component.hpp"
#include "fake_munin_graphics_context.hpp"
#include <boost/function.hpp>
#include <boost/lambda/lambda.hpp>

using namespace boost;
using namespace std;
using namespace odin;

namespace bll = boost::lambda;

CPPUNIT_TEST_SUITE_REGISTRATION(munin_component_fixture);

void munin_component_fixture::test_constructor()
{
    fake_component<char> component;
    (void)component;
}

void munin_component_fixture::test_position()
{
    fake_component<char> component;
    
    munin::point position = component.get_position();
    CPPUNIT_ASSERT_EQUAL(u32(0), position.x);
    CPPUNIT_ASSERT_EQUAL(u32(0), position.y);
    
    position.x = 5;
    position.y = 6;
    component.set_position(position);
    
    munin::point new_position = component.get_position();
    CPPUNIT_ASSERT_EQUAL(position.x, new_position.x);
    CPPUNIT_ASSERT_EQUAL(position.y, new_position.y);
}

void munin_component_fixture::test_size()
{
    fake_component<char> component;
    
    munin::extent extent = component.get_size();
    CPPUNIT_ASSERT_EQUAL(u32(0), extent.width);
    CPPUNIT_ASSERT_EQUAL(u32(0), extent.height);
    
    extent.width  = 240;
    extent.height = 480;
    
    component.set_size(extent);
    
    munin::extent new_extent = component.get_size();
    CPPUNIT_ASSERT_EQUAL(extent.width, new_extent.width);
    CPPUNIT_ASSERT_EQUAL(extent.height, new_extent.height);
}

void munin_component_fixture::test_preferred_size()
{
    fake_component<char> component;

    munin::extent preferred_extent =
        static_cast<munin::component<char>&>(component).get_preferred_size();
        
    CPPUNIT_ASSERT_EQUAL(u32(0), preferred_extent.width);
    CPPUNIT_ASSERT_EQUAL(u32(0), preferred_extent.height);
    
    munin::extent extent;
    extent.width  = 240;
    extent.height = 480;
    
    component.set_preferred_size(extent);
    
    preferred_extent =
        static_cast<munin::component<char>&>(component).get_preferred_size();
        
    CPPUNIT_ASSERT_EQUAL(extent.width,  preferred_extent.width);
    CPPUNIT_ASSERT_EQUAL(extent.height, preferred_extent.height);
}

void munin_component_fixture::test_draw()
{
    fake_component<char>      component;
    fake_graphics_context<char> context;
    
    munin::point position;
    position.x = 1;
    position.y = 1;
    component.set_position(position);
    
    munin::extent size;
    size.width  = 4;
    size.height = 4;
    component.set_size(size);
    
    munin::rectangle region;
    region.origin.x = 0;
    region.origin.y = 0;
    region.size.width = 2;
    region.size.height = 2;
    component.set_brush('X');
    
    munin::point offset;
    offset.x = 0;
    offset.y = 0;
    component.draw(context, offset, region);
    
    /* Should be equivalent to:
       "    "
       " XX "
       " XX "
       "    "
       
       where all blanks are '\0's.
    */
    
    CPPUNIT_ASSERT_EQUAL('X', context.values_[1][1]);
    CPPUNIT_ASSERT_EQUAL('X', context.values_[2][1]);
    CPPUNIT_ASSERT_EQUAL('X', context.values_[1][2]);
    CPPUNIT_ASSERT_EQUAL('X', context.values_[2][2]);
    
    CPPUNIT_ASSERT_EQUAL('\0', context.values_[0][0]);
    CPPUNIT_ASSERT_EQUAL('\0', context.values_[1][0]);
    CPPUNIT_ASSERT_EQUAL('\0', context.values_[2][0]);
    CPPUNIT_ASSERT_EQUAL('\0', context.values_[3][0]);
    CPPUNIT_ASSERT_EQUAL('\0', context.values_[0][1]);
    CPPUNIT_ASSERT_EQUAL('\0', context.values_[3][1]);
    CPPUNIT_ASSERT_EQUAL('\0', context.values_[0][2]);
    CPPUNIT_ASSERT_EQUAL('\0', context.values_[3][2]);
    CPPUNIT_ASSERT_EQUAL('\0', context.values_[0][3]);
    CPPUNIT_ASSERT_EQUAL('\0', context.values_[1][3]);
    CPPUNIT_ASSERT_EQUAL('\0', context.values_[2][3]);
    CPPUNIT_ASSERT_EQUAL('\0', context.values_[3][3]);
    
    region.origin.x = 1;
    region.origin.y = 1;
    component.set_brush('Y');
    
    component.draw(context, offset, region);
    
    /* Should be equivalent to:
       "     "
       " XX  "
       " XYY "
       "  YY "
       "     "
    */
    
    CPPUNIT_ASSERT_EQUAL('X', context.values_[1][1]);
    CPPUNIT_ASSERT_EQUAL('X', context.values_[2][1]);
    CPPUNIT_ASSERT_EQUAL('X', context.values_[1][2]);
    
    CPPUNIT_ASSERT_EQUAL('Y', context.values_[2][2]);
    CPPUNIT_ASSERT_EQUAL('Y', context.values_[3][2]);
    CPPUNIT_ASSERT_EQUAL('Y', context.values_[2][3]);
    CPPUNIT_ASSERT_EQUAL('Y', context.values_[3][3]);
    
    CPPUNIT_ASSERT_EQUAL('\0', context.values_[0][0]);
    CPPUNIT_ASSERT_EQUAL('\0', context.values_[1][0]);
    CPPUNIT_ASSERT_EQUAL('\0', context.values_[2][0]);
    CPPUNIT_ASSERT_EQUAL('\0', context.values_[3][0]);
    CPPUNIT_ASSERT_EQUAL('\0', context.values_[4][0]);
    CPPUNIT_ASSERT_EQUAL('\0', context.values_[0][1]);
    CPPUNIT_ASSERT_EQUAL('\0', context.values_[3][1]);
    CPPUNIT_ASSERT_EQUAL('\0', context.values_[4][1]);
    CPPUNIT_ASSERT_EQUAL('\0', context.values_[0][2]);
    CPPUNIT_ASSERT_EQUAL('\0', context.values_[4][2]);
    CPPUNIT_ASSERT_EQUAL('\0', context.values_[0][3]);
    CPPUNIT_ASSERT_EQUAL('\0', context.values_[1][3]);
    CPPUNIT_ASSERT_EQUAL('\0', context.values_[4][3]);
    CPPUNIT_ASSERT_EQUAL('\0', context.values_[0][4]);
    CPPUNIT_ASSERT_EQUAL('\0', context.values_[1][4]);
    CPPUNIT_ASSERT_EQUAL('\0', context.values_[2][4]);
    CPPUNIT_ASSERT_EQUAL('\0', context.values_[3][4]);
    CPPUNIT_ASSERT_EQUAL('\0', context.values_[4][4]);
    
    region.origin.x    = 2;
    region.origin.y    = 2;
    region.size.width  = 1;
    region.size.height = 1;
    component.set_brush('Z');
    
    component.draw(context, offset, region);
    
    /* Should be equivalent to:
       "     "
       " XX  "
       " XYY "
       "  YZ "
       "     "
    */
    
    CPPUNIT_ASSERT_EQUAL('X', context.values_[1][1]);
    CPPUNIT_ASSERT_EQUAL('X', context.values_[2][1]);
    CPPUNIT_ASSERT_EQUAL('X', context.values_[1][2]);
    
    CPPUNIT_ASSERT_EQUAL('Y', context.values_[2][2]);
    CPPUNIT_ASSERT_EQUAL('Y', context.values_[3][2]);
    CPPUNIT_ASSERT_EQUAL('Y', context.values_[2][3]);
    
    CPPUNIT_ASSERT_EQUAL('Z', context.values_[3][3]);
    
    CPPUNIT_ASSERT_EQUAL('\0', context.values_[0][0]);
    CPPUNIT_ASSERT_EQUAL('\0', context.values_[1][0]);
    CPPUNIT_ASSERT_EQUAL('\0', context.values_[2][0]);
    CPPUNIT_ASSERT_EQUAL('\0', context.values_[3][0]);
    CPPUNIT_ASSERT_EQUAL('\0', context.values_[4][0]);
    CPPUNIT_ASSERT_EQUAL('\0', context.values_[0][1]);
    CPPUNIT_ASSERT_EQUAL('\0', context.values_[3][1]);
    CPPUNIT_ASSERT_EQUAL('\0', context.values_[4][1]);
    CPPUNIT_ASSERT_EQUAL('\0', context.values_[0][2]);
    CPPUNIT_ASSERT_EQUAL('\0', context.values_[4][2]);
    CPPUNIT_ASSERT_EQUAL('\0', context.values_[0][3]);
    CPPUNIT_ASSERT_EQUAL('\0', context.values_[1][3]);
    CPPUNIT_ASSERT_EQUAL('\0', context.values_[4][3]);
    CPPUNIT_ASSERT_EQUAL('\0', context.values_[0][4]);
    CPPUNIT_ASSERT_EQUAL('\0', context.values_[1][4]);
    CPPUNIT_ASSERT_EQUAL('\0', context.values_[2][4]);
    CPPUNIT_ASSERT_EQUAL('\0', context.values_[3][4]);
    CPPUNIT_ASSERT_EQUAL('\0', context.values_[4][4]);
}

void munin_component_fixture::test_redraw()
{
    boost::shared_ptr< fake_component<char> > component(
        new fake_component<char>);
    
    vector<munin::rectangle> regions;
    function<void (vector<munin::rectangle>)> on_redraw = (
        bll::var(regions) = bll::_1
    );
    
    component->on_redraw.connect(on_redraw);
    
    CPPUNIT_ASSERT_EQUAL(size_t(0), regions.size());
    
    // Settings the position should not trigger a redraw.  It is the job of the
    // entity doing the sizing (such as a layout manager) to request a redraw.
    munin::point position;
    position.x = 1;
    position.y = 2;
    
    component->set_position(position);
    CPPUNIT_ASSERT_EQUAL(size_t(0), regions.size());
    
    // Setting the size should not trigger a redraw.  It is the job of the
    // entity doing the sizing (such as a layout manager) to request a redraw.
    munin::extent size;
    size.width  = 2;
    size.height = 3;
    
    component->set_size(size);
    
    CPPUNIT_ASSERT_EQUAL(size_t(0), regions.size());
    
    // Setting the brush of our fake component should trigger the component
    // to redraw everything.
    component->set_brush('0');
    
    CPPUNIT_ASSERT_EQUAL(size_t(1), regions.size());
    CPPUNIT_ASSERT_EQUAL(size.width,  regions[0].size.width);
    CPPUNIT_ASSERT_EQUAL(size.height, regions[0].size.height);
}