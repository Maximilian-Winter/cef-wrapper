#ifndef JAVASCRIPT_PYTHON_BINDING_HANDLER_H
#define JAVASCRIPT_PYTHON_BINDING_HANDLER_H

#include "include/cef_client.h"

#include <list>

#include "include/cef_render_process_handler.h"
#include "include/wrapper/cef_helpers.h"
#include "javascript_binding.h"

class JavascriptPythonBindingsHandler : public CefV8Handler {

public:
  JavascriptPythonBindingsHandler(std::vector<JavascriptPythonBinding> pythonBindings,
                 CefRefPtr<CefBrowser> browser) {
    m_Browser = browser;
    m_PythonBindings = pythonBindings;
  };
  virtual bool Execute(const CefString &name, CefRefPtr<CefV8Value> object,
                       const CefV8ValueList &arguments,
                       CefRefPtr<CefV8Value> &retval,
                       CefString &exception) override {

    for (int i = 0; i < m_PythonBindings.size(); ++i) {
      if (name == m_PythonBindings[i].MessageTopic) {
        // Create the message object.
        CefRefPtr<CefProcessMessage> msg =
            CefProcessMessage::Create("call-python-api-no-args");

        // Retrieve the argument list object.
        CefRefPtr<CefListValue> args = msg->GetArgumentList();

        // Populate the argument values.
        args->SetString(0, m_PythonBindings[i].MessageTopic);
        // Send the process message to the main frame in the render process.
        // Use PID_BROWSER instead when sending a message to the m_Browser
        // process.
        m_Browser->GetMainFrame()->SendProcessMessage(PID_BROWSER, msg);
        return true;
      }
    }
    // Function does not exist.
    return false;
  }
  CefRefPtr<CefBrowser> m_Browser;
  std::vector<JavascriptPythonBinding> m_PythonBindings;
  // Provide the reference counting implementation for this class.
  IMPLEMENT_REFCOUNTING(JavascriptPythonBindingsHandler);
};
#endif // JAVASCRIPT_PYTHON_BINDING_HANDLER_H
