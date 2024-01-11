ifdef OS
	CPP = g++.exe
	FLAGS = -lwinmm
	RM = del /Q
	FixPath = $(subst /,\,$1)
else
	CPP = c++
	FLAGS = -lncurses
	RM = rm -f 
	FixPath = $1
endif
CFLAGS = -std=c++17 -O2 -s
Nombre = MemoriaExtreem

$(Nombre): main.cpp menus.h JuegoHead.h FuncionesGen.h
	$(CPP) -o $(call FixPath,$(Nombre)) $< $(FLAGS) $(CFLAGS)

clean:
	$(RM) $(call FixPath,$(Nombre).exe)
	$(RM) $(call FixPath,$(Nombre).out)
	$(RM) $(call FixPath,$(Nombre))
	$(RM) $(call FixPath,a.exe)
	$(RM) $(call FixPath,a.out)
