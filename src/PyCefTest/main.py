import time
from PyCef import PyCef, py_cef_cefsubprocess_path


# This function is the endpoint of a javascript binding, and it's get called on the test website.
def my_js_binding():
    global can_find_ticker
    can_find_ticker = True
    print("This function is called from Javascript!")


pycef = PyCef()
pycef.set_cefsub_path(py_cef_cefsubprocess_path)
pycef.add_javascript_python_binding("testfunc", my_js_binding)
pycef.init_cef("C:\\ZenDraft\\ZenDraft\\build\\index.html")
can_find_ticker = False
counter = 0

while pycef.is_running():
    time.sleep(0.01)
    pycef.do_cef_message_loop_work()
    if can_find_ticker:
        code = f"window.state.setTicker({counter})"
        pycef.execute_javascript(code)
        counter += 1
