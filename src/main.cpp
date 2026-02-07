#include "core/Display.h"
#include "core/Logger.h"

int main()
{
  Display display("Survival Shooter", 1280, 720);
  display.SetVsync(true);

  // Main Game Loop
  while(display.IsRunning())
  {
    display.Update();

    display.SwapBuffers();
  }
}
