#include "cef_wrapper_render_process_handler.h"

#include "include/cef_render_process_handler.h"
#include "include/internal/cef_ptr.h"
#include "javascript_binding.h"
#include "javascript_bindings_handler.h"
#include "javascript_python_binding_handler.h"

void SimpleRenderProcessHandler::OnBrowserCreated(
    CefRefPtr<CefBrowser> browser, CefRefPtr<CefDictionaryValue> extra_info) {
    CEF_REQUIRE_RENDERER_THREAD();


    if (extra_info->HasKey("JSCallbacks"))
    {
        CefRefPtr<CefBinaryValue>callbackList = extra_info->GetBinary("JSCallbacks");
        JavascriptBinding callbacks[100];
        m_Javascript_Bindings = std::vector<JavascriptBinding>();
        callbackList->GetData(&callbacks[0], (sizeof(JavascriptBinding) * 100), 0);
        int size = extra_info->GetInt("JSCallbacksSize");
        for (int i = 0; i < size; ++i) {
          m_Javascript_Bindings.push_back(callbacks[i]);
        }
    }

    if (extra_info->HasKey("JSNativePythonApi"))
    {
      CefRefPtr<CefBinaryValue>callbackList = extra_info->GetBinary("JSNativePythonApi");
      JavascriptPythonBinding callbacks[100];
      m_Javascript_Python_Bindings = std::vector<JavascriptPythonBinding>();
      callbackList->GetData(&callbacks[0], (sizeof(JavascriptPythonBinding) * 100), 0);
      int size = extra_info->GetInt("JSNativePythonApiSize");
      for (int i = 0; i < size; ++i) {
        m_Javascript_Python_Bindings.push_back(callbacks[i]);
      }
    }
}
/* Null, because instance will be initialized on demand. */
CefRefPtr<SimpleRenderProcessHandler> SimpleRenderProcessHandler::instance = nullptr;

CefRefPtr<SimpleRenderProcessHandler> SimpleRenderProcessHandler::getInstance()
{
    if (instance == nullptr)
    {
        instance = CefRefPtr<SimpleRenderProcessHandler>(new SimpleRenderProcessHandler());
    }

    return instance;
}

void SimpleRenderProcessHandler::SetJavascriptBindings(std::vector<JavascriptBinding> javascript_bindings, std::vector<JavascriptPythonBinding> javascript_python_bindings)
{
    getInstance()->m_Javascript_Bindings = javascript_bindings;
    getInstance()->m_Javascript_Python_Bindings = javascript_python_bindings;
}

SimpleRenderProcessHandler::SimpleRenderProcessHandler()
= default;

void SimpleRenderProcessHandler::OnContextCreated(
    CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame,
    CefRefPtr<CefV8Context> context) {
    //CEF_REQUIRE_RENDERER_THREAD();

    if (!m_Javascript_Bindings.empty())
    {
        // Retrieve the context's window object.
        CefRefPtr<CefV8Value> object = context->GetGlobal();
        CefRefPtr<CefV8Handler> handler = new JavascriptBindingsHandler(m_Javascript_Bindings, browser);
        for (int i = 0; i < m_Javascript_Bindings.size(); ++i)
        {
            CefRefPtr<CefV8Value> func = CefV8Value::CreateFunction(
              m_Javascript_Bindings[i].functionName, handler);
            object->SetValue(m_Javascript_Bindings[i].functionName, func, V8_PROPERTY_ATTRIBUTE_NONE);
        }
    }

    if (!m_Javascript_Python_Bindings.empty())
    {
      // Retrieve the context's window object.
      CefRefPtr<CefV8Value> object = context->GetGlobal();
      CefRefPtr<CefV8Handler> handler = new JavascriptPythonBindingsHandler(
          m_Javascript_Python_Bindings, browser);
      for (int i = 0; i < m_Javascript_Python_Bindings.size(); ++i)
      {
        CefRefPtr<CefV8Value> func = CefV8Value::CreateFunction(
            m_Javascript_Python_Bindings[i].MessageTopic, handler);
        object->SetValue(m_Javascript_Python_Bindings[i].MessageTopic, func, V8_PROPERTY_ATTRIBUTE_NONE);
      }
    }
}


