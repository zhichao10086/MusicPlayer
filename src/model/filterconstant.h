#ifndef FILTERCONSTANT_H
#define FILTERCONSTANT_H


#include <QString>

const QString FILTER_EQUALIZER_NAME = "equalizer";

const int EQUALIZER_FILTER_COUNT = 10;

const QString Equalizer_instance_name[] = {   "equalizer35",
                                        "equalizer64",
                                        "equalizer125",
                                        "equalizer250",
                                        "equalizer500",
                                        "equalizer1K",
                                        "equalizer2K",
                                        "equalizer4K",
                                        "equalizer8K",
                                        "equalizer16K"};

const QString equalizer_config_name[] = {"frequency",
                                  "width_type",
                                  "width",
                                  "gain",
                                  "instance_name"};

const int equalizer_freqs[]={     35,
                             64,
                             125,
                             250,
                             500,
                             1000,
                             2000,
                             4000,
                             8000,
                             16000};



typedef struct FilterConfig{

}FilterCtx;



class FilterConstant
{
public:
    FilterConstant();
};

#endif // FILTERCONSTANT_H
