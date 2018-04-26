#ifndef READWRITEARDUINO_H
#define READWRITEARDUINO_H


class ReadWriteArduino
{
public:
    ReadWriteArduino();
    void readFromArduino(QString incomingData);
    void writeToFile(QString outgoingData);

private:
    QString send_data;

};

#endif // READWRITEARDUINO_H
