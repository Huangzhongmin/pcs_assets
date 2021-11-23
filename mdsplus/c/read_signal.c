#include "mds_helper.h"

int main(int argc, char* argv[]){
    const char* mds_server = "localhost";
    const char* mds_db = "pcfg_hl2m";
    const int shot = 900123;
    const char* sig_node = ":SIGNAL1";
    const char* sig_timebase = "DIM_OF(:SIGNAL1)";

    int dtypeFloat = DTYPE_FLOAT;
    int null = 0;
    int status; 
    int socket; 
    float *data; 
    float *timebase; 
    int sigDesc; 
    int timeDesc;
    int size; 
 
    socket = MdsConnect(mds_server);
    if ( socket == -1 ){
        fprintf(stderr,"Error connecting to mdsip server.\n");
        return -1;
    }

    status = MdsOpen(mds_db, &shot);
    if ( !statusOk(status) ){
        fprintf(stderr,"Error opening tree for shot %d: %s.\n",shot, MdsGetMsg(status));
        return -1;
    }

    size = getSize(sig_node);
    if ( size < 1 ){
        fprintf(stderr,"Error retrieving length of signal\n");
        return -1;
    }

    data = (float *)malloc(size * sizeof(float));
    if ( !data ){
        fprintf(stderr,"Error allocating memory for data\n");
        return -1;
    }
    timebase = (float *)malloc(size * sizeof(float));
    if ( !timebase ){
        fprintf(stderr,"Error allocating memory for timebase\n");
        free( (void *)data );
        return -1;      
    }

    sigDesc = descr(&dtypeFloat, data, &size, &null);
    timeDesc = descr(&dtypeFloat, timebase, &size, &null);

    status = MdsValue(sig_node, &sigDesc, &null, &retLen );
    if ( !statusOk(status) ){
        fprintf(stderr,"Error retrieving signal: %s\n", MdsGetMsg(status));
        return -1;
    }

    status = MdsValue(sig_timebase, &timeDesc, &null, &retLen);
    if ( !statusOk(status) ){
        fprintf(stderr,"Error retrieving timebase: %s\n", MdsGetMsg(status));
        free( (void *)data );
        free( (void *)timebase );
        return -1;
    }

    int i;
    for ( i = 0 ; i < size ; i++ )
        printf("%i X:%f Y:%f\n", i, timebase[i], data[i]);

    free( (void *)data);
    free( (void *)timebase);

    MdsClose(mds_db, &shot);
    MdsDisconnect(mds_server);

    return 0;
}