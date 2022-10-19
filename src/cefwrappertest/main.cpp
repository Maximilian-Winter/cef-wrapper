//
// Created by maxim on 11.10.2022.
//

#include "../cefwrapper/library.h"
#include <iostream>

bool can_run_javascript = false;

void testfunc(void* data)
{
  can_run_javascript = true;
  std::cout << "I FOUGHT THE LAW AND I WON!" << std::endl;
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
          if(can_run_javascript)
          {
            std::stringstream ss;
            ss << "window.state.setTicker(" << counter++ << ")";
            cefSimpleWrapper.ExecuteJavascript(ss.str());
          }
  }

  //cefSimpleWrapper.ShutdownCefSimple();
  return 0;
}


