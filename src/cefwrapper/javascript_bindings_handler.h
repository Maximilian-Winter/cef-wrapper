#ifndef JAVASCRIPT_BINDINGS_HANDLER_H
#define JAVASCRIPT_BINDINGS_HANDLER_H

#include "include/cef_client.h"

#include <list>

#include "include/cef_render_process_handler.h"
#include "include/wrapper/cef_helpers.h"
#include "javascript_binding.h"

class JavascriptBindingsHandler : public CefV8Handler {

public:
  JavascriptBindingsHandler(std::vector<JavascriptBinding> callbacks, CefRefPtr<CefBrowser> browser) {
    JsCallbacks = callbacks;
    m_Browser = browser;
  };
  virtual bool Execute(const CefString &name, CefRefPtr<CefV8Value> object,
                       const CefV8ValueList &arguments,
                       CefRefPtr<CefV8Value> &retval,
                       CefString &exception) override {

    for (int i = 0; i < JsCallbacks.size(); ++i) {
      if (name == JsCallbacks[i].functionName) {
        // Create the message object.
        CefRefPtr<CefProcessMessage> msg =
            CefProcessMessage::Create("call-api-no-args");

        // Retrieve the argument list object.
        CefRefPtr<CefListValue> args = msg->GetArgumentList();

        // Populate the argument values.
        args->SetString(0, JsCallbacks[i].functionName);
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
  std::vector<JavascriptBinding> JsCallbacks;
  // Provide the reference counting implementation for this class.
  IMPLEMENT_REFCOUNTING(JavascriptBindingsHandler);
};
#endif // JAVASCRIPT_BINDINGS_HANDLER_H
