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

#ifndef CMDWORKED_H
#define CMDWORKED_H

//Abstract Base Class
class cmdWorked
{ 
   protected:
      bool worked; //Bool to determine if the command ran properly
   
   public:
      virtual void execute(char **) = 0; //virtual function to execute a process
};

#endif
