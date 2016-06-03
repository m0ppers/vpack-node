// vpack-node.cpp
#include <node.h>
#include "nan.h"

#include <iostream>

#include <velocypack/Builder.h>
#include <velocypack/Buffer.h>
#include <velocypack/Hexdump.h>
#include <velocypack/velocypack-aliases.h>

#include "v8-vpack.h"

namespace VPackNode {

using v8::Context;
using v8::Exception;
using v8::Function;
using v8::FunctionCallbackInfo;
using v8::Handle;
using v8::Isolate;
using v8::Local;
using v8::Object;
using v8::String;
using v8::Value;

void decode(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();

    // Check the number of arguments passed.
    if (args.Length() < 1) {
        // Throw an Error that is passed back to JavaScript
        isolate->ThrowException(Exception::TypeError(
                    String::NewFromUtf8(isolate, "Wrong number of arguments")));
        return;
    }

    char* buf = node::Buffer::Data(args[0]);

    VPackSlice slice(buf);
    
    std::string json = slice.toJson();
    args.GetReturnValue().Set(TRI_VPackToV8(isolate, slice));
}

void encode(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();

    // Check the number of arguments passed.
    if (args.Length() < 1) {
        // Throw an Error that is passed back to JavaScript
        isolate->ThrowException(Exception::TypeError(
                    String::NewFromUtf8(isolate, "Wrong number of arguments")));
        return;
    }
    
    VPackBuilder builder;
    if (TRI_V8ToVPack(isolate, builder, args[0], false) != TRI_ERROR_NO_ERROR) {
        // Throw an Error that is passed back to JavaScript
        isolate->ThrowException(Exception::TypeError(
                    String::NewFromUtf8(isolate, "Failed transforming to vpack")));
        return;
    }
    
    auto buffer = builder.buffer();
    args.GetReturnValue().Set(Nan::CopyBuffer(
                  (char*)buffer->data(), buffer->size()).ToLocalChecked()
            );
}

void init(Local<Object> exports) {
    NODE_SET_METHOD(exports, "encode", encode);
    NODE_SET_METHOD(exports, "decode", decode);
}

NODE_MODULE(addon, init)

}  // namespace VPackNode
