#include "telnet_options_subnegotiationless_server_fixture.hpp"
#include "odin/telnet/options/subnegotiationless_server.hpp"
#include "odin/telnet/stream.hpp"
#include "odin/telnet/router.hpp"
#include "odin/telnet/protocol.hpp"
#include "fake_datastream.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(telnet_options_subnegotiationless_server_fixture);

using namespace std;
using namespace boost;

typedef fake_datastream<odin::u8, odin::u8> fake_byte_stream;

void telnet_options_subnegotiationless_server_fixture::test_constructor()
{
    boost::asio::io_service          io_service;
    shared_ptr<fake_byte_stream>     fake_stream(
        new fake_datastream<odin::u8, odin::u8>(io_service));
    shared_ptr<odin::telnet::stream> telnet_stream(
        new odin::telnet::stream(fake_stream, io_service));
    shared_ptr<odin::telnet::router> telnet_router(
        new odin::telnet::router(telnet_stream));

    odin::telnet::options::subnegotiationless_server<
        odin::telnet::ECHO
    > echo_server(telnet_stream, telnet_router);
    
    odin::telnet::options::subnegotiationless_server<
        odin::telnet::SUPPRESS_GOAHEAD
    > suppress_ga_server(telnet_stream, telnet_router);
    
    CPPUNIT_ASSERT_EQUAL(odin::telnet::ECHO, echo_server.get_option_id());
    CPPUNIT_ASSERT_EQUAL(
        odin::telnet::SUPPRESS_GOAHEAD
      , suppress_ga_server.get_option_id());
}

void telnet_options_subnegotiationless_server_fixture::test_inheritance()
{
    boost::asio::io_service          io_service;
    shared_ptr<fake_byte_stream>     fake_stream(
        new fake_datastream<odin::u8, odin::u8>(io_service));
    shared_ptr<odin::telnet::stream> telnet_stream(
        new odin::telnet::stream(fake_stream, io_service));
    shared_ptr<odin::telnet::router> telnet_router(
        new odin::telnet::router(telnet_stream));

    odin::telnet::options::subnegotiationless_server<
        odin::telnet::ECHO
    > subnegotiationless_server(telnet_stream, telnet_router);
    
    odin::telnet::server_option &option = subnegotiationless_server;
    (void)option;
}