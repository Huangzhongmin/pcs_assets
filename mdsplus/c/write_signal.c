#include "mds_helper.h"

int main(int argc, char* argv[]){
    const char* mds_server = "localhost";
    const char* mds_db = "pcfg_hl2m";
    const int shot = 900123;
    const char *sig_node = ":SIGNAL1";

    float data[1000];
    float timebase[1000];
    for(i = 0; i < 1000; i++){
        data[i] = sin(i / 300.) * cos(i / 20.);
        timebase[i] = i/1000.; 
    }

    create_tree(mds_server, mds_db, shot);

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

    write_signal(SIG_NODE, timebase, data, 1000);

    status = MdsClose(mds_db, &shot);
    if ( !statusOk(status) ){
        fprintf(stderr,"Error closing tree for shot %d: %s.\n",shot,
        MdsGetMsg(status));
        return -1;
    }

    MdsDisconnect(mds_server);
    return 0;
}