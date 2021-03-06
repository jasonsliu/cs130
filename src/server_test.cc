#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include "config_parser.h"
#include <vector>
#include <iostream>
#include <string>
#include "gtest/gtest.h"
#include "server.h"

// Server initialization test
TEST(ServerTest, SimpleServerTest) {
	boost::asio::io_service io_service;

	// "config" should eventually be moved to a global constant
	Server *server = Server::makeServer(io_service, "test_config");
	EXPECT_TRUE(server != nullptr);
	delete server;
}

TEST(ServerInfoTest, GetServerInfo) {
	ServerInfo info;
	EXPECT_TRUE(Server::getServerInfo("config_parser/test_config", &info));
	EXPECT_EQ(info.port, 2020);
	EXPECT_EQ(info.uri_prefix_to_handler.size(), 4);
}

TEST(ServerInfoTest, UnexpectedConfig) {
	ServerInfo info;
	EXPECT_FALSE(Server::getServerInfo("config_parser/test_config_bad", &info));
}

TEST(ServerInfoTest, DuplicatePort) {
	ServerInfo info;
	EXPECT_FALSE(Server::getServerInfo("config_parser/test_config_bad2", &info));
}

TEST(ServerInfoTest, DuplicateHandler) {
	ServerInfo info;
	EXPECT_FALSE(Server::getServerInfo("config_parser/test_config_bad2", &info));
}
