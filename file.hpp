#pragma once

/* Inkluderingsdirektiv: */
#include <iostream>
#include <string>
#include <fstream>

#ifndef __cplusplus
extern "C++" {
#endif /* cplusplus */

   namespace file {
      namespace file {
         /***************************************************************************************
         * Strukt f�r enkel filhantering med valbara parametrar.
         ***************************************************************************************/
         struct file {
            /***************************************************************************************
            * Skriver nytt inneh�ll till en fil.
            ***************************************************************************************/
            template<class X, class Y> static void write(const X* filepath, const Y* data) {
               std::ofstream fstream(static_cast<const std::string>(*filepath), std::ios::app);
               if (!fstream) {
                  std::cout << "Could not open path " << *filepath << " for writing!\n\n";
                  return;
               } fstream << *data; return;
            }

            /***************************************************************************************
            * L�ser in en rad fr�n en given fil, vilket returneras via en str�ngpekare.
            ***************************************************************************************/
            template<class T> static void read(const T* filepath, std::string* data) {
               std::ifstream fstream(static_cast<const std::string>(*filepath), std::ios::in);
               if (!fstream) {
                  std::cout << "Could not open path " << *filepath << " for reading!\n\n";
                  return;
               } std::getline(fstream, *data); return;
            }
         };
      }
   }

#ifndef __cplusplus
}
#endif /* cplucplus */

