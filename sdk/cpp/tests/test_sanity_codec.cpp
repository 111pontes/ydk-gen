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

#include <iostream>
#include <string.h>

#include <ydk/codec_provider.hpp>
#include <ydk/codec_service.hpp>
#include <ydk/path_api.hpp>
#include <ydk_ydktest/ydktest_sanity.hpp>
#include <ydk_ydktest/ydktest_sanity_types.hpp>
#include <ydk_ydktest/ydktest_sanity_typedefs.hpp>
#include <ydk_ydktest/oc_pattern.hpp>

#include <ydk_ydktest_new/ietf_system.hpp>

#include <ydk_ydktest/openconfig_routing_policy.hpp>

#include "config.hpp"
#include "catch.hpp"

using namespace std;
using namespace ydktest;
using namespace ydktest_new;
using namespace ydk;

std::string XML_OC_PATTERN_PAYLOAD = R"(<oc-A xmlns="http://cisco.com/ns/yang/oc-pattern">
  <a>Hello</a>
<B><b>Hello</b></B>
</oc-A>
)";

std::string XML_ENUM_PAYLOAD_2 = R"(<runner xmlns="http://cisco.com/ns/yang/ydktest-sanity">
  <ytypes>
    <built-in-t>
      <enum-value>local</enum-value>
    </built-in-t>
  </ytypes>
</runner>
)";

std::string XML_RUNNER_PAYLOAD_1 = R"(<runner xmlns="http://cisco.com/ns/yang/ydktest-sanity">
  <two-list>
    <ldata>
      <number>11</number>
      <name>l11name</name>
      <subl1>
        <number>111</number>
        <name>s111name</name>
      </subl1>
      <subl1>
        <number>112</number>
        <name>s112name</name>
      </subl1>
    </ldata>
    <ldata>
      <number>12</number>
      <name>l12name</name>
      <subl1>
        <number>121</number>
        <name>s121name</name>
      </subl1>
      <subl1>
        <number>122</number>
        <name>s122name</name>
      </subl1>
    </ldata>
  </two-list>
</runner>
)";

std::string XML_RUNNER_PAYLOAD_2 = R"(<runner xmlns="http://cisco.com/ns/yang/ydktest-sanity">
  <two-list>
    <ldata>
      <number>21</number>
      <name>modified</name>
      <subl1>
        <number>211</number>
        <name>s211name</name>
      </subl1>
      <subl1>
        <number>212</number>
        <name>s212name</name>
      </subl1>
    </ldata>
    <ldata>
      <number>22</number>
      <name>l22name</name>
      <subl1>
        <number>221</number>
        <name>s221name</name>
      </subl1>
      <subl1>
        <number>222</number>
        <name>s222name</name>
      </subl1>
    </ldata>
  </two-list>
</runner>
)";

std::string JSON_RUNNER_PAYLOAD_1 = R"({
  "ydktest-sanity:runner": {
    "two-list": {
      "ldata": [
        {
          "number": 11,
          "name": "l11name",
          "subl1": [
            {
              "number": 111,
              "name": "s111name"
            },
            {
              "number": 112,
              "name": "s112name"
            }
          ]
        },
        {
          "number": 12,
          "name": "l12name",
          "subl1": [
            {
              "number": 121,
              "name": "s121name"
            },
            {
              "number": 122,
              "name": "s122name"
            }
          ]
        }
      ]
    }
  }
}
)";

std::string JSON_RUNNER_PAYLOAD_2 = R"({
  "ydktest-sanity:runner": {
    "two-list": {
      "ldata": [
        {
          "number": 21,
          "name": "modified",
          "subl1": [
            {
              "number": 211,
              "name": "s211name"
            },
            {
              "number": 212,
              "name": "s212name"
            }
          ]
        },
        {
          "number": 22,
          "name": "l22name",
          "subl1": [
            {
              "number": 221,
              "name": "s221name"
            },
            {
              "number": 222,
              "name": "s222name"
            }
          ]
        }
      ]
    }
  }
}
)";

