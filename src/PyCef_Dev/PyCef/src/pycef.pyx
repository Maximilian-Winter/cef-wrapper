# distutils: language=c++
# cython: language_level=3
from PyCef.src.header.cefsimplewrapper cimport CefWrapper

cdef inline void callback( void *f):
    (<object>f)()

cdef class PyCef:
    cdef CefWrapper cef_simple_wrapper;

    def __init__(self):
        self.cef_simple_wrapper = CefWrapper()

    def init_cef(self, start_url: str):
        self.cef_simple_wrapper.InitCefSimple(start_url.encode("utf-8"))

    def execute_javascript(self, code: str):
        self.cef_simple_wrapper.ExecuteJavascript(code.encode("utf-8"))

   #def add_native_api_function(self, name, func: js_binding_function_ptr):
   #   self.cef_simple_wrapper.AddJavascriptBinding(name, func)

    def add_javascript_python_binding(self, name: str, func):
       self.cef_simple_wrapper.AddJavascriptPythonBinding(name.encode("utf-8"), callback,<void *>func)

    def shutdown_cef(self):
        self.cef_simple_wrapper.ShutdownCefSimple()

    def is_running(self):
        return self.cef_simple_wrapper.IsRunning()

    def do_cef_message_loop_work(self):
        return self.cef_simple_wrapper.DoCefMessageLoopWork()

    def set_cefsub_path(self, path: str):
        self.cef_simple_wrapper.SetCustomCefSubprocessPath(path.encode("utf-8"))

    def set_cef_cache_path(self, path: str):
        self.cef_simple_wrapper.SetCustomCefCachePath(path.encode("utf-8"))

    def load_url(self, url: str):
        self.cef_simple_wrapper.LoadUrl(url.encode("utf-8"))