#include "library.h"

#include "global_vars.h"
#include "javascript_binding.h"
#include <filesystem>
#include <iostream>
#undef CEF_USE_SANDBOX


std::string ExePath() {
  std::filesystem::path cwd = std::filesystem::current_path() / "cefsubprocess" / "cefsubprocess.exe";   //"C:\\Dev\\cef-binaries\\cef_binary_106.0.27+g20ed841+chromium-106.0.5249.103_windows64\\cmake-build-debug-visual-studio\\src\\cefsubprocess\\Debug\\cefsubprocess.exe";
  return cwd.string();
}

std::string CachePath() {
  std::filesystem::path cwd = std::filesystem::current_path() / "cache";   //"C:\\Dev\\cef-binaries\\cef_binary_106.0.27+g20ed841+chromium-106.0.5249.103_windows64\\cmake-build-debug-visual-studio\\src\\cefsubprocess\\Debug\\cefsubprocess.exe";
  return cwd.string();
}

void CefWrapper::InitCefSimple(std::string start_url) {
  CefEnableHighDPISupport();

  void *sandbox_info = nullptr;

  CefMainArgs main_args;

  m_App = CefRefPtr<CefWrapperApp>(new CefWrapperApp( start_url, m_Callbacks, m_NativePythonApi));
  CefExecuteProcess(main_args, m_App.get(), sandbox_info);

  CefRefPtr<CefCommandLine> command_line = CefCommandLine::CreateCommandLine();
  command_line->InitFromString(::GetCommandLineW());

  CefSettings settings;

  if(m_UseCustomCefCachePath)
  {
    CefString(&settings.cache_path) = m_CustomCefCachePath;
    CefString(&settings.root_cache_path) = m_CustomCefCachePath;
  }
  else
  {
    CefString(&settings.cache_path) = CachePath();
    CefString(&settings.root_cache_path) = CachePath();
  }

  // settings.multi_threaded_message_loop = true;
  settings.no_sandbox = true;

  if(m_UseCustomCefSubPath)
  {
    CefString(&settings.browser_subprocess_path).FromASCII(m_CustomCefSubPath.c_str());
  }
  else
  {
    CefString(&settings.browser_subprocess_path).FromASCII(ExePath().c_str());
  }

  CefInitialize(main_args, settings, m_App.get(), sandbox_info);
  g_IsRunning = true;
}
void CefWrapper::ExecuteJavascript(std::string code) {
  CefRefPtr<CefFrame> frame = m_App->GetBrowser()->GetMainFrame();
  if (g_IsRunning) {
    if (CefWrapperClientHandler::GetInstance()->IsReadyToExecuteJs()) {
      frame->ExecuteJavaScript(code, frame->GetURL(), 0);
    }
  }
}
void CefWrapper::ShutdownCefSimple() { CefShutdown(); }

bool CefWrapper::IsRunning() { return g_IsRunning; }

void CefWrapper::DoCefMessageLoopWork() { CefDoMessageLoopWork(); }
bool CefWrapper::IsReadyToExecuteJavascript() {
  return CefWrapperClientHandler::GetInstance()->IsReadyToExecuteJs();
}

void CefWrapper::AddJavascriptBinding(std::string name, js_binding_function_ptr jsNativeApiFunctionPtr)
{
  m_Callbacks.push_back(JavascriptBinding(name, jsNativeApiFunctionPtr));
}
CefWrapper::CefWrapper() {}
void CefWrapper::AddJavascriptPythonBinding(
    std::string name,
    js_python_bindings_handler_function_ptr python_bindings_handler,
    js_python_callback_object_ptr python_callback_object) {
  m_NativePythonApi.push_back(
      JavascriptPythonBinding(python_bindings_handler, name, python_callback_object));
}
void CefWrapper::SetCustomCefSubprocessPath(std::string cefsub_path) {
  m_UseCustomCefSubPath = true;
  m_CustomCefSubPath = cefsub_path;
}
void CefWrapper::SetCustomCefCachePath(std::string cef_cache_path) {
  m_UseCustomCefCachePath = true;
  m_CustomCefCachePath = cef_cache_path;
}
void CefWrapper::LoadUrl(std::string url) {
 m_App->LoadUrl(url);
}
