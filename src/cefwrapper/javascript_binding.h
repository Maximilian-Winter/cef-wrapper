#ifndef JAVASCRIPT_BINDING_H
#define JAVASCRIPT_BINDING_H

#include "include/cef_client.h"
#include "include/cef_render_process_handler.h"
#include "include/wrapper/cef_helpers.h"
#include <list>

class CefValueWrapper
{
public:
  CefValueWrapper(){}

  bool IsInt()
  {
    return Type == 0;
  }
  bool IsBool()
  {
    return Type == 1;
  }
  bool IsDouble()
  {
    return Type == 2;
  }
  bool IsString()
  {
    return Type == 3;
  }

  int GetInt()
  {
    return IntValue;
  }
  bool GetBool()
  {
    return BoolValue;
  }
  double GetDouble()
  {
    return DoubleValue;
  }
  std::string GetString()
  {
    return StringValue;
  }
  int Type;
  int IntValue;
  bool BoolValue;
  double DoubleValue;
  std::string StringValue;
};
typedef void (*js_python_callback_object_ptr);
typedef void (*js_python_bindings_handler_function_ptr)(void* python_callback_object, int argsSize, CefValueWrapper* callback_args );
typedef void (*js_binding_function_ptr)();

class JavascriptPythonBinding {
public:
  js_python_bindings_handler_function_ptr HandlerFunction;
  std::string MessageTopic;
  js_python_callback_object_ptr PythonCallbackObject;


  JavascriptPythonBinding(){}

  JavascriptPythonBinding(void (*handlerFunction)(void *, int, CefValueWrapper*),
                    const std::string &messageTopic,
                    void *pythonCallbackObject)
      : HandlerFunction(handlerFunction), MessageTopic(messageTopic),
        PythonCallbackObject(pythonCallbackObject) {}

  void CallHandler(int argsSize, CefValueWrapper* args) const
  {
    HandlerFunction(PythonCallbackObject, argsSize, args);
  }
};


class JavascriptBinding {
public:
  JavascriptBinding() {}
  JavascriptBinding(std::string name, js_binding_function_ptr pFunction) {
    functionName = name;
    function = pFunction;
  }
  std::string functionName;
  js_binding_function_ptr function;
};
#endif // JAVASCRIPT_BINDING_H
