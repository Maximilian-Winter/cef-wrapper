# distutils: language=c++
# cython: language_level=3
from PyCef.src.header.cefsimplewrapper cimport CefWrapper, CefValueWrapper

#from .header.cefsimplewrapper cimport CefWrapper, CefValueWrapper

cdef class PyCefValueWrapper:
    cdef CefValueWrapper cef_value_wrapper;

    def __init__(self):
        self.cef_value_wrapper = CefValueWrapper()

    def is_int(self):
        return self.cef_value_wrapper.IsInt()

    def is_bool(self):
        return self.cef_value_wrapper.IsBool()

    def is_double(self):
        return self.cef_value_wrapper.IsDouble()

    def is_string(self):
        return self.cef_value_wrapper.IsString()

    def get_int(self):
        return self.cef_value_wrapper.GetInt()

    def get_bool(self):
        return self.cef_value_wrapper.GetBool()

    def get_double(self):
        return self.cef_value_wrapper.GetDouble()

    def get_string(self):
        return self.cef_value_wrapper.GetString()


cdef inline void callback( void *f, int size, CefValueWrapper* args):
    cdef CefValueWrapper* fargs = args
    arg_list = []
    cdef PyCefValueWrapper v2
    for i in range(size):
        v2 = PyCefValueWrapper()
        v2.cef_value_wrapper = fargs[0]
        if v2.is_int():
            arg_list.append(v2.get_int())
        if v2.is_bool():
            arg_list.append(v2.get_bool())
        if v2.is_string():
            arg_list.append(bytes.decode(v2.get_string(), "utf-8"))
        if v2.is_double():
            arg_list.append(v2.get_double())
        fargs += 1

    (<object>f)(arg_list)

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

