#ifndef TEMP_H
#define TEMP_H


class temp :  public readwritearduino, public sensor
{
public:
    temp();
    int tempData;
    };

#endif // TEMP_H
