#include <string>
#include <vector>

#ifndef MODULE_NAME_H
#define MODULE_NAME_H

#define PROCESS_OK   0
#define PROCESS_FAIL 1

using namespace std;

string execute_hello( const string &val ) {
    return string("Hello node, coffeescript and c++ ") + val;
}

class MyObject : public node::ObjectWrap {
 	public:
 		static void Init(v8::Handle<v8::Object> exports);

 	protected:
  		MyObject();
  		~MyObject();

  		static v8::Handle<v8::Value> New(const v8::Arguments& args);
  		static v8::Handle<v8::Value> PlusOne(const v8::Arguments& args);
  		double counter_;
};


#endif 