#include "serverdefs.h"
#include "serverprotos.h"
#include "serverglobals.h"

int find_ctgy(char* ctgy_name){
    int cindex = 0;
    int catcode;
    while (categories_algorithms[cindex].category != 0 && categories_algorithms[cindex].algorithm == 0){
        catcode = categories_algorithms[cindex].category;
        if (!strcmp(categories_algorithms[cindex].name, ctgy_name))
            return catcode - 1;
        cindex++;
    }
    fprintf(stderr, "[waveserver] Can NOT locate category: %s", ctgy_name);
}

struct wvphsseq* find_seq(int cindex, char* seq_name, struct wvphsseq* seq){
    seq = phaseseqentries[cindex].forqueue;
    while (seq != NULL){
        if (!strcmp(seq->name, seq_name))
            return seq;
        seq = seq->nextseq;
    }
    fprintf(stderr, "[waveserver] Can NOT locate sequence: %s", seq_name);   
}

struct shotphase* find_phase(int cindex, struct wvphsseq* seq, struct shotphase* phase){
    struct waveform_variable *wavelist = seq->wavelist;
    int number;
    for (i = 0; i < wavelist->numvertex; i++){
        number = (int)(wavelist->data[i].y + 0.5);
        phase = phaseentries[cindex].forqueue;
        while (phase != NULL){
            if (phase->number == number)
                return phase;
            phase = phase->nextphase;
        }
    }
    fprintf(stderr, "[waveserver] Can NOT locate phase at category:%s , sequence: %s", categories_algorithms[cindex].name, seq->name); 
}

int find_wave_len(char* alg_name, char* wave_name,struct shotphase* phase){
    int algindex = phase->algorithm;
    char* identifier = get_algorithm_identifier_by_phase(phase);
}

