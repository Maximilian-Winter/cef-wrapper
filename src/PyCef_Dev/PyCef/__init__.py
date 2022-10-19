import os
py_cef_path = os.path.abspath(__file__)
py_cef_path = os.path.dirname(py_cef_path)
py_cef_cefsubprocess_path = f'{py_cef_path}\\cefsubprocess\\cefsubprocess.exe'
os.add_dll_directory(f'{py_cef_path}\\bin')
from .src import PyCef
