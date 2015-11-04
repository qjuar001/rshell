#ifndef CMDWORKED_H
#define CMDWORKED_H

class cmdWorked
{
   protected:
      bool worked;
   
   public:
      virtual void execute(char **) = 0;
};

#endif
