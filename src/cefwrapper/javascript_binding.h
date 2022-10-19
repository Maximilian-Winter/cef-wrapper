#ifndef JAVASCRIPT_BINDING_H
#define JAVASCRIPT_BINDING_H

#include "include/cef_client.h"
#include "include/cef_render_process_handler.h"
#include "include/wrapper/cef_helpers.h"
#include <list>
typedef void (*js_python_callback_object_ptr);
typedef void (*js_python_bindings_handler_function_ptr)(void* python_callback_object );
typedef void (*js_binding_function_ptr)();


class JavascriptPythonBinding {
public:
  js_python_bindings_handler_function_ptr HandlerFunction;
  std::string MessageTopic;
  js_python_callback_object_ptr PythonCallbackObject;

  JavascriptPythonBinding(){}

  JavascriptPythonBinding(void (*handlerFunction)(void *),
                    const std::string &messageTopic,
                    void *pythonCallbackObject)
      : HandlerFunction(handlerFunction), MessageTopic(messageTopic),
        PythonCallbackObject(pythonCallbackObject) {}

  void CallHandler()
  {
    HandlerFunction(PythonCallbackObject);
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
