#ifndef LIBRARY_LIBRARY_H
#define LIBRARY_LIBRARY_H

#include <Windows.h>

#include "cef_wrapper_app.h"
#include "cef_wrapper_client_handler.h"
#include "include/cef_command_line.h"
#include "include/cef_sandbox_win.h"
#include "javascript_binding.h"

class CefWrapper {
public:
  CefWrapper();
  void InitCefSimple(std::string start_url);
  void ExecuteJavascript(std::string code);
  void ShutdownCefSimple();
  bool IsRunning();
  bool IsReadyToExecuteJavascript();
  void DoCefMessageLoopWork();
  void AddJavascriptBinding(std::string name,
                                js_binding_function_ptr jsNativeApiFunctionPtr);
  void AddJavascriptPythonBinding(std::string name,
      js_python_bindings_handler_function_ptr python_bindings_handler,
      js_python_callback_object_ptr python_callback_object);
  void SetCustomCefSubprocessPath(std::string cefsub_path);
  void SetCustomCefCachePath(std::string cef_cache_path);
  void LoadUrl(std::string url);

private:
    CefRefPtr<CefWrapperApp> m_App;

    bool m_UseCustomCefSubPath = false;
    std::string m_CustomCefSubPath = "";

    bool m_UseCustomCefCachePath = false;
    std::string m_CustomCefCachePath = "";

    std::vector<JavascriptBinding>m_Callbacks;
    std::vector<JavascriptPythonBinding> m_NativePythonApi;
}
;

#endif//LIBRARY_LIBRARY_H
