#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef CPP
#  define NAME "mmake++"
#  define EXT "cpp"
#  define COMPIL "g++"
#else
#  define NAME "mmake"
#  define EXT "c"
#  define COMPIL "gcc"
#endif

void show_help(void);

int main(int argc, char ** argv){
    FILE  * fp;
    _Bool   forced   = 0;
    int     id_exec  = argc;
    int     start_cf = argc;
    int     end_cf;
    int     start_lf = argc;
    int     end_lf;
    int     id_cc    = argc;
    int     i;
    size_t  len;

    // loading parameters
    for(i = 1; i < argc; ++i){
	len = strlen(argv[i]);
	if(len >= 4 && !strcmp("--LF", argv[i])){ // --LF
	    start_lf = i + 1;
	    for(end_lf = start_lf; end_lf < argc && (len < 2 || strncmp("--",argv[end_lf],2)); ++end_lf);

	    if(end_lf == start_lf){
		fprintf(stderr, "WARNING : --LF has no parameter, it is ignored [%d]\n", i);
		start_cf = argc;
	    }
	    i = end_lf - 1;
	}else if(len >= 4 && !strcmp("--CF", argv[i])){ // --CF
	    start_cf = i + 1;
	    for(end_cf = start_cf; end_cf < argc && (len < 2 || strncmp("--",argv[end_cf],2)); ++end_cf);

	    if(end_cf == start_cf){
		fprintf(stderr, "WARNING : --CF has no parameter, it is ignored [%d]\n", i);
		start_cf = argc;
	    }
	    i = end_cf - 1;
	}else if(len >= 6 &&
		 (!strncmp("--OUT=", argv[i], 6)
		  || !strncmp("--out=", argv[i], 6))){ // --OUT=
	    if(len == 6){
		fprintf(stderr, "WARNING : --OUT= needs to have a value after the '=' character [%d]\n", i);
	    }else{
		id_exec = i;
	    }
	}else if(len >= 5 &&
		 (!strncmp("--cc=", argv[i], 5)
		  || !strncmp("--CC=", argv[i], 5))){ // --cc=
	    if(len == 5){
		fprintf(stderr, "WARNING : --cc= needs to have a value after the '=' character [%d]\n", i);
	    }else{
		id_cc = i;
	    }
	}else if((len == 3 && !strcmp("--h", argv[i]))
		 || (len == 6 && !strcmp("--help", argv[i]))){ // -h / --help
	    show_help();
	    return 0;
	}else if((len == 3 && !strcmp("--f", argv[i]))
		 || (len == 8 && !strcmp("--forced", argv[i]))){ // -f / --forced
	    forced = 1;
	}else{ // UNKNOWN
	    fprintf(stderr, "WARNING : Unknown argument '%s' [%d]\n", argv[i], i);
	}
    }

    if(!forced){
	fp = fopen("Makefile","r");

	if(fp){
	    fprintf(stderr,"Makefile already exist, rerun with -f option to overwrite\n");
	    fclose(fp);
	    return -1;
	}
    }

    fp = fopen("Makefile","w");
    if(fp){
	#ifdef DEBUG
	printf("CF : %d -> %d\n",start_cf,end_cf);
	printf("LF : %d -> %d\n",start_lf,end_lf);
	printf("id_cc : %d\n",id_cc);
	#endif

	fprintf(fp,
		"#!/bin/makefile\n\n"
		"SRC=$(wildcard *." EXT ")\n"
		"OFILES=$(SRC:.o=." EXT ")\n"
		"EXEC=");
	
	if(argc <= id_exec)
	    fprintf(fp,"a.out\n");
	else
	    fprintf(fp,"%s\n",argv[id_exec] + 6);
	
	fprintf(fp,
		"LDFLAGS=");
	for(i = start_lf; i < end_lf && i < argc; ++i)
	    fprintf(fp,"%s ",argv[i]);
	
	fprintf(fp,
		"\nCFLAGS=");
	for(i = start_cf; i < end_cf && i < argc; ++i)
	    fprintf(fp,"%s ",argv[i]);

	fprintf(fp,
		"\nCC=%s",id_cc < argc ? argv[id_cc] + 5 : COMPIL);
	fprintf(fp,"\nCLEAN=*.o *~\n\n"
		"all:$(EXEC)\n\n"
		"$(EXEC):$(OFILES)\n"
		"\t$(CC) $^ -o $@ $(LDFLAGS)\n\n"
		"%c.%c:%c." EXT "\n"
		"\t$(CC) -c $< $(CFLAGS)\n\n"
		"clean:\n"
		"\trm $(CLEAN)\n\n"
		"clear: clean\n\n"
		"cleaner:\n"
		"\trm $(EXEC) $(CLEAN)\n\n",'%','o','%'
	    );
	
	fclose(fp);
    }else{
	fprintf(stderr,"Failed to create%s the Makefile file.\n",forced ? "/overwrite" : "");
	return -2;
    }

    return 0;
}

void show_help(){
    puts(NAME " is a program made by Klevh (Baptiste Apollinaire PRUNIER)\n\n"
	"How to use it :\n"
	"\t" NAME " [--OUT=...] [--LF ...] [--CF ...] [--cc=...] [--h or --help] [--f or --forced]\n\n"
	"Parameters :\n"
	"\t--OUT=...       : define the program's name as '...'\n"
	"\t--cc=...        : define the compiler's name as '...'\n"
	"\t--h or --help   : show this help\n"
	"\t--f or --forced : overwrite the Makefile file if it exists\n"
	"\t--LF ...        : define all flags to put during linking\n"
	"\t--CF ...        : define all flags to put during compilation\n");
}
