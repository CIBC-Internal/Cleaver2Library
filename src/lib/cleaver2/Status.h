#ifndef __STATUS_H__
#define __STATUS_H__

//@author Brig Bagley
//@date 14 Jan 2015
//@descrip This file is a simple "print progress" for verbose status of a process's progress.
//
#include <stdio.h>
#include <stdlib.h>

class Status {
  public:
    explicit Status(int tot, bool verbose) : total_(double(tot)), count_(0), percent_(-1), verbose_(verbose)
    {}
    void printStatus()
    {
      double pcnt = double(count_) / total_;
      int val = int(std::min(1.,std::max(0.,pcnt))*100.+0.5);
      if (val != percent_)
      {
        percent_ = val;
        if (verbose_)
        {
          printf("\r|");
          for(int i = 0; i < 50; i++)
            if(i < val/2) printf("-");
            else printf(" ");
          printf("| %d%%",val);
          fflush(stdout);
        }
      }
      count_++;
    }
    void done()
    {
      if (verbose_)
        printf("\n"); 
      percent_ = 0;
      count_ = 0;
    }
  private:
    double total_;
    int count_;
    int percent_;
    bool verbose_;
};
#endif
