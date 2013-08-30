

#include <v8.h>
#include <node.h>
#include <iostream>


#include "moduleName.h"


using namespace node;
using namespace v8;
using namespace std;


// Convert a JavaScript string to a std::string.  To not bother too
// much with string encodings we just use ascii.
string ObjectToString(Local<Value> value) {
  String::Utf8Value utf8_value(value);
  return string(*utf8_value);
}



int GetArgumentIntValue ( const Arguments& args, int argNum, int &value )
{
    if (args[argNum]->IsNumber())
    {
        value = args[argNum]->Int32Value();
    } 
    else {
        string emsg("GetArgumentIntValue arg " + ObjectToString(args[argNum]) + " not an integer");
        ThrowException(Exception::TypeError(String::New(emsg.c_str())));
        return PROCESS_FAIL;
    }
    return PROCESS_OK;
}


int GetArgumentDoubleValue ( const Arguments& args, int argNum, double &value )
{
    if (args[argNum]->IsNumber())
    {
        value = args[argNum]->NumberValue();
    } 
    else {
        string emsg("GetArgumentDoubleValue arg " + ObjectToString(args[argNum]) + " not an number");
        ThrowException(Exception::TypeError(String::New(emsg.c_str())));
        return PROCESS_FAIL;
    }
    return PROCESS_OK;
}


int GetArgumentStringValue ( const Arguments& args, int argNum, string &value)
{
    if (args[argNum]->IsString())
    {
        value = ObjectToString(args[argNum]);    
    } 
    else {
        string emsg("GetArgumentStringValue arg " + ObjectToString(args[argNum]) + " not an string");
        ThrowException(Exception::TypeError(String::New(emsg.c_str())));
        return PROCESS_FAIL;
    }
    return PROCESS_OK;

}

static Handle<Value> hello(const Arguments& args)
{
    if (args.Length() < 1) {
        ThrowException(Exception::TypeError(String::New("ModuleName::hello invalid number of arguments, expect 1")));
        return Number::New(PROCESS_FAIL);
    }
    int targ=0;
    string val;

    int status = GetArgumentStringValue ( args, targ++, val);

    string out = execute_hello(val);

    return String::New(out.c_str());
}



MyObject::MyObject() {};
MyObject::~MyObject() {};

void MyObject::Init(Handle<Object> exports) {
    // Prepare constructor template
    Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
    tpl->SetClassName(String::NewSymbol("MyObject"));
    tpl->InstanceTemplate()->SetInternalFieldCount(1);
    // Prototype
    tpl->PrototypeTemplate()->Set(String::NewSymbol("plusOne"),
      FunctionTemplate::New(PlusOne)->GetFunction());

    Persistent<Function> constructor = Persistent<Function>::New(tpl->GetFunction());
    exports->Set(String::NewSymbol("MyObject"), constructor);
}

Handle<Value> MyObject::New(const Arguments& args) {
    HandleScope scope;

    MyObject* obj = new MyObject();
    obj->counter_ = args[0]->IsUndefined() ? 0 : args[0]->NumberValue();
    obj->Wrap(args.This());

    return args.This();
}

Handle<Value> MyObject::PlusOne(const Arguments& args) {
    HandleScope scope;

    MyObject* obj = ObjectWrap::Unwrap<MyObject>(args.This());
    obj->counter_ += 1;

    return scope.Close(Number::New(obj->counter_));
}



#ifdef _MODULE_NAME_NODE_MODULE

extern "C" {
  static void init(Handle<Object> exports)
  {
      HandleScope scope;
      cout << "_MODULE_NAME_NODE_MODULE is defined " << endl;
      
      // functions
      NODE_SET_METHOD(exports, "hello", hello);

      // classes
      MyObject::Init(exports);
  }

  NODE_MODULE(moduleName, init)
}

#endif
