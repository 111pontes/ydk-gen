/*  ----------------------------------------------------------------
 Copyright 2016 Cisco Systems

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
------------------------------------------------------------------*/

#ifndef _ARGS_PARSER_H_
#define _ARGS_PARSER_H_

#include <string>
#include <vector>


#ifndef _UTILITY_MODULE_
const char* TEST_HOME = "/home/yan/ydk-workspace/ydk-gen/sdk/cpp/gnmi/samples/../../core/tests/models";
#endif

void show_usage(std::string name);
std::vector<std::string> parse_args(int argc, char* argv[]);

// Test utilities
void print_tree(ydk::path::DataNode* dn, const std::string& indent);
void print_data_node(std::shared_ptr<ydk::path::DataNode> dn);
void print_entity(std::shared_ptr<ydk::Entity> entity, ydk::path::RootSchemaNode& root);

#endif /* _ARGS_PARSER_H_*/