void
config_runner_2(ydktest_sanity::Runner *runner)
{
    auto l_1 = std::make_unique<ydktest_sanity::Runner::TwoList::Ldata>();
    auto l_2 = std::make_unique<ydktest_sanity::Runner::TwoList::Ldata>();
    auto s_11 = std::make_unique<ydktest_sanity::Runner::TwoList::Ldata::Subl1>();
    auto s_12 = std::make_unique<ydktest_sanity::Runner::TwoList::Ldata::Subl1>();
    auto s_21 = std::make_unique<ydktest_sanity::Runner::TwoList::Ldata::Subl1>();
    auto s_22 = std::make_unique<ydktest_sanity::Runner::TwoList::Ldata::Subl1>();

    l_1->number = 21;
    l_1->name = "l21name";
    l_1->parent = runner->two_list.get();
    l_2->number = 22;
    l_2->name = "l22name";
    l_2->parent = runner->two_list.get();
    s_11->number = 211;
    s_11->name = "s211name";
    s_11->parent = l_1.get();
    s_12->number = 212;
    s_12->name = "s212name";
    s_12->parent = l_1.get();
    s_21->number = 221;
    s_21->name = "s221name";
    s_21->parent = l_2.get();
    s_22->number = 222;
    s_22->name = "s222name";
    s_22->parent = l_2.get();

    l_1->subl1.push_back(std::move(s_11));
    l_1->subl1.push_back(std::move(s_12));
    l_2->subl1.push_back(std::move(s_21));
    l_2->subl1.push_back(std::move(s_22));

    runner->two_list->ldata.push_back(std::move(l_1));
    runner->two_list->ldata.push_back(std::move(l_2));
}

void
config_runner_1(ydktest_sanity::Runner *runner)
{
    auto l_1 = std::make_unique<ydktest_sanity::Runner::TwoList::Ldata>();
    auto l_2 = std::make_unique<ydktest_sanity::Runner::TwoList::Ldata>();
    auto s_11 = std::make_unique<ydktest_sanity::Runner::TwoList::Ldata::Subl1>();
    auto s_12 = std::make_unique<ydktest_sanity::Runner::TwoList::Ldata::Subl1>();
    auto s_21 = std::make_unique<ydktest_sanity::Runner::TwoList::Ldata::Subl1>();
    auto s_22 = std::make_unique<ydktest_sanity::Runner::TwoList::Ldata::Subl1>();

    l_1->number = 11;
    l_1->name = "l11name";
    l_1->parent = runner->two_list.get();
    l_2->number = 12;
    l_2->name = "l12name";
    l_2->parent = runner->two_list.get();
    s_11->number = 111;
    s_11->name = "s111name";
    s_11->parent = l_1.get();
    s_12->number = 112;
    s_12->name = "s112name";
    s_12->parent = l_1.get();
    s_21->number = 121;
    s_21->name = "s121name";
    s_21->parent = l_2.get();
    s_22->number = 122;
    s_22->name = "s122name";
    s_22->parent = l_2.get();

    l_1->subl1.push_back(std::move(s_11));
    l_1->subl1.push_back(std::move(s_12));
    l_2->subl1.push_back(std::move(s_21));
    l_2->subl1.push_back(std::move(s_22));

    runner->two_list->ldata.push_back(std::move(l_1));
    runner->two_list->ldata.push_back(std::move(l_2));
}

TEST_CASE("typedef_encode")
{
    CodecServiceProvider codec_provider{EncodingFormat::XML};
    CodecService codec_service{};

    // Create class System and set values for its members
    auto system = std::make_unique<ydktest_sanity_typedefs::System>();
    system->id = 22;
    system->mode = ydktest_sanity_typedefs::TopMode::stand_alone;

    std::string xml = codec_service.encode(codec_provider, *system, true);

    auto system_decoded = codec_service.decode(codec_provider, xml, std::make_unique<ydktest_sanity_typedefs::System>());

    CHECK(*system_decoded == *system);
}

TEST_CASE("single_encode")
{
    CodecServiceProvider codec_provider{EncodingFormat::XML};

    CodecService codec_service{};

    auto runner = std::make_unique<ydktest_sanity::Runner>();

    config_runner_1(runner.get());

    std::string xml = codec_service.encode(codec_provider, *runner, true);
    CHECK(XML_RUNNER_PAYLOAD_1 == xml);
}

TEST_CASE("multiple_encode")
{

    CodecServiceProvider codec_provider{EncodingFormat::XML};
    CodecService codec_service{};

    auto runner1 = std::make_unique<ydktest_sanity::Runner>();
    auto runner2 = std::make_unique<ydktest_sanity::Runner>();

    config_runner_1(runner1.get());
    config_runner_2(runner2.get());

    runner2->two_list->ldata[0]->name = "modified";

    std::map<std::string, std::unique_ptr<Entity>> entity_map;
    entity_map["runner1"] = std::move(runner1);
    entity_map["runner2"] = std::move(runner2);

    std::map<std::string, std::string> payload_map = codec_service.encode(codec_provider, entity_map, true);

    CHECK(payload_map["runner1"] == XML_RUNNER_PAYLOAD_1);
    CHECK(payload_map["runner2"] == XML_RUNNER_PAYLOAD_2);
}

