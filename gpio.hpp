#pragma once

/* Inkluderingsdirektiv: */
#include <iostream>
#include <string>
#include "file.hpp"

#ifdef __cplusplus
extern "C" {
#endif /* cplusplus*/
#include <stdio.h>
#include <stdlib.h>
   typedef enum { FALSE, TRUE } bool_t;
#ifdef __cplusplus
}
#endif /* cplusplus */

namespace gpio {
   /* Enumerationsklasser: */
   struct enums {
      enum class direction { input, output };
      enum class value { low, high };
   };

   /* Inkapslade funktioner: */
   namespace {
      /***************************************************************************************
      * Reserverar PIN för aktuell process.
      ***************************************************************************************/
      static void export_pin(const std::uint8_t* pin) {
         const char* filepath = "/sys/class/gpio/export";
         for (auto* i = filepath; *i; i++)
         {
            file::file::file::write<const char*, std::uint8_t>(&i, pin);
         }
         return;
      }

      /***************************************************************************************
      * Tar bort reservation av PIN så att denna kan användas i framtida processer.
      ***************************************************************************************/
      static void unexport_pin(const std::uint8_t* pin)
      {
         const char* filepath = "/sys/class/gpio/unexport";
         for (auto* i = filepath; *i; i++)
         {
            file::file::file::write<const char*, std::uint8_t>(&i, pin);
         }
         return;
      }

      /***************************************************************************************
      * Ställer in datariktning på aktuell PIN.
      ***************************************************************************************/
      static void set_direction(const std::uint8_t* pin, const enums::direction* direction)
      {
         const std::string filepath = "/sys/class/gpio/gpio" + std::to_string(*pin) + "direction";
         std::string s;
         if (*direction == enums::direction::output) { s = "out"; }
         else { s = "in"; }
         file::file::file::write<std::string, std::string>(&filepath, &s);
         return;
      }
   }

   /***************************************************************************************
   * GPIO-klass för enkel implementering av en given PIN.
   ***************************************************************************************/
   class gpio : public file::file::file
   {
   public:
      /***************************************************************************************
      * Sätter ny utsignal till utport.
      ***************************************************************************************/
      static void write(const std::uint8_t& pin, const enums::value& value) {
         const std::string filepath = "/sys/class/gpio" + std::to_string(pin) + "value";
         try {
            const std::size_t cast_value = static_cast<std::size_t>(value);
            for (auto i : filepath)
            {
               file::write<const std::string, const std::size_t>(&filepath, &cast_value);
            }
         }
         catch (std::invalid_argument&) {
            std::string s;
            if (value == enums::value::high) {
               const char c = '1';
               file::write<std::string, const char>(&filepath, &c);
            }
            else {
               const char c = '0';
               file::write<std::string, const char>(&filepath, &c);
            }
         } return;
      }

      /***************************************************************************************
      * Läser aktuell insignal från in- eller utport.
      ***************************************************************************************/
      static enums::value read(const std::uint8_t& pin) {
         const std::string filepath = "/sys/class/gpio" + std::to_string(pin) + "value";
         std::string value; file::read<std::string>(&filepath, &value);
         if (value == "1") { return enums::value::high; }
         else { return enums::value::low; }
      }

      /***************************************************************************************
      * Initierar PIN genom att reservera denna samt välja datariktning.
      ***************************************************************************************/
      static void setup(const std::uint8_t& pin, const enums::direction& direction) {
         export_pin(&pin);
         set_direction(&pin, &direction);
         return;
      }
   };
}

