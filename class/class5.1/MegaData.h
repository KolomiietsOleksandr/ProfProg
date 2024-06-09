#ifndef MEGADATA_H
#define MEGADATA_H

class MegaData {
public:
    float smallArray[1024];
    double bigArray[1024 * 1024];

    MegaData();
    void reset();
};

#endif