// YCoreError: YCodecError:Unknown element "oc-A".. Path:
TEST_CASE("test_oc_pattern")
{
//TODO
//    CodecServiceProvider codec_provider{EncodingFormat::JSON};
//    CodecService codec_service{};
//
//    auto entity = codec_service.decode(codec_provider, "{\n"
//            "  \"oc-pattern:oc-A\": [\n"
//            "    {\n"
//            "      \"a\": \"Hello\",\n"
//            "      \"B\": {\n"
//            "        \"b\": \"Hello\"\n"
//            "      }\n"
//            "    }\n"
//            "  ]\n"
//            "}", make_unique<oc_pattern::OcA>());
//
//    oc_pattern::OcA * entity_ptr = dynamic_cast<oc_pattern::OcA*>(entity.get());
//    CHECK(entity_ptr->a.get() == "Hello");
}

TEST_CASE("enum_2")
{

    CodecServiceProvider codec_provider{EncodingFormat::XML};
    CodecService codec_service{};

    auto entity = codec_service.decode(codec_provider, XML_ENUM_PAYLOAD_2, make_shared<ydktest_sanity::Runner>());
    ydktest_sanity::Runner * entity_ptr = dynamic_cast<ydktest_sanity::Runner*>(entity.get());
    CHECK(entity_ptr->ytypes->built_in_t->enum_value.get() == "local");
}

TEST_CASE("single_decode")
{

    CodecServiceProvider codec_provider{EncodingFormat::JSON};
    CodecService codec_service{};

    auto entity = codec_service.decode(codec_provider, JSON_RUNNER_PAYLOAD_1, make_shared<ydktest_sanity::Runner>());
    CHECK(entity!=nullptr);

    ydktest_sanity::Runner * entity_ptr = dynamic_cast<ydktest_sanity::Runner*>(entity.get());

    CHECK(entity_ptr->two_list->ldata[0]->number.get() == "11");
    CHECK(entity_ptr->two_list->ldata[0]->name.get() == "l11name");
    CHECK(entity_ptr->two_list->ldata[0]->subl1[0]->number.get() == "111");
    CHECK(entity_ptr->two_list->ldata[0]->subl1[0]->name.get() == "s111name");
    CHECK(entity_ptr->two_list->ldata[0]->subl1[1]->number.get() == "112");
    CHECK(entity_ptr->two_list->ldata[0]->subl1[1]->name.get() == "s112name");
    CHECK(entity_ptr->two_list->ldata[1]->number.get() == "12");
    CHECK(entity_ptr->two_list->ldata[1]->name.get() == "l12name");
    CHECK(entity_ptr->two_list->ldata[1]->subl1[0]->number.get() == "121");
    CHECK(entity_ptr->two_list->ldata[1]->subl1[0]->name.get() == "s121name");
    CHECK(entity_ptr->two_list->ldata[1]->subl1[1]->number.get() == "122");
    CHECK(entity_ptr->two_list->ldata[1]->subl1[1]->name.get() == "s122name");
}

TEST_CASE("encode_decode")
{

     CodecServiceProvider codec_provider{EncodingFormat::XML};
     CodecService codec_service{};

     std::string test = "<runner xmlns=\"http://cisco.com/ns/yang/ydktest-sanity\"><one><name>test</name></one></runner>";

     auto entity = codec_service.decode(codec_provider, test, make_shared<ydktest_sanity::Runner>());
     CHECK(entity!=nullptr);

     std::string xml = codec_service.encode(codec_provider, *entity);
     CHECK(xml == test);

     auto redecode = codec_service.decode(codec_provider, xml, make_shared<ydktest_sanity::Runner>()) ;
     CHECK(redecode!=nullptr);

     ydktest_sanity::Runner * entity_ptr = dynamic_cast<ydktest_sanity::Runner*>(redecode.get());
     auto runner = std::make_unique<ydktest_sanity::Runner>();
     runner->ydktest_sanity_one->name = "test";

     CHECK(entity_ptr->ydktest_sanity_one->name == runner->ydktest_sanity_one->name);
}

