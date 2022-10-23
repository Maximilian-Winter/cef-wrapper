//
// Created by maxim on 11.10.2022.
//

#include "../cefwrapper/library.h"
#include <iostream>



void testfunc(void* data, int size, CefValueWrapper* args)
{
  std::cout << "I FOUGHT THE LAW AND I WON!"<< size << std::endl;
}

int main()
{
  CefWrapper cefSimpleWrapper;
  cefSimpleWrapper.AddJavascriptPythonBinding("testfunc", testfunc, nullptr);
  cefSimpleWrapper.InitCefSimple("C:\\ZenDraft\\ZenDraft\\build\\index.html");

  long long counter = 0;
  while (cefSimpleWrapper.IsRunning())
  {
	  Sleep(10);
	  cefSimpleWrapper.DoCefMessageLoopWork();
          std::stringstream ss;
          ss << "window.state.setTicker(" << counter++ << ")";
          cefSimpleWrapper.ExecuteJavascript(ss.str());
  }

  //cefSimpleWrapper.ShutdownCefSimple();
  return 0;
}


