#Dante Eleutério dos Santos GRR20206686 UFPR Curitiba


CFLAGS = -Wall -std=c99

ALLEGROFLAGS= $$(pkg-config allegro-5 allegro_font-5 allegro_ttf-5 allegro_image-5 allegro_audio-5 allegro_acodec-5 allegro_primitives-5 --libs --cflags)

objects = main.o headers.o display.o map.o drawing.o keyboard.o


all: boulderdash

boulderdash: $(objects)
	gcc	-o boulderdash $(objects) $(CFLAGS) $(ALLEGROFLAGS)
main.o:	main.c headers.h display.h map.h drawing.h keyboard.h
	gcc -c main.c  $(CFLAGS) $(ALLEGROFLAGS)
headers.o:	headers.c headers.h
	gcc -c headers.c $(CFLAGS) $(ALLEGROFLAGS)
display.o: display.c display.h
	gcc -c display.c $(CFLAGS) $(ALLEGROFLAGS)
map.o:	map.c map.h
	gcc -c map.c $(CFLAGS) $(ALLEGROFLAGS)
drawing.o: drawing.c drawing.h
	gcc -c drawing.c $(CFLAGS) $(ALLEGROFLAGS)
keyboard.o:	keyboard.c keyboard.h
	gcc -c keyboard.c $(CFLAGS) $(ALLEGROFLAGS)
clean:
	-rm -f $(objects)
purge:	clean
	-rm -f boulderdash