/* Inkluderingsdirektiv: */
#include "gpio.hpp"

extern "C++" {
   /********************************************************************************************
   * I följande program ansluts en lysdiod till PIN 17 och en tryckknapp till PIN 27.
   * Vid nedtryckning av tryckknappen skall lysdioden tändas, annars skall den hållas släckt.
   ********************************************************************************************/
int main(void) {
      std::cout << "Please clean up this mess!\n\n";
      gpio::gpio::setup(17, gpio::enums::direction::output);
      gpio::gpio::setup(27, gpio::enums::direction::input);
      while (!FALSE) { gpio::gpio::write(17, gpio::gpio::read(27)); }
      return 0;
   } }

