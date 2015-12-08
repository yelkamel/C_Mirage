# mapcorp

OCAML=ocamlopt
OCAMLFLAGS= -w a -I +sdl -I +lablgtk2
OCAMLLD=lablgtk.cmxa bigarray.cmxa sdl.cmxa sdlloader.cmxa
#SRCS= line.ml
#OBJS=$(SRCS:%.ml=%.o)

.PHONY: all line choose transform

all: line choose transform 

line: line.ml
	${OCAML} ${OCAMLFLAGS} ${OCAMLLD} -o line line.ml

choose: choose.ml
	${OCAML} ${OCAMLFLAGS} ${OCAMLLD} -o choose choose.ml

transform: transform.ml
	${OCAML} ${OCAMLFLAGS} ${OCAMLLD} -o transform transform.ml

#all: $(OBJS)
#	$(OCAML) $(OCAMLLD) -o map $^

#%.o: %.ml
#	$(OCAML) $(OCAMLFLAGS) -o $@ -c $< 

clean::
	rm -f *~ *.o *.cm? a.out truc *.so

# FIN
