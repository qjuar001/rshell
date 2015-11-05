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
