#Makefile general 
CFLAGS=-c -std=c99
EXEC=ejecutable
#OPTIMIZACION=-O2 
#OPTION=
#DEBUGEO=-g
CPPS:=$(wildcard src/*.c)
OBJS:=$(patsubst src/%.c,obj/%.o,$(CPPS))
OBJDIR:=obj
#==================================
#Proceso de compilado de programa =
#==================================
all: bin/$(EXEC)
recortar: bin/recortar
bin/$(EXEC):$(OBJS) | bin  
	rm -f $(OBJDIR)/recorta.o
	gcc -o $@ $(OBJS) -std=c99 -lm
bin:
	mkdir -p $@
$(OBJDIR)/%.o: src/%.c | $(OBJDIR)
	gcc $(CFLAGS) -lm $< -o $@
$(OBJDIR): 
	mkdir -p $@ 
bin/recortar:$(OBJS)| bin
	rm -f $(OBJDIR)/main.o 	
	gcc -o $@ $(OBJS) -std=c99 -lm

#obj/lectura.o: source/lectura.c
#	gcc $(CFLAGS) source/lectura.c 
#obj/estructura.o: source/estructura.c
#	gcc $(CFLAGS) source/estructura.c
#=======================
#Proceso de limpieza   =
#=======================
clean: 
	rm $(OBJS) latex/*.aux latex/*.log  

#===============================
#Proceso de compilado de latex =
#===============================
reporte: 
	cd latex && make -f makereporte
	mv latex/*.pdf docs
#	pdflatex -output-directory ./docs  latex/reporte.tex
#=====================
#Mensajes de ayuda   =
#=====================
help: 
	@echo "Hola soy el asistente de ayuda, sus opciones son:"
	@echo " make: el programa compilara desde /source y guardara el"
	@echo "       ejecutable en la carpeta /bin y creara el reporte en /docs "
	@echo " make clean: Elimina los archivos generados por la compilacion"
	@echo "             en las carpetas /obj y /latex"
	@echo " make reporte: Se ejecuta automaticamente con make, puede ejecutarse solo"
	@echo " make help: esta ayuda "
	@echo "Fue un placer atenderle"
