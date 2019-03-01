#ifndef SOURCE_PREDICTION_H
#define SOURCE_PREDICTION_H

class CPrediction
{
    virtual ~CPrediction() {}
    virtual void Init(void) = 0;
    virtual void Shutdown(void) = 0;
    virtual void Update(int,bool,int,int) = 0;
};

#endif
