import time
from datetime import datetime

from PyCef import PyCef, py_cef_cefsubprocess_path


# This function is the endpoint of a javascript binding, and it's get called on the test website.
def my_js_binding(args):
    print("This function is called from Javascript!")
    print(args)


pycef = PyCef()
pycef.set_cefsub_path(py_cef_cefsubprocess_path)
pycef.add_javascript_python_binding("testfunc", my_js_binding)
pycef.init_cef("C:\\ZenDraft\\ZenDraft\\build\\index.html")
counter = 0

while pycef.is_running():
    time.sleep(0.01)
    pycef.do_cef_message_loop_work()
    now = datetime.now()  # current date and time
    date_time = now.strftime("%d.%m.%Y, %H:%M:%S")
    code = f"window.state.setTicker('{date_time}')"
    pycef.execute_javascript(code)
    counter += 1

