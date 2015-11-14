// <This program essetially mocks a common shell terminal.>
// Copyright (C) <2015>  <Queston Juarez & Mark Spencer>

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>

#ifndef CONNECTERS_H
#define CONNECTERS_H

#include "cmdWorked.h"
#include <string>

using namespace std;

//Class that holds connectors to determine if next command should run
class connecters: public cmdWorked
{
   protected:
      bool runNext; //Holds value to determine fi next value runs or not

   public:
 
      void execute(char**) //Doesn't do anything yet but needs to be here
      {};

      virtual bool compare (bool cmdRan) = 0; //virtual function for AND and OR
};

//The OR class runs next command only if the first one failed
class OR: connecters
{
   public:
      
      //Constructor sets worked to false
      OR()
      {
         worked = false;
      };

      //THe compare function determines if the first cmd falied or not then
      //returns the proper value depending on the first command
      bool compare (bool cmdRan)
      {
         if (cmdRan == this->worked)
           this->runNext = true;
         else
           this->runNext = false;
         return runNext;
      };
};

//The AND class runs the next command only if the first one succeeded
class AND: connecters
{
   public:

      //Constructor sets worked to true
      AND()
      {
         worked = true;
      };

      //Determines if the next cmd should run based on the result of the first cmd
      bool compare (bool cmdRan)
      {
         if (cmdRan == this->worked)
            this->runNext = true;
         else
            this->runNext = false;
         return runNext;
      };
};

#endif
