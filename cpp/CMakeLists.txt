# Copyright 2013 Andrew Punch
#
# Licensed under the Apache License, Version 2.0 (the 'License')
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#         http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an 'AS IS' BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "-std=c++0x -Wall -Werror -O3 -fPIC -g")
 
if(COMMAND cmake_policy)
  cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

FIND_PACKAGE (Boost REQUIRED COMPONENTS
              system
              regex)
#enable_testing()
#find_path(GTEST_INC gtest/gtest.h)
#INCLUDE_DIRECTORIES(${GTEST_INC})
#find_library(GTEST_LIB libgtest.so)
#find_library(GTEST_LIB_STATIC libgtest.a)
INCLUDE(FindPkgConfig)
pkg_check_modules(YAML yaml-cpp)
pkg_check_modules(GLOG libglog)

add_library(uaparser_cpp_OBJLIB OBJECT UaParser.cpp)
set_target_properties(uaparser_cpp_OBJLIB PROPERTIES POSITION_INDEPENDENT_CODE 1)
add_library(uaparser_cpp SHARED $<TARGET_OBJECTS:uaparser_cpp_OBJLIB>)
add_library(uaparser_cpp_static STATIC $<TARGET_OBJECTS:uaparser_cpp_OBJLIB> )
set_target_properties(uaparser_cpp_static PROPERTIES OUTPUT_NAME uaparser_cpp)
target_link_libraries(uaparser_cpp ${YAML_LIBRARIES} ${GLOG_LIBRARIES} ${Boost_LIBRARIES})
target_link_libraries(uaparser_cpp_static ${YAML_LIBRARIES} ${GLOG_LIBRARIES} ${Boost_LIBRARIES})

#add_executable(UaParserStaticTest UaParserTest.cpp)
#target_link_libraries(UaParserStaticTest libuaparser_cpp_static${YAML_LIBRARIES} ${GLOG_LIBRARIES} ${Boost_LIBRARIES} ${GTEST_LIB})

#add_executable(UaParserDynamicTest UaParserTest.cpp)
#target_link_libraries(UaParserDynamicTest libuaparser_cpp ${YAML_LIBRARIES} ${GLOG_LIBRARIES} ${Boost_LIBRARIES} ${GTEST_LIB})

add_library(ua_parser_OBJLIB OBJECT ua_parser.cpp)
set_target_properties(ua_parser_OBJLIB PROPERTIES POSITION_INDEPENDENT_CODE 1)
add_library(ua_parser SHARED $<TARGET_OBJECTS:ua_parser_OBJLIB>)
add_library(ua_parser_static STATIC $<TARGET_OBJECTS:ua_parser_OBJLIB>)
set_target_properties(ua_parser_static PROPERTIES OUTPUT_NAME ua_parser)
target_link_libraries(ua_parser_static ${YAML_LIBRARIES} ${GLOG_LIBRARIES} ${Boost_LIBRARIES})
target_link_libraries(ua_parser ${YAML_LIBRARIES} ${GLOG_LIBRARIES} ${Boost_LIBRARIES})

add_executable(ua_parser_cli main.cpp)
target_link_libraries(ua_parser_cli ua_parser ${YAML_LIBRARIES} ${GLOG_LIBRARIES} ${Boost_LIBRARIES})

#add_executable(ua_parser_test ua_parser_test.cpp)
#target_link_libraries(ua_parser_test ua_parser pthread)
