#pragma once


#ifdef _DEBUG
#pragma  comment(lib, "Protobuf\\Debug\\libprotobufd.lib")
#else
#pragma  comment(lib, "Protobuf\\Release\\libprotobuf.lib")
#endif

#include <iostream>
#include<algorithm>
#include <string>
#include <list>
#include <vector>
#include <deque>
#include <map>
#include <thread>

#include <boost/bind.hpp>
#include <boost/asio.hpp>

#include "Constant.h"


using namespace std;
