////////////////////////////////////////////////////////////////////////////////
/// DISCLAIMER
///
/// Copyright 2014-2016 ArangoDB GmbH, Cologne, Germany
/// Copyright 2004-2014 triAGENS GmbH, Cologne, Germany
///
/// Licensed under the Apache License, Version 2.0 (the "License");
/// you may not use this file except in compliance with the License.
/// You may obtain a copy of the License at
///
///     http://www.apache.org/licenses/LICENSE-2.0
///
/// Unless required by applicable law or agreed to in writing, software
/// distributed under the License is distributed on an "AS IS" BASIS,
/// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
/// See the License for the specific language governing permissions and
/// limitations under the License.
///
/// Copyright holder is ArangoDB GmbH, Cologne, Germany
///
/// @author Jan Steemann
////////////////////////////////////////////////////////////////////////////////

#ifndef ARANGODB_V8_V8__VPACK_H
#define ARANGODB_V8_V8__VPACK_H 1

#include <node.h>
#include <velocypack/Builder.h>
#include <velocypack/Options.h>
#include <velocypack/Slice.h>

#define TRI_ERROR_NO_ERROR 0
#define TRI_ERROR_OUT_OF_MEMORY 1
#define TRI_ERROR_BAD_PARAMETER 2
#define TRI_ERROR_INTERNAL 3

#define THROW_ARANGO_EXCEPTION_MESSAGE(code, message) \
  throw std::exception()


#define TRI_V8_STD_STRING(name)                                             \
  v8::String::NewFromUtf8(isolate, name.c_str(), v8::String::kNormalString, \
                          (int)name.length())


#define TRI_V8_PAIR_STRING(name, length)                              \
  v8::String::NewFromUtf8(isolate, (name), v8::String::kNormalString, \
                          (int)(length))

#define TRI_ASSERT(test) assert(test)
////////////////////////////////////////////////////////////////////////////////
/// @brief converts a VPack value into a V8 object
////////////////////////////////////////////////////////////////////////////////

v8::Handle<v8::Value> TRI_VPackToV8(
    v8::Isolate* isolate, arangodb::velocypack::Slice const&,
    arangodb::velocypack::Options const* options =
        &arangodb::velocypack::Options::Defaults,
    arangodb::velocypack::Slice const* base = nullptr);

////////////////////////////////////////////////////////////////////////////////
/// @brief convert a V8 value to VPack value
////////////////////////////////////////////////////////////////////////////////

int TRI_V8ToVPack(v8::Isolate* isolate, arangodb::velocypack::Builder& builder,
                  v8::Handle<v8::Value> const value, bool keepTopLevelOpen);

////////////////////////////////////////////////////////////////////////////////
/// @brief convert a V8 value to VPack value, simplified version
/// this function assumes that the V8 object does not contain any cycles and
/// does not contain types such as Function, Date or RegExp
////////////////////////////////////////////////////////////////////////////////

int TRI_V8ToVPackSimple(v8::Isolate* isolate, arangodb::velocypack::Builder& builder,
                        v8::Handle<v8::Value> const value);

#endif
