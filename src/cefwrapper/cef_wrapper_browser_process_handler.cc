


#include "cef_wrapper_browser_process_handler.h"
#include "cef_wrapper_client_handler.h"
#include "cef_wrapper_render_process_handler.h"
#include "javascript_binding.h"

CefWrapperBrowserProcessHandler::CefWrapperBrowserProcessHandler() = default;

/* Null, because instance will be initialized on demand. */
CefRefPtr<CefWrapperBrowserProcessHandler>
    CefWrapperBrowserProcessHandler::instance = nullptr;

CefRefPtr<CefWrapperBrowserProcessHandler>
CefWrapperBrowserProcessHandler::GetInstance()
{
  if (instance == nullptr)
  {
    instance = CefRefPtr<CefWrapperBrowserProcessHandler>(new CefWrapperBrowserProcessHandler());
  }

  return instance;
}
void CefWrapperBrowserProcessHandler::SetJavascriptBindings(std::vector<JavascriptBinding> javascript_bindings, std::vector<JavascriptPythonBinding> javascript_python_bindings)
{
  GetInstance()->m_JavascriptBindings = javascript_bindings;
  GetInstance()->m_JavascriptPythonBindings = javascript_python_bindings;
}

CefRefPtr<CefClient> CefWrapperBrowserProcessHandler::GetDefaultClient()
{
  return CefWrapperClientHandler::GetInstance();
}

void CefWrapperBrowserProcessHandler::OnContextInitialized()
{
  CEF_REQUIRE_UI_THREAD();

  CefRefPtr<CefCommandLine> command_line =
      CefCommandLine::GetGlobalCommandLine();

  bool use_views = command_line->HasSwitch("use-views");

  CefRefPtr<CefWrapperClientHandler> handler(new CefWrapperClientHandler(use_views, m_JavascriptBindings, m_JavascriptPythonBindings));
  SimpleRenderProcessHandler::getInstance()->SetJavascriptBindings(
      m_JavascriptBindings, m_JavascriptPythonBindings);

  CefBrowserSettings browser_settings;

  std::string url;
  url = StartUrl;

  CefWindowInfo window_info;

#if defined(OS_WIN)
  // On Windows we need to specify certain flags that will be passed to
  // CreateWindowEx().
  window_info.SetAsPopup(nullptr, "cefsimple");
#endif

  CefRefPtr<CefDictionaryValue> extra = CefDictionaryValue::Create();
  if(!m_JavascriptBindings.empty())
  {

    CefRefPtr<CefBinaryValue> val = CefBinaryValue::Create(static_cast<void*>(m_JavascriptBindings.data()),  (sizeof(JavascriptBinding) * m_JavascriptBindings.size())
    );
    extra->SetBinary("JSCallbacks", val);
    extra->SetInt("JSCallbacksSize", (int)m_JavascriptBindings.size());
  }

  if(!m_JavascriptPythonBindings.empty())
  {

    CefRefPtr<CefBinaryValue> val = CefBinaryValue::Create(static_cast<void*>(m_JavascriptPythonBindings.data()),  (sizeof(JavascriptPythonBinding) * m_JavascriptPythonBindings.size())
    );
    extra->SetBinary("JSNativePythonApi", val);
    extra->SetInt("JSNativePythonApiSize", (int)m_JavascriptPythonBindings.size());
  }

  Browser = CefBrowserHost::CreateBrowserSync(window_info, handler, url, browser_settings,
                                                extra, nullptr);

  // m_Browser->GetHost()->ShowDevTools(window_info, nullptr, browser_settings, CefPoint());
}
void CefWrapperBrowserProcessHandler::SetStartUrl(std::string url) {
  CefWrapperBrowserProcessHandler::GetInstance()->StartUrl = url;
}
void CefWrapperBrowserProcessHandler::LoadUrl(std::string url) {
  CefWrapperBrowserProcessHandler::GetInstance()->Browser->GetMainFrame()->LoadURL(url);
}
