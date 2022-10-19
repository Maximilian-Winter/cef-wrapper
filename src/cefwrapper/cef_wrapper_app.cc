



#include "cef_wrapper_app.h"

#include "include/cef_browser.h"
#include "include/cef_command_line.h"

#include "javascript_binding.h"
#include "javascript_bindings_handler.h"

CefRefPtr<CefBrowser> CefWrapperApp::GetBrowser()
{
    return CefWrapperBrowserProcessHandler::GetInstance()->Browser;
}

void CefWrapperApp::OnBeforeCommandLineProcessing(
    const CefString &process_type, CefRefPtr<CefCommandLine> command_line) {
  CefApp::OnBeforeCommandLineProcessing(process_type, command_line);
}

CefWrapperApp::CefWrapperApp(std::string start_url, std::vector<JavascriptBinding> javascript_bindings, std::vector<JavascriptPythonBinding> javascript_python_bindings) {
  m_Javascript_Bindings = javascript_bindings;
  m_Javascript_Python_Bindings = javascript_python_bindings;
  CefWrapperBrowserProcessHandler::SetJavascriptBindings(
      m_Javascript_Bindings, m_Javascript_Python_Bindings);
  CefWrapperBrowserProcessHandler::SetStartUrl(start_url);
}

void CefWrapperApp::LoadUrl(std::string url) {
  CefWrapperBrowserProcessHandler::LoadUrl(url);
}