TEST_CASE("multiple_bundles_codec")
{
    CodecServiceProvider codec_provider{EncodingFormat::XML};

    CodecService codec_service{};

    auto runner = std::make_unique<ydktest_sanity::Runner>();
    config_runner_1(runner.get());
    std::string xml = codec_service.encode(codec_provider, *runner, true);
    CHECK(XML_RUNNER_PAYLOAD_1 == xml);

    auto system = std::make_unique<ietf_system::System>();
    system->contact = "1223";
    xml = codec_service.encode(codec_provider, *system, true);
    CHECK(xml == "<system xmlns=\"urn:ietf:params:xml:ns:yang:ietf-system\">\n"
            "  <contact>1223</contact>\n"
            "</system>\n");

    xml = codec_service.encode(codec_provider, *runner, true);
    CHECK(XML_RUNNER_PAYLOAD_1 == xml);

    xml = codec_service.encode(codec_provider, *system, true);
    CHECK(xml == "<system xmlns=\"urn:ietf:params:xml:ns:yang:ietf-system\">\n"
            "  <contact>1223</contact>\n"
            "</system>\n");
}

TEST_CASE("user_provided_repo")
{
    ydk::path::Repository repo{TEST_HOME};
    CodecServiceProvider codec_provider{repo, EncodingFormat::XML};

    CodecService codec_service{};

    auto runner = std::make_unique<ydktest_sanity::Runner>();

    config_runner_1(runner.get());

    std::string xml = codec_service.encode(codec_provider, *runner, true);
    CHECK(XML_RUNNER_PAYLOAD_1 == xml);
}

TEST_CASE("invalid_decode")
{
    std::string invalid_xml = R"(<runner xmlns="http://cisco.com/ns/yang/ydktest-sanity">
      <ytypes>
        <built-in-t>
          <llstring>abc</llstring>
          <llstring>abc</llstring>
        </built-in-t>
      </ytypes>
    </runner>
    )";

    CodecServiceProvider codec_provider{EncodingFormat::XML};
    CodecService codec_service{};

    CHECK_THROWS_AS(codec_service.decode(codec_provider, invalid_xml, make_unique<ydktest_sanity::Runner>()), YModelError);

}

TEST_CASE("embedded_quote_codec")
{
    std::string xml = R"(<routing-policy xmlns="http://openconfig.net/yang/routing-policy"><defined-sets><bgp-defined-sets xmlns="http://openconfig.net/yang/bgp-policy"><community-sets><community-set><community-set-name>COMMUNITY-SET1</community-set-name><config><community-set-name>COMMUNITY-SET1</community-set-name><community-member>ios-regex '^65172:17...$'</community-member><community-member>65172:16001</community-member></config><state><community-set-name>COMMUNITY-SET1</community-set-name><community-member>ios-regex '^65172:17... $'</community-member><community-member>65172:16001</community-member></state></community-set></community-sets></bgp-defined-sets></defined-sets></routing-policy>)";

    CodecServiceProvider codec_provider{EncodingFormat::XML};
    CodecService codec_service{};

    auto rp = codec_service.decode(codec_provider, xml, make_unique<openconfig_routing_policy::RoutingPolicy>());

    std::string encoded_xml = codec_service.encode(codec_provider, *rp, false);
    CHECK(xml == encoded_xml);

    auto rp_decode = codec_service.decode(codec_provider, xml, make_unique<openconfig_routing_policy::RoutingPolicy>());
    CHECK(*rp == *rp_decode);
}

TEST_CASE("TestSessionPathAnyxml")
{
    ydk::path::Codec s{};
    ydk::path::NetconfSession session{"127.0.0.1", "admin", "admin",  12022};
    ydk::path::RootSchemaNode& root_schema = session.get_root_schema();

    auto & schema = session.get_root_schema();

    std::string xml = R"(<?xml version="1.0"?><runner xmlns="http://cisco.com/ns/yang/ydktest-sanity"><ytypes><built-in-t><bits-value>disable-nagle auto-sense-speed</bits-value></built-in-t></ytypes></runner>)";
    auto a = s.decode(schema, xml, EncodingFormat::XML);
    REQUIRE(a!=nullptr);

    schema = session.get_root_schema();
    xml = R"(<?xml version="1.0"?>
    <runner xmlns="http://cisco.com/ns/yang/ydktest-sanity"><ytypes><built-in-t><bits-value>disable-nagle auto-sense-speed</bits-value></built-in-t></ytypes></runner>)";
    a = s.decode(schema, xml, EncodingFormat::XML);
    REQUIRE(a!=nullptr);
}
